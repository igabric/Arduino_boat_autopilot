void setup(void) {
  // ************ SERIAL MONITOR SETUP ************
  Serial.begin(115200); // For debug
  delay(1000);
  
  // ************ SD CARD INITIALIZATION ************ 
  
  if (!SD.begin(53)) {
    Serial.println(F("SD failed!"));
  }
  else {
    // OPEN NEW TEXT FILE ON SD CARD  
    #ifdef Add_new_POI
      SD.remove(F("tocke.csv"));
      myFile = SD.open(F("tocke.csv"), FILE_WRITE);
      myFile.close();
      add_poi_list();
    #endif
    parse_poi_list();
  }
  
  myFile = SD.open("varijabl.txt", FILE_READ);
  if (myFile) {
    steering_offset = myFile.parseInt();
    lower_speed_limit = myFile.parseInt();
    dop_odstupanje_kursa = myFile.parseInt();
    heading_correction = myFile.parseInt();
    stepper_speed = myFile.parseInt();
    course_COG = myFile.parseInt();
    step_direction_positive = myFile.parseInt();
    gps_reading_smart_delay = myFile.parseInt();
    Max_steering_turning_deg = myFile.parseInt();
    pulley1_teeth = myFile.parseInt();
    pulley2_teeth = myFile.parseInt();
    delay_to_neutral = myFile.parseInt();
    myFile.close();
  }
   
  pinMode(buzzer, OUTPUT); // Set buzzer
  // ************ TFT DISPLAY INITIALIZATION ************
  tft.init();
  tft.invertDisplay(1);
  tft.setRotation(1);
  
  tft.fillScreen(TFT_BLACK);

  // ************ STEPPER SETTINGS ************
  STEPPER_MOTOR.connectToPins(stepPin, dirPin);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, LOW); // disable stepper
  
  // Move motor in degrees of steering angle:
  // StepsPerMillimeter = 4;
  StepsPerMillimeter = int(round((float(pulley2_teeth) / float(pulley1_teeth))*(float(stepsPerRevolution)/360)));
  // StepsPerMillimeter = int(round((pulley2_teeth / pulley1_teeth)*(stepsPerRevolution/360)));
  #ifdef DEBUG
    Serial.print("StepsPerMillimeter: ");
    Serial.println(StepsPerMillimeter);
  #endif 
  STEPPER_MOTOR.setStepsPerMillimeter(StepsPerMillimeter); // set the number of steps per 1 degree turning of the steering wheel
  STEPPER_MOTOR.setSpeedInMillimetersPerSecond(stepper_speed);
  STEPPER_MOTOR.setAccelerationInMillimetersPerSecondPerSecond(StepperAcceleration);
  
  // ************ ROTARY ENCODER SETUP ************
  pinMode(CLK, INPUT);   // Set encoder pins as inputs
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  lastStateCLK = digitalRead(CLK);  // Read the initial state of CLK

  // ************ PUSH BUTTON SETUP ************
  pinMode(PB_1p, INPUT_PULLUP);
  pinMode(PB_10p, INPUT_PULLUP);
  pinMode(PB_1n, INPUT_PULLUP);
  pinMode(PB_10n, INPUT_PULLUP);

  Serial1.begin(9600);
  if(!mag.begin())
  {
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setCursor(50, 160, 4);
    tft.println("Magnetometer sensor error !");
    Serial.println(F("Ooops, no HMC5883 detected ... Check your wiring!"));
    delay(2000);
  }
}

void add_poi_list(){
  File dataFile = SD.open(F("tocke.csv"), FILE_WRITE);
  if (dataFile) {
      dataFile.println(F("Latitude,Longitude,Lokacija"));
      dataFile.println(F("43.495343,16.529534,Strozanac"));
      dataFile.println(F("43.195919,16.365723,Hvar_rtPelegrin"));
      dataFile.println(F("43.223936,16.516944,Hvar_rtKabal"));
      dataFile.println(F("43.452741,16.179312,Drvenik"));
      dataFile.println(F("43.387745,16.552794,Brac_Supetar"));
      dataFile.println(F("43.393104,16.422984,Brac_rtGomilica"));
      dataFile.println(F("43.280239,16.493358,Brac_Smrka"));
      dataFile.println(F("43.362102,16.738663,Brac_Pucisca"));
      dataFile.println(F("43.345844,16.823890,Brac_Luke"));
      dataFile.println(F("43.372425,16.666777,Brac_Lovrecina"));
      dataFile.println(F("43.363082,16.721581,Brac_Cesminova"));
      dataFile.println(F("43.357956,16.771303,Brac_Lozna"));
      dataFile.println(F("43.333443,16.403894,Brac_RT_Zaglav"));
      dataFile.println(F("43.370176,16.683497,Brac_Konopjikova"));
      dataFile.println(F("43.306792,16.430982,Brac_Osibova"));
      dataFile.println(F("43.300424,16.447904,Brac_Lucice"));
      dataFile.println(F("43.390437,16.206188,Solta_Sesula"));
      dataFile.println(F("43.397712,16.201863,Solta_Maslinica"));
      dataFile.println(F("43.365216,16.282547,Solta_Tatinja"));
      dataFile.println(F("43.397442,16.322912,Solta_Necujam"));
      dataFile.println(F("43.375801,16.353505,Solta_Stomorska"));
      dataFile.println(F("43.401091,16.302815,Solta_Rogac"));
      dataFile.println(F("43.499936,16.340179,Ciovo_Slatine"));
      dataFile.println(F("43.493026,16.364040,Ciovo_RT_Supetar"));
      dataFile.println(F("43.483603,16.365788,Ciovo_Prizidinica"));
      dataFile.close();
  }
}

void parse_poi_list(){
  CSV_Parser cp(/*format*/ "ffs", /*has_header*/ true, /*delimiter*/ ',');
  if (cp.readSDfile("tocke.csv")) {
    float *column_1 = (float*)cp["Latitude"];
    float *column_2 = (float*)cp["Longitude"];
    char  **column_3 = (char**)cp["Lokacija"];
    number_of_POI = cp.getRowsCount();
    
    if (column_1 && column_2) {
      for(int row = 0; row < number_of_POI; row++) {
        latArray[row] = column_1[row];
        longArray[row] = column_2[row];
        pointArray[row] = column_3[row];
        Serial.print(pointArray[row]);Serial.print("  |  "); Serial.print(latArray[row],6);Serial.print("  |  "); Serial.println(longArray[row],6);
      }
    } else {
      Serial.println("ERROR: At least 1 of the columns was not found, something went wrong.");
    }
    // uncomment for output parsed values (allows to check that the file was parsed correctly)
    // cp.print(); // assumes that "Serial.begin()" was called before (otherwise it won't work)
  } 
  else {
    Serial.println("ERROR: File called '/tocke.csv' does not exist...");
  }
}
