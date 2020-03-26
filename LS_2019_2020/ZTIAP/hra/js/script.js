//globalne premenne
var mouseX;
var mouseY;
var fps = 60;
var redrawInterval;
var frameNo = 0;
var score = [{ date: null, score: null, gameMode: null }];
var myScore = 0;
var diff = 5;
var myStorage = window.localStorage;
var lives = 3;
var soundMode = "menu";
var audio;
var mode;
var sec = 0;
var count = 0;
var done = 0;

//inicializačná funkcia --------------------------------------------------------------------------------------
function init() {
  preloadAssets();
  audio = new Audio();
  // na pracu s formatmi dat
  if (myStorage.getItem("score") != null) {
    score = JSON.parse(myStorage.getItem("score"));
  }

  window.addEventListener("click", mouseClicked);
  // canvas
  gameArea.createCanvas();
  setTimeout(drawMenu, 400);
  live = new kolieska();
  boat = new lodka();

  printToTable();
}

// skore -----------------------------------------------------------------------------------------------------
function printToTable() {
  var table = document.querySelector("tbody");
  for (var i = 0; i < score.length; i++) {
    if (score[i].date != null && score[i].score != null) {
      var row = document.createElement("tr");
      var cell = document.createElement("td");
      cell.textContent =
        score[i].date + " " + score[i].score + " Mode: " + score[i].gameMode;
      row.appendChild(cell);
      table.appendChild(row);
    }
  }
}

// zvuky -----------------------------------------------------------------------------------------------------
// let funkcie sa nestackuju
function selectSound() {
  var random = Math.floor(Math.random() * 5);
  switch (true) {
    // menu
    case soundMode == "menu":
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

    // soundMode 01
    case soundMode == "mode01":
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

    // soundMode 02
    case soundMode == "mode02":
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

    // rules
    case soundMode == "rules":
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

    // end screen
    case soundMode == "endscreen":
      playSound("../assets/music/endscreen.mp3");
      break;
  }
}

function playSound(src) {
  audio.pause();
  audio.src = src;
  audio.volume = 0.5;
  audio.play();
  audio.onended = function() {
    selectSound();
  };
}

//prednačítnie všetkých obrázkov --------------------------------------------------------------------------------
function preloadAssets() {
  // pozadie 02
  this.background02_01 = new Image(); //vytvorenie objektu "obrázok"
  this.background02_01.src = "../assets/pictures/bg/bg02_01.png"; //pridanie objektu cestu k súboru
  this.background02_02 = new Image();
  this.background02_02.src = "../assets/pictures/bg/bg02_02.png";
  this.background02_03 = new Image();
  this.background02_03.src = "../assets/pictures/bg/bg02_03.png";

  // pozadie 01
  this.background01_01 = new Image();
  this.background01_01.src = "../assets/pictures/bg/bg01_01.png";
  this.background01_02 = new Image();
  this.background01_02.src = "../assets/pictures/bg/bg01_02.png";
  this.background01_03 = new Image();
  this.background01_03.src = "../assets/pictures/bg/bg01_03.png";

  // menu
  this.menu01 = new Image();
  this.menu01.src = "../assets/pictures/bg/menu01.png";
  this.menu02 = new Image();
  this.menu02.src = "../assets/pictures/bg/menu02.png";

  // chapadielka
  this.chapadlo01 = new Image();
  this.chapadlo01.src = "../assets/pictures/octo/chapadlo01.PNG";
  this.chapadlo02 = new Image();
  this.chapadlo02.src = "../assets/pictures/octo/chapadlo02.PNG";
  this.chapadlo03 = new Image();
  this.chapadlo03.src = "../assets/pictures/octo/chapadlo03.PNG";

  // chobotnica
  this.octo01 = new Image();
  this.octo01.src = "../assets/pictures/octo/octo01.PNG";
  this.octo02 = new Image();
  this.octo02.src = "../assets/pictures/octo/octo02.PNG";
  this.octo03 = new Image();
  this.octo03.src = "../assets/pictures/octo/octo03.png";

  // lodka
  this.boat01 = new Image();
  this.boat01.src = "../assets/pictures/boat/boat01.PNG";
  this.boat02 = new Image();
  this.boat02.src = "../assets/pictures/boat/boat02.PNG";

  // zivoty
  this.lives01 = new Image();
  this.lives01.src = "../assets/pictures/lives/lives01.png";
  this.lives02 = new Image();
  this.lives02.src = "../assets/pictures/lives/lives02.png";
  this.lives03 = new Image();
  this.lives03.src = "../assets/pictures/lives/lives03.png";

  // pena
  this.imgPena = new Image();
  this.imgPena.src = "../assets/pictures/particles/pena.png";
}

