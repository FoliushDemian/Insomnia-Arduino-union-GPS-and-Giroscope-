#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // не використовується тут, але в майбутньому пригодиться
#include <stdio.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>


SoftwareSerial sim(6,5);
int _timeout;
String _buffer;                                              // ITS ALL FOR GSM MODULE
String number = "+380680082163"; //-> change with your number

//#define R_PIN 3
//#define G_PIN 5  // до для першого виду підсвітки(спокійної)
//#define B_PIN 6


#define LED_R 3 // Pin D3 --> червоний
#define LED_G 5 // Pin D5 --> зелений   // то для другого виду підсвітки(страбоскопної)
#define LED_B 6 // Pin D6 --> синій

int red();
int green(); // то для другого виду підсвітки(стробоскопної)
int blue();

static const int RXPin = 10, TXPin = 11;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

// i2c
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

void setupSensor()
{
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
;
}

void setup() 
{
//  pinMode(R_PIN, OUTPUT);
//  pinMode(G_PIN, OUTPUT); // то для першого виду підсвітки(спокійної)
//  pinMode(B_PIN, OUTPUT);

  pinMode( LED_R, OUTPUT );
  pinMode( LED_G, OUTPUT );  // то для другого виду підсвітки(стробоскопної)
  pinMode( LED_B, OUTPUT );
  
  analogWrite (LED_R,255);
  analogWrite (LED_G,255);  // то для другого виду підсвітки(стробоскопної)
  analogWrite (LED_B,255);

  
  Serial.begin(115200);
  ss.begin(GPSBaud);

  while (!Serial) {
    delay(10000);
  }
  
  Serial.println("LSM9DS1 data read demo");
  

  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS1 9DOF");


  setupSensor();


  delay(7000); //delay for 7 seconds to make sure the  GSM module get the signal
  Serial.begin(9600);
  _buffer.reserve(50);
  Serial.println("System Started...");
  sim.begin(9600);
  delay(1000);
  Serial.println("Type s to send an SMS, r to receive an SMS, and c to make a Call");
}

void loop() 
{
//  static int counter = 0;
//  counter += 10;
////  colorWheel(counter);  // то для першого виду підсвітки(спокійної)
//  delay(100);
//  lsm.read();   
// 
//  sensors_event_t a, m, g, temp;
//
//  lsm.getEvent(&a, &m, &g, &temp); 
//
//  Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.print(" m/s^2 ");
//  Serial.print("\tY: "); Serial.print(a.acceleration.y);     Serial.print(" m/s^2 ");
//  Serial.print("\tZ: "); Serial.print(a.acceleration.z);     Serial.println(" m/s^2 ");
//
//  Serial.print("Mag X: "); Serial.print(m.magnetic.x);   Serial.print(" uT");
//  Serial.print("\tY: "); Serial.print(m.magnetic.y);     Serial.print(" uT");
//  Serial.print("\tZ: "); Serial.print(m.magnetic.z);     Serial.println(" uT");
//
//  Serial.print("Gyro X: "); Serial.print(g.gyro.x);   Serial.print(" rad/s");
//  Serial.print("\tY: "); Serial.print(g.gyro.y);      Serial.print(" rad/s");
//  Serial.print("\tZ: "); Serial.print(g.gyro.z);      Serial.println(" rad/s");
//
//  Serial.println();
//
//  static const double POLITECH_LAT = 49.833333, POLITECH_LON = 24.000000;
//Serial.print("satelits - \t\t\t\t");
//printInt(gps.satellites.value(), gps.satellites.isValid(), 5);          //- інформація про супутники
//Serial.println();
//Serial.print("horizontal accuracy - \t\t\t");
//printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1);                  // - Точність
//Serial.println();
//Serial.print("latitude and longitude - \t\t\t");
//  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
//  Serial.print(" / ");
//  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
//Serial.println();
//Serial.print("date and time - \t\t\t\t");
//printDateTime(gps.date, gps.time);
//Serial.println();
//Serial.print("altitude - \t\t");
//printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
//Serial.println();
//Serial.print("Direction of movement (compass) - \t");
//printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
//Serial.println();
//Serial.print("Speed in km. - \t\t\t");
//printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
//Serial.println();
//Serial.print("Direction - \t\t\t\t");
//  printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6);
//Serial.println();
//Serial.print("Distance to the Polytechnic - \t\t\t");
//  unsigned long distanceKmToPolitech =
//    (unsigned long)TinyGPSPlus::distanceBetween(
//      gps.location.lat(),
//      gps.location.lng(),
//      POLITECH_LAT, 
//      POLITECH_LON) / 1000;
//  printInt(distanceKmToPolitech, gps.location.isValid(), 9);
//
//  double courseToPolitech =
//    TinyGPSPlus::courseTo(
//      gps.location.lat(),
//      gps.location.lng(),
//      POLITECH_LAT, 
//      POLITECH_LON);
//
//  printFloat(courseToPolitech, gps.location.isValid(), 7, 2);
//
//Serial.println();
//Serial.print("Distance to the Polytechnic - \t\t\t");  
//
//  const char *cardinalToPolitech = TinyGPSPlus::cardinal(courseToPolitech);
//
//  printStr(gps.location.isValid() ? cardinalToPolitech : "*** ", 6);
//Serial.println();
//  Serial.println("------------------------------------------------------------------");
//  
//  smartDelay(3000);                                                      // Пауза для виводу
//
//  if (millis() > 5000 && gps.charsProcessed() < 10)
//    Serial.println(F("Дані GPS не отримані: перевірте з'єднання"));
//





    // ТО ДЛЯ ДРУГОЇ ПІДСВІТКИ(СТРАБОСКОПНОЇ)
    //-------------запалюєм і гасим червоний
{
  int x = 1;
  for (int i = 0; i > -1; i = i + x){
      red(i);
      if (i == 255) x = -1;             //переключення в сторону гасіння на максимумі свічення
      delay(5);
   }
}
//-------------запалюєм і гасим зелений
{
  int x = 1;
  for (int i = 0; i > -1; i = i + x){
      green(i);
      if (i == 255) x = -1;             // переключення в сторону гасіння на максимумі свічення
      delay(5);
   }
}
//-------------запалюєм і гасим синій
{
  int x = 1;
  for (int i = 0; i > -1; i = i + x){
      blue(i);
      if (i == 255) x = -1;             // переключення в сторону гасіння на максимумі свічення
      delay(5);
   }
}

//------------- мигаємо кожним кольором по три рази
red(0);
delay(100);
red(80);
delay(100);
red(0);
delay(100);
red(160);
delay(100);
red(0);
delay(100);
red(255);
delay(100);
red(0);
delay(100);
green(80);
delay(100);
green(0);
delay(100);
green(160);
delay(100);
green(0);
delay(100);
green(255);
delay(100);
green(0);
delay(100);
blue(80);
delay(100);
blue(0);
delay(100);
blue(160);
delay(100);
blue(0);
delay(100);
blue(255);
delay(100);
blue(0);
//-------------мигаємо випадковими кольорами і випадковою яскравістю
   for (int i=0; i <= 50; i++){
    
    int color=(random(3)+1);
      if (color=1) {red(random(256)); delay(100);red(0);}
      if (color=2) {green(random(256)); delay(100);green(0);}
      if (color=3) {blue(random(256)); delay(100);blue(0);}
   }

if (Serial.available() > 0)// begin of gsm module code 
    switch (Serial.read())
    {
      case 's':
        SendMessage();
        break;
      case 'r':
        RecieveMessage();
        break;
      case 'c':
        callNumber();
        break;
    }
  if (sim.available() > 0)
    Serial.write(sim.read()); // end of gsm module code 
   
}// КІНЕЦЬ VOID LOOP не видалити випадково!!!



