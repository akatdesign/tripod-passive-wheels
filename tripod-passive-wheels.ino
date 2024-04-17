#include <PS4BT.h>
#include <usbhub.h>
#include <SPI.h>
#include <IcsHardSerialClass.h>


const byte EN_PIN = 2;
const long BAUDRATE = 115200;
const int TIMEOUT = 10;    //通信できてないか確認用にわざと遅めに設定

IcsHardSerialClass krs(&Serial, EN_PIN, BAUDRATE, TIMEOUT); //インスタンス＋ENピン(2番ピン)およびUARTの指定



USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

PS4BT PS4(&Btd, PAIR);

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;


void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));

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
  Usb.Task();

  if (PS4.connected()) {
      if (PS4.getButtonPress(TRIANGLE)) {
        Serial.print(F("\r\nTriangle"));
        PS4.setRumbleOn(RumbleLow);
        if (PS4.getButtonClick(UP)) {
          Serial.print(F("\r\nUp"));
          //PS4.setLed(Red);
          krs.setPos(0, 7500 + 1000);
          krs.setPos(10, 7500 - 1000);
          delay(500);
          krs.setPos(0, 7500 - 1500);
          krs.setPos(10, 7500 + 1500);
          delay(500);
        } if (PS4.getButtonClick(RIGHT)) {
          Serial.print(F("\r\nRight"));
          //PS4.setLed(Blue);
          krs.setPos(24, 7500 + 250 -500);
        } if (PS4.getButtonClick(DOWN)) {
          Serial.print(F("\r\nDown"));
          //PS4.setLed(Yellow);
          krs.setPos(24, 7500 + 250);
        } if (PS4.getButtonClick(LEFT)) {
          Serial.print(F("\r\nLeft"));
          //PS4.setLed(Green);
          krs.setPos(24, 7500 + 250 + 500);

        }
      }
      if (PS4.getButtonPress(CIRCLE)) {
        Serial.print(F("\r\nCircle"));
        //PS4.setRumbleOn(RumbleHigh);
        if (PS4.getButtonClick(UP)) {
          Serial.print(F("\r\nUp"));
          //PS4.setLed(Red);
          krs.setPos(20, 7500 + 1000);
          krs.setPos(0, 7500 - 1000);
          delay(500);
          krs.setPos(20, 7500 - 1500);
          krs.setPos(0, 7500 + 1500);
          delay(500);
        } if (PS4.getButtonClick(RIGHT)) {
          Serial.print(F("\r\nRight"));
          //PS4.setLed(Blue);
          krs.setPos(14, 7500 + 250 - 500);
        } if (PS4.getButtonClick(DOWN)) {
          Serial.print(F("\r\nDown"));
          //PS4.setLed(Yellow);
          krs.setPos(14, 7500 + 250);
        } if (PS4.getButtonClick(LEFT)) {
          Serial.print(F("\r\nLeft"));
          //PS4.setLed(Green);
          krs.setPos(14, 7500 + 250 + 500);
        }
      }
      if (PS4.getButtonClick(CROSS)) {
        Serial.print(F("\r\nCross"));
        PS4.setLedFlash(10, 10); // Set it to blink rapidly
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
      if (PS4.getButtonPress(SQUARE)) {
        Serial.print(F("\r\nSquare"));
        PS4.setLedFlash(0, 0); // Turn off blinking
        if (PS4.getButtonClick(UP)) {
          Serial.print(F("\r\nUp"));
          //PS4.setLed(Red);
          krs.setPos(10, 7500 + 1000);
          krs.setPos(20, 7500 - 1000);
          delay(500);
          krs.setPos(10, 7500 - 1500);
          krs.setPos(20, 7500 + 1500);
          delay(500);
        } if (PS4.getButtonClick(RIGHT)) {
          Serial.print(F("\r\nRight"));
          //PS4.setLed(Blue);
          krs.setPos(4, 7500 + 250 - 500);
        } if (PS4.getButtonClick(DOWN)) {
          Serial.print(F("\r\nDown"));
          //PS4.setLed(Yellow);
          krs.setPos(4, 7500 + 250);
        } if (PS4.getButtonClick(LEFT)) {
          Serial.print(F("\r\nLeft"));
          //PS4.setLed(Green);
          krs.setPos(4, 7500 + 250 + 500);
        }
      }

      if (PS4.getButtonPress(UP)) {
        Serial.print(F("\r\nUp"));
        //PS4.setLed(Red);

      } if (PS4.getButtonPress(RIGHT)) {
        Serial.print(F("\r\nRight"));
        //PS4.setLed(Blue);

      } if (PS4.getButtonClick(DOWN)) {
        Serial.print(F("\r\nDown"));
        PS4.setLed(Yellow);
      } if (PS4.getButtonPress(LEFT)) {
        Serial.print(F("\r\nLeft"));
        //PS4.setLed(Green);

      }

      if (PS4.getButtonClick(L1)) {
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
      if (PS4.getButtonPress(L3))
        Serial.print(F("\r\nL3"));
      if (PS4.getButtonClick(R1)) {
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
      if (PS4.getButtonClick(R3))
        Serial.print(F("\r\nR3"));

      if (PS4.getButtonClick(SHARE))
        Serial.print(F("\r\nShare"));
      if (PS4.getButtonClick(OPTIONS)) {
        Serial.print(F("\r\nOptions"));
        printAngle = !printAngle;
      }
      if (PS4.getButtonClick(TOUCHPAD)) {
        Serial.print(F("\r\nTouchpad"));
        printTouch = !printTouch;
      }

      if (printAngle) { // Print angle calculated using the accelerometer only
        Serial.print(F("\r\nPitch: "));
        Serial.print(PS4.getAngle(Pitch));
        Serial.print(F("\tRoll: "));
        Serial.print(PS4.getAngle(Roll));
        
      }

      if (printTouch) { // Print the x, y coordinates of the touchpad
        if (PS4.isTouching(0) || PS4.isTouching(1)) // Print newline and carriage return if any of the fingers are touching the touchpad
          Serial.print(F("\r\n"));
        for (uint8_t i = 0; i < 2; i++) { // The touchpad track two fingers
          if (PS4.isTouching(i)) { // Print the position of the finger if it is touching the touchpad
            Serial.print(F("X")); Serial.print(i + 1); Serial.print(F(": "));
            Serial.print(PS4.getX(i));
            Serial.print(F("\tY")); Serial.print(i + 1); Serial.print(F(": "));
            Serial.print(PS4.getY(i));
            Serial.print(F("\t"));
          }
        }
      }
  }
}
