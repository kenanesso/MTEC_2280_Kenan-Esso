/*
  Kenan Esso
  Short Sketch #3 - Simple Music Visual

  p5.SerialPort setup
  Music Animation Inspiration: https://dev.to/devsatasurion/creative-coding-with-p5js-an-inclusive-javascript-library-4e55

  Potentiometer controls:
  - circle size
  - music bar height
  - brightness of circle
*/

let serial; // declare serial object
let portName = '/dev/tty.usbserial-1110'; // changed to my port
let options = { baudRate: 9600 }; // matching the Arduino

let inData = 0; // incoming serial data

function setup() {
  // P5 SerialPort Setup
  serial = new p5.SerialPort();
  serial.on('list', printList);
  serial.on('connected', serverConnected);
  serial.on('open', portOpen);
  serial.on('data', serialEvent);
  serial.on('error', serialError);
  serial.on('close', portClose);

  serial.list();
  serial.open(portName, options);

  // Typical p5 setup
  createCanvas(1500, 800);
  textSize(50);
  textAlign(CENTER, CENTER);
}

function draw() {
  // gray style background
  background(100, 100, 100);

  // map incoming value to circle size
  let diameter = map(inData, 0, 255, 50, 250);

  // map incoming value to bar height
  let barHeight = map(inData, 0, 255, 20, 300);

  // draw center circle
  fill(inData, 150, 255);
  noStroke();
  circle(width / 2, height / 2 - 50, diameter);

  // draw 3 simple music bars
  fill(200, 200, 200);

  rect(width / 2 - 90, height - 200, 40, -barHeight);
  rect(width / 2 - 20, height - 200, 40, -barHeight);
  rect(width / 2 + 50, height - 200, 40, -barHeight);

  // display incoming value
  fill(0);
  text("Value: " + inData, width / 2, height - 60);
}

function printList(portList) {
  print("List of Available Serial Ports:");
  for (let i = 0; i < portList.length; i++) {
    print(i + ": " + portList[i]);
  }
}

function serverConnected() {
  print("CONNECTED TO SERVER");
}

function portOpen() {
  print("SERIAL PORT OPEN");
}

function serialEvent() {
  inData = Number(serial.read());
}

function serialError(err) {
  print("ERROR: " + err);
}

function portClose() {
  print("SERIAL PORT CLOSED");
}