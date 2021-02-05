#include "Arduino.h"
#include "SoftwareSerial.h"

#include "DFRobotDFPlayerMini.h"
#include <LiquidCrystal_I2C.h>


//LiquidCrystal_I2C lcd(0x27, 20, 4);

SoftwareSerial mySerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int f = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  //Serial.begin(115200);

  //Serial.println();
  //Serial.println(F("DFRobot DFPlayer Mini Demo"));
  //Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(Serial)) {  //Use softwareSerial to communicate with mp3.
    //Serial.println(F("Unable to begin:"));
    //Serial.println(F("1.Please recheck the connection!"));
    //Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  //Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(100);  //Set volume value. From 0 to 30
  //lcd.init();                      // initialize the lcd
  //lcd.backlight();
  //myDFPlayer.play(1);  //Play the first mp3
  //lcd.clear();
  //lcd.setCursor(3, 0);
  //lcd.print("HELLO");
}

void loop() {
  /*if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
    }*/
  if (analogRead(A0) < 990 && analogRead(A1) < 880 && analogRead(A2) < 975 && analogRead(A3) < 935 && a == 0) {
    Serial.println("H");
    mySerial.println("H");
    //lcd.clear();
    //lcd.setCursor(3, 0);
    //lcd.print("HELP");
    myDFPlayer.play(6);
    delay(3000);
    a = 1;
    b = 0;
    c = 0;
    d = 0;
    e = 0;
    f = 0;
  }
  else if (analogRead(A0) > 990 && analogRead(A1) > 880 && analogRead(A2) > 975 && analogRead(A3) > 920) {
    //Serial.println("Play");
    if (analogRead(A4) < 300 && b == 0) {
      Serial.println("M");
      mySerial.println("M");
      //lcd.clear();
      //lcd.setCursor(3, 0);
      //lcd.print("MEDICINE");
      myDFPlayer.play(4);
      delay(3000);
      a = 0;
      b = 1;
      c = 0;
      d = 0;
      e = 0;
      f = 0;
    }
    else if (analogRead(A4) > 380 && c == 0 ) {
      Serial.println("S");
      mySerial.println("S");
      //lcd.clear();
      //lcd.setCursor(3, 0);
      //lcd.print("STOP");
      myDFPlayer.play(1);
      delay(3000);
      a = 0;
      b = 0;
      c = 1;
      d = 0;
      e = 0;
      f = 0;
    }
    else if (analogRead(A5) > 380 && d == 0) {
      Serial.println("F");
      mySerial.println("F");
      //lcd.clear();
      //lcd.setCursor(3, 0);
      //lcd.print("FOOD");
      myDFPlayer.play(5);
      delay(3000);
      a = 0;
      b = 0;
      c = 0;
      d = 1;
      e = 0;
      f = 0;
    }
    else if (analogRead(A5) < 300 && e == 0) {
      Serial.println("W");
      mySerial.println("W");
      //lcd.clear();
      //lcd.setCursor(3, 0);
      //lcd.print("WATER");
      myDFPlayer.play(3);
      delay(3000);
      a = 0;
      b = 0;
      c = 0;
      d = 0;
      e = 1;
      f = 0;
    }
  }
  else if (analogRead(A0) < 990 && analogRead(A1) < 880 && analogRead(A2) < 975 && analogRead(A3) > 960 && f == 0) {
    Serial.println("I");
    mySerial.println("I");
    //lcd.clear();
    //lcd.setCursor(3, 0);
    //lcd.print("FINE");
    myDFPlayer.play(2);
    delay(3000);
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    e = 0;
    f = 1;
  }


  /*Serial.print(analogRead(A0));
    Serial.print('\t');
    Serial.print(analogRead(A1));
    Serial.print('\t');
    Serial.print(analogRead(A2));
    Serial.print('\t');
    Serial.print(analogRead(A3));
    Serial.print('\t');*/
    //Serial.println(analogRead(A4));
    //Serial.print('\t');
    //Serial.println(analogRead(A5));


}

void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
