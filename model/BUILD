licenses(["notice"])  # BSD

package(default_visibility = ["//visibility:public"])

exports_files(
    [
        "libsvm_nu_svr_model.txt",
        "tcdvoip_nu.568_c5.31474325639_g3.17773760038_model.txt",
        "lattice_tcditugen_ls3_140_lap1e3_ls16_4_frozen_graph.pb",
        "lattice_nsimstddeg_tfcompile_config.pbtxt",
    ],
)

filegroup(
    name = "speech_lattice_model_medium_size",
    srcs = glob(
        ["lattice_tcditugen_ls3_140_lap1e3_ls16_4/**"],
        exclude_directories = 0,
    ),
)
