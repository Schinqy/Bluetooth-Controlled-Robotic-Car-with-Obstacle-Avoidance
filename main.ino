//DC Motors will be controlled by an Android Application called Bluetooth RC Car (https://play.google.com/store/apps/details%3Fid%3Dbraulio.calle.bluetoothRCcontroller%26hl%3Den_US%26gl%3DUS&sa=U&ved=2ahUKEwjz0dDa8d72AhWuTDABHaqhDzcQFnoECAUQAg&usg=AOvVaw0TkDtiHC9b64huIKwZr69g)
//DC Motors will be connected to the Arduino Nano via L298N module. The motors will be controlled via the Bluetooth module (HC-06)
//The control character will be relayed to the Arduino via the Bluetooth module from the android app

char t;
int echo = 10;
int trig= 11;
int en1 =3; 
int en2 =5;
int m1p1 =2; //IN1
int m1p2 =4; //IN2
long distance, duration;
int buzzer=12;
void setup() {
pinMode(en1,OUTPUT);  
pinMode(en2,OUTPUT);  
pinMode(m1p1,OUTPUT);   
pinMode(m1p2,OUTPUT); 
pinMode(echo, INPUT);
pinMode(trig, OUTPUT);  
pinMode(buzzer, OUTPUT);  
Serial.begin(9600); 
}

void loop() {

//*******************************CALCULATE DISTANCE*******************************//
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  duration=pulseIn(echo, HIGH, 300000); 
  distance=duration/58.2;

 Serial.println(distance);
  //delay(10);

//*******************************CALCULATE DISTANCE END*******************************//

if(Serial.available()){
  Serial.setTimeout(100); //Decrease the lag by avoiding the serial buffer over-fill
  t = Serial.read();
  Serial.println(t);

if(t == 'F' && distance > 50){            //move forward(all motors rotate in forward direction) 
    analogWrite(en1, 150);
  analogWrite(en2, 150);
  digitalWrite(m1p1, LOW);
  digitalWrite(m1p2, LOW); // 
} 
else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
    digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  digitalWrite(m1p1,HIGH);
  digitalWrite(m1p2,HIGH);

}
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
   analogWrite(en1,0);
  analogWrite(en2,255);
  digitalWrite(m1p1,HIGH);
  digitalWrite(m1p2,LOW);
}

else if(t == 'L'){    //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
   analogWrite(en1,255);
  analogWrite(en2,0);
  digitalWrite(m1p1,LOW);
  digitalWrite(m1p2,HIGH);
} 

else if(t == 'S'){      //STOP (all motors stop)
 analogWrite(en1,0);
  analogWrite(en2,0);
  digitalWrite(m1p1,LOW);
  digitalWrite(m1p2,LOW);

}

if(distance < 50){    //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
   digitalWrite(buzzer, HIGH);
} 
else
{
  digitalWrite(buzzer, LOW);
}
}
}
