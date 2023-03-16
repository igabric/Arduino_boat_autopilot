// ************************************************************************************************

//                                      ROTARY ENCODER MODULE
//                               SETTING VALUE USING ROTARY ENCODER

// ************************************************************************************************
float rot_encoder(float set_value, int dec_plc, int max_val, String text) {
  unsigned long lastButtonPress = millis();
  float izlazna_velicina;
  int counter = 0;
  izlazna_velicina = set_value;
  char buf1[8];
  int currentStateCLK;
  Label(text,10,110,4,"green"); 
  SET_HDG(float(izlazna_velicina));
  while( true ) {
    currentStateCLK = digitalRead(CLK);  // Read the current state of CLK
    if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
      if (digitalRead(DT) != currentStateCLK) {
        counter ++;
        int heading = int(izlazna_velicina + counter/pow(10,dec_plc));
        if (heading > max_val- 1){
          counter -= max_val;
        }
        SET_HDG(float(izlazna_velicina + counter/pow(10,dec_plc)));
      } else {
        counter --;
        int heading = int(izlazna_velicina + counter/pow(10,dec_plc));
        if (heading < 0){
          counter += max_val;
        }
        SET_HDG(float(izlazna_velicina + counter/pow(10,dec_plc)));
      }
    }
    lastStateCLK = currentStateCLK;
  
    int btnState = digitalRead(SW);
    if (btnState == LOW) {
      if (millis() - lastButtonPress > 50) {
        izlazna_velicina += counter/pow(10,dec_plc);
        break;
      }
      lastButtonPress = millis();
    }
  }
  Label(text,10,110,4,"black"); 
  delay(1);
  return izlazna_velicina;
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                      SETTING ACTIVE POI MODULE
//                               SETTING ACTIVE POI USING ROTARY ENCODER

// ************************************************************************************************
int rot_encoder_POI() {
  unsigned long lastButtonPress = millis();
  int count = 0;
  int currentStateCLK;
  int x1 = 220;  int x2 = 300;  int y1 = 220;
  Label("POI:",220, 160, 4,"black"); Label("POI SETTING:",220, 160, 4,"green"); 
  while( true ) {
    currentStateCLK = digitalRead(CLK);  // Read the current state of CLK
    if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
      if (digitalRead(DT) != currentStateCLK) {
        count --;
        
        if (count < 0){
          Label(pointArray[0],220, 190, 4,"black");
          Label(String(latArray[0],6),x1, y1, 2,"black");
          Label(String(longArray[0],6),x2, y1, 2,"black");
          count += number_of_POI;
        }
        Label(pointArray[count+1],220, 190, 4,"black"); Label(pointArray[count],220, 190, 4,"white");
        Label(String(latArray[count+1],6),x1, y1, 2,"black"); Label(String(latArray[count],6),x1, y1, 2,"white");
        Label(String(longArray[count+1],6),x2, y1, 2,"black"); Label(String(longArray[count],6),x2, y1, 2,"white");
      } else {
        count ++;
        if (count > number_of_POI - 1){
          Label(pointArray[number_of_POI - 1],220, 190, 4,"black");
          Label(String(latArray[number_of_POI - 1],6),x1, y1, 2,"black");
          Label(String(longArray[number_of_POI - 1],6),x2, y1, 2,"black");
          count -= number_of_POI;
        }
        Label(pointArray[count-1],220, 190, 4,"black"); Label(pointArray[count],220, 190, 4,"white"); 
        Label(String(latArray[count-1],6),x1, y1, 2,"black"); Label(String(latArray[count],6),x1, y1, 2,"white");
        Label(String(longArray[count-1],6),x2, y1, 2,"black"); Label(String(longArray[count],6),x2, y1, 2,"white");
      }
    }
    lastStateCLK = currentStateCLK;
    int btnState = digitalRead(SW);
    if (btnState == LOW) {
      if (millis() - lastButtonPress > 50) {
        break;
      }
      lastButtonPress = millis();
    }
  }
  Label("POI SETTING:",220, 160, 4,"black"); Label("POI:",220, 160, 4,"cyan"); 
  return count;
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                      POI SELECT MODULE
//                               SELECT ACTIVE POI USING ROTARY ENCODER

