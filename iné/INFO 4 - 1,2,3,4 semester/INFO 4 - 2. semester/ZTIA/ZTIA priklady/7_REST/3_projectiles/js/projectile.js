class Projectile extends GameObject {
  constructor(game, x, y) {
    super(game, x, y, 60, 60)
    this.dx = 0
    this.dy = -25
    this.maxLife = 8
    this.life = 0
    this.img = document.getElementById("projectile")
  }

  ondraw(ctx) {
    var frame = Math.round((this.life/this.maxLife)*8)
    ctx.save()
    ctx.translate(this.x, this.y)
    ctx.rotate(this.life)
    ctx.drawImage(this.img, 64*frame, 0, 64, 64, -20, -30, this.width, this.height)
    ctx.restore()
  }

  onmove(dt) {
    this.x += this.dx * dt
    this.y += this.dy * dt

    // Collision logic here

    // Die when reaching maxLife
    this.life += dt
    if (this.life > this.maxLife) this.game.remove(this)
  }
}
