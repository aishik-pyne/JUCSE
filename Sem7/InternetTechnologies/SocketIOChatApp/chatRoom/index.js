const colors = require('colors');
let users = {}
let logs = []
module.exports = {
  logs,
  users,
  addUser({ id, name }) {
    users[id] = { id, name }
    console.log(colors.cyan(`User connected ${id}: ${name}`));
  },
  removeUser({ id }) {
    if (id in users) {
      const name = users[id]['name']
      delete users[id]
      console.log(colors.red(`User disconnected ${id}: ${name}`));
    }
  },
  newMessage({ id, text, timestamp }) {
    if (id in users) {
      
      logs.push({
        name: users[id].name,
        text,
        timestamp
      })
      console.log(colors.magenta(`New Message from  ${users[id].name}`));
      return {
        name: users[id].name,
        text,
        timestamp
      }
    }
  }
}