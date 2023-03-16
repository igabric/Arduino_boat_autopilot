// ************************************************************************************************

//                                         AUTOPILOT MODULE
//                                AUTOMATIC STEERING BY HEADING OR BY POI

// ************************************************************************************************
void Autopilot(bool ukljucen){
  int x_pos = 220; 
  int y_pos = 130;
  bool dir = true;
  float acc;
  if(ukljucen){
    tft.fillScreen(TFT_BLACK);
    // hdg_set_value = int(rot_encoder(int(hdg_set_value), 0, 360, "Heading SET:"));
    hdg_set_value = Calc_heading();
    tft.setTextColor(TFT_YELLOW);
    tft.drawString("Heading:        ", 10, 110, 4);
    SET_HDG(hdg_set_value);
    delay(100);
          
    if (autopilot_heading){
        
      Compas_preparation();
      tft.setTextColor(TFT_GREEN, TFT_BLACK);
      tft.setCursor(x_pos, y_pos, 4);  tft.print("Pilot ON   ");
      tft.fillCircle(x_pos + 150,y_pos, 20,  TFT_GREEN);
      time_count = millis();
      int prolaz_vrij = 0;
      while (digitalRead(PB_1p) == HIGH or digitalRead(PB_10p) == HIGH){ // Autopilot - heading on until the buttons (PB_1p and PB_10p) are pressed at the same time 
        prolaz_vrij += 1;
        if(prolaz_vrij == 10){
          temp = temperatura(); 
          tft.setTextColor(TFT_YELLOW, TFT_BLACK);
          tft.setCursor(110, 60, 4);
          tft.print(temp, 0);
          tft.setCursor(140, 60, 4);
          tft.print("C");
          prolaz_vrij = 0;
        }
        if (gps.time.isValid()){
          #ifdef TIME_ZONE
            setthetime();
            utc = now();  // read the time in the correct format to change via the TimeChangeRules
            local = CE.toLocal(utc);
            Time_TFT(hour(local), minute(local));   
          #else
            Time_TFT(gps.time.hour(), gps.time.minute());
            // // // Serial.println("Time updated!");
          #endif  
        }
        else{Time_TFT(0,0);}
        if (gps.date.isValid()){Date_TFT(gps.date.day(), gps.date.month(), gps.date.year());}
        else{Date_TFT(0,0,1900);}

        if (course_COG == 1){
          if (gps.course.isValid()){
            course_over_ground = gps.course.deg();
            Kompas_labels(int(course_over_ground));         
          }
          else{
            
            Kompas_labels(0);
          }
        }
        else{
          course_over_ground = Calc_heading();
          Kompas_labels(int(course_over_ground));
        }
        if (gps.speed.isValid()){
          speed_knots = gps.speed.knots();
          Cog_Sog(gps.course.deg() , speed_knots);
        }   
        else{
          Cog_Sog(0, 0);
        } 
        if (gps.satellites.isValid()){Satelites_TFT(gps.satellites.value());}
        else{Satelites_TFT(0);} 
        if (gps.hdop.isValid()){
          acc = 2.1 * CEP * float(gps.hdop.value())/100;
          hdop_TFT(acc);
        }
        else{hdop_TFT(0);} 

        Change_heading();

        if (course_COG == 1){
          if (autopilot_ON and gps.course.isValid()){
            Navigate();
          } 
        }
        else {
          if (autopilot_ON){
            Navigate();
          } 
        }
        delay(500);
      }
    }
  }      
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.setCursor(x_pos, y_pos, 4);  tft.print("Pilot OFF   ");
  tft.fillCircle(x_pos + 150, y_pos, 20,  TFT_RED);
  delay(2000);
}  
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                         AUTOPILOT SIGNAL MODULE
//                                       SHOW ON TFT AUTOPILOT STATE

// ************************************************************************************************
void Autopilot_heading_POI(bool ukljucen){
  int x_pos = 160;  
  int y_pos = 100;

  if(ukljucen){
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setCursor(x_pos, y_pos, 2);  tft.print("Heading navigate ");  
    autopilot_heading = true;
  }
  else {
    tft.setTextColor(TFT_ORANGE, TFT_BLACK);
    tft.setCursor(x_pos, y_pos, 2);  tft.print("POI navigate       "); 
    autopilot_heading = false; 
  }
}  
// ------------------------------------------------------------------------------------------------


