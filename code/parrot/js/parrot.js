var net = require('net');
var fs = require('fs');
var socketPath = './parrot.sock';

var arDrone = require('ar-drone');
var client  = arDrone.createClient();

fs.stat(socketPath, function(err) {
	if (!err) fs.unlinkSync(socketPath);
	var unixServer = net.createServer(function(localSerialConnection) {
		localSerialConnection.on('data', function(data) {
			console.log(data);
			//TODO some processing to split <command>:<value> into two components
			//TODO call the execute function with these components
		});
	});
	unixServer.listen(socketPath);
});

function execute(command, speed) {
	switch(command) {
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

