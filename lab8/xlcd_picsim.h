
#define LENA  PORTEbits.RE1
#define LDAT  PORTEbits.RE2
#define LPORT PORTD

/* Function Set defines */
#define FOUR_BIT   0b00101111  /* 4-bit Interface               */
#define EIGHT_BIT  0b00111111  /* 8-bit Interface               */
#define LINE_5X7   0b00110011  /* 5x7 characters, single line   */
#define LINE_5X10  0b00110111  /* 5x10 characters               */
#define LINES_5X7  0b00111011  /* 5x7 characters, multiple line */


#define L_ON	0x0F
#define L_OFF	0x08
#define L_CLR	0x01
#define L_L1	0x80
#define L_L2	0xC0
#define L_CR	0x0F		
#define L_NCR	0x0C	

#define L_CFG   0x38

void atraso_ms(unsigned int valor);
void OpenXLCD(unsigned char lcdtype);
void WriteCmdXLCD(unsigned char val); 
void WriteDataXLCD(unsigned char val);
void putrsXLCD(const rom unsigned char* str);
void putsXLCD(unsigned char *str);
#define putcXLCD WriteDataXLCD
