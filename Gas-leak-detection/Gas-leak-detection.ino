#include <Blynk.h>

#define BLYNK_TEMPLATE_ID "TMPL3RGN8ZA0b"
#define BLYNK_TEMPLATE_NAME "Gas detection"
#define BLYNK_AUTH_TOKEN "YH4C1J1AguJU7wI7x2L6Ii8-kS8tQ0Ap"
#define BLYNK_PRINT Serial

#define Rled D1
#define Iled D3
#define Gled D2
#define buzzer D5

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer;

int trig = 250;
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Shoumo";  // wifi name
char pass[] = "shoumo@2g";  // wifi password

int smokeA0 = A0;
int data = 0;


void sendSensor()
{

 int data = analogRead(smokeA0);
 Blynk.virtualWrite(V0, data);
  Serial.print("Pin A0: ");
  Serial.println(data);

  digitalWrite(Iled,LOW);
  delay(1500);
  digitalWrite(Iled,HIGH);

  if(data > trig) // If smoke detected
  {
   
    Blynk.logEvent("gas_alert","Gas Leakage Detected");
    Serial.print(" \n Smoke detected!  ");
    digitalWrite(buzzer,HIGH);     //Buzzer is turned on
    digitalWrite(Rled,HIGH);       //Red LED is on
    digitalWrite(Gled,LOW);        //Green Led is off
    
  }

    else                  // If no smoke is deteced
  {
     Serial.print(" \n Smoke  not detected!  ");   
     digitalWrite(buzzer,LOW);      //Buzzer is turned off
     digitalWrite(Rled,LOW);        //Red LED is off
     digitalWrite(Gled,HIGH);       //Green LED is ON
  
  } 
}

void setup()
{
  //pin mode
  pinMode(smokeA0, INPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(Rled, OUTPUT);
  pinMode(Gled, OUTPUT);
  pinMode(Iled, OUTPUT);
  
  digitalWrite(Iled,HIGH);

  
  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

 
  
  //dht.begin();
  timer.setInterval(250L, sendSensor);//send sensor function call
  
}

void loop()
{
  Blynk.run();
  timer.run();
  
}