const express  = require('express');

const app      = express();
 

const path = require('path');
 

const SerialPort = require('serialport').SerialPort;

const sp = new SerialPort( {

  path:'COM3',

  baudRate: 9600
});

 

const port = 3000;

 

app.get('/increase',function(req,res)

{

	sp.write('=\n\r', function(err){

		if (err) {

            return console.log('Error on write: ', err.message);

        }

        console.log('send: led on');

		res.writeHead(200, {'Content-Type': 'text/plain'});

		res.end('LED ON\n');

	});

});

 

app.get('/decrease',function(req,res)

{

	sp.write('-\n\r', function(err){

		if (err) {

            return console.log('Error on write: ', err.message);

        }

        console.log('send: led off');

		res.writeHead(200, {'Content-Type': 'text/plain'});

		res.end('LED OFF\n');

	}); 

});

 

app.use(express.static(__dirname + '/public'));

 

app.listen(port, function() {

    console.log('listening on *:' + port);

});
