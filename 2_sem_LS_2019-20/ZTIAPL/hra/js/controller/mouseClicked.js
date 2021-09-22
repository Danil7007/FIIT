// funkcia po kliknutí myšou ------------------------------------------------------------------------------------

function mouseClicked(e) {
    gameArea.mouseX = e.pageX - gameArea.oX;
    gameArea.mouseY = e.pageY - gameArea.oY;
  
    // menu -------------------------------------------------------------------
    if (typeof menuBtn_01 != "undefined" && menuBtn_01.clicked()) {
      gameArea.mode = 1;
      play();
    }
    if (typeof menuBtn_02 != "undefined" && menuBtn_02.clicked()) {
      gameArea.mode = 2;
      play();
    }
    if (typeof menuBtn_03 != "undefined" && menuBtn_03.clicked()) {
      setTimeout(drawRules, 200);
    }
  
    // chapadla v hre - mod 01 ------------------------------------------------
    if (typeof chapadielko1 != "undefined" && chapadielko1.clicked()) {
      playSoundEffect();
      chapadielko1.height = 200;
      chapadielko1.Y = 200;
    }
    if (typeof chapadielko1 != "undefined" && chapadielko2.clicked()) {
      playSoundEffect();
      chapadielko2.height = 200;
      chapadielko2.Y = 200;
    }
    if (typeof chapadielko1 != "undefined" && chapadielko3.clicked()) {
      playSoundEffect();
      chapadielko3.height = 200;
      chapadielko3.Y = 200;
    }
    if (typeof chapadielko1 != "undefined" && chapadielko4.clicked()) {
      playSoundEffect();
      chapadielko4.height = 200;
      chapadielko4.Y = 200;
    }
  
    // tlacitko(a) pauza --------------------------------------------------------
  
    if (typeof pauzickaBtn != "undefined" && pauzickaBtn.clicked()) {
      clearInterval(redrawInterval);
      gameArea.paused = 1;
  
      drawPause();
    }
  
    if (typeof quitBtn != "undefined" && quitBtn.clicked()) {
      deactivateBtns();
  gameArea.paused = 0;
      audio.pause();
      drawEndScreen();
    }
  
    if (typeof resumeBtn != "undefined" && resumeBtn.clicked()) {
      gameArea.paused = 0;
      quitBtn.active = false;
      resumeBtn.active = false;
      if (gameArea.mode == 2)
        redrawInterval = setInterval(updateGameAreaPlay2, 1000 / gameArea.fps);
      if (gameArea.mode == 1)
        redrawInterval = setInterval(updateGameAreaPlay1, 1000 / gameArea.fps);
    }
  
    // tlačitka endscreen ----------------------------------------------------
    if (typeof endBtn_01 != "undefined" && endBtn_01.clicked()) {
      score.myScore = 0;
      audio.pause();
      drawMenu();
    }
    if (typeof endBtn_02 != "undefined" && endBtn_02.clicked()) {
      score.myScore = 0;
      deactivateBtns();
      audio.pause();
      play();
    }
  
    // tlačitka v hre- mod 02 ------------------------------------------------
    if (
      typeof chapadielko1_2 != "undefined" &&
      chapadielko1_2.clicked() &&
      chapadielko1_2.visible == 1
    ) {
      playSoundEffect();
      chapadielko1_2.visible = 0;
      score.myScore++;
    }
    if (
      typeof chapadielko2_2 != "undefined" &&
      chapadielko2_2.clicked() &&
      chapadielko2_2.visible == 1
    ) {
      playSoundEffect();
      chapadielko2_2.visible = 0;
      score.myScore++;
    }
    if (
      typeof chapadielko3_2 != "undefined" &&
      chapadielko3_2.clicked() &&
      chapadielko3_2.visible == 1
    ) {
      playSoundEffect();
      chapadielko3_2.visible = 0;
      score.myScore++;
    }
    if (
      typeof chapadielko4_2 != "undefined" &&
      chapadielko4_2.clicked() &&
      chapadielko4_2.visible == 1
    ) {
      playSoundEffect();
      chapadielko4_2.visible = 0;
      score.myScore++;
    }
    if (
      typeof chapadielko5_2 != "undefined" &&
      chapadielko5_2.clicked() &&
      chapadielko5_2.visible == 1
    ) {
      playSoundEffect();
      chapadielko5_2.visible = 0;
      score.myScore++;
    }
    if (
      typeof chapadielko6_2 != "undefined" &&
      chapadielko6_2.clicked() &&
      chapadielko6_2.visible == 1
    ) {
      playSoundEffect();
      chapadielko6_2.visible = 0;
      score.myScore++;
    }
    if (
      typeof chapadielko7_2 != "undefined" &&
      chapadielko7_2.clicked() &&
      chapadielko7_2.visible == 1
    ) {
      playSoundEffect();
      chapadielko7_2.visible = 0;
      score.myScore++;
    }
    if (
      typeof chapadielko8_2 != "undefined" &&
      chapadielko8_2.clicked() &&
      chapadielko8_2.visible == 1
    ) {
      playSoundEffect();
      chapadielko8_2.visible = 0;
      score.myScore++;
    }
    if (
      typeof chapadielko9_2 != "undefined" &&
      chapadielko9_2.clicked() &&
      chapadielko9_2.visible == 1
    ) {
      playSoundEffect();
      chapadielko9_2.visible = 0;
      score.myScore++;
    }
  
    if (typeof goBackBtn != "undefined" && goBackBtn.clicked()) {
      delete txt;
      //delete btn;
      deactivateBtns();
      drawMenu();
    }
  
    if (typeof muteBtn != "undefined" && muteBtn.clicked()) {
      muteSound();
    }
}