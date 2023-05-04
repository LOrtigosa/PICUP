//Here are some of the optimizations made:

//Converted the duration input from multiple bytes to a single string for easier processing.
//Removed the need for byte1 to byte6 variables by processing the command as a single character.
//Removed the need for a while loop when setting the LED duration, instead waiting for the next command.
//Used a boolean flag for the LED state instead of a separate ledState variable.

const int LED_PIN = A0;  // LED pin
unsigned long period = 0; // blinking period
unsigned long start_millis;  // initial start time
bool is_led_on = false; // flag for LED state

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Welcome to KeepUP!");
  Serial.println("Enter 'h' for help.");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == 'h') {  // Help command
      Serial.println("\n-----------------------------");
      Serial.println("| Available commands:        |");
      Serial.println("| 'h': Help                  |");
      Serial.println("| 't': Set duration          |");
      Serial.println("| 'p': View duration         |");
      Serial.println("| 'l': Toggle LED on/off     |");
      Serial.println("-----------------------------\n");
    }
    else if (command == 't') {  // Set duration command
      char duration_string[6];
      Serial.readBytes(duration_string, 5);
      duration_string[5] = '\0'; // Null-terminate the string
      period = atol(duration_string);
      Serial.print("Duration set to ");
      Serial.print(period);
      Serial.println(" ms.");
      is_led_on = false;
    }
    else if (command == 'p') {  // View duration command
      Serial.print("Duration is ");
      Serial.print(period);
      Serial.println(" ms.");
    }
    else if (command == 'l') {  // Toggle LED on/off command
      if (period == 0) {
        Serial.println("Please set a duration first.");
      }
      else {
        if (is_led_on) {
          digitalWrite(LED_PIN, LOW);
          is_led_on = false;
        }
        else {
          digitalWrite(LED_PIN, HIGH);
          start_millis = millis();
          is_led_on = true;
        }
      }
    }
  }

  if (is_led_on && millis() - start_millis >= period) {  // Turn off LED after duration
    digitalWrite(LED_PIN, LOW);
    Serial.println("-");
    is_led_on = false;
  }
}



////----------------global variables available later in the program----------------
//const int ledPin = A0;
//int ledState = LOW;
//unsigned long period = 0L; //blinking period
//
//char byte1;
//
//char byte2;
//
//char byte3;
//
//char byte4;
//
//char byte5;
//
//char byte6;
//
//unsigned long startMillis;  //for the time loop
//
//unsigned long currentMillis; //for the time loop
//
////-------------------------------------------------------------------------------
//
//
//void setup () {
//
//  Serial.begin(9600);
//
//  pinMode(ledPin, OUTPUT);
//
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }
//
//  // send an intro:
//  Serial.println("Welcome to KeepUP!");
//  Serial.println();
//  Serial.println("Enter the letter 'h' if you need help.");
//  Serial.println();
//
//}
//
//void loop () {
//
//  if (Serial.available() > 0){
//
////----------------------------Save every character as byte#-------------------------------------
//
//    byte1 = Serial.read();
//    byte2 = Serial.read();
//    byte3 = Serial.read();
//    byte4 = Serial.read();
//    byte5 = Serial.read();
//    byte6 = Serial.read();
//
////-----------------------Do different stuff acording to the bytes-------------------------------
//
//    //----------------If first is 'h' = Help --> Explain commands-------------------------------
//
//    if (byte1 == 'h') {
//
//      Serial.println();
//      Serial.println(" ------------------------------Help Menu------------------------------ ");
//      Serial.println(" | The program has 4 types of commands:                                 | ");
//      Serial.println(" |                                                                     | ");
//      Serial.println(" |  -Command 'h': Help                                                 | ");
//      Serial.println(" |    Allows you to access the Help Menu.                              | ");
//      Serial.println(" |                                                                     | ");
//      Serial.println(" |  -Command 't': Time                                                 | ");
//      Serial.println(" |    Allows you to enter the period you want the LED to light for.    | ");
//      Serial.println(" |                                                                     | ");
//      Serial.println(" |    In order to choose a lighting time, type the letter 't' followed | ");
//      Serial.println(" |    by the number of miliseconds you want the LED to turn On for.    | ");
//      Serial.println(" |    WARNING: The value NEEDS to have 5 digits!                       | ");
//      Serial.println(" |                                                                     | ");
//      Serial.println(" |    Example: to set lighting time at 95634 ms -- > type t95634        | ");
//      Serial.println(" |             to set lighting time at 1000  ms -- > type t01000        | ");
//      Serial.println(" |                                                                     | ");
//      Serial.println(" |  -Command 'p': Period                                               | ");
//      Serial.println(" |    Tells you what's the currently set lighting period               |");
//      Serial.println("|                                                                     |");
//      Serial.println("|  -Command 'l': Light                                                |");
//      Serial.println("|    Turns the LED On for the duration indicated by command 't'       |");
//      Serial.println("|                                                                     |");
//      Serial.println(" --------------------------------------------------------------------- ");
//      Serial.println();
//    }
//
//    //----------------If first is 't' = Time --> Record time period-----------------------------
//
//    else if (byte1 == 't') {
//
//      //---------------------If a 5 digit number isn't written: Explain command---------------- -
//
//      if (isDigit(byte2) == false || isDigit(byte3) == false || isDigit(byte4) == false || isDigit(byte5) == false || isDigit(byte6) == false){
//        Serial.println("You have to enter a 5 digit number right after the letter 't' for the");
//        Serial.println("command to work.");
//        Serial.println();
//        Serial.println("    Example: to set lighting time at 95634 ms --> type t95634        ");
//        Serial.println("             to set lighting time at 1000  ms --> type t01000        ");
//        Serial.println();
//      }
//
//      //---------------------If a 5 digit number is written: Record period----------------------
//
//      else {
//
//        //To do math with integers to long numbers you need to add L to the numbers
//        period = (byte2 - 48)*10000L + (byte3 - 48)*1000L + (byte4 - 48)*100L + (byte5 - 48)*10L + (byte6 - 48);
//
//        Serial.print ("Lighting time for the LED was set at ");
//        Serial.print (period);
//        Serial.println (" ms.");
//        Serial.println ("If you want to change it type a 't' command again");
//        Serial.println ("If you want to light the LED for that duration press l");
//        Serial.println();
//      }
//
//    }
//
//    //-------------If first is 'p' = Period --> Reminds you what the currently set period is----
//
//    else if (byte1 == 'p') {
//      Serial.print("The currently set period is ");
//      Serial.print(period);
//      Serial.println(" ms");
//      Serial.println();
//    }
//
//
//    //-------------If first is 'l' = Light --> Flash the light for -period-ms-------------------
//
//    else if (byte1 == 'l') {
//
//      //---------------------If period hasn't been specified --> Offer command 't'--------------
//
//      if (period == 0){
//        Serial.println("You haven't set a lighting period yet.");
//        Serial.println("Set it by using a 't' command");
//        Serial.println();
//      }
//
//      //---------------------If period has been specified --> Light ON -------------------------
//
//      else {
//        Serial.println ("Lighting...");
//
//        startMillis = millis();  //initial start time (when typing "1")
//        currentMillis = millis();  //current time
//
//        while (currentMillis - startMillis <= period) { //Turn ON while [current - start] is lower than the period
//          digitalWrite(ledPin, HIGH);
//          currentMillis = millis(); //Update the current time
//        }
//
//        digitalWrite(ledPin, LOW); //turn off when the while loop ends
//        Serial.println ("Done!");
//        Serial.println();
//      }
//
//    }
//
//  }
//
//}
