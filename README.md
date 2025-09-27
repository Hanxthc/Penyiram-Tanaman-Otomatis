🌱 Sistem Penyiraman Otomatis Arduino

<div align="center">

https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white
https://img.shields.io/badge/Version-3.1-blue?style=for-the-badge
https://img.shields.io/badge/License-MIT-green?style=for-the-badge

Sistem pintar untuk menyiram tanaman secara otomatis berdasarkan kelembaban tanah

"Tanamanmu sehat, hidupmu tenang" 🌿

</div>

📋 Daftar Isi

· 🎯 Overview
· ✨ Fitur Unggulan
· 📦 Hardware yang Diperlukan
· 🔧 Instalasi dan Setup
· 🎮 Cara Penggunaan
· 💻 Command List
· 📊 Penjelasan Kode
· 🤝 Kontribusi
· 📄 Lisensi

🎯 Overview

Sistem Penyiraman Otomatis ini adalah solusi cerdas untuk menjaga tanaman Anda tetap sehat tanpa perlu khawatir lupa menyiram. Dengan menggunakan sensor kelembaban tanah, sistem akan secara otomatis mengaktifkan pompa air ketika tanah terlalu kering.

🎨 Visual Sistem Kerja

```
Sensor Baca Kelembaban → Analisis Data → Keputusan Penyiraman → Action Motor
       ↑                      ↑               ↑
   Tanaman Kering?    Threshold Setting    Mode Operation
```

✨ Fitur Unggulan

· 🌊 Auto Watering: Menyiram otomatis berdasarkan kelembaban tanah
· 💡 LED Indicator: Status visual dengan 3 warna LED
· 📱 Serial Monitor Control: Kontrol penuh melalui Serial Monitor
· 💾 EEPROM Memory: Penyimpanan setting threshold permanen
· 📊 Moving Average: Filter data sensor untuk hasil akurat
· ⚠️ Anomaly Detection: Deteksi error sensor otomatis
· 🔄 Multiple Modes: Auto, Manual ON, Manual OFF

📦 Hardware yang Diperlukan

Komponen List

Komponen Jumlah Keterangan
Arduino Uno 1 Board utama
Soil Moisture Sensor 1 Sensor kelembaban tanah
Relay Module 1 Kontrol pompa air
Water Pump 1 Pompa air kecil
LED Merah, Kuning, Hijau Masing-masing 1 Indicator status
Resistor 220Ω 3 Untuk LED
Breadboard 1 Tempat merangkai
Kabel Jumper Secukupnya Konektor

🔌 Wiring Diagram

```
Arduino Pin   →   Komponen
A0           →   Soil Sensor Signal
Pin 7        →   Relay IN (kontrol pompa)
Pin 2        →   LED Merah (+ resistor 220Ω)
Pin 3        →   LED Kuning (+ resistor 220Ω)
Pin 4        →   LED Hijau (+ resistor 220Ω)
5V           →   Sensor VCC, Relay VCC
GND          →   Sensor GND, Relay GND, LED Cathode
```

🔧 Instalasi dan Setup

Langkah 1: Software Preparation

1. Download Arduino IDE dari arduino.cc
2. Install Arduino IDE sesuai sistem operasi Anda
3. Buka Arduino IDE dan sambungkan Arduino ke komputer

Langkah 2: Upload Code

```cpp
// Salin kode dari file utama dan paste di Arduino IDE
// Klik "Verify" (✓) untuk kompilasi
// Klik "Upload" (→) untuk upload ke Arduino
```

Langkah 3: Hardware Setup

1. Rangkai komponen sesuai wiring diagram di atas
2. Pastikan koneksi benar sebelum menyalakan
3. Hubungkan Arduino ke komputer via USB

Langkah 4: Testing

1. Buka Serial Monitor (Tools → Serial Monitor)
2. Set baud rate ke 9600
3. Tunggu startup sequence - LED akan berkedip
4. System ready! 🎉

