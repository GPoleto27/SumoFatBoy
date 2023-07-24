// esp32 arduino code to control TB6612FNG motor driver
#include <TB6612_ESP32.h>

#define MOTOR_A_PWM 12
#define MOTOR_A_IN1 27
#define MOTOR_A_IN2 14
#define STANDBY 26
#define MOTOR_B_IN1 25
#define MOTOR_B_IN2 33
#define MOTOR_B_PWM 32

#define OFFSET_A 1
#define OFFSET_B 1

#define RIGHT_PWM 0
#define LEFT_PWM 1

#define PWM_FREQUENCY 5000
#define RESOLUTION 8

// Motor A is right motor
Motor rightMotor = Motor(MOTOR_A_IN1, MOTOR_A_IN2, MOTOR_A_PWM, OFFSET_A, STANDBY, PWM_FREQUENCY, RESOLUTION, RIGHT_PWM);
// Motor B is left motor
Motor leftMotor = Motor(MOTOR_B_IN1, MOTOR_B_IN2, MOTOR_B_PWM, OFFSET_B, STANDBY, PWM_FREQUENCY, RESOLUTION, LEFT_PWM);

void setup() {
    Serial.begin(115200);
    Serial.println("Hello World");
}

void loop() {
    Serial.println("Right Forward");
    rightMotor.drive(100,2000);
    delay(2000);
    rightMotor.brake();
    Serial.println("Right Backward");
    rightMotor.drive(-100,2000);
    delay(2000);
    rightMotor.brake();
    Serial.println("Left Forward");
    leftMotor.drive(100,2000);
    delay(200)0;
    leftMotor.brake();
    Serial.println("Left Backward");
    leftMotor.drive(-100,2000);
    delay(2000);
    leftMotor.brake();
}

