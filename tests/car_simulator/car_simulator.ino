const unsigned long PULSES_PER_KM = 4971;

const int speedOutPin = 2;
const int rpmOutPin = 3;

unsigned long previousSpeedTime = 0;
unsigned long speedDelayMicroSeconds = 10 * 1000000;

void setup()
{
  Serial.begin(9600);

  pinMode(speedOutPin, OUTPUT);
}

void loop()
{
  unsigned long currentTime = micros();

  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil(':');
    int data = Serial.parseInt();
    
    if (command == "speed")
    {
      float speedFrequency = (PULSES_PER_KM * data) / 3600.0f;
      speedDelayMicroSeconds = (1.0f / speedFrequency) * 1000000;
    }
  }

  if (currentTime - previousSpeedTime > (speedDelayMicroSeconds - 5)) {
    previousSpeedTime = currentTime;

    digitalWrite(speedOutPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(speedOutPin, LOW);
  }
}

