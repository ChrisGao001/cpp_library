enum DataType : int32_t {
    kInt8 = proto::DataType::kInt8,
    kInt16 = proto::DataType::kInt16,
    kInt32 = proto::DataType::kInt32,
    kInt64 = proto::DataType::kInt64,
    kFloat = proto::DataType::kFloat,
    kDouble = proto::DataType::kDouble,
    kBool = proto::DataType::kBool
};
}

using types::DataType;

/**
 * template used to convert between enum and type
 */
template <class T>
struct DataTypeToEnum {};

template <DataType VALUE>
struct EnumToDataType {};

#define MATCH_TYPE_AND_ENUM(TYPE, ENUM)                   \
    template <>                                           \
    struct DataTypeToEnum<TYPE> {                         \
        static DataType v() { return DataType::ENUM; }    \
        static constexpr DataType value = DataType::ENUM; \
    };                                                    \
    template <>                                           \
    struct EnumToDataType<DataType::ENUM> {               \
        typedef TYPE Type;                                \
    }

MATCH_TYPE_AND_ENUM(int8_t, kInt8);
MATCH_TYPE_AND_ENUM(int16_t, kInt16);
MATCH_TYPE_AND_ENUM(int32_t, kInt32);
MATCH_TYPE_AND_ENUM(int64_t, kInt64);
MATCH_TYPE_AND_ENUM(float, kFloat);
MATCH_TYPE_AND_ENUM(double, kDouble);
MATCH_TYPE_AND_ENUM(bool, kBool);
