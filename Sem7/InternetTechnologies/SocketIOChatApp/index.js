const express = require('express')
const config = require('config')
const colors = require('colors')
const moment = require('moment')
const app = express()
// Start server
app.use('/', express.static('public'))
const server = app.listen(config.server.port, config.server.host, () => {
  console.log(`Server started at http://${config.server.host}:${config.server.port}/`);

})

// Handle sockets
const io = require('socket.io')(server)
const chatRoom = require('./chatRoom')
let onlineUsers = 0
io.on('connection', (socket) => {
  onlineUsers += 1
  socket.on('disconnect', () => {
    onlineUsers -= 1;
    const user = chatRoom.removeUser({
      id: socket.id
    })
    socket.broadcast.emit('UserLeft', user);

  })

  // ChatRoomEvents
  socket.on('NewUser', (data) => {
    const user = chatRoom.addUser({
      id: socket.id,
      name: data.name
    })
    socket.broadcast.emit('UserJoined', user);
  })
  socket.on('DelUser', () => {
    const user = chatRoom.removeUser({
      id: socket.id
    })
    socket.broadcast.emit('UserLeft', user);
  })
  socket.on('NewMessage', (data) => {
    const message = chatRoom.newMessage({
      id: socket.id,
      text: data.text,
      timestamp: moment().format('h:mm:ss')
    })
    io.emit('NewMessage', message);
  })
  socket.on('Sync', (cb) => {
    cb(chatRoom.logs)
    // socket.emit('Sync', chatRoom.logs);
  })

})