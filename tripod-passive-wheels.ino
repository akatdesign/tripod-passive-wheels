#include <PS4Controller.h>
#include <IcsHardSerialClass.h>

const byte EN_PIN = 2;
const long BAUDRATE = 115200;
const int TIMEOUT = 10;    //通信できてないか確認用にわざと遅めに設定

IcsHardSerialClass krs(&Serial, EN_PIN, BAUDRATE, TIMEOUT); //インスタンス＋ENピン(2番ピン)およびUARTの指定

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

void setup() {
  Serial.begin(115200);
  PS4.begin("08:B6:1F:ED:4B:E2");

  krs.begin();  //サーボモータの通信初期設定
  krs.setPos(0, 7500);     //位置指令　ID:0サーボを7500へ 中央
  krs.setPos(1, 7500 - 1500);   //位置指令　ID:1サーボを7500へ 中央
  krs.setPos(2, 7500);     //位置指令　ID:2サーボを7500へ 中央
  krs.setPos(3, 7500 - 1000);   //位置指令　ID:3サーボを7500へ 中央
  krs.setPos(4, 7500 + 250); //位置指令　ID:4サーボを7500へ 中央
  krs.setPos(10, 7500);     //位置指令　ID:0サーボを7500へ 中央
  krs.setPos(11, 7500 - 1500);   //位置指令　ID:1サーボを7500へ 中央
  krs.setPos(12, 7500);     //位置指令　ID:2サーボを7500へ 中央
  krs.setPos(13, 7500 - 1000);   //位置指令　ID:3サーボを7500へ 中央
  krs.setPos(14, 7500 + 250);   //位置指令　ID:4サーボを7500へ 中央
  krs.setPos(20, 7500);     //位置指令　ID:0サーボを7500へ 中央
  krs.setPos(21, 7500 - 1500);   //位置指令　ID:1サーボを7500へ 中央
  krs.setPos(22, 7500);     //位置指令　ID:2サーボを7500へ 中央
  krs.setPos(23, 7500 + 1000);   //位置指令　ID:3サーボを7500へ 中央
  krs.setPos(24, 7500 + 250);   //位置指令　ID:4サーボを7500へ 中央
}

void loop() {
  if (PS4.isConnected()) {
      if (PS4.Up()) {
          Serial.print(F("\r\nUp"));
          krs.setPos(0, 7500 + 1000);
          krs.setPos(10, 7500 - 1000);
          delay(500);
          krs.setPos(0, 7500 - 1500);
          krs.setPos(10, 7500 + 1500);
          delay(500);
      }
      if (PS4.Right()) {
          Serial.print(F("\r\nRight"));
          krs.setPos(24, 7500 + 250 -500);
      } 
      if (PS4.Down()) {
          Serial.print(F("\r\nDown"));
          krs.setPos(24, 7500 + 250);
      } 
      if (PS4.Left()) {
          Serial.print(F("\r\nLeft"));
          krs.setPos(24, 7500 + 250 + 500);
      } 
      if (PS4.Circle()) {
        Serial.print(F("\r\nCircle"));
        if (PS4.Up()) {
          Serial.print(F("\r\nUp"));
          krs.setPos(20, 7500 + 1000);
          krs.setPos(0, 7500 - 1000);
          delay(500);
          krs.setPos(20, 7500 - 1500);
          krs.setPos(0, 7500 + 1500);
          delay(500);
        } if (PS4.Right()) {
          Serial.print(F("\r\nRight"));
          krs.setPos(14, 7500 + 250 - 500);
        } if (PS4.Down()) {
          Serial.print(F("\r\nDown"));
          krs.setPos(14, 7500 + 250);
        } if (PS4.Left()) {
          Serial.print(F("\r\nLeft"));
          krs.setPos(14, 7500 + 250 + 500);
        }
      }
      if (PS4.Cross()) {
        Serial.print(F("\r\nCross"));
        krs.setPos(0, 7500);     //位置指令　ID:0サーボを7500へ 中央
        krs.setPos(1, 7500 - 1500);   //位置指令　ID:1サーボを7500へ 中央
        krs.setPos(2, 7500);     //位置指令　ID:2サーボを7500へ 中央
        krs.setPos(3, 7500 - 1000);   //位置指令　ID:3サーボを7500へ 中央
        krs.setPos(4, 7500 + 250); //位置指令　ID:4サーボを7500へ 中央
        krs.setPos(10, 7500);     //位置指令　ID:0サーボを7500へ 中央
        krs.setPos(11, 7500 - 1500);   //位置指令　ID:1サーボを7500へ 中央
        krs.setPos(12, 7500);     //位置指令　ID:2サーボを7500へ 中央
        krs.setPos(13, 7500 - 1000);   //位置指令　ID:3サーボを7500へ 中央
        krs.setPos(14, 7500 + 250);   //位置指令　ID:4サーボを7500へ 中央
        krs.setPos(20, 7500);     //位置指令　ID:0サーボを7500へ 中央
        krs.setPos(21, 7500 - 1500);   //位置指令　ID:1サーボを7500へ 中央
        krs.setPos(22, 7500);     //位置指令　ID:2サーボを7500へ 中央
        krs.setPos(23, 7500 + 1000);   //位置指令　ID:3サーボを7500へ 中央
        krs.setPos(24, 7500 + 250);   //位置指令　ID:4サーボを7500へ 中央

      }
      if (PS4.Square()) {
        Serial.print(F("\r\nSquare"));
        if (PS4.Up()) {
          Serial.print(F("\r\nUp"));
          krs.setPos(10, 7500 + 1000);
          krs.setPos(20, 7500 - 1000);
          delay(500);
          krs.setPos(10, 7500 - 1500);
          krs.setPos(20, 7500 + 1500);
          delay(500);
        } if (PS4.Right()) {
          Serial.print(F("\r\nRight"));
          krs.setPos(4, 7500 + 250 - 500);
        } if (PS4.Down()) {
          Serial.print(F("\r\nDown"));
          krs.setPos(4, 7500 + 250);
        } if (PS4.Left()) {
          Serial.print(F("\r\nLeft"));
          krs.setPos(4, 7500 + 250 + 500);
        }
      }
      if (PS4.L1()) {
        Serial.print(F("\r\nL1"));
        krs.setPos(4, 7500 + 1750);
        krs.setPos(14, 7500 + 1750);
        krs.setPos(24, 7500 + 1750);
        delay(500);
        krs.setPos(2, 7500);
        krs.setPos(12, 7500);
        krs.setPos(22, 7500);
        krs.setPos(3, 7500 - 1000);
        krs.setPos(13, 7500 - 1000);
        krs.setPos(23, 7500 + 1000);
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
        krs.setPos(23, 7500 + 2500);
        delay(500);
      }
      if (PS4.R1()) {
        Serial.print(F("\r\nR1"));
        krs.setPos(4, 7500 - 1250);
        krs.setPos(14, 7500 - 1250 );
        krs.setPos(24, 7500 - 1250 );
        delay(500);
        krs.setPos(2, 7500);
        krs.setPos(12, 7500);
        krs.setPos(22, 7500);
        krs.setPos(3, 7500 - 1000);
        krs.setPos(13, 7500 - 1000);
        krs.setPos(23, 7500 + 1000);
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
        krs.setPos(23, 7500 + 2500);
        delay(500);
      }
  }
}
