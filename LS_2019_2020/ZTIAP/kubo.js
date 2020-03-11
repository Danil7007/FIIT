//získanie elementu "canvas"
var canvas = document.querySelector('canvas');
var obsah = canvas.getContext('2d');
//funkcia na zmenu šírky a výsky elementu canvas
function setCanvasDimensions(){
    
    setTimeout(setCanvasDimensions,100);
}
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;
//zavolanie funkcie na zmenu -//-
function draw(){
    //hlava
    obsah.beginPath();
    obsah.strokeStyle = "limegreen";
    obsah.arc(200, 50, 30, 0, Math.PI * 2, true);
    obsah.lineWidth = 3;
    obsah.stroke();
    //oči
    obsah.beginPath();
    obsah.fillStyle = "blue";
    obsah.arc(190, 45, 3, 0, Math.PI * 2, true);
    obsah.fill();
    obsah.arc(210, 45, 3, 0, Math.PI * 2, true);
    obsah.fill();
    //usmev
    obsah.beginPath();
    obsah.strokeStyle = "magenta";
    obsah.lineWidth = 5;
    obsah.arc(200, 50, 20, 0, Math.PI /2, false);
    obsah.stroke();
    //telo
    obsah.beginPath();
    obsah.moveTo(200, 80);
    obsah.lineTo(200, 180);
    obsah.strokeStyle = "limegreen";
    obsah.stroke();
    //ruke
    obsah.beginPath();
    obsah.strokeStyle = "limegreen";
    obsah.moveTo(200, 80);
    obsah.lineTo(150, 130);
    obsah.moveTo(200, 80);
    obsah.lineTo(250, 130);
    obsah.stroke();
    //nohe
    obsah.beginPath();
    obsah.strokeStyle = "limegreen";
    obsah.moveTo(200, 180);
    obsah.lineTo(150, 280);
    obsah.moveTo(200, 180);
    obsah.lineTo(250, 280);
    obsah.stroke();
    
}
draw();
function setScore(score){
    var storage = window.localStorage;
    storage.setItem('score',score);
    window.alert("Skore ulozene");
}
function getScore(){
    var storage = window.localStorage;
    score = storage.getItem('score');
    window.alert(score);
    obsah.fillText(score, 250, 500);
}
console.log(canvas);
console.log(obsah);