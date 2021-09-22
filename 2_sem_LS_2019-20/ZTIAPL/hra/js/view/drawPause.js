// pauzicka menu -----------------------------------------------------------------------------------------------

function drawPause() {
    resumeBtn.active = true;
    quitBtn.active = true;
  
    gameArea.context.beginPath();
    gameArea.context.globalAlpha = 0.6;
    gameArea.context.fillStyle = "#264060";
    // menu
    gameArea.context.fillRect(
      gameArea.canvas.width / 2 - 150,
      gameArea.canvas.height / 2 - 150,
      300,
      200
    );
    gameArea.context.globalAlpha = 1.0;
  
    // tlacitka
    gameArea.context.fillRect(
      gameArea.canvas.width / 2 - 100,
      gameArea.canvas.height / 2 - 125,
      200,
      50
    );
    gameArea.context.fillRect(
      gameArea.canvas.width / 2 - 100,
      gameArea.canvas.height / 2 - 25,
      200,
      50
    );
  
    resumeText = new txt(
      gameArea.canvas.width / 2 - 75,
      gameArea.canvas.width / 2 - 165,
      "50px",
      "white",
      "0"
    );
    quitText = new txt(
      gameArea.canvas.width / 2 - 48,
      gameArea.canvas.width / 2 - 67,
      "50px",
      "white",
      "0"
    );
    resumeText.text = "RESUME";
    quitText.text = "QUIT";
    resumeText.drawMe();
    quitText.drawMe();
  
    //resumeBtn.drawMe();
    //quitBtn.drawMe();
}