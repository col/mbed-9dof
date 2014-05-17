import shapes3d.*;
import shapes3d.utils.*;
import shapes3d.animation.*;
import processing.serial.*; 

Serial serial;
Box box;

byte[] newKalmanXBytes = new byte[0];
byte[] newKalmanYBytes = new byte[0];

float newKalmanX = 90.0;
float newKalmanY = 90.0;

public void setup() {
  size(400, 400, P3D);  
  createBox();
  setupSerial();
}

void setupSerial()
{
  // DEBUG - Print the connected serial devices
  println(Serial.list()); 
  println(Serial.list()[5]);
  
  // Baud Rates: 9600 - 57600 - 115200 
  serial = new Serial(this, Serial.list()[5], 9600);  
  serial.bufferUntil('\n'); // Buffer until line feed
}  

void createBox()
{
  box = new Box(this);
  String[] faces = new String[] {
    "front.png", "back.png", "right.png", 
    "left.png", "bottom.png", "top.png"
  };
  box.setTextures(faces);
  box.fill(color(255));
  box.stroke(color(190));
  box.strokeWeight(1.2f);
  box.setSize(100, 50, 150);
  box.drawMode(S3D.TEXTURE | S3D.WIRE);
}

public void draw() {
  background(20);
  
  pushMatrix();  
  camera(0, 0, 300, 0, 0, 0, 0, 1, 0);  
  rotateX((newKalmanX - 90) * -0.0174532925);
  rotateZ((newKalmanY - 90) * 0.0174532925); 
  box.draw();  
  popMatrix();  
}

void serialEvent (Serial serial) {
  try
  { 
    newKalmanX = readFloatUntil(serial, '\t');
    newKalmanY = readFloatUntil(serial, '\t');    
    serial.readBytesUntil('\n');   
    serial.clear();    
  } catch(Exception e) {
    println( e ); 
  }
}

public String readStringUntil(Serial serial, int inByte) {
  byte temp[] = serial.readBytesUntil(inByte);
  if (temp == null) {
    return null;
  } else {
    return new String(temp);
  }
}

public float readFloatUntil(Serial serial, int inByte) {
  byte temp[] = serial.readBytesUntil(inByte);
  if (temp == null || temp.length < 5) {
    return 0.0;
  } else {
    float value = get4bytesFloat(temp, 0);    
    return value;
  }
}

float get4bytesFloat(byte[] data, int offset) { 
  String hexint = hex(data[offset+3])+hex(data[offset+2])+hex(data[offset+1])+hex(data[offset]); 
  return Float.intBitsToFloat(unhex(hexint)); 
}
