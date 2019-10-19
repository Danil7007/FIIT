Simple REST server for game score.

Score is stored while the server is running in "score" global object. Each player name is stored as key and value pair in "score".

The REST API is as follows:
GET /score - Get the whole score object
GET /score/:name - Get score for player :name
POST /score/:name/:num - Store player score
PUT /score/:name/:num - Update player score
DELETE /score/:name - Delete player score

Installation:
- Install node.js
- npm install restify

Run:
- node server.js
