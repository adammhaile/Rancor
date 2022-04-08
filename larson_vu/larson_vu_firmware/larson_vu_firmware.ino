#include <FastLED.h>

#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1

//audio vars
int FreqL[7];
int FreqR[7];

int SumL = 0;
int SumR = 0;

bool mono_audio = true;

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

uint8_t led_r_start = (NUM_LEDS / 2);
uint8_t led_l_start = led_r_start - 1;

uint8_t last_anim = 1;
uint8_t cur_anim = 1;

#define ANIM_AUDIO 0
#define ANIM_LARSON_RED 1

unsigned long last_frame = 0;
#define FRAME_TIME 5

unsigned long last_audio = 0;
#define AUDIO_COOLDOWN 1000
CRGB AudioColor(215,95,0);

int step = 0;


/********************Setup Loop*************************/
void setup()
{
    FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(64);
    
    // Set spectrum Shield pin configurations
    pinMode(STROBE, OUTPUT);
    pinMode(RESET, OUTPUT);
    pinMode(DC_One, INPUT);
    pinMode(DC_Two, INPUT);

    // Initialize Spectrum Analyzers
    digitalWrite(STROBE, LOW);
    digitalWrite(RESET, LOW);
    delay(5);

    Serial.begin(57600);
    // while (!Serial) { delay(1); }
    
    set_anim(ANIM_LARSON_RED);
}

void FetchAudio()
{
    digitalWrite(RESET, HIGH);
    delayMicroseconds(200);
    digitalWrite(RESET, LOW);
    delayMicroseconds(200);

    static int freq_amp = 0;
    for (freq_amp = 0; freq_amp < 7; freq_amp++)
    {
        digitalWrite(STROBE, HIGH);
        delayMicroseconds(50);
        digitalWrite(STROBE, LOW);
        delayMicroseconds(50);

        FreqL[freq_amp] = analogRead(DC_One);
        FreqR[freq_amp] = analogRead(DC_Two);
    }
    
    static int i = 0;
    SumL = SumR = 0;
    for (i = 0; i < 7; i++)
    {
        SumL += FreqL[i];
        SumR += FreqR[i];
    }
    
    SumL /= 7;
    SumR /= 7;
    
    SumL = map(SumL, MIN_LEVEL, MAX_LEVEL, OUT_MIN, OUT_MAX);
    SumL = constrain(SumL, OUT_MIN, OUT_MAX);
    SumR = map(SumR, MIN_LEVEL, MAX_LEVEL, OUT_MIN, OUT_MAX);
    SumR = constrain(SumR, OUT_MIN, OUT_MAX);
    
    if(mono_audio)
    {
        SumR = SumL;
    }
}

void set(uint8_t i, CRGB color)
{
    if(i >= 0 && i < NUM_LEDS)
    {
        leds[i] = color;
    }
}

void anim_audio()
{
    static int x = 0;
    static int c = 0;
    
    FastLED.clear();
    
    c = 0;
    for(x=led_l_start; x>=0; x--)
    {
        if(SumL > c)
        {
            leds[x] = AudioColor;
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
            leds[x] = AudioColor;
        }
        else
        {
            break;
        }
        c++;
    }
    
    FastLED.show();
}

uint8_t larson_tail = 5;
int8_t  larson_dir = -1;
uint8_t larson_fade = 256 / (larson_tail + 2);
uint8_t larson_divider = 6;
uint8_t larson_sub_step = 0;

void set_anim(uint8_t i)
{
    step = 0;
    cur_anim = i;
    last_anim = i;
    larson_dir = -1;
}

void anim_larson(CRGB color, bool rainbow=false)
{
    static uint8_t i = 0;
    static int anim_step = 0;
    static uint8_t fade_val = 0;
    static uint8_t hue = 0;
    
    anim_step = step / larson_divider;
    
    if(rainbow)
    {
        hue = map(anim_step, 0, NUM_LEDS-1, 0, 255);
        hue = (hue + larson_sub_step) % 255;
        hsv2rgb_rainbow(CHSV(hue, 255, 255), color);
    }
    
    set(anim_step, color);
    
    for(i=1; i<=larson_tail; i++)
    {
        fade_val = 255 - (larson_fade * i);
        set(anim_step-i, color.nscale8(fade_val));
        set(anim_step+i, color.nscale8(fade_val));
    }

    step += larson_dir;
    
    if(anim_step >= NUM_LEDS && larson_dir == 1)
    {
        anim_step = (NUM_LEDS-1) * larson_divider;
        larson_dir = -1;
    }
    else if(anim_step <= 0 && larson_dir == -1)
    {
        step = 0;
        larson_dir = 1;
        larson_sub_step += 5;
    }
}

void loop()
{
    FetchAudio();
    
    if(SumL > 0 || SumR > 0)
    {
        last_audio = millis();
    }
    
    if(millis() - last_audio < AUDIO_COOLDOWN)
    {
        cur_anim = ANIM_AUDIO;
    }
    else if(cur_anim == ANIM_AUDIO)
    {
        set_anim(last_anim);
    }
    
    if(millis() - last_frame > FRAME_TIME)
    {
        last_frame = millis();
        FastLED.clear();
        switch(cur_anim)
        {
            case ANIM_LARSON_RED:
                // anim_larson(CRGB(255, 0, 0));
                anim_larson(AudioColor);
                //anim_larson(CRGB(), true);
                break;
            default:
                anim_audio();
                break;
        }
        
        // leds[0] = CRGB(0, 255, 0);
        FastLED.show();
    }
}

