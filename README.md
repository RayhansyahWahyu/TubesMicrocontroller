# Sistem Atap Jemuran Otomatis

## Penjelasan Sistem
Sistem atap jemuran otomatis adalah proyek berbasis IoT yang dirancang untuk melindungi pakaian yang dijemur dari hujan dan panas matahari yang berlebihan. Sistem ini menggunakan ESP32 sebagai pengendali utama yang memproses data dari berbagai sensor untuk menggerakkan atap jemuran secara otomatis. Sensor yang digunakan meliputi LDR untuk mendeteksi intensitas cahaya, Rain Drop untuk mendeteksi hujan, dan DHT11 untuk memonitor suhu serta kelembapan. Dua servo SG90 digunakan untuk membuka dan menutup atap sesuai dengan kondisi cuaca.

## Fitur Utama
- **Deteksi Cuaca Otomatis**: Membuka atap saat matahari terik dan menutupnya saat hujan.
- **Pemantauan Lingkungan**: Sensor DHT11 memberikan informasi suhu dan kelembapan.
- **Efisiensi Energi**: Sistem hanya aktif saat diperlukan.
- **Integrasi IoT (opsional)**: Data sensor dapat dikirim ke aplikasi untuk pemantauan jarak jauh.

## Perangkat / Alat dan Bahan yang Dibutuhkan
1. **Mikrokontroler**: ESP32
2. **Sensor**:
   - LDR (Light Dependent Resistor)
   - Rain Drop Sensor
   - DHT11 Sensor
3. **Servo Motor**:
   - 2x Servo SG90
4. **Komponen Elektronik**:
   - Resistor (10k ohm untuk LDR)
   - Kabel jumper
   - Breadboard
5. **Sumber Daya**:
   - Power Bank atau Adaptor 5V
6. **Struktur Mekanik**:
   - Atap jemuran (bahan plastik atau logam ringan)
   - Rangka jemuran
7. **Software**:
   - Arduino IDE
   - Library untuk sensor dan servo (DHT, Servo, dll.)

## Instalasi
1. **Persiapan Perangkat Keras**:
   - Pasang sensor LDR, Rain Drop, dan DHT11 ke breadboard.
   - Sambungkan servo SG90 ke ESP32.
   - Pastikan semua komponen terhubung sesuai wiring diagram.
2. **Persiapan Perangkat Lunak**:
   - Install Arduino IDE.
   - Tambahkan board ESP32 ke Arduino IDE melalui Board Manager.
   - Install library untuk DHT, servo, dan sensor lainnya.
3. **Upload Program**:
   - Tulis atau gunakan kode yang telah disiapkan.
   - Upload kode ke ESP32 melalui kabel USB.

## Wiring Diagram
Berikut adalah koneksi wiring untuk sistem:
- **LDR**: Sambungkan pin data ke salah satu pin digital ESP32.
- **Rain Drop Sensor**: Sambungkan pin data ke salah satu pin digital ESP32.
- **DHT11**: Sambungkan pin data ke pin digital ESP32.
- **Servo SG90**: Sambungkan pin sinyal masing-masing servo ke pin PWM ESP32.

## Cara Kerja
1. **Deteksi Cuaca**:
   - LDR mendeteksi intensitas cahaya. Jika cahaya cukup terang, sistem membuka atap.
   - Rain Drop Sensor mendeteksi adanya hujan. Jika hujan terdeteksi, atap ditutup.
2. **Monitoring Suhu dan Kelembapan**:
   - DHT11 memberikan data suhu dan kelembapan untuk analisis tambahan.
3. **Pengendalian Atap**:
   - Dua servo SG90 digunakan untuk membuka dan menutup atap sesuai instruksi dari ESP32 berdasarkan data sensor.
4. **Operasi Otomatis**:
   - Sistem berjalan secara otomatis tanpa intervensi manual.

---
Dengan sistem ini, pengguna tidak perlu khawatir tentang kondisi cuaca saat menjemur pakaian, karena sistem akan menyesuaikan atap secara otomatis sesuai kebutuhan.

