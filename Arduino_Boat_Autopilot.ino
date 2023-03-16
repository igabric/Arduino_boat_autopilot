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
 *                            stepPin -      - D14;  
 *                            dirPin -       - D15;  
 *                            enablePin -    - D16;
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
 *                            
 *                            
 *   >>> THERMISTOR PTC 100k <<<                         
 *                            wire1 - 5V
 *                            wire2 - A4   
 *                            resistor 100k: A4 - GND   
 */

#define Beitian_BN_880
#define TIME_ZONE
// #define NON_BLOCKING
// #define Add_new_POI
#define DEBUG



// ***>>>>>>>>>>>>>>             <<<<<<<<<<<<<<***

#ifdef TIME_ZONE
  #include <Timezone.h>
  time_t local, utc;
  // Change these two rules corresponding to your timezone, see https://github.com/JChristensen/Timezone
  // Central European Time (Frankfurt, Paris)  120 = +2 hours in daylight saving time (summer).
  TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120};
  // Central European Time (Frankfurt, Paris)  60  = +1 hour in normal time (winter)
  TimeChangeRule CET = {"CET ", Last, Sun, Oct, 3, 60};
  Timezone CE(CEST, CET);
#endif

#include <math.h>
#include <SD.h>
#include <CSV_Parser.h>
File myFile;
#include <SpeedyStepper.h> // https://github.com/Stan-Reifel/SpeedyStepper/blob/master/Documentation.md
#include <TFT_HX8357.h> // TFT_LCD library
TFT_HX8357 tft = TFT_HX8357();       


//***   STEPPER MOTOR - PINS   ***
#define stepPin 14 
#define dirPin  15
#define enablePin 16

//***   4 Channel 433MHz RF   ***
#define button1 2
#define button2 12
#define button3 13
#define button4 17

// *** ROTARY ENCODER PINOUT AND VARIABLES ***
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

// Thermistor
#define THERMISTOR
int thermistorPin = A4;
int Vo; // Holds the ADC Value
float R2, tKelvin, tCelsius;
const float Beta     = 3974.0;
const float roomTemp = 298.15;   // room temperature in Kelvin
const float Ro = 10000.0; // Resistance of the thermistor at roomTemp
const float R1 = 9710.0;  // Resistnce of the known resistor
float temp;

// System SETUP
bool autopilot_ON = false;
bool autopilot_heading = true;
bool steering = false;
long time_count;
bool dir = true;
int course_COG  = 1;
int step_direction_positive = 0; // settin positive turning of steering wheel
int gps_reading_smart_delay = 5; // delay in sec
int stepsPerRevolution = 200;
SpeedyStepper STEPPER_MOTOR;
int lastStateCLK;
int delay_to_neutral = 5; // seconds

//***   TIME BELT PULLEYS   ***
int pulley1_teeth = 18;// Number of teeth on smaller pulley
int pulley2_teeth = 120; // Number of teeth on larger pulley
int Max_steering_turning_deg = 120;

#ifdef Beitian_BN_880
  #include <TinyGPSPlus.h>
  TinyGPSPlus gps; // The TinyGPSPlus object
  #include <Wire.h>
  #include <Adafruit_Sensor.h>
  #include <Adafruit_HMC5883_U.h>
  Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);  
  double gps_long;     // GPS variable for current position storing
  double gps_lat;      // GPS variable for current position storing
  double gps_long_anc; // GPS variable for anchoring
  double gps_lat_anc;  // GPS variable for anchoring
#endif
// STEPPER SETTINGS

int StepsPerMillimeter = 4; // stepper initialisation - change if necessary
int StepperAcceleration = 1000; // mm/sec^2

float declinationAngle = 0.0788; // Milna - Brač - change acording your location
float Heading_reading;
int difference = 0; // variable for storing deviation of the actual bearing value from the desired value
int number_of_POI;  // variable to storing number of POI (stored on the SD card)
int POI_selection;  // variable for remember selected POI
float custom_POI_long; // variable for custom position storing - it is enabled to store only one current position
float custom_POI_lat;  // variable for custom position storing - it is enabled to store only one current position
float course_over_ground;
float speed_knots;
int lower_speed_limit = 3;
int stepper_speed = 5;
float CEP = 2; // Accuracy Position Horizontal : 2.0 m CEP  for Beitian BN-880 module
// *******************************************************************
//// USING FLASH MEMORY (ROM) FOR SAVING STRINGS kurs_labels AND CONSTANT dop_odstupanje_kursa
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

int heading_correction = 108;
int dop_odstupanje_kursa = 10;
int steering_offset = 20;
bool steering_neutral = true;
float hdg_set_value = 180; // VARIABLE FOR SAVING THE DESIRED COURSE (Heading)
float cog = 252.1;
float sog = 12.2;
File myfile;
long x, y;  
String loc, loc2;
float longArray[26] = {};
float latArray[26] = {};
String pointArray[26] = {};
bool sign_custom_POI = false; // variable for checking the previous CUSTOM POI entry
// *********** FUNCTION DECLARATRION ***********
void Compas_preparation();
#ifdef Declination
  float Calc_declination(float longitude, float latitude, uint8_t godina, uint8_t mjesec, uint8_t dan);
#endif Declination
float rot_encoder(float value, int dec_plc);
float rot_encoder_CUSTOM_coordinate(int max_val, String text);
float rot_encoder_SET_CUSTOM_COORDINATE(int x_pos, int y_pos, int max_val, int text_size, int min_val = 0, int leading = 2, int custom_value = 0);
void rot_encoder_CUSTOM_POI();
void SET_HDG(float hdg_set_value);
void Navigate_by_POI();
void Lat_Long(float latitude, float longitude);
void Cog_Sog(float cog, float sog);
void Time_TFT(int sati, int minuta, int posx = 0, int posy = 60, int letter_size = 2);
void Label(String labela, int posx, int posy, int letter_size, String colour_fore = "green");
void Date_TFT(int dan, int mjesec, int godina);
void Satelites_TFT(int sat_num);
int Calc_heading();
bool readLine(File &f, char* line, size_t maxLen);
bool readVals(long* v1, long* v2, String* loc, String* loc2);
String Leading_space(int number, int number_of_place);
void HELP_scr1();
void HELP_scr2();
void Screen_1_navigation();
