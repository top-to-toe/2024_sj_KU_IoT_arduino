const express = require('express');
const app = express();
app.use(express.static(__dirname + '/public'));
app.use(express.urlencoded({extended:true}));
// app.use(express.jason());

app.post('/send_text', function(req, res){
	console.log(req.body.name_);
	console.log(req.body.id_);
	console.log(req.body.pw_);
});

const port = 3000;

app.listen(port, function(){
    console.log('listening on *:' + port);
});