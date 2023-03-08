void GeneralSetup(void)
{
  pinMode(SW2_pin, INPUT);
  digitalWrite(SW2_pin, HIGH);

  pinMode(SW3_pin, INPUT);
  digitalWrite(SW3_pin, HIGH);

  POWER_ON;
}
