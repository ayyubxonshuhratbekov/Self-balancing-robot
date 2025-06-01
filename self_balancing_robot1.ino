// C++ code
//
// --- PID constants --- you may need adjust these values based on the performance of your robot
float Kp = 10;
float Ki = 0.001;
float Kd = 20; 

// --- Variables ---
float setPoint = 765;  // Adjust based on upright sensor value
float input, error, previousError = 0;
float integral = 0;
float output;

// --- Motor 1 (Left) --- // your motor may not have this exact same order. Feel free (safely) order your motors.
int ENA = 10;
int IN1 = 5;
int IN2 = 7;

// --- Motor 2 (Right) ---
int ENB = 9;
int IN3 = 6;
int IN4 = 8;

// --- Sensor pin ---
int sensorPin = A0;

void setup() {
  Serial.begin(9600);
  
  // Motor 1
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Motor 2
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  input = analogRead(sensorPin); // read info from the analog sensor
  error = setPoint - input; // set the error to the difference between desired value and the sensor reading

  integral += error; // += is a short hand for integral = integral + error, meaning the accumulating error will be stored as integral
  float derivative = error - previousError; // derivative deals with the rate of the error
  output = Kp * error + Ki * integral + Kd * derivative; // this is the final result for driving the motor
  previousError = error; // in each loop renew the previousError based on the sensor readings

  moveMotors(output); // this is defined as new void function below
  delay(10);
}

void moveMotors(float speed) { // the output will be exucuted into here and adjust the speed of the motor accordingly. For instance, if the robot is leaning towards the ground, the motor will go backward or vice versa.
  speed = constrain(speed, -355, 355);
  Serial.println(error);

  if (speed > 0) {
    // Move backward
    digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    analogWrite(ENA, -speed);
    analogWrite(ENB, -speed);
  } else {
    // Move forward
    digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
  }
  
}