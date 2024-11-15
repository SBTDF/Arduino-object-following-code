#define trigPin 7
#define echoPin 8
#define IR_Left 2
#define IR_Right 3

#define motor1Pin1 4
#define motor1Pin2 5
#define motor2Pin1 9
#define motor2Pin2 10

#define MAX_DISTANCE 400  // Maximum measurable distance of the ultrasonic sensor

// Distance Function
int getDistance() {
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Cap distance to max measurable distance
  if (distance > MAX_DISTANCE) {
    distance = MAX_DISTANCE;
  }
  
  return distance;
}

void setup() {
  
  // Initializing pins

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IR_Left, INPUT);
  pinMode(IR_Right, INPUT);
  
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  Serial.begin(9600);
}

void moveForward() {
  // Serial.println("Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void moveBackward() {
  // Serial.println("Backward");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void stopMoving() {
  // Serial.println("Stop");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void turnLeft() {
  // Serial.println("Left");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);  // Left motor backward
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);   // Right motor forward
}

void turnRight() {
  // Serial.println("Right");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);   // Left motor forward
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);  // Right motor backward
}

void loop() {
  int frontDist = getDistance();
  int leftRead = digitalRead(IR_Left);
  int rightRead = digitalRead(IR_Right);

  // Following Logic

  if (leftRead == 0 && rightRead == 1) { // Turn left if object within range of left
    turnLeft();
  } else if (leftRead == 1 && rightRead == 0) { // Turn right if object within range of right
    turnRight();
  } else if (frontDist < 5) { // Move back if too close
    moveBackward();
  } else if ((leftRead == 0 && rightRead == 0) || frontDist < 50) { // Move forward if object within certain range of front
    moveForward();
  } else {
    stopMoving();
  }
    
  delay(50); // Small delay between sensor readings to avoid interference
    
}