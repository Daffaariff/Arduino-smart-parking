#include <Wire.h>               // Library komunikasi I2C
#include <LiquidCrystal_I2C.h>  // Library modul I2C LCD

// default address 0x27
// tipe LCD 16x2 (16,2)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
#include <Servo.h>

#define NOTE_C1 262
#define NOTE_C2 330

Servo myservo1;
Servo myservo2;

int led1 = 8;
int led2 = 11;

int bz1 = 12;
int bz2 = 9;

int IR1 = 7;
int IR2 = 4;

int slot = 4;  //Enter Total number of parking Slots

int flag1 = 0;
int flag2 = 0;

int flag3 = 0;
int flag4 = 0;

void setup() {

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  pinMode(bz1, OUTPUT);
  pinMode(bz2, OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);


  myservo1.attach(3);
  myservo1.write(90);

  myservo2.attach(2);
  myservo2.write(90);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("     TI UMMI   ");
  lcd.setCursor(0, 1);
  lcd.print(" SMART PARKING ");
  delay(2000);
  lcd.clear();
}

void loop() {

  if (digitalRead(IR1) == 0 && flag1 == 0)  // read degital data from IR sensor1
  {
    if (slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        tone(bz1, NOTE_C1, 1000);
        digitalWrite(led1, HIGH);        
        myservo1.write(-180);
        slot = slot - 1;
        
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Parkiran Penuh ");
      delay(1500);
    }
  }

  if (digitalRead(IR1) == 0 && flag2 == 0)  // read degital data from IR sensor2
  {
    flag2 = 1;
    if (flag1 == 0) {
      digitalWrite(led1, LOW); 
      myservo1.write(-180);  // sets the servo at 180 degree position
      noTone(bz1);
    }
    delay(4000);
    myservo1.write(90);
  }

  if (flag1 == 1 && flag2 == 1) {
    delay(4000);
    myservo1.write(90);
    flag1 = 0, flag2 = 0;
  }

  if (digitalRead(IR2) == 0 && flag3 == 0)  // read degital data from IR sensor1
  {
    if (slot < 4) {
      flag3 = 1;
      if (flag4 == 0) {
        tone(bz2, NOTE_C1, 1000);
        digitalWrite(led2, HIGH);  
        myservo2.write(-180);
        slot = slot + 1;
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Tidak Ada Kendaraan!!! ");
      delay(1500);
    }
  }

  if (digitalRead(IR2) == 0 && flag4 == 0)  // read degital data from IR sensor2
  {
    flag4 = 1;
    if (flag3 == 0) {
      noTone(bz2);
      digitalWrite(led2, LOW);  
      myservo2.write(-180);  // sets the servo at 180 degree position
    }
    delay(4000);
    myservo2.write(90);
  }

  if (flag3 == 1 && flag4 == 1) {
    delay(1000);
    myservo2.write(90);
    flag3 = 0, flag4 = 0;
  }

  delay(1);
  lcd.setCursor(0, 0);
  lcd.print("    WELCOME!    ");
  lcd.setCursor(0, 1);
  lcd.print("Slot Tersisa: ");
  lcd.print(slot);
}
