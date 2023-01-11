// ************************************************************************************************

//                                         ANCHOR ALARM MODULE
//                                     ACTIVATE BUZZER ON EMERGENCY

// ************************************************************************************************
void Anchor_alarm(){
//  float gps_lat_anc = 0;
//  float gps_long_anc = 0;
  String text;
  float distanca;
  int tolerance = 15; // Dopuštena udaljenost od točke sidrenja
  float acc;
  float x_dist;
  float y_dist;
  tft.fillScreen(TFT_BLACK);
  Label("Waiting for GPS!", 20, 100, 4, "red");
//  bool newData = false;
//  while (newData == false){
//    if (Serial1.available() > 0)
//      if (gps.encode(Serial1.read()))
//        if (gps.location.isValid()){  
//          newData = true;  
//        }
//    delay(200);
//  }

  for (int i = 0; i <= 5; i++) {
    gps_lat_anc == 0;
    while(gps_lat_anc == 0){
      if (Serial1.available()>0)
        if (gps.encode(Serial1.read())>0)
          if (gps.location.isUpdated()){
            if (gps.location.isValid()){  
              Serial.print("***");
              gps_lat_anc = gps.location.lat();
              gps_long_anc = gps.location.lng();
            } 
          }     
    if (digitalRead(PB_1p) == LOW and digitalRead(PB_10p) == LOW){
      break;
    }
    }
  }
  tft.fillScreen(TFT_BLACK);
  tft.drawCircle(90, 230, 80, TFT_YELLOW);
  tft.fillCircle(90, 230, 5, TFT_YELLOW);
  drawRAW("sidrenje.raw", 220, 160, 50, 50);
  Label("ANCHORING", 100, 30, 4, "red"); 
  Label("Anchoring tolerance:", 20, 100, 4, "green");
  Label("meters", 310, 100, 4, "green");
  tolerance = int(rot_encoder_SET_CUSTOM_COORDINATE(270, 100, 50, 4));
  delay(1000);
  if (gps.location.isValid()){
    gps_long_anc = gps.location.lng();
    gps_lat_anc = gps.location.lat();
  }
  // Serial.print(gps_long_anc,16);Serial.print("   ");Serial.print(gps_lat_anc,16);Serial.println("  anchoring location");
  
  // tolerance = int(rot_encoder(tolerance, 0, 50, "Anchoring tolerance, m:"));
  
//  tft.fillScreen(TFT_BLACK);
//  Label("ANCHORING", 100, 30, 4, "red");
//  Label("Udaljenost", 20, 105, 4, "green");
//  Label("m", 200, 105, 4, "green");
  tft.fillRect(0, 0, 480, 2, TFT_WHITE);
  tft.fillRect(0, 12, 480, 2, TFT_WHITE);
  tft.fillRect(0, 2, 200, 10, TFT_RED);
  tft.fillRect(280, 2, 200, 10, TFT_GREEN);
  tft.fillRect(0, 16, 480, 30, TFT_WHITE);

  
  tft.drawCircle(240, 160, 12, TFT_WHITE);
  tft.drawCircle(240, 200, 12, TFT_WHITE);
  tft.fillCircle(240, 160, 10, TFT_YELLOW);
  tft.fillCircle(240, 200, 10, TFT_GREEN);    
  int prolaz_vrij = 0;  
  while (digitalRead(PB_1p) == HIGH or digitalRead(PB_10p) == HIGH){ // Anchoring uključen dok se istodobno ne pritisnu tasteri PB_1p i PB_10p
    // Change anchoring tolerances in meters
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
    if (digitalRead(PB_10p) == HIGH and digitalRead(PB_1p) == HIGH and digitalRead(PB_1n) == HIGH and digitalRead(PB_10n) == HIGH and digitalRead(SW)== LOW){
      tolerance = int(rot_encoder_SET_CUSTOM_COORDINATE(270, 100, 50, 4));
      tft.fillCircle(90+int(80*x_dist/tolerance), 230+int(80*y_dist/tolerance), 6, TFT_BLACK);
    }
    if (Serial1.available()>0)
      if (gps.encode(Serial1.read()))
        if (gps.location.isValid()){  
          Serial.print("");
        } 
         
    if (gps.location.isValid()){
      gps_long = gps.location.lng();
      gps_lat = gps.location.lat();
      // Serial.println("GPS valid");
    }
//    if (gps.location.isUpdated()){
//      Serial.println("Updated !");
//    } 
    // Serial.print(gps_long,16);Serial.print("   ");Serial.println(gps_lat,16);
    distanca = Udaljenost_m(gps_long_anc, gps_lat_anc, gps_long, gps_lat);
    hdg_set_value = navigateTo(gps_lat_anc, gps_long_anc, gps_lat, gps_long); hdg_set_value = radians(hdg_set_value);
    tft.fillCircle(90+int(80*x_dist/tolerance), 230+int(80*y_dist/tolerance), 6, TFT_BLACK);
    x_dist = distanca * sin(hdg_set_value); y_dist = distanca * cos(hdg_set_value);
    
    
    
    tft.fillCircle(90+int(80*x_dist/tolerance), 230+int(80*y_dist/tolerance), 6, TFT_RED);
    tft.fillCircle(90, 230, 3, TFT_YELLOW);
    // Serial.print(distanca);Serial.print("   ");Serial.println(tolerance);
    if (distanca > tolerance){
        // ANCHORING ALARM ON
        tone(buzzer, 1000);
        tft.drawCircle(90, 230, 80, TFT_RED);
         
    }
    else if (distanca < tolerance){ 
      noTone(buzzer);
      tft.drawCircle(90, 230, 80, TFT_YELLOW);

    }
    Heading_reading = Calc_heading();
    Kompas_labels(Heading_reading);
    Lat_Long(gps_lat, gps_long);
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
    // Print Date on TFT display
    if (gps.date.isValid()){
      Date_TFT(gps.date.day(), gps.date.month(), gps.date.year());
    }
    if (gps.satellites.isValid()){
      //Satelites_TFT(gps.satellites.value());
      Satelites_TFT(gps.satellites.value());
    }
    if (gps.hdop.isValid()){
      // acc = float(int(gps.hdop.value()/10))/100;
      acc = 2.1 * CEP * float(gps.hdop.value())/100;
      hdop_TFT(acc);
    }
    smartDelay(100);    
    tft.fillCircle(90+int(80*x_dist/tolerance), 230+int(80*y_dist/tolerance), 6, TFT_BLACK);
    if (distanca > tolerance){
        tft.drawCircle(90, 230, 80, TFT_RED);
    }
    else { 
      tft.drawCircle(90, 230, 80, TFT_YELLOW);
    }
  }
  noTone(buzzer); 
  
  drawRAW("kormilo_.raw", 280, 160, 50, 50);
  delay(1000);
  // tft.fillCircle(90+int(80*x_dist/tolerance), 230+int(80*y_dist/tolerance), 6, TFT_BLACK);
  // tft.fillCircle(90, 230, 3, TFT_YELLOW);
}
