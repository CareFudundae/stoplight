int green_pin=7; //relay1
int yellow_pin=6;//relay2
int red_pin=5;   //relay3
int relay_pin=4; //relay4
int PIR_pin=2;

int loop_delay=10; //milliseconds
int relay_delay=10; //milliseconds
int warning_time=1;  //seconds
int caution_time=warning_time+7; //seconds

float distance;
float min_distance=2;  //inches
float max_distance=80;//25; //inches

long cautionMillis=-10000;
bool already_green=false;
bool already_yellow=false;
bool PIR_status;

void setup()
{
  Serial.begin(9600);
  pinMode(green_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  pinMode(red_pin, OUTPUT);
  pinMode(PIR_pin, INPUT);
}

void loop()
{  
//  delay(loop_delay);
  unsigned long currentMillis=millis();
  PIR_status=PIR_sense(PIR_pin);
  
  if (PIR_status==HIGH) //if someone present, go red
  {
    Serial.print("ALERT, run red");  
    Serial.println();
    already_green=false;
    already_yellow=false;
    red();
//    delay(warning_time*1000);
    cautionMillis=currentMillis;
  }
  else //if no one present, go yellow for a while, then green
  {
    if (currentMillis-cautionMillis < (caution_time*1000)) //if within caution time, go yellow
    {
      already_green=false;
    
      if (already_yellow==false)
      {
        Serial.print("caution, run yellow");  
        Serial.println();
        yellow();
        already_yellow=true;
      }
    }
    else //if past caution time, go yellow
    {
      already_yellow=false;
      if (already_green==false)
      {
        Serial.print("clear, run green");  
        Serial.println();
        green();
        already_green=true;
      }
    }
  }


  
//  {
////    Serial.print("caution");
//    already_green=false;
//    
//    if (already_yellow==false)
//    {
//      Serial.println();
//      Serial.print("caution, run yellow");
//      Serial.println();
//      yellow();
//      already_yellow=true;
//    }
//  }    
//  else
//  {
////    Serial.print("clear");
//    already_yellow=false;
//    if (already_green==false)
//    {
//      Serial.println();
//      Serial.print("clear, run green");
//      Serial.println();
//      green();
//      already_green=true;
//    }
//  }
//  Serial.print("   ");
//  Serial.print(currentMillis);
//  Serial.print("   ");
//  Serial.print(cautionMillis);
//  Serial.println();
//delay(loop_delay);
//  }
}


int green(){
  LED_on(green_pin);
  LED_off(yellow_pin);
  LED_off(red_pin);
  delay(relay_delay);
}
int yellow(){
  LED_off(green_pin);
  LED_on(yellow_pin);
  LED_off(red_pin);
  delay(relay_delay);
}
int red(){
  LED_off(green_pin);
  LED_off(yellow_pin);
  LED_on(red_pin);
  delay(relay_delay);
}
int LED_on(int pin){
  digitalWrite(pin,HIGH);
}
int LED_off(int pin){
  digitalWrite(pin,LOW);
}
bool PIR_sense(int pin){
  int PIR_;
  PIR_=digitalRead(pin);
  return PIR_;
}
