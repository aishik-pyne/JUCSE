const express = require('express')
const config = require('config')
const colors = require('colors')
const moment = require('moment')
const mongoose = require('mongoose')
const bodyParser = require('body-parser')
const apiRouter = require('./api')
const app = express()
// Start server
app.use(bodyParser.json())
app.use('/', express.static('public'))
app.use('/api', apiRouter)

mongoose.connect(`mongodb://${config.mongo.host}:${config.mongo.port}/${config.mongo.db}`)
const db = mongoose.connection
db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', function callback () {
  console.log("Connected to mongodb");
});
const server = app.listen(config.server.port, config.server.host, () => {
  console.log(`Server started at http://${config.server.host}:${config.server.port}/`);

})