// ************************************************************************************************

//                                         NAVIGATE BY POI MODULE

// ************************************************************************************************
void Navigate_by_POI(){
  tft.fillScreen(TFT_BLACK);
  Label("Waiting for GPS!", 20, 100, 4, "red");
  float lat_POI = latArray[POI_selection]; float long_POI = longArray[POI_selection];
  float acc;
  double lon1; double lati1; double lon2; double lati2;
  float ttg; int ttg_hours;  int ttg_minutes;  // variables for determining the remaining travel time
  int x_pos; int y_pos; float distanca;
  x_pos = 220; y_pos = 130;
  time_count = millis();  
  tft.fillScreen(TFT_BLACK);  
  Compas_preparation(); 
  Label(pointArray[POI_selection],220, 190, 4,"white"); 

  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setCursor(x_pos, y_pos, 4);  tft.print("Pilot ON   ");
  tft.fillCircle(x_pos + 150,y_pos, 20,  TFT_GREEN);
  int prolaz_vrij = 0;
 
  while (digitalRead(PB_1p) == HIGH or digitalRead(PB_10p) == HIGH){ // Autopilot - heading on until the buttons (PB_1p and PB_10p) are pressed at the same time 
    // Print temperature
    smartDelay(gps_reading_smart_delay * 1000); 
    prolaz_vrij += 1;
    if(prolaz_vrij == 1){
      temp = temperatura(); 
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      tft.setCursor(110, 60, 4);
      tft.print(temp, 0);
      tft.setCursor(140, 60, 4);
      tft.print("C");
      prolaz_vrij = 0;
    }
    // Očitavanje idealnog kursa prema trenutnoj GPS lokaciji
    if (Serial1.available()>0)
      if (gps.encode(Serial1.read()))
        if (gps.location.isValid()){  
          Serial.print("");
        }  
      
// ******************    gps_long = gps.location.lng(); gps_lat = gps.location.lat(); Lat_Long(gps_lat, gps_long);
    if (gps.location.isValid()){  
      gps_long = gps.location.lng(); gps_lat = gps.location.lat();
      Lat_Long(gps_lat, gps_long);
      lon1 = gps_long; lati1 = gps_lat; lon2 = longArray[POI_selection]; lati2 = latArray[POI_selection];
      // ISPIS UDALJENOSTI TRENUTNE POZICIJE DO POI
      distanca = Udaljenost(lon1, lati1, lon2, lati2);
      hdg_set_value = navigateTo(lati1, lon1, lati2, lon2); SET_HDG(hdg_set_value);
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.setCursor(x_pos, 100, 4);  tft.print("LOC UPD");
      
      // smartDelay(gps_reading_smart_delay * 1000);
    }

    
    if (course_COG == 1){
      if (gps.course.isValid()){
        course_over_ground = gps.course.deg();
        Kompas_labels(int(course_over_ground));         
      }
    }
    else{
      course_over_ground = Calc_heading();
      Kompas_labels(int(course_over_ground));
    }
    
    
    // TFT DISPLAY      
    if (gps.time.isValid()){
      #ifdef TIME_ZONE
        setthetime();
        utc = now();  // read the time in the correct format to change via the TimeChangeRules
        local = CE.toLocal(utc);
        Time_TFT(hour(local), minute(local));   
      #else
        Time_TFT(gps.time.hour(), gps.time.minute());
      #endif  
    }
    if (gps.date.isValid()){
      Date_TFT(gps.date.day(), gps.date.month(), gps.date.year());
    }
    if (gps.speed.isValid() and gps.course.isValid()){
      cog = gps.course.deg(); sog = gps.speed.knots(); Cog_Sog(cog, sog);
      lon2 = longArray[POI_selection]; lati2 = latArray[POI_selection];
      distanca = Udaljenost(lon1, lati1, lon2, lati2)/1852;
      ttg = distanca / sog;  ttg_hours = int(ttg); ttg_minutes = int((ttg-int(ttg))*60);
      if (ttg_hours < 100){
        Time_TFT(ttg_hours, ttg_minutes, 300, 225, 4); Label("TTG:", 220, 225, 4,"green");
      }
    }
    else{
      Cog_Sog(0, 0);
      if (course_COG == 1){
        Kompas_labels(0);
      } 
    }
    if (gps.satellites.isValid()){
      Satelites_TFT(gps.satellites.value());
    }
    if (gps.hdop.isValid()){
      acc = 2.1 * CEP * float(gps.hdop.value())/100;
      hdop_TFT(acc);
    }
    
    if (autopilot_ON){
      if (gps.location.isValid() and gps.course.isValid()){ 
        Navigate();
      }
    }
    if (digitalRead(PB_10p) == HIGH and digitalRead(PB_1p) == HIGH and digitalRead(PB_1n) == HIGH and digitalRead(PB_10n) == HIGH and digitalRead(SW)== LOW){
      // select_POI();
      POI_selection = rot_encoder_POI();
      delay(100);
    }    
    tft.setTextColor(TFT_BLACK, TFT_BLACK);
    tft.setCursor(x_pos, 100, 4);  tft.print("LOC UPD");
    // smartDelay(gps_reading_smart_delay * 1000); 
  }
  
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.setCursor(x_pos, y_pos, 4);  tft.print("Pilot OFF   ");
  tft.fillCircle(x_pos + 150, y_pos, 20,  TFT_RED);
  delay(2000);
} 
// ************************************************************************************************

