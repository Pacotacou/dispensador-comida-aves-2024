const mqtt = require('mqtt');
const express = require('express');

const app = express();
const http = require('http').Server(app);
const io = require('socket.io')(http);

// Conecta al broker MQTT
const client = mqtt.connect('mqtt://broker.hivemq.com');

client.on('connect', () => {
  console.log('Conectado al broker MQTT');
  client.subscribe('nodemcu/test');
});

client.on('message', (topic, message) => {
  console.log(message.toString());
  io.emit('mqtt_message', message.toString());
});

app.get('/', (req, res) => {
  
  res.sendFile(__dirname + '/Client/index.html');
});

http.listen(3000, () => {
  console.log('Servidor escuchando en el puerto 3000');
});

io.on('connection', (socket) => {
  console.log('Un usuario se ha conectado');
  io.to(socket.id).emit('ping');
});