// ************************************************************************************************
int select_POI() {
  tft.fillScreen(TFT_BLACK);
  unsigned long lastButtonPress = millis();
  int count = 0;
  int currentStateCLK;
  Label("POI SELECT (use rotary encoder):",10, 100, 4,"green"); 
  while( true ) {
    currentStateCLK = digitalRead(CLK);  // Read the current state of CLK
    if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
      if (digitalRead(DT) != currentStateCLK) {
        count --;
        
        if (count < 0){
          Label(pointArray[0],100, 200, 4,"black");
          Label(String(latArray[0],6),100, 250, 4,"black");
          Label(String(longArray[0],6),250, 250, 4,"black");
          count += number_of_POI;
        }
        Label(pointArray[count+1],100, 200, 4,"black"); Label(pointArray[count],100, 200, 4,"white");
        Label(String(latArray[count+1],6),100, 250, 4,"black");Label(String(latArray[count],6),100, 250, 4,"white");
        Label(String(longArray[count+1],6),250, 250, 4,"black");Label(String(longArray[count],6),250, 250, 4,"white");
      } else {
        count ++;
        if (count > number_of_POI - 1){
          Label(pointArray[number_of_POI - 1],100, 200, 4,"black");
          Label(String(latArray[number_of_POI - 1],6),100, 250, 4,"black");
          Label(String(longArray[number_of_POI - 1],6),250, 250, 4,"black");
          count -= number_of_POI;
        }
        Label(pointArray[count-1],100, 200, 4,"black"); Label(pointArray[count],100, 200, 4,"white"); 
        Label(String(latArray[count-1],6),100, 250, 4,"black");Label(String(latArray[count],6),100, 250, 4,"white");
        Label(String(longArray[count-1],6),250, 250, 4,"black");Label(String(longArray[count],6),250, 250, 4,"white");
      }
    }
    lastStateCLK = currentStateCLK;
    int btnState = digitalRead(SW);
    if (btnState == LOW) {
      if (millis() - lastButtonPress > 50) {
        break;
      }
      lastButtonPress = millis();
    }
  }
  POI_selection = count;
  Label("OK",350, 200, 4,"yellow");
  delay(1000);
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                         SET CUSTOM POI MODULE
//                               SETTING CUSTOM POI LONGITUDE AND LATITUDE

