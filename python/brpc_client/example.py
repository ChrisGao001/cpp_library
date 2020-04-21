#coding: utf-8

from brpc_client import BrpcClient
import echo_pb2
import sys

if __name__ == '__main__':
    ip = "localhost"
    port = 8000
    client = BrpcClient(ip, port)
    req_msg = echo_pb2.EchoRequest()
    req_msg.message = "hello world"
    res_msg = echo_pb2.EchoResponse()
    sys.stdout.write("request :" + str(req_msg))
    rc = client.send_req("EchoService", "Echo", req_msg, res_msg)
    if not rc:
        sys.exit(1)
    sys.stdout.write("response: " + str(res_msg))
    

