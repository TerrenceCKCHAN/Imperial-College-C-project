#include <bcm2835.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

#define CORRECT 	2//RPI_GPIO_P1_03	//GPIO 02
#define WRONG 		3//RPI_GPIO_P1_05    //GPIO 03
#define YOUR_TURN 	4//RPI_GPIO_P1_7	//GPIO 04
#define RED 		17//RPI_GPIO_P1_11	//GPIO 17
#define YELLOW 		27//RPI_GPIO_P1_13	//GPIO 27
#define GREEN 		9//RPI_GPIO_P1_21	//GPIO 09
#define WHITE 		22//RPI_GPIO_P1_15	//GPIO 22
#define RED_BOTTON 			10//RPI_GPIO_P1_19	//GPIO 10
#define YELLOW_BOTTON 		11//RPI_GPIO_P1_23	//GPIO 11
#define WHITE_BOTTON 		14//RPI_GPIO_P1_8	//GPIO 14
#define GREEN_BOTTON 		15//RPI_GPIO_P1_10	//GPIO 15
#define COUNTER_3 		25//RPI_GPIO_P1_12	//GPIO 25
#define COUNTER_2 		24//RPI_GPIO_P1_16	//GPIO 24
#define COUNTER_1 		23//RPI_GPIO_P1_18	//GPIO 23
#define COUNTER_0 		18//RPI_GPIO_P1_22	//GPIO 18



enum light{
	REDL,
	YELLOWL,
	GREENL,
	WHITEL
};

enum state{
	CORRECTS,
	WRONGS,
	WAIT
};


void WRONGLightON(){
	bcm2835_gpio_write(WRONG,HIGH);
	delay(500);
	bcm2835_gpio_write(WRONG,LOW);
}

void CORRECTLightON(){
	bcm2835_gpio_write(CORRECT,HIGH);
	delay(500);
	bcm2835_gpio_write(CORRECT,LOW);
}

void YOUR_TURNLightOn(){
	bcm2835_gpio_write(YOUR_TURN,HIGH);
	delay(500);
	bcm2835_gpio_write(YOUR_TURN,LOW);
}

void REDLightOn(){
	bcm2835_gpio_write(RED,HIGH);
	delay(500);
	bcm2835_gpio_write(RED,LOW);
	delay(500);
}
void GREENLightOn(){
	bcm2835_gpio_write(GREEN,HIGH);
	delay(500);
	bcm2835_gpio_write(GREEN,LOW);
	delay(500);
}
void YELLOWLightOn(){
	bcm2835_gpio_write(YELLOW,HIGH);
	delay(500);
	bcm2835_gpio_write(YELLOW,LOW);
	delay(500);
}
void WHITELightOn(){
	bcm2835_gpio_write(WHITE,HIGH);
	delay(500);
	bcm2835_gpio_write(WHITE,LOW);
	delay(500);
}

void C_0_ON(){
	bcm2835_gpio_write(COUNTER_0,HIGH);
}

void C_1_ON(){
	bcm2835_gpio_write(COUNTER_1,HIGH);	
}
void C_2_ON(){
	bcm2835_gpio_write(COUNTER_2,HIGH);	
}
void C_3_ON(){
	bcm2835_gpio_write(COUNTER_3,HIGH);	
}
void C_0_OFF(){
	bcm2835_gpio_clr(COUNTER_0);
}
void C_1_OFF(){
	bcm2835_gpio_clr(COUNTER_1);
}
void C_2_OFF(){
	bcm2835_gpio_clr(COUNTER_2);
}
void C_3_OFF(){
	bcm2835_gpio_clr(COUNTER_3);
}

void initSequence(enum light sequence[], int length){
	srand(time(NULL));
	int index =0;
	for(; index < length ; index ++){
		int randColour = rand() % 4;
		sequence[index] = (enum light) randColour;
	}
}

