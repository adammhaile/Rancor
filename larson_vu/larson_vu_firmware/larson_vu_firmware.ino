#define USB Serial
#define Duet Serial1

#define STROBE 16
#define RESET 17
#define DC_One A0
#define DC_Two A1

// Define spectrum variables
int freq_amp;
int Frequencies_One[7];
int Frequencies_Two[7];
int i;

void setup()
{

    memset(Frequencies_One, 0, sizeof(int) * 7);
    memset(Frequencies_Two, 0, sizeof(int) * 7);

    pinMode(STROBE, OUTPUT);
    pinMode(RESET, OUTPUT);
    pinMode(DC_One, INPUT);
    pinMode(DC_Two, INPUT);

    // Initialize Spectrum Analyzers
    digitalWrite(STROBE, LOW);
    digitalWrite(RESET, LOW);
    // digitalWrite(DC_One, LOW);
    // digitalWrite(DC_Two, LOW);
    delay(5);

    USB.begin(57600);
}

void Read_Frequencies()
{
    digitalWrite(RESET, HIGH);
    delayMicroseconds(200);
    digitalWrite(RESET, LOW);
    delayMicroseconds(200);

    // Read frequencies for each band
    for (freq_amp = 0; freq_amp < 7; freq_amp++)
    {
        digitalWrite(STROBE, HIGH);
        delayMicroseconds(50);
        digitalWrite(STROBE, LOW);
        delayMicroseconds(50);

        Frequencies_One[freq_amp] = analogRead(DC_One);
        // Frequencies_Two[freq_amp] = analogRead(DC_Two);
    }
}

void Graph_Frequencies()
{
    for (i = 0; i < 7; i++)
    {
        // USB.print((Frequencies_One[i] + Frequencies_Two[i]) / 2);
        USB.print(Frequencies_One[i]);
        USB.print("    ");
    }
    USB.println();
}

void loop()
{
    Read_Frequencies();
    Graph_Frequencies();
    delay(50);
    
    // digitalWrite(STROBE, LOW);
    // digitalWrite(RESET, LOW);
    // digitalWrite(DC_One, LOW);
    // digitalWrite(DC_Two, LOW);
    
    // delay(1000);
    
    // digitalWrite(STROBE, HIGH);
    // digitalWrite(RESET, HIGH);
    // digitalWrite(DC_One, HIGH);
    // digitalWrite(DC_Two, HIGH);
    
    // delay(1000);
}