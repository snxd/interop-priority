/** @file _priority.js
 *  @class Priority
 *  @brief sets the priority of the current process
 */
 
(function (root) {
    function Priority(instanceId) {
        this.instanceId = instanceId;
    }
    
    Priority.prototype = new EventEmitter();
    
    Priority.prototype.release = function() {
        this.emit("finalize");
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

    root.createPriority = function(instanceId) {
        return interop.createInstance("SSN.Priority", Priority, instanceId);
    };

    /** Global instance of Priority created when interop loaded
     *  @type Priority
     */
    interop.on("load", function(info) {
        if (info.name == "priority") {
            root.priority = createPriority();
        }
    });
    interop.on("unload", function(info) {
        if (info.name == "priority") {
            root.priority.release();
            root.priority = null;
        }
    });
    
}(_global()));