🎮 Cara Penggunaan

Mode Otomatis (Default)

```bash
# Sistem akan otomatis menyiram ketika tanah kering
# Threshold default: 500 (1-1023, semakin kecil semakin basah)
```

Monitoring Real-time

```bash
# Aktifkan monitor untuk melihat data sensor
monitor on

# Contoh output:
[DATA] Sensor: 650 | Kering: 63% -> [AUTO] Kering → Motor ON
[DATA] Sensor: 300 | Kering: 29% -> [AUTO] Basah → Motor OFF
```

Manual Control

```bash
# Paksa motor menyiram terus
mode on

# Matikan motor sepenuhnya
mode off

# Kembali ke mode otomatis
mode auto
```

💻 Command List

Command Syntax Contoh Keterangan
Set Threshold set <angka> set 600 Atur sensitivitas (1-1023)
Change Mode mode <auto/on/off> mode on Ubah mode operasi
Monitor monitor <on/off> monitor on Aktif/matikan monitoring
Sensor Delay delay sensor <ms> delay sensor 2000 Atur interval baca sensor
Status status status Cek kondisi terkini
Help help help Tampilkan semua command

🎯 LED Indicator Guide

· 🔴 LED Merah: Motor OFF / Tanaman cukup air
· 🟡 LED Kuning: Error sensor / Startup
· 🟢 LED Hijau: Motor ON / Sedang menyiram

📊 Penjelasan Kode

🏗️ Struktur Program

```cpp
// === BAGIAN KONFIGURASI ===
const int sensorPin = A0;    // Pin sensor kelembaban
const int motorPin = 7;      // Pin kontrol motor
// ... dan seterusnya

// === SETUP AWAL ===
void setup() {
  // Inisialisasi pin dan serial communication
}

// === LOOP UTAMA ===
void loop() {
  // Baca sensor, proses data, dan kontrol motor
}
```

🔧 Fungsi Penting

1. bacaSensor() - Membaca kelembaban dengan filter moving average
2. printStatus() - Menampilkan status sistem ke Serial Monitor
3. cekSerial() - Memproses command dari user
4. animasiStartup() - LED animation saat startup

⚙️ Parameter yang Dapat Disesuaikan

```cpp
// Ubah nilai ini sesuai kebutuhan:
int threshold = 500;        // Sensitivitas kelembaban
int delaySensor = 1000;     // Interval baca sensor (ms)
const int sampleCount = 5;  // Jumlah sample untuk averaging
```

🚀 Tips Penggunaan

💧 Optimalisasi untuk Jenis Tanaman Berbeda

```bash
# Tanaman suka air (pakai threshold rendah)
set 300

# Tanaman tahan kering (pakai threshold tinggi)
set 700
```

🔧 Troubleshooting Common Issues

Problem: Sensor membaca nilai aneh (-1)
Solution:Periksa koneksi sensor, mungkin kabel longgar

Problem: Motor tidak menyala
Solution:Cek koneksi relay dan pastikan mode tidak "off"

Problem: Serial Monitor tidak merespon
Solution:Pastikan baud rate 9600 dan port Arduino benar

🤝 Kontribusi

Contributions are welcome! 🎊

1. Fork project ini
2. Buat feature branch (git checkout -b feature/AmazingFeature)
3. Commit changes (git commit -m 'Add some AmazingFeature')
4. Push to branch (git push origin feature/AmazingFeature)
5. Buat Pull Request

📄 Lisensi

Distributed under the MIT License. See LICENSE for more information.

👨‍💻 Developer

Hanxthc - GitHub Profile

Jika project ini membantu Anda, jangan lupa beri ⭐ di repository ini!

---

<div align="center">

💡 Ingat Selalu Cek Keadaan Tanaman Secara Berkala!

Sistem otomatis membantu, tetapi perhatian manusia tetap yang terbaik 🌟

</div>

---

Terakhir diperbarui: December 2024 | Firmware Version: 3.1
