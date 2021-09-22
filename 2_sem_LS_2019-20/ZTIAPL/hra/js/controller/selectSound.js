// nahodny vyber zvukov
function selectSound() {
    // vygenerovanie náhodného čisla
    var random = Math.floor(Math.random() * 5);
  
    switch (true) {
      // menu ----------------------------------------------------------
      case gameArea.soundMode == "menu":
        switch (random) {
          case 1:
            playSound("../assets/music/menu01.mp3");
            break;
          case 2:
            playSound("../assets/music/menu02.mp3");
            break;
          case 3:
            playSound("../assets/music/menu03.mp3");
            break;
          case 4:
            playSound("../assets/music/menu04.mp3");
            break;
          case 0:
            playSound("../assets/music/menu05.mp3");
            break;
        }
        break;
  
      // soundMode 01 -----------------------------------------------
      case gameArea.soundMode == "mode01":
        switch (random) {
          case 1:
            playSound("../assets/music/mode01_01.mp3");
            break;
          case 2:
            playSound("../assets/music/mode01_02.mp3");
            break;
          case 3:
            playSound("../assets/music/mode01_03.mp3");
            break;
          case 4:
            playSound("../assets/music/mode01_04.mp3");
            break;
          case 0:
            playSound("../assets/music/mode01_05.mp3");
            break;
        }
        break;
  
      // soundMode 02 ---------------------------------------------
      case gameArea.soundMode == "mode02":
        switch (random) {
          case 1:
            playSound("../assets/music/mode02_01.mp3");
            break;
          case 2:
            playSound("../assets/music/mode02_02.mp3");
            break;
          case 3:
            playSound("../assets/music/mode02_03.mp3");
            break;
          case 4:
            playSound("../assets/music/mode02_04.mp3");
            break;
          case 0:
            playSound("../assets/music/mode02_05.mp3");
            break;
        }
        break;
  
      // rules ---------------------------------------------------
      case gameArea.soundMode == "rules":
        // 3 na vyber, nie 5
        random = random % 3;
        switch (random) {
          case 1:
            playSound("../assets/music/rules01.mp3");
            break;
          case 2:
            playSound("../assets/music/rules02.mp3");
            break;
          case 0:
            playSound("../assets/music/rules03.mp3");
            break;
        }
        break;
  
      // end screen ----------------------------------------------
      case gameArea.soundMode == "endscreen":
        playSound("../assets/music/endscreen.mp3");
        break;
    }
}