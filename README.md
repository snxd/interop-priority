## Priority Interop Example for DIRECT 6.1

This is an example interop that shows how to change the priority of the current process.

### Contents

* bin - Priority interop dlls
* js/priority.js - Javascript priority object
* interop - DIRECT interop headers
* mac - macOS specific files
* linux - Linux specific files
* windows - Windows specific files

### Requirements

* CMake 2.8

### Build Instructions

CMake is a makefile generator that produces solutions and project files for various compiler toolkits.

#### Visual Studio

```
cmake .
cmake --build . --config Debug
```

#### Xcode

```
cmake . -G Xcode
cmake --build . --config Debug
```

#### Unix Makefiles

```
cmake . -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```

### Setup Instructions

1. Compile the solution or project for your platform
2. Copy the dynamic library from the target directory to the host.exe directory
3. Edit workflow.json and add the following task to be run in the load entry point: ```
    "loadPriority": {
        "type": "interopLoad",
        "name": "priority",
        "path": "{ModuleDirectory}{LibraryPrefix}priority.{LibraryExtension}"
    },```
4. Edit workflow.json and add the following task to be run in the unload entry point: ```
    "unloadPriority": {
        "type": "interopUnload",
        "name": "priority",
        "path": "{ModuleDirectory}{LibraryPrefix}priority.{LibraryExtension}"
    },```
5. You can then modify the workflow.json to use the priority task: ```
    "setPriority": {
        "type": "priority",
        "level": "low"
    }```
5. Copy priority.js from the js directory to the skin directory
6. Open main.html and insert the following scripts after main.js: ```
    <script src="priority.js" type="text/javascript"></script>```
7. You can then modify main.js to wait for the interop to load before setting the process level: ```
    interop.on("load", function(info) {
        if (info.name == "priority") {
            window.priority.setLow();
        }
    });```
8. Run host.exe with --disablesecurity as the first argument (during production if you sign the dll you won't need this).
