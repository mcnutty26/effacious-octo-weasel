var arDrone = require('ar-drone');
var client  = arDrone.createClient();

/*process.argv.forEach(function (val, index, array) {
	if (index==3) {
		speed = val;
	}
});*/ 

var myArgs = process.argv.slice(2)

speed = myArgs[1]

console.log(myArgs);

switch(myArgs[0]) {
	case "up":
        client.up(speed)
        break;
    case "down":
        client.down(speed)
        break;
	case "left":
        client.left(speed)
        break;
	case "right":
        client.right(speed)
        break;
	case "front":
        client.front(speed)
        break;
	case "back":
        client.back(speed)
        break;
	case "takeoff":
		console.log("DUBUG");
        client.takeoff();
        break;
	case "land":
        client.land(speed)
        break;
	case "clockwise":
        client.clockwise(speed)
        break;
	case "counterClockwise":
        client.counterClockwise(speed)
        break;
	case "stop":
        client.stop()
        break;
    default:
        console.log('Error - command not recognised');
}

/*process.argv.forEach(function (val, index, array) {
  console.log(index + ': ' + val);
});
*/

//process.exit()