void red(int s){
analogWrite (LED_R,255-s);
}
//***************************************************
void green(int s){
analogWrite (LED_G,255-s);
}
//***************************************************//ТО ДЛЯ ДРУГОГО КОДУ ПІДСВІТКИ(СТРАБОСКОПНОЇ)
void blue(int s){
analogWrite (LED_B,255-s);
}

// This custom version of delay() ensures that the gps object.
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}




//void colorWheel(int color) {
//  byte _r, _g, _b;
//  if (color <= 255) {                       // RED max, green is growing
//    _r = 255;
//    _g = color;
//    _b = 0;
//  }
//  else if (color > 255 && color <= 510) {   // GREEN max, red is falling
//    _r = 510 - color;
//    _g = 255;
//    _b = 0;
//  }
//  else if (color > 510 && color <= 765) {   // GREEN max, blue is growing
//    _r = 0;
//    _g = 255;
//    _b = color - 510;
//  }
//  else if (color > 765 && color <= 1020) {  // BLUE is max, green is falling
//    _r = 0;
//    _g = 1020 - color;
//    _b = 255;
//  }
//  else if (color > 1020 && color <= 1275) {   // BLUE is max, red is growing
//    _r = color - 1020;
//    _g = 0;
//    _b = 255;
//  }
//  else if (color > 1275 && color <= 1530) { // RED max, blue is falling
//    _r = 255;
//    _g = 0;
//    _b = 1530 - color;
//  }
//  analogWrite(R_PIN, 255 - _r);
//  analogWrite(G_PIN, 255 - _g);
//  analogWrite(B_PIN, 255 - _b);
//}

void SendMessage()                         // BEGIN of gsm module code
{
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(1000);
//  String SMS = "Hello, all is working";
//  sim.println(SMS);
//  delay(100);
//  sim.println((char)26);// ASCII code of CTRL+Z
//  delay(1000);
  



  lsm.read();   // ПОТІМ МОЖЕ ДОВЕДЕТЬСЯ ВИДАЛИТИ
 
  sensors_event_t a, m, g, temp;

  lsm.getEvent(&a, &m, &g, &temp); 

//  Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.print(" m/s^2 ");
//  Serial.print("\tY: "); Serial.print(a.acceleration.y);     Serial.print(" m/s^2 ");
//  Serial.print("\tZ: "); Serial.print(a.acceleration.z);     Serial.println(" m/s^2 ");
//  Serial.println();  // ПОТІМ МОЖЕ ДОВЕДЕТЬСЯ ВИДАЛИТИ

//  Serial.print("satelits - \t\t\t\t");
//  printInt(gps.satellites.value(), gps.satellites.isValid(), 5);          //- інформація про супутники
//  Serial.println();
//  Serial.print("horizontal accuracy - \t\t\t");
//  printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1);                  // - Точність
//  Serial.println();
  Serial.print("latitude and longitude - \t\t\t");
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  Serial.print(" / ");
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  Serial.println();
  Serial.print("date and time - \t\t\t\t");
  printDateTime(gps.date, gps.time);
  Serial.println();


  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000); 
  _buffer = _readSerial();
}
void RecieveMessage()
{
  Serial.println ("SIM800L Read an SMS");
  delay (1000);
  sim.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
  Serial.write ("Unread Message done");
}
String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
}
void callNumber() {
  sim.print (F("ATD"));
  sim.print (number);
  sim.print (F(";\r\n"));
  _buffer = _readSerial();
  Serial.println(_buffer);
}                             // END of gsm module code
