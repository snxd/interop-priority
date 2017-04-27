import qbs;

Product {
    name: "empty"
    type: [ "dynamiclibrary" ]
    consoleApplication: false

    Depends { name: "cpp" }

    cpp.commonCompilerFlags: [
        "-Wno-unused-parameter",
        "-Wno-unused-function",
        "-Wno-empty-body",
        "-Wno-sequence-point"
    ]

    Properties {
        condition: qbs.targetOS.contains("linux")
        cpp.includePaths: outer.concat([
            "/usr/include/",
            "../jansson/",
            "../interop/"
        ])
        cpp.visibility: "hidden"
        cpp.linkerFlags: base.concat([
            "-Wl,--retain-symbols-file=" + sourceDirectory + "/empty.def"
        ])
    }

    Group {
        name: "exports"
        files: [
            "empty.def"
        ]
    }

    Group {
        name: "sources"
        prefix: "../"
        files: [
            "emptyinterop.c"
        ]
    }


    Group {
        name: "interop"
        prefix: "../interop/"
        files: [
            "interoplib.h",
            "interopstub.h"
        ]
    }

    Group {
        name: "jansson"
        prefix: "../jansson/"
        files: [
            "dump.c",
            "error.c",
            "hashtable.h",
            "hashtable.c",
            "hashtable_seed.c",
            "jansson.h",
            "jansson_config.h",
            "jansson_private.h",
            "load.c",
            "lookup3.h",
            "memory.c",
            "pack_unpack.c",
            "strbuffer.h",
            "strbuffer.c",
            "strconv.c",
            "utf.h",
            "utf.c",
            "value.c"
        ]
    }

    Group {
        // Copy produced library to install root
        fileTagsFilter: "dynamiclibrary"
        qbs.install: true
    }
}
