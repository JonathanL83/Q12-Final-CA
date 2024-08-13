#include "mbed.h"
#include "LSM6DSLSensor.h"

// Define LED pins
PwmOut led1(LED1);
PwmOut led2(LED2);
PwmOut led3(LED3);

// Initialize I2C and accelerometer sensor
static DevI2C devI2c(PB_11,PB_10);
static LSM6DSLSensor acc_gyro(&devI2c, 0xD4, D4, D5);

// Function to normalize the axis data to a value between 0 and 1
float normalize(int value) {
    float normalized = fabs(value) / 2000.0f;  // Assuming max acceleration is 2000 mg
    return (normalized > 1.0f) ? 1.0f : normalized;
}

int main() {
    uint8_t id;
    int32_t axes[3];

    acc_gyro.init(NULL);
    acc_gyro.enable_x();
    acc_gyro.enable_g();

    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    while(1) {
        acc_gyro.get_x_axes(axes);

        // Normalize axis values to control LED brightness
        led1.write(normalize(axes[0]));  // X-axis controls LED1
        led2.write(normalize(axes[1]));  // Y-axis controls LED2
        led3.write(normalize(axes[2]));  // Z-axis controls LED3

        printf("LSM6DSL: %6d, %6d, %6d\r\n", axes[0], axes[1], axes[2]);

        thread_sleep_for(100);
    }
}
