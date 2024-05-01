#include <Arduino.h>
#include <BleKeyboard.h>
#include <IRremote.hpp>

// update pin number as per your ESP32 board
#define IR_RECEIVE_PIN 15 // D15

BleKeyboard bleKeyboard("Macro Remote", "onkar", 100);

void setup()
{
  // to debug the code using IDE 
  // uncomment following line and all 'Serial.println' lines
  // Serial.begin(115200);

  // Bluetooth connection indicator
  pinMode(2, OUTPUT);

  bleKeyboard.begin();
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  // printActiveIRProtocols(&Serial);
  // Serial.println("device initialized");
}

void loop()
{
  if (bleKeyboard.isConnected())
  {
    digitalWrite(2, HIGH);
    if (IrReceiver.decode())
    {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
      // IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
      // IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
      switch (IrReceiver.decodedIRData.command)
      {
      // *
      case 0x16:
        bleKeyboard.write(KEY_MEDIA_MUTE);
        break;
      // ok
      case 0x1c:
        bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
        break;
      // up
      case 0x18:
        bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
        break;
      // down
      case 0x52:
        bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
        break;
      // left
      case 0x8:
        bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
        break;
      // right
      case 0x5A:
        bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
        break;
      default:
        bleKeyboard.press(KEY_RIGHT_CTRL);
        bleKeyboard.press(KEY_RIGHT_SHIFT);
        switch (IrReceiver.decodedIRData.command)
        {
          // 1
          case 0x45:
            bleKeyboard.press(KEY_F1);
            break;
          // 2
          case 0x46:
            bleKeyboard.press(KEY_F2);
            break;
          // 3
          case 0x47:
            bleKeyboard.press(KEY_F3);
            break;
          // 4
          case 0x44:
            bleKeyboard.press(KEY_F4);
            break;
          // 5
          case 0x40:
            bleKeyboard.press(KEY_F5);
            break;
          // 6
          case 0x43:
            bleKeyboard.press(KEY_F6);
            break;
          // 7
          case 0x7:
            bleKeyboard.press(KEY_F7);
            break;
          // 8
          case 0x15:
            bleKeyboard.press(KEY_F8);
            break;
          // 9
          case 0x9:
            bleKeyboard.press(KEY_F9);
            break;
          // 0 - mid volume
          case 0x19:
            bleKeyboard.press(KEY_F10);
            break;
          // # - high volume
          case 0xD:
            bleKeyboard.press(KEY_F11);
            break;
        }
      }
      delay(50);
      bleKeyboard.releaseAll();
      delay(100);
      IrReceiver.resume();
    }
  }
  else
  {
    digitalWrite(2, LOW);
    delay(5000);
  }
}

/*
Key codes of my remote
1 - 0x45
2 - 0x46
3 - 0x47
4 - 0x44
5 - 0x40
6 - 0x43
7 - 0x7
8 - 0x15
9 - 0x9
* - 0x16
0 - 0x19
# - 0xD
up - 0x18
down - 0x52
left - 0x8
right - 0x5A
ok - 0x1C
*/