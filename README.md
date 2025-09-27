# 🌱 Sistem Penyiraman Otomatis  
**Firmware v3.1 | Author: Hanxthc**

---

## 📖 Deskripsi
Proyek ini adalah **sistem penyiram tanaman otomatis berbasis Arduino Nano/UNO**.  
Alat ini menggunakan **sensor kelembaban tanah** untuk mendeteksi kondisi media tanam,  
dan mengontrol **motor pompa air** secara otomatis sesuai kebutuhan.

Tujuan dari firmware ini:  
- **Membantu menyiram tanaman otomatis** biar nggak lupa.  
- **Ngasih kontrol manual** (mode ON / OFF).  
- **Ngasih deteksi anomali sensor** (misal sensor rusak / data ngaco).  
- **Fleksibel** karena threshold, mode, dan delay bisa diatur lewat Serial Monitor.

---

## ⚙️ Fitur Utama
- **3 Mode Operasi**  
  - `auto` → motor nyala otomatis kalau tanah kering.  
  - `on` → motor nyala paksa.  
  - `off` → motor mati paksa.  

- **Atur Threshold**  
  Batas kelembaban tanah bisa diubah (1–1023).  

- **Realtime Monitor**  
  Bisa aktif/nonaktif sesuai keinginan (`monitor on/off`).  

- **Delay Fleksibel**  
  Atur jeda pembacaan sensor (`delay sensor <ms>`).  

- **Deteksi Anomali**  
  Kalau data sensor tiba-tiba lompat jauh (ngaco), sistem kasih warning `[!] Sensor ngaco`.  

- **EEPROM Support**  
  Threshold terakhir tersimpan otomatis walau board dimatikan.  

- **Animasi Startup**  
  LED indikator nyala-berurutan pas booting.  

---

## 🔌 Wiring (Contoh Setup)
| Pin Arduino | Koneksi          |
|-------------|------------------|
| A0          | Sensor kelembaban |
| D7          | Motor / Pompa via relay |
| D2          | LED Merah (Basah) |
| D3          | LED Kuning (Error) |
| D4          | LED Hijau (Kering) |

---

## 💻 Command List (Serial Monitor)
Ketik di **Serial Monitor (9600 baud, Newline)**:

| Command | Fungsi |
|---------|--------|
| `set <angka>` | Set threshold kelembaban (1–1023) |
| `mode auto` | Mode otomatis (default) |
| `mode on` | Motor nyala paksa |
| `mode off` | Motor mati paksa |
| `monitor on` | Aktifkan realtime monitoring |
| `monitor off` | Nonaktifkan realtime monitoring |
| `delay sensor <ms>` | Atur jeda sampling sensor (default 200 ms) |
| `status` | Tampilkan status sensor & motor sekarang |
| `help` | Tampilkan daftar command |

---

## 🟢 Contoh Alur Pemakaian
1. Upload kode ke Arduino Nano/UNO lewat Arduino IDE.  
2. Hubungkan sensor & motor sesuai tabel wiring.  
3. Buka **Serial Monitor** (9600 baud, Newline).  
4. Saat startup akan muncul tampilan:  

