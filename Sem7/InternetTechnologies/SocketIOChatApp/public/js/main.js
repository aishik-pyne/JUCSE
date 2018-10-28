
var app = new Vue({
  el: '#app',
  data() {
    return {
      name: "aishik",
      inputBox: "",
      socket: io(),
      chats: []
    }
  },
  methods: {
    sendText() {
      if (this.inputBox === "") {
        console.log(`Input Box is empty`)
      } else {
        console.log(`Trying to send text ${this.inputBox}`)
        this.socket.emit('NewMessage', {
          text: this.inputBox
        })
        this.inputBox = ""
      };
    },
    sync() {
      this.socket.emit('Sync', (response) => {
        this.chats = response
      });
    }
  },
  created() {
    this.socket.on('NewMessage', () => {
      this.sync()
    })
    this.name = prompt("What's your name?")
  },
  mounted() {
    this.socket.emit('NewUser', { name: this.name })
    this.sync()
    // socket.on('connect', function () {
    //   socket.emit('NewUser', { name: 'aishik' });
    //   socket.on('disconnected', function () {
    //     socket.emit('DelUser');
    //   });

    // });
  },

})