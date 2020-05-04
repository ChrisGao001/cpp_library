def pb2json(pb):
    from google.protobuf.json_format import MessageToJson
    data = (MessageToJson(req))
    data = data.replace("\n","").replace(" ","")
    return data
