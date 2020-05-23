/*
 * The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */
#include <LiquidCrystal.h>

#include "HX711.h"

#include <SoftwareSerial.h>

#include <SPI.h>
#include <MFRC522.h>

#define DOUT  4
#define CLK  5

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance. 
SoftwareSerial MyBlue(2, 3); // RX | TX 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int flag = 0; 
int LED = 8; 
float calibration_factor = 2230; // this calibration factor is adjusted according to my load cell
float units;

unsigned char code  tag1[] = "55000DE0E058";  
unsigned char code  tag2[] = "55000DD0D25A";
unsigned char code  tag3[] = "55000DC7B02F";
unsigned char code  tag4[] = "55000D577A75";
unsigned char code  tag5[] = "55000D8A0FDD";
unsigned char code  tag6[] = "55000D6D5E6B";
unsigned char code  tag7[] = "55000DAE19EF";

unsigned char code  *item[] = 
{
 "TATA SALT 1kg ",
 "BISCUIT OREO",
 "DAIRYMILK SILK",
 "MAGGI 100gms",
 "SURF EXCEL MATIC",
 "KISSAN KETCHUP",
 "COLGATE TOTAL",
}

unsigned int cost[] = { 18, 12 , 100 , 10 , 340 , 120 , 95 }

unsigned char code press_but[] = "Press ADD/REMOVE";

void update_lcd(unsigned char dis)
{
 lcd.setCursor(0, 1);
 lcd.print(item[dis]);
 lcd.setCursor(1, 1);
 lcd.print("    Rs: ");
 lcd.print(cost[dis]);
// balance = balance + cost[dis];
// lcdcmd(0xC8);
// lcd_putUINT16(balance);

}

unsigned char item_true[12] = 0;

void take_action(unsigned char dat)
{
 if(dat>=1 && dat<=7)  // rfid 
 {

  if(item_true[dat]==0)
  {
   update_lcd(dat);
   balance = balance + cost[dat];
   item_true[dat] = 1;
  }

  else
  {
   lcd(press_but, LINE1);
   lcd(item[dat], LINE2);
   while(add==1 && remove==1);
   msdelay(5);
   while(add==1 && remove==1 );

   if(add==0)
   {
     update_lcd(dat); item_true[dat]=1;
   }
   else 
   {
   if(balance>0)   balance = balance - cost[dat]; item_true[dat]=0;
    lcd(item[dat] , LINE1);
    lcd( "     Removed    ", LINE2);

   }
  }

  
 }

}

unsigned char check_data()
{

///***************** CHECK RFID DATA ****************************///
 unsigned char result;
  result = 10;

  result = strcmp(store_rfid,tag1);
  if(result==0)  { return(1);  }

  result = strcmp(store_rfid,tag2);
  if(result==0)  { return(2);  }

  result = strcmp(store_rfid,tag3);
  if(result==0)  { return(3);  }

  result = strcmp(store_rfid,tag4);
  if(result==0)  { return(4);  }

  result = strcmp(store_rfid,tag5);
  if(result==0)  { return(5);  }

  result = strcmp(store_rfid,tag6);
  if(result==0)  { return(6);  }

  result = strcmp(store_rfid,tag7);
  if(result==0)  { return(7);  }

  result = strcmp(store_rfid,tag8);
  if(result==0)  { return(8);  }

  result = strcmp(store_rfid,tag9);
  if(result==0)  { return(9);  }

  result = strcmp(store_rfid,tag10);
  if(result==0)  { return(10);  }
 return(0);
}



void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  Serial.begin(9600);    //baud rate
  
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  scale.tare();

  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  
  MyBlue.begin(9600); 
  pinMode(LED, OUTPUT); 
  Serial.println("Ready to connect\nDefualt password is 1234 or 000"); 

}

void loop() {
  // put your main code here, to run repeatedly:

}
