// Object Node
function Node(name) {
  // Nodes to message
  this.nodes = []
  this.name = name
}

// Add node
Node.prototype.add = function(node) {
  this.nodes.push(node)
}

// Remove node
Node.prototype.remove = function(node) {
  var index = this.nodes.indexOf(node)
  delete this.nodes[index]
}

// Pass message "event" to child nodes
Node.prototype.notify = function(event, argument) {
  for (index in this.nodes) {
    var node = this.nodes[index]
    // If node has defined message method
    if (typeof(node[event]) == "function")
      node[event](argument)
  }
}

// Example messages
Node.prototype.hello = function(parent) {
  this.onHello(parent)
  // Pass message to children
  this.notify("hello", this)
}

Node.prototype.onHello = function(parent) {
  // Determine who is parent
  var name = "no parent"
  if (parent)
    name = parent.name

  // Print hello message
  console.log("hello from : " + this.name + " parent: " + name)
}