void printCounter(int rounds){
	switch(rounds){
		case 1:
			C_0_ON();
			C_1_OFF();
			C_2_OFF();
			C_3_OFF();
			break;
		case 2:
			C_0_OFF();
			C_1_ON();
			C_2_OFF();
			C_3_OFF();
			break;
		case 3:
			C_0_ON();
			C_1_ON();
			C_2_OFF();
			C_3_OFF();
			break;
		case 4:
			C_0_OFF();
			C_1_OFF();
			C_2_ON();
			C_3_OFF();
			break;
		case 5:
			C_0_ON();
			C_1_OFF();
			C_2_ON();
			C_3_OFF();
			break;
		case 6:
			C_0_OFF();
			C_1_ON();
			C_2_ON();
			C_3_OFF();
			break;
		case 7:
			C_0_ON();
			C_1_ON();
			C_2_ON();
			C_3_OFF();
			break;
		case 8:
			C_0_OFF();
			C_1_OFF();
			C_2_OFF();
			C_3_ON();
			break;
		case 9:
			C_0_ON();
			C_1_OFF();
			C_2_OFF();
			C_3_ON();
			break;
		case 10:
			C_0_OFF();
			C_1_ON();
			C_2_OFF();
			C_3_ON();
			break;
		case 11:
			C_0_ON();
			C_1_ON();
			C_2_OFF();
			C_3_ON();
			break;
		case 12:
			C_0_OFF();
			C_1_OFF();
			C_2_ON();
			C_3_ON();
			break;
		case 13:
			C_0_ON();
			C_1_OFF();
			C_2_ON();
			C_3_ON();
			break;
		case 14:
			C_0_OFF();
			C_1_ON();
			C_2_ON();
			C_3_ON();
			break;
		case 15:
			C_0_ON();
			C_1_ON();
			C_2_ON();
			C_3_ON();
			break;	
		
		}
}
void printSequence(enum light sequence[], int length){
	int index = 0;
	for(;index<length;index++){
		switch(sequence[index]){
			case REDL:
				REDLightOn();
				break;
			case YELLOWL:
				YELLOWLightOn();
				break;
			case GREENL:
				GREENLightOn();
				break;
			case WHITEL:
				WHITELightOn();
				break;
				
		}
	}
}

void OFFLight(){
		bcm2835_gpio_clr(RED);
		bcm2835_gpio_clr(GREEN);
		bcm2835_gpio_clr(WHITE);
		bcm2835_gpio_clr(YELLOW);
		bcm2835_gpio_clr(CORRECT);
		bcm2835_gpio_clr(WRONG);
		bcm2835_gpio_clr(YOUR_TURN);
		bcm2835_gpio_clr(COUNTER_0);
		bcm2835_gpio_clr(COUNTER_1);
		bcm2835_gpio_clr(COUNTER_2);
		bcm2835_gpio_clr(COUNTER_3);
}


char ReadInput(){
		while(1){
		if(bcm2835_gpio_eds(RED_BOTTON)){
			REDLightOn();
			bcm2835_gpio_set_eds(RED_BOTTON);
			return 'R';
		}
		if(bcm2835_gpio_eds(GREEN_BOTTON)){
			GREENLightOn();
			bcm2835_gpio_set_eds(GREEN_BOTTON);
			return 'G';
		}
		if(bcm2835_gpio_eds(YELLOW_BOTTON)){
			YELLOWLightOn();
			bcm2835_gpio_set_eds(YELLOW_BOTTON);
			return 'Y';
		}
		if(bcm2835_gpio_eds(WHITE_BOTTON)){
			WHITELightOn();
			bcm2835_gpio_set_eds(WHITE_BOTTON);
			return 'W';
		}
	}
}


void initOutput()
{
	bcm2835_gpio_fsel(WRONG,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(CORRECT,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(YOUR_TURN,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(RED,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(YELLOW,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(GREEN,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(WHITE,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(COUNTER_0,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(COUNTER_1,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(COUNTER_2,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_fsel(COUNTER_3,BCM2835_GPIO_FSEL_OUTP);
}

void initInput()
{
	bcm2835_gpio_fsel(RED_BOTTON,BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(RED_BOTTON,BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_len(RED_BOTTON);
	bcm2835_gpio_fsel(YELLOW_BOTTON,BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(YELLOW_BOTTON,BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_len(YELLOW_BOTTON);
	bcm2835_gpio_fsel(WHITE_BOTTON,BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(WHITE_BOTTON,BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_len(WHITE_BOTTON);
	bcm2835_gpio_fsel(GREEN_BOTTON,BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(GREEN_BOTTON,BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_len(GREEN_BOTTON);

}


int main(int argc, char **argv)
{
	bcm2835_init();
	if(!bcm2835_init()){
		return 1;
	}
	
	enum light sequence[100];
	enum state gamestate = WAIT;
	enum light input;

	int round = 1;

	
	
	OFFLight();
	initOutput();
	initInput();
	
	initSequence(sequence,100);
	
	
	 
	
	while(gamestate != WRONGS){
		printSequence(sequence,round);
		int pos = 0;
		YOUR_TURNLightOn();
		while(gamestate == WAIT){
		if(pos == round){
			CORRECTLightON();
			printCounter(round);
			gamestate = CORRECTS;
			break;
		}
		char c = ReadInput();
		
		switch(c){
			case 'R':
				input = REDL;
				break;
			case 'Y':
				input = YELLOWL;
				break;
			case 'G':
				input = GREENL;
				break;
			case 'W':
				input = WHITEL;
				break;				
		}
		
		if(sequence[pos] == input){
			pos++;
		}else{
			gamestate = WRONGS;
		}
		
	}
	
		if(gamestate == CORRECTS){
			round++;
			gamestate = WAIT;
		}else if(gamestate == WRONGS){
			WRONGLightON();
		}
	}
	

	OFFLight();
	
	bcm2835_close();
	
	return 0;
}

