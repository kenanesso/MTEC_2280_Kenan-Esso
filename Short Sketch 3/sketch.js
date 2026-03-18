/*
 Kenan Esso 
  Short Sketch #4 - Sensor to control a software p5.js sketch

  (Sensor Used: Potentiometer)

Music Style Aesthetic reference from 
  https://dev.to/devsatasurion/creative-coding-with-p5js-an-inclusive-javascript-library-4e55
  */


  // Variable to store the incoming sensor value
let sensor = 0;

// These are the variables for serial connection
let port;
let reader;

async function setup() {
  // Create the canvas
  createCanvas(600, 400);

  // Make a button so user can connect to ESP32
  let button = createButton("Connect to ESP32");
  button.position(10, 10);
  button.mousePressed(connectSerial);
}

function draw() {
  // Map sensor value to brightness
  let level = map(sensor, 0, 4095, 0, 255);

  // Change background brightness with sensor
  background(level * 0.3);

  // Map sensor value to circle size
  let circleSize = map(sensor, 0, 4095, 50, 200);

  // Draw main circle
  fill(100, 200, 255);
  ellipse(width / 2, height / 2, circleSize, circleSize);

  // Map sensor value to bar height
  let barHeight = map(sensor, 0, 4095, 10, height);

  // Draw simple music-style bars
  fill(255);
  rect(100, height - barHeight, 30, barHeight);
  rect(200, height - barHeight, 30, barHeight);
  rect(300, height - barHeight, 30, barHeight);

  // Optional text showing sensor value
  fill(255);
  textSize(16);
  text("Sensor: " + sensor, 20, 60);
}

// Function to connect browser to ESP32
async function connectSerial() {
  // Ask user to choose the serial port
  port = await navigator.serial.requestPort();

  // Open the selected port at 9600 baud
  await port.open({ baudRate: 9600 });

  // Create a decoder so incoming serial data becomes readable text
  const decoder = new TextDecoderStream();
  port.readable.pipeTo(decoder.writable);

  // Create a reader to read the serial data
  reader = decoder.readable.getReader();

  // Start reading serial data
  readSerial();
}

// Function that keeps reading sensor data
async function readSerial() {
  while (true) {
    // Read one piece of incoming data
    const { value, done } = await reader.read();

    // If reading is finished, stop
    if (done) {
      reader.releaseLock();
      break;
    }

    // If data exists
    if (value) {
      // This splits incoming text by lines
      let lines = value.split("\n");

      // Get the most recent full line
      let lastLine = lines[lines.length - 2];

      // If line is valid, turn it into a number
      if (lastLine) {
        sensor = Number(lastLine.trim());
        console.log(sensor); // helps with debugging
      }
    }
  }
}