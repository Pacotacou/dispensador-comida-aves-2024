const express = require('express');
const http = require('http');
const socketIO = require('socket.io');
const mqtt = require('mqtt');

class Server {
    constructor() {
        this.app = express();
        this.server = http.createServer(this.app);
        this.io = socketIO(this.server);
        this.mqttClient = mqtt.connect('mqtt://localhost'); // Replace with your MQTT broker URL

        this.init();
    }

    init() {
        this.app.use(express.static('public'));

        this.io.on('connection', (socket) => {
            console.log('A client connected');

            // Handle socket events here

            socket.on('disconnect', () => {
                console.log('A client disconnected');
            });
        });

        this.mqttClient.on('connect', () => {
            console.log('Connected to MQTT broker');

            // Subscribe to MQTT topics and handle incoming messages here
        });
    }

    start(port) {
        this.server.listen(port, () => {
            console.log(`Server started on port ${port}`);
        });
    }
}

module.exports = Server;