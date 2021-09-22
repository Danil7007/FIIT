// funkcia UPDATEGAMEAREA 02 -------------------------------------------------------------------- !
function updateGameAreaPlay2() {
    pauzickaBtn.active = true;
    muteBtn.active = true;
    gameArea.frameNo += 1;

    if (gameArea.frameNo > 3) {
      gameArea.frameNo = 0;
      count += 0.5; // na pravidelnost vystrkavania chapadiel
      sec--; // odpocitava celkovy cas
    }
  
    console.log(count);
    gameArea.clear();
  
    // animacia
    switch (true) {
      case gameArea.frameNo == 0:
        gameArea.context.drawImage(
          background02_01,
          0,
          0,
          gameArea.canvas.width,
          gameArea.canvas.height
        );
        break;
  
      case gameArea.frameNo == 1:
        gameArea.context.drawImage(
          background02_02,
          0,
          0,
          gameArea.canvas.width,
          gameArea.canvas.height
        );
        break;
  
      case gameArea.frameNo == 2:
        gameArea.context.drawImage(
          background02_03,
          0,
          0,
          gameArea.canvas.width,
          gameArea.canvas.height
        );
        break;
  
      case gameArea.frameNo == 3:
        gameArea.context.drawImage(
          background02_02,
          0,
          0,
          gameArea.canvas.width,
          gameArea.canvas.height
        );
        done = 0;
        break;
    }
  
    // narocnost
    if (sec == 60) gameArea.diff = 2;
    if (sec == 45) gameArea.diff = 1;
    if (sec == 30) gameArea.diff = 0.5;
  
    if (count >= gameArea.diff && done == 0) {
      chapadielko1_2.visible = 0;
      chapadielko2_2.visible = 0;
      chapadielko3_2.visible = 0;
      chapadielko4_2.visible = 0;
      chapadielko5_2.visible = 0;
      chapadielko6_2.visible = 0;
      chapadielko7_2.visible = 0;
      chapadielko8_2.visible = 0;
      chapadielko9_2.visible = 0;
  
      var random = Math.floor(Math.random() * 9);
  
      done = 1;
      count = 0;
  
      // vyber nahodneho chapadla
      switch (random) {
        case 0:
          chapadielko1_2.visible = 1;
          break;
  
        case 1:
          chapadielko2_2.visible = 1;
          break;
  
        case 2:
          chapadielko3_2.visible = 1;
          break;
  
        case 3:
          chapadielko4_2.visible = 1;
          break;
  
        case 4:
          chapadielko5_2.visible = 1;
          break;
  
        case 5:
          chapadielko6_2.visible = 1;
          break;
  
        case 6:
          chapadielko7_2.visible = 1;
          break;
  
        case 7:
          chapadielko8_2.visible = 1;
          break;
  
        case 8:
          chapadielko9_2.visible = 1;
          break;
      }
    }
  
    // vykreslenie vybrateho chapadla
    if (chapadielko1_2.visible == 1) {
      chapadielko1_2.drawMe(2);
      pena1.drawMe();
    }
    if (chapadielko2_2.visible == 1) {
      chapadielko2_2.drawMe(2);
      pena2.drawMe();
    }
    if (chapadielko3_2.visible == 1) {
      chapadielko3_2.drawMe(2);
      pena3.drawMe();
    }
    if (chapadielko4_2.visible == 1) {
      chapadielko4_2.drawMe(2);
      pena4.drawMe();
    }
    if (chapadielko5_2.visible == 1) {
      chapadielko5_2.drawMe(2);
    }
    if (chapadielko6_2.visible == 1) {
      chapadielko6_2.drawMe(2);
    }
    if (chapadielko7_2.visible == 1) {
      chapadielko7_2.drawMe(2);
    }
    if (chapadielko8_2.visible == 1) {
      chapadielko8_2.drawMe(2);
    }
    if (chapadielko9_2.visible == 1) {
      chapadielko9_2.drawMe(2);
    }
  
    // mute (a zmena polohy lebo sa prekryva s textom)
    muteBtn.yT = 20;
    muteBtn.yB = 50;
    if (gameArea.mute == 1) {
      gameArea.context.drawImage(mute, 10, 20, 30, 30);
    } else {
      gameArea.context.drawImage(mute02, 10, 20, 30, 30);
    }
    gameArea.context.drawImage(pause, 60, 20, 30, 30);
  
    // vypis skore
    scoreTextMode02.text = "Score: " + score.myScore;
    timeLeft.text = "Time left: " + sec;
    scoreTextMode02.drawMe();
    timeLeft.drawMe();
    scoreTextMode02.drawMe();
    timeLeft.drawMe();
    scoreTextMode02.drawMe();
    timeLeft.drawMe();
  
    // GAME OVER
    if (sec <= 0) {
      deactivateBtns();
      delete txt;
  
      clearInterval(redrawInterval);
      drawEndScreen();
    }
}
  