bazel build @com_google_protobuf//:protoc
../bazel-bin/external/com_google_protobuf/protoc --python_out=./ model_proto/baidu_rpc_meta.proto model_proto/brpc/*
