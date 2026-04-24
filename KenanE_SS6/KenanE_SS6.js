/*
  Kenan Esso
  Assignment 6 - Serial Handshaking (Call & Response)

  This sketch:
  1. Sends a request to Arduino
  2. Sends the current mode to Arduino
  3. Receives 2 sensor values back
  4. Uses those values to animate the screen

  Controls:
  Press 0 = Calm Mode
  Press 1 = Active Mode
*/

let serial;
let portName = '/dev/tty.usbserial-1110';

let serialReady = false;

let pot1 = 0;
let pot2 = 0;

let mode = 0; // 0 = calm, 1 = active mode

function setup() {
  createCanvas(1000, 650);
  textAlign(CENTER, CENTER);
  textSize(22);

  serial = new p5.SerialPort();

  serial.on('open', portOpen);
  serial.on('data', serialEvent);
  serial.on('error', serialError);

  serial.open(portName, { baudRate: 9600 });
}

function draw() {
  drawVisualizer();

  // ask Arduino for new data every frame
  sendRequest();
}

function drawVisualizer() {
  // map sensor values to visual changes
  let circleSize = map(pot1, 0, 1023, 80, 260);
  let barHeight = map(pot2, 0, 1023, 60, 280);
  let lightSize = map(pot1, 0, 1023, 40, 100);

  // different background by mode
  if (mode === 0) {
    background(50, 90, 200); // calm = blue
  } else {
    background(200, 70, 70); // active = red
  }

  noStroke();

  // primitive 1: circle
  fill(180, 220, 255);
  circle(width / 2, height / 2 - 90, circleSize);

  // primitive 2: rectangles
  fill(255);
  rect(width / 2 - 120, height - 130, 50, -barHeight);
  rect(width / 2 - 25, height - 130, 50, -(barHeight * 0.7));
  rect(width / 2 + 70, height - 130, 50, -(barHeight * 1.1));

  // primitive 3: ellipses
  fill(255, 255, 120);
  ellipse(180, 140, lightSize, lightSize);
  ellipse(width - 180, 140, lightSize, lightSize);

  // stage floor
  fill(40);
  rect(0, height - 100, width, 100);

  // text
  fill(255);
  text("Serial Handshaking Visualizer", width / 2, 40);
  text("Press 0 = Calm Mode      Press 1 = Active Mode", width / 2, 80);
  text("Pot1: " + pot1, width / 2, 115);
  text("Pot2: " + pot2, width / 2, 145);

  if (mode === 0) {
    text("Mode: Calm", width / 2, 180);
  } else {
    text("Mode: Active", width / 2, 180);
  }
}

function keyPressed() {
  if (key === '0') {
    mode = 0;
  }

  if (key === '1') {
    mode = 1;
  }
}

function sendRequest() {
  // p5 asks Arduino for data and also sends current mode
  if (serialReady) {
    let message = "R," + mode + "\n";
    serial.write(message);
  }
}

function serialEvent() {
  let data = serial.readLine();
  data = trim(data);

  if (!data) return;

  let values = data.split(",");

  if (values.length === 2) {
    pot1 = int(values[0]);
    pot2 = int(values[1]);
  }
}

function portOpen() {
  serialReady = true;
  console.log("Serial connected");
}

function serialError(err) {
  console.log("Serial error:", err);
}