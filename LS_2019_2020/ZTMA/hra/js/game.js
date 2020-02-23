function startGame() {
    myGameArea.start();
}

var myGameArea = {
        start : function() {
            this.context = document.getElementById("myCanvas").getContext("2D");
        }
}

