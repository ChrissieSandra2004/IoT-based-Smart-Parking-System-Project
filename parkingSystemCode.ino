#include <Servo.h> //includes the servo library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//LiquidCrystal_I2C lcd(0x27, 20, 4);
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;

#define ir_enter 2
#define ir_back  4

#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8
#define ir_car5 9


int S1=0, S2=0, S3=0, S4=0, S5=0;
int flag1=0, flag2=0; 
int slot = 5;
int emptySlots = 0;
void setup(){
Serial.begin(9600);

pinMode(ir_car1, INPUT);
pinMode(ir_car2, INPUT);
pinMode(ir_car3, INPUT);
pinMode(ir_car4, INPUT);
pinMode(ir_car5, INPUT);

pinMode(ir_enter, INPUT);
pinMode(ir_back, INPUT);

myservo.attach(3);
myservo.write(90);
lcd.begin(16, 2);  
delay (2000);
// lcd.clear();   

Read_Sensor();


int total = S1+S2+S3+S4+S5;
slot = slot-total; 

lcd.setCursor (0,1);
lcd.print("Hi");

}

void loop(){
  emptySlots = 0;
  Read_Sensor();
  
  lcd.setCursor (0,1);
  // lcd.print("Empty"); 
  lcd.setCursor (0,1);
  if(S1==0){
    lcd.print("1,");
    emptySlots = emptySlots + 1;
  }
      
  if(S2==0){
    lcd.print("2,"); 
    emptySlots = emptySlots + 1;
  }
      
  if(S3==0){
    lcd.print("3,"); 
    emptySlots = emptySlots + 1;
  }
      
  if(S4==0){
    lcd.print("4,");
    emptySlots = emptySlots + 1;
  }
      
  if(S5==0){
    lcd.print("5,");
    emptySlots = emptySlots + 1;
  }
  slot = emptySlots;
  lcd.setCursor (0,0);
  lcd.print("Have Slot:"); 
  lcd.print(slot);
  if(digitalRead(ir_enter) == 0 && flag1==0){
    if(slot>0){
      flag1=1;
      if(flag2==0){
        myservo.write(180); 
        //slot = slot-1;
        }
    }else{
      lcd.setCursor (0,0);
      lcd.clear();
      lcd.print("Full");  
      
    }   
  }

  if(digitalRead(ir_back) == 0 && flag2==0){
    flag2=1;
    if(flag1==0){
      myservo.write(180); 
      // slot = slot+1;
      }
  }

  if(flag1==1 && flag2==1){
    // delay (1000);
    myservo.write(90);
    flag1=0;
    flag2=0;
  }
  delay(1500);
  lcd.clear();
  // delay(1);
}

void Read_Sensor(){
S1=0, S2=0, S3=0, S4=0, S5=0;

if(digitalRead(ir_car1) == 0){S1=1;}
if(digitalRead(ir_car2) == 0){S2=1;}
if(digitalRead(ir_car3) == 0){S3=1;}
if(digitalRead(ir_car4) == 0){S4=1;}
if(digitalRead(ir_car5) == 0){S5=1;}
}