#include <Arduino.h>
#line 1 "D:\\DevFiles\\Arduino\\Arduino_projects\\Physical_Experiment\\Physical_Experiment.ino"
#include <DHT11.h>

#define DHT_PIN 13          // DHT11传感器引脚
#define BUTTON_PIN 12       // 按钮引脚

// 初始化DHT传感器
DHT11 dht(DHT_PIN);

#line 9 "D:\\DevFiles\\Arduino\\Arduino_projects\\Physical_Experiment\\Physical_Experiment.ino"
void setup();
#line 15 "D:\\DevFiles\\Arduino\\Arduino_projects\\Physical_Experiment\\Physical_Experiment.ino"
void loop();
#line 9 "D:\\DevFiles\\Arduino\\Arduino_projects\\Physical_Experiment\\Physical_Experiment.ino"
void setup() {
    Serial.begin(115200);     // 串口初始化
    pinMode(DHT_PIN, INPUT_PULLUP);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
    int temp, hum;
    temp = dht.readTemperature();
    hum = dht.readHumidity();
    if (temp == DHT11::ERROR_TIMEOUT || hum == DHT11::ERROR_TIMEOUT || temp == DHT11::ERROR_CHECKSUM || hum == DHT11::ERROR_CHECKSUM) {
        Serial.println("DHT11 Error");
    }
    else {
        Serial.print("Temperature: ");
        Serial.print(temp);
        Serial.print(" C, Humidity: ");
        Serial.print(hum);
        Serial.println("%");
    }
    delay(1000);  // 每秒循环一次

    if(digitalRead(BUTTON_PIN) == LOW){
        delay(50);
        Serial.println("Button pressed");
    }
}
