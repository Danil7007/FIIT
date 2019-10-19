// More complex application
// Just simulate a scene with collisions
var scene = []

function moveScene() {
  for (i in scene) {
    scene[i].move()
  }
}

function ObjectA(x, y) {
  this.x = x
  this.y = y
  this.size = 10
  this.move = function() {
  }
  this.onCollision = function(obj) {
    // Delete self
    var i = scene.indexOf(this)
    scene.splice(i, 1)
  }
}

function ObjectB(x, y) {
  this.x = x
  this.y = y
  this.size = 5
  this.health = 100
  this.move = function() {
    // Test collision
    for (i in scene) {
      var obj = scene[i]
      var collision_test = this.x > obj.x + obj.size || this.x + this.size < obj.x || this.y > obj.y + obj.size || this.y + this.size < obj.y
      if(!collision_test && obj != this) {
        this.onCollision(obj);
      }
    }
  }
  this.onCollision = function(obj) {
    // Message the other object too:w
    obj.onCollision(this)
    this.health -= 10
  }
}

// Test with custom scene
test( "Scene collision test", function() {
  // Pepare a scene to test
  scene = []
  var a1 = new ObjectA(10,0);
  var a2 = new ObjectA(20,10);
  var b = new ObjectB(0,0);
  scene.push(a1)
  scene.push(a2)
  scene.push(b)

  pass(scene.length == 3, "All objects should be in the scene.")

  moveScene()

  pass(scene.length == 3, "No objects should collide yet.")

  b.x += 5
  moveScene() // Should collide with a1

  fail(scene.indexOf(a1) == 0, "Object a1 should no longer be in scene")
  pass(scene.length == 2, "Scene should now be length 2.")
  pass(b.health == 90, "Object b should have less health.")
})
