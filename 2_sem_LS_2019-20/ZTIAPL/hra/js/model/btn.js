// tlacidla -----------------------------------------------------------------------------------------------------

function btn(xLeft, xRight, yTop, yBottom) {
    this.xL = xLeft; // začiatok na X
    this.xR = xRight; // koniec na X
    this.yT = yTop; // začiatok na Y
    this.yB = yBottom; // začiatok na Y
    this.height = this.yB - this.yT;
    this.width = this.xR - this.xL;
    this.active = false;
    // debugovacia funkcia na polohovanie tlacitiek
    this.drawMe = function () {
      // funkcia na vykreslenie v canvas
      gameArea.context.strokeStyle = "red";
      gameArea.context.beginPath();
      gameArea.context.rect(this.xL, this.yT, this.width, this.height);
      gameArea.context.stroke();
    };
}

// funkcia na overenie kliknutia na tlačidlo
btn.prototype.clicked = function () {
    if (
      this.xL <= gameArea.mouseX &&
      gameArea.mouseX <= this.xR &&
      this.yT <= gameArea.mouseY &&
      gameArea.mouseY <= this.yB &&
      this.active == true
    ) {
      return true;
    }
};