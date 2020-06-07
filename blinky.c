#include <avr/io.h>
#include <avr/interrupt.h>

//#define F_CPU 1000000UL - change & uncomment if clock freq is other than 1 MHz
unsigned char blinkCounter = 0; 

int main (void)
{
  //1 = output, 0 = input
  DDRB |= (1 << PINB3); // set Pin4 / PB3 / OC0 as output ; PINB3=3
  
  // enable global interrupts
  sei();
  // enable CTC interrupt on match
  TIMSK |= (1<<OCIE0);
  
  // set comparison value
  OCR0 = 0xFE;
  
  // set counter start value
  TCNT0 = 0x00;
  
  // set timer/counter control register
  TCCR0 = (0<<WGM00) | (1<<WGM01) | (0<<COM01) | (1<<COM00) | (1<<CS02) | (0<<CS01) | (1<<CS00);
  
  while(1)
  {
    // do nothing as ISR would handle wave generation
  }
  cli();
  return(0);
}

ISR(TIMER0_COMP_vect)
{
  // increment blinkCounter
  blinkCounter++;
  // after 10 interrupts, toggle the freq via pre-scalar - 256 / 1024 & reset counter
  if (blinkCounter >= 10)
  {
    TCCR0 ^= (1<<CS00);
    blinkCounter = 0;
  }
}




