#include <Arduino.h>
#include <PS4Controller.h>
#include <IcsHardSerialClass.h>

const byte EN_PIN = 2;
const long BAUDRATE = 115200;
const int TIMEOUT = 10;    //通信できてないか確認用にわざと遅めに設定

IcsHardSerialClass krs(&Serial, EN_PIN, BAUDRATE, TIMEOUT); //インスタンス＋ENピン(2番ピン)およびUARTの指定

void reset_position();
void forward(int right_leg_id, int left_leg_id);
void right_rotation();
void left_rotation();

void setup() {
  Serial.begin(115200);
  PS4.begin("08:B6:1F:ED:4B:E2");
  krs.begin();  //サーボモータの通信初期設定
  reset_position(); // サーボの初期位置設定
}

void loop() {
  if (PS4.isConnected()) {
      if (PS4.Up()) {
        forward(0, 10);
      }
      if (PS4.Right()) {
          krs.setPos(24, 7500 + 250 -500);
      }
      if (PS4.Down()) {
          krs.setPos(24, 7500 + 250);
      }
      if (PS4.Left()) {
          krs.setPos(24, 7500 + 250 + 500);
      }
      if (PS4.Cross()) {
        reset_position();
      }
      if (PS4.L1()) {
        left_rotation();
      }
      if (PS4.R1()) {
        right_rotation();
      }
      if (PS4.Circle()) {
        if (PS4.Up()) {
          forward(20, 0);
        }
        if (PS4.Right()) {
          krs.setPos(14, 7500 + 250 - 500);
        }
        if (PS4.Down()) {
          krs.setPos(14, 7500 + 250);
        }
        if (PS4.Left()) {
          krs.setPos(14, 7500 + 250 + 500);
        }
      }
      if (PS4.Square()) {
        if (PS4.Up()) {
          forward(10, 20);
        }
        if (PS4.Right()) {
          krs.setPos(4, 7500 + 250 - 500);
        }
        if (PS4.Down()) {
          krs.setPos(4, 7500 + 250);
        }
        if (PS4.Left()) {
          krs.setPos(4, 7500 + 250 + 500);
        }
      }
  }
}


void reset_position() {
  for (int id = 0; id <= 24; id += 10) {
    krs.setPos(id, 7500);
    krs.setPos(id + 1, 7500 - 1500);
    krs.setPos(id + 2, 7500);
    krs.setPos(id + 3, 7500 - 1000);
    krs.setPos(id + 4, 7500 + 250);
  }
}

void forward(int right_leg_id, int left_leg_id) {
  krs.setPos(right_leg_id, 7500 + 1000);
  krs.setPos(left_leg_id, 7500 - 1000);
  delay(500);
  krs.setPos(right_leg_id, 7500 - 1500);
  krs.setPos(left_leg_id, 7500 + 1500);
  delay(500);
}

void right_rotation() {
  krs.setPos(4, 7500 - 1250);
  krs.setPos(14, 7500 - 1250 );
  krs.setPos(24, 7500 - 1250 );
  delay(500);
  krs.setPos(2, 7500);
  krs.setPos(12, 7500);
  krs.setPos(22, 7500);
  krs.setPos(3, 7500 - 1000);
  krs.setPos(13, 7500 - 1000);
  krs.setPos(23, 7500 - 1000);
  delay(500);
  krs.setPos(4, 7500 + 1750);
  krs.setPos(14, 7500 + 1750);
  krs.setPos(24, 7500 + 1750);
  delay(500);
  krs.setPos(2, 7500 - 1500);
  krs.setPos(12, 7500 - 1500);
  krs.setPos(22, 7500 - 1500);
  krs.setPos(3, 7500 - 2500 );
  krs.setPos(13, 7500 - 2500 );
  krs.setPos(23, 7500 - 2500);
  delay(500);
}

void left_rotation() {
  krs.setPos(4, 7500 + 1750);
  krs.setPos(14, 7500 + 1750);
  krs.setPos(24, 7500 + 1750);
  delay(500);
  krs.setPos(2, 7500);
  krs.setPos(12, 7500);
  krs.setPos(22, 7500);
  krs.setPos(3, 7500 - 1000);
  krs.setPos(13, 7500 - 1000);
  krs.setPos(23, 7500 - 1000);
  delay(500);
  krs.setPos(4, 7500 - 1250);
  krs.setPos(14, 7500 - 1250 );
  krs.setPos(24, 7500 - 1250 );
  delay(500);
  krs.setPos(2, 7500 - 1500);
  krs.setPos(12, 7500 - 1500);
  krs.setPos(22, 7500 - 1500);
  krs.setPos(3, 7500 - 2500 );
  krs.setPos(13, 7500 - 2500 );
  krs.setPos(23, 7500 - 2500);
  delay(500);
}

// Serial.print(F("\r\nLeft"));