#include <Wire.h>
#define uchar unsigned char     //line follower module 
uchar t;
uchar data[16];

int pwmRight = 11;             // pwmRightRight ports
int pwmLeft = 10;

int threshold = 90;         //value for when to turn

int rightForward = 6;
int rightBackward = 9;
int leftForward = 3;
int leftBackward = 5;       //variable names for each direction/wheel

void setup()
{
  Wire.begin();
  Serial.begin(9600);                        // Start serial monitor
  t = 0;

  pinMode(rightBackward, OUTPUT) ;        // We have to set pwmRightRight pin as output
  pinMode(leftBackward, OUTPUT) ;
  pinMode(rightForward, OUTPUT) ;
  pinMode(leftForward, OUTPUT) ;      // Logic pins are also set as output

  pinMode(pwmRight, OUTPUT);
  pinMode(pwmLeft, OUTPUT);           // pmw is output

}



void loop()
{

  Wire.requestFrom(9, 16);
  while (Wire.available())
  {
    data[t] = Wire.read();
    if (t < 15)
      t++;
    else
      t = 0;
  }                                          // line sensor data

  Serial.print("data[0]:");
  Serial.println(data[0]) ;
  Serial.print("data[14]:");
  Serial.println(data[14]);             //line sensor values

  linefollower();
}



void linefollower()
{
  if (data[14] > threshold && data[0] > threshold )      // if it senses white, turn slightly right
  {
    Serial.println("FOLLOW");
    digitalWrite(rightForward, HIGH) ;
    digitalWrite(leftForward, HIGH) ;
    digitalWrite(rightBackward, LOW) ;
    digitalWrite(leftBackward, LOW) ;
    analogWrite(pwmRight, 70) ; //160
    analogWrite(pwmLeft, 120) ; //220
    
  }

  if (data[14] < threshold && data[0] > threshold)     // turn left if left sensor finds line
  {
    Serial.println("Turn Left");
    digitalWrite(rightForward, HIGH) ;
    digitalWrite(leftForward, HIGH) ;
    digitalWrite(rightBackward, LOW) ;
    digitalWrite(leftBackward, LOW) ;
    analogWrite(pwmRight, 90); //150
    analogWrite(pwmLeft, 0);  //0

  }

//  if (data[14] < threshold && data[0] < threshold)  // stop if both sense black
//  {
//    Serial.println("STOP");
//
//    digitalWrite(rightForward, HIGH) ;
//    digitalWrite(leftForward, HIGH) ;
//    digitalWrite(rightBackward, LOW) ;
//    digitalWrite(leftBackward, LOW) ;
//    analogWrite(pwmRight, 0) ;
//    analogWrite(pwmLeft, 0) ;
//  }

}
