## Priority Interop Example

This is an example interop that shows how to change the priority of the current process.

### Contents 

* bin/ - Priority interop dlls
* js/priority.js - Javascript priority object
* interop/ - DIRECT interop headers
* jansson/ - Jansson javascript parser
* mac/ - Xcode project files
* linux/ - QtCreator project files
* windows/ - Windows project files

### Requirements

* Visual Studio 2013
* Xcode 8
* QtCreator 5.8
* DIRECT 5

### Setup Instructions

1. Compile the solution
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
5. Copy simpleobject.js and simpleobjecttest.js from the js directory to the skin directory
6. Open main.html and insert the following scripts after main.js: ```
    <script src="priority.js" type="text/javascript"></script>```
7. You can then modify main.js to wait for the interop to load before setting the process level: ```
    interop.on("libraryLoad", function(info) {
        if (info.name.toLowerCase() == "priority") {
            window.priority.setLow();
        }
    });```
8. Run host.exe with --disablesecurity as the first argument (during production if you sign the dll you won't need this).

