// Create a server with express
const express = require('express')
const app = express()
var cors = require('cors')
// Set the port of the server to 3000
const port = 3000

// Parse the body of the request to JavaScript object, so server can use it
app.use(express.json());
app.use(cors());


let temp = 0;
let hum = 0;

// When opening the URL /, the server will respond with "Hello World!"
app.get('/', (req, res) => {
  res.send('Hello World!')
})

// When posting to the URL /, print the body of the request and respond with "1"
app.post('/', (req, res) => {
  // console.log("Nhan duoc du lieu",req.body);
  temp = req.body.temp;
  hum = req.body.hum;
  console.log("Temp:",temp);
  console.log("Hum:",hum);
  // Send a response to the client saying "1"
  res.json(1);
})

app.get('/data', (req, res) => {
  let mData = {mTem: temp, mHum: hum};
  res.json(mData);
})

// Server starts listening on port 3000, then prints "Example app listening on port 3000"
app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})