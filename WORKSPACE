########################
# Platform Independent #
########################
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

# For protobuf rule:
http_archive(
    name = "six",
    build_file = "@com_google_protobuf//:third_party/six.BUILD",
    sha256 = "d16a0141ec1a18405cd4ce8b4613101da75da0e9a7aec5bdd4fa804d0e0eba73",
    urls = ["https://pypi.python.org/packages/source/s/six/six-1.12.0.tar.gz"],
)

# proto_library, cc_proto_library, and java_proto_library rules implicitly
# depend on @com_google_protobuf for protoc and proto runtimes.
# This statement defines the @com_google_protobuf repo.
http_archive(
    name = "com_google_protobuf",
    sha256 = "761bfffc7d53cd01514fa237ca0d3aba5a3cfd8832a71808c0ccc447174fd0da",
    strip_prefix = "protobuf-3.11.1",
    url = "https://github.com/protocolbuffers/protobuf/releases/download/v3.11.1/protobuf-all-3.11.1.tar.gz",
)

git_repository(
    name = "org_tensorflow",
    remote = "https://github.com/tensorflow/tensorflow.git",
    tag = "v2.6.0",
)

# Import all of TensorFlow Serving's external dependencies.
# Downstream projects (projects importing TensorFlow Serving) need to
# duplicate all code below in their WORKSPACE file in order to also initialize
# those external dependencies.
http_archive(
    name = "rules_pkg",
    sha256 = "352c090cc3d3f9a6b4e676cf42a6047c16824959b438895a76c2989c6d7c246a",
    url = "https://github.com/bazelbuild/rules_pkg/releases/download/0.2.5/rules_pkg-0.2.5.tar.gz",
)

# Check bazel version requirement, which is stricter than TensorFlow's.
load(
    "@org_tensorflow//tensorflow:version_check.bzl",
    "check_bazel_version_at_least",
)

check_bazel_version_at_least("3.7.2")

# Initialize TensorFlow's external dependencies.
load("@org_tensorflow//tensorflow:workspace3.bzl", "workspace")

workspace()

load("@org_tensorflow//tensorflow:workspace2.bzl", workspace2 = "workspace")

workspace2()

load("@org_tensorflow//tensorflow:workspace1.bzl", workspace3 = "workspace")

workspace3()

load("@org_tensorflow//tensorflow:workspace0.bzl", workspace4 = "workspace")

workspace4()

# Initialize bazel package rules' external dependencies.
load("@rules_pkg//:deps.bzl", "rules_pkg_dependencies")

rules_pkg_dependencies()

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()

# GoogleTest/GoogleMock framework.
git_repository(
    name = "com_google_googletest",
    remote = "https://github.com/google/googletest.git",
    tag = "release-1.10.0",
)

# Google Abseil Libs
git_repository(
    name = "com_google_absl",
    remote = "https://github.com/abseil/abseil-cpp.git",
    tag = "20200923",
)

# LIBSVM
http_archive(
    name = "svm_lib",
    build_file_content = """
cc_library(
    name = "libsvm",
    srcs = glob(["svm.cpp"]),
    hdrs = glob(["svm.h"]),
    visibility = ["//visibility:public"],
)
""",
    sha256 = "401a60bd828bce8870b9eebf5023602028c7751b0db928a6a3bc351560b8b618",
    strip_prefix = "libsvm-324",
    # Depending on a recent stable version.
    urls = ["https://github.com/cjlin1/libsvm/archive/v324.zip"],
)

# Armadillo Headers
http_archive(
    name = "armadillo_headers",
    build_file_content = """
cc_library(
    name = "armadillo_header",
    hdrs = glob(["include/armadillo", "include/armadillo_bits/*.hpp"]),
    includes = ["include/"],
    visibility = ["//visibility:public"],
)
""",
    sha256 = "d856ea58c18998997bcae6689784d2d3eeb5daf1379d569fddc277fe046a996b",
    strip_prefix = "armadillo-9.860.2",
    urls = ["http://sourceforge.net/projects/arma/files/armadillo-9.860.2.tar.xz"],
)

http_archive(
    name = "bazel_skylib",
    sha256 = "97e70364e9249702246c0e9444bccdc4b847bed1eb03c5a3ece4f83dfe6abc44",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.0.2/bazel-skylib-1.0.2.tar.gz",
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.0.2/bazel-skylib-1.0.2.tar.gz",
    ],
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()

# Python bindings
git_repository(
    name = "pybind11_bazel",
    branch = "master",
    remote = "https://github.com/pybind/pybind11_bazel.git",
)

http_archive(
    name = "pybind11",
    build_file = "@pybind11_bazel//:pybind11.BUILD",
    strip_prefix = "pybind11-2.5.0",
    urls = ["https://github.com/pybind/pybind11/archive/v2.5.0.tar.gz"],
)

load("@pybind11_bazel//:python_configure.bzl", "python_configure")

python_configure(name = "local_config_python")

# pybind11_abseil does not have an abseil.
new_git_repository(
    name = "pybind11_abseil",
    branch = "experimental",
    build_file_content = """
pybind_library(
    name = "absl_casters",
    hdrs = ["absl_casters.h"],
    data = ["//third_party/py/dateutil"],
    deps = [
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/container:flat_hash_set",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/time",
        "@com_google_absl//absl/types:optional",
        "@com_google_absl//absl/types:span",
    ],
)


pybind_library(
    name = "absl_numpy_span_caster",
    hdrs = ["absl_numpy_span_caster.h"],
    deps = [
        "@com_google_absl//absl/types:span",
#        "//third_party/py/numpy:headers",  # buildcleaner: keep
#        "//third_party/py/numpy:multiarray",  # buildcleaner: keep
    ],
)

pybind_library(
    name = "status_utils",
    srcs = ["status_utils.cc"],
    hdrs = ["status_utils.h"],
    deps = [
        ":absl_casters",
        ":status_not_ok_exception",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
)

pybind_library(
    name = "status_casters",
    hdrs = ["status_casters.h"],
    deps = [
        ":status_utils",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/status:statusor",
    ],
)
""",
    remote = "https://github.com/pybind/pybind11_abseil.git",
)

new_git_repository(
    name = "pybind11_protobuf",
    branch = "master",
    build_file_content = """
pybind_library(
    name = "proto_casters",
)
""",
    remote = "https://github.com/pybind/pybind11_protobuf.git",
)

# PFFFT
new_git_repository(
    name = "pffft_lib",
    branch = "master",
    build_file_content = """
cc_library(
    name = "pffft_lib",
    srcs = glob(["pffft.c"]),
    hdrs = glob(["pffft.h"]),
    copts = select({
    "@bazel_tools//src/conditions:windows": [
        "/D_USE_MATH_DEFINES",
        "/W0",
    ],
    "//conditions:default": [
    ]}),
    visibility = ["//visibility:public"],
)
""",
    remote = "https://bitbucket.org/jpommier/pffft.git",
)

http_archive(
    name = "io_bazel_rules_closure",
    sha256 = "5b00383d08dd71f28503736db0500b6fb4dda47489ff5fc6bed42557c07c6ba9",
    strip_prefix = "rules_closure-308b05b2419edb5c8ee0471b67a40403df940149",
    urls = [
        "https://storage.googleapis.com/mirror.tensorflow.org/github.com/bazelbuild/rules_closure/archive/308b05b2419edb5c8ee0471b67a40403df940149.tar.gz",
        "https://github.com/bazelbuild/rules_closure/archive/308b05b2419edb5c8ee0471b67a40403df940149.tar.gz",  # 2019-06-13
    ],
)
