#include <SparkFunMPU9250-DMP.h>
#define SerialPort Serial
#define LED_PIN 2
MPU9250_DMP imu;

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  SerialPort.begin(115200);
  if (imu.begin() != INV_SUCCESS)
  {
    while (1)
    {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      delay(500);
    }
  }
  
  imu.dmpBegin(DMP_FEATURE_6X_LP_QUAT | // Enable 6-axis quat
               DMP_FEATURE_GYRO_CAL, // Use gyro calibration
              10); // Set DMP FIFO rate to 10 Hz
  digitalWrite(LED_PIN, HIGH);
}

void loop() 
{
  if ( imu.fifoAvailable() )
  {
    if ( imu.dmpUpdateFifo() == INV_SUCCESS)
    {
      imu.computeEulerAngles();
      printIMUData();
    }
  }
}

void printIMUData(void)
{  
  float q0 = imu.calcQuat(imu.qw);
  float q1 = imu.calcQuat(imu.qx);
  float q2 = imu.calcQuat(imu.qy);
  float q3 = imu.calcQuat(imu.qz);
  SerialPort.println(String(q0,6) + "," + String(q1,6) + "," + String(q2,6) + "," + String(q3,6));
}

