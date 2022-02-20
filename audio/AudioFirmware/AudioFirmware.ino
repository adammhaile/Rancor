#include "VS1053.h"

#define USB Serial
#define Duet Serial1
#define LED 13

String input; 


void setup() {
  USB.begin(115200); //USB Serial
  Duet.begin(57600); // IO Serial - connected to Duet via IO_1
//  while (!USB) { delay(1); }
  delay(500);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

  begin_audio();

  input = "";
}

void do_play(String filename)
{
  USB.println("PLAY: " + filename);
  if(play_audio(filename))
  {
    for(long i=0;i<5;i++)
    {
      digitalWrite(LED, HIGH);
      delay(750);
      digitalWrite(LED, LOW);
      delay(250);
    }
  }
  else
  {
    for(long i=0;i<10;i++)
    {
      digitalWrite(LED, HIGH);
      delay(500);
      digitalWrite(LED, LOW);
      delay(250);
    }
  }
}

void loop() {
  if(NO_SD)
  {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }
  else if(NO_PLAYER)
  {
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(200);
  }
  else if(Duet.available()) {
    char c = Duet.read();
    if(c == 10) // newline, end of command
    {
      do_play(input);
      input = "";
    }
    else
    {
      input += c;
    }
  }
}
