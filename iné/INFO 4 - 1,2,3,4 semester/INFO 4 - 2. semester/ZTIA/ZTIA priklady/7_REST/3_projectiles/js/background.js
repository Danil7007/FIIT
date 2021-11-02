class Background extends GameObject {
  constructor(game) {
    super(game, 0, 0, game.canvas.width, game.canvas.height)
    this.img = document.getElementById("background")
  }

  ondraw(ctx) {
    ctx.drawImage(this.img, this.x, this.y, this.width, this.height)
  }
}
