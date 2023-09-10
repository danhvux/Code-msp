#include "msp430g2553.h"

#define clock BIT0
#define DATA BIT1
#define CHOT BIT2

#define OUTPUT P1DIR
#define INPUT P1DIR

void clk(int x)
{
  
  for (int a=0;a<x;a++)
  {
    P1OUT |=BIT0;
    P1OUT &=~BIT0;
  }
}


void data(int x)
{
  if (x==1)
  {
    P1OUT |=BIT1; 
  }
  else
  {
    P1OUT &=~BIT1;  
  }
  
}

void chot()
{
  P1OUT |=BIT2;
  P1OUT &=~BIT2;
}


void hieuung()
{
  for(int x=1; x <16;x++)
  {
    data(1);
    clk(x);
      
    data(0);
    clk(32-2*x);
    
    data(1);
    clk(x);
    chot();
    
    __delay_cycles(10000);
  }
}
void hieuung1()
{
  for(int x=1; x <=30 ;x++)
  {
    data(1);
    clk(x);
      
    data(0);
    clk(32-x);
    
    data(1);
    clk(x);
    chot();
    
    __delay_cycles(10000);
  
  }
}
void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  OUTPUT |= BIT0+ BIT1+BIT2;
  
  while (1){
  for(int x=31; x >=0 ;x--)
  {
    if(x==31){
    data(0);
    clk(x);	
    data(1);		
    clk(1);		
    chot();
    }
    else{
    data(0);
    clk(x);	
    data(1);
    clk(1);
    data(0);
    clk(31-x);
    chot();
    }
    
    __delay_cycles(10000);
  }
}
}