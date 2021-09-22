// objekt pre chapadielko ---------------------------------------------------------------------------------------

function chapadlo(x, y, scale) {
    this.X = x;
    this.Y = y;
    this.visible = 0;
    this.width = scale / 2;
    this.height = scale;
    this.active = false;
  
    // zjednotenie s tladiclom
    this.xR = this.X + this.width;
    this.yB = this.Y + this.height;
  
    this.drawMe = function (version) {
      // animacia
      switch (true) {
        case version == 1:
          gameArea.context.drawImage(
            chapadlo01,
            this.X,
            this.Y,
            this.width,
            this.height
          );
          break;
  
        case version == 2:
          gameArea.context.drawImage(
            chapadlo02,
            this.X,
            this.Y,
            this.width,
            this.height
          );
          break;
  
        case version == 3:
          gameArea.context.drawImage(
            chapadlo03,
            this.X,
            this.Y,
            this.width,
            this.height
          );
          break;
      }
    };
  }
  
  // kliknutie na chapadlo
  chapadlo.prototype.clicked = function () {
    if (
      this.X <= gameArea.mouseX &&
      gameArea.mouseX <= this.xR &&
      this.Y <= gameArea.mouseY &&
      gameArea.mouseY <= this.yB &&
      this.active
    ) {
      return true;
    }
};