#include <Arduino.h>
#include <IcsHardSerialClass.h>
#include <PS4Controller.h>

const byte EN_PIN = 2;
const long BAUDRATE = 115200;
const int TIMEOUT = 10;

IcsHardSerialClass krs(&Serial, EN_PIN, BAUDRATE, TIMEOUT); // インスタンス＋ENピン(2番ピン)およびUARTの指定

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
  int designatedPos0, int designatedPos1, int designatedPos2, int designatedPos3, int designatedPos4,
  int designatedPos10, int designatedPos11, int designatedPos12, int designatedPos13, int designatedPos14,
  int designatedPos20, int designatedPos21, int designatedPos22, int designatedPos23, int designatedPos24,
  int delayTime, int interpolation
) {
  int currentPos[15];
  int targetPos[15];
  int homePos[15] = {0};
  int designatedPos[15] = {
    designatedPos0, designatedPos1, designatedPos2, designatedPos3, designatedPos4,
    designatedPos10, designatedPos11, designatedPos12, designatedPos13, designatedPos14,
    designatedPos20, designatedPos21, designatedPos22, designatedPos23, designatedPos24
  };
//targetpos[]に目標値を代入
  for (int j = 0; j < 5; j++) {
    targetPos[j] = 7500 + homePos[j] + designatedPos[j];
    targetPos[j + 5] = 7500 + homePos[j + 5] + designatedPos[j + 5];
    targetPos[j + 10] = 7500 + homePos[j + 10] + designatedPos[j + 10];

    currentPos[j] = krs.getPos(j); //+1?

    targetPos[j] -= currentPos[j];
    targetPos[j] /= interpolation;
  }

  // 配列の中身を出力
  // Serial.println("currentPos配列の中身:");
  // for (int i = 0; i < 15; i++) {
  //   Serial.print("Index ");
  //   Serial.print(i);
  //   Serial.print(": ");
  //   Serial.println(currentPos[i]); // 値を1行ずつ出力
  // }

  //   Serial.println("目標配列の中身:");
  //   for (int i = 0; i < 15; i++) {
  //     Serial.print("Index ");
  //     Serial.print(i);
  //     Serial.print(": ");
  //     Serial.println(targetPos[i]); // 値を1行ずつ出力
  //   }

for (int o = 0; o < interpolation; o++) {
  for (int p = 0; p < 5; p++) {
    currentPos[p] = currentPos[p] + targetPos[p];
    krs.setPos(p, currentPos[p]);
    krs.setPos(p+10, currentPos[p+5]);
    krs.setPos(p+20, currentPos[p+10]);
  }
  delay(delayTime);
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
  krs.begin(); // サーボモータの通信初期設定
  resetPosition();
}

void loop() {
  static Mode mode = front_leg;

    if (PS4.isConnected()) {
      if (PS4.Share()) {
        mode = ChangeMode(mode);
        resetPosition();
      }
      if (mode == front_leg) {
        PS4.setLed(255, 0, 0);
        if (PS4.Up()) {
          // forwardImp(0, 10, 4, 14);
          controlPos(
            -1000, 0, 0, 0, 0,  // id = 0
            -1000, 0, 0, 0, 0,  // id = 10
            0, 0, 0, 0, 0,   // id = 20
            20, 60
          );
          // controlPos(
          //   0, 0, 0, 0, 0,  // id = 0
          //   0, 0, 0, 0, 0,  // id = 10
          //   0, 0, 0, 0, 0,   // id = 20
          //   20, 60
          // );
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
        // resetPosition();
          controlPos(
            0, -1500, 0, -1000, 250,  // id = 0
            0, -1500, 0, -1000, 250,  // id = 10
            0, -1500, 0, -1000, 250,   // id = 20
            20, 60
          );
      }
      if (PS4.L1()) {
        leftRotation();
      }
      if (PS4.R1()) {
        rightRotation();
      }
      PS4.sendToController();
    } else {
      resetPosition();
      delay(1000);
    }
  }