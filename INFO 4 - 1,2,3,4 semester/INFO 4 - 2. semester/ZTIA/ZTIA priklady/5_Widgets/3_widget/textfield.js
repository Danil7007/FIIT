function Textfield(text, x, y, w, h) {
  this.text = text

  // Construct Widget
  Widget.call(this, x, y, w, h)
}

// Copy Widget prototype
Textfield.prototype = Object.create(Widget.prototype)

Textfield.prototype.ondraw = function(context) {
  context.fillStyle = "white"
  if (this.focus)
    context.fillStyle = "yellow"
  context.fillRect(0, 0, this.w, this.h)

  context.font = "30px Arial"
  if (this.focus) {
    context.fillStyle = "red"
    context.fillText(this.text + "_", 5, 35)
  }
  context.fillStyle = "black"
  context.fillText(this.text, 5, 35)
}

// Handle keyboard
Textfield.prototype.onkey = function(event) {
  var key = event.which
  switch (key) {
    case 8:
      this.text = this.text.substring(0, this.text.length - 1);
      break;
    case 13:
      this.action()
      break;
    default:
      this.text += String.fromCharCode(key)
  }
}

// By default do nothing
Textfield.prototype.action = function() {}
