// funkcia text -------------------------------------------------------------------------------------------------

function txt(x, y, size, color, text) {
    this.X = x;
    this.Y = y;
    this.size = size;
    this.color = color;
    this.text = text;
  
    this.drawMe = function () {
      gameArea.context.font = this.size + " AR";
      gameArea.context.fillStyle = color;
      gameArea.context.fillText(this.text, this.X, this.Y);
    };
}