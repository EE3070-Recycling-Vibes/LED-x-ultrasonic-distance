#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    7
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

int trigPin = 13;
int echoPin = 12;
int LED;
float duration, distance;

void setup() {
    delay( 1000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(BRIGHTNESS);
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop()
{  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = (duration / 2) * 0.0343;
  //LED = distance;

  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */    //change color
    
  FillLEDsFromPaletteColors( startIndex);     //fill color
    
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.print(" cm");
  Serial.print(" LED = ");
  Serial.println(LED);
  FastLED.clear();
 
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    LED = 9 - round(0.6 * distance);
    for( int i = LED-1; i >= 0; i--) {    //change num here
        leds[6-i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }

}
