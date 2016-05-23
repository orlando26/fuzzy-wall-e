
#include <Wire.h>
#include "ArduinoNunchuk.h"
#include "WiiChuck.h"
#include <Servo.h>


ArduinoNunchuk nunchuk = ArduinoNunchuk();
WiiChuck chuck = WiiChuck();
Servo llantas;
Servo martillo;
const int EN = 6;
const int MC1 = 2;
const int MC2 = 3;

int val = 0;
int velocity = 0;
int girar = 0;


void setup()
{
  Serial.begin(9600);
  chuck.begin();
  nunchuk.init();
  pinMode(EN, OUTPUT);
  pinMode(MC1,OUTPUT);
  pinMode(MC2, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  llantas.attach(11);
  martillo.attach(5);
  brake();
}
void loop(){
  nunchuk.update();
  chuck.update();
  val = nunchuk.analogY;
  
 girar = constrain(chuck.readAccelX(), -150, 150);
 int f=chuck.readAccelY();
  f=constrain(chuck.readAccelY(), -139, 180);
  f=map(f,-139,180,0,90);
  if (nunchuk.cButton == 1){
  martillo.write(f);
  }else{
 if(girar == -150){
    llantas.write(137);
  }else if(girar == 150){
    llantas.write(70);
  }else{
    llantas.write(106);
  }
  }
  //Serial.print(chuck.readAccelY());
  
  //Serial.print("      ");
  
  Serial.println(f);
  
  if (val > 134){
    velocity = map(val, 134, 255, 0, 255);
    paDelante(velocity);
    //llantas.write(0);
  }else if(val < 132){
    velocity = map(val, 132, 0, 0, 255);
    paAtras(velocity);
    //llantas.write(180);
  }else{
    brake();
    //llantas.write(90);
  }
  
  //Serial.println(girar);
 
}
void paDelante(int rate){
  digitalWrite(EN, LOW);
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  analogWrite(EN, rate);
  digitalWrite(8, HIGH);
  digitalWrite(12, LOW);
}
void paAtras(int rate){
  digitalWrite(EN, LOW);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, HIGH);
  analogWrite(EN, rate);
  digitalWrite(12, HIGH);
  digitalWrite(8, LOW);
}
void brake(){
  digitalWrite(EN, LOW);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, LOW);
  digitalWrite(EN, LOW);
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
}
