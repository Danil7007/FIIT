// spustenie obnovovacieho intervalu PLAY -----------------------------------------------------------------------

function play() {
    deactivateBtns();
    if(gameArea.mode == 4){
      gameArea.mode = gameArea.previousMode;
    }
    // mod 01 -------------------------------------------------------------------
    if (gameArea.mode == 1) {
      // počet framov za sekundu
      gameArea.fps = 60;
  
      // vytvorenie objektu txt
      scoreText = new txt(480, 100, "25px", "black", "0");
  
      // nastavenie modu audia (pre vyber) a zavolanie funkcie
      gameArea.soundMode = "mode01";
      selectSound();
  
      // ake vsetky objekty potrebuje na mod 01
  
      // deklaracia lodky a zivotov
      live = new kolieska();
      boat = new lodka();
  
      // chapadielka
      chapadielko1 = new chapadlo(100, 200, 200);
      chapadielko2 = new chapadlo(200, 200, 200);
      chapadielko3 = new chapadlo(300, 200, 200);
      chapadielko4 = new chapadlo(400, 200, 200);
      chapadielko1.active = true;
      chapadielko2.active = true;
      chapadielko3.active = true;
      chapadielko4.active = true;
      btns.push(chapadielko3, chapadielko2, chapadielko1, chapadielko4);
      redrawInterval = setInterval(updateGameAreaPlay1, 1000 / gameArea.fps);
    }
  
    // mod 02 -------------------------------------------------------------------
    if (gameArea.mode == 2) {
      gameArea.fps = 3;
      // cas na hru
      sec = 60;
  
      // texty
      scoreTextMode02 = new txt(500, 20, "25px", "black", "0");
      timeLeft = new txt(10, 20, "25px", "black", "0");
  
      // zvuk
      gameArea.soundMode = "mode02";
      selectSound();
  
      // objekty
      chapadielko1_2 = new chapadlo(30, 180, 200);
      chapadielko1_2.active = true;
      pena1 = new pena(68, 370, 36, 30);
  
      chapadielko2_2 = new chapadlo(200, 140, 200);
      chapadielko2_2.active = true;
      pena2 = new pena(235, 320, 36, 30);
  
      chapadielko3_2 = new chapadlo(320, 140, 200);
      chapadielko3_2.active = true;
      pena3 = new pena(355, 315, 36, 30);
  
      chapadielko4_2 = new chapadlo(460, 180, 200);
      chapadielko4_2.active = true;
      pena4 = new pena(500, 360, 36, 30);
  
      chapadielko5_2 = new chapadlo(100, 80, 125);
      chapadielko5_2.active = true;
  
      chapadielko6_2 = new chapadlo(175, 120, 125);
      chapadielko6_2.active = true;
  
      chapadielko7_2 = new chapadlo(300, 80, 125);
      chapadielko7_2.active = true;
  
      chapadielko8_2 = new chapadlo(500, 80, 125);
      chapadielko8_2.active = true;
  
      chapadielko9_2 = new chapadlo(220, 25, 90);
      chapadielko9_2.active = true;
      chapadielko9_2.width = 60;
  
      btns.push(
        chapadielko1_2,
        chapadielko2_2,
        chapadielko3_2,
        chapadielko4_2,
        chapadielko5_2,
        chapadielko6_2,
        chapadielko7_2,
        chapadielko8_2,
        chapadielko9_2
      );
  
      redrawInterval = setInterval(updateGameAreaPlay2, 1000 / gameArea.fps);
    }
}
  