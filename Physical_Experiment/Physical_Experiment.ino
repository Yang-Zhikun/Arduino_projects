/**
 * 
 */

#include<DHT11.h>
#define DHT11_1_PIN 13
#define DHT11_2_PIN 12
DHT11 dht11_1(DHT11_1_PIN);
DHT11 dht11_2(DHT11_2_PIN);

void setup() {
    Serial.begin(115200);
    pinMode(DHT11_2_PIN, INPUT_PULLUP);
    pinMode(DHT11_1_PIN, INPUT_PULLUP);
}

void loop(){
    int temp1 = dht11_1.readTemperature();
    int hum1 = dht11_1.readHumidity();
    if (temp1 == DHT11::ERROR_TIMEOUT || hum1 == DHT11::ERROR_TIMEOUT || temp1 == DHT11::ERROR_CHECKSUM || hum1 == DHT11::ERROR_CHECKSUM){
        Serial.println("dht11_1 Error");
    }
    else{
        Serial.print("Temperature1: ");
        Serial.print(temp1);
        Serial.print(".C, Humidity1: ");
        Serial.print(hum1);
        Serial.println("%");
    }

    int temp2 = dht11_2.readTemperature();
    int hum2 = dht11_2.readHumidity();
    if (temp2 == DHT11::ERROR_TIMEOUT){
        Serial.println("dht11_2 Error");
    }
    else{
        Serial.print("Temperature2: ");
        Serial.print(temp2);
        Serial.print(".C, Humidity2: ");
        Serial.print(hum2);
        Serial.println("%");
    }
}