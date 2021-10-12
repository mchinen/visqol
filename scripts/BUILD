load("//devtools/python/blaze:pytype.bzl", "pytype_strict_binary")
load("//devtools/python/blaze:strict.bzl", "py_strict_test")

licenses(["notice"])  # BSD

py_binary(
    name = "fit_nsim_to_mos_poly",
    srcs = ["fit_nsim_to_mos_poly.py"],
    deps = ["@numpy"],
)

pytype_strict_binary(
    name = "train_lattice",
    srcs = ["train_lattice.py"],
    python_version = "PY3",
    srcs_version = "PY3",
    test_lib = True,
    deps = [
        "//file/colossus/public:cns",
        "//pyglib:gfile",
        "//third_party/py/absl:app",
        "//third_party/py/absl/flags",
        "//third_party/py/absl/logging",
        "//third_party/py/attr",
        "@numpy//:numpy",
        "//third_party/py/pandas",
        "//third_party/py/tensorflow",
        "//third_party/py/tensorflow_lattice",
    ],
)

py_binary(
    name = "make_svm_train_file",
    srcs = ["make_svm_train_file.py"],
)

py_strict_test(
    name = "train_lattice_test",
    srcs = ["train_lattice_test.py"],
    python_version = "PY3",
    srcs_version = "PY3",
    deps = [
        ":train_lattice.testonly_lib",
        "//testing/pybase",
        "//testing/pybase:parameterized",
        "@numpy//:numpy",
        "//third_party/py/pandas",
    ],
)
