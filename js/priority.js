/** @file _priority.js
 *  @class Priority
 *  @brief sets the priority of the current process
 */

function Priority(instanceId) {
    this.instanceId = instanceId;
}

Priority.prototype.release = function() {
    this.releaseInstance(this.instanceId);
};
Priority.prototype.releaseInstance = function() {
    interop.releaseInstance(this.instanceId);
};
Priority.prototype.invoke = function(methodBinding) {
    return interop.invoke(this.instanceId, methodBinding);
};

/**
 * Sets the current process to low priority
 * @type bool
 */
Priority.prototype.setLow = function() {
    return this.invoke({
        "method":"setLow"
    });
};
/**
 * Sets the current process to normal priority
 * @type bool
 */
Priority.prototype.setNormal = function() {
    return this.invoke({
        "method":"setNormal"
    });
};
/**
 * Sets the current process to high priority
 * @type bool
 */
Priority.prototype.setHigh = function() {
    return this.invoke({
        "method":"setHigh"
    });
};

function createPriority(instanceId) {
    return interop.createInstance("SSN.Priority", Priority, instanceId);
}

/** Global instance of Priority created when interop loaded
 *  @type Priority
 */
interop.on("libraryLoad", function(info) {
    if (info.name.toLowerCase() == "priority") {
        window.priority = createPriority();
    }
});
interop.on("libraryUnload", function(info) {
    if (info.name.toLowerCase() == "priority") {
        window.priority.release();
        window.priority = null;
    }
});