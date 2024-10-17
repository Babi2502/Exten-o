#include <AFMotor.h> // inclui a biblioteca Adafruit motor control
#include <Servo.h>//inclui a biblioteca serv

Servo servoSub; //cria objeto do tipo servo com nome servoSub
Servo servoFec;//cria objeto do tipo servo com nome servoFec

AF_DCMotor motorD(4);////cria objetps do tipo AF_DCMotor com nome motorD
AF_DCMotor motorE(1);//cria objetps do tipo AF_DCMotor com nome motorE
int trigPin = 36;//define triggPin como 36
int echoPin = 38;
// Determinação das portas a se utilizar para os sensores
float duration;
const int sD  = 34; //sensor centro direito
const int sE  = 30; //sensor centro esquerdo
const int sDP = 21; //sensor externo direito
const int sEP = 24; //sensor externo esquerdo
const int buzzer = 31;

// valores de posição do servo
const int garraLevantada = 130;
const int garraAbaixada = 50;
const int garraAberta = 100;
const int garraFechada = 30;

const int dist = 15; //distância para detecção

float soma, media;
int valD, valE, valDP, valEP;

void setup() {
  pinMode(buzzer, OUTPUT);
  servoSub.attach(10);
  servoFec.attach(9);
  servoSub.write(garraLevantada);
  servoFec.write(garraAberta);
  delay(2000);
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
  else{ */
  if(ultraMedia(15)<dist){
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    //peg
    parar();
    servoFec.write(garraAberta);
    delay(500);
    servoSub.write(garraAbaixada);
    delay(1000);
    movFrente();
    delay(500);
    parar();
    servoFec.write(garraFechada);
    delay(1000);
    servoSub.write(garraLevantada);
    delay(1000);
    while(!(digitalRead(sDP)&&digitalRead(sEP)&&digitalRead(sD)&&digitalRead(sE)))
    {
      if (!digitalRead(sE) && !digitalRead(sD) && !digitalRead(sDP) && !digitalRead(sEP)){
        movFrente();
      }     
      else if (!digitalRead(sE) && digitalRead(sD) && !digitalRead(sEP) && !digitalRead(sDP)){
        ajusteD();
      }
      else if (digitalRead(sE) && !digitalRead(sD) && !digitalRead(sEP) && !digitalRead(sDP)){
        ajusteE();
      }
      else if ((!digitalRead(sEP) && !digitalRead(sE) && digitalRead(sDP) && digitalRead(sD)) || (!digitalRead(sEP) && digitalRead(sE) && digitalRead(sDP) && digitalRead(sD))){ 
        parar();
      }
      else if ((!digitalRead(sDP) && !digitalRead(sD) && digitalRead(sEP) && digitalRead(sE)) || (!digitalRead(sDP) && digitalRead(sD) && digitalRead(sEP) && digitalRead(sE))){
        parar();
      }
    }
    else if(digitalRead(sE) && digitalRead(sEP) && digitalRead(sD) && digitalRead(sDP)){
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(50);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer,LOW);
      delay(100);
      digitalWrite(buzzer, HIGH);
      delay(150);
      digitalWrite(buzzer,LOW);
      parar();
      //devolver a lata
      delay(300);
      goback();
      delay(500);
      parar();
      delay(100);
      servoSub.write(garraAbaixada);
      delay(500);
      servoFec.write(garraAberta);
      delay(1000);
      servoSub.write(garraLevantada);
      while(true);
    }
  }
  else{
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
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer,LOW);
      movFrente();
      delay(250);
      parar();
      while(!digitalRead(sDP)){
      giro90E();
      }
      while(!digitalRead(sD)){
      giro90D();      
      }
      parar();
    }
    else if ((valD && valDP && !valE && !valEP) || (valD && valDP && valE && !valEP ) || (!valD && valDP && !valE && !valEP)){    
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer,LOW);
      movFrente();
      delay(250);
      parar();
      while(!digitalRead(sEP)){
      giro90D();
      }
      while(!digitalRead(sE)){
      giro90E();
      }
      
    }
}}
//}

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
void goback (){
  motorD.setSpeed(100);
  motorE.setSpeed(100);
  motorD.run(BACKWARD);
  motorE.run(BACKWARD);    
}
void ajusteE (){
  motorD.setSpeed(92);
  motorE.setSpeed(0);
  motorD.run(FORWARD);
  motorE.run(BACKWARD);    
}
void movFrente (){
  motorD.setSpeed(135);  
  motorE.setSpeed(112);
  motorD.run(FORWARD);
  motorE.run(FORWARD);
}
void giro90E (){
  motorD.setSpeed(92);
  motorE.setSpeed(92);
  motorE.run(BACKWARD);
  motorD.run(FORWARD);
  }
void giro90D (){
  motorD.setSpeed(92);  
  motorE.setSpeed(92);
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
