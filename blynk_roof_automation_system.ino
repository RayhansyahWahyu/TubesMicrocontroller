#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6cN-eEIhU"  // Ganti dengan ID template Anda
#define BLYNK_TEMPLATE_NAME "ESP32"        // Ganti dengan nama template Anda
#define BLYNK_AUTH_TOKEN "InRyylLQhULFg-PtrOtOSeAdnuK-jZen" // Ganti dengan token autentikasi Anda

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <ESP32Servo.h>

// Konfigurasi pin dan jenis sensor DHT
#define DHTPIN 15      // Pin untuk sensor DHT (GPIO15)
#define DHTTYPE DHT11  // Tipe sensor DHT (DHT11)

DHT dht(DHTPIN, DHTTYPE);

// Pin sensor hujan dan LDR
#define RAIN_PIN 34    // Pin analog untuk sensor hujan (GPIO34)
#define LDR_PIN 35     // Pin analog untuk LDR (GPIO35)

// Pin servo
#define SERVO_PIN_1 13   // Pin GPIO untuk servo 1 (GPIO13)
#define SERVO_PIN_2 12   // Pin GPIO untuk servo 2 (GPIO12)

// Inisialisasi servo
Servo servo1;
Servo servo2;

// Inisialisasi variabel pembacaan sensor
float temperature;
float humidity;
int rainLevel;
int lightLevel;

// Inisialisasi posisi servo
int servoOpen = 0;   // Derajat untuk posisi terbuka
int servoClose = 180;  // Derajat untuk posisi tertutup

// Kredensial WiFi
char ssid[] = "username";    // Ganti dengan nama WiFi Anda
char pass[] = "password";  // Ganti dengan password WiFi Anda

void setup() {
  // Konfigurasi Serial Monitor
  Serial.begin(115200);

  // Inisialisasi koneksi ke Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Inisialisasi sensor DHT
  dht.begin();

  // Inisialisasi servo
  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2);

  // Memulai posisi servo tertutup
  servo1.write(servoClose);
  servo2.write(servoClose);

  // Konfigurasi pin LDR dan Rain Sensor sebagai input
  pinMode(RAIN_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);

  Serial.println("Weather Monitoring System with Servo and Blynk Initialized!");
}

void loop() {
  // Proses Blynk
  Blynk.run();

  // Membaca data dari DHT11
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Membaca data dari sensor hujan dan LDR
  rainLevel = analogRead(RAIN_PIN);
  lightLevel = analogRead(LDR_PIN);

  // Memetakan data sensor hujan ke nilai persentase (0-100%)
  rainLevel = map(rainLevel, 0, 4095, 100, 0);

  // Memetakan data LDR ke nilai persentase (0-100%)
  lightLevel = map(lightLevel, 0, 4095, 100, 0);

  // Memeriksa apakah pembacaan DHT berhasil
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    // Menampilkan data di Serial Monitor
    Serial.println("Weather Data:");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Rain Level: ");
    Serial.print(rainLevel);
    Serial.println(" %");

    Serial.print("Light Level: ");
    Serial.print(lightLevel);
    Serial.println(" %");
    Serial.println("-----------------------------");

    // Kirim data ke Blynk
    Blynk.virtualWrite(V0, temperature);  // Virtual pin V0 untuk suhu
    Blynk.virtualWrite(V1, humidity);     // Virtual pin V1 untuk kelembapan
    Blynk.virtualWrite(V2, rainLevel);    // Virtual pin V2 untuk tingkat hujan
    Blynk.virtualWrite(V3, lightLevel);   // Virtual pin V3 untuk tingkat cahaya

    // Logika kontrol servo berdasarkan sensor
    if (rainLevel > 50) {  // Jika hujan lebat (lebih dari 50% kelembapan)
      servo1.write(servoClose); // Servo 1 tertutup
      servo2.write(servoClose); // Servo 2 tertutup
      Serial.println("Servo: Tertutup karena hujan");
      Blynk.virtualWrite(V4, "Closed");  // Virtual pin V4 untuk status servo
    } else if (lightLevel < 30) { // Jika gelap (kurang dari 30% pencahayaan)
      servo1.write(servoClose); // Servo 1 tertutup
      servo2.write(servoClose); // Servo 2 tertutup
      Serial.println("Servo: Tertutup karena gelap");
      Blynk.virtualWrite(V4, "Closed");  // Virtual pin V4 untuk status servo
    } else {
      servo1.write(servoOpen); // Servo 1 terbuka
      servo2.write(servoOpen); // Servo 2 terbuka
      Serial.println("Servo: Terbuka karena cuaca cerah");
      Blynk.virtualWrite(V4, "Opened");  // Virtual pin V4 untuk status servo
    }
  }

  // Delay untuk memperbarui data
  delay(2000);
}
