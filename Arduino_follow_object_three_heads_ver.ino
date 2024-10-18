#define trigPin1 7
#define echoPin1 8
#define trigPin2 2
#define echoPin2 3
#define trigPin3 11
#define echoPin3 12

#define motor1Pin1 4
#define motor1Pin2 5
#define motor2Pin1 9
#define motor2Pin2 10

// Distance Function
int getDistance(int trigPin, int echoPin) {
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}

void setup() {
  
  // Initializing pins

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int frontDist = getDistance(trigPin1, echoPin1);
  int leftDist = getDistance(trigPin2, echoPin2);
  int rightDist = getDistance(trigPin3, echoPin3);

  // Following Logic

  if (frontDist < 5) { // Move back if too close
    moveBackward();
  } else if (frontDist < leftDist && frontDist < rightDist && frontDist < 50) { // Move forward if object within certain range of front
    moveForward();
  } else if (leftDist < 50 && leftDist < rightDist) { // Turn left if object within range of left
    turnLeft();
  } else if (rightDist < 50) { // Turn right if object within range of right
    turnRight();
  } else {
    stopMoving();
  }
}


void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void stopMoving() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);  // Left motor backward
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);   // Right motor forward
}

void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);   // Left motor forward
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);  // Right motor backward
}
