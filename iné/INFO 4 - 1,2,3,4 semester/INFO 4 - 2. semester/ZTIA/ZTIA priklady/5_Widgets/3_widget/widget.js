// Simple Widget implementation
function Widget(x, y, w, h) {
  // Construct Node
  Node.call(this)

  this.x = x
  this.y = y
  this.w = w
  this.h = h
  this.rotation = 0
  this.visible = true
  this.focus = false
  this.border = false
}

// Copy Node prototype
Widget.prototype = Object.create(Node.prototype)

// Drawing widgets using canvas
Widget.prototype.draw = function(context) {
  if (!this.visible) return

  // Each widget contained in its parent
  context.save()
  // Clipping
  context.translate(this.x, this.y)
  context.rotate(this.rotation)
  context.beginPath()
  context.rect(0, 0, this.w, this.h)
  context.clip()
  // Draw
  this.ondraw(context)
  // Send draw event to other Widgets
  this.notify("draw", context)

  // Draw border
  if(this.border) {
  	context.beginPath()
    context.rect(0,0,this.w,this.h)
  	context.lineWidth = 5
  	context.strokeStyle="red"
  	context.stroke()
  }

  context.restore()
}

// Widget specific drawing
Widget.prototype.ondraw = function(context) {}

// Click handling
Widget.prototype.click = function(point) {
  if (!this.visible) return

  // Point needs to be converted to local coordinates
  var localPoint = {
    x: point.x - this.x,
    y: point.y - this.y
  }

  // Check localPoint is inside Widget boundary
  if (0 < localPoint.x && localPoint.x < this.w)
    if (0 < localPoint.y && localPoint.y < this.h) {
      this.focus = true
      // Call onclick function
      this.onclick(localPoint)
    } else
      this.focus = false

    // Send click event to other Widgets
  this.notify("click", localPoint)
}

Widget.prototype.onclick = function(point) {}

// Keyboard handling
Widget.prototype.key = function(key) {
  if (!this.visible) return

  if (this.focus) this.onkey(key)

  // Send key message to other Widgets
  this.notify("key", key)
}

Widget.prototype.onkey = function(key) {}
