function Player(x, y) {
  var size = 50
  GameObject.call(this, x * size, y * size, size)
}

// Also inherits from GameObject
Player.prototype = Object.create(GameObject.prototype)

Player.prototype.move = function(dt) {
  var last_x = this.x
  var last_y = this.y

  // Move accoding to pressed keys
  if (keys[37]) this.x -= 5
  if (keys[39]) this.x += 5
  if (keys[38]) this.y -= 5
  if (keys[40]) this.y += 5

  if(this.checkCollision()) {
    this.x = last_x
    this.y = last_y
  }

  // Load level2
  if (keys[13]) {
    scene = level2()
    return
  }

  // Remove self
  if (keys[27]) {
    var index = scene.indexOf(this)
    scene.splice(index, 1)
  }
}

Player.prototype.draw = function() {
  ctx.fillStyle = "blue"
  ctx.beginPath()
  ctx.arc(this.x + this.size / 2, this.y + this.size / 2, this.size / 2, 0, Math.PI * 2)
  ctx.closePath()
  ctx.fill()
}