//                             UDALJENOST (lon1, lati1, lon2, lati2)
//                                   vraća duljinu u metrima

// ************************************************************************************************

float Udaljenost(double long1, double lat1, double long2, double lat2){
  char buf1[5];
  double delta = radians(long1-long2);
  double sdlong = sin(delta);
  double cdlong = cos(delta);
  lat1 = radians(lat1);
  lat2 = radians(lat2);
  double slat1 = sin(lat1);
  double clat1 = cos(lat1);
  double slat2 = sin(lat2);
  double clat2 = cos(lat2);
  delta = (clat1 * slat2) - (slat1 * clat2 * cdlong);
  delta = sq(delta);
  delta += sq(clat2 * sdlong);
  delta = sqrt(delta);
  double denom = (slat1 * slat2) + (clat1 * clat2 * cdlong);
  delta = atan2(delta, denom);
  dtostrf(delta * 6372795/1852, 8, 2, buf1);
  tft.drawString("Dist:", 410, 160, 4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawRightString(buf1, 470, 190, 4); 
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawString("nm", 420, 210, 4);
  return delta * 6372795 / 1852; 
}
// ************************************************************************************************

//                             Distance_m (lon1, lati1, lon2, lati2)
//                                  returns the length in meters

// ************************************************************************************************

float Distance_m(double long1, double lat1, double long2, double lat2){
  char buf1[5];
  double delta = radians(long1-long2);
  double sdlong = sin(delta);
  double cdlong = cos(delta);
  lat1 = radians(lat1);
  lat2 = radians(lat2);
  double slat1 = sin(lat1);
  double clat1 = cos(lat1);
  double slat2 = sin(lat2);
  double clat2 = cos(lat2);
  delta = (clat1 * slat2) - (slat1 * clat2 * cdlong);
  delta = sq(delta);
  delta += sq(clat2 * sdlong);
  delta = sqrt(delta);
  double denom = (slat1 * slat2) + (clat1 * clat2 * cdlong);
  delta = atan2(delta, denom);
  dtostrf(delta * 6372795, 8, 2, buf1);
  tft.drawString("Dist:", 410, 160, 4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawRightString(buf1, 470, 190, 4); 
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawString("m", 420, 210, 4);
  return delta * 6372795; 
}
// ************************************************************************************************

//                                   hdg_set_value_promjena (heading)
//                                   validates and prints the course

// ************************************************************************************************
void hdg_set_value_promjena(int broj){
  hdg_set_value += broj;  
  if (hdg_set_value > 359){
    hdg_set_value -= 360;
  }  
  if (hdg_set_value < 0){
    hdg_set_value += 360;
  }
  SET_HDG(hdg_set_value);
  delay(100);
}
// ************************************************************************************************

//                                   smartDelay(time_in_ms)
//                               

// ************************************************************************************************
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial1.available()>0)
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}
// ************************************************************************************************
//                                            Navigate()
//                                         navigation to POI 
// ************************************************************************************************
void Navigate(){
  int x_pos = 220; 
  int y_pos = 130;
  String buf1;
  // Comparison of the current and optimal course and its correction using the autopilot
  // COURSE CORRECTION IF THE DEVIATION IS GREATER THAN THE INITIALLY SET NUMBER OF DEGREES
  if (millis() - time_count > delay_to_neutral*1000){
//    if (gps.speed.isValid() and gps.course.isValid()){
    if (course_COG == 1){
      if (gps.course.isValid()){
        course_over_ground = gps.course.deg();
        Kompas_labels(int(course_over_ground));  
      }
    }
    else{
      course_over_ground = Calc_heading();
      Kompas_labels(int(course_over_ground));
    } 
    if (gps.speed.isValid()){
      speed_knots = gps.speed.knots();
    }
    else {speed_knots = 0.1;}
    Kompas_labels(int(course_over_ground));
    if (speed_knots > lower_speed_limit){
      if (course_COG == 1){
        if (gps.course.isValid()){
          course_over_ground = gps.course.deg();
          Kompas_labels(int(course_over_ground));  
        }
      }
      else{
        course_over_ground = Calc_heading();
        Kompas_labels(int(course_over_ground));
      } 
      
      difference = course_over_ground - hdg_set_value;
      if (abs(difference)>180){
        if(difference<0){
          difference+=360;
        }
        else{
          difference-=360;
        }
      }        
      if (abs(difference) > dop_odstupanje_kursa and difference > 0 and steering == false){
        tft.setTextColor(TFT_PINK, TFT_BLACK);
        tft.setCursor(x_pos, y_pos, 4);  tft.print("STEERING    ");
        tft.fillCircle(x_pos + 150, y_pos, 20,  TFT_PINK);
        digitalWrite(enablePin, HIGH); // enable stepper
        temp = temperatura(); // Serial.print("Temperatura = ");Serial.println(temp,2);
// *****************************************************************************************
        Stepper_move_position(1);   
// *****************************************************************************************
        digitalWrite(enablePin, LOW); // disable stepper
        tft.fillCircle(x_pos + 150,y_pos, 20,  TFT_GREEN);
        time_count = millis();
        steering = true;
        steering_neutral = false;
        dir = true;
        tft.setTextColor(TFT_BLACK, TFT_BLACK);
        tft.setCursor(x_pos, y_pos, 4);  tft.print("STEERING    ");
        tft.setTextColor(TFT_GREEN, TFT_BLACK);        
        tft.setCursor(x_pos, y_pos, 4);  tft.print("Pilot ON   ");        
      }
      if (abs(difference) > dop_odstupanje_kursa and difference < 0 and steering == false){
        tft.setTextColor(TFT_PINK, TFT_BLACK);
        tft.setCursor(x_pos, y_pos, 4);  tft.print("STEERING    ");
        tft.fillCircle(x_pos + 150, y_pos, 20,  TFT_PINK);
        digitalWrite(enablePin, HIGH); // enable stepper
        temp = temperatura(); // Serial.print("Temperatura = ");Serial.println(temp,2);
        Stepper_move_position(-1);
        digitalWrite(enablePin, LOW); // disable stepper
        tft.fillCircle(x_pos + 150,y_pos, 20,  TFT_GREEN);
        time_count = millis();
        steering = true;
        steering_neutral = false;
        dir = false;
        tft.setTextColor(TFT_BLACK, TFT_BLACK);
        tft.setCursor(x_pos, y_pos, 4);  tft.print("STEERING    ");
        tft.setTextColor(TFT_GREEN, TFT_BLACK);        
        tft.setCursor(x_pos, y_pos, 4);  tft.print("Pilot ON   ");
      }
      if (abs(difference) > dop_odstupanje_kursa and difference > 0 and steering == true){
        if(dir == false and difference > 0){
          tft.setTextColor(TFT_PINK, TFT_BLACK);
          tft.setCursor(x_pos, y_pos, 4);  tft.print("STEERING    ");
          tft.fillCircle(x_pos + 150, y_pos, 20,  TFT_PINK);
          digitalWrite(enablePin, HIGH); // enable stepper
          temp = temperatura(); // Serial.print("Temperatura = ");Serial.println(temp,2);
          Stepper_move_position(1);
          digitalWrite(enablePin, LOW); // disable stepper
          tft.fillCircle(x_pos + 150,y_pos, 20,  TFT_GREEN);
          time_count = millis();
          steering = true;
          steering_neutral = false;
          dir = true;
          tft.setTextColor(TFT_BLACK, TFT_BLACK);
          tft.setCursor(x_pos, y_pos, 4);  tft.print("STEERING    ");
          tft.setTextColor(TFT_GREEN, TFT_BLACK);           
          tft.setCursor(x_pos, y_pos, 4);  tft.print("Pilot ON   ");          
        }
      }
      if (abs(difference) > dop_odstupanje_kursa and difference < 0 and steering == true){
        if(dir == true and difference < 0){
          tft.setTextColor(TFT_PINK, TFT_BLACK);
          tft.setCursor(x_pos, y_pos, 4);  tft.print("STEERING    ");
          tft.fillCircle(x_pos + 150, y_pos, 20,  TFT_PINK);
          digitalWrite(enablePin, HIGH); // enable stepper
          temp = temperatura(); //Serial.print("Temperatura = ");Serial.println(temp,2);
          Stepper_move_position(-1);
          digitalWrite(enablePin, LOW); // disable stepper
          tft.fillCircle(x_pos + 150,y_pos, 20,  TFT_GREEN);
          time_count = millis();
          steering = true;
          steering_neutral = false;
          dir = false;
          tft.setTextColor(TFT_BLACK, TFT_BLACK);
          tft.setCursor(x_pos, y_pos, 4);  tft.print("STEERING    ");
          tft.setTextColor(TFT_GREEN, TFT_BLACK);          
          tft.setCursor(x_pos, y_pos, 4);  tft.print("Pilot ON   ");          
        }
      }
    }
//    }
    tft.setTextColor(TFT_BLACK, TFT_BLACK);
    tft.setCursor(420, y_pos, 4);
    tft.print("-000");
    buf1 = Leading_zero(STEPPER_MOTOR.getCurrentPositionInMillimeters(), 3);
    tft.setTextColor(TFT_PINK, TFT_BLACK);
    tft.setCursor(420, y_pos, 4);
    tft.print(buf1);
  }
  
  /* Neutral position steering */ 
  if (millis() - time_count > delay_to_neutral*1000 and steering == true){
    if (course_COG == 1){
      course_over_ground = gps.course.deg();
      Kompas_labels(int(course_over_ground));  
    }
    else{
      course_over_ground = Calc_heading();
      Kompas_labels(int(course_over_ground));
    }
    difference = course_over_ground - hdg_set_value; 
    if (abs(difference)>180){
      if(difference<0){
        difference+=360;
      }
      else{
        difference-=360;
      }
    }
    if (abs(difference) < dop_odstupanje_kursa){
      if (dir == true){
         tft.setTextColor(TFT_PINK, TFT_BLACK);
         tft.setCursor(x_pos, y_pos, 4);  tft.print("STEERING    ");
         tft.fillCircle(x_pos + 150, y_pos, 20,  TFT_PINK);
         digitalWrite(enablePin, HIGH); // enable stepper
         temp = temperatura(); // Serial.print("Temperatura = ");Serial.println(temp,2);
         Stepper_move_neutral(-1);
         digitalWrite(enablePin, LOW); // disable stepper
         tft.fillCircle(x_pos + 150,y_pos, 20,  TFT_GREEN);
         tft.setTextColor(TFT_BLACK, TFT_BLACK);
         tft.setCursor(x_pos, y_pos, 4);  tft.print("STEERING    ");
         tft.setTextColor(TFT_GREEN, TFT_BLACK);         
         tft.setCursor(x_pos, y_pos, 4);  tft.print("Pilot ON   ");         
      }
      else{
        tft.setTextColor(TFT_PINK, TFT_BLACK);
        tft.setCursor(x_pos, y_pos, 4);  tft.print("STEERING    ");
        tft.fillCircle(x_pos + 150, y_pos, 20,  TFT_PINK);
        digitalWrite(enablePin, HIGH); // enable stepper
        temp = temperatura(); // Serial.print("Temperatura = ");Serial.println(temp,2);
        Stepper_move_neutral(1);
        digitalWrite(enablePin, LOW); // disable stepper 
        tft.fillCircle(x_pos + 150,y_pos, 20,  TFT_GREEN);     
        tft.setTextColor(TFT_BLACK, TFT_BLACK);
        tft.setCursor(x_pos, y_pos, 4);  tft.print("STEERING    ");  
        tft.setTextColor(TFT_GREEN, TFT_BLACK);  
        tft.setCursor(x_pos, y_pos, 4);  tft.print("Pilot ON   ");         
      }
      delay(100);
      tft.setTextColor(TFT_PINK, TFT_BLACK);
      tft.setCursor(x_pos, y_pos, 4);  tft.print("STEERING    ");
      tft.fillCircle(x_pos + 150, y_pos, 20,  TFT_PINK);
      digitalWrite(enablePin, HIGH); // enable stepper
      temp = temperatura(); // Serial.print("Temperatura = ");Serial.println(temp,2);
      STEPPER_MOTOR.moveToPositionInMillimeters(0);
      digitalWrite(enablePin, LOW); // disable stepper
      tft.fillCircle(x_pos + 150,y_pos, 20,  TFT_GREEN);
      steering_neutral = true;
      time_count = millis();
      steering = false;
      tft.setTextColor(TFT_BLACK, TFT_BLACK);
      tft.setCursor(x_pos, y_pos, 4);  tft.print("STEERING    ");
      tft.setTextColor(TFT_GREEN, TFT_BLACK);
      tft.setCursor(x_pos, y_pos, 4);  tft.print("Pilot ON   ");      
    }
    // // // Serial.println("EXIT steering to neutral!");
    tft.setTextColor(TFT_BLACK, TFT_BLACK);
    tft.setCursor(420, y_pos, 4);
    tft.print("-000");
    buf1 = Leading_zero(STEPPER_MOTOR.getCurrentPositionInMillimeters(), 3);
    tft.setTextColor(TFT_PINK, TFT_BLACK);
    tft.setCursor(420, y_pos, 4);
    tft.print(buf1);
  }
}

