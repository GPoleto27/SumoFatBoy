#include <Adafruit_VL53L0X.h>

#define X_SHUT_PIN_LEFT 5
#define X_SHUT_PIN_MIDDLE 18
#define X_SHUT_PIN_RIGHT 19

Adafruit_VL53L0X lox_left = Adafruit_VL53L0X();
Adafruit_VL53L0X lox_middle = Adafruit_VL53L0X();
Adafruit_VL53L0X lox_right = Adafruit_VL53L0X();

VL53L0X_RangingMeasurementData_t measure_left;
VL53L0X_RangingMeasurementData_t measure_middle;
VL53L0X_RangingMeasurementData_t measure_right;

/*
    Reset all sensors by setting all of their XSHUT pins low for delay(10), then set all XSHUT high to bring out of reset
    Keep sensor #1 awake by keeping XSHUT pin high
    Put all other sensors into shutdown by pulling XSHUT pins low
    Initialize sensor #1 with lox.begin(new_i2c_address) Pick any number but 0x29 and it must be under 0x7F. Going with 0x30 to 0x3F is probably OK.
    Keep sensor #1 awake, and now bring sensor #2 out of reset by setting its XSHUT pin high.
    Initialize sensor #2 with lox.begin(new_i2c_address) Pick any number but 0x29 and whatever you set the first sensor to
 */
void setID() {
    digitalWrite(X_SHUT_PIN_LEFT, LOW);
    digitalWrite(X_SHUT_PIN_MIDDLE, LOW);
    digitalWrite(X_SHUT_PIN_RIGHT, LOW);
    delay(10);
    digitalWrite(X_SHUT_PIN_LEFT, HIGH);
    digitalWrite(X_SHUT_PIN_MIDDLE, HIGH);
    digitalWrite(X_SHUT_PIN_RIGHT, HIGH);
    delay(10);
    digitalWrite(X_SHUT_PIN_MIDDLE, LOW);
    digitalWrite(X_SHUT_PIN_RIGHT, LOW);
    delay(10);
    if (!lox_left.begin(0x30)) {
        Serial.println(F("Failed to boot first VL53L0X"));
        while(1);
    }
    delay(10);
    digitalWrite(X_SHUT_PIN_MIDDLE, HIGH);
    delay(10);
    if (!lox_middle.begin(0x31)) {
        Serial.println(F("Failed to boot second VL53L0X"));
        while(1);
    }
    delay(10);
    digitalWrite(X_SHUT_PIN_RIGHT, HIGH);
    delay(10);
    if (!lox_right.begin(0x32)) {
        Serial.println(F("Failed to boot third VL53L0X"));
        while(1);
    }
    delay(10);
}


void read_multi_sensors(){
    lox_left.rangingTest(&measure_left, false);
    

    if (measure_left.RangeStatus != 4) {  // phase failures have incorrect data
        Serial.print("L: ");
        Serial.print(measure_left.RangeMilliMeter);
        Serial.print("mm");
    } else {
        Serial.print("1: out of range ");
    }

    lox_middle.rangingTest(&measure_middle, false);
    if (measure_middle.RangeStatus != 4) {  // phase failures have incorrect data
        Serial.print(" M: ");
        Serial.print(measure_middle.RangeMilliMeter);
        Serial.print("mm");
    } else {
        Serial.print("2: out of range ");
    }

    lox_right.rangingTest(&measure_right, false);
    if (measure_right.RangeStatus != 4) {  // phase failures have incorrect data
        Serial.print(" R: ");
        Serial.print(measure_right.RangeMilliMeter);
        Serial.print("mm");
    } else {
        Serial.print("3: out of range ");
    }

}

// VL53L0X_RangingMeasurementData_t 
void setup() {
    Serial.begin(115200);
    while (!Serial) { delay(1); }
    pinMode(X_SHUT_PIN_LEFT, OUTPUT);
    pinMode(X_SHUT_PIN_MIDDLE, OUTPUT);
    pinMode(X_SHUT_PIN_RIGHT, OUTPUT);

    digitalWrite(X_SHUT_PIN_LEFT, LOW);
    digitalWrite(X_SHUT_PIN_MIDDLE, LOW);
    digitalWrite(X_SHUT_PIN_RIGHT, LOW);

    setID();
}

void loop() {
    read_multi_sensors();
    Serial.println();
    delay(100);
}                                                                                                                                                                         