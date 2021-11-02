// Simple Button implementation
function Button(text, x, y, w, h) {
  this.text = text
  this.pressed = false

  // Construct Widget
  Widget.call(this, x, y, w, h)
}

// Copy Widget prototype
Button.prototype = Object.create(Widget.prototype)

// Redefine ondraw function
Button.prototype.ondraw = function(context) {
  context.fillStyle = "blue"
  if (this.pressed)
    context.fillStyle = "green"
  context.fillRect(0, 0, this.w, this.h)
  context.font = "30px Arial";
  context.fillStyle = "white"
  context.textAlign = 'center';
  context.fillText(this.text, this.w / 2, this.h / 2);
}

// Redefine onclick function
Button.prototype.onclick = function(event) {
  this.pressed = !this.pressed
  if (this.action) return this.action()
}