void Change_heading(){
  // ************ HEADING SETTING BY ROTTARY ENCODER ************ 
  if (digitalRead(PB_10p) == HIGH and digitalRead(PB_1p) == HIGH and digitalRead(PB_1n) == HIGH and digitalRead(PB_10n) == HIGH and digitalRead(SW)== LOW){
    //// // // Serial.println("LOW");
    hdg_set_value = int(rot_encoder(int(hdg_set_value), 0, 360, "Heading SET:"));
    tft.setTextColor(TFT_YELLOW);
    tft.drawString("Heading:        ", 10, 110, 4);
    SET_HDG(hdg_set_value);
    delay(100);
  } 
  // ************ RADIO FREQUENCY (4 Channel 433MHz RF) REMOTE HEADING SETTING ************ 
  if (digitalRead(PB_10p) == HIGH and digitalRead(PB_1p) == LOW and digitalRead(PB_1n) == HIGH and digitalRead(PB_10n) == HIGH and digitalRead(SW)== HIGH){
    // SET HEADING 1 DEGREE CLOCKWISE
    hdg_set_value_promjena(1);
  }
  else if(digitalRead(button1) == HIGH){
    // SET HEADING 1 DEGREE CLOCKWISE
    hdg_set_value_promjena(-10);
  }
  else if(digitalRead(PB_10p) == HIGH and digitalRead(PB_1p) == HIGH and digitalRead(PB_1n) == LOW and digitalRead(PB_10n) == HIGH and digitalRead(SW)== HIGH){
    // SET HEADING 1 DEGREE COUNTERCLOCKWISE
     hdg_set_value_promjena(-1);
  }
  else if(digitalRead(button3) == HIGH){
    // SET HEADING 1 DEGREE COUNTERCLOCKWISE
    hdg_set_value_promjena(-1);
  }
  else if(digitalRead(PB_10p) == LOW and digitalRead(PB_1p) == HIGH and digitalRead(PB_1n) == HIGH and digitalRead(PB_10n) == HIGH and digitalRead(SW)== HIGH){
    // SET HEADING 10 DEGREE CLOCKWISE
     hdg_set_value_promjena(10);
  }
  else if(digitalRead(button2) == HIGH){
    // SET HEADING 10 DEGREE CLOCKWISE
    hdg_set_value_promjena(10);
  }
  else if(digitalRead(PB_10p) == HIGH  and digitalRead(PB_1p) == HIGH and digitalRead(PB_1n) == HIGH and digitalRead(PB_10n) == LOW and  digitalRead(SW)== HIGH){
    // SET HEADING 10 DEGREE COUNTERCLOCKWISE
     hdg_set_value_promjena(-10);
  }
  else if(digitalRead(button4) == HIGH){
    // SET HEADING 1 DEGREE COUNTERCLOCKWISE
    hdg_set_value_promjena(1);
  }
}

