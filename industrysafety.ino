#include <DHT.h>

// Define Pins
#define DHTPIN 2
#define MQ2PIN A0
#define LDRPIN 3
#define TEMP_LED 6
#define GAS_LED 7
#define LDR_LED 8

// Define Sensor Thresholds
#define TEMP_THRESHOLD 32   // Adjust as needed
#define GAS_THRESHOLD 400   // Adjust as needed

DHT dht(DHTPIN, DHT11);

void setup() {
    pinMode(MQ2PIN, INPUT);
    pinMode(LDRPIN, INPUT);
    pinMode(TEMP_LED, OUTPUT);
    pinMode(GAS_LED, OUTPUT);
    pinMode(LDR_LED, OUTPUT);
    
    Serial.begin(9600);
    dht.begin();
}

void loop() {
    float temperature = dht.readTemperature();
    int gasLevel = analogRead(MQ2PIN);
    int lightStatus = digitalRead(LDRPIN); // Digital value: HIGH (bright) / LOW (dark)

    Serial.print("Temp: "); Serial.print(temperature); Serial.println("C");
    Serial.print("Gas: "); Serial.println(gasLevel);
    Serial.print("Light Status: "); Serial.println(lightStatus == HIGH ? "Dark" : "Bright");

    // Alert Conditions
    digitalWrite(TEMP_LED, temperature > TEMP_THRESHOLD ? HIGH : LOW);
    digitalWrite(GAS_LED, gasLevel > GAS_THRESHOLD ? HIGH : LOW);
    digitalWrite(LDR_LED, lightStatus == HIGH ? HIGH : LOW); // LED turns ON in darkness

    delay(2000);
}
