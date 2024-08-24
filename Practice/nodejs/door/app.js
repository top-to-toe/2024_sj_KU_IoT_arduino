var express  = require('express');
var app      = express();
 
var http     = require('http').Server(app);
var io       = require('socket.io')(http);
var SerialPort = require('serialport').SerialPort;

var ReadlineParser = require('@serialport/parser-readline').ReadlineParser;

var parsers    = SerialPort.parsers;

var sp = new SerialPort( {

  path:'COM3',

  baudRate: 9600
});

var tx_str = "pw"; 
var doorStatus = 0;

const parser = sp.pipe(new ReadlineParser({ delimiter: '\r\n' }));

sp.on('dooropen', () => console.log('Port open'));
parser.on('data', function (data) {
	var rcv = data.toString();

	if(rcv.substring(0,4) == 'door'){
    
		doorStatus = rcv.substring(4);
		
		io.emit('doorStatus', doorStatus);
	}
	////////////////////////////////////////////////////////
	// if (rcv.substring(0, 3) == 'led'){
  
	// 	  if(rcv.substring(3,4) == "1")	ledStatus = "on";
	// 	  else							ledStatus = "off";  
	// 	  }
	// 	  console.log('led status: ' + ledStatus);
	// 	  io.emit('led', ledStatus);
		  
	// //////////////////////////////////////////////////////// case of starting with "led"
	// if (rcv.substring(0, 3) == 'adc'){
	// 	var adc = parseInt(rcv.substring(3));
	// 	console.log('adc:',adc);
	// 	io.emit('adc', adc);
	// //////////////////////////////////////////////////////// case of starting with "adc"
	
  });

app.get('/btn0',function(req,res)

{
	tx_str = tx_str + '0';
	console.log("btn0");
});
app.get('/btn1',function(req,res)

{
	tx_str = tx_str + '1';
	console.log("btn1");
});
app.get('/btn2',function(req,res)

{
	tx_str = tx_str + '2';
	console.log("btn2");
});
app.get('/btn3',function(req,res)

{
	tx_str = tx_str + '3';
	console.log("btn3");
});
app.get('/btn4',function(req,res)

{
	tx_str = tx_str + '4';
	console.log("btn4");
});
app.get('/btn5',function(req,res)

{
	tx_str = tx_str + '5';
	console.log("btn5");
});
app.get('/btn6',function(req,res)

{
	tx_str = tx_str + '6';
	console.log("btn6");
});
app.get('/btn7',function(req,res)

{
	tx_str = tx_str + '7';
	console.log("btn7");
});
app.get('/btn8',function(req,res)

{
	tx_str = tx_str + '8';
	console.log("btn8");
});
app.get('/btn9',function(req,res)

{
	tx_str = tx_str + '9';
	console.log("btn9");
});
app.get('/reset',function(req,res)

{
	console.log("reset");
	tx_str="pw";
});
app.get('/openDoor',function(req,res)

{
	console.log("open");
	console.log(tx_str);
	tx_str=tx_str+'\n';
	sp.write(tx_str, function(err){

		if (err) {

            return console.log('Error on write: ', err.message);

        }

        console.log('pw = '+ tx_str);

		res.writeHead(200, {'Content-Type': 'text/plain'});

		res.end(tx_str);

	}); 

	
});

app.use(express.static(__dirname + '/public'));

 

const port = 3000;
http.listen(port, function () {
  console.log('Server listening on http://localhost:' + port);
});