## Optimizing for CPU

CPUs, which includes Intel® Xeon Phi™, achieve optimal performance when TensorFlow is @{install_sources*i**n**s**t**a**l**l**s**o**u**r**c**e**s*built from source} with all of the instructions supported by the target CPU.

Beyond using the latest instruction sets, Intel® has added support for the Intel® Math Kernel Library for Deep Neural Networks (Intel® MKL-DNN) to TensorFlow. While the name is not completely accurate, these optimizations are often simply referred to as 'MKL' or 'TensorFlow with MKL'. [TensorFlow with Intel® MKL-DNN](vscode-resource://file///Users/gaoyumin/project/github/ad_tensorflow/tensorflow/docs_src/performance/performance_guide.md#tensorflowwithintelmkldnn) contains details on the MKL optimizations.

The two configurations listed below are used to optimize CPU performance by adjusting the thread pools.

- `intra_op_parallelism_threads`: Nodes that can use multiple threads to parallelize their execution will schedule the individual pieces into this pool.
- `inter_op_parallelism_threads`: All ready nodes are scheduled in this pool.



```bash
./configure
# Pick the desired options
bazel build --config=mkl --config=opt //tensorflow/tools/pip_package:build_pip_package
```

```bash
python tf_cnn_benchmarks.py --forward_only=True --device=cpu --mkl=True \
--kmp_blocktime=0 --nodistortions --model=resnet50 --data_format=NCHW \
--batch_size=1 --num_inter_threads=1 --num_intra_threads=4 \
--data_dir=<path to ImageNet TFRecords>
```

