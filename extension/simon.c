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

int difficulty = 1;

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
	int i =0;
	for(;i<10;i++){
	bcm2835_gpio_write(WRONG,HIGH);
	delay(200);
	bcm2835_gpio_write(WRONG,LOW);
	delay(200);
	}
	delay(3000);
}

void CORRECTLightON(){
	bcm2835_gpio_write(CORRECT,HIGH);
	delay(1000);
	bcm2835_gpio_write(CORRECT,LOW);
}

void YOUR_TURNLightOn(){
	bcm2835_gpio_write(YOUR_TURN,HIGH);
	delay(1000);
	bcm2835_gpio_write(YOUR_TURN,LOW);
}

void REDLightOn(int time){
	bcm2835_gpio_write(RED,HIGH);
	delay(time);
	bcm2835_gpio_write(RED,LOW);
	delay(time);
}
void GREENLightOn(int time){
	bcm2835_gpio_write(GREEN,HIGH);
	delay(time);
	bcm2835_gpio_write(GREEN,LOW);
	delay(time);
}
void YELLOWLightOn(int time){
	bcm2835_gpio_write(YELLOW,HIGH);
	delay(time);
	bcm2835_gpio_write(YELLOW,LOW);
	delay(time);
}
void WHITELightOn(int time){
	bcm2835_gpio_write(WHITE,HIGH);
	delay(time);
	bcm2835_gpio_write(WHITE,LOW);
	delay(time);
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

void CounterBlink(){
	int i =0 ;
	for(;i<5;i++){
	C_0_ON();
	C_1_ON();
	C_2_ON();
	C_3_ON();
	delay(300);
	C_0_OFF();
	C_1_OFF();
	C_2_OFF();
	C_3_OFF();
	delay(300);
	}
	
}


void RotateLight(int time, int circle){
	int  i =0;
	CounterBlink();
	for(;i<circle;i++){
		bcm2835_gpio_write(RED,HIGH);
		delay(time);
		bcm2835_gpio_write(RED,LOW);
		delay(time);
		bcm2835_gpio_write(YELLOW,HIGH);
		delay(time);
		bcm2835_gpio_write(YELLOW,LOW);
		delay(time);
		bcm2835_gpio_write(GREEN,HIGH);
		delay(time);
		bcm2835_gpio_write(GREEN,LOW);
		delay(time);
		bcm2835_gpio_write(WHITE,HIGH);
		delay(time);
		bcm2835_gpio_write(WHITE,LOW);
		delay(time);
		
		
		
	}
}

void AllBlink(){
	RotateLight(20,100);	
}

void StartGame(){
	RotateLight(50,5);
	YOUR_TURNLightOn();
	CORRECTLightON(); 
	WRONGLightON();
	delay(500);
	
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
	if(rounds > 16 ){
		rounds %= 15;
		
	}else if(rounds == 16 || rounds == 32){
		difficulty++;
		RotateLight(50,5);
	}
	
	int bit[4];
	int pos = 0;
	while(pos < 4) {
		bit[pos] = rounds % 2;
		rounds /= 2;
		pos++;
	}
	if(bit[0]) {
		C_0_ON();
	} else {
		C_0_OFF();
	}
	if(bit[1]) {
		C_1_ON();
	} else {
		C_1_OFF();
	}
	if(bit[2]) {
		C_2_ON();
	} else {
		C_2_OFF();
	}
	if(bit[3]) {
		C_3_ON();
	} else {
		C_3_OFF();
	}
}
void printSequence(enum light sequence[], int length, int time){
	int index = 0;
	for(;index<length;index++){
		switch(sequence[index]){
			case REDL:
				REDLightOn(time);
				break;
			case YELLOWL:
				YELLOWLightOn(time);
				break;
			case GREENL:
				GREENLightOn(time);
				break;
			case WHITEL:
				WHITELightOn(time);
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
		int time = 500;
		while(1){
		if(bcm2835_gpio_eds(RED_BOTTON)){
			REDLightOn(time);
			bcm2835_gpio_set_eds(RED_BOTTON);
			return 'R';
		}
		if(bcm2835_gpio_eds(GREEN_BOTTON)){
			GREENLightOn(time);
			bcm2835_gpio_set_eds(GREEN_BOTTON);
			return 'G';
		}
		if(bcm2835_gpio_eds(YELLOW_BOTTON)){
			YELLOWLightOn(time);
			bcm2835_gpio_set_eds(YELLOW_BOTTON);
			return 'Y';
		}
		if(bcm2835_gpio_eds(WHITE_BOTTON)){
			WHITELightOn(time);
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
	while(1){
	bcm2835_init();
	if(!bcm2835_init()){
		return 1;
	}
	
	enum light sequence[100];
	enum state gamestate = WAIT;
	enum light input;

	int round = 1;

	int time = 450 - difficulty*150;

	
		
		
	

	
	OFFLight();
	initOutput();
	initInput();
	
	initSequence(sequence,100);
	StartGame();
	
	 
	
	while(gamestate != WRONGS){
		printSequence(sequence,round, time);
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
		if(difficulty == 2){
			AllBlink();
			break;
		}
	}
	

	OFFLight();
	
	bcm2835_close();
}
	
	return 0;
}

