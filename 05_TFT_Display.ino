// ************************************************************************************************

//                                        COMPASS LABELS MODULE
//                              PRINT DYNAMICALLY COMPASS LABELS ON TFT DISPLAY

// ************************************************************************************************
void Kompas_labels(int angle_pos){
  tft.setTextColor(TFT_BLACK);
  String kurs_labels[] = {"N", "30", "60", "E", "120", "150", "S", "210", "240", "W", "300", "330",
                        "N", "30", "60", "E", "120", "150", "S", "210", "240", "W", "300", "330"};
  char buf[10];
  int len = 4;  
  float faktor = 2.2;
  int label_offset = 2;
  int pomak_oznaka;
   
  tft.fillRect(0, 16, 480, 30, TFT_WHITE);
  tft.drawRect(172, 50, 140, 40, TFT_WHITE);
  
  tft.fillTriangle(240, 16, 235, 26, 245, 26, TFT_BLACK);
  tft.fillTriangle(240, 18, 237, 24, 243, 24, TFT_WHITE);
  
  if (angle_pos > 90 and angle_pos <= 120){
      label_offset = 0;
      pomak_oznaka = int((angle_pos - 90)*faktor);
    }
    else if (angle_pos > 120 and angle_pos <= 150){
      label_offset = 1;
      pomak_oznaka = int((angle_pos - 120)*faktor);
    }
    else if (angle_pos > 150 and angle_pos <= 180){
      label_offset = 2;
      pomak_oznaka = int((angle_pos - 150)*faktor);
    }
    else if (angle_pos > 180 and angle_pos <= 210){
      label_offset = 3;
      pomak_oznaka = int((angle_pos - 180)*faktor);
    }
    else if (angle_pos > 210 and angle_pos <= 240){
      label_offset = 4;
      pomak_oznaka = int((angle_pos - 210)*faktor);
    }
    else if (angle_pos > 240 and angle_pos <= 270){
      label_offset = 5;
      pomak_oznaka = int((angle_pos - 240)*faktor);
    }
    else if (angle_pos > 270  and angle_pos <= 300 ){
      label_offset = 6;
      pomak_oznaka = int((angle_pos - 270)*faktor);
    }
    else if (angle_pos > 300  and angle_pos <= 330){
      label_offset = 7;
      pomak_oznaka = int((angle_pos - 300)*faktor);
    }
    else if (angle_pos > 330  and angle_pos <= 359){
      label_offset = 8;
      pomak_oznaka = int((angle_pos - 330)*faktor);
    }
    else if (angle_pos >= 0 and angle_pos <= 30){
      label_offset = 9;
      pomak_oznaka = int((angle_pos - 0)*faktor);
    }
    else if (angle_pos > 30  and angle_pos <= 60){
      label_offset = 10;
      pomak_oznaka = int((angle_pos - 30)*faktor);
    }
    else {
      label_offset = 11;
      pomak_oznaka = int((angle_pos - 60)*faktor);
    }

  tft.setTextColor(TFT_YELLOW);
  tft.fillRect(250, 60, 50, 25, TFT_BLACK);
  tft.drawString("HDG:", 180, 60, 4);
  
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setCursor(250, 57, 4);
  tft.print(Leading_zero(angle_pos, 3));

  tft.drawCircle(300, 57, 3, TFT_YELLOW);
   
  for (int i = 0; i < 8; i++){
    tft.setTextColor(TFT_BLACK);
    
    kurs_labels[label_offset+i].toCharArray(buf, len);

    tft.drawRect(-pomak_oznaka + 9 +33  + 66*i, 16, 3, 7, TFT_RED);    
    tft.drawLine(-pomak_oznaka + 31 +33  + 66*i, 16, -pomak_oznaka + 31 +33  + 66*i, 20, TFT_RED); 
    tft.drawLine(-pomak_oznaka + 53 +33  + 66*i, 16, -pomak_oznaka + 53 +33  + 66*i, 20, TFT_RED); 
    if (-pomak_oznaka + 9 +33 + 66*i < 471 and -pomak_oznaka + 9 + 33 + 66*i > 6 ){
      tft.drawCentreString(buf, -pomak_oznaka + 9 +33 + 66*i, 28, 2);
    }
  }
  delay(200);
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                        COMPASS PREPARING MODULE
//               PREPARING AND PRINTING OF GRAPHICS FOR COMPASS ON THE TOP OF TFT DISPLAY

// ************************************************************************************************
void Compas_preparation(){

  tft.fillRect(0, 0, 480, 2, TFT_WHITE);
  tft.fillRect(0, 12, 480, 2, TFT_WHITE);
  tft.fillRect(0, 2, 200, 10, TFT_RED);
  tft.fillRect(280, 2, 200, 10, TFT_GREEN);
  tft.fillRect(0, 16, 480, 30, TFT_WHITE);

  tft.setTextColor(TFT_CYAN);
  tft.setCursor(220, 160, 4);  tft.print("POI:");
  tft.setTextColor(TFT_YELLOW);
  tft.drawString("Heading:        ", 10, 110, 4);
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                        COG SOG MODULE
//                              PRINT COG AND SOG ON TFT DISPLAY

// ************************************************************************************************
void Cog_Sog(float cog, float sog){
  char buf1[8];
  char buf2[8];  
  dtostrf(sog, 4, 1, buf1);
  dtostrf(cog, 4, 1, buf2);
  
  tft.fillRect(80, 260, 50, 25, TFT_BLACK);
  tft.setTextColor(TFT_YELLOW);
  tft.fillRect(30, 260, 50, 25, TFT_BLACK);
  tft.drawString("SOG:", 10, 260, 4);
  tft.drawString("knots", 136, 260, 4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawRightString(buf1, 130, 260, 4); 
  
  tft.fillRect(80, 290, 70, 25, TFT_BLACK);
  tft.fillRect(30, 290, 50, 25, TFT_BLACK);
  tft.setTextColor(TFT_YELLOW);
  tft.drawString("COG:", 10, 290, 4);
  tft.drawCircle(156, 287, 3, TFT_WHITE);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawRightString(buf2, 150, 290, 4); 
  
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                        DISTANCE TO GO MODULE
//                              PRINT DISTANCE TO GO MODULE ON TFT DISPLAY

// ************************************************************************************************
void TFT_distance(float way_to_go){
  char buf1[5];
  dtostrf(way_to_go, 8, 2, buf1);
  tft.drawString("Dist:", 410, 160, 4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawRightString(buf1, 480, 190, 4); 
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawString("nm", 420, 210, 4);
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                        SET HEADING MODULE
//                                  PRINT HEADING ON TFT DISPLAY

// ************************************************************************************************
void SET_HDG(float hdg_set_value){
  int decimal = int(100*(hdg_set_value - int(hdg_set_value)));
  String buf1 = Leading_zero(hdg_set_value, 3);
  String buf2 = Leading_zero(decimal, 2);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.setCursor(10, 140, 8);
  tft.print(buf1);
  tft.setCursor(180, 140, 4);
  tft.print(buf2);
  tft.setTextColor(TFT_BLACK, TFT_BLACK);
  tft.setCursor(65, 220, 4);
  tft.print("        ");
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.setCursor(65, 220, 4);
  tft.print(gps.cardinal(hdg_set_value)); // print the sides of the world in letters form
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                        LONGITUDE LATITUDE MODULE
//                                  PRINT LONGITUDE AND LATITUDE ON TFT DISPLAY

// ************************************************************************************************
void Lat_Long(float latitude, float longitude){
  char buf1_long [8]; char buf2_lat [8];  
  dtostrf(longitude, 5, 4, buf1_long);
  dtostrf(latitude, 5, 4, buf2_lat);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString("Long:", 280, 260, 4);
  
  tft.drawCircle(455, 257, 3, TFT_WHITE);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawRightString(buf1_long, 445, 260, 4); 

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString("Lat:", 280, 290, 4);
  drawRAW("Rudder.raw", 215, 260, 50, 50);
  tft.drawCircle(455, 287, 3, TFT_WHITE);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawRightString(buf2_lat, 445, 290, 4); 
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                          TIME MODULE
//                                PRINT CURRENT TIME ON TFT DISPLAY


// ************************************************************************************************
void Time_TFT(int sati, int minuta, int posx, int posy, int letter_size){

  String buf1;  String buf2;
  buf1 = Leading_zero(sati, 2);  buf2 = Leading_zero(minuta, 2);
    
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setCursor(posx, posy, letter_size);  tft.print(buf1);
  tft.setCursor(posx + 30, posy, letter_size);  tft.print(":");
  tft.setCursor(posx + 38, posy, letter_size);  tft.print(buf2);
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                          LABEL MODULE
//                                PRINT CUSTOM LABELS ON TFT DISPLAY

// ************************************************************************************************
void Label(String labela, int posx, int posy, int letter_size, String colour_fore){
  if (colour_fore == "green"){
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
  }
  else if(colour_fore == "yellow"){
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  }
  else if(colour_fore == "cyan"){
    tft.setTextColor(TFT_CYAN, TFT_BLACK);
  }
  else if(colour_fore == "red"){
    tft.setTextColor(TFT_RED, TFT_BLACK);
  }
  else if(colour_fore == "black"){
    tft.setTextColor(TFT_BLACK);
  }
  else if(colour_fore == "white"){
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
  }
  tft.setCursor(posx, posy, letter_size);  tft.print(labela);
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                          DATE MODULE
//                                PRINT CURRENT DATE ON TFT DISPLAY

// ************************************************************************************************
void Date_TFT(int dan, int mjesec, int godina){
  String buf1;  String buf2;  String buf3;
  
  buf1 = Leading_zero(dan, 2);
  buf2 = Leading_zero(mjesec, 2);
  buf3 = String(godina);
  
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setCursor(0, 80, 2);  tft.print(buf1);
  tft.setCursor(20, 80, 2);  tft.print("-");
  tft.setCursor(30, 80, 2);  tft.print(buf2);
  tft.setCursor(48, 80, 2);  tft.print("-");
  tft.setCursor(60, 80, 2);  tft.print(buf3);
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                          SATELITE MODULE
//                           PRINT NUMBER OF ACTIVE SATELLITES ON TFT DISPLAY

// ************************************************************************************************
void Satelites_TFT(int sat_num){
  String buf1 = String(sat_num); 
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setCursor(340, 80, 4);  tft.print("Sat. no.:");
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  if (sat_num < 10){
    buf1 = "0" + buf1;
  }
  tft.setCursor(440, 80, 4);  tft.print(buf1);
}
void hdop_TFT(float hdop_val){
  String buf1 = String(hdop_val); 
  tft.setCursor(400, 50, 4);  tft.print("        ");
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setCursor(340, 50, 4);  tft.print("Acc:");
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(400, 50, 4);  tft.print(buf1);
}
