// Pookie!!

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; 
const int input = 7, reset = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte backslash[8] = {
  0b00000,
  0b10000,
  0b01000,
  0b00100,
  0b00010,
  0b00001,
  0b00000,
  0b00000
};

byte smallMouth[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01010,
  0b10101,
  0b00000,
  0b00000
};

const String loading1 = "      .         ";
const String loading2 = "      ..        ";
const String loading3 = "      ...       ";

unsigned long previousMillis = millis();
bool sleeping = true;
bool resetting = false;

void setup() {
  Serial.begin(9600);
  pinMode(input, INPUT_PULLUP);
  pinMode(reset, INPUT_PULLUP);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.createChar(1, backslash);
  lcd.createChar(2, smallMouth);
}

void loop() {
  String firstLine = "";
  String secondLine = "";
  unsigned long currentMillis = millis();

  if(digitalRead(input) == LOW && sleeping) {
    if(currentMillis - previousMillis < 1000) {
      firstLine = widthParser("/(.   .)\x1");
      secondLine = loading1;
    } else if (currentMillis - previousMillis < 2000) {
      firstLine = widthParser("/(o _ o)\x1");
      secondLine = loading2;
    } else if (currentMillis - previousMillis < 3000) {
      firstLine = widthParser("/(O _ O)\x1");
      secondLine = loading3;
    } else {
      firstLine = widthParser("\x1(O w O)/");
      secondLine = widthParser("\"haii!\"");
      sleeping = false;
    }
  } else if(sleeping == false) {
    firstLine = widthParser("\x1(O w O)/");
    secondLine = widthParser("\"haii!\"");
    if(digitalRead(reset) == LOW) {
      resetting = true;
      firstLine = widthParser("/(> \x2 <)\x1");
      secondLine = widthParser("\"buwah!\"");
    } else if(resetting) {
      resetting = false;
      sleeping = true;
    }
  } else {
    previousMillis = millis();
    firstLine = widthParser("/(_   _)\x1");
    secondLine = widthParser("\"snorr mimimimi\"");
    if(digitalRead(reset) == LOW) {
      firstLine = widthParser("/(_ o _)\x1");
      secondLine = widthParser("\"honnnk shooooo\"");
    }
  }


  lcd.setCursor(0, 0);
  lcd.print(firstLine);
  lcd.setCursor(0, 1);
  lcd.print(secondLine);
}

String widthParser(String line) {
  // Such that width = len + spacesLeft + spacesRight
  int width = 16;
  int len = line.length();
  int spaces = width - len;
  int spacesLeft = floor(spaces / 2.0);
  int spacesRight = ceil(spaces / 2.0);
  
  String output = repeatString(" ", spacesLeft) + line + repeatString(" ", spacesRight);
  return output;
}

String repeatString(String element, int repeats) {
  String output = "";
  for(int i = 0; i < repeats; i++) {
    output += element;
  }
  return output;
}