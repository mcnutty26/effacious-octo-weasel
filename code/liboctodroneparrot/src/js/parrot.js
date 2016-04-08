/*
This file is part of octoDrone.

octoDrone is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

octoDrone is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with octoDrone.  If not, see <http://www.gnu.org/licenses/>.
*/

var net = require('net');
var fs = require('fs');
var socketPath = './parrot.sock';

var arDrone = require('ar-drone');
var client  = arDrone.createClient();

process.on('uncaughtException', function (er) {
	console.log('error@nodeServer: unhandled exception');
	console.log(er.stack);
	process.exit(1);
});

fs.stat(socketPath, function(err) {
	if (!err) fs.unlinkSync(socketPath);
	var unixServer = net.createServer(function(localSerialConnection) {
		localSerialConnection.on('data', function(data) {
			command = data.toString().split(";");
			console.log("message@nodeServer: (" + command[0] + ", " + command[1] + ")");
			execute(command[0], parseFloat(command[1]));
		});
	});
	unixServer.listen(socketPath);
});

console.log("init@nodeServer: listening on socket " + socketPath);

function execute(command, speed) {
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
				console.log('error@nodeServer: command not recognised');
		}
};

