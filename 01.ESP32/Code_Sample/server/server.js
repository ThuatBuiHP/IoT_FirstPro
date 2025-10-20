const express = require('express')
const server = express()
// Set up the port of the server in our lap
const port = 3000 // server(80) --> configure ESP as a server in port 80

// Parse JSon data into a JavaScript object and save it in req.body
server.use(express.json())

// When opening the url / in the browser, the server will respond with the text 'Hello World!'
server.get('/', (req, res) => {
  res.send('<div style="color:red"> Hello World! </div>')
})

// When someone posts to the url /, the server will send back a response of 1
server.post('/', (req, res) => {
  console.log("Nhận được dữ liệu là : ", req.body);
  res.json(1);
})

// URL of the server : http://192.168.1.11:3000/

// Start listening for requests on the port 3000
server.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})