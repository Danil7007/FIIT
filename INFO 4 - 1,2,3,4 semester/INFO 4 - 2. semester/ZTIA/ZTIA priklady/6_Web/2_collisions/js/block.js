function Block(x, y) {
  var size = 50
  GameObject.call(this, x * size, y * size, size)
  this.physical = true
  this.img = document.getElementById("block")
}

// Inherit from GameObject
Block.prototype = Object.create(GameObject.prototype)

Block.prototype.draw = function() {
  ctx.drawImage(this.img, this.x, this.y, this.size, this.size)
}
