var restify = require('restify');

// Model
var score = {}

// REST API
var server = restify.createServer({
  name: 'HighScore!',
});

// Get score
server.get('/score', function (req, res, next) {
  console.log("GET SCORE")
  res.send(score)
});

// Update player score
server.put('/score/:name/:num', function (req, res, next) {
  var player = req.params.name
  var num = req.params.num
  console.log("PUT: "+player+" NUM: "+num)
  if (score[player]) {
    score[player] = num
    res.send(score)
  } else {
    res.send({"Error": "Player "+player+" does not exist"})
  }
});

// Add player score
server.post('/score/:name/:num', function (req, res, next) {
  var player = req.params.name
  var num = req.params.num
  console.log("POST: "+player+" NUM: "+num)
  if (!score[player]) {
    score[player] = num
    res.send(score)
  } else {
    res.send({"Error": "Player "+player+" already exists"})
  }
});

// Get score for player
server.get('/score/:name', function (req, res, next) {
  var player = req.params.name
  console.log("GET: "+player)
  if (score[player]) {
    res.send(score[player])
  } else {
    res.send({Error: "Player "+player+" does not exist"})
  }
});

// Delete player score
server.del('/score/:name', function (req, res, next) {
  var player = req.params.name
  console.log("DEL: "+player)
  if (score[player]) {
    delete score[player]
    res.send(true)
  } else {
    res.send({Error: "Player "+player+" does not exist"})
  }
});

// Enable Cross-Origin Resource Sharing
server.use(restify.CORS());

// Start server
server.listen(8080);
