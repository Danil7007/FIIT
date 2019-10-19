// Object Node
function Node() {
  // Nodes to message
  this.nodes = []
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

// Notify nodes of event
Node.prototype.notify = function(event, argument) {
  for (index in this.nodes) {
    var node = this.nodes[index]
    if (typeof(node[event]) == "function")
      node[event](argument)
  }
}