//spustenie obnovovacieho intervalu
function play() {
  delete menuBtn_01;
  delete menuBtn_02;
  delete menuBtn_03;
  // mod 01
  if (mode == 1) {
    fps = 60;
    scoreText = new txt(480, 100, "25px", "black", "0");
    soundMode = "mode01";
    selectSound();
    chapadielko1 = new chapadlo(100, 200, 200);
    chapadielko1Btn = new btn(125, 175, 200, 400);

    chapadielko2 = new chapadlo(200, 200, 200);
    chapadielko2Btn = new btn(225, 275, 200, 400);

    chapadielko3 = new chapadlo(300, 200, 200);
    chapadielko3Btn = new btn(325, 375, 200, 400);

    chapadielko4 = new chapadlo(400, 200, 200);
    chapadielko4Btn = new btn(425, 475, 200, 400);

    redrawInterval = setInterval(updateGameAreaPlay1, 1000 / fps);
  }

  //mód 2
  if (mode == 2) {
    fps = 3;
    sec = 60;
    scoreTextMode02 = new txt(500, 20, "25px", "black", "0");
    timeLeft = new txt(10, 20, "25px", "black", "0");
    soundMode = "mode02";
    selectSound();
    chapadielko1 = new chapadlo(30, 180, 200);

    pena1 = new pena(68, 370, 36, 30);

    chapadielko2 = new chapadlo(200, 140, 200);

    pena2 = new pena(235, 320, 36, 30);

    chapadielko3 = new chapadlo(320, 140, 200);

    pena3 = new pena(355, 315, 36, 30);

    chapadielko4 = new chapadlo(460, 180, 200);

    pena4 = new pena(500, 360, 36, 30);

    chapadielko5 = new chapadlo(100, 80, 125);

    chapadielko6 = new chapadlo(175, 120, 125);

    chapadielko7 = new chapadlo(300, 80, 125);

    chapadielko8 = new chapadlo(500, 80, 125);

    chapadielko9 = new chapadlo(220, 25, 90);
    chapadielko9.width = 60;

    redrawInterval = setInterval(updateGameAreaPlay2, 1000 / fps);
  }
}

