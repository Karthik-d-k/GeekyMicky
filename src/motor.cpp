#include <Arduino.h>

#include <motor.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 gyroscope;

L293D RIGHT_MOTOR;
L293D LEFT_MOTOR;

#define getAccX gyroscope.getAccelerationX()
#define getAccY gyroscope.getAccelerationY()
#define getAccZ gyroscope.getAccelerationZ()
#define getRotX gyroscope.getRotationX()

unsigned long prevTime = 0;
float speedX = 0, speedY = 0, speedZ = 0, rotSpeed = 0;

void init_Gyroscope()
{
    gyroscope.initialize();
}

void calculateSpeedAndRotation()
{

    unsigned long currentTime = millis();
    float rate = (currentTime - previousTime) / 1000.0;
    previousTime = currentTime;

    speedX += getAccX * rate;
    speedY += getAccY * rate;
    speedZ += getAccZ * rate;
    rotSpeed = getRotX * (180.0 / 3.14);
    GYROSCOPE_OUT.speedX = speedX;
    GYROSCOPE_OUT.speedY = speedY;
    GYROSCOPE_OUT.speedZ = speedZ;
    GYROSCOPE_OUT.rotSpeed = rotSpeed;
    delay(10);
}

void L293D_init(L293D* l293d_ptr, int pin_E, int pin_A, int pin_B) {
    pinMode(pin_E, OUTPUT);
    pinMode(pin_A, OUTPUT);
    pinMode(pin_B, OUTPUT);
    l293d_ptr->pin_E = pin_E;
    l293d_ptr->pin_A = pin_A;
    l293d_ptr->pin_B = pin_B;
    // Set initially to 0
    L293D_set_int(l293d_ptr, 0);
}

void L293D_set(L293D* l293d_ptr, double value) {
    if (value <= 1 && value >= -1) {
        L293D_set_int(l293d_ptr, (int)(value * 255));
    }
}

void L293D_set_int(L293D* l293d_ptr, int value) {
    if (value == 0) {
        digitalWrite(l293d_ptr->pin_E, LOW);
        l293d_ptr->speed = value;
    } else if (value > 0 && value <= 255) {
        // disable before possibly switching directions
        digitalWrite(l293d_ptr->pin_E, LOW);
        // drive pin A HIGH and pin B LOW
        digitalWrite(l293d_ptr->pin_A, HIGH);
        digitalWrite(l293d_ptr->pin_B, LOW);
        // enable
        analogWrite(l293d_ptr->pin_E, value);
        // Save value it's been set to
        l293d_ptr->speed = value;
    } else if (value < 0 && value >= -255) {
        // disable before possibly switching directions
        digitalWrite(l293d_ptr->pin_E, LOW);
        // drive pin A LOW and pin B HIGH
        digitalWrite(l293d_ptr->pin_A, LOW);
        digitalWrite(l293d_ptr->pin_B, HIGH);
        // enable
        analogWrite(l293d_ptr->pin_E, -1 * value); // Multiply by -1 to make sure the value is positive.
        // Save value it's been set to
        l293d_ptr->speed = value;
    }
}

int L293D_get(L293D* l293d_ptr) {
    return l293d_ptr->speed;
}

void init_motors(void) {
    L293D_init(&RIGHT_MOTOR, RIGHT_MOTOR_PWM_PIN, RIGHT_MOTOR_PIN1, RIGHT_MOTOR_PIN2);
    L293D_init(&LEFT_MOTOR, LEFT_MOTOR_PWM_PIN, LEFT_MOTOR_PIN1, LEFT_MOTOR_PIN2);
    init_Gyroscope();
}

void test_right_motors(void) {
    // Set motor speed and direction with a double value between -1 and 1
    L293D_set(&RIGHT_MOTOR, 0.75); // 75% power forward
    delay(2500);
    L293D_set(&RIGHT_MOTOR, -0.3); // 30% power reverse
    delay(2500);

    // Set motor speed and direction with an int value between -255 and 255
    L293D_set_int(&RIGHT_MOTOR, 200);
    delay(2500);
    L293D_set_int(&RIGHT_MOTOR, -150);
    delay(2500);

    // Use L293D_get() to get current speed and then update it from that
    L293D_set_int(&RIGHT_MOTOR, -255);
    while (L293D_get(&RIGHT_MOTOR) != 255) {
        L293D_set_int(&RIGHT_MOTOR, L293D_get(&RIGHT_MOTOR) + 5); // Increment motor speed from previous speed
        delay(100);                                               // Delay 100ms to see the speed changing
    }
}

void test_left_motors(void) {
    // Set motor speed and direction with a double value between -1 and 1
    L293D_set(&LEFT_MOTOR, 0.75); // 75% power forward
    delay(2500);
    L293D_set(&LEFT_MOTOR, -0.3); // 30% power reverse
    delay(2500);

    // Set motor speed and direction with an int value between -255 and 255
    L293D_set_int(&LEFT_MOTOR, 200);
    delay(2500);
    L293D_set_int(&LEFT_MOTOR, -150);
    delay(2500);

    // Use L293D_get() to get current speed and then update it from that
    L293D_set_int(&LEFT_MOTOR, -255);
    while (L293D_get(&LEFT_MOTOR) != 255) {
        L293D_set_int(&LEFT_MOTOR, L293D_get(&LEFT_MOTOR) + 5); // Increment motor speed from previous speed
        delay(100);                                             // Delay 100ms to see the speed changing
    }
}
