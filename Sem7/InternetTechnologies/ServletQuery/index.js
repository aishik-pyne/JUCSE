const express = require('express');
const bodyParser = require('body-parser');
const port = 9001;
const KeyValuePairController = require('./controllers/keyValuePair.controller')


const app = express();
app.use(bodyParser.json());
app.set('view engine', 'ejs');
app.route("/")
    .get(KeyValuePairController.fetch)
    .post(KeyValuePairController.create)

app.route("/list")
    .get(KeyValuePairController.list)


app.listen(port, ()=>{
    console.log("server on port "+port);
    
});