int startSensor = 54;
int numSensors = 16;

int startSensor2 = 3;
int numSensors2 = 1;

void setup() {
  Serial.begin(9600);  //скорость порта
  // put your setup code here, to run once:
  for (int i = startSensor; i <= startSensor + numSensors; i++)
    pinMode(i, INPUT);      // sets the digital pin as input
}


void loop() {
  boolean sensors[numSensors + numSensors2];
  for (int i = 0; i < numSensors + numSensors2; i++)
    sensors[i] = false;
  bool found = false;
  int timeRead = 0;
  //(digitalRead(A0));
  //  Serial.println("!"+String(A0)+"!");
  for (int i = startSensor; i < startSensor + numSensors; i++)
  {
    if (digitalRead(i))
    {
      Serial.println(String(i) + "active");
      found = true;
      sensors[i - startSensor] = true;
    }
  }

  for (int i = startSensor2; i < startSensor2 + numSensors2; i++)
  {
    if (digitalRead(i))
    {
      Serial.println(String(i+ numSensors) + "active");
      found = true;
      sensors[i - startSensor2 + numSensors] = true;
    }
  }
  if (found)
  {
    while (timeRead < 1000)
    {
      for (int i = startSensor; i <= startSensor + numSensors; i++)
        if (digitalRead(i))
          sensors[i - startSensor] = true;

      for (int i = startSensor2; i <= startSensor2 + numSensors2; i++)
        if (digitalRead(i))
          sensors[i - startSensor + numSensors] = true;

      timeRead += 100;
      delay(100);
    }
  }
  if (found)
  {
    String logData;
    for (int i = 0; i < numSensors; i++)
      if (sensors[i])
        logData += ' ' + String(i);
    Serial.println(logData);
    delay(2000);
  }
  else delay(100);
}
