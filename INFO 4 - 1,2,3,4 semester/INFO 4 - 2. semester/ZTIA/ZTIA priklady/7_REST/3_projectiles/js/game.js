class Game extends GameObject {
	constructor(canvas) {
		// Init game object
		super(undefined, 0, 0, canvas.width, canvas.height)

		this.canvas = canvas
		this.ctx = canvas.getContext("2d")

		// Model
		this.keys = []
		this.time = Date.now()

		// Event handlers
		var game = this
		window.addEventListener("keydown", function(event) {
			game.keys[event.keyCode] = true
		})

		window.addEventListener("keyup", function(event) {
			game.keys[event.keyCode] = false
		})

		// Loop callback
		this.loop = function() {
			game.onloop()
		}

		// Load level1
		this.level1()
	}

	onloop() {
		// Get time delta
		var now = Date.now()
		var dt = (now - this.time) / 100
		this.time = now

		// Animate
		this.move(dt)

		// Draw
		this.draw(this.ctx)

		// Loop animation
		requestAnimationFrame(this.loop)
	}

	level1() {
		this.nodes = []
		this.add(new Background(this))
		this.add(new Player(this, 0, 120))
	}
}

// Init
window.onload = function() {
	var game = new Game(document.getElementById("canvas"))
	game.loop()
}
