//convert all axis
int minAngle = -360;
int maxAngle = 360;

void convert() {   
  /* convert the gyro x-axis */
//  gyroX[gyroX.length-1] = map(newGyroX, minAngle, maxAngle, 0, height);
//  gyroY[gyroY.length-1] = map(newGyroY, minAngle, maxAngle, 0, height);
  
  /* convert the accelerometer x-axis */
//  accX[accX.length-1] = map(newAccX, minAngle, maxAngle, 0, height);
//  accY[accY.length-1] = map(newAccY, minAngle, maxAngle, 0, height);
  
  /* convert the kalman filter x-axis */
  kalmanX[kalmanX.length-1] = map(newKalmanX, minAngle, maxAngle, 0, height);
  kalmanY[kalmanY.length-1] = map(newKalmanY, minAngle, maxAngle, 0, height);
}
