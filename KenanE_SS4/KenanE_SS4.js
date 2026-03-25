/*
Kenan Esso
Assignment 4 – Simple Serial Visual

Sensors:
Pot1 → circle size
Pot2 → music bar height
Button1 → shape color mode
Button2 → background color
*/

// serial setup
let serial;
let portName = '/dev/tty.usbserial-1110';

// sensor variables
let pot1 = 0;
let pot2 = 0;
let button1 = 1;
let button2 = 1;

function setup() {

  // create canvas (within assignment limits)
  createCanvas(1000, 650);

  textAlign(CENTER);
  textSize(20);

  // start serial
  serial = new p5.SerialPort();
  serial.open(portName, { baudRate: 9600 });

  // when data arrives run serialEvent()
  serial.on('data', serialEvent);
}

function draw() {

  // map sensor values to visual ranges
  let circleSize = map(pot1, 0, 1023, 50, 250);
  let barHeight = map(pot2, 0, 1023, 40, 300);

  // background toggle using button2
  if (button2 == 0) {
    background(80,120,255);   // blue
  } else {
    background(120);          // gray
  }

  // shape color toggle using button1
  if (button1 == 0) {
    fill(255,120,150);
  } else {
    fill(100,220,255);
  }

  noStroke();

  // primitive 1: circle
  circle(width/2, height/2 - 80, circleSize);

  // primitive 2: rectangles (music bars)
  fill(220);
  rect(width/2 -120, height-150, 50, -barHeight);
  rect(width/2 -25, height-150, 50, -barHeight*0.7);
  rect(width/2 +70, height-150, 50, -barHeight*1.2);

  // primitive 3: ellipse lights
  fill(255,255,120);
  ellipse(180,120,60,60);
  ellipse(width-180,120,60,60);

  // display sensor values
  fill(0);
  text("Pot1: " + pot1, width/2, height-80);
  text("Pot2: " + pot2, width/2, height-50);
}

// this function runs whenever new serial data arrives
function serialEvent() {

  let data = serial.readLine();
  data = trim(data);

  if(!data) return;

  // split incoming values
  let values = data.split(",");

  // convert to numbers
  if(values.length == 4){
    pot1 = int(values[0]);
    pot2 = int(values[1]);
    button1 = int(values[2]);
    button2 = int(values[3]);
  }
}