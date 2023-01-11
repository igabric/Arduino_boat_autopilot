  /*   GRADAC - AUTOPILOT v0
 *     
 *   >>> Beitian_BN_880 connection <<<
 *                            SDA - D20
 *                            SCL - D21
 *                            GND - GND
 *                            VCC - 5V
 *                            TX  - D18
 *                            RX  - D19
 * 
 *   >>> Rotary encoder KY - 040 <<<
 *                            CLK - D7
 *                            DT  - D6
 *                            SW  - D5
 *                            VCC - 5V
 *                            GND - GND
 *                            
 *   >>> PUSH BUTTONS <<<                         
 *                            PB_1 positive degree - D8   
 *                            PB_10 positive degree - D9   
 *                            PB_1 negative degree - D10
 *                            PB_1 negative degree - D11
 *                            
 *   >>> STEPPER DRIVER TB6600 <<<
 *                            stepPin   - D14;  
 *                            dirPin    - D15;  
 *                            enablePin - D16;
 *                             
 *   >>> 4 Channel 433MHz RF <<<                           
 *                            D0 - D2
 *                            D1  - D12
 *                            D2  - D13
 *                            D3  - D17
 *                            VCC - 5V
 *                            GND - GND   
 *   
 *   >>> BUZZER <<< 
 *                            VCC - D3
 *                            GND - GND
 */

/*
 Adafruit HMC5883 library for magnentometer/compass sensor

 TinyGPSPlus library for GPS sensor
 
 An example analogue meter using a HX8357 TFT LCD screen

 Needs Font 2 (also Font 4 if using large scale label)

 Make sure all the required fonts are loaded by editting the
 User_Setup.h file in the TFT_HX8357 library folder.

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  ######       TO SELECT THE FONTS AND PINS YOU USE, SEE ABOVE       ######
  #########################################################################
*/

// Define meter size as multiplier ot 240 pixels wide 1.0 and 1.3333 work OK
// #define M_SIZE 1.333
// #include <avr/dtostrf.h> // Only needed by Due
// ***>>>>>>>>>>>>>> DEMO or GPS <<<<<<<<<<<<<<***

// ************  DEBUGING  ****************

// ************  DEBUGING  ****************


#define Beitian_BN_880
// #define Demo
// #define Add_new_POI
// #define TinyGPS_PLUS


// ***>>>>>>>>>>>>>>             <<<<<<<<<<<<<<***



#include <math.h>
#include <SD.h>
#include <CSV_Parser.h>
File myFile;
#include <AccelStepper.h> 
// #include <SoftwareSerial.h>
#include <TFT_HX8357.h> // Hardware-specific library
TFT_HX8357 tft = TFT_HX8357();       // Invoke custom library




#define motorInterfaceType 1

//***   KORAČNI MOTORI - PIN   ***
#define stepPin 14 
#define dirPin  15
#define enablePin 16

//***   4 Channel 433MHz RF   ***
#define button1 2
#define button2 12
#define button3 13
#define button4 17


// *** ROTARY ENCODER PINOUT AND VARIABLE ***
#define CLK 7
#define DT 6
#define SW 5

// *** PUSH BUTTONS ***
#define PB_1p 9
#define PB_10p 8
#define PB_1n 11
#define PB_10n 10

// *** BUZZER ***
#define buzzer 3

bool autopilot_ON = false;
bool autopilot_heading = true;

const int stepsPerRevolution = 200;
AccelStepper STEPPER_MOTOR(motorInterfaceType, stepPin, dirPin);
//long stepper_position = 0;
// int counter = 0;
int time_count = 0;

// int currentStateCLK;
int lastStateCLK;
// String currentDir;

// unsigned long lastButtonPress = 0;
// SoftwareSerial ss(19, 18);
#ifdef Beitian_BN_880

  #include <TinyGPSPlus.h>
  TinyGPSPlus gps; // The TinyGPSPlus object

  
  //#include <NeoSWSerial.h> // Is possible to use common SoftwareSerial library
  #include <Wire.h>
  #include <Adafruit_Sensor.h>
  #include <Adafruit_HMC5883_U.h>
  Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
  
  // static const int RXPin = 4, TXPin = 3;
  // SoftwareSerial ss(RXPin, TXPin);
  // static const uint32_t GPSBaud = 4800;
  // The TinyGPSPlus object
  
  // The serial connection to the GPS device
  
  
  // NeoSWSerial ss(4, 3); // RX, TX - correct to match
  float gps_long;
  float gps_lat;
  float gps_long_anc;
  float gps_lat_anc;
  
#endif

