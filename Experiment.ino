const int trigPin = 9; //sets trig on the ultrasonic sensor to pin 9
const int echoPin = 10; //sets echo on the ultrasonic sensor to pin 10
const int buzzerPin = 8; //sets the active buzzer to pin 8
const int buttonPin = 11; //sets the button to pin 11
const int rLEDa = 2; //sets red LED a to pin 2
const int rLEDb = 3; //sets red LED b to pin 3
const int rLEDc = 4; //sets red LED c to pin 4
const int gLEDa = 5; //sets green LED a to pin 5
const int gLEDb = 6; //sets green LED b to pin 6
const int bLEDa = 7; //sets blue LED a to pin 7

bool systemOn = false; //tracks whether the system is ON or OFF
bool lastButtonState = HIGH; //stores the previous button state

void setup() { //the setup funtion
  pinMode(trigPin, OUTPUT); //sets trig on the ultrasonic sensor to an output
  pinMode(echoPin, INPUT); //sets echo on the ultrasonic sensor to an input
  pinMode(buzzerPin, OUTPUT); //sets the buzzer to an output
  pinMode(buttonPin, INPUT); //sets the button to an input but with an internal pull-up resistor

  pinMode(rLEDa, OUTPUT); //sets red LED a to an output
  pinMode(rLEDb, OUTPUT); //sets red LED b to an output
  pinMode(rLEDc, OUTPUT); //sets red LED c to an output
  pinMode(gLEDa, OUTPUT); //sets green LED a to an output
  pinMode(gLEDb, OUTPUT); //sets green LED b to an output
  pinMode(bLEDa, OUTPUT); //sets blue LED a to an output
  Serial.begin(9600); //allows the serial monitor to run at 9600 bits
}

void loop() { //the loop function
  long duration; //makes the duration variable
  int distance; //makes the distance variable

  bool currentButtonState = digitalRead(buttonPin); //reads the current button state

  if (lastButtonState == HIGH && currentButtonState == LOW) { //detects if button was pressed (falling edge)
    systemOn = !systemOn; //toggles the system state
    Serial.println(systemOn); //prints system state to serial monitor
    delay(50); //adds a small delay to prevent button bounce
  }

  lastButtonState = currentButtonState; //updates the lastButtonState

  if(systemOn == false) { //what happens if the system is OFF
    digitalWrite(bLEDa, HIGH); //turns blue LED a on
    noTone(buzzerPin); //turns the buzzer off
    digitalWrite(rLEDa, LOW); //turns red LED a off
    digitalWrite(rLEDb, LOW); //turns red LED b off
    digitalWrite(rLEDc, LOW); //turns red LED c off
    digitalWrite(gLEDa, LOW); //turns green LED a off
    digitalWrite(gLEDb, LOW); //turns green LED b off
  } else { //what happens if the system is ON
    digitalWrite(bLEDa, LOW); //turns blue LED a off
    digitalWrite(trigPin, LOW); //turns the trig on ultrasonic sensor off
    delayMicroseconds(2); //waits 2 microseconds
    digitalWrite(trigPin, HIGH); //turns the trig on ultrasonic sensor on
    delayMicroseconds(10); //waits 10 microseconds
    digitalWrite(trigPin, LOW); //turns the trig on ultrasonic sensor off

    duration = pulseIn(echoPin, HIGH); //detects the duration of the pulse from the ultrasonic sensor
    distance = duration * 0.034 / 2; //calculates the distance based on the pulse duration

    if(distance < 5) { //if ultrasonic sensor detects something within 5cm
      digitalWrite(gLEDa, LOW); //turns green LED a off
      digitalWrite(gLEDb, LOW); //turns green LED b off
      tone(buzzerPin, 50); //sets the buzzer tone to 50Hz
      digitalWrite(rLEDa, HIGH); //turns red LED a on
      digitalWrite(rLEDb, HIGH); //turns red LED b on
      digitalWrite(rLEDc, HIGH); //turns red LED c on
      delay(400); //waits 0.4 seconds
      noTone(buzzerPin); //turns the buzzer off
      digitalWrite(rLEDa, LOW); //turns red LED a off
      digitalWrite(rLEDb, LOW); //turns red LED b off
      digitalWrite(rLEDc, LOW); //turns red LED c off
      delay(400); //waits 0.4 seconds
      tone(buzzerPin, 80); //sets the buzzer tone to 80Hz
      digitalWrite(rLEDa, HIGH); //turns red LED a on
      digitalWrite(rLEDb, HIGH); //turns red LED b on
      digitalWrite(rLEDc, HIGH); //turns red LED c on
      delay(400); //waits 0.4 seconds
      noTone(buzzerPin); //turns the buzzer off
      digitalWrite(rLEDa, LOW); //turns red LED a off
      digitalWrite(rLEDb, LOW); //turns red LED b off
      digitalWrite(rLEDc, LOW); //turns red LED c off
      delay(400); //waits 0.4 seconds
    } else { //if the ultrasonic sensor doesn't detect anything
      digitalWrite(gLEDa, HIGH); //turns green LED a on
      digitalWrite(gLEDb, HIGH); //turns green LED b on
      noTone(buzzerPin); //turns the buzzer off
      digitalWrite(rLEDa, LOW); //turns red LED a off
      digitalWrite(rLEDb, LOW); //turns red LED b off
      digitalWrite(rLEDc, LOW); //turns red LED c off
    }

    delay(200); //waits 0.2 seconds
  }
}
