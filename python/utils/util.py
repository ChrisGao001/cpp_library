import zipfile

def pb2json(pb):
    from google.protobuf.json_format import MessageToJson
    data = (MessageToJson(req))
    data = data.replace("\n","").replace(" ","")
    return data

def save_protobuf(path, message, as_text=False):
    from google.protobuf import text_format
    dir_name = os.path.dirname(path)
    if dir_name:
        os.makedirs(dir_name, exist_ok=True)
    if as_text:
        with open(path, "w") as f:
            f.write(text_format.MessageToString(message))
    else:
        with open(path, "wb") as f:
            f.write(message.SerializeToString())


def save_onnx_zip(target_path, model_proto, external_tensor_storage):
    """ use zip save file"""
    with zipfile.ZipFile(target_path, 'w') as z:
        z.writestr("__MODEL_PROTO.onnx", model_proto.SerializeToString())
        for k, v in external_tensor_storage.name_to_tensor_data.items():
            z.writestr(k, v)

def model_proto_from_zip(zip_path, external_tensor_storage):
    model_proto = ModelProto()
    with zipfile.ZipFile(zip_path, 'r') as z:
        for n in z.namelist():
            f = z.open(n)
            if n.endswith(".onnx"):
                model_proto.ParseFromString(f.read())
            else:
                external_tensor_storage.name_to_tensor_data[n] = f.read()
    return model_proto
