import processing.serial.*; 
Serial arduino; 

float newGyroX;
float newGyroY;

float newAccX;
float newAccY;

float newKalmanX;
float newKalmanY;

float[] gyroX = new float[600];
float[] gyroY = new float[600];

float[] accX = new float[600];
float[] accY = new float[600];

float[] kalmanX = new float[600];
float[] kalmanY = new float[600];

void setup() {  
  size(600, 400);
  println(arduino.list()); // Use this to print connected serial devices

  arduino = new Serial(this, Serial.list()[5], 9600);  
  arduino.bufferUntil('\n'); // Buffer until line feed

  for (int i=0;i<600;i++) { // center all variables    
    gyroX[i] = height/2;
    gyroY[i] = height/2;
    accX[i] = height/2;
    accY[i] = height/2;
    kalmanX[i] = height/2; 
    kalmanY[i] = height/2;
  }
}

void draw()
{ 
  // Draw graphPaper
  background(255); // white
  for (int i = 0 ;i<=width/10;i++) {      
    stroke(200); // gray
    line((-frameCount%10)+i*10, 0, (-frameCount%10)+i*10, height);
    line(0, i*10, width, i*10);
  }

  stroke(0); // black
  for (int i = 1; i <= 3; i++)
    line(0, height/4*i, width, height/4*i); // Draw line, indicating 90 deg, 180 deg, and 270 deg

  convert();
//  drawAxisX();
  drawAxisY();
}

void serialEvent (Serial arduino) {
  try
  {
  
//    newGyroX = readFloatUntil(arduino, '\t');
//    newGyroY = readFloatUntil(arduino, '\t');  

//    newAccX = readFloatUntil(arduino, '\t');
//    newAccY = readFloatUntil(arduino, '\t');

    newKalmanX = readFloatUntil(arduino, '\t');
    newKalmanY = readFloatUntil(arduino, '\t');
  
    arduino.clear(); // Clear buffer
  } catch(Exception e) {
//   println(e); 
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
  if (temp == null) {
    return 0.0;
  } else {
    float value = get4bytesFloat(temp, 0);    
    return value;
  }
}

float get4bytesFloat(byte[] data, int offset) { 
  String hexint=hex(data[offset+3])+hex(data[offset+2])+hex(data[offset+1])+hex(data[offset]); 
  return Float.intBitsToFloat(unhex(hexint)); 
}
