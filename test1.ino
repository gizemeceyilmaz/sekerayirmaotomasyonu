#include <Servo.h>
#include <Stepper.h>

#define STEPS_PER_OUTPUT_REVOLUTION 2048

#define S0 6
#define S1 7
#define S2 8
#define S3 9
#define OUT 10

#define Rpin 11
#define Bpin A1
#define Gpin A2

#define SERVO 12
Servo myservo;
Stepper stepper(32, 2, 3 , 4 , 5 );
int Steps2Take;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);

  myservo.attach(SERVO);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW );

  Serial.begin(9600);

  al_MM();

  pinMode(Rpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Bpin, OUTPUT);

}

void loop() {
 

  // Setting Red
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  int R = pulseIn(OUT, LOW);
  delay(200);

  // Setting Green
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  int G = pulseIn(OUT, LOW);
  delay(200);

  // Setting Blue
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  int B = pulseIn(OUT, LOW);
  delay(200);

  Serial.print("R= ");
  Serial.print(R );

  Serial.print(",G= " );
  Serial.print(G );

  Serial.print(",B= ");
  Serial.println(B );

  if (R < 60 && G < 60 && B < 60) {
    Serial.println("Unknown");
  }
  else if (R < G  ) {

    if (G > 100 && G > B) {
      Serial.println("Red");
      analogWrite(Rpin, 250);
 MoveServo(0);
    }
    else {
      Serial.println("Yellow");
      //analogWrite(Rpin, 115);
      //analogWrite(Gpin, 250);
      MoveServo(60);
    }
  }
  else {
    if (R > 100 && G - B > 20) {
      Serial.println("blue");
      analogWrite(Bpin, 250);
      MoveServo(120);
    }
    else if (R < 100 )
    {
      Serial.println("green");
      analogWrite(Gpin, 250);
      MoveServo(180);
    }
    else
      Serial.println("xxxxx");
  }

  delay(1000);
}

void MoveServo(int aci) {
  myservo.write(aci);
  delay(1000);
  al_MM();

}

void al_MM() {
  Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION / 4;
  stepper.setSpeed(500);
  stepper.step(Steps2Take);
  delay(2000);
}