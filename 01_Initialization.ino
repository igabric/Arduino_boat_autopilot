void Inicijalizacija(){
  init_disp();
  delay(1000);
  //digitalWrite(enablePin, HIGH); // enable stepper
  STEPPER_MOTOR.setCurrentPositionInMillimeters(0);
  tft.fillRect(0, 0, 480, 2, TFT_WHITE);
  tft.fillRect(0, 12, 480, 2, TFT_WHITE);
  tft.fillRect(0, 2, 200, 10, TFT_RED);
  tft.fillRect(280, 2, 200, 10, TFT_GREEN);
  tft.fillRect(0, 16, 480, 30, TFT_WHITE);
  while(digitalRead(PB_1p)== HIGH){
    // digitalWrite(enablePin, HIGH); // enable stepper
    if (digitalRead(PB_1n) == LOW){
      offset_input();
      break;
    }
    while (digitalRead(PB_10n) == LOW or digitalRead(button1) == HIGH){
      // tft.fillCircle(10, 100, 10, TFT_GREEN);
      tft.fillTriangle(60, 100, 90, 80, 90, 120, TFT_GREEN);
      digitalWrite(enablePin, HIGH); // enable stepper
      temp = temperatura(); 
      STEPPER_MOTOR.moveRelativeInMillimeters(10);
      // digitalWrite(enablePin, LOW); // disable stepper    
    }
    while (digitalRead(PB_10p) == LOW or digitalRead(button2) == HIGH){
      tft.fillTriangle(410, 100, 380, 80, 380, 120, TFT_GREEN);
      digitalWrite(enablePin, HIGH); // enable stepper
      temp = temperatura(); 
      STEPPER_MOTOR.moveRelativeInMillimeters(-10); 
      // digitalWrite(enablePin, LOW); // disable stepper       
    }
    tft.fillTriangle(60, 100, 90, 80, 90, 120, TFT_BLACK);
    tft.fillTriangle(410, 100, 380, 80, 380, 120, TFT_BLACK);
    digitalWrite(enablePin, LOW); // disable stepper

    
    
    Kompas_labels(int(Calc_heading()));

  }
  STEPPER_MOTOR.setCurrentPositionInMillimeters(0);
  digitalWrite(enablePin, LOW); // disable stepper
  tft.fillScreen(TFT_BLACK); 
  tft.setTextColor(TFT_YELLOW, TFT_BLACK); tft.setCursor(50, 160, 4); tft.println("INITIALIZATION    FINISHED !!!");
  delay(1000);
  tft.fillScreen(TFT_BLACK);
  Screen_1_navigation();
}

void init_disp(){
  tft.fillScreen(TFT_BLACK);
  int pos_x = 100;
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  
  tft.setCursor(80, 100, 4);
  tft.setTextColor(TFT_RED, TFT_BLACK);

  tft.fillCircle(50, 188, 15, TFT_WHITE);
  tft.fillCircle(50, 188, 10, TFT_YELLOW);

  tft.fillCircle(50, 148, 15, TFT_WHITE);
  tft.fillCircle(50, 148, 10, TFT_RED);

  tft.fillCircle(50, 268, 15, TFT_WHITE);
  tft.fillCircle(50, 268, 10, TFT_GREEN);

  tft.fillCircle(50, 228, 15, TFT_WHITE);
  tft.fillCircle(50, 228, 10, TFT_BLACK);
  
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setCursor(pos_x, 180, 4);
  tft.println(" Turn sterring wheel right");
  tft.setCursor(pos_x, 140, 4);
  tft.println(" Turn sterring wheel left");
  tft.setCursor(pos_x, 260, 4);
  tft.println(" Initialization finish");
  tft.setCursor(pos_x, 220, 4);
  tft.println(" Setting offset");
}

