### 编译

#### 依赖环境

+ gcc5.4

  ```bash
  密码： lijian
  scp lijian@10.181.47.140:/export/lijian/tools/gcc54.sh .  
  sudo sh gcc54.sh
  ```

+ bazel 0.18

  ```bash
  wget https://github.com/bazelbuild/bazel/releases/download/0.18.0/bazel-0.18.0-installer-linux-x86_64.sh
  sh bazel-0.18.0-installer-linux-x86_64.sh --prefix=/export/opt/bazel
  ```

+ python tensorflow v1.10.1

  ```bash
  wget https://repo.anaconda.com/archive/Anaconda2-2019.10-Linux-x86_64.sh
  pip install tensorflow==1.10.1
  ```

  

### predictor编译

```bash
git clone git@git.jd.com:ads-model-service/model_predictor.git
cd model_predictor
git submodule update --init --recursive
python config.py -tf=1.10
bazel build //server:predictor_server
ll bazel-bin/server/predictor_server
```



### demo

1. 生成模型文件

```bash

cd example/tensorflow
python make_data.py
python train.py
```

2. 将模型数据拷贝到predictor server

    ```bash
   tensorflow/
   |-- model
   |   |-- saved_model.pbtxt
   |   |-- tensor_stream.conf
   |   `-- variables
   |       |-- variables.data-00000-of-00001
   |       `-- variables.index
   `-- model.status
    ```

   

3. 修改dict.conf path建议使用绝对路径

   

   ```bash
   [
       {
           "id": "tf_model",
           "update_interval": 30,
           "path": "/export/project/ad/model_predictor/example/general_server/tensorflow/model",
           "class_name": "TFGraphModel"
       }
   ]
   ```

   

4. 重新生成dict.conf MD5

   ```bash
   md5sum dict.conf > dict.conf.status
   ```

5. 启动server

   ```bash
   cd model_predictor/example/general_server
   cp ../../bazel-bin/server/predictor_server .
   sh start.sh
   ```

   

6. 运行client

   ```bash
   cd client
   python send_request.py --ip_address=127.0.0.1 --port=8010 --batch_size=1 --file_path=test.txt 
   ```

   

7. 资源

   ```shell
   /export/lijian/git/ads-model/tensorflow_r1.10
   brpc       focus        lightbridge      norm_guard                  Photon            predictord_online_conf  predictor_online_conf  rpc-proxy-online  tensorflow_compile
   client     grpc         lightbridge_bak  online_model_pressure_test  predictor         predictor_lib_rpc       proxy_online_conf      rpc_proxy_server  tensorflow_r1.10
   client.py  jsf_wrapper  motor_inference  personalized_server         predictor_client  predictor_new_client    rpc_creative_server    tensorflow_1.15   third_party
   ```

   