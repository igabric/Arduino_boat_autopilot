// ************************************************************************************************

//                                         STEPPER MODULE
//                                     ACTIVATE STEPPER MOTOR

// ************************************************************************************************
void Stepper_RUN(int stepper_speed, int stepper_position){
  if (STEPPER_MOTOR.run() == 0){
    STEPPER_MOTOR.enableOutputs();
    STEPPER_MOTOR.setSpeed(stepper_speed);
    STEPPER_MOTOR.moveTo(stepper_position);
    STEPPER_MOTOR.runToPosition();
    STEPPER_MOTOR.disableOutputs();
  }  
}

//void Stepper_init(){
//  STEPPER_MOTOR.enableOutputs();
//  
//  tft.setTextColor(TFT_YELLOW);
//  tft.drawCentreString("INITIALIZATION", 240, 150, 4);
//    
////  while(digitalRead(PB_1n) == LOW or digitalRead(PB_1p) == LOW){
////    while(digitalRead(PB_10n) == LOW){
////      STEPPER_MOTOR.setSpeed(-6400);
////      STEPPER_MOTOR.run();
////    }
////    while(digitalRead(PB_10p) == LOW){
////      STEPPER_MOTOR.setSpeed(6400);
////      STEPPER_MOTOR.run();
////    }
////  }
//  
//  delay(2000);
//  tft.fillScreen(TFT_BLACK);
//  
//}
