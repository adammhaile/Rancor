// Specifically for use with the Adafruit Feather, the pins are pre-set here!

// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <SD.h>
#include "Adafruit_VS1053.h"
// These are the pins used
#define VS1053_RESET   -1     // VS1053 reset pin (not used!)

// Feather ESP8266
#if defined(ESP8266)
#define VS1053_CS      16     // VS1053 chip select pin (output)
#define VS1053_DCS     15     // VS1053 Data/command select pin (output)
#define CARDCS          2     // Card chip select pin
#define VS1053_DREQ     0     // VS1053 Data request, ideally an Interrupt pin

// Feather ESP32
#elif defined(ESP32) && !defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2)
#define VS1053_CS      32     // VS1053 chip select pin (output)
#define VS1053_DCS     33     // VS1053 Data/command select pin (output)
#define CARDCS         14     // Card chip select pin
#define VS1053_DREQ    15     // VS1053 Data request, ideally an Interrupt pin

// Feather Teensy3
#elif defined(TEENSYDUINO)
#define VS1053_CS       3     // VS1053 chip select pin (output)
#define VS1053_DCS     10     // VS1053 Data/command select pin (output)
#define CARDCS          8     // Card chip select pin
#define VS1053_DREQ     4     // VS1053 Data request, ideally an Interrupt pin

// WICED feather
#elif defined(ARDUINO_STM32_FEATHER)
#define VS1053_CS       PC7     // VS1053 chip select pin (output)
#define VS1053_DCS      PB4     // VS1053 Data/command select pin (output)
#define CARDCS          PC5     // Card chip select pin
#define VS1053_DREQ     PA15    // VS1053 Data request, ideally an Interrupt pin

#elif defined(ARDUINO_NRF52832_FEATHER )
#define VS1053_CS       30     // VS1053 chip select pin (output)
#define VS1053_DCS      11     // VS1053 Data/command select pin (output)
#define CARDCS          27     // Card chip select pin
#define VS1053_DREQ     31     // VS1053 Data request, ideally an Interrupt pin

// Feather M4, M0, 328, ESP32S2, nRF52840 or 32u4
#else
#define VS1053_CS       6     // VS1053 chip select pin (output)
#define VS1053_DCS     10     // VS1053 Data/command select pin (output)
#define CARDCS          5     // Card chip select pin
// DREQ should be an Int pin *if possible* (not possible on 32u4)
#define VS1053_DREQ     9     // VS1053 Data request, ideally an Interrupt pin

#endif

bool NO_SD = false;
bool NO_PLAYER = false;

/// File listing helper
void printDirectory(File dir) {
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }

    if (entry.isDirectory()) {
      //Serial.println("/");
      //printDirectory(entry);
    } else {
      Serial.println(entry.name());
    }
    entry.close();
  }
}

Adafruit_VS1053_FilePlayer musicPlayer =
  Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);

void begin_audio() {
  if (! musicPlayer.begin()) { // initialise the music player
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
    NO_PLAYER = true;
    return;
  }

  Serial.println(F("VS1053 found"));

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    NO_SD = true;
    return;
  }
  Serial.println("SD OK!");

  // list files
  Serial.println("******Files******");
  printDirectory(SD.open("/"));

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(10, 10);

#if defined(__AVR_ATmega32U4__)
  // Timer interrupts are not suggested, better to use DREQ interrupt!
  // but we don't have them on the 32u4 feather...
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_TIMER0_INT); // timer int
#else
  // If DREQ is on an interrupt pin we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
#endif
}

byte rand_count = 0;
String getRandom(String base)
{
  randomSeed(millis());
  
  int count = 0;
  
  File dir = SD.open("/");
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }


    bool cont = true;
    if (entry.isDirectory()) cont = false;
    
    String name(entry.name());
    if (cont && !name.endsWith(".mp3")) cont = false;

    if(cont && name.startsWith(base + "_"))
    {
      count++;
    }
    entry.close();
  }

  if(count > 0)
  {
    // random sucks on Arduino. This helps it from 
    // repeating the same value 
    long val = (random(count) + rand_count) % count;
    rand_count++;
    String rand_name = base + "_" + String(val);

    String f_name = rand_name + ".mp3";
    if(SD.exists(f_name.c_str()))
    {
      return rand_name;
    }
  }

  return base;
}

bool play_audio(String filename)
{
  if(filename.startsWith("*"))
  {
    filename.remove(0, 1);
    Serial.println("RANDOM");
    Serial.print(filename);
    Serial.print(" > ");
    filename = getRandom(filename);
    Serial.println(filename);
  }
  
  filename = "/" + filename + ".mp3";
  if (SD.exists(filename.c_str()))
  {
    musicPlayer.startPlayingFile(filename.c_str());
    return true;
  }
  else
  {
    Serial.println("Unable to load: " + filename);
    return false;
  }
}
