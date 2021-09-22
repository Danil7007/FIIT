// objekt pre lodku ---------------------------------------------------------------------------------------------

function lodka() {
    this.X = 0;
    this.Y = 0;
    this.width = 613.9;
    this.height = 434;
  
    this.drawMe = function (version) {
      // animacia
      switch (true) {
        case version == 1:
          gameArea.context.drawImage(
            boat01,
            this.X,
            this.Y,
            this.width,
            this.height
          );
          break;
  
        case version == 2:
          gameArea.context.drawImage(
            boat02,
            this.X,
            this.Y,
            this.width,
            this.height
          );
          break;
      }
    };
}