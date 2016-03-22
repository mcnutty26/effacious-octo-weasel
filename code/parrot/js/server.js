var net = require('net');
var fs = require('fs');
var socketPath = './parrotsock';

fs.stat(socketPath, function(err) {
    if (!err) fs.unlinkSync(socketPath);
    var unixServer = net.createServer(function(localSerialConnection) {
        localSerialConnection.on('data', function(data) {
            // data is a buffer from the socket
        });
        // write to socket with localSerialConnection.write()
    });

unixServer.listen(socketPath);
});
