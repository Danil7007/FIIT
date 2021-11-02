var canvas
var ctx
var time
var keys = []

// Model
var scene = []

// View
function draw() {
  // Clear the canvas
  ctx.fillStyle = "white"
  ctx.fillRect(0, 0, canvas.width, canvas.height)
	// Draw all objects in scene
  for (i in scene) {
    scene[i].draw()
  }
}

// Controller
function move(dt) {
	// Just move all the objects
  for (var i in scene) {
    scene[i].move(dt)
  }
}

// Main loop
function step() {
  // Get time delta
  var now = Date.now()
  var dt = (now - time) / 100
  time = now

  // Animate
  move(dt)

  // Draw
  draw()

  // Loop animation
  requestAnimationFrame(step)
}

// Initialization
window.onload = function() {
  // Prepare canvas
  canvas = document.getElementById("canvas")
  ctx = canvas.getContext("2d")

  // Use level1 as the scene
	scene = level1()

  time = Date.now()
  requestAnimationFrame(step)
}

// Handle events
window.onkeydown = function(event) {
  keys[event.keyCode] = true
}

window.onkeyup = function(event) {
  keys[event.keyCode] = false
}
