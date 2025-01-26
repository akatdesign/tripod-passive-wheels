#include <Arduino.h>
#include <IcsHardSerialClass.h>
#include <PS4Controller.h>

const byte EN_PIN = 2;
const long BAUDRATE = 115200;
const int TIMEOUT = 10;

IcsHardSerialClass krs(&Serial, EN_PIN, BAUDRATE, TIMEOUT); // インスタンス＋ENピンおよびUARTの指定

enum Mode { front_leg, right_leg, left_leg, reverse_leg };

Mode ChangeMode(Mode current) {
  if (current == front_leg) {
    return right_leg;
  } else if (current == right_leg) {
    return left_leg;
  } else if (current == left_leg) {
    return reverse_leg;
  } else if (current == reverse_leg) {
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

void reversePosition() {
  for (int id = 0; id <= 24; id += 10) {
    krs.setPos(id, 7500);
    krs.setPos(id + 1, 7500 - 1500);
    krs.setPos(id + 2, 7500 + 3000);
    krs.setPos(id + 3, 7500 - 3500);
    krs.setPos(id + 4, 7500 + 250);
  }
}

void zeroPosition() {
  for (int id = 0; id <= 24; id += 10) {
    krs.setPos(id, 7500);
    krs.setPos(id + 1, 7500);
    krs.setPos(id + 2, 7500);
    krs.setPos(id + 3, 7500);
    krs.setPos(id + 4, 7500);
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
  int homePos[15]; // = {0} defalt 7500
  homePos[0] = 0;
  homePos[1] = -1500;
  homePos[2] = 0;
  homePos[3] = -1000;
  homePos[4] = 250; //id 4
  homePos[5] = 0;
  homePos[6] = -1500;
  homePos[7] = 0;
  homePos[8] = -1000;
  homePos[9] = 250; //id 14
  homePos[10] = 0;
  homePos[11] = -1500;
  homePos[12] = 0;
  homePos[13] = -1000;
  homePos[14] = 250; //id 24
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

    currentPos[j] = krs.getPos(j);
    currentPos[j + 5] = krs.getPos(j + 10);
    currentPos[j + 10] = krs.getPos(j + 20);

    targetPos[j] -= currentPos[j];
    targetPos[j] /= interpolation;
    targetPos[j + 5] -= currentPos[j + 5];
    targetPos[j + 5] /= interpolation;
    targetPos[j + 10] -= currentPos[j + 10];
    targetPos[j + 10] /= interpolation;
  }

  //配列の中身を出力
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
// int postest[2];

void forward(int left_leg_id, int right_leg_id) {
  // postest[1] = krs.getStrc(right_leg_id);
  // postest[2] = krs.getStrc(left_leg_id);
  // Serial.println(postest[1]);
  // Serial.println(postest[2]);
  krs.setPos(left_leg_id, 7500 + 1000);
  krs.setPos(right_leg_id, 7500 - 1000);
  delay(500);
  krs.setPos(left_leg_id, 7500 - 1500);
  krs.setPos(right_leg_id, 7500 + 1500);
  delay(500);
}

void forwardImp(int left_leg_id, int right_leg_id, int left_tip_leg_id, int right_tip_leg_id) {
  krs.setPos(left_leg_id, 7500 + 1000);
  krs.setPos(right_leg_id, 7500 - 1000);
  krs.setPos(left_tip_leg_id, 7500 + 2000);
  krs.setPos(right_tip_leg_id, 7500 - 2000);
  delay(500);
  krs.setPos(right_tip_leg_id, 7500);
  krs.setPos(left_tip_leg_id, 7500);
  delay(500);
  krs.setPos(left_leg_id, 7500 - 1500);
  krs.setPos(right_leg_id, 7500 + 1500);
  krs.setPos(left_tip_leg_id, 7500 + 500);  //why
  krs.setPos(right_tip_leg_id, 7500);
  delay(500);
}

void forwardOpenClose(int left_leg_id, int right_leg_id, int left_tip_leg_id, int right_tip_leg_id, int delay_time) {
  krs.setPos(left_tip_leg_id, 7500 - 1000);//ハ
  krs.setPos(right_tip_leg_id, 7500 + 1000);
  delay(delay_time);
  krs.setPos(left_leg_id, 7500 - 2000);//閉じる
  krs.setPos(right_leg_id, 7500 + 2000);
  delay(delay_time);
  krs.setPos(left_tip_leg_id, 7500 + 2000);//逆ハ
  krs.setPos(right_tip_leg_id, 7500 - 2000);
  delay(delay_time);
  krs.setPos(left_leg_id, 7500 + 1000);//開く ±1000なしで昨年度
  krs.setPos(right_leg_id, 7500 - 1000);
  delay(delay_time);
}

void backward(int left_leg_id, int right_leg_id, int left_tip_leg_id, int right_tip_leg_id, int delay_time) {
  krs.setPos(left_tip_leg_id, 7500 + 1000);//ハ
  krs.setPos(right_tip_leg_id, 7500 - 1000);
  delay(delay_time);
  krs.setPos(left_leg_id, 7500 - 1500);//閉じる
  krs.setPos(right_leg_id, 7500 + 1500);
  delay(delay_time);
  krs.setPos(left_tip_leg_id, 7500 - 1000);//逆ハ
  krs.setPos(right_tip_leg_id, 7500 + 1000);
  delay(delay_time);
  krs.setPos(left_leg_id, 7500);//開く
  krs.setPos(right_leg_id, 7500);
  delay(delay_time);
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

void reverseRightRotation() {
  krs.setPos(4, 7500 - 1250);
  krs.setPos(14, 7500 - 1250);
  krs.setPos(24, 7500 - 1250);
  delay(500);
  krs.setPos(2, 7500 + 3000);
  krs.setPos(12, 7500 + 3000);
  krs.setPos(22, 7500 + 3000);
  krs.setPos(3, 7500 - 3500);
  krs.setPos(13, 7500 - 3500);
  krs.setPos(23, 7500 - 3500);
  delay(500);
  krs.setPos(4, 7500 + 1750);
  krs.setPos(14, 7500 + 1750);
  krs.setPos(24, 7500 + 1750);
  delay(500);
  krs.setPos(2, 7500 + 4000);//max
  krs.setPos(12, 7500 + 4000);
  krs.setPos(22, 7500 + 4000);
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

void reverseLeftRotation() {
  krs.setPos(4, 7500 + 1750);
  krs.setPos(14, 7500 + 1750);
  krs.setPos(24, 7500 + 1750);
  delay(500);
  krs.setPos(2, 7500 + 3000);
  krs.setPos(12, 7500 + 3000);
  krs.setPos(22, 7500 + 3000);
  krs.setPos(3, 7500 - 3500);
  krs.setPos(13, 7500 - 3500);
  krs.setPos(23, 7500 - 3500);
  delay(500);
  krs.setPos(4, 7500 - 1250);
  krs.setPos(14, 7500 - 1250);
  krs.setPos(24, 7500 - 1250);
  delay(500);
  krs.setPos(2, 7500 + 4000);
  krs.setPos(12, 7500 + 4000);
  krs.setPos(22, 7500 + 4000);
  krs.setPos(3, 7500 - 2500);
  krs.setPos(13, 7500 - 2500);
  krs.setPos(23, 7500 - 2500);
  delay(500);
}

void setup() {
  Serial.begin(115200);
  PS4.begin("08:B6:1F:ED:4B:E2");
  krs.begin(); // サーボモータの通信初期設定
  zeroPosition();
  delay(500);
  resetPosition();
  // reversePosition(); 
}

void loop() {
  static Mode mode = front_leg;

    if (PS4.isConnected()) {
      if (PS4.Share()) {
        mode = ChangeMode(mode);
        if (mode == reverse_leg) {
          reversePosition();
        } else {
          resetPosition();
        }
      }
      if (mode == front_leg) {
        PS4.setLed(255, 0, 0);
        if (PS4.Up()) {
          // forward(0, 10);
          // forwardImp(0, 10, 4, 14);
          forwardOpenClose(0, 10, 4, 14, 100);
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
      }else if (mode == reverse_leg) {
        PS4.setLed(255, 255, 0);
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
        if (PS4.R2()) {
          reverseRightRotation();
        }
        if (PS4.L2()) {
          reverseLeftRotation();
        }
        if (PS4.Triangle()) {
          reversePosition();
        }
      }
      if (PS4.Cross()) {
        resetPosition();
        // reversePosition();
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