// ************************************************************************************************
void rot_encoder_SET_CUSTOM_POI() {
  tft.fillScreen(TFT_BLACK);
  int text_size = 4;
  Label("Use rotary encoder for input!", 10, 10, text_size,"red");
  Label("Longitude (decimal degree):", 100, 50, text_size,"cyan");
  Label(Leading_zero(16, 2), 170, 100, text_size,"yellow");
  int custom_deg = rot_encoder_SET_CUSTOM_COORDINATE(170, 100, 89, text_size, 0, 2, 16);
  Label(".", 205, 100, text_size,"white");

  Label(Leading_zero(50, 2), 210, 100, text_size,"yellow");
  int custom_dec12 = rot_encoder_SET_CUSTOM_COORDINATE(210, 100, 99, text_size, 0, 2, 50);
  Label(Leading_zero(50, 2), 240, 100, text_size,"yellow");
  int custom_dec34 = rot_encoder_SET_CUSTOM_COORDINATE(240, 100, 99, text_size, 0, 2, 50);
  Label(Leading_zero(50, 2), 270, 100, text_size,"yellow");
  int custom_dec56 = rot_encoder_SET_CUSTOM_COORDINATE(270, 100, 99, text_size, 0, 2, 50);    
  custom_POI_long = float(custom_deg) + float(custom_dec12)/100 + float(custom_dec34)/10000 + float(custom_dec34)/1000000;
  
  Label("Latitude (decimal degree):", 100, 180, text_size,"cyan");
  Label(Leading_zero(43, 2), 170, 230, text_size,"yellow");
  custom_deg = rot_encoder_SET_CUSTOM_COORDINATE(170, 230, 89, text_size, 0, 2, 43);
  Label(".", 205, 230, text_size,"white");
  Label(Leading_zero(50, 2), 210, 230, text_size,"yellow");
  custom_dec12 = rot_encoder_SET_CUSTOM_COORDINATE(210, 230, 99, text_size, 0, 2, 50);
  Label(Leading_zero(50, 2), 240, 230, text_size,"yellow");
  custom_dec34 = rot_encoder_SET_CUSTOM_COORDINATE(240, 230, 99, text_size, 0, 2, 50); 
  Label(Leading_zero(50, 2), 270, 230, text_size,"yellow");
  custom_dec56 = rot_encoder_SET_CUSTOM_COORDINATE(270, 230, 99, text_size, 0, 2, 50);   
  custom_POI_lat = float(custom_deg) + float(custom_dec12)/100 + float(custom_dec34)/10000 + float(custom_dec56)/1000000;
  delay(1000);
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                               SET VALUES USING ROTARY ENCODER MODULE 1
//                             SET CUSTOM POI VALUES USING ROTARY ENCODER 

// ************************************************************************************************
float rot_encoder_SET_CUSTOM_COORDINATE(int x_pos, int y_pos, int max_val, int text_size, int min_val = 0, int leading = 2, int custom_value = 0) {
  unsigned long lastButtonPress = millis();
  int count = custom_value; int currentStateCLK;
  while( true ) {
    currentStateCLK = digitalRead(CLK);  // Read the current state of CLK
    if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
      if (digitalRead(DT) == currentStateCLK) {
        Label(Leading_zero(count, leading), x_pos, y_pos, text_size,"black");
        count --;
        if (count < min_val){
          count = max_val;
        }
        Label(Leading_zero(count, leading), x_pos, y_pos, text_size,"white");
      } else {
        Label(Leading_zero(count, leading), x_pos, y_pos, text_size,"black");
        count ++;
        if (count > max_val){
          count = min_val;
        }
        Label(Leading_zero(count, leading), x_pos, y_pos, text_size,"white"); 
      }
    }
    lastStateCLK = currentStateCLK;
    int btnState = digitalRead(SW);
    if (btnState == LOW or digitalRead(PB_10n) == LOW) {
      if (millis() - lastButtonPress > 50) {
        break;
      }
      if (digitalRead(PB_10n) == LOW) {
        delay(250);
        if (digitalRead(PB_10n) == LOW) {
          delay(250);
          break;
        }
        
      }
      lastButtonPress = millis();
    }
  }
  return count;
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                         CUSTOM POI MODULE
//                               DEFINE CUSTOM POI LONGITUDE AND LATITUDE

// ************************************************************************************************
void rot_encoder_CUSTOM_POI() {
  int custom_deg = rot_encoder_CUSTOM_coordinate(90, "lon deg");
  int custom_min = rot_encoder_CUSTOM_coordinate(60, "lon min");
  int custom_sec = rot_encoder_CUSTOM_coordinate(60, "lon sec");  
  custom_POI_long = float(custom_deg) + float(custom_min)/60 + float(custom_sec)/3600;
  custom_deg = rot_encoder_CUSTOM_coordinate(90, "lat deg");
  custom_min = rot_encoder_CUSTOM_coordinate(60, "lat min");
  custom_sec = rot_encoder_CUSTOM_coordinate(60, "lat sec");  
  custom_POI_lat = float(custom_deg) + float(custom_min)/60 + float(custom_sec)/3600;

  char buf[8]; dtostrf(custom_POI_long, 14, 4, buf); Label(buf, 180, 190, 4,"white");
  char buf1[8]; dtostrf(custom_POI_lat, 14, 4, buf1); Label(buf1, 180, 220, 4,"white");
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                               SET VALUES USING ROTARY ENCODER MODULE
//                             SET CUSTOM POI VALUES USING ROTARY ENCODER 

// ************************************************************************************************
float rot_encoder_CUSTOM_coordinate(int max_val, String text) {
  Label(text, 180, 190, 4,"cyan");
  unsigned long lastButtonPress = millis();
  int count = 0; int currentStateCLK;
  while( true ) {
    currentStateCLK = digitalRead(CLK);  // Read the current state of CLK
    if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
      if (digitalRead(DT) == currentStateCLK) {
        Label(Leading_zero(count, 2), 280, 190, 4,"black");
        count --;
        if (count < 0){
          count = max_val;
        }
        Label(Leading_zero(count, 2), 280, 190, 4,"white");
      } else {
        Label(Leading_zero(count, 2), 280, 190, 4,"black");
        count ++;
        if (count > max_val){
          count = 0;
        }
        Label(Leading_zero(count, 2), 280, 190, 4,"white"); 
      }
    }
    lastStateCLK = currentStateCLK;
    int btnState = digitalRead(SW);
    if (btnState == LOW) {
      if (millis() - lastButtonPress > 50) {
        break;
      }
      lastButtonPress = millis();
    }
  }
  return count;
}

String rot_encoder_POI_NAME() {
  tft.fillScreen(TFT_BLACK);
  Label("Set custom POI name", 50, 50, 4,"yellow");
  unsigned long lastButtonPress = millis();
  int max_val = 61;
  String let_num[] = {"", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "Lj", "M", "N", "Nj", "O", "P", "R", "S", "T", "U", "V", "Z", 
                      "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "lj", "m", "n", "nj", "o", "p", "r", "s", "t", "u", "v", "z",
                      "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", " ", "-", "_"};                   
  String POI_name = "";
  int poz = 1;
  int count = 1;
  while ( true ){
    int currentStateCLK;
    int count = 0;
    while( true ) {
      currentStateCLK = digitalRead(CLK);  // Read the current state of CLK
      if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
        if (digitalRead(DT) == currentStateCLK) {
          Label(let_num[count], 100 + poz * 20, 100, 4,"black");
          count --;
          if (count < 0){
            count = max_val;
          }
          Label(let_num[count], 100 + poz * 20, 100, 4,"white");
        } else {
          Label(let_num[count], 100 + poz * 20, 100, 4,"black");
          count ++;
          if (count > max_val){
            count = 0;
          }
          Label(let_num[count], 100 + poz * 20, 100, 4,"white");
        }
      }
      lastStateCLK = currentStateCLK;
      int btnState = digitalRead(SW);
      if (btnState == LOW) {
        if (millis() - lastButtonPress > 50) {
          break;
        }
        lastButtonPress = millis();
      }
    }
    POI_name = POI_name + let_num[count];

    if (count == 0){
      tft.fillScreen(TFT_BLACK);
      break;
    }
    poz += 1;
    delay(200);
  } 
  return POI_name; 
}
