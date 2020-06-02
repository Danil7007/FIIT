// vykreslenie endscreen ----------------------------------------------------------------------------------------

function drawEndScreen() {
    deactivateBtns();
    // ziskanie aktualneho casu (preddefinovane v js)
    gameArea.previousMode = gameArea.mode;
    gameArea.mode=4;
    var date = new Date();
    muteBtn.yT = 10;
    muteBtn.yB = 40;
    printToTable();
  
    gameArea.soundMode = "endscreen";
    selectSound();
  
    // text
    scoreTextEndScreen_01 = new txt(100, 200, "50px", "black", "0");
    scoreTextEndScreen_02 = new txt(
      gameArea.canvas.width / 2 - 10,
      250,
      "60px",
      "black",
      "0"
    );
  
    gameArea.clear(); // vyčistenie canvas
    gameArea.context.drawImage(
      // nakreslenie obrázku
      menu02, //aký obrázok
      0, // kde na X
      0, // kde na Y
      gameArea.canvas.width, // širka
      gameArea.canvas.height // výška
    );
  
    scoreTextEndScreen_01.text = "Your score was: ";
    scoreTextEndScreen_02.text = score.myScore;
  
    scoreTextEndScreen_01.drawMe();
    scoreTextEndScreen_02.drawMe();

    //mute
    if (gameArea.mute == 1) {
      gameArea.context.drawImage(mute, 10, 10, 30, 30);
    } else {
      gameArea.context.drawImage(mute02, 10, 10, 30, 30);
    }
    
    endBtn_01.active = true;
    endBtn_02.active = true;
    muteBtn.active = true;
}