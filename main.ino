#define ANALOG_IN_PIN A0

#include <Wire.h> 

#include <LiquidCrystal_I2C.h>

#include <Sim800L.h>

#include <SoftwareSerial.h>           

#define RX  3

#define TX  11

Sim800L GSM(RX, TX);

LiquidCrystal_I2C lcd(0x27,20,4);

char* text;

char* number;

bool error;

float adc_voltage = 0.0;

float in_voltage = 0.0;

int buzzer = 12;

float R1 = 30000.0;

float R2 = 7500.0; 

String status = "Solar";

float ref_voltage = 5.0;

int adc_value = 0;

int ac = 8;

int dc = 7;

int flagn=0;

int flags=0;

void setup() {

  GSM.begin(4800);

  Serial.begin(9600);

  Serial.println("DC Voltage Test");

  lcd.init();

  lcd.init();

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(buzzer, OUTPUT);

  lcd.backlight();

  pinMode(ac, OUTPUT);

  pinMode(dc, OUTPUT);

  digitalWrite(ac, 0);

  digitalWrite(dc, 0);

}

void send_status(char* text){

  #include <Sim800L.h>

  #define RX  3

  #define TX  11

  

  Sim800L GSM(RX, TX);

  GSM.begin(4800);

  Serial.begin(9600); 

  number="+2347018571511";

  error=GSM.sendSms(number,text);

  }

void loop() {

  adc_value = analogRead(ANALOG_IN_PIN);

  adc_voltage  = (adc_value * ref_voltage) / 1024.0;

  in_voltage = adc_voltage / (R2/(R1+R2));

  Serial.print("Input Voltage = ");

  Serial.println(in_voltage, 2);

  lcd.clear();

  lcd.setCursor(0,0);

  lcd.print("In Volt:");

  lcd.print(in_voltage, 2);

  lcd.print("V");

  lcd.setCursor(0,1);

  lcd.print("Status:");

  lcd.print(status);

  if(in_voltage < 7 && in_voltage > 3){

    digitalWrite(ac, 1);

    digitalWrite(dc, 0);

    digitalWrite(LED_BUILTIN, HIGH);

    digitalWrite(buzzer, LOW);

    status = "NEPA";

    flags=0;

    if(flagn<2){

      send_status("You Are On NEPA: All Appliances are Powered");

      flagn++;

    }

    

  }else{

    digitalWrite(dc, 1);

    digitalWrite(ac, 0);

    digitalWrite(LED_BUILTIN, LOW);

    digitalWrite(buzzer, HIGH);

    status = "Solar";

    flagn=0;

    if(flags<2){

      send_status("You Are On Solar: Bulb,Fan,CCTV and Inverter AC");

      flags++;

    }

  }

  delay(2000);

}
