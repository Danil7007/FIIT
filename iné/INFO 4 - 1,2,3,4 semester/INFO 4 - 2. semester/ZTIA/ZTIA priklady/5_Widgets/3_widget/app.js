// Simple application abstraction
function App(element) {
  this.canvas = window.document.getElementById(element)
  this.context = this.canvas.getContext("2d")

  Widget.call(this, 0, 0, canvas.width, canvas.height)
}

// Copy from Widget
App.prototype = Object.create(Widget.prototype)

// Redefine draw
App.prototype.ondraw = function(context) {
  context.fillStyle = "gray"
  context.fillRect(0, 0, this.w, this.h)
}

// Redraw everything
App.prototype.update = function() {
  this.draw(this.context)
}

// Initialize application handlers
App.prototype.start = function() {
  var app = this

  // Register mouse handler
  window.onclick = function(event) {
    var point = {
        x: event.layerX,
        y: event.layerY,
      }
    // Send click message
    app.click(point)
  }

  // Register keyb handler
  window.onkeydown = function(event) {
    // Prevent browser from handling backspace key press
    event.cancelBubble = true
    if (event.stopPropagation) event.stopPropagation()

    // Send key message
    app.key(event)
    return false
  }

  // Update 30time per second
  setInterval(function() {
    app.update()
  }, 1000 / 30)
}
