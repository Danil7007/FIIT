function updateGameAreaPlay() {
        // podla frame-u
        if (gameArea.frameNo == 15) {
            background = new Image();
            background.src = "../assets/pictures/bg/bg02_02.png";
            background.onload = function() {
              
              gameArea.clear();
              gameArea.context.drawImage(
                background,
                0,
                0,
                gameArea.canvas.width,
                gameArea.canvas.height
              );
            };
          }
          if (gameArea.frameNo == 30) {
            background = new Image();
            background.src = "../assets/pictures/bg/bg02_03.png";
            background.onload = function() {
              gameArea.clear();
              gameArea.context.drawImage(
                background,
                0,
                0,
                gameArea.canvas.width,
                gameArea.canvas.height
              );
            };
          }
          if (gameArea.frameNo == 45) {
            background = new Image();
            background.src = "../assets/pictures/bg/bg02_02.png";
            background.onload = function() {
              gameArea.clear();
              gameArea.context.drawImage(
                background,
                0,
                0,
                gameArea.canvas.width,
                gameArea.canvas.height
              );
            };
          }
          if (gameArea.frameNo == 0) {
            background = new Image();
            background.src = "../assets/pictures/bg/bg02_01.png";
            background.onload = function() {

              gameArea.clear();
              gameArea.context.drawImage(
                background,
                0,
                0,
                gameArea.canvas.width,
                gameArea.canvas.height
              );
            };
          }
          gameArea.frameNo += 1;
          if (gameArea.frameNo == 60) {
            gameArea.frameNo = 0;
          }
    }
    
  