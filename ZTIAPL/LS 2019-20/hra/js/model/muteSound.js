// mute - ked to stlačíš, prepínanie hore dole medzi dvoma stavmi
function muteSound() {
    // z mute na ne mute
    if (gameArea.mute == 1) {
      audio.muted = false;
      gameArea.mute = 0;
      if(gameArea.mode == 3){
        drawMenu();
      }
      
      if(gameArea.mode == 2){
        updateGameAreaPlay2();
        if(gameArea.paused == 1)
        drawPause();
      }
      
      if(gameArea.mode == 1){
        updateGameAreaPlay1();
        if(gameArea.paused == 1)
        drawPause();
      }
  
      if(gameArea.mode == 4){
        drawEndScreen();
      }
      
    }
    // z ne mute na mamute
    else {
      audio.muted = true;
      gameArea.mute = 1;
      if(gameArea.mode == 3){
        drawMenu();
      }
      
      if(gameArea.mode == 2){
        updateGameAreaPlay2();
        if(gameArea.paused == 1)
        drawPause();
      }
      
      if(gameArea.mode == 1){
        updateGameAreaPlay1();
        if(gameArea.paused == 1)
        drawPause();
      }
  
      if(gameArea.mode == 4){
        drawEndScreen();
      }
    }
   
}