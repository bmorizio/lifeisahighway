#include <Wire.h>
#define uchar unsigned char     //line follower module 
uchar t;
uchar data[16];

int pwmRight = 11;             // pwmRightRight ports
int pwmLeft = 10;

int threshold = 69;         //value for when to turn
int a = 0;
int rightForward = 6;
int rightBackward = 9;
int leftForward = 3;
int leftBackward = 5;       //variable names for each direction/wheel

const int trigPin = 12;       // trig in port 12
const int echoPin = 13;      // echo in 13

long duration;
int distance;            // variables to calculate ultra values 


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

  pinMode(trigPin, OUTPUT);      // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);      // Sets the echoPin as an Input

}

void loop()
{
    digitalWrite(trigPin, LOW);    // Clears the trigPin
    delayMicroseconds(2);         // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);    // Reads the echoPin, returns the sound wave travel time in microseconds

    duration = pulseIn(echoPin, HIGH);     // Calculating the distance
    distance = duration * 0.034 / 2;

    Serial.print("Distance: ");         //Prints the ultrasonic distance
    Serial.println(distance);


    
  
  if (a == 0)                             //Always true; this always runs
  {
    serialmonitor();
  }
  
  if (distance >= 20)               //if nothing inthe way, run linefollower f(x)
  {
    linefollower();
  }
  
  if (distance < 20 && distance >= 10) 
  {
    careful();             //if something is in way, run ultra
  }

//  if (distance < 10 && distance >= 5)
//  {
//    reallycareful();
//  }

  if (distance < 10)
  {
    halt();
  }

  
  
}

void serialmonitor()
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

  Serial.print("data[2]:");
  Serial.println(data[2]) ; 
  Serial.print("data[14]:");
  Serial.println(data[14]);             //line sensor values


//  digitalWrite(trigPin, LOW);        // Clears the trigPin
//  delayMicroseconds(2);             // Sets the trigPin on HIGH state for 10 micro seconds
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);              // Reads the echoPin, returns the sound wave travel time in microseconds
//  duration = pulseIn(echoPin, HIGH);     // Calculating the distance
//  distance = duration * 0.034 / 2;


}


void linefollower()
{
  if (data[14] > threshold && data[2] > 80 )      // if it senses white, turn slightly right
  {
    Serial.println("FOLLOW");
    digitalWrite(rightForward, HIGH) ;
    digitalWrite(leftForward, HIGH) ;
    digitalWrite(rightBackward, LOW) ;
    digitalWrite(leftBackward, LOW) ;
    analogWrite(pwmRight, 140) ; 
    analogWrite(pwmLeft, 170) ; 
  }

  if (data[14] < threshold && data[2] > 80 )      // if it senses white, turn slightly right
  {
    Serial.println("TurnOut");
    digitalWrite(rightForward, HIGH) ;
    digitalWrite(leftForward, HIGH) ;
    digitalWrite(rightBackward, LOW) ;
    digitalWrite(leftBackward, LOW) ;
    analogWrite(pwmRight, 130) ; 
    analogWrite(pwmLeft, 0) ;
  }

}



void careful()
{
 Serial.println("careful");
  
if (data[14] > threshold && data[2] > threshold )      // if it senses white, turn slightly right
{

    digitalWrite(rightForward, HIGH) ; 
    digitalWrite(leftForward, HIGH) ;
    digitalWrite(rightBackward, LOW) ;
    digitalWrite(leftBackward, LOW) ;
    analogWrite(pwmRight, 70) ;
    analogWrite(pwmLeft, 120) ;
  }

  if (data[14] < threshold && data[2] > threshold)     // turn left if left sensor finds line
  {

    digitalWrite(rightForward, HIGH) ;
    digitalWrite(leftForward, HIGH) ;
    digitalWrite(rightBackward, LOW) ;
    digitalWrite(leftBackward, LOW) ;
    analogWrite(pwmRight, 90);
    analogWrite(pwmLeft, 0); 
  }

}

//void reallycareful()
//{
//     Serial.println("reallycareful");
//    
//  if (data[14] > threshold && data[2] > 80 )      // if it senses white, turn slightly right
//  {
//
//    digitalWrite(rightForward, HIGH) ;
//    digitalWrite(leftForward, HIGH) ;
//    digitalWrite(rightBackward, LOW) ;
//    digitalWrite(leftBackward, LOW) ;
//    analogWrite(pwmRight, 70) ;
//    analogWrite(pwmLeft, 120) ;
//  }
//
//  if (data[14] < threshold && data[2] > 80)     // turn left if left sensor finds line
//  {
//
//    digitalWrite(rightForward, HIGH) ;
//    digitalWrite(leftForward, HIGH) ;
//    digitalWrite(rightBackward, LOW) ;
//    digitalWrite(leftBackward, LOW) ;
//    analogWrite(pwmRight, 90);
//    analogWrite(pwmLeft, 0); 
//  }
//}

void halt()
{
 Serial.println("halt");

    digitalWrite(rightForward, HIGH) ;
    digitalWrite(leftForward, HIGH) ;
    digitalWrite(rightBackward, LOW) ;
    digitalWrite(leftBackward, LOW) ;
    analogWrite(pwmRight, 0) ;
    analogWrite(pwmLeft, 0) ;
}
