int data[100];
int x = 0;
long sum = 0;
void setup()
{
  Serial.begin(115200);
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 7999;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  sei();
}
void loop()
{
  if (x >= 100)
  {
    x = 0;
    while (1);
  }
}
ISR(TIMER1_COMPA_vect)
{
  if (x < 100)
  {
    data[x] = analogRead(A0);
    x++;
  }
  if (x >= 100)
  {
    //cli();
    //TIMSK1 &= ~(1 << OCIE1A);
    for (int i = 0; i <= 100; i++ )
    {
      sum += data[i];
    }
    sum = sum / 100;
    for (int j = 0; j <= 100; j++)
    {
      //Serial.println(data[j]);
     // Serial.print(",");
      Serial.println(sum);
    }
    x++;
    sum = 0;
  }
}
