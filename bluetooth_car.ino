#include <AFMotor.h>
#include <SoftwareSerial.h>

// Bluetooth pinleri: RX=A5, TX=A4
SoftwareSerial bluetooth(A5, A4); 

// Motor Tanımlamaları
AF_DCMotor solArka(1); 
AF_DCMotor solOn(2);
AF_DCMotor sagArka(3);
AF_DCMotor sagOn(4);

char komut;
int tamHiz = 255;
int donusHizi = 120; // Kavisli dönüşte içte kalan tekerleklerin hızı

void setup() {
  bluetooth.begin(9600);
  dur();
}

void loop() {
  if (bluetooth.available() > 0) {
    komut = bluetooth.read();
    
    switch (komut) {
      case 'F': ileri(); break;
      case 'B': geri();  break;
      case 'L': tamSol();   break; // Olduğu yerde sol
      case 'R': tamSag();   break; // Olduğu yerde sağ
      case 'G': ileriSol(); break; // İleri giderken sola meyilli
      case 'I': ileriSag(); break; // İleri giderken sağa meyilli
      case 'H': geriSol();  break; // Geri giderken sola meyilli
      case 'J': geriSag();  break; // Geri giderken sağa meyilli
      case 'S': dur();      break;
      case 'X': dur();      break;
    }
  }
}

// --- HAREKET FONKSİYONLARI ---

void ileri() {
  hizAyarla(tamHiz, tamHiz);
  solArka.run(FORWARD); solOn.run(FORWARD);
  sagArka.run(FORWARD); sagOn.run(FORWARD);
}

void geri() {
  hizAyarla(tamHiz, tamHiz);
  solArka.run(BACKWARD); solOn.run(BACKWARD);
  sagArka.run(BACKWARD); sagOn.run(BACKWARD);
}

void ileriSol() {
  // Sola meyilli gitmek için sol motorları yavaşlat, sağları tam hız yap
  hizAyarla(donusHizi, tamHiz);
  solArka.run(FORWARD); solOn.run(FORWARD);
  sagArka.run(FORWARD); sagOn.run(FORWARD);
}

void ileriSag() {
  // Sağa meyilli gitmek için sağ motorları yavaşlat, solları tam hız yap
  hizAyarla(tamHiz, donusHizi);
  solArka.run(FORWARD); solOn.run(FORWARD);
  sagArka.run(FORWARD); sagOn.run(FORWARD);
}

void tamSol() {
  hizAyarla(tamHiz, tamHiz);
  solArka.run(BACKWARD); solOn.run(BACKWARD);
  sagArka.run(FORWARD);  sagOn.run(FORWARD);
}

void tamSag() {
  hizAyarla(tamHiz, tamHiz);
  solArka.run(FORWARD);  solOn.run(FORWARD);
  sagArka.run(BACKWARD); sagOn.run(BACKWARD);
}

void geriSol() {
  hizAyarla(donusHizi, tamHiz);
  solArka.run(BACKWARD); solOn.run(BACKWARD);
  sagArka.run(BACKWARD); sagOn.run(BACKWARD);
}

void geriSag() {
  hizAyarla(tamHiz, donusHizi);
  solArka.run(BACKWARD); solOn.run(BACKWARD);
  sagArka.run(BACKWARD); sagOn.run(BACKWARD);
}

void dur() {
  solArka.run(RELEASE); solOn.run(RELEASE);
  sagArka.run(RELEASE); sagOn.run(RELEASE);
}

// Yardımcı fonksiyon: Hızları tek seferde ayarlar
void hizAyarla(int solHiz, int sagHiz) {
  solArka.setSpeed(solHiz);
  solOn.setSpeed(solHiz);
  sagArka.setSpeed(sagHiz);
  sagOn.setSpeed(sagHiz);
}