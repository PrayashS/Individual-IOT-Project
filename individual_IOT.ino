#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
char auth[] = "LdeCoXDElcsjmqpFBxOanc2yKL9Jrst_"; // Blynk Authenication code
char ssid[] = "vaak"; //Name of Wi-Fi
char pass[] = "123456789"; //Password of Wi-Fi
int buzzer = D4; //Buzzer is connected with D4
int n; ?? Declaring variable for notification

void setup()
{
  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(16,OUTPUT);
  pinMode(5,OUTPUT);
  timer.setInterval(1000L, sendUptime);
}

void sendUptime()
{
  Blynk.virtualWrite(V1, n); //Setting virtual pin V1 at blynk for notification
}

void loop()
{
  Blynk.run();  // Initiates Blynk
  timer.run();  // Initiates simple timer
  
  n=analogRead(A0); //Reads the value from A0 pin
  Serial.println(n);
  
  if(n>300) //Checks threshold value
  {
      tone(buzzer, 500,500); //Buzzer starts to buzz
   Blynk.notify("Alert: Gas leakage detected"); 
    digitalWrite(16,LOW);  //D0 White led doesnot glow
    digitalWrite(5,HIGH);  //D1 Green led glows
    delay(2000);  
  }
  
  if(n<300) //Checks threshold value
  {
      digitalWrite(16,HIGH); //D0 White led glows
      digitalWrite(5,LOW); //D1 Green led does not glow
      delay(2000);   
  }}
