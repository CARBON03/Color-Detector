

#include <LiquidCrystal_I2C.h>
#include <Wire.h> 


LiquidCrystal_I2C lcd(0x27,16,2); 
bool showMessage = true;


#define S0 4
#define S1 5
#define S2 7
#define S3 6
#define sensorOut 8
 
int redMin = 19; // Red minimum value
int redMax = 292; // Red maximum value
int greenMin = 20; // Green minimum value
int greenMax = 308; // Green maximum value
int blueMin = 16; // Blue minimum value
int blueMax = 235; // Blue maximum value
 
// Variables for Color Pulse Width Measurements
 
int redPW = 0;
int greenPW = 0;
int bluePW = 0;
 
// Variables for final Color values
 
int redValue;
int greenValue;
int blueValue;
 
void setup() {

  lcd.init();                     
  lcd.backlight();
  lcd.setBacklight(HIGH);
 
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Set Sensor output as input
  pinMode(sensorOut, INPUT);
  
  // Set Frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  // Setup Serial Monitor
  Serial.begin(9600);
}
 
void loop() {
  
  // Read Red value
  redPW = getRedPW();
  // Map to value from 0-255
  redValue = map(redPW, redMin,redMax,255,0);
  // Delay to stabilize sensor
  delay(200);
  
  // Read Green value
  greenPW = getGreenPW();
  // Map to value from 0-255
  greenValue = map(greenPW, greenMin,greenMax,255,0);
  // Delay to stabilize sensor
  delay(200);
  
  // Read Blue value
  bluePW = getBluePW();
  // Map to value from 0-255
  blueValue = map(bluePW, blueMin,blueMax,255,0);
  // Delay to stabilize sensor
  delay(200);


if (showMessage) {
    showMessage = false; // Set the flag to false after displaying the message once
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Color Detector!!");
    delay(2000);
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Div-A");
    lcd.setCursor(0,1);
    lcd.print("Rollno.-50,51,55");
    delay(3000);
    lcd.clear();
  }


  
  // Print output to Serial Monitor
  Serial.print("Red = ");
  Serial.print(redValue);
  Serial.print(" - Green = ");
  Serial.print(greenValue);
  Serial.print(" - Blue = ");
  Serial.println(blueValue);

if (redValue > 200 && greenValue > 200 && blueValue > 200) {
    Serial.println(" - WHITE detected!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("White detected!");
} else if (redValue < 50 && greenValue < 50 && blueValue < 50) {
    Serial.println(" - Black detected!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Black detected!");
} else if (redValue > greenValue && redValue > blueValue) {
    Serial.println(" - RED detected!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Red detected!");
} else if (blueValue > redValue && blueValue > greenValue) {
    Serial.println(" - BLUE detected!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Blue detected!");
} else if (greenValue > redValue && greenValue > blueValue) {
    Serial.println(" - GREEN detected!");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Green detected!");
} else {
    Serial.println(" - Unknown color!"); // Handling cases not covered
}


  
}
 
 
// Function to read Red Pulse Widths
int getRedPW() {
 
  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}
 
// Function to read Green Pulse Widths
int getGreenPW() {
 
  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}
 
// Function to read Blue Pulse Widths
int getBluePW() {
 
  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}