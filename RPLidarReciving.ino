#define m1c 33
#define m1a 11

#define m2c 31
#define m2a 10

#define m3c 29
#define m3a 9

#define m4c 27
#define m4a 8

#define target 270
#define maxSpeed 100

int maxSpd = 255, minSpd = 30, maxError2 = 800, minError2 = 0;
int totError2=0,targetError2=0;
#define forward LOW
#define backward HIGH
int poleDistance = 119;
int dirVal_1 = HIGH,dirVal_2 = LOW,dirVal_3 = LOW,dirVal_4 = HIGH;
int distance,alignPWM;

const int bufferSize = 64;
char buffer[bufferSize];

int error = 0, prevError = 0;
int kp = 10, kd = 0,Kp = 25;
int motorSpeed = 250;


void setup() {
  Serial.begin(9600);
  pinMode(m1c, OUTPUT);
  pinMode(m1a, OUTPUT);
  pinMode(m2c, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m3c, OUTPUT);
  pinMode(m3a, OUTPUT);
  pinMode(m4c, OUTPUT);
  pinMode(m4a, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int bytesRead = Serial.readBytesUntil('\n', buffer, bufferSize);

    // Process the received data
    if (bytesRead > 0) {
      buffer[bytesRead] = '\0'; // Null-terminate the string

      // Extract the angle and distance values
      char* angle_str = strtok(buffer, ",");
      char* distance_str = strtok(NULL, ",");

      // Convert the string values to float
      float angle = atof(angle_str);
      float distance = atof(distance_str);

      // Process the angle and distance values
      // ...
      Serial.println(angle);
      prevError = error;
      error = target - angle;
      if (abs(error) < 5)return;
      if (angle > 90 && angle < 270) {
        dirFor();
      }
      else {
        dirBack();
        if (angle < target) {
          error = 90 + angle;
        }
        else {
          error *= -1;
        }
      }

      int motorSpeed = kp * error + kd * (error -  prevError);
      motorSpeed = map(motorSpeed, 0, 90, 0, maxSpeed);
      motorMov();
      delay(100);
      poleAlign(poleDistance);

    }
  }
}
void dirBack() {
  digitalWrite(m1c, backward);
  digitalWrite(m2c, backward);
  digitalWrite(m3c, backward);
  digitalWrite(m4c, backward);
}
void dirFor() {
  digitalWrite(m1c, forward);
  digitalWrite(m2c, forward);
  digitalWrite(m3c, forward);
  digitalWrite(m4c, forward);
}
void motorMov() {
  analogWrite(m1a, motorSpeed);
  analogWrite(m2a, motorSpeed);
  analogWrite(m3a, motorSpeed);
  analogWrite(m4a, motorSpeed);
}
    
void poleAlign(int poleDistance) {

  while (!((poleDistance - distance) < 1 && (poleDistance - distance) > -1)) {
    // int diff = poleDistance - distance3;
   
    if (distance < poleDistance) {
      // Going Backwards
      dirVal_1 = LOW;
      dirVal_2 = HIGH;
      dirVal_3 = HIGH;
      dirVal_4 = LOW;
    }
    else {
      // Going Front
      dirVal_1 = HIGH;
      dirVal_2 = LOW;
      dirVal_3 = LOW;
      dirVal_4 = HIGH;
    }
    targetError2 = distance - poleDistance;
    totError2 = Kp * targetError2 ;
    alignPWM = map(totError2, Kp * maxError2 , minError2, maxSpd, minSpd);
    alignPWM = abs(alignPWM);
    if (targetError2 <= 1 && targetError2 >= -1 ) {
      alignPWM = 0;
    }
    else {
      alignPWM += 25;
    }
    analogWrite(m1a, alignPWM);
    digitalWrite(m1c, dirVal_1);
    analogWrite(m2a, alignPWM);
    digitalWrite(m2c, dirVal_2);
    analogWrite(m3a, alignPWM);
    digitalWrite(m3c, dirVal_3);
    analogWrite(m4a, alignPWM);
    digitalWrite(m4c, dirVal_4);
    
  }
  Serial.println(" Alignment Over");
}
