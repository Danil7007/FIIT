window.onload = function() {
  console.log("\n>>> ROOT Message")
  // Add root node
  var root = new Node("root")
  // Send hello message
  root.hello()

  console.log("\n>>>> Children Message")
  // Add root children
  var child1 = new Node("child1")
  var child2 = new Node("child2")
  root.add(child1)
  root.add(child2)
  // Send hello message
  root.hello()

  console.log("\n>>>> Grandchildren Message")
  // Add grandChildren
  var grandChild = new Node("grandChild")
  var blackSheep = new Node("blackSheep")
  blackSheep.onHello = function(parent) {
    console.log("I don't want to tell.")
  }
  child1.add(grandChild)
  child1.add(blackSheep)
  //child2.add(child2)

  // Send hello message
  root.hello()
}
