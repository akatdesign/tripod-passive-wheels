#include <Arduino.h>
#include <IcsHardSerialClass.h>
#include <PS4Controller.h>

const byte EN_PIN = 2;
const long BAUDRATE = 115200;
const int TIMEOUT = 10; // 通信できてないか確認用にわざと遅めに設定

IcsHardSerialClass
    krs(&Serial, EN_PIN, BAUDRATE,
        TIMEOUT); // インスタンス＋ENピン(2番ピン)およびUARTの指定

enum Mode { front_leg, right_leg, left_leg };

Mode ChangeMode(Mode current) {
  if (current == front_leg) {
    return right_leg;
  } else if (current == right_leg) {
    return left_leg;
  } else if (current == left_leg) {
    return front_leg;
  } else {
    return front_leg; // デフォルトの戻り値
  }
}

void resetPosition() {
  for (int id = 0; id <= 24; id += 10) {
    krs.setPos(id, 7500);
    krs.setPos(id + 1, 7500 - 1500);
    krs.setPos(id + 2, 7500);
    krs.setPos(id + 3, 7500 - 1000);
    krs.setPos(id + 4, 7500 + 250);
  }
}

void controlPos(
  int designatedPos0,
  int designatedPos1,
  int designatedPos2,
  int designatedPos3,
  int designatedPos4,
  int designatedPos10,
  int designatedPos11,
  int designatedPos12,
  int designatedPos13,
  int designatedPos14,
  int designatedPos20,
  int designatedPos21,
  int designatedPos22,
  int designatedPos23,
  int designatedPos24,
  int dtime,
  int interpolation
){
  int i = 0;
  int c = 0;

  int pos[15];
  int targetPos[15];
  int homePos[15];
  int designatedPos[15];

  homePos[0] = 0;
  homePos[1] = 0;
  homePos[2] = 0;
  homePos[3] = 0;
  homePos[4] = 0;
  homePos[5] = 0;
  homePos[6] = 0;
  homePos[7] = 0;
  homePos[8] = 0;
  homePos[9] = 0;
  homePos[10] = 0;
  homePos[11] = 0;
  homePos[12] = 0;
  homePos[13] = 0;
  homePos[14] = 0;

    // 指定値を配列に代入
  designatedPos[0] = designatedPos0;
  designatedPos[1] = designatedPos1;
  designatedPos[2] = designatedPos2;
  designatedPos[3] = designatedPos3;
  designatedPos[4] = designatedPos4;
  designatedPos[5] = designatedPos10;
  designatedPos[6] = designatedPos11;
  designatedPos[7] = designatedPos12;
  designatedPos[8] = designatedPos13;
  designatedPos[9] = designatedPos14;
  designatedPos[10] = designatedPos20;
  designatedPos[11] = designatedPos21;
  designatedPos[12] = designatedPos22;
  designatedPos[13] = designatedPos23;
  designatedPos[14] = designatedPos24;

  for (int i = 0; i < 15; i++) {
    targetPos[i] = 7500 + homePos[i] + designatedPos[i];
    pos[i] = krs.getPos(i + 1); // 現在値を取得
    targetPos[i] -= pos[i];     // 現在値から目標値への差分を計算
    targetPos[i] /= interpolation; // 補間回数で割る
  }

  // 補間動作でモーターを動かす
  for (int step = 0; step < interpolation; step++) {
    for (int i = 0; i < 15; i++) {
      pos[i] += targetPos[i];      // 補間ステップ分移動
      krs.setPos(i + 1, pos[i]);   // 新しい位置を設定
    }
    delay(dtime); // 指定した間隔を空ける
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

void forwardImp(int right_leg_id, int left_leg_id, int right_tip_leg_id, int left_tip_leg_id) {
  krs.setPos(right_leg_id, 7500 + 1000);
  krs.setPos(left_leg_id, 7500 - 1000);
  krs.setPos(right_tip_leg_id, 7500 + 1000);
  krs.setPos(left_tip_leg_id, 7500 - 1000);
  delay(500);
  krs.setPos(right_leg_id, 7500 - 1500);
  krs.setPos(left_leg_id, 7500 + 1500);
  krs.setPos(right_tip_leg_id, 7500 - 100);
  krs.setPos(left_tip_leg_id, 7500 + 100);
  delay(500);
}

void rightRotation() {
  krs.setPos(4, 7500 - 1250);
  krs.setPos(14, 7500 - 1250);
  krs.setPos(24, 7500 - 1250);
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
  krs.setPos(3, 7500 - 2500);
  krs.setPos(13, 7500 - 2500);
  krs.setPos(23, 7500 - 2500);
  delay(500);
}

void leftRotation() {
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
  krs.setPos(14, 7500 - 1250);
  krs.setPos(24, 7500 - 1250);
  delay(500);
  krs.setPos(2, 7500 - 1500);
  krs.setPos(12, 7500 - 1500);
  krs.setPos(22, 7500 - 1500);
  krs.setPos(3, 7500 - 2500);
  krs.setPos(13, 7500 - 2500);
  krs.setPos(23, 7500 - 2500);
  delay(500);
}

void setup() {
  Serial.begin(115200);
  PS4.begin("08:B6:1F:ED:4B:E2");
  krs.begin();     // サーボモータの通信初期設定
  resetPosition(); // サーボの初期位置設定
}

void loop() {
  Mode mode = front_leg;

  while (true) {
    if (PS4.isConnected()) {
      if (PS4.Share()) {
        mode = ChangeMode(mode);
        resetPosition();
      }
      if (mode == front_leg) {
        PS4.setLed(255, 0, 0);
        if (PS4.Up()) {
          forwardImp(0, 10, 4, 14);
        }
        if (PS4.Right()) {
          krs.setPos(24, 7500 + 250 - 500);
        }
        if (PS4.Down()) {
          krs.setPos(24, 7500 + 250);
        }
        if (PS4.Left()) {
          krs.setPos(24, 7500 + 250 + 500);
        }
      } else if (mode == right_leg) {
        PS4.setLed(0, 255, 0);
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
      } else if (mode == left_leg) {
        PS4.setLed(0, 0, 255);
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
      if (PS4.Cross()) {
        resetPosition();
      }
      if (PS4.L1()) {
        leftRotation();
      }
      if (PS4.R1()) {
        rightRotation();
      }
      PS4.sendToController();
    }
  }
}