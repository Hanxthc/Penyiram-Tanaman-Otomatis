#include <EEPROM.h>

// === Sistem Penyiraman Otomatis ===
// Firmware v3.1 | Author: HanzNTahlah

// === Pin & Konfigurasi ===
const int sensorPin = A0;   
const int motorPin  = 7;    
const int ledMerah  = 2;    
const int ledKuning = 3;    
const int ledHijau  = 4;    

int threshold = 500;  
String mode = "auto";
const int addrThreshold = 0;  

// Buffer untuk moving average
const int sampleCount = 5;
int buffer[sampleCount];
int indexSample = 0;

// Delay setting
unsigned long lastSensor = 0;
int delaySensor = 200;
int lastKelembaban = 0;

bool monitorAktif = false;

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(ledMerah, OUTPUT);
  pinMode(ledKuning, OUTPUT);
  pinMode(ledHijau, OUTPUT);

  Serial.begin(9600);

  // Animasi startup
  animasiStartup();

  // Info booting
  Serial.println("\n=====================================");
  Serial.println("   Sistem Penyiraman Otomatis");
  Serial.println("   Firmware v3.1 | Author: HanzNTahlah");
  Serial.println("=====================================\n");

  Serial.println("Command list:");
  Serial.println("   set <angka>         -> set threshold (1-1023)");
  Serial.println("   mode auto/on/off    -> ubah mode kerja");
  Serial.println("   monitor on/off      -> nyalain / matiin realtime print");
  Serial.println("   delay sensor <ms>   -> ubah jeda sampling sensor");
  Serial.println("   status              -> cek kondisi sekarang");
  Serial.println("   help                -> list command\n");
  Serial.println("=====================================\n");

  // Load threshold dari EEPROM
  threshold = EEPROM.read(addrThreshold) * 4; 
  if (threshold <= 0 || threshold > 1023) threshold = 500;

  Serial.print(">> Threshold awal: "); Serial.println(threshold);
  Serial.print(">> Mode awal: "); Serial.println(mode);

  // Init buffer
  for (int i = 0; i < sampleCount; i++) buffer[i] = analogRead(sensorPin);
}

void loop() {
  unsigned long now = millis();

  if (now - lastSensor >= delaySensor) {
    lastSensor = now;
    lastKelembaban = bacaSensor();

    if (monitorAktif) {
      printStatus();
    }
  }

  cekSerial();
}

// === Print status santai ===
void printStatus() {
  resetLED();
  Serial.print("[DATA] Sensor: ");

  if (lastKelembaban < 0) {
    setStatus(ledKuning, motorPin, LOW, "[!] Sensor ngaco (anomali)");
    return;
  }

  // hitung persen kekeringan
  int persen = map(lastKelembaban, 0, 1023, 0, 100);
  Serial.print(lastKelembaban);
  Serial.print(" | Kering: ");
  Serial.print(persen);
  Serial.print("%");

  if (mode == "on") {
    setStatus(ledHijau, motorPin, HIGH, "[MODE] ON paksa");
  } else if (mode == "off") {
    setStatus(ledMerah, motorPin, LOW, "[MODE] OFF paksa");
  } else { // auto
    if (lastKelembaban > threshold) {
      setStatus(ledHijau, motorPin, HIGH, "[AUTO] Kering → Motor ON");
    } else {
      setStatus(ledMerah, motorPin, LOW, "[AUTO] Basah → Motor OFF");
    }
  }
}

// === Fungsi bantu ===
void resetLED() {
  digitalWrite(ledMerah, LOW);
  digitalWrite(ledKuning, LOW);
  digitalWrite(ledHijau, LOW);
}

void setStatus(int led, int motor, int motorState, String msg) {
  digitalWrite(led, HIGH);
  digitalWrite(motor, motorState);
  Serial.print(" -> ");
  Serial.println(msg);
}

void cekSerial() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.startsWith("set")) {
      int newThreshold = input.substring(4).toInt();
      if (newThreshold > 0 && newThreshold <= 1023) {
        threshold = newThreshold;
        EEPROM.write(addrThreshold, threshold / 4);
        Serial.print("[OK] Threshold diubah ke: ");
        Serial.println(threshold);
      } else {
        Serial.println("[ERR] Salah input! Gunakan: set <1-1023>");
      }
    } 
    else if (input.startsWith("mode")) {
      String newMode = input.substring(5);
      newMode.toLowerCase();
      if (newMode == "auto" || newMode == "on" || newMode == "off") {
        mode = newMode;
        Serial.print("[OK] Mode diubah ke: "); Serial.println(mode);
      } else {
        Serial.println("[ERR] Mode salah! Pilih: auto / on / off");
      }
    }
    else if (input.startsWith("monitor")) {
      String arg = input.substring(8);
      arg.toLowerCase();
      if (arg == "on") {
        monitorAktif = true;
        Serial.println("[INFO] Monitor realtime aktif");
      } else if (arg == "off") {
        monitorAktif = false;
        Serial.println("[INFO] Monitor realtime dimatiin");
      } else {
        Serial.println("[ERR] Gunakan: monitor on / off");
      }
    }
    else if (input.startsWith("delay sensor")) {
      int newDelay = input.substring(12).toInt();
      if (newDelay >= 50) {
        delaySensor = newDelay;
        Serial.print("[OK] Delay sensor diubah ke: ");
        Serial.print(delaySensor); Serial.println(" ms");
      } else {
        Serial.println("[ERR] Minimal 50 ms biar stabil");
      }
    }
    else if (input == "status") {
      printStatus();
    }
    else if (input == "help") {
      Serial.println("Command List:");
      Serial.println("   set <angka>         -> set threshold (1-1023)");
      Serial.println("   mode auto/on/off    -> ubah mode kerja");
      Serial.println("   monitor on/off      -> nyalain / matiin realtime print");
      Serial.println("   delay sensor <ms>   -> ubah jeda sampling sensor");
      Serial.println("   status              -> cek kondisi sekarang");
      Serial.println("   help                -> list command");
    }
  }
}

void animasiStartup() {
  int delayTime = 150;
  int leds[] = {ledMerah, ledKuning, ledHijau};
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      digitalWrite(leds[j], HIGH); delay(delayTime);
      digitalWrite(leds[j], LOW);
    }
  }
  for (int j = 0; j < 3; j++) digitalWrite(leds[j], HIGH);
  delay(300);
  for (int j = 0; j < 3; j++) digitalWrite(leds[j], LOW);
}

// === Moving Average + Deteksi Anomali ===
int bacaSensor() {
  buffer[indexSample] = analogRead(sensorPin);
  indexSample = (indexSample + 1) % sampleCount;

  long total = 0;
  for (int i = 0; i < sampleCount; i++) total += buffer[i];
  int avg = total / sampleCount;

  // deteksi anomali
  int last = buffer[(indexSample - 1 + sampleCount) % sampleCount];
  if (abs(last - avg) > 300) {
    return -1;
  }

  return avg;
}
