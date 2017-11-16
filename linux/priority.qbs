import qbs;

Product {
    name: "priority"
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
            "../interop/",
            "../"
        ])
        cpp.visibility: "hidden"
        cpp.linkerFlags: base.concat([
            "-Wl,--retain-symbols-file=" + sourceDirectory + "/priority.def"
        ])
    }

    Group {
        name: "exports"
        files: [
            "priority.def"
        ]
    }

    Group {
        name: "sources"
        prefix: "../"
        files: [
            "prioritytask.c",
            "priorityinvoke.c"
        ]
    }

    Group {
        name: "linux sources"
        files: [
            "priority.c"
        ]
    }

    Group {
        name: "headers"
        prefix: "../"
        files: [
            "priority.h",
            "prioritytask.h"
        ]
    }

    Group {
        name: "interop"
        prefix: "../interop/"
        files: [
            "dictionaryi.h",
            "interoplib.h",
            "interoplib.c",
            "interopstub.h",
            "workflowi.h",
            "taski.h"
        ]
    }

    Group {
        // Copy produced library to install root
        fileTagsFilter: "dynamiclibrary"
        qbs.install: true
    }
}
