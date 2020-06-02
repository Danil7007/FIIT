// objekt skore -------------------------------------------------------------------------------------------------

function skore() {
    // s cim robi
    this.myScore = 0;
    this.values = [{ date: null, score: null, gameMode: null }];
    // ziskanie skore
    this.getScore = function () {
      // JSON na pracu s formatmi dat pre ukladanie do tabulky
      if (myStorage.getItem("score") != null) {
        this.values = JSON.parse(myStorage.getItem("score"));
      }
    };
    // ulopzenie
    this.storeScore = function () {
      let date = new Date();
      this.values.push({
        date: date.getDate() + "/" + date.getMonth() + "/" + date.getFullYear(),
        score: this.myScore,
        gameMode: gameArea.mode,
      });
  
      // sortovanie - volanie
      this.sortScore();
    };
  
    this.updateScore = function () {
      this.storeScore();
      this.saveScore();
    };
  
    // vytvorenie sortovania
    this.sortScore = function () {
      if (values.length > 10) values.splice(0, 1);
      values.sort((a, b) => (a.score < b.score ? 1 : -1));
    };
  
    // ulozenie skore trvale
    this.saveScore = function () {
      myStorage.setItem("score", JSON.stringify(values));
    };
  }