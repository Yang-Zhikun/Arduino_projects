#include <DHT11.h>

#define DHT_PIN 13          // DHT11����������
#define BUTTON_PIN 12       // ��ť����

// ��ʼ��DHT������
DHT11 dht(DHT_PIN);

void setup() {
    Serial.begin(115200);     // ���ڳ�ʼ��
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
    delay(1000);  // ÿ��ѭ��һ��

    if(digitalRead(BUTTON_PIN) == LOW){
        delay(50);
        Serial.println("Button pressed");
    }
}