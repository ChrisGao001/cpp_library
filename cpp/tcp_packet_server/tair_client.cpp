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

#include <byteswap.h>
#include "response_return_packet.hpp"
#include "ping_packet.hpp"
#include "common/easy_helper.hpp"
#include "packet.hpp"
#include "log.hpp"
#include "client.hpp"

#define TAIR_PACKET_FLAG             0x6D426454

using namespace tair;
void append(string &data, int n) {
    data.append((char *)&n, 4);
}

int main(int argc, char *argv[]) {
    log_info("start client.");
    int port = 23456;
    Client client("localhost", 23456);
    client.create();

    string data;
    append(data, bswap_32(TAIR_PACKET_FLAG)); 
    append(data, bswap_32(5));
    append(data, bswap_32(TAIR_REQ_PING_PACKET));
    append(data, bswap_32(8));
    append(data,bswap_32(2345));
    append(data, bswap_32(6789));
    client.send_request(data);
    
    return EXIT_SUCCESS;
}

////////////////////////////////END
