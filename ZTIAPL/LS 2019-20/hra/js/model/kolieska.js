// objekt pre zivoty --------------------------------------------------------------------------------------------

function kolieska() {
    this.X = 475;
    this.Y = 5;
    this.width = 130;
    this.height = 40;
  
    this.drawMe = function (version) {
      // ubudanie zivotov
      switch (true) {
        case version == 1:
          gameArea.context.drawImage(
            lives03,
            this.X,
            this.Y,
            this.width,
            this.height
          );
          break;
  
        case version == 2:
          gameArea.context.drawImage(
            lives02,
            this.X,
            this.Y,
            this.width,
            this.height
          );
          break;
  
        case version == 3:
          gameArea.context.drawImage(
            lives01,
            this.X,
            this.Y,
            this.width,
            this.height
          );
          break;
      }
    };
}