//funkcia mod1
function updateGameAreaPlay1() {
  frameNo += 1;

  // zvysovanie narocnosti
  if (myScore != 0 && myScore % 5 == 0) {
    diff += 1 / 120;
  }

  if (frameNo > 60) {
    frameNo = 0;
    myScore += 1;
  } //počítanie čísla snímku
  gameArea.clear(); //čistenie canvas

  // lodka
  if (frameNo <= 30) {
    boat.drawMe(1);
  }
  if (frameNo > 30) {
    boat.drawMe(2);
  }

  switch (
    true //prehrávanie animácie
  ) {
    // pozadie + chapadla
    case frameNo <= 15:
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
    case frameNo <= 30:
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
    case frameNo <= 45:
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
    case frameNo <= 60:
      gameArea.context.drawImage(
        background01_02,
        0,
        0,
        gameArea.canvas.width,
        gameArea.canvas.height
      );

      // pohyb chapadiel
      var random = Math.floor(Math.random() * 20);
      chapadielko1.drawMe(2);
      chapadielko2.drawMe(1);
      chapadielko3.drawMe(2);
      chapadielko4.drawMe(3);
      // chapadlo 01
      if (chapadielko1.Y >= 0 && random == 0) {
        chapadielko1.height += 1 * diff;
        chapadielko1.Y -= 1 * diff;
        chapadielko1Btn.yT = chapadielko1.Y;
        // chytilo lod
        if (chapadielko1.Y < 0) {
          lives -= 1;
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
        chapadielko2.height += 1 * diff;
        chapadielko2.Y -= 1 * diff;
        chapadielko2Btn.yT = chapadielko2.Y;
        // chytilo lod
        if (chapadielko2.Y < 0) {
          lives -= 1;
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
        chapadielko3.height += 1 * diff;
        chapadielko3.Y -= 1 * diff;
        chapadielko3Btn.yT = chapadielko3.Y;
        // chytilo lod
        if (chapadielko3.Y < 0) {
          lives -= 1;
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
        chapadielko4.height += 1 * diff;
        chapadielko4.Y -= 1 * diff;
        chapadielko4Btn.yT = chapadielko4.Y;
        // chytilo lod
        if (chapadielko4.Y < 0) {
          lives -= 1;
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

  // zivoty
  if (lives == 3) {
    live.drawMe(1);
  }
  if (lives == 2) {
    live.drawMe(2);
  }
  if (lives == 1) {
    live.drawMe(3);
  }

  // chobotnica
  //gameArea.context.drawImage(octo03, 60, 235, 460, 240);
  gameArea.context.drawImage(octo03, 0, 0, 613, 434);
  scoreText.text = "Score: " + myScore;
  scoreText.drawMe();

  if (lives <= 0) {
    clearInterval(redrawInterval);

    // odstranenie objektov
    delete btn;
    delete chapadlo;
    delete kolieska;
    delete lodka;
    // endscreen

    lives = 3;
    drawEndScreen();
  }
}

function updateGameAreaPlay2() {
  frameNo += 1;

  if (frameNo > 3) {
    frameNo = 0;
    count += 0.5;
    sec--;
  }
  console.log(count);
  gameArea.clear();
  switch (true) {
    case frameNo == 0:
      gameArea.context.drawImage(
        background02_01,
        0,
        0,
        gameArea.canvas.width,
        gameArea.canvas.height
      );
      break;
    case frameNo == 1:
      gameArea.context.drawImage(
        background02_02,
        0,
        0,
        gameArea.canvas.width,
        gameArea.canvas.height
      );
      break;
    case frameNo == 2:
      gameArea.context.drawImage(
        background02_03,
        0,
        0,
        gameArea.canvas.width,
        gameArea.canvas.height
      );
      break;
    case frameNo == 3:
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
  if (sec == 60) diff = 2;
  if (sec == 45) diff = 1;
  if (sec == 30) diff = 0.5;
  if (count >= diff && done == 0) {
    chapadielko1.visible = 0;
    chapadielko2.visible = 0;
    chapadielko3.visible = 0;
    chapadielko4.visible = 0;
    chapadielko5.visible = 0;
    chapadielko6.visible = 0;
    chapadielko7.visible = 0;
    chapadielko8.visible = 0;
    chapadielko9.visible = 0;
    var random = Math.floor(Math.random() * 9);
    done = 1;
    count = 0;
    switch (random) {
      case 0:
        chapadielko1.visible = 1;
        chapadielko1Btn2 = new btn(60, 110, 200, 380);
        break;
      case 1:
        chapadielko2.visible = 1;
        chapadielko2Btn2 = new btn(225, 275, 150, 350);
        break;
      case 2:
        chapadielko3.visible = 1;
        chapadielko3Btn2 = new btn(350, 400, 150, 350);
        break;
      case 3:
        chapadielko4.visible = 1;
        chapadielko4Btn2 = new btn(490, 530, 200, 400);
        break;
      case 4:
        chapadielko5.visible = 1;
        chapadielko5Btn2 = new btn(115, 155, 100, 210);
        break;
      case 5:
        chapadielko6.visible = 1;
        chapadielko6Btn2 = new btn(200, 220, 130, 250);
        break;
      case 6:
        chapadielko7.visible = 1;
        chapadielko7Btn2 = new btn(325, 345, 90, 210);
        break;
      case 7:
        chapadielko8.visible = 1;
        chapadielko8Btn2 = new btn(525, 545, 90, 210);
        break;
      case 8:
        chapadielko9.visible = 1;
        chapadielko9Btn2 = new btn(245, 265, 35, 120);
        break;
    }
  }

  if (chapadielko1.visible == 1) {
    chapadielko1.drawMe(2);
    pena1.drawMe();
  }
  if (chapadielko2.visible == 1) {
    chapadielko2.drawMe(2);
    pena2.drawMe();
  }
  if (chapadielko3.visible == 1) {
    chapadielko3.drawMe(2);
    pena3.drawMe();
  }
  if (chapadielko4.visible == 1) {
    chapadielko4.drawMe(2);
    pena4.drawMe();
  }
  if (chapadielko5.visible == 1) {
    chapadielko5.drawMe(2);
  }
  if (chapadielko6.visible == 1) {
    chapadielko6.drawMe(2);
  }
  if (chapadielko7.visible == 1) {
    chapadielko7.drawMe(2);
  }
  if (chapadielko8.visible == 1) {
    chapadielko8.drawMe(2);
  }
  if (chapadielko9.visible == 1) {
    chapadielko9.drawMe(2);
  }

  scoreTextMode02.text = "Score: " + myScore;
  timeLeft.text = "Time left: " + sec;
  scoreTextMode02.drawMe();
  timeLeft.drawMe();
  scoreTextMode02.drawMe();
  timeLeft.drawMe();
  scoreTextMode02.drawMe();
  timeLeft.drawMe();

  if (sec <= 0) {
    delete btn;
    delete txt;
    delete chapadlo;
    delete pena;
    clearInterval(redrawInterval);
    drawEndScreen();
  }
}
//
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
  goBackBtn = new btn(0, gameArea.canvas.width, 0, gameArea.canvas.height);
  ctx.textAlign = "left";
}

// nakreslenie menu
function drawMenu() {
  soundMode = "menu";
  selectSound();
  menuBtn_01 = new btn(195, 445, 80, 140); //vytvorenie objektov tlačidiel
  menuBtn_02 = new btn(195, 445, 200, 260);
  menuBtn_03 = new btn(195, 445, 290, 360);

  gameArea.clear(); //vyčistenie canvas
  gameArea.context.drawImage(
    //nakreslenie obrázku
    menu01,
    0,
    0,
    gameArea.canvas.width,
    gameArea.canvas.height
  );
}

// endscreen
function drawEndScreen() {
  var date = new Date();
  score.push({
    date: date.getDate() + "/" + date.getMonth() + "/" + date.getFullYear(),
    score: myScore,
    gameMode: mode
  });
  if (score.length > 10) score.splice(0, 1);
  score.sort((a, b) => (a.score < b.score ? 1 : -1));

  myStorage.setItem("score", JSON.stringify(score));
  printToTable();
  soundMode = "endscreen";
  selectSound();

  endBtn_01 = new btn(45, 290, 300, 365); //vytvorenie objektov tlačidiel
  endBtn_02 = new btn(325, 575, 300, 365);

  scoreTextEndScreen_01 = new txt(100, 200, "50px", "black", "0");
  scoreTextEndScreen_02 = new txt(
    gameArea.canvas.width / 2 - 10,
    250,
    "60px",
    "black",
    "0"
  );

  gameArea.clear(); //vyčistenie canvas
  gameArea.context.drawImage(
    //nakreslenie obrázku
    menu02,
    0,
    0,
    gameArea.canvas.width,
    gameArea.canvas.height
  );

  scoreTextEndScreen_01.text = "Your score was: ";
  scoreTextEndScreen_02.text = myScore;

  scoreTextEndScreen_01.drawMe();
  scoreTextEndScreen_02.drawMe();
}

// objekt tlačidlo
function btn(xLeft, xRight, yTop, yBottom) {
  this.xL = xLeft;
  this.xR = xRight;
  this.yT = yTop;
  this.yB = yBottom;
  this.height = this.yB - this.yT;
  this.width = this.xR - this.xL;
  this.drawMe = function() {
    //funkcia na vykreslenie v canvas
    gameArea.context.strokeStyle = "red";
    gameArea.context.beginPath();
    gameArea.context.rect(this.xL, this.yT, this.width, this.height);
    gameArea.context.stroke();
  };
}

//funkcia na overenie kliknutia na tlačidlo
btn.prototype.clicked = function() {
  if (
    this.xL <= mouseX &&
    mouseX <= this.xR &&
    this.yT <= mouseY &&
    mouseY <= this.yB
  ) {
    return true;
  }
};

// funkcia text --------------------------------------------------------------------------------------------
function txt(x, y, size, color, text) {
  this.X = x;
  this.Y = y;
  this.size = size;
  this.color = color;
  this.text = text;
  this.drawMe = function() {
    gameArea.context.font = this.size + " AR";
    gameArea.context.fillStyle = color;
    gameArea.context.fillText(this.text, this.X, this.Y);
  };
}

//objekt pre chapadielko
function chapadlo(x, y, scale) {
  this.X = x;
  this.Y = y;
  this.visible = 0;
  this.width = scale / 2;
  this.height = scale;
  this.drawMe = function(version) {
    switch (true) {
      case version == 1:
        gameArea.context.drawImage(
          chapadlo01,
          this.X,
          this.Y,
          this.width,
          this.height
        );
        break;
      case version == 2:
        gameArea.context.drawImage(
          chapadlo02,
          this.X,
          this.Y,
          this.width,
          this.height
        );
        break;
      case version == 3:
        gameArea.context.drawImage(
          chapadlo03,
          this.X,
          this.Y,
          this.width,
          this.height
        );
        break;
    }
  };
}

//objekt pre zivoty
function kolieska() {
  this.X = 475;
  this.Y = 5;
  this.width = 130;
  this.height = 40;
  this.drawMe = function(version) {
    switch (true) {
      case version == 1:
        gameArea.context.drawImage(
          lives03,
          this.X,
          this.Y,
          this.width,
          this.height
        );
        break;
      case version == 2:
        gameArea.context.drawImage(
          lives02,
          this.X,
          this.Y,
          this.width,
          this.height
        );
        break;
      case version == 3:
        gameArea.context.drawImage(
          lives01,
          this.X,
          this.Y,
          this.width,
          this.height
        );
        break;
    }
  };
}

//objekt pre lodku
function lodka() {
  this.X = 0;
  this.Y = 0;
  this.width = 613.9;
  this.height = 434;
  this.drawMe = function(version) {
    switch (true) {
      case version == 1:
        gameArea.context.drawImage(
          boat01,
          this.X,
          this.Y,
          this.width,
          this.height
        );
        break;
      case version == 2:
        gameArea.context.drawImage(
          boat02,
          this.X,
          this.Y,
          this.width,
          this.height
        );
        break;
    }
  };
}

//objekt pre penu
function pena(x, y, width, height) {
  this.X = x;
  this.Y = y;
  this.width = width;
  this.height = height;
  this.drawMe = function() {
    gameArea.context.drawImage(
      imgPena,
      this.X,
      this.Y,
      this.width,
      this.height
    );
  };
}

// premenná pre canvas --------------------------------------------------------------------
var gameArea = {
  canvas: document.querySelector("canvas"), //ziskanie elementu canvas
  nadpis: document.querySelector("h1"), //ziskanie elementu nadpis
  frameNo: 0,
  menu: 0,

  createCanvas: function() {
    this.context = this.canvas.getContext("2d"); //zsikanie contextu - obsahu canvas
    this.canvas.width = 613.9;
    this.canvas.height = 434;
    //this.canvas.style.cursor = url("../assets/cursor/chapadlo03.cur"),auto;
    // offset od vrchu stranky po canvas
    this.oX = parseInt(window.getComputedStyle(this.canvas).marginLeft);
    this.oY =
      parseInt(window.getComputedStyle(this.canvas).marginTop) +
      parseInt(window.getComputedStyle(this.nadpis).height);
  },

  // cistenie canvas
  clear: function() {
    this.context.clearRect(0, 0, this.canvas.width, this.canvas.height);
  }
};

// funkcia po kliknutí myšou ------------------------------------------------------------
function mouseClicked(e) {
  this.mouseX = e.pageX - gameArea.oX;
  this.mouseY = e.pageY - gameArea.oY;

  // menu
  if (typeof menuBtn_01 != "undefined" && menuBtn_01.clicked()) {
    mode = 1;
    play();
  }
  if (typeof menuBtn_02 != "undefined" && menuBtn_02.clicked()) {
    mode = 2;
    play();
  }
  if (typeof menuBtn_03 != "undefined" && menuBtn_03.clicked()) {
    setTimeout(drawRules, 200);
  }
  // chapadla v hre - mod 01
  if (typeof chapadielko1Btn != "undefined" && chapadielko1Btn.clicked()) {
    chapadielko1.height = 200;
    chapadielko1.Y = 200;
  }
  if (typeof chapadielko1Btn != "undefined" && chapadielko2Btn.clicked()) {
    chapadielko2.height = 200;
    chapadielko2.Y = 200;
  }
  if (typeof chapadielko1Btn != "undefined" && chapadielko3Btn.clicked()) {
    chapadielko3.height = 200;
    chapadielko3.Y = 200;
  }
  if (typeof chapadielko1Btn != "undefined" && chapadielko4Btn.clicked()) {
    chapadielko4.height = 200;
    chapadielko4.Y = 200;
  }
  // tlačitka endscreen
  if (typeof endBtn_01 != "undefined" && endBtn_01.clicked()) {
    myScore = 0;
    delete btn;
    drawMenu();
  }
  if (typeof endBtn_02 != "undefined" && endBtn_02.clicked()) {
    myScore = 0;
    delete btn;
    play();
  }

  //tlačitka mode2
  if (typeof chapadielko1Btn2 != "undefined" && chapadielko1Btn2.clicked()) {
    chapadielko1.visible = 0;
    myScore++;
    delete chapadielko1Btn2;
  }
  if (typeof chapadielko2Btn2 != "undefined" && chapadielko2Btn2.clicked()) {
    chapadielko2.visible = 0;
    myScore++;
    delete chapadielko2Btn2;
  }
  if (typeof chapadielko3Btn2 != "undefined" && chapadielko3Btn2.clicked()) {
    chapadielko3.visible = 0;
    myScore++;
    delete chapadielko3Btn2;
  }
  if (typeof chapadielko4Btn2 != "undefined" && chapadielko4Btn2.clicked()) {
    chapadielko4.visible = 0;
    myScore++;
    delete chapadielko4Btn2;
  }
  if (typeof chapadielko5Btn2 != "undefined" && chapadielko5Btn2.clicked()) {
    chapadielko5.visible = 0;
    myScore++;
    delete chapadielko5Btn2;
  }
  if (typeof chapadielko6Btn2 != "undefined" && chapadielko6Btn2.clicked()) {
    chapadielko6.visible = 0;
    myScore++;
    delete chapadielko6Btn2;
  }
  if (typeof chapadielko7Btn2 != "undefined" && chapadielko7Btn2.clicked()) {
    chapadielko7.visible = 0;
    myScore++;
    delete chapadielko7Btn2;
  }
  if (typeof chapadielko8Btn2 != "undefined" && chapadielko8Btn2.clicked()) {
    chapadielko8.visible = 0;
    myScore++;
    delete chapadielko8Btn2;
  }
  if (typeof chapadielko9Btn2 != "undefined" && chapadielko9Btn2.clicked()) {
    chapadielko9.visible = 0;
    myScore++;
    delete chapadielko9Btn2;
  }

  if (typeof goBackBtn != "undefined" && goBackBtn.clicked()) {
    delete txt;
    delete btn;
    drawMenu();
  }
}
