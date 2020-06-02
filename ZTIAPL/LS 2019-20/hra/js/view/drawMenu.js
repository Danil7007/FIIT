// vykreslenie menu ---------------------------------------------------------------------------------------------

function drawMenu() {
    deactivateBtns();
  
    gameArea.mode=3;
    gameArea.soundMode = "menu";
  
    selectSound();
  
    menuBtn_01.active = true; // vytvorenie objektov tlačidiel
    menuBtn_02.active = true;
    menuBtn_03.active = true;
    muteBtn.active = true;
    pauzickaBtn.active = true;
  
    gameArea.clear(); // vyčistenie canvas
  
    gameArea.context.drawImage(
      // nakreslenie obrázku
      menu01,
      0,
      0,
      gameArea.canvas.width,
      gameArea.canvas.height
    );
    if (gameArea.mute == 1) {
      gameArea.context.drawImage(mute, 10, 10, 30, 30);
    } else {
      gameArea.context.drawImage(mute02, 10, 10, 30, 30);
    }
}