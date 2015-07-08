const unsigned long PULSES_PER_KM = 4500;

const int speedOutPin = 2;
const int rpmOutPin = 3;

unsigned long previousSpeedTime = 0;
unsigned long speedDelayMicroSeconds = 1 * 10000;

unsigned long previousRpmTime = 0;
unsigned long rpmDelayMicroSeconds = 1 * 1000000;
unsigned long halfRpmDelayMicroSeconds = rpmDelayMicroSeconds / 2;

void setup()
{
  Serial.begin(115200);

  pinMode(speedOutPin, OUTPUT); 
  pinMode(rpmOutPin, OUTPUT);
}

void loop()
{
  unsigned long currentTime = micros();

  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil(':');
    
    if (command == "S")
    {
      int speed = Serial.parseInt();
      float speedFrequency = (PULSES_PER_KM * speed) / 3600.0f;
      speedDelayMicroSeconds = (1.0f / speedFrequency) * 1000000;
    }
    else if (command == "R")
    {
      int rpm = Serial.parseInt();
      float rpmFrequency = rpm / 60.0f;
      rpmDelayMicroSeconds = (1.0f / rpmFrequency) * 1000000;
      halfRpmDelayMicroSeconds = rpmDelayMicroSeconds / 2;
    }
  }

  if (currentTime - previousSpeedTime > speedDelayMicroSeconds)
  {
    previousSpeedTime = currentTime;

    digitalWrite(speedOutPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(speedOutPin, LOW);
  }

  // RPM signal from the car is a PWM square wave with 50% duty-cycle.
  if (currentTime - previousRpmTime > rpmDelayMicroSeconds)
  {
    previousRpmTime = currentTime;

    digitalWrite(rpmOutPin, HIGH);
  }

  if (currentTime - previousRpmTime > halfRpmDelayMicroSeconds)
  {
    digitalWrite(rpmOutPin, LOW);
  }
}