float declinationAngle = 0.0788; // Milna - Brač
int Heading_reading;
int difference = 0;
int number_of_POI;
int POI_selection;
float custom_POI_long;
float custom_POI_lat;
// *******************************************************************
// KOMPAS
// #define TFT_GREY 0x5AEB
// #define M_SIZE 0.8

// >>>>>>>>>>>>>>>>>>>> #define offset_x 80
// >>>>>>>>>>>>>>>>>>>> #define offset_y 0

//String kurs_labels[] = {"N", "30", "60", "E", "120", "150", "S", "210", "240", "W", "300", "330",
//                        "N", "30", "60", "E", "120", "150", "S", "210", "240", "W", "300", "330"};

//// KORIŠTENJE FLASH MEMORIJE (ROM) ZA POHRANU POLJA STRINGOVA kurs_labels I KONSTANTE dop_odstupanje_kursa
const char string_0[] PROGMEM = "N";
const char string_1[] PROGMEM = "30";
const char string_2[] PROGMEM = "60";
const char string_3[] PROGMEM = "E";
const char string_4[] PROGMEM = "120";
const char string_5[] PROGMEM = "150";
const char string_6[] PROGMEM = "S";
const char string_7[] PROGMEM = "210";
const char string_8[] PROGMEM = "240";
const char string_9[] PROGMEM = "W";
const char string_10[] PROGMEM = "300";
const char string_11[] PROGMEM = "330";
const char string_12[] PROGMEM = "N";
const char string_13[] PROGMEM = "30";
const char string_14[] PROGMEM = "60";
const char string_15[] PROGMEM = "E";
const char string_16[] PROGMEM = "120";
const char string_17[] PROGMEM = "150";
const char string_18[] PROGMEM = "S";
const char string_19[] PROGMEM = "210";
const char string_20[] PROGMEM = "240";
const char string_21[] PROGMEM = "W";
const char string_22[] PROGMEM = "300";
const char string_23[] PROGMEM = "330";

const char *const kurs_labels[] PROGMEM = {string_0, string_1, string_2, string_3, string_4, string_5, string_6, string_7, string_8, string_9, string_10, string_11,
                                           string_12, string_13, string_14, string_15, string_16, string_17, string_18, string_19, string_20, string_21, string_22, string_23};


char buffer[10];

int dop_odstupanje_kursa = 5;
int steering_offset = 2;


// int label_offset = 2;
// int pozicija;
// int pomak_oznaka;
// int input;
// String inString = "";
// float ltx = 0;    // Saved x coord of bottom of needle
// uint16_t osx = M_SIZE*120, osy = M_SIZE*120; // Saved x & y coords
// uint16_t osx = 0.8*120, osy = 0.8*120; // Saved x & y coords
// uint32_t updateTime = 0;       // time for next update
// int old_analog =  -999; // Value last displayed
// int value[6] = {0, 0, 0, 0, 0, 0};
// int old_value[6] = { -1, -1, -1, -1, -1, -1};
// int d = 0;
float hdg_set_value = 11; // VARIJABLA ZA SPREMANJE ŽELJENOG KURSA (Heading)
float cog = 252.1;
float sog = 12.2;
// *******************************************************************
// *******************************************************************
// POKAZIVAČ BRZINE
//int delta_x = 140;       // POLOŽAJ x INSTRUMENTA BRZINE
//int delta_y = 220;     // POLOŽAJ y INSTRUMENTA BRZINE

// *******************************************************************
File myfile;
long x, y;
String loc, loc2;
float longArray[26] = {};
float latArray[26] = {};
String pointArray[26] = {};
bool sign_custom_POI = false; // varijabla za provjeru prethodnog unosa CUSTOM POI
// *********** FUNCTION DECLARATRION ***********
void Kompas_priprema();
#ifdef Declination
  float Calc_declination(float longitude, float latitude, uint8_t godina, uint8_t mjesec, uint8_t dan);
#endif Declination
float rot_encoder(float value, int dec_plc);
float rot_encoder_CUSTOM_coordinate(int max_val, String text);
void rot_encoder_CUSTOM_POI();
void SET_HDG(float hdg_set_value);
void Navigate_by_POI();
void Lat_Long(float latitude, float longitude);
void Cog_Sog(float cog, float sog);
void Time_TFT(int sati, int minuta, int posx = 0, int posy = 60, int letter_size = 2);
void Label(String labela, int posx, int posy, int letter_size, String colour_fore = "green");
void Date_TFT(int dan, int mjesec, int godina);
void Sateliti_TFT(int sat_num);
int Calc_heading();
bool readLine(File &f, char* line, size_t maxLen);
bool readVals(long* v1, long* v2, String* loc, String* loc2);
String Leading_space(int number, int number_of_place);
void HELP_scr1();
void HELP_scr2();
// float Udaljenost(double lat1, double long1, double lat2, double long2);
