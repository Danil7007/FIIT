//globalne premenne
var mouseX;
var mouseY;
var fps = 60;
var redrawInterval;
var frameNo = 0;
var score = [
  { date: null, score: null }
];
var myScore =0;
var diff=1;
var myStorage = window.localStorage;
var lives = 3;
var soundMode = "menu";
var audio;

//inicializačná funkcia
function init() {
  preloadAssets();
  audio = new Audio();
  // na pracu s formatmi dat
  score = JSON.parse(myStorage.getItem('score'));
  window.addEventListener("click", mouseClicked);
  gameArea.createCanvas();
  setTimeout(drawMenu, 400);
  live = new kolieska();
  setTimeout(selectSound, 4000);
  
}

function printToTable(){
    var table = document.querySelector("tbody");
    for(var i = 0; i< score.length;i++){
      if(score[i].date != null && score[i].score != null){
      var row = document.createElement('tr');
      var cell = document.createElement('td');
      cell.textContent = score[i].date + " " + score[i].score;
      row.appendChild(cell);
      table.appendChild(row);
      }
    }
}

// let funkcie sa nestackuju
function selectSound() {
  var random = Math.floor(Math.random() * 5);
  switch (true) {
    // menu
    case (soundMode == 'menu'):
      switch (random){
        case 1: playSound('../assets/music/menu01.mp3');break;
        case 2: playSound('../assets/music/menu02.mp3');break;
        case 3: playSound('../assets/music/menu03.mp3');break;
        case 4: playSound('../assets/music/menu04.mp3');break;
        case 0: playSound('../assets/music/menu05.mp3');break;
      }
      break;

    // soundMode 01
    case (soundMode == 'mode01'):
      
      switch (random){
        case 1: playSound('../assets/music/mode01_01.mp3');break;
        case 2: playSound('../assets/music/mode01_02.mp3');break;
        case 3: playSound('../assets/music/mode01_03.mp3');break;
        case 4: playSound('../assets/music/mode01_04.mp3');break;
        case 0: playSound('../assets/music/mode01_05.mp3');break;
      }
      break;

    // soundMode 02
    case (soundMode == 'mode02'):
      
      switch (random){
        case 1: playSound('../assets/music/mode02_01.mp3');break;
        case 2: playSound('../assets/music/mode02_02.mp3');break;
        case 3: playSound('../assets/music/mode02_03.mp3');break;
        case 4: playSound('../assets/music/mode02_04.mp3');break;
        case 0: playSound('../assets/music/mode02_05.mp3');break;
      }
      break;

    // rules
    case (soundMode == 'rules'):
        random = random %3;
        switch (random){
        case 1: playSound('../assets/music/rules01.mp3');break;
        case 2: playSound('../assets/music/rules02.mp3');break;
        case 0: playSound('../assets/music/rules03.mp3');break;

      }
      break;

    // end screen
    case (soundMode == 'endscreen'):
      playSound('../assets/music/endscreen.mp3');break;

  }
}

function playSound (src){
  audio.pause();
  audio.src = src;
  audio.volume = 0.5;
  audio.play();
  audio.onended = function(){
    selectSound();
  }
}



//prednačítnie všetkých obrázkov
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

  // zivoty
  this.lives01 = new Image();
  this.lives01.src = "../assets/pictures/lives/lives01.png";
  this.lives02 = new Image();
  this.lives02.src = "../assets/pictures/lives/lives02.png";
  this.lives03 = new Image();
  this.lives03.src = "../assets/pictures/lives/lives03.png";
}

//spustenie obnovovacieho intervalu
function play(i) {
  delete menuBtn_01;
  delete menuBtn_02;
  if (i == 1) {
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
  } //mód 1
  if (i == 2) {
    soundMode = "mode02";
    selectSound();
    redrawInterval = setInterval(updateGameAreaPlay2, 1000 / fps);
  } //mód 2
}

