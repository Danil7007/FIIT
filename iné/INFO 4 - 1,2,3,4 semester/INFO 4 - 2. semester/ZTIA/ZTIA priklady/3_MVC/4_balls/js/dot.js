var colours = ["red", "green", "blue", "yellow", "cyan", "black"]

// Creating a cObject

// Constructor that will make a new "Dot" object
// NOTE: "this" keyword used to represent the created object
function Dot() {
  this.x = Math.random() * canvas.width
  this.y = Math.random() * canvas.height
  this.dx = Math.random() * 50 - 25
  this.dy = Math.random() * 50 - 25
  this.size = Math.random() * 10 + 5

  // Pick random colour
  var colour_index = Math.round(Math.random() * (colours.length - 1))
  this.colour = colours[colour_index]

  // Returns "this"
}

// This is shared for all Dot objects
Dot.prototype = {
  // Movement logic
  move: function(dt) {
    if (this.x > canvas.width) {
      this.x = canvas.width
      this.dx = -Math.abs(this.dx)
    }
    if (this.x < 0) {
      this.x = 0
      this.dx = Math.abs(this.dx)
    }
    if (this.y > canvas.height) {
      this.y = canvas.height
      this.dy = -Math.abs(this.dy)
    }
    if (this.y < 0) {
      this.y = 0
      this.dy = Math.abs(this.dy) * 0.95
    }

    // Movement
    this.x += this.dx * dt
    this.y += this.dy * dt
  },

  // Render self
  draw: function() {
    ctx.fillStyle = this.colour
    ctx.beginPath();
    ctx.arc(this.x, this.y, this.size, 0, Math.PI * 2);
    ctx.closePath();
    ctx.fill();
  }
}
