##############third party########################

package(default_visibility = ["//visibility:public"],)

licenses(["notice"])  # Apache 2.0

# check git repo version
genrule(
    name = "check_git_version",
    outs = ["check_git_version.txt"],
    visibility = ["//visibility:private"],
    cmd = "echo '1' > $@ && ./$(location check_git_version_sh)",
    tools = [":check_git_version_sh"],
)

sh_binary(
    name = "check_git_version_sh",
    srcs = ["check_repo_version.py",],
    visibility = ["//visibility:public",],
)

cc_library(
    name = "base64",
    hdrs = glob(["base64/include/*.h"]),
    srcs = glob(["base64/include/*.cpp"]),
    includes = ["base64/include/"],
    visibility = ["//visibility:public",],
)

cc_library(
    name = "grpc",
    hdrs = glob(["grpc/include/**/*.h"]),
    srcs = glob(["grpc/lib/*.a"]),
    includes = ["grpc/include/"],
    visibility = ["//visibility:public",],
)

cc_library(
    name = "protobuf",
    hdrs = glob(["google/protobuf/include/**/*.h"]),
    srcs = glob(["google/protobuf/lib/*.a"]),
    includes = ["google/protobuf/include/"],
    visibility = ["//visibility:public",],
)

cc_library(
    name = "boost",
    hdrs = glob([
        "boost/include/**/*.hpp",
        "boost/include/**/*.h",
    	"boost/include/**/*.ipp",
        "boost/include/**/**/*.hpp",
        "boost/include/**/**/*.h",
        "boost/include/**/**/**/*.hpp",
        "boost/include/**/**/**/*.h",
    ],
    exclude = ["boost/include/boost/test/*"],),
    srcs = glob(["boost/lib/**/*.a", "boost/lib/*.a",],
        exclude = ["boost/lib/*_test_*", "boost/lib/*_prg_exec_*"],),
    includes = ["boost/include",],
    deps = [":zlib", ":iconv"],
    visibility = ["//visibility:public",],
)

cc_library(
    name = "boost_lexical_cast",
    hdrs = glob([
        "boost/include/boost/lexical_cast.hpp",
        "boost/include/boost/lexical_cast/**/*.hpp",
    ]),
    includes = ["boost/include",],
    visibility = ["//visibility:public",],
)

cc_library(
    name = "boost_string_algo",
    hdrs = glob([
        "boost/include/boost/algorithm/string.hpp",
        "boost/include/boost/algorithm/string/**/*.hpp",
    ]),
    includes = ["boost/include",],
    visibility = ["//visibility:public",],
)

cc_library(
    name = "boost_filesystem",
    hdrs = glob([
        "boost/include/boost/filesystem.hpp",
        "boost/include/boost/filesystem/**/*.hpp",
    ]),
    includes = ["boost/include",],
    srcs = glob([
        "boost/lib/libboost_filesystem.a",
        "boost/lib/libboost_system.a",
    ]),
    visibility = ["//visibility:public",],
)

cc_library(
    name = "boost_thread",
    hdrs = glob([
        "boost/include/boost/thread.hpp",
        "boost/include/boost/thread/**/*.hpp",
        "boost/include/boost/system/**/*.hpp",
    ]),
    includes = ["boost/include",],
    srcs = glob([
        "boost/lib/libboost_thread.a",
        "boost/lib/libboost_system.a",
    ]),
    visibility = ["//visibility:public",],
)

cc_library(
    name = "boost_locale",
    hdrs = glob([
        "boost/include/boost/locale.hpp",
        "boost/include/boost/locale/**/*.hpp",
    ]),
    includes = ["boost/include",],
    srcs = glob([
        "boost/lib/libboost_locale.a",
    ]),
    visibility = ["//visibility:public",],
)

cc_library(
    name = "curl",
    hdrs = glob(["curl/include/**/*.h"]),
    srcs = ["curl/lib/libcurl.a",],
    includes = ["curl/include",],
    deps = [":zlib",],
    visibility = ["//visibility:public",],
)

