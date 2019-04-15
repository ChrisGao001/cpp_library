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

#include "packet_factory.hpp"
#include "easy_helper.hpp"
#include "base_packet.hpp"
#include "ping_packet.hpp"
#include "response_return_packet.hpp"

#define TAIR_PACKET_FLAG             0x6D426454
namespace tair {
easy_atomic32_t packet_factory::chid = 100;

void *packet_factory::decode_cb(easy_message_t *m) {
    if (m->input->last - m->input->pos < (int) (4 * sizeof(int))) {
        log_debug("packet header not complete");
        return NULL;
    }

    assert(m->pool->tlock <= 1 && m->pool->flags <= 1);
    DataBuffer input(m->input);
    int flag = input.readInt32();
    int chid = input.readInt32();
    int pcode = input.readInt32();
    int len = input.readInt32();
    if (flag != TAIR_PACKET_FLAG || len < 0 || len > (1 << 26) /* 64M */) {
        log_error("decoding failed: flag=%d, len=%d, m->status=%d, pcode=%d",
                  flag, len, m->status, pcode);
        m->status = EASY_ERROR;
        return NULL;
    }
    // set one packet end offset
    // end postion = now postion + len
    input.setLastReadMark(len);

    if (m->input->last - m->input->pos < len) {
        //~ data not enough
        log_debug("data in buffer not enough for a whole packet: data_len=%d, buf_len=%lu, pcode=%d",
                  len, m->input->last - m->input->pos, pcode);
        m->next_read_len = len - (m->input->last - m->input->pos);
        m->input->pos -= 4 * sizeof(int); //~ restore buffer
        return NULL;
    }

    base_packet *bp = create_packet(pcode);
    if (bp == NULL) {
        m->status = EASY_ERROR;
        log_error("create packet failed: pcode=%d", pcode);
        return NULL;
    }
    bp->_packetHeader._chid = chid;
    bp->_packetHeader._pcode = pcode;
    bp->_packetHeader._dataLen = len;
    bp->peer_id = easy_helper::convert_addr(m->c->addr);
#if 0
    if (bp->_packetHeader._pcode == TAIR_FLOW_CONTROL) {
        flow_control *control = dynamic_cast<flow_control *>(bp);
        control->set_user_data(m->c->handler->user_data);
        control->set_addr(m->c->addr);
    }
#endif

    uint8_t *start = (uint8_t *) m->input->pos;
    if (!bp->decode(&input, &bp->_packetHeader)) {
        log_error("decoding packet failed: pcode=%d", pcode);
        delete bp;
        m->status = EASY_ERROR;
        return NULL;
    }

    if (start + len != (uint8_t *) m->input->pos) {
        m->status = EASY_ERROR;
        delete bp;
        log_error("len not match");
        return NULL;
    }

    assert(m->pool->tlock <= 1 && m->pool->flags <= 1);
    return bp;
}

int packet_factory::encode_cb(easy_request_t *r, void *packet) {
    base_packet *bp = (base_packet *) packet;
    bool flip = true; //! only should client send one packet one time
    while (bp != NULL) {
        if (!flip) {
            log_warn("not allowed for client to send multiple packets once");
            break;
        }
        if (r->ms->c->type == EASY_TYPE_CLIENT) {
            bp->_packetHeader._chid = (uint32_t) ((easy_session_t *) r->ms)->packet_id;
            flip = false;
        } else if (r->ms->c->type == EASY_TYPE_SERVER) {
            if (((easy_message_t *) r->ms)->status == EASY_MESG_DESTROY) {
                return EASY_ERROR;
            }
            if (r->retcode == EASY_ABORT) {
                r->ms->c->pool->ref--;
                easy_atomic_dec(&r->ms->pool->ref);
                r->retcode = EASY_OK;
            }
        }

        easy_list_t list;
        easy_list_init(&list);
        DataBuffer output(r->ms->pool, &list);

        output.reserve(bp->size() + sizeof(bp->_packetHeader));

        output.writeInt32(TAIR_PACKET_FLAG);
        output.writeInt32(bp->_packetHeader._chid);
        output.writeInt32(bp->_packetHeader._pcode);

        output.writeInt32(0); //~ placeholder for data length
        easy_buf_t *b = easy_list_get_last(&list, easy_buf_t, node);
        uint32_t *len_pos = (uint32_t *) (b->last - 4);

        if (!bp->encode(&output)) {
            return EASY_ERROR;
        }

        int len = 0;
        b = NULL;
        easy_list_for_each_entry(b, &list, node)
        {
            len += b->last - b->pos;
        }
        len -= TAIR_PACKET_HEADER_SIZE;
        *len_pos = bswap_32(len);

        easy_request_addbuf_list(r, &list); //~ add buffers into `request'
        bp = (base_packet *) bp->_next;
    }
    return EASY_OK;
}

uint64_t packet_factory::get_packet_id_cb(easy_connection_t *c, void *packet) {
    int32_t packet_id = 0;
    if (packet != NULL) {
        base_packet *bp = (base_packet *) packet;
        packet_id = bp->getChannelId();
    }
    if (packet_id == 0) {
        while (packet_id == 0 || packet_id == -1) {
            packet_id = (int32_t) easy_atomic32_add_return(&chid, 1);
        }
    }
    return packet_id;
}

base_packet *packet_factory::create_packet(int pcode) {
    base_packet *packet = NULL;
    bool control_cmd = false;
    switch (pcode) {
        case TAIR_REQ_PING_PACKET:
            packet = new request_ping();
            break;
        case TAIR_RESP_RETURN_PACKET:
            packet = new response_return();
            break;
        default:
            log_error("create packet failed: pcode=%d", pcode);
            break;
    }
    if (packet != NULL) {
        assert(pcode == packet->getPCode());
    }
    if (control_cmd) {
        ((base_packet *) packet)->control_cmd = true;
    }
    return packet;
}

base_packet *packet_factory::create_dup_packet(base_packet *ipacket) {
    int pcode = ipacket->getPCode();
    base_packet *bp = NULL;
    switch (pcode) {
        default:
            log_error("create duplicate packet failed: pcode=%d", pcode);
            return NULL;
            break;
    }
    bp->setChannelId(0);
    bp->server_flag = TAIR_SERVERFLAG_DUPLICATE;
    return bp;
}

base_packet *packet_factory::create_response(const base_packet *p) {
    switch (p->getPCode()) {
        default:
            return NULL;
        case TAIR_REQ_PUT_PACKET:
        case TAIR_REQ_REMOVE_PACKET:
        case TAIR_REQ_PING_PACKET:
        case TAIR_REQ_LOCK_PACKET:
        case TAIR_REQ_HIDE_PACKET:
        case TAIR_REQ_EXPIRE_PACKET:
            return new response_return;
    }
}

}
