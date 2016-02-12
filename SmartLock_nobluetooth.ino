int securerelay = 10;
int relayampli = 11;
int klakson = 12;
int sensorkontak = 4;
int sensorrahasia = 5;
int hp = A0;
int valsensorkontak;
int valsensorrahasia;
int securestate;
int buzzstate;
int hiject = 0;
unsigned long timekontakon;

void setup() 
{
  pinMode(securerelay,OUTPUT);
  pinMode(relayampli,OUTPUT);
  pinMode(klakson,OUTPUT);
  pinMode(sensorkontak,INPUT);
  pinMode(sensorrahasia,INPUT_PULLUP);
  
  //digitalWrite(securerelay,HIGH);
  //digitalWrite(relayampli,HIGH);
  //digitalWrite(klakson,HIGH);
  
  delay(5000);
}

void loop() 
{
  valsensorkontak = digitalRead(sensorkontak);
  
  readsensorrahasia();
  readhp();
  
  if(hiject == 0) //jika tidak hiject
  {
    if(valsensorkontak==LOW && valsensorrahasia==HIGH)
    {
      sensorrahasiaoff();
    }
  
    if(valsensorkontak==HIGH && valsensorrahasia==HIGH)
    {
      sensorrahasiaon();
    }
  
    if(valsensorkontak==HIGH)
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
        digitalWrite(securerelay,HIGH);//secure relay hidup
        digitalWrite(relayampli,LOW);//relay ampli mati
      }
    }
    else //jika kontak off 
    {
      sensorrahasiaoff();
    }
  }
  else //jika hiject = 1
  {
    digitalWrite(securerelay,LOW);//secure relay mati
    digitalWrite(relayampli,HIGH);//relay ampli hidup
    buzzstate=1;
  }
  
  if(buzzstate==1)
  {
    buzz();
  }
  
  delay(1);
}

void readsensorrahasia()
{
  valsensorrahasia = digitalRead(sensorrahasia);
  if (valsensorrahasia==LOW)
  {
    valsensorrahasia = HIGH;
    hiject = 0;
  }
  else
  {
    valsensorrahasia = LOW;
  }
}

void readhp()
{
  if(analogRead(hp)>10)
  {
    hiject = 1;
  }
}

void sensorrahasiaon()
{
  securestate = 1;
  digitalWrite(securerelay,HIGH);//secure relay hidup
}

void sensorrahasiaoff()
{
  securestate = 0;
  digitalWrite(securerelay,LOW);//secure relay mati
}

void buzz()
{
  digitalWrite(klakson,HIGH);
  delay(250);
  digitalWrite(klakson,LOW);
  delay(750);
}
