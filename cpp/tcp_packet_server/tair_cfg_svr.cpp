/*
 * (C) 2007-2017 Alibaba Group Holding Limited
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * See the AUTHORS file for names of contributors.
 *
 */

#include "tair_cfg_svr.hpp"
#include "easy_helper.hpp"
#include "response_return_packet.hpp"
#include "ping_packet.hpp"
#include "log.hpp"

namespace tair {
namespace config_server {
tair_config_server *tair_config_server::_this = NULL;

tair_config_server::tair_config_server() {
    stop_flag = 0;
    _this = this;
    memset(&eio, 0, sizeof(eio));
}

tair_config_server::~tair_config_server() {
}

void tair_config_server::start() {
    if (initialize() != EXIT_SUCCESS) {
        return;
    }
    int port = 23456;
    easy_listen_t *listen = easy_io_add_listen(&eio, NULL, port, &handler);
    if (listen == NULL) {
      log_error("listen port %d error", port);
    } else {
      log_info("listen tcp port: %d", port);
    }

    if (listen) {
        log_info("---- program stated PID: %d ----", getpid());
        easy_io_start(&eio);
    } else {
        stop();
    }

    //my_server_conf_thread.wait();
    easy_io_wait(&eio);

    destroy();
}

void tair_config_server::stop() {
    if (stop_flag == 0) {
        stop_flag = 1;
        log_warn("will stop eio");
        easy_io_stop(&eio);
        log_warn("will stop server_conf_thread");
    }
}

int tair_config_server::initialize() {
    int task_thread_count = 3;
    int io_thread_count = 2;

    //~ create eio
    log_warn("task_thread_count=%d,io_thread_count=%d",task_thread_count,io_thread_count);
    if (!easy_io_create(&eio, io_thread_count)) {
        log_error("create eio failed");
        return EXIT_FAILURE;
    }
    eio.do_signal = 0;
    eio.no_redispatch = 0;
    eio.listen_all = 1;
    eio.no_reuseport = 1;
    eio.tcp_nodelay = 1;
    eio.tcp_cork = 0;
    eio.affinity_enable = 1;

    //~ initialize eio handler
    easy_helper::init_handler(&handler, this);
    handler.process = easy_io_packet_handler_cb;

    //~ create thread pool
    task_queue = easy_request_thread_create(&eio, task_thread_count, packet_handler_cb, NULL);

    return EXIT_SUCCESS;
}

int tair_config_server::destroy() {
    easy_io_destroy(&eio);
    return EXIT_SUCCESS;
}

int tair_config_server::easy_io_packet_handler(easy_request_t *r) {
    base_packet *packet = (base_packet *) r->ipacket;
    if (packet == NULL || !packet->isRegularPacket()) {
        log_error("ControlPacket, timeout");
        return EASY_OK;
    }

    packet->set_direction(DIRECTION_RECEIVE);
    // set hash_code is 0, libeasy will rehash it by addr of struct connection_t
    easy_thread_pool_push(task_queue, r, 0);
    return EASY_AGAIN;
}

int tair_config_server::packet_handler(easy_request_t *r) {
    base_packet *packet = (base_packet *) r->ipacket;
    int pcode = packet->getPCode();

    bool send_ret = true;
    int ret = EXIT_SUCCESS;
    log_error("handle packet pcode: %d", pcode);
    const char *msg = "this is ping packet";
    switch (pcode) {
        case TAIR_REQ_PING_PACKET: {
            response_return *resp = new response_return(packet->getChannelId(), ret, msg, 0);
            request_ping *req = (request_ping*)packet; 
            log_error("ping packet version:%d,value:%d", req->config_version, req->value);
            r->opacket = resp;
            send_ret = false;
            break;
        }
        default:
            log_error("unknow packet pcode: %d", pcode);
    }
    if (send_ret && packet->get_direction() == DIRECTION_RECEIVE) {
        response_return *resp = new response_return(packet->getChannelId(), ret, msg, 0);
        r->opacket = resp;
    }
    return EASY_OK;
}
}
} // namespace end

////////////////////////////////////////////////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////////////////////////////////////////////////
tair::config_server::tair_config_server *tair_cfg_svr = NULL;

void
sign_handler(int sig) {
}

void
print_usage(char *prog_name) {
    fprintf(stderr, "%s -f config_file\n"
            "    -f, --config_file  config file\n"
            "    -h, --help         this help\n"
            "    -V, --version      version\n\n", prog_name);
}

char *
parse_cmd_line(int argc, char *const argv[]) {
    int opt;
    const char *opt_string = "hVf:";
    struct option longopts[] = {
            {"config_file", 1, NULL, 'f'},
            {"help",        0, NULL, 'h'},
            {"version",     0, NULL, 'V'},
            {0,             0, 0,    0}
    };

    char *config_file = NULL;
    while ((opt = getopt_long(argc, argv, opt_string, longopts, NULL)) != -1) {
        switch (opt) {
            case 'f':
                config_file = optarg;
                break;
            case 'V':
                //fprintf(stderr, "BUILD_TIME: %s %s\nGIT: %s\n", __DATE__, __TIME__, TAIR_GIT_INFO);
                exit(1);
            case 'h':
                print_usage(argv[0]);
                exit(1);
        }
    }
    return config_file;
}

int main(int argc, char *argv[]) {
    // parse cmd
    //char *config_file = parse_cmd_line(argc, argv);

    log_info("start program.");
    //if (tbsys::CProcess::startDaemon(sz_pid_file, sz_log_file) == 0) {
    
        signal(SIGPIPE, SIG_IGN);
        signal(SIGHUP, SIG_IGN);
        signal(SIGINT, sign_handler);
        signal(SIGTERM, sign_handler);
        signal(40, sign_handler);
        signal(41, sign_handler);
        signal(42, sign_handler);

        tair_cfg_svr = new tair::config_server::tair_config_server();
        tair_cfg_svr->start();

        // ignore signal when destroy, cause sig_handler may use tair_cfg_svr between delete and set it to NULL.
        signal(SIGINT, SIG_IGN);
        signal(SIGTERM, SIG_IGN);

        delete tair_cfg_svr;
        tair_cfg_svr = NULL;

        log_info("exit program.");
    //}

    return EXIT_SUCCESS;
}

////////////////////////////////END
