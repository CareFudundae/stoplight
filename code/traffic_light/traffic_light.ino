int green_pin=7; //relay1
int yellow_pin=6;//relay2
int red_pin=5;   //relay3
int relay_pin=4; //relay4
int trig_pin=8;
int echo_pin=9;

//int loop_delay=20; //milliseconds
int relay_delay=10; //milliseconds
int warning_time=3;  //seconds
int caution_time=warning_time+10; //seconds

float distance;
float min_distance=6;//2;  //inches
float max_distance=48;//25; //inches

//int alert=0;
long cautionMillis=-10000;

void setup()
{
  Serial.begin(9600);
  pinMode(green_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);
  pinMode(trig_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
}

void loop()
{
  unsigned long currentMillis=millis();

  distance=sonic_ping();

  if (distance>min_distance && distance<max_distance)
  {
    Serial.print("ALERT");
    red();
    delay(warning_time*1000);
    cautionMillis=currentMillis;
  }

  else if (currentMillis-cautionMillis < (caution_time*1000))
  {
    Serial.print("caution");
    yellow();
  }    
  else
  {
    Serial.print("clear");
    green();
  }
  Serial.print("   ");
  Serial.print(currentMillis);
  Serial.print("   ");
  Serial.print(cautionMillis);
  Serial.println();




  

//  //check for someone/something in range
//  if (distance>min_distance && distance<max_distance)         //in range, go red
//  {
//    red();
//    Serial.print("ALERT");
//    alert=1;
//    delay(warning_time*1000);    
//  }
//  else if (alert>0 && alert<(caution_time*(1000/loop_delay))) //recently in range, yellow
//  {
//    yellow();
//    Serial.print("caution");
//    alert=alert+1;
//  }
//  else                                                        //clear, green
//  {
//    green();
//    Serial.print("clear");
//    alert=0;
//  }
//  Serial.print("   alert=");
//  Serial.print(alert);
//  Serial.println();
//  
//  delay(loop_delay);
}
int green(){
  LED_on(green_pin);
  delay(relay_delay);
  LED_off(yellow_pin);
  delay(relay_delay);
  LED_off(red_pin);
  delay(relay_delay);
}
int yellow(){
  LED_off(green_pin);
  delay(relay_delay);
  LED_on(yellow_pin);
  delay(relay_delay);
  LED_off(red_pin);
  delay(relay_delay);
}
int red(){
  LED_off(green_pin);
  delay(relay_delay);
  LED_off(yellow_pin);
  delay(relay_delay);
  LED_on(red_pin);
  delay(relay_delay);
}
int LED_on(int pin){
  digitalWrite(pin,HIGH);
}
int LED_off(int pin){
  digitalWrite(pin,LOW);
}

float sonic_ping(){
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:


  digitalWrite(trig_pin,LOW); //turn off trig pin
  delayMicroseconds(2); //short break
  digitalWrite(trig_pin,HIGH);
  delayMicroseconds(10); //pulse duration
  digitalWrite(trig_pin,LOW);

  float duration=pulseIn(echo_pin,HIGH);

  // convert the time into a distance
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  float dist = duration/74.0/2.0;
  //Serial.print(dist);
  //Serial.print(" in   ");
  ////Serial.println();
  return dist;
  
}
