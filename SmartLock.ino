char karakter;
String cmd = "";

int kontak = 9;
int securerelay = 10;
int starter = 11;
int klakson = 12;
int rem = 13;
int sensorkontak = 4;
int sensorrahasia = 5;
int valsensorkontak;
int valsensorrahasia;
int securestate;
int buzzstate;
unsigned long timekontakon;

void setup() 
{
  Serial.begin(9600);
  pinMode(securerelay,OUTPUT);
  pinMode(kontak,OUTPUT);
  pinMode(starter,OUTPUT);
  pinMode(klakson,OUTPUT);
  pinMode(rem,OUTPUT);
  pinMode(sensorkontak,INPUT);
  pinMode(sensorrahasia,INPUT);
}

void loop() 
{
  cekcmd();
  
  valsensorkontak = digitalRead(sensorkontak);
  valsensorrahasia = digitalRead(sensorrahasia);
  
  if(valsensorrahasia==HIGH)
  {
    if (valsensorkontak==LOW)
    {
      sensorrahasiaoff();
    }
    else
    {
      sensorrahasiaon();
    }
  }
  
  if(valsensorkontak==LOW)
  {
    sensorrahasiaoff();
  }
  else
  {
    if (securestate == 0)
    {
      if(timekontakon <= 10000)
      {
        timekontakon++;
      }
      else
      {
        buzzstate = 1;
      }
    }
    else
    {
      buzzstate = 0;
      timekontakon = 0;
    }
  }
  
  if(buzzstate==1)
  {
    buzz();
  }
  
  delay(1);
}

void cekcmd()
{
  if(Serial.available())
  {
    karakter = (char)Serial.read();
    if(karakter != '\n')
    {
      cmd += karakter;
    }
    else
    {
      if(cmd=="on")
      {
        digitalWrite(kontak,HIGH);
        sensorrahasiaon();
        cmd = "";
        Serial.println(" Kontak ON");
        delay(1000);
      }
      else if(cmd=="off")
      {
        digitalWrite(kontak,LOW);
        sensorrahasiaoff();
        cmd = "";
        Serial.println(" Mesin dan Kontak OFF");
        delay(1000);
      }
      else if(cmd=="cut")
      {
        digitalWrite(kontak,LOW);
        sensorrahasiaoff();
        buzzstate = 1;
        cmd = "";
        Serial.println(" Mesin OFF, Alaram ON");
        delay(1000);
      }
      else if(cmd=="bel")
      {
        Serial.println(" Bel ON");
        bel();
        cmd = "";
      }
      else if(cmd=="start")
      {
        Serial.println(" Menghidupkan Mesin");
        start();
        cmd = "";
      }
    }
  }
}

void sensorrahasiaon()
{
  securestate = 1;
  digitalWrite(securerelay,HIGH);
}

void sensorrahasiaoff()
{
  securestate = 0;
  digitalWrite(securerelay,LOW);
}

void start()
{
  digitalWrite(rem,HIGH);
  delay(500);
  digitalWrite(starter,HIGH);
  delay(1000);
  digitalWrite(starter,LOW);
  delay(500);
  digitalWrite(rem,LOW);
}

void bel()
{
  digitalWrite(klakson,HIGH);
  digitalWrite(rem,HIGH);
  delay(500);
  digitalWrite(klakson,LOW);
  digitalWrite(rem,LOW);
  delay(500);
  digitalWrite(klakson,HIGH);
  digitalWrite(rem,HIGH);
  delay(500);
  digitalWrite(klakson,LOW);
  digitalWrite(rem,LOW);
  delay(500);
}
void buzz()
{
  digitalWrite(klakson,HIGH);
  digitalWrite(rem,HIGH);
  delay(500);
  digitalWrite(klakson,LOW);
  digitalWrite(rem,LOW);
  delay(500);
}
