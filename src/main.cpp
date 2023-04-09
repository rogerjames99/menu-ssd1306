#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <KeyDetector.h>
#include <GEM_adafruit_gfx.h>
#include <Fonts/FreeSans24pt7b.h>

static int LED = D13;

static const uint8_t BUTTON_1 = 1;
static const uint8_t BUTTON_2 = 2;
static const uint8_t BUTTON_3 = 3;
static const uint8_t BUTTON_4 = 4;

static const uint8_t button1_Pin = 4;
static const uint8_t button2_Pin = 5;
static const uint8_t button3_Pin = 6;
static const uint8_t button4_Pin = 7;

static const uint8_t NUMBER_OF_BUTTONS  = 4;

Key buttons[NUMBER_OF_BUTTONS] = {
    {GEM_KEY_UP, button1_Pin},
    {GEM_KEY_DOWN, button2_Pin},
    {GEM_KEY_CANCEL, button3_Pin},
    {GEM_KEY_OK, button4_Pin}
    };

KeyDetector keyDetector(buttons, NUMBER_OF_BUTTONS, 15, 16, true);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16
static const unsigned char PROGMEM logo_bmp[] =
    {0b00000000, 0b11000000,
     0b00000001, 0b11000000,
     0b00000001, 0b11000000,
     0b00000011, 0b11100000,
     0b11110011, 0b11100000,
     0b11111110, 0b11111000,
     0b01111110, 0b11111111,
     0b00110011, 0b10011111,
     0b00011111, 0b11111100,
     0b00001101, 0b01110000,
     0b00011011, 0b10100000,
     0b00111111, 0b11100000,
     0b00111111, 0b11110000,
     0b01111100, 0b11110000,
     0b01110000, 0b01110000,
     0b00000000, 0b00110000};


// Menu pages
GEMPage menuPageMain("Main");

bool switch1;
GEMItem switch_1("Switch 1", switch1);

// Create menu object of class GEM_adafruit_gfx. Supply its constructor with reference to display object we created earlier
// GEM_adafruit_gfx menu(display, GEM_POINTER_ROW, GEM_ITEMS_COUNT_AUTO);

//void setupMenu() {
//  menuPageMain.addMenuItem(switch_1);
//  menu.setMenuPageCurrent(menuPageMain);
//}

void setup() {
    pinMode(LED, OUTPUT);
    Serial.begin(9600);

    Serial.printf("\nInitialising Wire\n");
    Wire.begin();


    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    Serial.printf("About to show logo\n");
    display.display();
    Serial.printf("Displaying logo\n");

    // Clear the buffer
    //display.clearDisplay();
    //display.display();

    //setupMenu();
    //menu.drawMenu();
}

void loop() {
    digitalToggle(LED);
    delay(200);
}

