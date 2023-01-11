void setup(void) {
  // ************ SERIAL MONITOR SETUP ************
  Serial.begin(115200); // For debug
  delay(1000);
  
  // ************ SD CARD INITIALIZATION ************ 
  
  if (!SD.begin(53)) {
    // // Serial.println(F("SD failed!"));
    //return;
  }
  else {
    // OPEN NEW TEXT FILE ON SD CARD  
    #ifdef Add_new_POI
      SD.remove(F("tocke.csv"));
      // // Serial.println(F("Creating tocke.csv..."));
      myFile = SD.open(F("tocke.csv"), FILE_WRITE);
      myFile.close();
      add_poi_list();
    #endif
    parse_poi_list();

//    CSV_Parser csv_cp(/*format*/ "ffs", /*has_header*/ true, /*delimiter*/ ',');
//    if (csv_cp.readSDfile("CUST_POI.csv")) {
//      float *column_1 = (float*)csv_cp["Latitude"];
//      float *column_2 = (float*)csv_cp["Longitude"];
//      char  **column_3 = (char**)csv_cp["Lokacija"];
//      // number_of_POI = csv_cp.getRowsCount();
//      
//      if (column_1 && column_2) {
//        
//          latArray[25] = column_1[0];
//          longArray[25] = column_2[0];
//          pointArray[25] = column_3[0];
//          Serial.println(pointArray[25]);
//      } else {
//        Serial.println("ERROR: At least 1 of the columns was not found, something went wrong.");
//      }
//      // output parsed values (allows to check that the file was parsed correctly)
//      csv_cp.print(); // assumes that "Serial.begin()" was called before (otherwise it won't work)
//      
//    } else {
//      Serial.println("ERROR: File called '/CUST_POI.csv' does not exist...");
//    }
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
    StepsPerMillimeter = myFile.parseInt();
    myFile.close();
  }
//  if (SD.exists("pois.txt")) {
//    myFile = SD.open("pois.txt", FILE_READ);
//    if (myFile) {
//      int lat_deg_int = myFile.parseInt();
//      int lat_deg_dec12 = myFile.parseInt();
//      int lat_deg_dec34 = myFile.parseInt();
//      int long_deg_int = myFile.parseInt();
//      int long_deg_dec12 = myFile.parseInt();
//      int long_deg_dec34 = myFile.parseInt();
//      
//      latArray[25] = lat_deg_int + float(lat_deg_dec12)/100 + float(lat_deg_dec34)/10000;
//      longArray[25] =  long_deg_int + float(long_deg_dec12)/100 + float(long_deg_dec34)/10000;;
//      pointArray[25] = "CUSTOM_POI";
//      // pointArray[25] = myFile.readStringUntil('\r');
//      Serial.print(latArray[25],4); Serial.print(" | ");
//      Serial.print(longArray[25],4); Serial.print(" | ");
//      Serial.println(pointArray[25]);
//      myFile.close();
//      number_of_POI += 1;
//    }
//  }
  

   
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
  
  // Move one motor in units of millimeters:
  STEPPER_MOTOR.setStepsPerMillimeter(StepsPerMillimeter); // set the number of steps per millimeter
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
//  Kompas_priprema();
//  Inicijalizacija();
//  // ************ COMPASS AND GPS INITIALIZATION ************
//  #ifdef Beitian_BN_880
//     
//    // ************ INITIAL HEADING SETTING AND DISPLAY ON TFT MONITOR ***********
//    Screen_1_navigation();
//    SET_HDG(Calc_heading());
//    time_count = millis();
//  #endif
//  
//  
//  Autopilot(autopilot_ON);
  
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
      // // Serial.println("Kreiran csv file!");
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
    // output parsed values (allows to check that the file was parsed correctly)
    // cp.print(); // assumes that "Serial.begin()" was called before (otherwise it won't work)
  } 
  else {
    Serial.println("ERROR: File called '/tocke.csv' does not exist...");
  }
}
