#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const int buzzerPin = 8;
const int motorPin = 9;
const int trigPin = 11;  
const int echoPin = 10; 
long duration;
float distance;  

//const int joyCPin = 8;  // Button for toggling motor on/off

Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool lastButtonState = HIGH;  // set the last button state as High
bool motorOn = false;  // Track whether the motor is on or off

void setup() {
  motorOn = false; //state the motor as off at the start
  
  pinMode(buzzerPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(trigPin, OUTPUT);    
  pinMode(echoPin, INPUT);
  Serial.begin(115200);

  lcd.init();  // turn the lcd on
  lcd.backlight();

  myservo.attach(9, 0, 180);  // attach the servo to pin 9 and set the angles to between 0 and 180
}

//void check();  // mention the check program 
void motor();

void loop() {
  //check();  // Check button press and toggle motor
  //Serial.println(motorOn); // serial print the state of the motor
  printd();
  buzzer();
  motor();
  
}


void printd() {
  Serial.print("Distance: ");
  Serial.println(dis());
  delay(100);
  
  if (dis() <= 20){  // if dis lower then or equal to 20 then lcd print a massage
    lcd.clear();
    lcd.print("DANGER!!!");
    delay(500);
  }
    // else print the distance as normal
  else { 
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.setCursor(0, 1);
    lcd.print(dis());
    delay(50);
  }
} 

float dis() {                                                                                                                                                                                                                             
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);  

  digitalWrite(trigPin, HIGH);  // send a wave for 10 micro seconds
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW); 

  duration = pulseIn(echoPin, HIGH); // set the duration as to when the echo recives the wave
  distance = (duration * 0.0343) / 2;  
  return distance; // return the distance
}

void motor() {
  myservo.write(2000);
  delay(1300);
  myservo.write(1000);
  delay(1100);
  myservo.write(1500);
  delay(500);


   
}
  
void buzzer(){
  if (dis() <= 20) {  
    tone(buzzerPin, 1000 ,100);
    }
}

