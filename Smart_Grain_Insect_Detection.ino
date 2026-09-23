#define BLYNK_TEMPLATE_ID "TMPL34qQ5s2SA"
#define BLYNK_TEMPLATE_NAME "Smart grain insect detection system"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_TOKEN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// ---------------- WIFI ----------------
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// ---------------- PINS ----------------
#define DHTPIN 4
#define DHTTYPE DHT11

#define VIB_PIN 5
#define GAS_PIN 34
#define BUZZER_PIN 18

// ---------------- SENSOR OBJECT ----------------
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// ---------------- THRESHOLD VALUES ----------------
#define TEMP_LIMIT 35
#define HUM_LIMIT 40
#define GAS_LIMIT 1500

// ---------------- ALERT FLAGS ----------------
bool tempAlert = false;
bool humAlert = false;
bool gasAlert = false;
bool vibAlert = false;

// ---------------- ALERT TIMER ----------------
unsigned long lastAlertTime = 0;
const long alertInterval = 10000;

// =================================================
// FUNCTION TO READ SENSOR DATA
// =================================================
void sendData()
{

    // Read sensors
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    int vib = digitalRead(VIB_PIN);
    int gas = analogRead(GAS_PIN);

    // Check DHT sensor
    if (isnan(temp) || isnan(hum))
    {
        Serial.println("DHT Error");
        return;
    }

    // ---------------- SERIAL MONITOR ----------------
    Serial.print("Temperature: ");
    Serial.print(temp);

    Serial.print(" °C | Humidity: ");
    Serial.print(hum);

    Serial.print(" % | Vibration: ");
    Serial.print(vib);

    Serial.print(" | Gas: ");
    Serial.println(gas);

    // ---------------- SEND DATA TO BLYNK ----------------
    Blynk.virtualWrite(V0, temp);
    Blynk.virtualWrite(V1, hum);
    Blynk.virtualWrite(V2, vib);
    Blynk.virtualWrite(V3, gas);

    bool alert = false;

    // ---------------- TEMPERATURE CHECK ----------------
    if (temp > TEMP_LIMIT)
    {
        tempAlert = true;
        alert = true;
    }
    else
    {
        tempAlert = false;
    }

    // ---------------- HUMIDITY CHECK ----------------
    if (hum > HUM_LIMIT)
    {
        humAlert = true;
        alert = true;
    }
    else
    {
        humAlert = false;
    }

    // ---------------- GAS CHECK ----------------
    if (gas > GAS_LIMIT)
    {
        gasAlert = true;
        alert = true;
    }
    else
    {
        gasAlert = false;
    }

    // ---------------- VIBRATION CHECK ----------------
    if (vib == HIGH)
    {
        vibAlert = true;
        alert = true;
    }
    else
    {
        vibAlert = false;
    }

    // ---------------- BUZZER CONTROL ----------------
    if (alert)
    {
        digitalWrite(BUZZER_PIN, HIGH);
    }
    else
    {
        digitalWrite(BUZZER_PIN, LOW);
    }

    // ---------------- BLYNK ALERT NOTIFICATIONS ----------------
    if (alert)
    {

        unsigned long currentTime = millis();

        if (currentTime - lastAlertTime >= alertInterval)
        {

            Serial.println("========== ALERT TRIGGERED ==========");

            if (tempAlert)
            {
                Serial.println("High Temperature Detected");
                Blynk.logEvent("temp_alert", "High Temperature Detected");
            }

            if (humAlert)
            {
                Serial.println("High Humidity Detected");
                Blynk.logEvent("humidity_alert", "High Humidity Detected");
            }

            if (gasAlert)
            {
                Serial.println("Gas Level Increased");
                Blynk.logEvent("gas_alert", "Gas Increase Detected");
            }

            if (vibAlert)
            {
                Serial.println("Vibration Detected");
                Blynk.logEvent("insect_alert", "Possible Insect Movement");
            }

            lastAlertTime = currentTime;
        }
    }
}

// =================================================
// SETUP
// =================================================
void setup()
{

    Serial.begin(115200);
    delay(1000);

    Serial.println("SYSTEM STARTED");

    // Pin configuration
    pinMode(VIB_PIN, INPUT_PULLUP);
    pinMode(GAS_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    digitalWrite(BUZZER_PIN, LOW);

    // Start DHT sensor
    dht.begin();

    // ---------------- WIFI ----------------
    WiFi.begin(ssid, pass);

    Serial.print("Connecting to WiFi");

    // ---------------- BLYNK ----------------
    Blynk.config(BLYNK_AUTH_TOKEN);

    // ---------------- TIMER ----------------
    timer.setInterval(2000L, sendData);
}

// =================================================
// LOOP
// =================================================
void loop()
{

    Blynk.run();
    timer.run();
}