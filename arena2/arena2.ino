#include <AFMotor.h>
#include <Servo.h>

Servo servoSub;
Servo servoFec;

AF_DCMotor motorD(4);
AF_DCMotor motorE(1);
int trigPin = 36;
int echoPin = 38;
// Determinação das portas a se utilizar para os sensores
float duration;
const int sD  = 34;
const int sE  = 30;
const int sDP = 21;
const int sEP = 24;
const int buzzer = 31;
float soma, media;
int valD, valE, valDP, valEP;

void setup() {
  pinMode(buzzer, OUTPUT);
  servoSub.attach(22);
  servoFec.attach(23);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(sD, INPUT);
  pinMode(sE, INPUT);
  pinMode(sDP, INPUT);
  motorD.setSpeed(200);
  motorD.run(RELEASE);
  motorE.setSpeed(200);
  motorE.run(RELEASE);
  Serial.begin(9600);
}

void loop() {
  soma=0;
  media=0;     
  valD  = digitalRead(sD);
  valE  = digitalRead(sE);
  valEP = digitalRead(sEP);
  valDP = digitalRead(sDP);
 /*if (ultraMedia(10, 36, 38)<=4){
    for (int pos=60; pos>=0; pos--) { 
      servoFec.write(pos);            
      delay(15);                      
    }
    for (int pos=0; pos<=90; pos++){
       servoSub.write(pos);
       delay(15);     
    }
    
    } 
*/
  if (!valE && !valD && !valDP && !valEP){
    movFrente();
  }     
  else if (!valE && valD && !valEP && !valDP){
    ajusteD();
  }
  else if (valE && !valD && !valEP && !valDP){
    ajusteE();
  }
  else if ((valE && valEP && !valDP && !valD) || (valE && valEP && valD && !valDP || (!valE && valEP && !valD && !valDP))){    
    parar();
    delay(200);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    movFrente();
    delay(350);
    parar();    
    if(digitalRead(sE) && digitalRead(sD) && digitalRead(sDP) && digitalRead(sEP)){
      movFrente();
      delay(1000);
      
      parar();
      
      delay(100);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer,LOW);
      while(1);
    }
    else{
    while(!digitalRead(sDP)){
    giro90E();
    }
    while(!digitalRead(sD)){
    giro90D();      
    }
    parar();
  }}
  else if ((valD && valDP && !valE && !valEP) || (valD && valDP && valE && !valEP ) || (!valD && valDP && !valE && !valEP)){    
    parar();
    delay(200);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    movFrente();
    delay(350);
    parar();
    if(digitalRead(sE) && digitalRead(sD) && digitalRead(sDP) && digitalRead(sEP)){
      movFrente();
      delay(1000);
      parar();
      delay(100);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer,LOW);
      
      while(1);
    }
    else{
    while(!digitalRead(sEP)){
    giro90D();
    }
    while(!digitalRead(sE)){
    giro90E();
    }
    parar();
  }}
}

void ajusteD (){
  
  motorD.setSpeed(0);  
  motorE.setSpeed(85);
  motorD.run(BACKWARD);
  motorE.run(FORWARD);
  /*  analogWrite  (pwmA, 80);
  analogWrite  (pwmB, 80);
  digitalWrite (inA1, HIGH);
  digitalWrite (inA2, LOW);
  digitalWrite (inB1, LOW);
  digitalWrite (inB2, HIGH);
*/
}
void ajusteE (){
  motorD.setSpeed(92);
  motorE.setSpeed(0);
  motorD.run(FORWARD);
  motorE.run(BACKWARD);    
}
void movFrente (){
  motorD.setSpeed(110);  
  motorE.setSpeed(95);
  motorD.run(FORWARD);
  motorE.run(FORWARD);
}
void giro90E (){
  motorD.setSpeed(95);
  motorE.setSpeed(95);
  motorE.run(BACKWARD);
  motorD.run(FORWARD);
  }
void giro90D (){
  motorD.setSpeed(95);  
  motorE.setSpeed(95);
  motorE.run(FORWARD);
  motorD.run(BACKWARD);
  }
void parar (){
  motorE.setSpeed(200);
  motorD.setSpeed(200);
  motorE.run(RELEASE);
  motorD.run(RELEASE);
}

float ultraMedia(int vezes){
  for (int i=0;i<vezes;i++){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    int distance = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
   // Serial.print("Distance: ");
   // Serial.println(distance);
    soma=soma+distance;
  }
  media=soma/vezes;
  return media;
  
}
