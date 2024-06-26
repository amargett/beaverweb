#ifndef IMU_H
#define IMU_H

struct Quaternion {
    double w, x, y, z;
};

struct EulerAngles {
    double roll, pitch, yaw;
    bool success;
    bool gyro;
};

void imuSetup(void);
EulerAngles readIMU();
void imuISR(void);
extern volatile bool imuDataReady;

void setReports(void);
void printEuler(EulerAngles angles);
EulerAngles ToEulerAngles(Quaternion q);
#endif // IMU_H