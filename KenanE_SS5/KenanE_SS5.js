/*
  Kenan Esso
  Assignment 5 - LED Beat Visualizer

  Controls:
  UP ARROW = faster beat
  DOWN ARROW = slower beat
*/

let serial;
let portName = '/dev/tty.usbserial-1110'; // change if needed

let beatSpeed = 800; // start slow
let lastSentSpeed = -1; // remembers last value sent to Arduino

function setup() {
  createCanvas(1000, 650);
  textAlign(CENTER, CENTER);
  textSize(24);

  serial = new p5.SerialPort();
  serial.open(portName, { baudRate: 9600 });
}

function draw() {
  drawVisualizer();
}

function drawVisualizer() {
  let speed = map(beatSpeed, 100, 1000, 0.2, 0.02);

  if (beatSpeed <= 300) {
    background(200, 60, 60);   // fast = red
  } else if (beatSpeed <= 700) {
    background(80, 80, 220);   // medium = blue
  } else {
    background(60, 160, 100);  // slow = green
  }

  noStroke();

  // circle
  let circleSize = map(sin(frameCount * speed), -1, 1, 120, 240);
  fill(180, 220, 255);
  circle(width / 2, height / 2 - 80, circleSize);

  // bars
  let bar1 = map(sin(frameCount * speed), -1, 1, 60, 220);
  let bar2 = map(sin(frameCount * speed + 1), -1, 1, 80, 260);
  let bar3 = map(sin(frameCount * speed + 2), -1, 1, 50, 200);

  fill(255);
  rect(width / 2 - 120, height - 130, 50, -bar1);
  rect(width / 2 - 25, height - 130, 50, -bar2);
  rect(width / 2 + 70, height - 130, 50, -bar3);

  // side lights
  let lightSize = map(sin(frameCount * speed), -1, 1, 40, 90);
  fill(255, 255, 120);
  ellipse(180, 140, lightSize, lightSize);
  ellipse(width - 180, 140, lightSize, lightSize);

  // floor
  fill(40);
  rect(0, height - 100, width, 100);

  // text
  fill(255);
  text("LED Beat Visualizer", width / 2, 40);
  text("UP ARROW = Faster Beat", width / 2, 80);
  text("DOWN ARROW = Slower Beat", width / 2, 120);
  text("Current Beat Speed: " + beatSpeed, width / 2, 170);
}

function keyPressed() {
  if (keyCode === UP_ARROW) {
    beatSpeed -= 100;
  }

  if (keyCode === DOWN_ARROW) {
    beatSpeed += 100;
  }

  beatSpeed = constrain(beatSpeed, 100, 1000);

  // send ONLY when the value changes
  sendSpeedToArduino();
}

function sendSpeedToArduino() {
  if (serial && serial.isOpen() && beatSpeed !== lastSentSpeed) {
    serial.write(beatSpeed + "\n");
    lastSentSpeed = beatSpeed;
    console.log("Sent to Arduino:", beatSpeed);
  }
}