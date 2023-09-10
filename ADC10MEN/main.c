
#include "msp430f2122.h"
#include "lcd.h"
#include "lm35.h"

void main(void)
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  BCSCTL1 = CALBC1_1MHZ;      // Set DCO to 1MHz 
  DCOCTL = CALDCO_1MHZ;
  
  Khoi_tao_LCD();
  
  P2DIR |= BIT6+BIT7;
  
  while(1)
  {   
    Vi_tri(1,0);  
    In_chuoi("NHIET DO: ");   
    In_so(Read_LM35(0));
    
    
    if(Read_LM35(0) >= 50){P2OUT |= BIT6+BIT7;}
    else{P2OUT &=~ BIT6+BIT7;}
  }
}