cc_library(
    name = "cpp_hocon",
    hdrs = glob([
        "cpp_hocon/include/**/*.hpp",
        "cpp_hocon/include/**/*.h"
    ]),
    srcs = glob(["cpp_hocon/lib/*.a"]),
    includes = ["cpp_hocon/include"],
    deps = ["//:leatherman",],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "leatherman",
    hdrs = glob([
        "leatherman/include/leatherman/**/*.hpp",
        "leatherman/include/boost/**/*.hpp",
        "leatherman/include/leatherman/**/*.h",
    ]),
    srcs = glob(["leatherman/lib/*.a"]),
    includes = ["leatherman/include"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "tinyxml",
    hdrs = glob(["tinyxml/include/*.h"]),
    srcs = glob(["tinyxml/lib/*.a",]),
    includes = ["tinyxml/include"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "libxml2",
    srcs = glob(["libxml2/lib/libxml2.so"]),
    hdrs = glob(["libxml2/include/libxml/*.h"]),
    visibility = ["//visibility:public"],
    includes = ["libxml2/include"],
    deps = ["//:iconv", "//:zlib"]
)
"""
cc_import(
    name = "libxml2",
    hdrs = glob(["libxml2/include/libxml/*.h"]),
    static_library = glob(["libxml2/lib/*.a"]),
    visibility = ["//visibility:public"],
    includes = ["libxml2/include"],
    deps = [":iconv", ":zlib"]
)
"""
cc_library(
    name = "iconv",
    srcs = ["iconv/lib/libiconv.a"],
    hdrs = glob(["iconv/include/*.h"]),
    visibility = ["//visibility:public"],
    includes = ["iconv/include"],
)

cc_library(
    name = "gflags",
    srcs = glob(["gflags/lib/*.a"]),
    hdrs = glob(["gflags/include/gflags/*.h"]),
    visibility = ["//visibility:public"],
    includes = ["gflags/include"],
    copts = ["-fPIC"],
)

cc_library(
    name = "feature_trace",
    srcs = glob(["feature_trace/lib/*.a"]),
    hdrs = glob(["feature_trace/include/*.h"]),
    visibility = ["//visibility:public"],
    includes = ["feature_trace/include"],
)

cc_library(
    name = "libutil",
    srcs = glob([
        "libutil/src/*.c",
        "libutil/src/*.cpp",
        "libutil/src/**/*.cc",],
        exclude = [
            "libutil/src/i_command_parser.cpp",
            "libutil/src/gprof-helper.c",
            "libutil/src/test_hashmap2.cpp"
        ],
    ),
    hdrs = glob([
        "libutil/include/*.inl",
        "libutil/include/*.h",
        "libutil/include/**/*.h",
    ]),
    visibility = ["//visibility:public"],
    includes = ["libutil/include"],
    # deps = [":tinyxml", ":boost", ":compress", ":json",":openssl", ":crypto",
        # "@com_github_google_glog//:glog",
    # ],
    deps = [
        ":feature_trace",
        ":boost",
        ":compress",
        "@jsoncpp_git//:jsoncpp",
        "@com_github_google_glog//:glog",
    ],
    linkstatic=True,
)

cc_library(
    name = "cate_util",
    srcs = glob([
        "cate_util/src/cate_judger.cpp",
    ]),
    hdrs = glob([
        "libutil/include/category_tree.h",
        "cate_util/include/cate_judger.h",
        "libutil/include/string_algorithms.h",
    ]),
    includes = ["cate_util/include",],
    visibility = ["//visibility:public",],
    deps = [
        ":boost_lexical_cast",
        "@jd_hocon//lib:jd-cpp-hocon",
        "@com_github_google_glog//:glog",
    ],
)

cc_library(
    name = "rapidjson",
    hdrs = glob(["rapidjson/*.h", "rapidjson/**/*.h"]),
    visibility = ["//visibility:public"],
    includes = ["rapidjson"],
)

cc_library(
    name = "lz4",
    srcs = glob(["lz4/lib/liblz4.a"]),
    hdrs = glob(["lz4/include/*.h"]),
    visibility = ["//visibility:public"],
    includes = ["lz4/include"],
)

cc_library(
    name = "log_trace",
    srcs = glob(["log_trace/src/*.cpp"]),
    hdrs = glob(["log_trace/include/*.h"]),
    visibility = ["//visibility:public"],
    includes = ["log_trace/include"],
)

cc_library(
    name = "snappy",
    srcs = glob(["snappy/lib/libsnappy.a"]),
    hdrs = glob(["snappy/include/*.h"]),
    visibility = ["//visibility:public"],
    linkopts = ["-lpthread"],
    includes = ["snappy/include"],
)

cc_library(
    name = "zlib",
    srcs = glob(["zlib/lib/*.a"]),
    hdrs = glob(["zlib/include/*.h"]),
    visibility = ["//visibility:public"],
    includes = ["zlib/include"],
)


cc_library(
    name = "compress",
    srcs = glob(["compress/lib/*.a"]),
    hdrs = glob(["compress/include/*.h"]),
    visibility = ["//visibility:public"],
    includes = ["compress/include"],
)

cc_library(
    name = "libzip",
    srcs = glob(["libzip/lib/libzip.a"]),
    hdrs = glob(["libzip/include/*.h"]),
    visibility = ["//visibility:public"],
    includes = ["libzip/include"],
)

cc_library(
    name = "seg4",
    srcs = glob([
        "seg4/analyzer/*.c*",
        "seg4/base/*.c*"
    ]),
    hdrs = glob([
        "seg4/analyzer/*.h",
        "seg4/base/*.h"
    ]),
    visibility = ["//visibility:public"],
    includes = ["seg4"],
    deps = [
        ":libutil",
        ":libzip",
        ":tinyxml",
        ":zlib",
    ],
    linkstatic=True,
)

cc_library(
    name = "faiss",
    hdrs = glob(["faiss/include/**/*"]),
    srcs = glob(["faiss/lib/*.a"]),
    includes = ["faiss/include/"],
    visibility = [
        "//visibility:public",
    ],
)

cc_library(
    name = "openblas",
    hdrs = glob(["openblas/include/**/*"]),
    srcs = glob(["openblas/lib/*.a"]),
    includes = ["openblas/include/"],
    visibility = [
        "//visibility:public",
    ],
)

cc_library(
    name = "double-conversion",
    hdrs = glob(["double-conversion/include/**/*"]),
    srcs = ["double-conversion/lib/libdouble-conversion.so",],
    includes = ["double-conversion/include/"],
    visibility = [
        "//visibility:public",
    ],
)

cc_library(
    name = "event2",
    hdrs = glob([
        "event2/include/**/*",
        "event2/include/*.h",
    ]),
    srcs = glob([
        "event2/lib/*.a",
        #"event2/lib/*.la",
        "event2/lib/*.so",
    ]),
    includes = ["event2/include/"],
    visibility = [
        "//visibility:public",
    ],
)

cc_library(
    name = "folly",
    hdrs = glob([
        "folly/include/folly/*",
        "folly/include/**/*",
    ]),
    srcs = glob(["folly/lib/*.a",]),
    includes = ["folly/include/"],
    visibility = [
        "//visibility:public",
    ],
)

cc_library(
    name = "libltdl",
    hdrs = glob([
        "libltdl/include/**/*",
        "libltdl/include/*.h",
    ]),
    srcs = glob([
        "libltdl/lib/libltdl.a",
        "libltdl/lib/libltdl.so",
    ]),
    includes = ["libltdl/include/"],
    visibility = [
        "//visibility:public",
    ],
)

cc_library(
    name = "gmock",
    srcs = glob(["gmock/lib/*.a"]),
    hdrs = glob(["gmock/include/gmock/*.h"]),
    visibility = ["//visibility:public"],
    includes = ["gmock/include"],
    copts = ["-fPIC"],
    deps = [],
)

cc_library(
    name = "msgpack",
    hdrs = glob(["msgpack/*.h",
		"msgpack/*.hpp",
		"msgpack/msgpack/*.h",
                "msgpack/msgpack/*.hpp",
                "msgpack/msgpack/type/*.h",
                "msgpack/msgpack/type/*.hpp",
                "msgpack/msgpack/type/tr1/*.h",
                "msgpack/msgpack/type/tr1/*.hpp"]),
    srcs = glob(["msgpack/lib/*.a"]),
    includes = ["msgpack/msgpack/","msgpack/"],
    visibility = [
        "//visibility:public",
    ],
    linkstatic = 1,
)

cc_library(
    name = "jsf_cpp_client",
    srcs = glob([
        "jsf-cpp-client/lib/jsf/**/*.cpp",
        "jsf-cpp-client/lib/jsf/*.cpp",
    ]),
    includes = [
	"jsf-cpp-client/",
        "jsf-cpp-client/lib/",
        "jsf-cpp-clientlib/jsf/",
    ],
    hdrs = glob([
        "jsf-cpp-client/lib/jsf/*.h",
        "jsf-cpp-client/lib/jsf/**/*.h",
        "jsf-cpp-client/lib/jsf/**/**/*.h",
    ]),
    deps = [
      ":boost",
      ":msgpack",
      ":curl",
      "@com_github_gflags_gflags//:gflags",
    ],
    linkopts = ["-lssl","-lcrypto"],
    visibility = ["//visibility:public",],
)

cc_library(
    name = "jsf_api",
    srcs = glob([
        "jsf_api/jsf_mgr.cc",
        "jsf_api/jsf_mgr_inl.cc",
        "jsf_api/jsf_brpc/*.cc",
    ]),
    includes = [
        "jsf_api/jsf_brpc/",
        "jsf_api/",
    ],
    hdrs = glob([
        "jsf_api/*.h",
        "jsf_api/**/*.h",
    ]),
    deps = [
        ":jsf_cpp_client",
        "@com_github_gflags_gflags//:gflags",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "sparsehash",
    hdrs = glob([
        "sparsehash/include/sparsehash/**/*",
        "sparsehase/google/**/*",
    ]),
    includes = ([
        "sparsehash/include",
    ]),
    visibility = ["//visibility:public"],
)

cc_library(
    name = "jimdbv2.2.0",
    srcs = glob([
        "jimdbv2.2.0/lib/libhellojimdb.a"
    ]),
    hdrs = glob([
        "jimdbv2.2.0/include/*",
    ]),
    includes = ["jimdbv2.2.0/include"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "zookeeper",
    hdrs = glob(["zookeeper/include/*.h"]),
    srcs = ["zookeeper/lib/libzookeeper_mt.a",],
    includes = ["zookeeper/include",],
    visibility = ["//visibility:public",],
)

cc_library(
    name = "palantir",
    hdrs = glob(["palantir/include/*.h"]),
    srcs = glob(["palantir/src/*.cc",]),
    includes = ["palantir/include"],
    visibility = ["//visibility:public"],
    deps = [
        ":boost",
        "@boringssl//:ssl",
        "@jsoncpp_git//:jsoncpp",
        "@com_github_google_glog//:glog",
        "@com_github_gflags_gflags//:gflags",
    ],
)

cc_library(
    name = "tcmalloc",
    hdrs = glob([
            "tcmalloc/include/gperftools/*.h",
            "tcmalloc/include/google/*.h"]),
    srcs = glob(["tcmalloc/lib/*.a",]),
    includes = ["tcmalloc/include"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "jemalloc",
    hdrs = glob(["jemalloc/include/jemalloc/*.h"]),
    srcs = glob(["jemalloc/lib/*.a",]),
    includes = ["jemalloc/include"],
    visibility = ["//visibility:public"],
)
