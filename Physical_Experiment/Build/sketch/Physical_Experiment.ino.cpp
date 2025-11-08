#include <Arduino.h>
#line 1 "D:\\DevFiles\\Arduino\\Arduino_projects\\Physical_Experiment\\Physical_Experiment.ino"
#include <DHT11.h>

#define DHT1_PIN 13          // 第一个DHT11传感器引脚
#define DHT2_PIN 12          // 第二个DHT11传感器引脚
#define DHT3_PIN 11          // 第三个DHT11传感器引脚

// 初始化DHT传感器
DHT11 dht1(DHT1_PIN);
DHT11 dht2(DHT2_PIN);
DHT11 dht3(DHT3_PIN);

#line 12 "D:\\DevFiles\\Arduino\\Arduino_projects\\Physical_Experiment\\Physical_Experiment.ino"
void setup();
#line 21 "D:\\DevFiles\\Arduino\\Arduino_projects\\Physical_Experiment\\Physical_Experiment.ino"
void loop();
#line 12 "D:\\DevFiles\\Arduino\\Arduino_projects\\Physical_Experiment\\Physical_Experiment.ino"
void setup() {
    Serial.begin(115200);     // 串口初始化
    pinMode(DHT1_PIN, INPUT_PULLUP);
    pinMode(DHT2_PIN, INPUT_PULLUP);
    pinMode(DHT3_PIN, INPUT_PULLUP);
    pinMode(8, OUTPUT);
    digitalWrite(8, HIGH);
}

void loop() {
    int temp1, hum1;
    temp1 = dht1.readTemperature();
    hum1 = dht1.readHumidity();
    if (temp1 == DHT11::ERROR_TIMEOUT || hum1 == DHT11::ERROR_TIMEOUT || temp1 == DHT11::ERROR_CHECKSUM || hum1 == DHT11::ERROR_CHECKSUM) {
        Serial.print("DHT11_1 Error: ");
        if (temp1 == DHT11::ERROR_TIMEOUT) {
            Serial.print("TEMP Timeout Error;  ");
        }
        if (temp1 == DHT11::ERROR_CHECKSUM) {
            Serial.print("TEMP Checksum Error;  ");
        }
        if (hum1 == DHT11::ERROR_TIMEOUT) {
            Serial.print("HUM Timeout Error;  ");
        }
        if (hum1 == DHT11::ERROR_CHECKSUM) {
            Serial.print("HUM Checksum Error;  ");
        }
    }
    else {
        Serial.print("Temp_1: ");
        Serial.print(temp1);
        Serial.print(" C, Hum_1: ");
        Serial.print(hum1);
        Serial.print("%;  ");
    }

    int temp2, hum2;
    temp2 = dht2.readTemperature();
    hum2 = dht2.readHumidity();
    if (temp2 == DHT11::ERROR_TIMEOUT || hum2 == DHT11::ERROR_TIMEOUT || temp2 == DHT11::ERROR_CHECKSUM || hum2 == DHT11::ERROR_CHECKSUM) {
        Serial.print("DHT11_2 Error: ");
        if (temp2 == DHT11::ERROR_TIMEOUT) {
            Serial.print("TEMP Timeout Error;  ");
        }
        if (temp2 == DHT11::ERROR_CHECKSUM) {
            Serial.print("TEMP Checksum Error;  ");
        }
        if (hum2 == DHT11::ERROR_TIMEOUT) {
            Serial.print("HUM Timeout Error;  ");
        }
        if (hum2 == DHT11::ERROR_CHECKSUM) {
            Serial.print("HUM Checksum Error;  ");
        }
    }
    else {
        Serial.print("Temp_2: ");
        Serial.print(temp2);
        Serial.print(" C, Hum_2: ");
        Serial.print(hum2);
        Serial.print("%;  ");
    }

    int temp3, hum3;
    temp3 = dht3.readTemperature();
    hum3 = dht3.readHumidity();
    if (temp3 == DHT11::ERROR_TIMEOUT || hum3 == DHT11::ERROR_TIMEOUT || temp3 == DHT11::ERROR_CHECKSUM || hum3 == DHT11::ERROR_CHECKSUM) {
        Serial.print("DHT11_3 Error: ");
        if (temp3 == DHT11::ERROR_TIMEOUT) {
            Serial.println("TEMP Timeout Error;  ");
        }
        if (temp3 == DHT11::ERROR_CHECKSUM) {
            Serial.println("TEMP Checksum Error;  ");
        }
        if (hum3 == DHT11::ERROR_TIMEOUT) {
            Serial.println("HUM Timeout Error;  ");
        }
        if (hum3 == DHT11::ERROR_CHECKSUM) {
            Serial.println("HUM Checksum Error;  ");
        }
    }
    else {
        Serial.print("Temp_3: ");
        Serial.print(temp3);
        Serial.print(" C, Hum_3: ");
        Serial.print(hum3);
        Serial.println("%;  ");
    }



    delay(1000);  // 每秒循环一次
}
