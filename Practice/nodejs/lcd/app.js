const express = require('express');
const app = express();

const path = require('path');
 

const SerialPort = require('serialport').SerialPort;

const sp = new SerialPort( {

  path:'COM3',

  baudRate: 9600
});
app.use(express.static(__dirname + '/public'));
app.use(express.urlencoded({extended:true}));
// app.use(express.jason());

var send_text = "";

app.post('/send_text', function(req, res){
	send_text = "lcd" + req.body.snd_txt + "\n";
	console.log(send_text);
	

	sp.write(send_text, function(err){

		if (err) {

            return console.log('Error on write: ', err.message);

        }

		res.writeHead(200, {'Content-Type': 'text/plain'});

		res.end('LED ON\n');

	});
	
});

const port = 3000;

app.listen(port, function(){
    console.log('listening on *:' + port);
});