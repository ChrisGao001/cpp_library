## TensorShape
```c++
// Tensorshape构造传入ArraySlice或初始化列表建议第二种
explicit TensorShapeBase(gtl::ArraySlice<int64> dim_sizes);
TensorShapeBase(std::initializer_list<int64> dim_sizes)
```
### OpKernelContext

```c++
    void Compute(OpKernelContext* context) override {
        std::vector<std::string> out;

        // Grab the input tensor
        if (context->num_inputs() > 0) {
            // get input tensor
            const Tensor& input_tensor = context->input(0);
            // convert tensor to array
            auto input = input_tensor.flat<string>(); 
            if (input.size())
                jd_search_level::tokenize(input(0), &out);
        }

        Tensor* output_tensor = NULL;
        // create output tensor
        OP_REQUIRES_OK(context, context->allocate_output(
                0, TensorShape{static_cast<int64>(out.size())}, &output_tensor));
        // set value
        auto output_flat = output_tensor->flat<string>();
        for (size_t i = 0; i < out.size(); ++i) {
            output_flat(i) = std::move(out[i]);
        }
    }
```



### customer op load 

```c++
  // Load the library.
  TF_Status* status = TF_NewStatus();
  TF_Library* lib =
      TF_LoadLibrary("tensorflow/c/test_op.so", status);
  TF_Code code = TF_GetCode(status);
  string status_msg(TF_Message(status));
  TF_DeleteStatus(status);
  ASSERT_EQ(TF_OK, code) << status_msg;

  // Test op list.
  TF_Buffer op_list_buf = TF_GetOpList(lib);
  tensorflow::OpList op_list;
  EXPECT_TRUE(op_list.ParseFromArray(op_list_buf.data, op_list_buf.length));
  ASSERT_EQ(op_list.op_size(), 1);
  EXPECT_EQ("TestCApi", op_list.op(0).name());

  TF_DeleteLibraryHandle(lib);
```



