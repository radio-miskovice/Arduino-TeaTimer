#include <Arduino.h>
#include <avr/sleep.h>

char lights = 7;
char current = 4;

const char BEEPER = A6 ;

void setup()
{
  pinMode(D5, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);
  pinMode(D3, OUTPUT);
  digitalWrite(D3, HIGH);
  pinMode(D2, OUTPUT);
  digitalWrite(D2, HIGH);
  digitalWrite(D5, HIGH);
  tone( BEEPER, 3000, 500 );
  digitalWrite(D2, LOW);
  delay(150);
  digitalWrite(D3, LOW);
  delay(150);
  digitalWrite(D4, LOW);
  delay(150);
  digitalWrite(D5, LOW);
  delay(100);
  digitalWrite(D5, HIGH);
  // pinMode( BEEPER, OUTPUT );
}

inline void led_off() { digitalWrite(D5, LOW); }
inline void led_on() { digitalWrite(D5, HIGH); }

char seconds = 60;
char minutes = 3;

void loop()
{
  if (current == 0)
  {
    if( seconds > 0 ) {
      digitalWrite(D2, LOW);
      digitalWrite(D3, LOW);
      digitalWrite(D4, LOW);
      digitalWrite(D5, HIGH);
      tone( BEEPER, 240, 500);
      delay(500);
      digitalWrite(D5, LOW);
      digitalWrite(BEEPER, LOW);
      delay(500);
      seconds -- ;
    }
    else {
      pinMode( LED_BUILTIN, OUTPUT);
      digitalWrite( LED_BUILTIN, HIGH );
      delay(2000);
      digitalWrite( LED_BUILTIN, LOW );
      pinMode(BEEPER, INPUT);
      sleep_enable();
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_cpu();
    }
  }
  else
  {
    digitalWrite(current, LOW); // switch on
    delay(500);
    digitalWrite(current, HIGH); // switch off
    delay(500);
    if (--seconds == 0)
    {
      tone(BEEPER, 1200, 1250 - minutes * 250);
      seconds = 60;
      minutes--;
      if (minutes > 0)
      {
        digitalWrite(current, HIGH); // switch off
        current--;
      }
      else {
        current = 0 ;
        seconds = 30 ;
      }
    }
  }
}