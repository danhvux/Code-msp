
#include "msp430g2553.h"

#define CLOCK           BIT0
#define DATA            BIT1
#define CHOT            BIT2

#define PIN_MODE        P1DIR
#define digitalWrite    P1OUT

void clock(int x);
void data(int x);
void chot(void);

void clock(int x){
  for(int a=0;a<x;a++){
    digitalWrite |=  CLOCK;
    digitalWrite &=~ CLOCK;
  }
}

void data(int x){
  if(x==1){
    digitalWrite |=  DATA;
  }
  else{
    digitalWrite &=~ DATA;
  }
}

void chot(void){
  digitalWrite |=  CHOT;
  digitalWrite &=~ CHOT;
}

void keo_rem_ra(void);
void keo_rem_vao(void);
void sang_tung_con(void);
void dich_trai(void);

void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  PIN_MODE |= CLOCK + DATA + CHOT;//khai bao ngo ra
  
  while(1){
    keo_rem_ra();
    keo_rem_vao();
    sang_tung_con();
    dich_trai();
    
  }
}

void keo_rem_ra(void){
  for(int x=15;x>0;x--){
    data(0);
    clock(x);
    
    data(1);
    clock(32-2*x);
    
    data(0);
    clock(x);
    
    chot();
    
    __delay_cycles(5000);  
  }
}

void keo_rem_vao(void){
  for(int x=1;x<=16;x++){
    data(1);
    clock(x);
    
    data(0);
    clock(32-2*x);
    
    data(1);
    clock(x);
    
    chot();
    
    __delay_cycles(5000);    
  }
}

void sang_tung_con(void){
  for(int x=1;x<32;x++){
    data(1);
    clock(x);
    
    data(0);
    clock(32-x);
    
    chot();
    
    __delay_cycles(5000);  
  }
}

void dich_trai(void){
  for(int x=0;x<=31;x++){
    if(x==0){
      data(0);
      clock(31);
      
      data(1);
      clock(1);
      
      chot();
      
      __delay_cycles(5000);  
    }
    else{
      data(0);
      clock(31-x);
      
      data(1);
      clock(1);
      
      data(0);
      clock(x);   
      
      chot();
      
      __delay_cycles(5000);   
    }
  }
}