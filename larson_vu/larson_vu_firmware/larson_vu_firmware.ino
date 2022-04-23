#include <FastLED.h>

#include <EEPROM.h>
#include <Arduino.h>

template <class T>
int EEPROM_writeAnything(int ee, const T &value)
{
    const byte *p = (const byte *)(const void *)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
        EEPROM.write(ee++, *p++);
    return i;
}

template <class T>
int EEPROM_readAnything(int ee, T &value)
{
    byte *p = (byte *)(void *)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
        *p++ = EEPROM.read(ee++);
    return i;
}

#define ANIM_AUDIO 0
#define ANIM_LARSON_RED 1
#define ANIM_LARSON_ORANGE 2
#define ANIM_LARSON_YELLOW 3
#define ANIM_LARSON_GREEN 4
#define ANIM_LARSON_BLUE 5
#define ANIM_LARSON_PURPLE 6
#define ANIM_LARSON_RAINBOW 7

#define MODE_OFF 0
#define MODE_SOUND 1
#define MODE_LARSON 2
#define MODE_BOTH 3

#define CONFIGCHECK 14
struct config_t
{
    uint8_t mode; // 0=off, 1=sound only, 2=larson only, 3=both
    uint8_t cur_anim;
} config;

void writeConfig()
{
    EEPROM_writeAnything(1, config);
}

void readConfig()
{
    EEPROM_readAnything(1, config);
}

void writeDefaultConfig()
{
    config.mode = MODE_BOTH;
    config.cur_anim = ANIM_LARSON_RED;
}

#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1

// audio vars
int FreqL[7];
int FreqR[7];

int SumL = 0;
int SumR = 0;

bool mono_audio = true;

// audio clamp values
#define MIN_LEVEL 100
#define MAX_LEVEL 350
#define OUT_MIN 0
#define OUT_MAX 20

// LED stuff
#define NUM_LEDS 40
#define DATA_PIN SPI_DATA
#define CLOCK_PIN SPI_CLOCK
CRGB leds[NUM_LEDS];

uint8_t led_r_start = (NUM_LEDS / 2);
uint8_t led_l_start = led_r_start - 1;

uint8_t last_anim = 1;

unsigned long last_frame = 0;
#define FRAME_TIME 5

unsigned long last_audio = 0;
#define AUDIO_COOLDOWN 1000

int step = 0;

String serial_input;

/********************Setup Loop*************************/
void setup()
{
    // if (EEPROM.read(0) != CONFIGCHECK)
    // {
    //     EEPROM.write(0, CONFIGCHECK);
    //     writeDefaultConfig();
    // }
    readConfig();

    serial_input = "";

    FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(192);

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

    set_anim(config.cur_anim);
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

    if (mono_audio)
    {
        SumR = SumL;
    }
}

void set(uint8_t i, CRGB color)
{
    if (i >= 0 && i < NUM_LEDS)
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
    for (x = led_l_start; x >= 0; x--)
    {
        if (SumL > c)
        {
            leds[x] = CRGB::Orange;
        }
        else
        {
            break;
        }
        c++;
    }

    c = 0;
    for (x = led_r_start; x < NUM_LEDS; x++)
    {
        if (SumR > c)
        {
            leds[x] = CRGB::Orange;
        }
        else
        {
            break;
        }
        c++;
    }

    FastLED.show();
}

uint8_t larson_tail = 15;
int8_t larson_dir = -1;
uint8_t larson_fade = 256 / (larson_tail + 2);
uint8_t larson_divider = 6;
uint8_t larson_sub_step = 0;

void set_anim(uint8_t i)
{
    step = 0;
    config.cur_anim = i;
    last_anim = i;
    larson_dir = -1;
    writeConfig();
}

void anim_larson(CRGB color, bool rainbow = false)
{
    static uint8_t i = 0;
    static int anim_step = 0;
    static uint8_t fade_val = 0;
    static uint8_t hue = 0;

    anim_step = step / larson_divider;

    if (rainbow)
    {
        hue = map(anim_step, 0, NUM_LEDS - 1, 0, 255);
        hue = (hue + larson_sub_step) % 255;
        hsv2rgb_rainbow(CHSV(hue, 255, 255), color);
    }

    set(anim_step, color);

    for (i = 1; i <= larson_tail; i++)
    {
        fade_val = 255 - (larson_fade * i);
        set(anim_step - i, color.nscale8(fade_val));
        set(anim_step + i, color.nscale8(fade_val));
    }

    step += larson_dir;

    if (anim_step >= NUM_LEDS && larson_dir == 1)
    {
        anim_step = (NUM_LEDS - 1) * larson_divider;
        larson_dir = -1;
    }
    else if (anim_step <= 0 && larson_dir == -1)
    {
        step = 0;
        larson_dir = 1;
        larson_sub_step += 5;
    }
}

void do_update_anim()
{
    if (serial_input.length() >= 2)
    {
        if (char(serial_input[1]) >= 49 && char(serial_input[1]) <= 57)
        {
            Serial.print("A");
            Serial.println(serial_input[1]);
            set_anim(char(serial_input[1]) - 48);
            writeConfig();
        }
    }
}

void do_update_mode()
{
    if (serial_input.length() >= 2)
    {
        if (char(serial_input[1]) >= 48 && char(serial_input[1]) <= 51)
        {
            config.mode = char(serial_input[1]) - 48;
            Serial.print("M");
            Serial.println(config.mode);
            writeConfig();
        }
    }
}

void check_serial()
{
    if (Serial.available())
    {
        char c = Serial.read();
        if (c == 10) // newline, end of command
        {
            if (serial_input.length() >= 1)
            {
                switch (serial_input[0])
                {
                case 'A':
                    do_update_anim();
                    break;
                case 'M':
                    do_update_mode();
                    break;
                }
            }
            serial_input = "";
        }
        else
        {
            serial_input += c;
        }
    }
}

void loop()
{
    if(config.mode == MODE_BOTH || config.mode == MODE_SOUND)
    {
        FetchAudio();
    }
    
    check_serial();
    
    if(config.mode == MODE_OFF)
    {
        FastLED.clear();
        FastLED.show();
        delay(5);
        return;
    }

    if (SumL > 0 || SumR > 0)
    {
        last_audio = millis();
    }
    
    if (millis() - last_audio < AUDIO_COOLDOWN && (config.mode == MODE_BOTH || config.mode == MODE_SOUND))
    {
        config.cur_anim = ANIM_AUDIO;
    }
    else if (config.cur_anim == ANIM_AUDIO)
    {
        set_anim(last_anim);
    }

    if (millis() - last_frame > FRAME_TIME)
    {
        last_frame = millis();
        FastLED.clear();
        
        if(config.mode == MODE_BOTH || config.mode == MODE_LARSON)
        {
            switch (config.cur_anim)
            {
            case ANIM_LARSON_RED:
                anim_larson(CRGB::Red);
                break;
            case ANIM_LARSON_ORANGE:
                anim_larson(CRGB::Orange);
                break;
            case ANIM_LARSON_YELLOW:
                anim_larson(CRGB::Yellow);
                break;
            case ANIM_LARSON_GREEN:
                anim_larson(CRGB::Green);
                break;
            case ANIM_LARSON_BLUE:
                anim_larson(CRGB::Blue);
                break;
            case ANIM_LARSON_PURPLE:
                anim_larson(CRGB::Purple);
                break;
            case ANIM_LARSON_RAINBOW:
                anim_larson(CRGB(), true);
                break;
            default:
                anim_audio();
                break;
            }
        }
        else
        {
            anim_audio();
        }
        FastLED.show();
    }
}
