#include "mbed.h"
#include "HMC5843.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "kalman.c"
#include "MAF.h"

#define Rad2Dree       57.295779513082320876798154814105

HMC5843 cmp(p28, p27);      // sda, scl
ADXL345 acc(p28, p27);      // sda, scl
ITG3200 gyr(p28, p27);      // sda, scl
Serial pc(USBTX, USBRX);    // tx, rx
Timer ProgramTimer;
MAF mafX;
MAF mafY;

typedef struct 
{ 
    float x;
    float y; 
    float z;    
} values; 

float accel_scale = 0.00395;

values gyro;
values accel;
values kal;

kalman filter_x; 
kalman filter_y;

//values x,y,z
int readings[3];

//ID Buffer
char buffer[3];

void update_gyro() {
    gyro.x = (int16_t)gyr.getGyroX();
    gyro.y = (int16_t)gyr.getGyroY();
    gyro.z = (int16_t)gyr.getGyroZ();
}

void update_accel() {
    acc.getOutput(readings);
    accel.x = ((int16_t)readings[0]) * accel_scale;
    accel.y = ((int16_t)readings[1]) * accel_scale;
    accel.z = ((int16_t)readings[2]) * accel_scale;
}

void setup_cmp() {
    // Continuous mode, , 10Hz measurement rate.
    // HMC5843_CONTINUOUS, HMC5843_10HZ_NORMAL HMC5843_1_0GA
    cmp.setDefault();
    // Wait some time(Need at least 5ms)
    wait(0.1);
    cmp.getAddress(buffer);
    pc.printf("cmp Id=%c%c%c \n\r",buffer[0],buffer[1],buffer[2]);
}
        
bool setup_acc() {
    // These are here to test whether any of the initialization fails. It will print the failure
    if (acc.setPowerControl(0x00)) {
        pc.printf("acc: didn't intitialize power control\n"); 
        return false;  
    }
    wait(.001);
    
    //Full resolution, +/-16g, 4mg/LSB.
    //if(acc.setDataFormatControl(0x0B)){
    if(acc.setDataFormatControl(0x09)){  // +/- 4G               
        pc.printf("didn't set data format\n");
        return false;  }
    wait(.001);
     
    //200Hz data rate.
    if(acc.setDataRate(ADXL345_200HZ)){
        pc.printf("didn't set data rate\n");
        return false;    }
    wait(.001);
     
    //Measurement mode.
    if(acc.setPowerControl(MeasurementMode)) {
        pc.printf("didn't set the power control to measurement\n"); 
        return false;   } 

    pc.printf("Acc Id=%x \n\r", acc.getDeviceID());
    pc.printf("%c" ,13,10);
    return true;
}

void setup_gyr() {
    //Set highest bandwidth.
    gyr.setLpBandwidth(LPFBW_256HZ);
    pc.printf("Gyro Id=%x \n\r", gyr.getWhoAmI());
    pc.printf("%c" ,13,10);
}

typedef union _data {
  float f;
  char  s[4];
} myData;

myData dataX;
myData dataY;

int main() {
    pc.baud(9600);            
    
    // used by kalman filter
    float R;
    unsigned long timer;
            
    setup_cmp();
    setup_acc();    
    setup_gyr();            

    wait(1);

    // Parameters ( R_angle, Q_gyro, Q_angle ) 
    kalman_init(&filter_x, R_matrix, Q_Gyro_matrix, Q_Accel_matrix); 
    kalman_init(&filter_y, R_matrix, Q_Gyro_matrix, Q_Accel_matrix);

    ProgramTimer.start();
    timer = ProgramTimer.read_us();

    while (1) {        
        update_gyro();
        update_accel();        

        //Calcuate the resulting vector R from the 3 acc axes
        R = sqrt(pow(accel.x , 2) + pow(accel.y , 2) + pow(accel.z , 2));
   
        kalman_predict(&filter_x, gyro.x,  (ProgramTimer.read_us() - timer)); 
        kalman_update(&filter_x, acos(accel.x/R));

        kalman_predict(&filter_y, gyro.y,  (ProgramTimer.read_us() - timer)); 
        kalman_update(&filter_y, acos(accel.y/R));
        
        kal.x = Rad2Dree * kalman_get_angle(&filter_x);
        kal.y = Rad2Dree * kalman_get_angle(&filter_y);                

        timer = ProgramTimer.read_us();

        dataX.f = mafX.update(kal.x);
        dataY.f = mafY.update(kal.y);
        pc.printf("K%c%c%c%c\t%c%c%c%c\n", dataX.s[0], dataX.s[1], dataX.s[2], dataX.s[3], dataY.s[0], dataY.s[1], dataY.s[2], dataY.s[3]);

        wait(0.01);        
    }
}
