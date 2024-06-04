
  
  <!DOCTYPE html>
  <html lang="en">
	<head>
	  <meta charset="UTF-8" />
	  <meta name="viewport" content="width=device-width, initial-scale=1.0" />
	  <title>Need For Pace</title>
	  <script
		src="https://cdnjs.cloudflare.com/ajax/libs/paho-mqtt/1.0.2/mqttws31.min.js"
	  >
		//Buttons
	  </script>
	</head>
	<body>
	  <button id="connectButton" class="btn btn-lg variant-filled"
		>Connect to MQTT</button
	  >
	  <button id="sendMessageButton" class="btn btn-lg variant-filled"
		>Send Message</button
	  >
	  <button id="driveForward" class="btn btn-lg variant-filled">Forward</button>
	  <button id="driveBackwards" class="btn btn-lg variant-filled"
		>Backwards</button
	  >
	  <button id="stopTheCar" class="btn btn-lg variant-filled">Stop</button>
	  <button id="turnServoRight" class="btn btn-lg variant-filled"
		>Turn Right</button
	  >
	  <button id="turnServoLeft" class="btn btn-lg variant-filled"
		>Turn Left</button
	  >
	  <button id="drivestraight" class="btn btn-lg variant-filled"
		>Drive Straight</button
	  >
	  <style>
		body {
		  font-family: Arial, sans-serif;
		  background-color: #f4f4f4;
		  display: flex;
		  flex-direction: column;
		  align-items: center;
		  justify-content: center;
		  height: 100vh;
		  margin: 0;
		}
  
		.btn {
		  display: inline-block;
		  padding: 15px 25px;
		  margin: 10px;
		  font-size: 16px;
		  font-weight: bold;
		  color: #fff;
		  background-color: #007bff;
		  border: none;
		  border-radius: 5px;
		  text-align: center;
		  text-decoration: none;
		  transition: background-color 0.3s ease;
		  cursor: pointer;
		}
  
		.btn:hover {
		  background-color: #0056b3;
		}
  
		.btn:active {
		  background-color: #00408a;
		}
  
		.btn:focus {
		  outline: none;
		  box-shadow: 0 0 5px rgba(0, 123, 255, 0.5);
		}
  
		.btn-lg {
		  padding: 20px 30px;
		  font-size: 18px;
		}
  
		.variant-filled {
		  background-color: #28a745;
		}
  
		.variant-filled:hover {
		  background-color: #218838;
		}
  
		.variant-filled:active {
		  background-color: #1e7e34;
		}
  
		.variant-filled:focus {
		  box-shadow: 0 0 5px rgba(40, 167, 69, 0.5);
		}
	  </style>
  
	  <script>
		//Decides what buttons do
		// MQTT broker connection options
		const brokerUrl = "maqiatto.com";
		const port = 8883; // MQTT over WebSockets port
		const clientId = "clientId_" + Math.random().toString(16).substr(2, 8); // Generate a random client ID
		const username = "antonsundstrom007@gmail.com"; // Your Maqiatto username
		const password = "GreenBean"; // Your Maqiatto password
  
		// MQTT client instance
		let client = null;
  
		// Function to connect to the MQTT broker
		function connectToBroker() {
		  // Initialize MQTT client
		  client = new Paho.MQTT.Client(brokerUrl, port, clientId);
  
		  // Set callback handlers
		  client.onConnectionLost = onConnectionLost;
		  client.onMessageArrived = onMessageArrived;
  
		  // Connect to MQTT broker
		  client.connect({
			onSuccess: onConnect,
			userName: username,
			password: password,
			useSSL: false, // Maqiatto does not support SSL
		  });
		}
  
		// Called when the client connects
		function onConnect() {
		  console.log("Connected to MQTT broker.");
		}
  
		// Called when the client loses its connection
		function onConnectionLost(responseObject) {
		  if (responseObject.errorCode !== 0) {
			console.error("Connection lost:", responseObject.errorMessage);
		  }
		}
  
		// Called when a message arrives
		function onMessageArrived(message) {
		  console.log("Message received:", message.payloadString);
		}
  
		// Function to send a message to the broker
		function sendMessage(topic, message) {
		  if (client && client.isConnected()) {
			const messageObject = new Paho.MQTT.Message(message);
			messageObject.destinationName = topic;
			client.send(messageObject);
			console.log("Message sent:", message);
		  } else {
			console.error("Not connected to MQTT broker.");
		  }
		}
		//When a button is pressed these functions decides what shall happen
		document.addEventListener("keydown", function (event) {
		  // Check if the pressed key is 'c'
		  if (event.key === "c") {
			// Trigger click event of the connect button
			document.getElementById("connectButton").click();
		  }
		});
  
		document.addEventListener("keydown", function (event) {
		  // Check if the pressed key is 's'
		  if (event.key === "m") {
			// Trigger click event of the connect button
			document.getElementById("sendMessageButton").click();
		  }
		});
		document.addEventListener("keydown", function (event) {
		  // Check if the pressed key is 's'
		  if (event.key === "w") {
			// Trigger click event of the connect button
			document.getElementById("driveForward").click();
		  }
		});
		document.addEventListener("keydown", function (event) {
		  // Check if the pressed key is 's'
		  if (event.key === "s") {
			// Trigger click event of the connect button
			document.getElementById("driveBackwards").click();
		  }
		});
		document.addEventListener("keydown", function (event) {
		  // Check if the pressed key is 's'
		  if (event.key === "p") {
			// Trigger click event of the connect button
			document.getElementById("stopTheCar").click();
		  }
		});
		document.addEventListener("keydown", function (event) {
		  // Check if the pressed key is 's'
		  if (event.key === "d") {
			// Trigger click event of the connect button
			document.getElementById("turnServoRight").click();
		  }
		});
		document.addEventListener("keydown", function (event) {
		  // Check if the pressed key is 's'
		  if (event.key === "a") {
			// Trigger click event of the connect button
			document.getElementById("turnServoLeft").click();
		  }
		});
		document.addEventListener("keydown", function (event) {
		  // Check if the pressed key is 's'
		  if (event.key === " ") {
			// Trigger click event of the connect button
			document.getElementById("drivestraight").click();
		  }
		});
  
		// Event listener for button click to connect
		document.getElementById("connectButton").addEventListener("click", () => {
		  if (!client || !client.isConnected()) {
			connectToBroker();
		  } else {
			console.log("Already connected to MQTT broker.");
		  }
		});
  
		// Event listener for button click to send message
		document
		  .getElementById("sendMessageButton")
		  .addEventListener("click", () => {
			const topic = "antonsundstrom007@gmail.com/Motor"; // Change to your desired topic
			const message = "FOrwaerwroaueiouwieuiawueouwa"; // Change to your desired message
			sendMessage(topic, message);
		  });
		// Event listener for button click to send message
		document.getElementById("driveForward").addEventListener("click", () => {
		  const topic = "antonsundstrom007@gmail.com/Motor"; // Change to your desired topic
		  const message = "Driving..."; // Change to your desired message
		  sendMessage(topic, message);
		});
		// Event listener for button click to send message
		document
		  .getElementById("driveBackwards")
		  .addEventListener("click", () => {
			const topic = "antonsundstrom007@gmail.com/Motor"; // Change to your desired topic
			const message = "Driving Backwards"; // Change to your desired message
			sendMessage(topic, message);
		  }); // Event listener for button click to send message
		document.getElementById("stopTheCar").addEventListener("click", () => {
		  const topic = "antonsundstrom007@gmail.com/Motor"; // Change to your desired topic
		  const message = "Stoping"; // Change to your desired message
		  sendMessage(topic, message);
		}); // Event listener for button click to send message
		document
		  .getElementById("turnServoRight")
		  .addEventListener("click", () => {
			const topic = "antonsundstrom007@gmail.com/Motor"; // Change to your desired topic
			const message = "Turning Right"; // Change to your desired message
			sendMessage(topic, message);
		  }); // Event listener for button click to send message
		document.getElementById("turnServoLeft").addEventListener("click", () => {
		  const topic = "antonsundstrom007@gmail.com/Motor"; // Change to your desired topic
		  const message = "Turning left"; // Change to your desired message
		  sendMessage(topic, message);
		});
		document.getElementById("drivestraight").addEventListener("click", () => {
		  const topic = "antonsundstrom007@gmail.com/Motor"; // Change to your desired topic
		  const message = "Driving Straight"; // Change to your desired message
		  sendMessage(topic, message);
		});
	  </script>
	</body>
  </html>