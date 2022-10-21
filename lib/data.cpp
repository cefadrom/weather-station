// libraries definitions
#include <SD.h>              // SD
#include <SPI.h>             // SD
#include <DS1307.h>          // clock
#include <Arduino.h>         // Arduino lib for VSCode
#include <MicroNMEA.h>       // GPS
#include <SoftwareSerial.h>  // Second Serial Port
#include <Adafruit_BME280.h> // Humidity/Pressure/Temperature

#define MEASURE_TIMEOUT 1000
#define LOG_INTERVAL 0001

// BME Definition (Pressure/humidity/temperature)
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

// Light sensor define
#define LIGHT_PIN A0
unsigned short low = 100;
unsigned short high = 800;

// TIME define
#define Hour 11
#define Minute 20
#define Seconde 0
#define Day 21
#define Month 10
#define Year 2022
#define DayWeek "THU"

// Led Define
#define LED_PIN 7

// initialisation of the name of the file with the data
String filename;

DS1307 clock;                    // RTC
File storageSD;                  // SD
Adafruit_BME280 bme;             // I2C
SoftwareSerial SoftSerial(6, 7); // GPS

// GPS structure
typedef struct GPS
{
  String latitude = "Na";
  String longitude = "Na";
} GPS;

// A structure for every type of Sensor data
typedef struct SensorDATA
{
  GPS gps;

  String temp = "Na";
  String press = "Na";
  String alt = "Na";
  String hum = "Na";

  String lightlevel = "Na";

  String time = "Na";
} SensorDATA;

SensorDATA data;

// GPS measures
void measureGPS(SensorDATA *gpsData)
{
  unsigned char buffer[96];
  MicroNMEA nmea(buffer, sizeof(buffer));

  long measurementStartTime = millis();
  while (millis() - measurementStartTime < MEASURE_TIMEOUT)
  {
    if (!SoftSerial.available() || !nmea.process(SoftSerial.read()) || !nmea.isValid())
      continue;
    gpsData->gps.latitude = nmea.getLatitude(); 
    gpsData->gps.longitude = nmea.getLongitude();
    break;
  }
  SoftSerial.end();
}

// Pressure/Humidity/Temperature measures
void measureBME(SensorDATA *bmeData)
{
  long measurementStartTime = millis();
  while ((millis() - measurementStartTime < MEASURE_TIMEOUT) && (data.temp == "Na" || data.press == "Na" || data.alt == "Na" || data.hum == "Na"))
  {
    bmeData->temp = String(bme.readTemperature());
    bmeData->press = String(bme.readPressure() / 100.0F);
    bmeData->alt = String(bme.readAltitude(SEALEVELPRESSURE_HPA));
    bmeData->hum = String(bme.readHumidity());
  }
}

// Light sensor measures
void measureLight(SensorDATA *lightData)
{
  long measurementStartTime = millis();
  while (millis() - measurementStartTime < MEASURE_TIMEOUT && data.lightlevel == "Na")
  {
    unsigned short lightValue = analogRead(LIGHT_PIN);
    if (lightValue <= low)
    {
      lightValue = low;
    }
    if (lightValue >= high)
    {
      lightValue = high;
    }
    lightData->lightlevel = String(lightValue);
  }
}

// clock measures
void timeRecup(SensorDATA *timeData)
{
  long measurementStartTime = millis();
  while (millis() - measurementStartTime < MEASURE_TIMEOUT && data.time == "Na")
  {
    clock.getTime();
    timeData->time = String(clock.hour) + ":" + String(clock.minute) + ":" + String(clock.second) + ";" + String(clock.month) + "," + String(clock.dayOfMonth) + "," + String(clock.year + 2000) + String(clock.dayOfWeek);
  }
}

// Measures to a single string
String measureData()
{
  measureGPS(&data);
  measureBME(&data);
  measureLight(&data);
  timeRecup(&data);
  return String(data.time + ";" + data.gps.latitude + ";" + data.gps.longitude + ";" + data.temp + ";" + data.press + ";" + data.alt + ";" + data.hum + ";" + data.lightlevel);
}

// Creation of a file
byte createFile(String name) // Function to create a file with a custom name
{
  if (!SD.begin(4)) // If No card detected
  {
    return 1;
  }
  if (SD.exists(name)) // If File already exist
  {
    return 1;
  }
  storageSD = SD.open(name, FILE_WRITE); // Creating the file
  storageSD.close();                     // Closing the file
  return 0;
}

// insertion of the data
byte appendLine(String file, String data) // Function to write data into the file
{
  if (!SD.begin(4)) // If No card detected
  {
    return 1;
  }
  if (!SD.exists(file)) // If File doesn't exist
  {
    createFile(file);
  }
  storageSD = SD.open(file, FILE_WRITE); // Openning of the file
  if (storageSD)
  {
    storageSD.println(data); // Adding the data to the file
    storageSD.close();       // Closing the file
  }
  else // If can't open the file
  {
    return 1;
  }
  return 0;
}

// Copies of the data to another file
byte moveFile(String currentFile, String newFile) // Function to move the content of a file to another file
{
  File FileTemp; // Creation of a temporary storage variable

  if (!SD.begin(4)) // If No card detected
  {
    return 1;
  }

  if (!SD.exists(currentFile)) // If currentFile doesn't exist
  {
    return 1;
  }

  if (!SD.exists(newFile)) // If newFile doesn't exist
  {
    createFile(newFile);
  }

  byte ch;
  FileTemp = SD.open(newFile, FILE_WRITE); // Openning of the file
  if (!FileTemp)                           // If can't open the file
  {
    return 1;
  }

  storageSD = SD.open(currentFile); // Openning of the file
  if (!storageSD)                   // If can't open the file
  {
    return 1;
  }

  while (storageSD.available()) // If read from the file until there's nothing else in it
  {
    ch = storageSD.read();
    FileTemp.write(ch);
  }

  storageSD.close(); // Closing the file
  FileTemp.close();  // Closing the file
  return 0;
}

// Creation of the file name
void generateFileName(String *name, byte revisionNumber)
{
  *name = String(clock.year) + String(clock.month) + String(clock.dayOfMonth) + "_" + String(revisionNumber) + ".csv"; // create name and type of doc
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  clock.begin();
  clock.fillByYMD(Year, Month, Day);
  clock.fillDayOfWeek(DayWeek);
  clock.fillByHMS(Hour, Minute, Seconde);
  clock.setTime();
  unsigned status;
  status = bme.begin(0x76);
  if (!status)
  {
    Serial.println(bme.sensorID(), 16);
    while (1)
    {
      delay(10);
    }
  }
  generateFileName(&filename, 0);
  createFile(filename);
}

void loop()
{

  appendLine(filename, measureData());
  delay(LOG_INTERVAL);
  data.gps.latitude = "Na";
  data.gps.longitude = "Na";
  data.temp = "Na";
  data.press = "Na";
  data.alt = "Na";
  data.hum = "Na";
  data.lightlevel = "Na";
  data.time = "Na";
}