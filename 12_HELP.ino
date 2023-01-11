void HELP_scr1(){
  tft.fillScreen(TFT_BLACK);
  int pos_x = 190;
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setCursor(20, 20, 4);
  tft.println("COMMANDS");
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.setCursor(20, 80, 4);
  tft.println("PUSH BTTN:");
  tft.setCursor(20, 120, 4);
  tft.println("BTN1 + BTN4:");
  tft.setCursor(20, 160, 4);
  tft.println("BTN2 + BTN3:");
  tft.setCursor(20, 200, 4);
  tft.println("BTN1 + BTN2:");
  tft.setCursor(20, 240, 4);
  tft.println("BTN1 / BTN2:");
  tft.setCursor(20, 280, 4);
  tft.println("BTN3 / BTN4:");
  
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setCursor(pos_x, 80, 4);
  tft.println(" Set HEADING");
  tft.setCursor(pos_x, 120, 4);
  tft.println(" POI / HEADING mode");
  tft.setCursor(pos_x, 160, 4);
  tft.println(" Autopilot ON/OFF");
  tft.setCursor(pos_x, 200, 4);
  tft.println(" EXIT HELP menu");
  tft.setCursor(pos_x, 240, 4);
  tft.println(" SetHEADING +1 / +10 deg");
  tft.setCursor(pos_x, 280, 4);
  tft.println(" SetHEADING -1 / -10 deg");
  delay(5000);
  tft.fillScreen(TFT_BLACK);
  Kompas_priprema();
  SET_HDG(hdg_set_value);
  Autopilot(autopilot_ON);
  HELP_scr2();
}

void HELP_scr2(){
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setCursor(170, 230, 2);
  tft.println("HELP :");
  tft.setTextColor(TFT_PINK, TFT_BLACK);
  tft.setCursor(220, 230, 2);
  tft.println("BTN1 + BTN2");
  tft.drawRoundRect(160, 225, 155, 25, 5, TFT_RED);
}
