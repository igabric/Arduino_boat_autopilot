void Screen_1_navigation(){
  int active_btn = 0;
  bool state = false;
  tft.fillScreen(TFT_BLACK);
  tft.drawRect(5, 5, 230, 150, TFT_YELLOW);
  tft.drawRect(245, 5, 230, 150, TFT_YELLOW);
  tft.drawRect(5, 165, 230, 150, TFT_YELLOW);
  tft.drawRect(245, 165, 230, 150, TFT_YELLOW);

  
  Set_Screen_1("Button 1", "Anchoring", 5, 5, false);
  Set_Screen_1("Button 2",  "Enter custom POI", 245, 5, false);
  Set_Screen_1("Button 3",  "Navigate by selected POI", 5, 165, false);
  Set_Screen_1("Button 4",  "Navigate by heading", 245, 165, false);
  TFT_print_entered_values();
  delay(1000);
  int prolaz_vrij = 0;
  while (true){
    prolaz_vrij += 1;
    if(prolaz_vrij == 2){
      temp = temperatura(); 
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      tft.setCursor(410, 20, 4);
      tft.print(temp, 0);
      tft.setCursor(445, 20, 4);
      tft.print("C");
      prolaz_vrij = 0;
    }
    
    if(digitalRead(SW)== LOW){
      Manual_navigate();
    }
    if(digitalRead(PB_10p) == LOW and digitalRead(PB_1p) == LOW and digitalRead(PB_1n) == HIGH and digitalRead(PB_10n) == HIGH and digitalRead(SW)== HIGH){
      break;
    }
    // if(digitalRead(PB_10n) == LOW and digitalRead(PB_1p) == HIGH and digitalRead(PB_1n) == HIGH and digitalRead(PB_10n) == HIGH and digitalRead(SW)== HIGH){
    if(digitalRead(PB_10n) == LOW){  
      Serial.println("Anchoring");
      if(active_btn == 1){
        state = 0; active_btn == 0;
        Set_Screen_1("Button 1", "Anchoring", 5, 5, false);
      }
      else if(active_btn == 2){
        Set_Screen_1("Button 2",  "Enter custom POI", 245, 5, false);
        Set_Screen_1("Button 1", "Anchoring", 5, 5, true);
        active_btn = 1; state = 1;
      }
      else if(active_btn == 3){
        Set_Screen_1("Button 3",  "Navigate by selected POI", 5, 165, false);
        Set_Screen_1("Button 1", "Anchoring", 5, 5, true);
        active_btn = 1; state = 1;
      }
      else if(active_btn == 4){
        Set_Screen_1("Button 4",  "Navigate by heading", 245, 165, false);
        Set_Screen_1("Button 1", "Anchoring", 5, 5, true);
        active_btn = 1; state = 1;
      }
      else{
        Set_Screen_1("Button 1", "Anchoring", 5, 5, true);
        active_btn = 1; state = 1;
      }
      delay(500);
    }
  if (digitalRead(PB_10n) == HIGH and digitalRead(PB_1n) == HIGH and digitalRead(PB_1p) == HIGH and digitalRead(PB_10p) == LOW and digitalRead(SW)== HIGH){
      Serial.println("Set POI");
      if(active_btn == 1){
        Set_Screen_1("Button 1", "Anchoring", 5, 5, false);
        Set_Screen_1("Button 2",  "Enter custom POI", 245, 5, true);
        active_btn = 2; state = 1;   
      }
      else if(active_btn == 2){
        state = 0; active_btn == 0;
        Set_Screen_1("Button 2",  "Enter custom POI", 245, 5, false);
      }
      else if(active_btn == 3){
        Set_Screen_1("Button 3",  "Navigate by selected POI", 5, 165, false);
        Set_Screen_1("Button 2",  "Enter custom POI", 245, 5, true);
        active_btn = 2; state = 1;
      }
      else if(active_btn == 4){
        Set_Screen_1("Button 4",  "Navigate by heading", 245, 165, false);
        Set_Screen_1("Button 2",  "Enter custom POI", 245, 5, true);
        active_btn = 2; state = 1;
      }
      else{
        Set_Screen_1("Button 2",  "Enter custom POI", 245, 5, true);
        active_btn = 2; state = 1;
      }
      delay(500);
    }
    if (digitalRead(PB_10n) == HIGH and digitalRead(PB_1n) == LOW and digitalRead(PB_1p) == HIGH and digitalRead(PB_10p) == HIGH and digitalRead(SW)== HIGH){
      Serial.println("Navigate by POI");
      if(active_btn == 1){
        Set_Screen_1("Button 1", "Anchoring", 5, 5, false);
        Set_Screen_1("Button 3",  "Navigate by selected POI", 5, 165, true);
        active_btn = 3; state = 1;   
      }
      else if(active_btn == 2){
        Set_Screen_1("Button 2",  "Enter custom POI", 245, 5, false);
        Set_Screen_1("Button 3",  "Navigate by selected POI", 5, 165, true);
        active_btn = 3; state = 1;
      }
      else if(active_btn == 3){
        state = 0; active_btn == 0;
        Set_Screen_1("Button 3",  "Navigate by selected POI", 5, 165, false);
      }
      else if(active_btn == 4){
        Set_Screen_1("Button 4",  "Navigate by heading", 245, 165, false);
        Set_Screen_1("Button 3",  "Navigate by selected POI", 5, 165, true);
        active_btn = 3; state = 1;
      }
      else{
        Set_Screen_1("Button 3",  "Navigate by selected POI", 5, 165, true);
        active_btn = 3; state = 1;
      }
      delay(500);
    }
    if (digitalRead(PB_10n) == HIGH and digitalRead(PB_1n) == HIGH and digitalRead(PB_1p) == LOW and digitalRead(PB_10p) == HIGH and digitalRead(SW)== HIGH){
      Serial.println("Navigate by heading");
      if(active_btn == 1){
        Set_Screen_1("Button 1", "Anchoring", 5, 5, false);
        Set_Screen_1("Button 4",  "Navigate by heading", 245, 165, true);
        active_btn = 4; state = 1;   
      }
      else if(active_btn == 2){
        Set_Screen_1("Button 2",  "Enter custom POI", 245, 5, false);
        Set_Screen_1("Button 4",  "Navigate by heading", 245, 165, true);
        active_btn = 4; state = 1;
      }
      else if(active_btn == 3){
        Set_Screen_1("Button 3",  "Navigate by selected POI", 5, 165, false);
        Set_Screen_1("Button 4",  "Navigate by heading", 245, 165, true);
        active_btn = 4; state = 1;
      }
      else if(active_btn == 4){
        state = 0; active_btn == 0;
        Set_Screen_1("Button 4",  "Navigate by heading", 245, 165, false);
      }
      else{
        Set_Screen_1("Button 4",  "Navigate by heading", 245, 165, true);
        active_btn = 4; state = 1;
      }
      delay(500);
    }
    
    if (state == 1){
      // IZBOR POI IZMEĐU PONUĐENIH U INTERNOJ BAZI PODATAKA
      if(active_btn == 1){ 
        Anchor_alarm();
        state = 0;
        Screen_1_navigation();
      }
      // UPIS PRILAGOĐENIH ("CUSTOM") GEOGRAFSKIH KOORDINATA
      else if(active_btn == 2){
//        // Enter custom POI coordinates
//        String POI_name = rot_encoder_POI_NAME();
//        pointArray[number_of_POI] = POI_name;
        number_of_POI = 26;
        pointArray[25] = "CUSTOM_POI";
        //Label(pointArray[arrLen], 200, 270, 4,"green");
        tft.setTextColor(TFT_YELLOW, TFT_BLACK);
        tft.setCursor(200, 270, 4);
        tft.print(pointArray[25]);
        rot_encoder_SET_CUSTOM_POI();
        longArray[25] = custom_POI_long;
        latArray[25] = custom_POI_lat;
        
//        Serial.print(latArray[number_of_POI],4); Serial.print("  ");
//        Serial.print(longArray[number_of_POI],4); Serial.print("  ");
//        Serial.println(pointArray[number_of_POI]);
        // pointArray[arrLen] = "CUSTOM  POI";
        
//        if (sign_custom_POI == false){ // Ukoliko je ranije definiran CUSTOM POI veličina polja se ne povećava
//          number_of_POI += 1;
//        } 
         
        sign_custom_POI = true;
        state = 0;
//        tft.fillScreen(TFT_BLACK);
//        tft.setTextColor(TFT_YELLOW, TFT_BLACK);
//        tft.setCursor(40, 40, 4);
//        // ADDING CUSTOM POI TO SD CARD FILE "tocke.csv"
//        tft.println("Save custom POI? Yes: Y/G ; No: R/B");
//        
//        while (true){
//          if (digitalRead(PB_1p) == LOW or digitalRead(PB_10p) == LOW){
//            // Serial.print("custom.txt removed ?  ");
////            SD.remove("tocke.csv");
////            Serial.print("pois.txt exist?:  ");
////            Serial.println(SD.exists("tocke.csv"));
//            add_poi_list();
//            myFile = SD.open("tocke.csv", FILE_WRITE);
//            
//            if (SD.exists("tocke.csv")) {
//              Serial.println("tocke.csv EXIST");
//              if(myfile){
//                Serial.println("myfile EXIST");
//                String tocka = String(custom_POI_lat) + "," + String(custom_POI_long)+"," + "CUSTOM_POI";
//                Serial.println(tocka);
//                myFile.println(tocka);
////                int lat_deg_int = int(custom_POI_lat);
////                int lat_deg_dec12 = int((custom_POI_lat - lat_deg_int)*100);
////                int lat_deg_dec34 = int(((custom_POI_lat - lat_deg_int)*100 - lat_deg_dec12)*100);
////                myFile.println(lat_deg_int);
////                myFile.println(lat_deg_dec12);
////                myFile.println(lat_deg_dec34);
////                Serial.println(lat_deg_int);
////                Serial.println(lat_deg_dec12);
////                Serial.println(lat_deg_dec34);              
////                int long_deg_int = int(custom_POI_long);
////                int long_deg_dec12 = int((custom_POI_long - long_deg_int)*100);
////                int long_deg_dec34 = int(((custom_POI_long - long_deg_int)*100 - long_deg_dec12)*100);
////                myFile.println(long_deg_int);
////                myFile.println(long_deg_dec12);
////                myFile.println(long_deg_dec34); 
////                Serial.println(long_deg_int);
////                Serial.println(long_deg_dec12);
////                Serial.println(long_deg_dec34); 
//                myFile.close();
//                parse_poi_list();
//              }
//            } 
//            break;         
//          }
//          else if (digitalRead(PB_1n) == LOW or digitalRead(PB_10n) == LOW){
//            break;
//          }
//        } 
            


        
        delay(1000);
        Screen_1_navigation();
      }
      // AUTOMATIC NAVIGATION by POINT OF INTEREST (POI)
      else if(active_btn == 3){
        // Navigate by selected POI 
        if (POI_selection != NULL){
          select_POI();
          state = 0;
          Autopilot_heading_POI(false);
          autopilot_ON = true;
          Navigate_by_POI();     
          delay(1000);
          Screen_1_navigation();
        }
        else{

          select_POI();         
          state = 0;
          autopilot_ON = true;
          Autopilot_heading_POI(false);
          Navigate_by_POI();     
          delay(1000);
          Screen_1_navigation();
        }
      }
      // AUTOMATIC NAVIGATION BY SELECTED HEADING
      else if(active_btn == 4){
        // Navigate by heading
        Autopilot_heading_POI(true);
        autopilot_ON = true;
        Autopilot(true);
        state = 0;
        Screen_1_navigation();
      }
    }
    delay(500);
  } 
  tft.fillScreen(TFT_BLACK);
}  

// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                         Set_Screen_1 MODULE
//                                  SET ACTIVE BUTTON COLOUR ON SCREEN 1

// ************************************************************************************************
void Set_Screen_1(String text_btn, String description, int posx, int posy, bool active){
  if (active == true){
    tft.drawRect(posx, posy, 230, 150, TFT_WHITE);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
  }
  else{
    tft.drawRect(posx, posy, 230, 150, TFT_YELLOW);
    tft.setTextColor(TFT_RED, TFT_BLACK);
  }
  if (text_btn == "Button 1"){
    tft.fillCircle(posx + 115, posy + 40, 15, TFT_WHITE);
    tft.fillCircle(posx + 115, posy + 40, 12, TFT_RED);
  }
  else if (text_btn == "Button 2"){
    tft.fillCircle(posx + 115, posy + 40, 15, TFT_WHITE);
    tft.fillCircle(posx + 115, posy + 40, 12, TFT_YELLOW);
  }
  else if (text_btn == "Button 3"){
    tft.fillCircle(posx + 115, posy + 40, 15, TFT_WHITE);
    tft.fillCircle(posx + 115, posy + 40, 12, TFT_BLACK);
  }
  else if (text_btn == "Button 4"){
    tft.fillCircle(posx + 115, posy + 40, 15, TFT_WHITE);
    tft.fillCircle(posx + 115, posy + 40, 12, TFT_GREEN);
  }
  // tft.setCursor(posx + 30, posy + 50, 4);
  // tft.print(text_btn);
  tft.setCursor(posx + 30, posy + 80, 2);
  tft.print(description);
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                    TFT_print_entered_values MODULE
//                               SHOW ON THE SCREEN 1 SELECTED/ENTERED VALUE 

// ************************************************************************************************
void TFT_print_entered_values(){
  if(custom_POI_long != NULL){
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setCursor(245 + 30, 5 + 100, 2);
    tft.print("Long:");
    tft.setCursor(245 + 30, 5 + 115, 2);
    tft.print("Lat:");
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(245 + 80, 5 + 100, 2);
    tft.print(custom_POI_long, 6); 
    tft.setCursor(245 + 80, 5 + 115, 2);
    tft.print(custom_POI_lat, 6);
  }
}
// ------------------------------------------------------------------------------------------------

void Manual_navigate(){
  String buf1 = "000";
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setCursor(140, 40, 4);
  tft.println("MANUAL STEERING");
  tft.setCursor(20, 270, 4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.println("Steering position:");
  drawRAW("kormilo_.raw", 215, 135, 50, 50);
  delay(1000);
  while (digitalRead(SW)== HIGH){
    tft.fillRect(270, 270, 50, 30, TFT_BLACK);
    buf1 = Leading_zero(STEPPER_MOTOR.getCurrentPositionInMillimeters(), 3);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setCursor(270, 270, 4);
    tft.print(buf1);
    if (digitalRead(PB_10p) == LOW and digitalRead(PB_1p) == HIGH and digitalRead(PB_1n) == HIGH and digitalRead(PB_10n) == HIGH and digitalRead(SW)== HIGH){
      // SET STEPPER CLOCKWISE
      sterring_positive();
    }
    else if(digitalRead(button1) == HIGH){
      // SET STEPPER COUNTERCLOCKWISE
      sterring_negative();
    }
//    else if(digitalRead(button3) == HIGH){
//      // SET STEPPER NEUTRAL
//      // tft.fillCircle(240, 240, 10, TFT_GREEN);
//      tft.fillRect(220, 220, 40, 40, TFT_GREEN);
//      digitalWrite(enablePin, HIGH); // enable stepper
//      temp = temperatura(); //Serial.print("Temperatura = ");Serial.println(temp,2);
//      STEPPER_MOTOR.moveToPositionInMillimeters(0);
//      digitalWrite(enablePin, LOW); // disable stepper
//      delay(500);
//    }
    else if(digitalRead(button2) == HIGH){
      // SET STEPPER CLOCKWISE
      sterring_positive();
    }
    else if(digitalRead(PB_10p) == HIGH  and digitalRead(PB_1p) == HIGH and digitalRead(PB_1n) == HIGH and digitalRead(PB_10n) == LOW and  digitalRead(SW)== HIGH){
      // SET STEPPER COUNTERCLOCKWISE
      sterring_negative();
    }
    else if(digitalRead(PB_1p) == LOW or digitalRead(PB_1n) == LOW or digitalRead(button3) == HIGH or digitalRead(button4) == HIGH){
      // tft.fillCircle(230, 160, 10, TFT_PINK);
      tft.fillRect(220, 220, 40, 40, TFT_GREEN);
      // SET STEPPER NEUTRAL
      digitalWrite(enablePin, HIGH); // enable stepper
      temp = temperatura(); //Serial.print("Temperatura = ");Serial.println(temp,2);
      STEPPER_MOTOR.moveToPositionInMillimeters(0);
      digitalWrite(enablePin, LOW); // disable stepper
      delay(500);
    }
    // tft.fillCircle(460, 160, 10, TFT_BLACK);
    // tft.fillCircle(20, 160, 10, TFT_BLACK);
    tft.fillTriangle(60, 160, 90, 140, 90, 180, TFT_BLACK);
    tft.fillTriangle(410, 160, 380, 140, 380, 180, TFT_BLACK);
    tft.fillRect(220, 220, 40, 40, TFT_BLACK);
    tft.setTextColor(TFT_BLACK, TFT_BLACK);
    tft.setCursor(135, 80, 4);
    tft.println("STEERING LIMIT !!!");
  }
  Screen_1_navigation();
}

void sterring_positive(){
  tft.fillTriangle(410, 160, 380, 140, 380, 180, TFT_GREEN);
  if(step_direction_positive == 1){
    if(STEPPER_MOTOR.getCurrentPositionInMillimeters()<100){
      // tft.fillCircle(460, 160, 10, TFT_RED);
      digitalWrite(enablePin, HIGH); // enable stepper
      temp = temperatura(); // Serial.print("Temperatura = ");Serial.println(temp,2);
      STEPPER_MOTOR.moveRelativeInMillimeters(5);
      digitalWrite(enablePin, LOW); // disable stepper
    }
    else{
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.setCursor(135, 80, 4);
      tft.println("STEERING LIMIT !!!");
      delay(500);
    }
  }
  else{
    if(STEPPER_MOTOR.getCurrentPositionInMillimeters()> -100){
      // tft.fillCircle(20, 160, 10, TFT_GREEN);
      // tft.fillTriangle(60, 160, 90, 140, 90, 180, TFT_GREEN);
      digitalWrite(enablePin, HIGH); // enable stepper
      temp = temperatura(); //Serial.print("Temperatura = ");Serial.println(temp,2);
      STEPPER_MOTOR.moveRelativeInMillimeters(-5);
      digitalWrite(enablePin, LOW); // disable stepper
    }
    else{
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.setCursor(135, 80, 4);
      tft.println("STEERING LIMIT !!!");
      delay(500);
    }
  }
}

void sterring_negative(){
  tft.fillTriangle(60, 160, 90, 140, 90, 180, TFT_GREEN);
  if(step_direction_positive == 1){
    if(STEPPER_MOTOR.getCurrentPositionInMillimeters()> -100){
      // tft.fillCircle(20, 160, 10, TFT_GREEN);
      digitalWrite(enablePin, HIGH); // enable stepper
      temp = temperatura(); //Serial.print("Temperatura = ");Serial.println(temp,2);
      STEPPER_MOTOR.moveRelativeInMillimeters(-5);
      digitalWrite(enablePin, LOW); // disable stepper
    }    
    else{
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.setCursor(135, 80, 4);
      tft.println("STEERING LIMIT !!!");
      delay(500);
    }
  }
  else{
    if(STEPPER_MOTOR.getCurrentPositionInMillimeters()<100){
      // tft.fillCircle(460, 160, 10, TFT_RED);
      // tft.fillTriangle(410, 160, 380, 140, 380, 180, TFT_GREEN);
      digitalWrite(enablePin, HIGH); // enable stepper
      temp = temperatura(); // Serial.print("Temperatura = ");Serial.println(temp,2);
      STEPPER_MOTOR.moveRelativeInMillimeters(5);
      digitalWrite(enablePin, LOW); // disable stepper
    }
    else{
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.setCursor(135, 80, 4);
      tft.println("STEERING LIMIT !!!");
      delay(500);
    }
  }  
}
