// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                    LEADING ZERO MODULE
//                         PREPARE STRING WITH LEADING ZERO FOR TFT PRINT

// ************************************************************************************************
String Leading_zero(int number, int number_of_place){
  String String_broj;
  if (number_of_place == 3){
    if (number < 100 and number >= 10){
      String_broj = "0" + String(number); 
    }
    else if (number < 10 and number >= 0){
      String_broj = "00" + String(number); 
    }
    else if (number < 0 and number > -10){
      String_broj = "-00" + String(abs(number));
    }
    else if (number <= -10 and number > -100){
      String_broj = "-0" + String(abs(number));
    }
    else{
      String_broj = String(number); 
    }
  }
  if (number_of_place == 2){
    if (number < 10 and number >= 0){
      String_broj = "0" + String(number); 
    }
    else if (number < 0 and number > -10){
      String_broj = "-0" + String(abs(number));
    }
    else{
      String_broj = String(number);
    }
  }
  return String_broj;
}

String Leading_space(int number, int number_of_place){
  String String_broj;
  if (number_of_place == 3){
    if (number < 100 and number > 9){
      String_broj = "  " + String(number); 
    }
    else if(number < 10){
      String_broj = "    " + String(number); 
    }
    else{
      String_broj = String(number); 
    }
  }
  if (number_of_place == 2){
    if (number < 10){
      String_broj = "  " + String(number); 
    }
    else{
      String_broj = String(number); 
    }
  }
  return String_broj;
}
// ------------------------------------------------------------------------------------------------

// ************************************************************************************************

//                                        RADIANS MODULE
//                              CONVERT DECIMAL DEGREES TO RADIANS

// ************************************************************************************************

float radijani(float stupanj){
  float rad = stupanj * M_PI/180;
  return rad;  
}
// ------------------------------------------------------------------------------------------------

/* *************************************************************************************************
** Function name:           drawRAW
** Descriptions:            draw a 565 format 16 bit raw image file
**************************************************************************************************/

// This function opens a ".raw" image file and displays it at the given coordinates.
// It is faster than plotting BMP images as the file is already in the correct
// format to pipe directly to the display.
// The width and height of the image in pixels must be passed to the function
// as these parameters are not in the file

// Set buffer size, 2 x this size of RAM bytes will be used in the array.
// Reduce if RAM is short with some performance penalty
// Powers of 2 work well

#define RBUFF_SIZE 256

void drawRAW(char *filename, int16_t x, int16_t y, int16_t rawWidth, int16_t rawHeight) {
  File     rawFile;
  uint8_t  sdbuffer[2 * RBUFF_SIZE];   // SD read pixel buffer (16 bits per pixel)
  //// // Serial.println(filename);

  // Check file exists and open it
  if ((rawFile = SD.open(filename)) == NULL) {
    // // Serial.println(F(" File not found"));
    return;
  }

  // Prepare the TFT screen area to receive the data
  tft.setWindow(x, y, x + rawWidth - 1, y + rawHeight - 1);
 
  // Work out how many whole buffers to send
  uint16_t nr = ((long)rawHeight * rawWidth)/RBUFF_SIZE;
  while(nr--) {
    rawFile.read(sdbuffer, sizeof(sdbuffer));
    tft.pushColors(sdbuffer, RBUFF_SIZE);
  }
  
  // Send any partial buffer
  nr = ((long)rawHeight * rawWidth)%RBUFF_SIZE;
  if (nr) {
    rawFile.read(sdbuffer, nr<<1); // We load  2 x nr bytes
    tft.pushColors(sdbuffer, nr);  // We send nr 16 bit pixels
  }

  // Close the file
  rawFile.close();
}
