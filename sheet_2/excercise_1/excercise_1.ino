

void setup()
{
}

void loop()
{
}

int read_ultra()
{
  // Send start signal
  pinMode(D8, OUTPUT);
  digitalWrite(D8, HIGH);
  delayMicroseconds(15);
  digitalWrite(D8, LOW);

  // switch to input 
  pinMode(D8, INPUT);

  // read sensor value
  uint16_t ultra_sensor_response_length = pulseIn(D8, HIGH, 30);
  Serial.print("Value of messurement: ");
  Serial.println(ultra_sensor_response_length);

  return ultra_sensor_response_length;
}