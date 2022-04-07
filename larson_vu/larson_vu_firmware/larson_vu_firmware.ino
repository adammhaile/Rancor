#include <FastLED.h>

#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1

//globals
int freq_amp;
int FreqL[7];
int FreqR[7];
int SumL = 0;
int SumR = 0;
int minv = 2048;
int maxv = -2048;

// audio clamp values
#define MIN_LEVEL 60
#define MAX_LEVEL 600
#define OUT_MIN 0
#define OUT_MAX 14

//LED stuff
#define NUM_LEDS  30
#define DATA_PIN SPI_DATA
#define CLOCK_PIN SPI_CLOCK
CRGB leds[NUM_LEDS];

int led_r_start = (NUM_LEDS / 2);
int led_l_start = led_r_start - 1;


/********************Setup Loop*************************/
void setup()
{
    FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
    FastLED.setBrightness(32);
    
    // Set spectrum Shield pin configurations
    pinMode(STROBE, OUTPUT);
    pinMode(RESET, OUTPUT);
    pinMode(DC_One, INPUT);
    pinMode(DC_Two, INPUT);

    // Initialize Spectrum Analyzers
    digitalWrite(STROBE, LOW);
    digitalWrite(RESET, LOW);
    delay(5);

    Serial.begin(115200);
    while (!Serial) { delay(1); }
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }

void do_led() { 
	static uint8_t hue = 0;
	Serial.print("x");
	// First slide the led in one direction
	for(int i = 0; i < NUM_LEDS; i++) {
		// Set the i'th led to red 
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show(); 
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(10);
	}
	Serial.print("x");

	// Now go in the other direction.  
	for(int i = (NUM_LEDS)-1; i >= 0; i--) {
		// Set the i'th led to red 
		leds[i] = CHSV(hue++, 255, 255);
		// Show the leds
		FastLED.show();
		// now that we've shown the leds, reset the i'th led to black
		// leds[i] = CRGB::Black;
		fadeall();
		// Wait a little bit before we loop around and do it again
		delay(10);
	}
}

void do_led_audio()
{
    static int x = 0;
    static int c = 0;
    
    FastLED.clear();
    
    c = 0;
    for(x=led_l_start; x>=0; x--)
    {
        if(SumL > c)
        {
            leds[x] = CRGB(255, 0, 0);
        }
        else
        {
            break;
        }
        c++;
    }
    
    c = 0;
    for(x=led_r_start; x<NUM_LEDS; x++)
    {
        if(SumR > c)
        {
            leds[x] = CRGB(255, 0, 0);
        }
        else
        {
            break;
        }
        c++;
    }
    
    FastLED.show();
}

void loop()
{
    ReadAudio();
    SumChannels();
    do_led_audio();
}

void ReadAudio()
{
    digitalWrite(RESET, HIGH);
    delayMicroseconds(200);
    digitalWrite(RESET, LOW);
    delayMicroseconds(200);

    for (freq_amp = 0; freq_amp < 7; freq_amp++)
    {
        digitalWrite(STROBE, HIGH);
        delayMicroseconds(50);
        digitalWrite(STROBE, LOW);
        delayMicroseconds(50);

        FreqL[freq_amp] = analogRead(DC_One);
        FreqR[freq_amp] = analogRead(DC_Two);
    }
}

void MapClamp()
{
    SumL = map(SumL, MIN_LEVEL, MAX_LEVEL, OUT_MIN, OUT_MAX);
    SumL = constrain(SumL, OUT_MIN, OUT_MAX);
    SumR = map(SumR, MIN_LEVEL, MAX_LEVEL, OUT_MIN, OUT_MAX);
    SumR = constrain(SumR, OUT_MIN, OUT_MAX);
}

void SumChannels()
{
    static int i = 0;
    SumL = SumR = 0;
    for (i = 0; i < 7; i++)
    {
        SumL += FreqL[i];
        SumR += FreqR[i];
    }
    
    SumL /= 7;
    SumR /= 7;
    
    MapClamp();
    
    // if(SumL < minv) minv = SumL;
    // if(SumL > maxv) maxv = SumL;
    // if(SumR < minv) minv = SumR;
    // if(SumR > maxv) maxv = SumR;
    
    Serial.print(SumL);
    Serial.print(",");
    Serial.print(SumR*-1);
    // Serial.print(",");
    // Serial.print(minv);
    // Serial.print(",");
    // Serial.print(maxv);
    Serial.println();
}
