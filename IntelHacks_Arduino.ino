// Button is connected from reset pin to ground, when soap is put into the device,
// the user presses the button to reset the board. Starts calibration
// procedure. 

// All comented out Serial prints were added during the development of the software, but 
// have to be disabled when the RPi is reading the Serial of the Arduino


int lightPin=1;
int threshold = 1000; // Set threshold for low volume condition (experimental)
int counter = 0;
int counter_setup = 0;
int times_setup = 0;
int times = 0;
int set_up = 0;
int setup_pin = 13;
int ready_pin = 12; 
int order_pin = 11; 
int resetbutton = 7;
int buttonstate = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(setup_pin,OUTPUT);
  pinMode(ready_pin,OUTPUT);
  pinMode(order_pin,OUTPUT);
  pinMode(resetbutton,INPUT);
}

// Create some conditions so that the user knows when its ready to go
void loop() {
  int volume = analogRead(lightPin);
  // LED is red, which means the sensor is reading light
  
  while (set_up == 0) { // while loop so that it doesn't fall back once soap has been ordered
    digitalWrite(order_pin,LOW);
    digitalWrite(setup_pin,HIGH);
//    Serial.println(volume);
//    Serial.println("setting up");
    volume = analogRead(lightPin);
    delay(1000);
    if (times_setup == 2) {
      digitalWrite(setup_pin,LOW);
      delay(1000);
      set_up = 1;
    } else if (volume < threshold) {
      times_setup = times_setup + 1;
      delay(1000); // delay for half a second to parse out any errors
    }
  } // once it stops reading light, the device is ready
  delay(500); // delay to stabilize void loop
  // LED is green, the device has been set up
  
  while (counter == 0) {
    volume = analogRead(lightPin);
    if (times == 2) { // We can make times be as high a value as we want
      // Shoot value to database
//      Serial.println("Ordering another soap");
      counter = 1; // To stop the loop
      digitalWrite(ready_pin,LOW);
      digitalWrite(order_pin,HIGH); // LED is blue, device has ordered
      Serial.println(1);
    } else if (volume > threshold) {
//      Serial.println("volume low!");
      delay(1000*60*5); // This delay is 5 minutes, so that it doesn't go back to analyzing right away
//      delay(1000*5);
      times = times + 1; // Increase the number of times it detects soap low
//      Serial.println(times);
    } else {
//      Serial.println("standby");
//      Serial.println(volume);
      digitalWrite(ready_pin,HIGH); // green LED starts
      delay(1000);
    }
     
  }
//  Serial.println("waiting for soap");
  buttonstate = digitalRead(resetbutton);
  if (buttonstate == HIGH) {
    counter = 0;
    set_up = 0;
    times = 0;
    times_setup = 0;
//    Serial.println("button press");
    delay(1000);
  }
}
