// objekt pre penu ----------------------------------------------------------------------------------------------

function pena(x, y, width, height) {
    this.X = x;
    this.Y = y;
    this.width = width;
    this.height = height;
  
    this.drawMe = function () {
      gameArea.context.drawImage(
        imgPena,
        this.X,
        this.Y,
        this.width,
        this.height
      );
    };
}