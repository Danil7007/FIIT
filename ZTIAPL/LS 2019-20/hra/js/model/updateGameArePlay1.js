// funkcia UPDATEGAMEAREA 01 -------------------------------------------------------------------- !
function updateGameAreaPlay1() {
    pauzickaBtn.active = true;
    muteBtn.active = true;
    // pre animaciu
    gameArea.frameNo += 1;
  
    // zvysovanie narocnosti
    if (score.myScore != 0 && score.myScore % 5 == 0) {
      gameArea.diff += 1 / 120;
    }
  
    // za kazdych 60 frameov (1s) = 1 skore
    if (gameArea.frameNo > 60) {
      gameArea.frameNo = 0;
      score.myScore += 1;
    } // počítanie čísla snímku




    // BONUS!!!!! 
    if (score.myScore == 20) {
      score.myScore += 10;
      bonusText = new txt(250,200,"100px","magenta","0");
      bonusText.text =  "BONUS!"; 
    }
    if (score.myScore == 35){
      delete bonusText;
    }

    if (score.myScore == 60 && gameArea.lives == 3) {
      score.myScore += 15;
      bonusText = new txt(260,200,"100px","yellow","0");
      bonusText.text =  "ACE!";
    }
    if (score.myScore == 80){
      delete bonusText;
    }

    if (score.myScore == 120 && gameArea.lives >= 2) {
      score.myScore += 20;
      bonusText = new txt(260,200,"100px","purple","0");
      bonusText.text =  "YES!";
    }
    if (score.myScore == 145){
      delete bonusText;
    }

    if (score.myScore == 160) {
      bonusText = new txt(205,200,"100px","green","0");
      bonusText.text =  "KEEP UP!";
    }
    if (score.myScore == 165){
      delete bonusText;
    }

    if (score.myScore == 200 && gameArea.lives >= 2) {
      score.myScore += 20;
      bonusText = new txt(247,200,"100px","cyan","0");
      bonusText.text =  "WOHOO!";
    }
    if (score.myScore == 225){
      delete bonusText;
    }

    if (score.myScore == 240 && gameArea.lives >= 2) {
      gameArea.diff -= 5;
      bonusText = new txt(247,200,"100px","blue","0");
      bonusText.text =  "GREAT!";
    }
    if (score.myScore == 245){
      delete bonusText;
    }

    if (score.myScore == 260 && gameArea.lives >= 2) {
      score.myScore += 20;
      bonusText = new txt(247,200,"100px","red","0");
      bonusText.text =  "FEVER!";
    }
    if (score.myScore == 285){
      delete bonusText;
    }

    if (score.myScore == 330 && gameArea.lives >= 2) {
      score.myScore += 20;
      gameArea.diff -= 10;
      bonusText = new txt(220,200,"100px","orange","0");
      bonusText.text =  "G.O.A.T.!";
    }
    if (score.myScore == 355){
      delete bonusText;
    }

    if (score.myScore == 400) {
      score.myScore += 20;
      gameArea.diff -= 5;
      
      bonusText = new txt(180,150,"120px","crimson","0");
      bonusText.text =  "DIE";

      bonusText2 = new txt(80,250,"120px","crimson","0");
      bonusText2.text =  "ALREADY!";
    }
    if (score.myScore == 430){
      delete bonusText;
      delete bonusText2;
    }


    gameArea.clear(); // čistenie canvas
  
    // lodka (animacia)
    if (gameArea.frameNo <= 30) {
      boat.drawMe(1);
    }
    if (gameArea.frameNo > 30) {
      boat.drawMe(2);
    }
  
    // prehrávanie animácie
    switch (true) {
      // pozadie + chapadla
  
      case gameArea.frameNo <= 15:
        gameArea.context.drawImage(
          background01_01,
          0,
          0,
          gameArea.canvas.width,
          gameArea.canvas.height
        );
  
        chapadielko1.drawMe(1);
        chapadielko2.drawMe(2);
        chapadielko3.drawMe(3);
        chapadielko4.drawMe(2);
        break;
  
      case gameArea.frameNo <= 30:
        gameArea.context.drawImage(
          background01_02,
          0,
          0,
          gameArea.canvas.width,
          gameArea.canvas.height
        );
  
        chapadielko1.drawMe(2);
        chapadielko2.drawMe(3);
        chapadielko3.drawMe(2);
        chapadielko4.drawMe(1);
        break;
  
      case gameArea.frameNo <= 45:
        gameArea.context.drawImage(
          background01_03,
          0,
          0,
          gameArea.canvas.width,
          gameArea.canvas.height
        );
  
        chapadielko1.drawMe(3);
        chapadielko2.drawMe(2);
        chapadielko3.drawMe(1);
        chapadielko4.drawMe(2);
        break;
  
      // POHYB V TOMTO CASE V MINULOM NIE ANI V BUDUCOM
      case gameArea.frameNo <= 60:
        gameArea.context.drawImage(
          background01_02,
          0,
          0,
          gameArea.canvas.width,
          gameArea.canvas.height
        );
  
        // pohyb chapadiel (20 na spomalenie pravdepodobnosti)
        var random = Math.floor(Math.random() * 20);
        chapadielko1.drawMe(2);
        chapadielko2.drawMe(1);
        chapadielko3.drawMe(2);
        chapadielko4.drawMe(3);
  
        // chapadlo 01
        if (chapadielko1.Y >= 0 && random == 0) {
          chapadielko1.height += 1 * gameArea.diff;
          chapadielko1.Y -= 1 * gameArea.diff;
          chapadielko1.yT = chapadielko1.Y;
          // chytilo lod
          if (chapadielko1.Y < 0) {
            gameArea.lives -= 1;
            chapadielko1.Y = 200;
            chapadielko1.height = 200;
            chapadielko2.Y = 200;
            chapadielko2.height = 200;
            chapadielko3.Y = 200;
            chapadielko3.height = 200;
            chapadielko3.Y = 200;
            chapadielko3.height = 200;
            chapadielko4.Y = 200;
            chapadielko4.height = 200;
          }
        }
  
        // chapadlo 02
        if (chapadielko2.Y >= 0 && random == 1) {
          chapadielko2.height += 1 * gameArea.diff;
          chapadielko2.Y -= 1 * gameArea.diff;
          chapadielko2.yT = chapadielko2.Y;
          // chytilo lod
          if (chapadielko2.Y < 0) {
            gameArea.lives -= 1;
            chapadielko1.Y = 200;
            chapadielko1.height = 200;
            chapadielko2.Y = 200;
            chapadielko2.height = 200;
            chapadielko3.Y = 200;
            chapadielko3.height = 200;
            chapadielko3.Y = 200;
            chapadielko3.height = 200;
            chapadielko4.Y = 200;
            chapadielko4.height = 200;
          }
        }
  
        // chapadlo 03
        if (chapadielko3.Y >= 0 && random == 2) {
          chapadielko3.height += 1 * gameArea.diff;
          chapadielko3.Y -= 1 * gameArea.diff;
          chapadielko3.yT = chapadielko3.Y;
          // chytilo lod
          if (chapadielko3.Y < 0) {
            gameArea.lives -= 1;
            chapadielko1.Y = 200;
            chapadielko1.height = 200;
            chapadielko2.Y = 200;
            chapadielko2.height = 200;
            chapadielko3.Y = 200;
            chapadielko3.height = 200;
            chapadielko3.Y = 200;
            chapadielko3.height = 200;
            chapadielko4.Y = 200;
            chapadielko4.height = 200;
          }
        }
  
        // chapadlo 04
        if (chapadielko1.Y >= 0 && random == 3) {
          chapadielko4.height += 1 * gameArea.diff;
          chapadielko4.Y -= 1 * gameArea.diff;
          chapadielko4.yT = chapadielko4.Y;
          // chytilo lod
          if (chapadielko4.Y < 0) {
            gameArea.lives -= 1;
            chapadielko1.Y = 200;
            chapadielko1.height = 200;
            chapadielko2.Y = 200;
            chapadielko2.height = 200;
            chapadielko3.Y = 200;
            chapadielko3.height = 200;
            chapadielko3.Y = 200;
            chapadielko3.height = 200;
            chapadielko4.Y = 200;
            chapadielko4.height = 200;
          }
        }
        break;
    }
  
    // mute
    if (gameArea.mute == 1) {
      gameArea.context.drawImage(mute, 10, 10, 30, 30);
    } else {
      gameArea.context.drawImage(mute02, 10, 10, 30, 30);
    }
    gameArea.context.drawImage(pause, 60, 10, 30, 30);
  
    // zivoty
    if (gameArea.lives == 3) {
      live.drawMe(1);
    }
    if (gameArea.lives == 2) {
      live.drawMe(2);
    }
    if (gameArea.lives == 1) {
      live.drawMe(3);
    }
  
    // chobotnica
    //gameArea.context.drawImage(octo03, 60, 235, 460, 240);
    gameArea.context.drawImage(octo03, 0, 0, 613, 434);
  
    // text
    scoreText.text = "Score: " + score.myScore;
    scoreText.drawMe();
  


    // BONUS!!!!!!
    if (typeof bonusText != "undefined")
      bonusText.drawMe();
    if (typeof bonusText2 != "undefined")
      bonusText2.drawMe();



    // GAME OVER
    if (gameArea.lives <= 0) {
      // prestane obnovovat
      clearInterval(redrawInterval);
  
      // uplne funkčtný nezlyhaný pokus o odstranenie objektov :))
      deactivateBtns();
      delete live;
      delete boat;
  
      // endscreen
      gameArea.lives = 3; // obnovenie zivotov
      drawEndScreen();
    }
}
  