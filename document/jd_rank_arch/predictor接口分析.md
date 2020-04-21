### tensorflow serving接口

```protobuf
message PredictRequest {
  // Model Specification. If version is not specified, will use the latest
  // (numerical) version.
  ModelSpec model_spec = 1;

  // Input tensors.
  // Names of input tensor are alias names. The mapping from aliases to real
  // input tensor names is stored in the SavedModel export as a prediction
  // SignatureDef under the 'inputs' field.
  map<string, TensorProto> inputs = 2;

  // Output filter.
  // Names specified are alias names. The mapping from aliases to real output
  // tensor names is stored in the SavedModel export as a prediction
  // SignatureDef under the 'outputs' field.
  // Only tensors specified here will be run/fetched and returned, with the
  // exception that when none is specified, all tensors specified in the
  // named signature will be run/fetched and returned.
  repeated string output_filter = 3;
}

// Response for PredictRequest on successful run.
message PredictResponse {
  // Effective Model Specification used to process PredictRequest.
  ModelSpec model_spec = 2;

  // Output tensors.
  map<string, TensorProto> outputs = 1;

  string tfs_infos = 4;
}
```

### tensorflow Example

```protobuf
message Feature {
  // Each feature can be exactly one kind.
  oneof kind {
    BytesList bytes_list = 1;
    FloatList float_list = 2;
    Int64List int64_list = 3;
  }
};

message Features {
  // Map from feature name to feature.
  map<string, Feature> feature = 1;
};

// Containers for sequential data.
//
// A FeatureList contains lists of Features.  These may hold zero or more
// Feature values.
//
// FeatureLists are organized into categories by name.  The FeatureLists message
// contains the mapping from name to FeatureList.
//
message Example {
   Features features = 1;
};
```

### predictor server接口

```protobuf
message Value {
  message StringList {
    repeated string value = 1;
  }
  message DoubleList {
    repeated double value = 1;
  }
  message IntList {
    repeated int64 value = 1;
  }
  message ByteList {
    repeated bytes value = 1;
  }
  oneof value {
    string s_value = 1;
    double d_value = 2;
    int64 i_value = 3;
    bytes b_value = 4;
    StringList s_list = 5;
    DoubleList d_list = 6;
    IntList i_list = 7;
    ByteList b_list = 8;
  }
}

message Feature {
  map<string, Value> value_map = 1;
}


message InferenceRequest {
  RequestHeader header = 1;
  ExtendInfo extend_info = 2;
  Feature common_features = 3;
  repeated Feature samples = 4;
}：


message InferenceResponse {
  repeated SampleOutput output = 1;
}

```



