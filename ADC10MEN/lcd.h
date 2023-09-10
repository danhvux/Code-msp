//===================Dinh nghia cac Port IO=============//
#define     LCD_OUT       P1OUT
#define     RS            BIT2   
#define     E             BIT3

#define     D4            BIT4         
#define     D5            BIT5         
#define     D6            BIT6          
#define     D7            BIT7 

#define    lcd_dir    P1DIR
#define    lcd_pins  (RS|E|D4|D5|D6|D7)

//-------------------dinh nghia cam bien hong ngoai
//===========================Tao ham Xung cho LCD===============================
void Xung_LCD()
{
  LCD_OUT |= E;
  __delay_cycles(330);
  LCD_OUT &= ~E;
  __delay_cycles(330);    
}
//===========================Ghi 1 byte lenh cho LCD============================
void Ghi_lenh_LCD(char Lenh)
{
  LCD_OUT = (Lenh & 0xF0);     // Ghi 4 bit cao
  
  LCD_OUT &= ~RS;
  Xung_LCD();
  LCD_OUT &=~0xFF;
  LCD_OUT |= ((Lenh & 0x0F) << 4); // Dich trai 4bit de ghi 4 bit thap
  
  LCD_OUT &= ~RS;
  Xung_LCD();
}
//===========================Ghi 1 byte data cho LCD============================   
void Ghi_data_LCD(char Data)
{
  LCD_OUT = (Data & 0xF0);     // Ghi 4 bit cao
  
  LCD_OUT |= RS;
  Xung_LCD();
  LCD_OUT &=~0xFF;
  
  LCD_OUT |= ((Data & 0x0F) << 4); // Dich trai 4bit de ghi 4 bit thap
  LCD_OUT |= RS;
  Xung_LCD();
}
//======================Vi tri xuat hien ky tu tren LCD========================= 
void Vi_tri(char Hang, char Cot)
{
  int firstChar[] = {0x80,0x80, 0xC0, 0x94, 0xD4};
  Ghi_lenh_LCD(firstChar[Hang] + Cot);
}
//====================Lam sach (xoa hien hien thi) tren LCD=====================
void Xoa_LCD()
{
  Ghi_lenh_LCD(0x01);//xoa hien thi
  Ghi_lenh_LCD(0x02);//dua con tro ve vi tri dau dong 1
}
//=============================Ham khoi tao LCD=================================
void Khoi_tao_LCD(void)
{
  lcd_dir = lcd_pins;
  LCD_OUT = 0x20;       //thiet lap giao thuc voi LCD
  Xung_LCD();           //thuc thi
  Ghi_lenh_LCD(0x28);   //thiet lap giao thuc voi LCD dung 4bit, lcd 2dong, do phan giai 5x8
  Ghi_lenh_LCD(0x06);   //ky tu in sau se dung sau ky tu in truoc
  Ghi_lenh_LCD(0x0C);   //bat hien thi con tro
}
//=========================In chuoi ky tu len LCD===============================
void In_chuoi(char *kytu)
{
  while ((kytu != 0) && (*kytu != 0))
  {
    Ghi_data_LCD(*kytu);
    kytu++;
  }
}

char arr[3]; // Bien chua ky tu doi tu so sang chuoi

void DOI(char* string, unsigned int a)
{
    string[0] = a/10+48;     //chuc
    string[1] = a%10+48;     //donvi
}

void In_so(int x)
{
  DOI(arr,x); 
  In_chuoi(arr);
}