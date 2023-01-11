// ************************************************************************************************

//                                         MAGNETOMETER MODULE
//                               READING HEADING USING MAGNETOMETER

// ************************************************************************************************
#ifdef Beitian_BN_880
  void displaySensorDetails()
  {
    sensor_t sensor;
    mag.getSensor(&sensor);
    delay(500);
  }
  
  int Calc_heading(){
    /* Get a new sensor event */ 
    sensors_event_t event; 
    mag.getEvent(&event);
    float heading = atan2(event.magnetic.y, event.magnetic.x);   
    heading += declinationAngle;
    
    if(heading < 0)             // Correct for when signs are reversed.
      heading += 2*PI;
      
    if(heading > 2*PI)          // Check for wrap due to addition of declination.
      heading -= 2*PI;
       
    int headingDegrees = int(heading * 180/M_PI);      // Convert radians to degrees for readability.     
    
    headingDegrees += heading_correction;

    if (headingDegrees > 359){
      headingDegrees -= 360;
    }  
    if (headingDegrees < 0){
      headingDegrees += 360;
    }
    Serial.println(headingDegrees);
    return headingDegrees;
  }  
#endif 
  
  
