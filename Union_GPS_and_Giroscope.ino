#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // не використовується тут, але в майбутньому пригодиться
#include <stdio.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

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
}

void loop() 
{
  
  lsm.read();   
 
  sensors_event_t a, m, g, temp;

  lsm.getEvent(&a, &m, &g, &temp); 

  Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.print(" m/s^2 ");
  Serial.print("\tY: "); Serial.print(a.acceleration.y);     Serial.print(" m/s^2 ");
  Serial.print("\tZ: "); Serial.print(a.acceleration.z);     Serial.println(" m/s^2 ");

  Serial.print("Mag X: "); Serial.print(m.magnetic.x);   Serial.print(" uT");
  Serial.print("\tY: "); Serial.print(m.magnetic.y);     Serial.print(" uT");
  Serial.print("\tZ: "); Serial.print(m.magnetic.z);     Serial.println(" uT");

  Serial.print("Gyro X: "); Serial.print(g.gyro.x);   Serial.print(" rad/s");
  Serial.print("\tY: "); Serial.print(g.gyro.y);      Serial.print(" rad/s");
  Serial.print("\tZ: "); Serial.print(g.gyro.z);      Serial.println(" rad/s");

  Serial.println();

  static const double POLITECH_LAT = 49.833333, POLITECH_LON = 24.000000;
Serial.print("satelits - \t\t\t\t");
printInt(gps.satellites.value(), gps.satellites.isValid(), 5);          //- інформація про супутники
Serial.println();
Serial.print("horizontal accuracy - \t\t\t");
printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1);                  // - Точність
Serial.println();
Serial.print("latitude and longitude - \t\t\t");
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  Serial.print(" / ");
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
Serial.println();
Serial.print("date and time - \t\t\t\t");
printDateTime(gps.date, gps.time);
Serial.println();
Serial.print("altitude - \t\t");
printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
Serial.println();
Serial.print("Direction of movement (compass) - \t");
printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
Serial.println();
Serial.print("Speed in km. - \t\t\t");
printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
Serial.println();
Serial.print("Direction - \t\t\t\t");
  printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6);
Serial.println();
Serial.print("Distance to the Polytechnic - \t\t\t");
  unsigned long distanceKmToPolitech =
    (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      POLITECH_LAT, 
      POLITECH_LON) / 1000;
  printInt(distanceKmToPolitech, gps.location.isValid(), 9);

  double courseToPolitech =
    TinyGPSPlus::courseTo(
      gps.location.lat(),
      gps.location.lng(),
      POLITECH_LAT, 
      POLITECH_LON);

  printFloat(courseToPolitech, gps.location.isValid(), 7, 2);

Serial.println();
Serial.print("Distance to the Polytechnic - \t\t\t");  

  const char *cardinalToPolitech = TinyGPSPlus::cardinal(courseToPolitech);

  printStr(gps.location.isValid() ? cardinalToPolitech : "*** ", 6);
Serial.println();
  Serial.println("------------------------------------------------------------------");
  
  smartDelay(3000);                                                      // Пауза для виводу

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("Дані GPS не отримані: перевірте з'єднання"));
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
