// Arquivo com os cabeçalhos do isr.c
#include<P18F4550.H>

// Protótipos das Funções de Interrupção
void ISR_Baixa_Prioridade(void);
void ISR_Alta_Prioridade(void);

#pragma code high_vector=0x08 
void int_alta(void)
{
	_asm GOTO ISR_Alta_Prioridade _endasm
}
#pragma code 


#pragma code low_vector=0x18 
void int_baixa(void)
{
	_asm GOTO ISR_Baixa_Prioridade _endasm
}
#pragma code 
