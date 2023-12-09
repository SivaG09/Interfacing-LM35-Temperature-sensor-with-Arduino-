#include <TimerOne.h>  //Required Header File for Using Timer functions

const int LM35_PIN = A0;   // Analog pin for LM35 temperature sensor
const int LED_PIN = 13;    // Onboard LED pin
int temperature = 0;    // Variable to store temperature reading
volatile unsigned long elapsedTime = 0;  //Assigning elapsed time = 0, Using Volatile keyword since the value may change unexpectedly 

void elapsedTimeFunc() {
  elapsedTime++;         //incrementing elaspsed time
}

void setup() {
  pinMode(13, OUTPUT);    // Set LED pin as output
  Timer1.initialize(1000); // Set the timer to trigger every 1 millisecond
  Timer1.attachInterrupt(elapsedTimeFunc);  //initiating interrupt routine
  Serial.begin(9600);    // Initialize serial communication
}

void loop() {
  int sensorValue = analogRead(LM35_PIN);    // Read analog value from LM35 sensor
  float voltage = sensorValue * (5.0 / 1023.0);    // Convert analog value to voltage
  float temperature = voltage* 100.0;    // Convert voltage to temperature in degrees Celsius
  Serial.print("Temperature: ");           //printing temperatur statement
  Serial.print(temperature,2);    // Print temperature with 2 decimal points
  Serial.println(" °C");          //printing the °C

  //Checking temperature < 30 or not
  if (temperature < 30) {
    
        digitalWrite(LED_PIN,HIGH);  //setting Led high ON
        my_Delay(250); // Delay for 250 milliseconds
        digitalWrite(LED_PIN,LOW);   //setting led OFF
        my_Delay(250); // Delay for 250 milliseconds

  }
  //Checking temperature > 30 or not
  else if (temperature > 30) {
        digitalWrite(LED_PIN,HIGH); //setting Led high ON
        my_Delay(500); // Delay for 500 milliseconds
        digitalWrite(LED_PIN,LOW); //setting led OFF
        my_Delay(500); // Delay for 500 milliseconds
  }
}

//defning function my_Delay
void my_Delay(unsigned long delayMs) {
  unsigned long startTime = elapsedTime; // Store the current elapsedTime
  
  while ((elapsedTime - startTime) < delayMs) {
    // Do nothing and continue to check for the elapsed time
  }
}