//funkcia mod1
function updateGameAreaPlay1() {
  frameNo += 1;
  
  console.log(myScore);
  // zvysovanie narocnosti
  if (myScore != 0 && myScore % 5 == 0) { diff+= 1/120;}

  if (frameNo > 60) {frameNo = 0; myScore += 1;} //počítanie čísla snímku
  gameArea.clear(); //čistenie canvas
  switch (
    true //prehrávanie animácie
  ) {
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
      var random = Math.floor(Math.random() * 20);
      chapadielko1.drawMe(2);
      chapadielko2.drawMe(1);
      chapadielko3.drawMe(2);
      chapadielko4.drawMe(3);
      if (chapadielko1.Y >= 0 && random == 0) {
        chapadielko1.height += 1 * diff;
        chapadielko1.Y -= 1 * diff;
        chapadielko1Btn.yT = chapadielko1.Y;
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
      if (chapadielko2.Y >= 0 && random == 1) {
        chapadielko2.height += 1 * diff;
        chapadielko2.Y -= 1 * diff;
        chapadielko2Btn.yT = chapadielko2.Y;
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
      if (chapadielko3.Y >= 0 && random == 2) {
        chapadielko3.height += 1 * diff;
        chapadielko3.Y -= 1 * diff;
        chapadielko3Btn.yT = chapadielko3.Y;
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
      if (chapadielko1.Y >= 0 && random == 3) {
        chapadielko4.height += 1 * diff;
        chapadielko4.Y -= 1 * diff;
        chapadielko4Btn.yT = chapadielko4.Y;
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
  if(lives == 3){live.drawMe(1);}
  if(lives == 2){live.drawMe(2);}
  if(lives == 1){live.drawMe(3);}

  gameArea.context.drawImage(octo03, 60, 235, 460, 240);
  chapadielko1Btn.drawMe();
  chapadielko2Btn.drawMe();
  chapadielko3Btn.drawMe();
  chapadielko4Btn.drawMe();

  if (lives <= 0) {
    clearInterval(redrawInterval);
    var date = new Date();
    score.push({date: date.getDate()+"/"+date.getMonth()+"/"+date.getFullYear(), score: myScore});
    myStorage.setItem("score", JSON.stringify(score));

    alert("Prehral/a si. Tvoje skore bolo: " + myScore);
  }
}


function updateGameAreaPlay2() {
  frameNo += 1;
  if (frameNo > 60) frameNo = 0;
  gameArea.clear();
  switch (true) {
    case frameNo <= 15:
      gameArea.context.drawImage(
        background02_01,
        0,
        0,
        gameArea.canvas.width,
        gameArea.canvas.height
      );
      break;
    case frameNo <= 30:
      gameArea.context.drawImage(
        background02_02,
        0,
        0,
        gameArea.canvas.width,
        gameArea.canvas.height
      );
      break;
    case frameNo <= 45:
      gameArea.context.drawImage(
        background02_03,
        0,
        0,
        gameArea.canvas.width,
        gameArea.canvas.height
      );
      break;
    case frameNo <= 60:
      gameArea.context.drawImage(
        background02_02,
        0,
        0,
        gameArea.canvas.width,
        gameArea.canvas.height
      );
      break;
  }
}

//nakreslenie menu
function drawMenu() {
  
  menuBtn_01 = new btn(190, 440, 80, 140); //vytvorenie objektov tlačidiel
  menuBtn_02 = new btn(190, 440, 160, 220);
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

//objekt pre chapadielko

function chapadlo(x, y, scale) {
  this.X = x;
  this.Y = y;
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
  this.X = 450;
  this.Y = 15;
  this.width = 140;
  this.height = 50;
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

// premenná pre canvas
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

//funkcia po kliknutí myšou
function mouseClicked(e) {
  this.mouseX = e.pageX - gameArea.oX;
  this.mouseY = e.pageY - gameArea.oY;
  console.log(mouseX + " " + mouseY);
  if (typeof menuBtn_01 != "undefined" && menuBtn_01.clicked()) {
    play(1);
  }
  if (typeof menuBtn_02 != "undefined" && menuBtn_02.clicked()) {
    play(2);
  }
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
}
