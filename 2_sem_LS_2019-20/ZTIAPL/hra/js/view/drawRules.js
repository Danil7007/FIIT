// vykreslenie pravidiel ----------------------------------------------------------------------------------------

function drawRules() {
    gameArea.clear();
    var ctx = gameArea.context;
    ctx.textAlign = "center";
  
    rulesText1 = new txt(
      gameArea.canvas.width / 2,
      100,
      "60px",
      "Black",
      "RULES"
    );
  
    rulesText2 = new txt(
      gameArea.canvas.width / 2,
      150,
      "18px",
      "Black",
      "Mode 01: Click on chapadielko object to retract it."
    );
  
    rulesText3 = new txt(
      gameArea.canvas.width / 2,
      170,
      "18px",
      "Black",
      "Mode 01: Chapadielko cannot touch the ship otherwise you loose a life."
    );
  
    rulesText4 = new txt(
      gameArea.canvas.width / 2,
      200,
      "18px",
      "Black",
      "Mode 02: Click as many chapadielko objects as you can."
    );
  
    rulesText5 = new txt(
      gameArea.canvas.width / 2,
      220,
      "18px",
      "Black",
      "Mode 02: You have 60 seconds."
    );
  
    rulesText6 = new txt(
      gameArea.canvas.width / 2,
      270,
      "18px",
      "Black",
      "To go back to the menu click anywhere on this screen"
    );
  
    rulesText1.drawMe();
    rulesText2.drawMe();
    rulesText3.drawMe();
    rulesText4.drawMe();
    rulesText5.drawMe();
    rulesText6.drawMe();
  
    // mute
    //gameArea.context.drawImage(mute,10,10,30,30);
  
    goBackBtn.active = true;
    ctx.textAlign = "left";
}