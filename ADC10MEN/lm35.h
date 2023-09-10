
unsigned int Read_LM35(int chanel);

unsigned int Read_LM35(int chanel)
{
  ADC10CTL0 &=~ (ENC + ADC10SC); //Khong cho phep bien doi ADC + ngung chuyen doi ADC
  while (ADC10CTL1 & BUSY); //cho neu ADC ban
  //Thoi gian lay mau va giu mau 64*ADC10CLK + bat bien doi ADC + [(REFON + SREF_1)=1.5V]
  ADC10CTL0 = ADC10SHT_3 + MSC + ADC10ON + REFON + SREF_1;
  ADC10CTL1 &=~ 0x0FFF; //clear thanh ghi ADC10CTL1
  ADC10CTL1 = (chanel*0x1000u) + ADC10DIV_7 + ADC10SSEL_3; //kenh A3 + clock/8 + MCLK
  ADC10AE0 |= (BIT0<<chanel); //vo hieu hoa bo dem
  ADC10CTL0 &=~ ADC10IFG; //Xoa co ngat
  ADC10CTL0 |= ENC + ADC10SC; //cho phep bien doi ADC + bat dau chuyen doi ADC
  while(!(ADC10CTL0 & ADC10IFG)); //Cho den khi chuyen doi xong
  return (int)((float)(ADC10MEM*1.5*100)/1024);
}