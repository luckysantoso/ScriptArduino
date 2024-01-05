// Program untuk mengukur volume menggunakan mikrometer pump
#include <Stepper.h>

// Definisi Pin untuk pompa mikrometer
const int stepPin = 2;  // Pin langkah (Step)
const int dirPin = 3;   // Pin arah (Direction)

// Karakteristik pompa mikrometer
const float stepsPerRevolution = 200;  // Langkah per revolusi
const float mLPerStep = 0.01;           // Volume yang dipompa per langkah (misalnya, 0.01 mL)

// Fungsi untuk mengukur dan mengontrol volume
void pumpVolume(float targetVolume) {
  // Menghitung jumlah langkah yang diperlukan
  int stepsRequired = int(targetVolume / mLPerStep);

  // Mengatur arah pompa sesuai dengan volume yang akan dipompa
  if (targetVolume > 0) {
    digitalWrite(dirPin, HIGH); // Maju
  } else {
    digitalWrite(dirPin, LOW); // Mundur (jika diperlukan)
  }

  // Menggerakkan pompa
  for (int i = 0; i < stepsRequired; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);  // Delay untuk mengendalikan kecepatan (sesuaikan jika diperlukan)
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);  // Delay untuk mengendalikan kecepatan (sesuaikan jika diperlukan)
  }
}

void setup() {
  // Mengatur pin sebagai OUTPUT
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  // Inisialisasi Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Contoh penggunaan: Mengukur dan memompa 1 mL
  float targetVolume = 1.0;  // Ganti dengan volume yang diinginkan dalam mL
  pumpVolume(targetVolume);

  // Menampilkan informasi ke Serial Monitor
  Serial.print("Volume yang dipompa: ");
  Serial.print(targetVolume);
  Serial.println(" mL");

  // Menunggu sejenak sebelum mengulangi
  delay(2000);
}
