#include <Arduino.h>
#line 1 "D:\\DevFiles\\Arduino\\Arduino_projects\\Physical_Experiment\\Physical_Experiment.ino"
#include <DHT11.h>

#define DHT1_PIN 13          // 第一个DHT11传感器引脚
#define DHT2_PIN 12          // 第二个DHT11传感器引脚
#define FAN_PIN 8           // 风扇控制引脚

// 初始化DHT传感器
DHT11 dht1(DHT1_PIN);
DHT11 dht2(DHT2_PIN);

#line 11 "D:\\DevFiles\\Arduino\\Arduino_projects\\Physical_Experiment\\Physical_Experiment.ino"
void setup();
#line 23 "D:\\DevFiles\\Arduino\\Arduino_projects\\Physical_Experiment\\Physical_Experiment.ino"
void loop();
#line 11 "D:\\DevFiles\\Arduino\\Arduino_projects\\Physical_Experiment\\Physical_Experiment.ino"
void setup() {
    Serial.begin(115200);     // 串口初始化
    pinMode(FAN_PIN, OUTPUT);
    digitalWrite(FAN_PIN, HIGH);

    // 试读取传感器数据
    dht1.readTemperature();
    dht1.readHumidity();
    dht2.readTemperature();
    dht2.readHumidity();
}

void loop() {
    // 读取传感器数据
    int temp1, humi1;
    temp1 = dht1.readTemperature();
    humi1 = dht1.readHumidity();

    int temp2, humi2;
    temp2 = dht2.readTemperature();
    humi2 = dht2.readHumidity();

    // 输出数据到串口
    if (temp1 == DHT11::ERROR_TIMEOUT || humi1 == DHT11::ERROR_TIMEOUT || temp1 == DHT11::ERROR_CHECKSUM || humi1 == DHT11::ERROR_CHECKSUM) {
        Serial.print("DHT11_1 Error: ");
    }
    else {
        Serial.print("Temp_1: ");
        Serial.print(temp1);
        Serial.print(" C, Humi_1: ");
        Serial.print(humi1);
        Serial.print("%;  ");
    }

    if (temp2 == DHT11::ERROR_TIMEOUT || humi2 == DHT11::ERROR_TIMEOUT || temp2 == DHT11::ERROR_CHECKSUM || humi2 == DHT11::ERROR_CHECKSUM) {
        Serial.print("DHT11_2 Error: ");
    }
    else {
        Serial.print("Temp_2: ");
        Serial.print(temp2);
        Serial.print(" C, Humi_2: ");
        Serial.print(humi2);
        Serial.print("%;  ");
    }

    // 特判温度等于0的情况
    if (temp1 == 0 && temp2 != 0) {
        temp1 = temp2;
    } 
    else if (temp2 == 0 && temp1 != 0) {
        temp2 = temp1;
    }
    // 计算平均值
    float avgTemp = (temp1 + temp2) / 2.0;
    float avgHumi = (humi1 + humi2) / 2.0;
    Serial.print("Avg Temp: ");
    Serial.print(avgTemp);
    Serial.print(" C, Avg Humi: ");
    Serial.print(avgHumi);
    Serial.println("%;  ");

    //delay(10);
}