//// ************************************************************************************************
//
////                                         navigate To
////                                       calculate Bearing
//
//// ************************************************************************************************
double navigateTo(double lat1, double long1, double lat2, double long2)
{
  // returns course in degrees (North=0, West=270) from position 1 to position 2,
  // both specified as signed decimal-degrees latitude and longitude.
  // Because Earth is no exact sphere, calculated course may be off by a tiny fraction.
  // Courtesy of Maarten Lamers
  double dlon = radians(long2-long1);
  lat1 = radians(lat1);
  lat2 = radians(lat2);
  double a1 = sin(dlon) * cos(lat2);
  double a2 = sin(lat1) * cos(lat2) * cos(dlon);
  a2 = cos(lat1) * sin(lat2) - a2;
  a2 = atan2(a1, a2);
  if (a2 < 0.0)
  {
    a2 += 2*3.1415926;
  }
  return 180*a2/3.1415926;
}
//// ************************************************************************************************
////                                  Stepper_move_position(int dir)
////                                  Stepper_move_neutral(int dir)
////                                       Modules for steering 
//// ************************************************************************************************
void Stepper_move_position(int dir){
  #ifdef NON_BLOCKING
    STEPPER_MOTOR.setupMoveInMillimeters(dir*Max_steering_turning_deg*step_direction_positive);
    while(!STEPPER_MOTOR.motionComplete()){
      STEPPER_MOTOR.processMovement();       // this call moves stepper
      int stepper_pos = STEPPER_MOTOR.getCurrentPositionInMillimeters();
      if (stepper_pos/10 == int(stepper_pos/10){
        Kompas_labels(int(Calc_heading()));
      }
    }
  #else
    STEPPER_MOTOR.moveToPositionInMillimeters(dir*Max_steering_turning_deg*step_direction_positive);
  #endif   
}

void Stepper_move_neutral(int dir){
  #ifdef NON_BLOCKING
    
    STEPPER_MOTOR.setupMoveInMillimeters(dir*steering_offset*step_direction_positive);
    while(!STEPPER_MOTOR.motionComplete()){
      STEPPER_MOTOR.processMovement();       // this call moves stepper
      int stepper_pos = STEPPER_MOTOR.getCurrentPositionInMillimeters();
      if (stepper_pos/10 == int(stepper_pos/10){
        Kompas_labels(int(Calc_heading()));
      }
    }
  #else
    STEPPER_MOTOR.moveToPositionInMillimeters(dir*steering_offset*step_direction_positive);
  #endif      
}

//// ************************************************************************************************
////                                         temperatura()
////                                    measuring temperature
//// ************************************************************************************************
float temperatura() {
  #ifdef THERMISTOR
    int critical_temp = 60;
    Vo = analogRead(thermistorPin);
    R2 = R1 * (1023.0 / (float)Vo - 1.0); // Resistance of the Thermistor
    tCelsius = (Beta * roomTemp) / (Beta + (roomTemp * log(R2 / Ro)))- 273.15;
    if( tCelsius > critical_temp){
      digitalWrite(enablePin, LOW); // disable stepper 
      tft.fillScreen(TFT_BLACK);
      tft.setTextColor(TFT_RED);
      tft.setCursor(50, 100, 6);  tft.print("WARNING overheating !!!");
    }
    return tCelsius;
  #endif
}

#ifdef TIME_ZONE
  //// ************************************************************************************************
  //
  ////                                  SETTING MICROCONTROLLER TIME
  //// ************************************************************************************************
  void setthetime(void)
  {
    int Year = gps.date.year();
    byte Month = gps.date.month();
    byte Day = gps.date.day();
    byte Hour = gps.time.hour();
    byte Minute = gps.time.minute();
    byte Second = gps.time.second();
    // Set Time from GPS data string
    setTime(Hour, Minute, Second, Day, Month, Year);  // set the time of the microcontroller to the UTC time from the GPS
  }
#endif
