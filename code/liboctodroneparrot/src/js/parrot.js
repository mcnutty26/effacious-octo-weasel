

var net = require('net');
var fs = require('fs');
var socketPath = './parrot.sock';

var arDrone = require('ar-drone');
var client  = arDrone.createClient();

process.on('uncaughtException', function (er) {
	console.log('Error - unhandled exception');
	console.log(er.stack);
	process.exit(1);
});

fs.stat(socketPath, function(err) {
	if (!err) fs.unlinkSync(socketPath);
	var unixServer = net.createServer(function(localSerialConnection) {
		localSerialConnection.on('data', function(data) {
			console.log("Received data on socket connection");
			command = data.toString().split(";");
			execute(command[0], command[1]);
		});
	});
	unixServer.listen(socketPath);
});

console.log("octoDrone node server started and listening on socket " + socketPath);

function execute(command, speed) {
	console.log("Running (" + command + ", " + speed + ")");
	switch(command.toLowerCase()) {
			case "up":
				client.up(speed);
				break;
			case "down":
				client.down(speed);
				break;
			case "left":
				client.left(speed);
				break;
			case "right":
				client.right(speed);
				break;
			case "front":
				client.front(speed);
				break;
			case "back":
				client.back(speed);
				break;
			case "takeoff":
				client.takeoff();
				break;
			case "land":
				client.land();
				break;
			case "clockwise":
				client.clockwise(speed);
				break;
			case "counterClockwise":
				client.counterClockwise(speed);
				break;
			case "stop":
				client.stop();
				break;
			default:
				console.log('Error - command not recognised');
		}
};

