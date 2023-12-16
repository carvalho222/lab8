// Arquivo das subrotinas de interrupção
#include "isr.h"

// Interrupção de alta prioridade 
#pragma interrupt ISR_Alta_Prioridade
void ISR_Alta_Prioridade(void){
	extern char temp_desejada, minutos, horas, segundos, menu, inc, confirma_acionado, ciclo_ativo;

///////////// CONTAGEM DO TEMPORIZADOR///////////////////////////
	// Ocorrência Timer 0
	WriteTimer0(26474);
	if(segundos == 0 && minutos == 0 && horas == 0){
		INTCONbits.TMR0IF = 0;}
	else{
		segundos--;
		if(segundos < 0 && minutos != 0 || segundos < 0 && horas != 0){
			segundos = 59;
			minutos--;
			if(minutos < 0 && horas != 0){
				minutos = 59;
				horas--;
				if(horas < 0){
				horas = 0;}
			}
			if(horas == 2 && minutos > 0)
			minutos == 0;	
		}
	}
	INTCONbits.TMR0IF = 0;

	// Ocorrência Timer 1
	ADCON0bits.GO_DONE = 1;
	TMR1H = 0xCF;
	TMR1L = 0x2C;
	PIR1bits.TMR1IF = 0;

///////////////// MUDANÇA DE MENUS///////////////////////

	// Ocorrência de INT1
if(confirma_acionado == 1){
	if(INTCON3bits.INT1IF){
		menu += inc;
		if(menu == 4)
		menu = 0;
}
	INTCON3bits.INT1IF = 0;
	
	// Ocorrência de INT2;
	if(INTCON3bits.INT2IF){
		menu -= inc;
		if(menu < 0)
		menu = 3;
}
	INTCON3bits.INT2IF = 0;
}

////////// CONFIGURAÇÃO DAS HORAS ///////////////////////

else{

	if (confirma_acionado == -1 && INTCON3bits.INT1F == 1 && menu == 0){
			temp_desejada += 5;
			if(temp_desejada > 75)
			temp_desejada = 0;
			if(temp_desejada < 25)
			temp_desejada = 25;
		INTCON3bits.INT1IF = 0;
		}

		if (INTCON3bits.INT2F){
			temp_desejada -= 5;
			if(temp_desejada < 25)
			temp_desejada = 25;
			if(temp_desejada > 75)
			temp_desejada = 0;
		INTCON3bits.INT2IF = 0;
		}

}

///////////////////// SELECIONAR AÇÃO///////////////////////////

	// Ocorrência do INT0
	
////////////// AJUSTE HORARIO /////////////////////////

	switch(menu){
	case 0:
	if (INTCONbits.INT0F){
		confirma_acionado = -confirma_acionado;
		INTCONbits.INT0IF = 0;
	}
	if(confirma_acionado == -1 && INTCONbits.INT0F == 1){
			confirma_acionado = -confirma_acionado;
			INTCONbits.INT0IF = 0;
	}

//////////// ALARME //////////////////////////////////

	case 1:
	if (INTCONbits.INT0F){
		confirma_acionado = -confirma_acionado;
		INTCONbits.INT0IF = 0;
	}
	if(confirma_acionado == -1 && INTCONbits.INT0F == 1){
	
			confirma_acionado = -confirma_acionado;
			INTCONbits.INT0IF = 0;
	}
	break;

//////////// SERIAL //////////////////////////////////

	case 2:
	if(INTCONbits.INT0IF){
	menu = 10;
	}
	INTCONbits.INT0IF = 0;
	break;

//////// DADOS SERIAL ///////////////////////////////

	case 10:
	if(INTCONbits.INT0IF){
	menu = 2;
	}
	INTCONbits.INT0IF = 0;
	break;

/////////// LÂMPADA ////////////////////////////////

	case 3:
	if (INTCONbits.INT0F){
		confirma_acionado = -confirma_acionado;
		INTCONbits.INT0IF = 0;
	}
	if(confirma_acionado == -1){
	if(INTCON3bits.INT1F){
	ciclo_ativo += 100; 	// Aumenta 10% o duty cycle
    if (ciclo_ativo > 1000) 	
		ciclo_ativo = 0; 			// Condição para zerar o duty cycle
	INTCON3bits.INT1IF = 0;
	}	
	
	}
	break;	
}
}
////////////////////////////////////////////////////////////////



// Interrupção de baixa prioridade
#pragma interruptlow ISR_Baixa_Prioridade 
void ISR_Baixa_Prioridade(void){
	extern char conversao, temp, sel, inc, menu, horas, minutos, segundos, confirma_acionado;

	
	// Interrupção ADC
	if(PIR1bits.ADIF){
	conversao = (ADRESH*256) + ADRESL;
	ltoa((long)conversao, temp);
	PIR1bits.ADIF = 0;
	}
}	



	