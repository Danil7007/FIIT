class Player extends GameObject {
  constructor(game, x, y) {
    super(game, x, y, 50, 50)

    this.rof = 30
    this.fireTimer = false
  }

  onmove(dt) {
    // Posun
    var keys = this.game.keys
    if ( keys[37] ) this.x-=5;
    if ( keys[39] ) this.x+=5;
    if ( keys[38] ) this.y-=5;
    if ( keys[40] ) this.y+=5;
    if ( keys[32] ) {
      this.startFiring()
    } else {
      this.stopFiring()
    }
  }

  startFiring() {
    if (this.fireTimer) return

    var player = this
    this.fireTimer = setInterval(function() {player.fire()}, this.rof)
  }

  stopFiring() {
    if (!this.fireTimer) return
    clearInterval(this.fireTimer)
    this.fireTimer = false
  }

  fire() {
    var projectile = new Projectile(this.game, this.x+this.width/2, this.y)
    this.game.add(projectile)
  }

  ondraw(ctx) {
    ctx.fillStyle = "blue"
    ctx.beginPath()
    ctx.arc(this.x+this.width/2, this.y+this.height/2, this.width/2, 0, Math.PI*2)
    ctx.closePath()
    ctx.fill()
  }
}