void offset_input(){

  // FIRST SETUP DISPLAY
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(20, 10, 4); tft.println("Steering Offset:");
  tft.setCursor(240, 10, 4); tft.println("Lower Speed Limit:");
  tft.setCursor(20, 95, 4); tft.println("AngleDeviation:");
  tft.setCursor(240, 95, 4); tft.println("Heading Correction:");
  tft.setCursor(20, 180, 4); tft.println("Steering Speed:");
  tft.setCursor(240, 180, 4); tft.println("CourseOverGround:");
  tft.setCursor(20, 260, 4); tft.println("StepperDirection:");
  tft.setCursor(240, 260, 4); tft.println("GPS Smart Delay:");

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setCursor(50, 50, 4); tft.println(steering_offset);
  tft.setCursor(270, 50, 4); tft.println(lower_speed_limit);
  tft.setCursor(50, 135, 4); tft.println(dop_odstupanje_kursa);
  tft.setCursor(270, 135, 4); tft.println(heading_correction);
  tft.setCursor(50, 220, 4); tft.println(stepper_speed);
  tft.setCursor(270, 220, 4); tft.println(course_COG);
  tft.setCursor(50, 290, 4); tft.println(step_direction_positive);
  tft.setCursor(270, 290, 4); tft.println(gps_reading_smart_delay);
  
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setCursor(110, 50, 4); tft.println("deg");
  tft.setCursor(330, 50, 4); tft.println("knots");
  tft.setCursor(110, 135, 4); tft.println("deg");
  tft.setCursor(330, 135, 4); tft.println("deg");
  tft.setCursor(110, 220, 4); tft.println("deg/s");
  tft.setCursor(330, 220, 4); tft.println(" -");
  tft.setCursor(110, 290, 4); tft.println(" -");
  tft.setCursor(330, 290, 4); tft.println("sec");

  delay(100);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawRect(45, 45, 60, 32, TFT_YELLOW);
  steering_offset = int(rot_encoder_SET_CUSTOM_COORDINATE(50, 50, 50, 4, 0 , 2, steering_offset));
  tft.drawRect(45, 45, 60, 32, TFT_BLACK);
  tft.drawRect(265, 45, 60, 32, TFT_YELLOW);
  lower_speed_limit = int(rot_encoder_SET_CUSTOM_COORDINATE(270, 50, 5, 4, 0, 2, lower_speed_limit));
  tft.drawRect(265, 45, 60, 32, TFT_BLACK);
  tft.drawRect(45, 130, 60, 32, TFT_YELLOW);
  dop_odstupanje_kursa = int(rot_encoder_SET_CUSTOM_COORDINATE(50, 135, 10, 4, 0, 2, dop_odstupanje_kursa));
  tft.drawRect(45, 130, 60, 32, TFT_BLACK);
  tft.drawRect(265, 130, 60, 32, TFT_YELLOW);  
  heading_correction = int(rot_encoder_SET_CUSTOM_COORDINATE(270, 135, 180, 4, -180, 3, heading_correction)); 
  tft.drawRect(265, 130, 60, 32, TFT_BLACK);
  tft.drawRect(45, 215, 60, 32, TFT_YELLOW);
  stepper_speed = int(rot_encoder_SET_CUSTOM_COORDINATE(50, 220, 120, 4, 1, 3, stepper_speed)); 
  tft.drawRect(45, 215, 60, 32, TFT_BLACK);
  tft.drawRect(265, 215, 60, 32, TFT_YELLOW);
  course_COG = int(rot_encoder_SET_CUSTOM_COORDINATE(270, 220, 1, 4, 0, 2, course_COG));
  tft.drawRect(265, 215, 60, 32, TFT_BLACK);
  tft.drawRect(45, 285, 60, 32, TFT_YELLOW);
  if(int(rot_encoder_SET_CUSTOM_COORDINATE(50, 290, 1, 4, 0, 2, step_direction_positive))==1){
    step_direction_positive = 1;
  }
  else{
    step_direction_positive = -1;
  }
  tft.drawRect(45, 285, 60, 32, TFT_BLACK);
  tft.drawRect(265, 285, 60, 32, TFT_YELLOW);
  gps_reading_smart_delay = int(rot_encoder_SET_CUSTOM_COORDINATE(270, 290, 30, 4, 1, 2, gps_reading_smart_delay));
  tft.drawRect(265, 285, 60, 32, TFT_BLACK);
  
  // SECOND SETUP DISPLAY
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(20, 10, 4); tft.println("SteeringMaxAngle :");
  tft.setCursor(20, 95, 4); tft.println("Pulley 1 - teeth:");
  tft.setCursor(240, 95, 4); tft.println("Pulley 2 - teeth:");
  tft.setCursor(20, 180, 4); tft.println("Delay to Neutral:");

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setCursor(50, 50, 4); tft.println(Max_steering_turning_deg);
  tft.setCursor(50, 135, 4); tft.println(pulley1_teeth);
  tft.setCursor(270, 135, 4); tft.println(pulley2_teeth);
  tft.setCursor(50, 220, 4); tft.println(delay_to_neutral);
  
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setCursor(110, 50, 4); tft.println("degrees");
  tft.setCursor(110, 135, 4); tft.println("teeth");
  tft.setCursor(330, 135, 4); tft.println("teeth");
  tft.setCursor(110, 220, 4); tft.println("seconds");

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawRect(45, 45, 60, 32, TFT_YELLOW);
  Max_steering_turning_deg = int(rot_encoder_SET_CUSTOM_COORDINATE(50, 50, 360, 4, 0 , 3, Max_steering_turning_deg));
  tft.drawRect(45, 45, 60, 32, TFT_BLACK);
  tft.drawRect(45, 130, 60, 32, TFT_YELLOW); 
  pulley1_teeth = int(rot_encoder_SET_CUSTOM_COORDINATE(50, 135, 250, 4, 0, 3, pulley1_teeth));
  tft.drawRect(45, 130, 60, 32, TFT_BLACK);
  tft.drawRect(265, 130, 60, 32, TFT_YELLOW);
  pulley2_teeth = int(rot_encoder_SET_CUSTOM_COORDINATE(270, 135, 250, 4, 0, 3, pulley2_teeth)); 
  tft.drawRect(265, 130, 60, 32, TFT_BLACK);
  tft.drawRect(45, 215, 60, 32, TFT_YELLOW);
  delay_to_neutral = int(rot_encoder_SET_CUSTOM_COORDINATE(50, 220, 10, 4, 1, 2, delay_to_neutral)); 
  tft.drawRect(45, 215, 60, 32, TFT_BLACK);

  // SAVING SETTINGS ON SD CARD
  
  SD.remove("varijabl.txt"); // delete the file if existed
  myFile = SD.open("varijabl.txt", FILE_WRITE); // create new file by opening file for writing
  myFile.println(steering_offset);
  myFile.println(lower_speed_limit);
  myFile.println(dop_odstupanje_kursa);
  myFile.println(heading_correction);
  myFile.println(stepper_speed);
  myFile.println(course_COG);
  myFile.println(step_direction_positive);
  myFile.println(gps_reading_smart_delay);
  myFile.println(Max_steering_turning_deg);
  myFile.println(pulley1_teeth);
  myFile.println(pulley2_teeth);
  myFile.println(delay_to_neutral);
  myFile.close();
  Serial.println("FILE UPDATED !!!");
  tft.fillScreen(TFT_BLACK);
   
  STEPPER_MOTOR.setSpeedInMillimetersPerSecond(stepper_speed);
  Inicijalizacija();
}
