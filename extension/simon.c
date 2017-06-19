#include <bcm2835.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

/////////////////////////////////////////////////////////////////////////////////////////
// Macro definition that help to set the GPIO Pins to their corresponding lights
/////////////////////////////////////////////////////////////////////////////////////////
#define CORRECTLIGHT   2
#define WRONGLIGHT     3
#define YOUR_TURN      4
#define REDLIGHT      17
#define YELLOWLIGHT   27
#define GREENLIGHT     9
#define WHITELIGHT    22
#define RED_BOTTON    10
#define YELLOW_BOTTON 11
#define WHITE_BOTTON  14
#define GREEN_BOTTON  15
#define COUNTER_3     25
#define COUNTER_2     24
#define COUNTER_1     23
#define COUNTER_0     18

//The maximum of sequence of light generated
#define MAX_NUMBER_OF_LIGHT 100
#define INIT_BLINKING_TIME  450
#define SCALE_OF_DIFF       150

#define BLINK_TIME         200
#define LEVEL_1            16
#define LEVEL_2            32


//indicate the difficulty of current game state
int difficulty = 0;

//enum to represent the light
enum light {
    RED,
    YELLOW,
    GREEN,
    WHITE
};

//current state of the game
enum state {
    CORRECT,
    WRONG,
    WAIT
};

void StartGameSound() {
    int pid;
    pid = fork();
    if (pid == 0) {
        execlp("/usr/bin/omxplayer", " ", "/home/pi/Desktop/Start.wav", NULL);
        _exit(0);
    }
}

void WaitStartSound() {
    int pid;
    pid = fork();
    if (pid == 0) {
        execlp("/usr/bin/omxplayer", " ", "/home/pi/Desktop/waitstart.mp3", NULL);
        _exit(0);
    }
}

void EndSound() {
    delay(500);
    int pid;
    pid = fork();
    if (pid == 0) {
        execlp("/usr/bin/omxplayer", " ", "/home/pi/Desktop/end.wav", NULL);
        _exit(0);
    }
}

void upgradeSound() {

    int pid;
    pid = fork();
    if (pid == 0) {
        execlp("/usr/bin/omxplayer", " ", "/home/pi/Desktop/Upgrade.mp3", NULL);
        _exit(0);
    }
}

void WinSound() {
    int pid;
    pid = fork();
    if (pid == 0) {
        execlp("/usr/bin/omxplayer", " ", "/home/pi/Desktop/win.mp3", NULL);
        _exit(0);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
//To check the wrong indicating light when starting the game
//POST: The wrong indicating light blinks
/////////////////////////////////////////////////////////////////////////////////////////
void StartWrongLightON() {
    int i = 0;
    for (; i < 13; i++) {
        bcm2835_gpio_write(WRONGLIGHT, HIGH);
        delay(BLINK_TIME);
        bcm2835_gpio_write(WRONGLIGHT, LOW);
        delay(BLINK_TIME);
    }
    delay(3000);
}
/////////////////////////////////////////////////////////////////////////////////////////
//To turn on the correct indicating light
//POST: The correct indicating light on for 1 second
/////////////////////////////////////////////////////////////////////////////////////////
void StartCorrectLightON() {
    bcm2835_gpio_write(CORRECTLIGHT, HIGH);
    delay(500);
    bcm2835_gpio_write(CORRECTLIGHT, LOW);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To turn on the wrong indicating light
//POST: The wrong indicating light on for 1 second
/////////////////////////////////////////////////////////////////////////////////////////
void StartYourTurnLightOn() {
    bcm2835_gpio_write(YOUR_TURN, HIGH);
    delay(500);
    bcm2835_gpio_write(YOUR_TURN, LOW);
}
/////////////////////////////////////////////////////////////////////////////////////////
//To turn on the wrong indicating light
//POST: The wrong indicating light blinks and the current game terminate
/////////////////////////////////////////////////////////////////////////////////////////
void WrongLightON() {
	
    int i = 0;
    for (; i < 2; i++) {
        bcm2835_gpio_write(WRONGLIGHT, HIGH);
        system("aplay /home/pi/Desktop/lose.wav");
        bcm2835_gpio_write(WRONGLIGHT, LOW);
        delay(BLINK_TIME);
    }
    delay(500);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To turn on the correct indicating light
//POST: The correct indicating light on for 1 second
/////////////////////////////////////////////////////////////////////////////////////////
void CorrectLightON() {
    bcm2835_gpio_write(CORRECTLIGHT, HIGH);
    system("aplay /home/pi/Desktop/correct.wav");
    bcm2835_gpio_write(CORRECTLIGHT, LOW);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To turn on the wrong indicating light
//POST: The wrong indicating light on for 1 second
/////////////////////////////////////////////////////////////////////////////////////////
void YourTurnLightOn() {
    bcm2835_gpio_write(YOUR_TURN, HIGH);
    system("aplay /home/pi/Desktop/wait.wav");
    bcm2835_gpio_write(YOUR_TURN, LOW);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To turn on the red light
//PRE: The time passed is valid
//POST: The red light is turned on for (time) milliseconds
/////////////////////////////////////////////////////////////////////////////////////////
void REDLightOn(int time) {
    bcm2835_gpio_write(REDLIGHT, HIGH);
    system("aplay /home/pi/Desktop/1.wav");
    bcm2835_gpio_write(REDLIGHT, LOW);
    delay(time);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To turn on the red light
//PRE: The time passed is valid
//POST: The red light is turned on for (time) milliseconds
/////////////////////////////////////////////////////////////////////////////////////////
void GREENLightOn(int time) {
    bcm2835_gpio_write(GREENLIGHT, HIGH);
    system("aplay /home/pi/Desktop/2.wav");
    bcm2835_gpio_write(GREENLIGHT, LOW);
    delay(time);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To turn on the yellow light
//PRE: The time passed is valid
//POST: The yellow light is turned on for (time) milliseconds
/////////////////////////////////////////////////////////////////////////////////////////
void YELLOWLightOn(int time) {
    bcm2835_gpio_write(YELLOWLIGHT, HIGH);
    system("aplay /home/pi/Desktop/3.wav");
    bcm2835_gpio_write(YELLOWLIGHT, LOW);
    delay(time);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To turn on the white light
//PRE: The time passed is valid
//POST: The white light is turned on for (time) milliseconds
/////////////////////////////////////////////////////////////////////////////////////////
void WHITELightOn(int time) {
    bcm2835_gpio_write(WHITELIGHT, HIGH);
    system("aplay /home/pi/Desktop/4.wav");
    bcm2835_gpio_write(WHITELIGHT, LOW);
    delay(time);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To turn on the counter_0 light
//POST: The counter_0 light is turned on
/////////////////////////////////////////////////////////////////////////////////////////
void C_0_ON() {
    bcm2835_gpio_write(COUNTER_0, HIGH);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To turn on the counter_1 light
//POST: The counter_1 light is turned on
/////////////////////////////////////////////////////////////////////////////////////////
void C_1_ON() {
    bcm2835_gpio_write(COUNTER_1, HIGH);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To turn on the counter_2 light
//POST: The counter_2 light is turned on
/////////////////////////////////////////////////////////////////////////////////////////
void C_2_ON() {
    bcm2835_gpio_write(COUNTER_2, HIGH);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To turn on the counter_3 light
//POST: The counter_3 light is turned on
/////////////////////////////////////////////////////////////////////////////////////////
void C_3_ON() {
    bcm2835_gpio_write(COUNTER_3, HIGH);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To turn off the counter_0 light
//POST: The counter_0 light is turned off
/////////////////////////////////////////////////////////////////////////////////////////
void C_0_OFF() {
    bcm2835_gpio_clr(COUNTER_0);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To turn off the counter_1 light
//POST: The counter_1 light is turned off
/////////////////////////////////////////////////////////////////////////////////////////
void C_1_OFF() {
    bcm2835_gpio_clr(COUNTER_1);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To turn off the counter_0 light
//POST: The counter_0 light is turned off
/////////////////////////////////////////////////////////////////////////////////////////
void C_2_OFF() {
    bcm2835_gpio_clr(COUNTER_2);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To turn off the counter_0 light
//POST: The counter_0 light is turned off
/////////////////////////////////////////////////////////////////////////////////////////
void C_3_OFF() {
    bcm2835_gpio_clr(COUNTER_3);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To blink the light on the binary counter
//POST: The counter is blinked for 5 times
/////////////////////////////////////////////////////////////////////////////////////////
void CounterBlink() {
    int i = 0;
    for (; i < 5; i++) {
        C_0_ON();
        C_1_ON();
        C_2_ON();
        C_3_ON();
        delay(BLINK_TIME);
        C_0_OFF();
        C_1_OFF();
        C_2_OFF();
        C_3_OFF();
        delay(BLINK_TIME);
    }

}

/////////////////////////////////////////////////////////////////////////////////////////
//To blink the 4 light (RED,YELLOW,GREEN,WHITE) circularly and form a pattern
//PRE: The time of delay and number of circle
//POST: The 4 light is blinked for (time) milliseconds each circularly in (circle) of times
/////////////////////////////////////////////////////////////////////////////////////////
void RotateLight(int time, int circle) {
    int i = 0;
    CounterBlink();
    for (; i < circle; i++) {
        bcm2835_gpio_write(REDLIGHT, HIGH);
        delay(time);
        bcm2835_gpio_write(REDLIGHT, LOW);
        delay(time);
        bcm2835_gpio_write(YELLOWLIGHT, HIGH);
        delay(time);
        bcm2835_gpio_write(YELLOWLIGHT, LOW);
        delay(time);
        bcm2835_gpio_write(GREENLIGHT, HIGH);
        delay(time);
        bcm2835_gpio_write(GREENLIGHT, LOW);
        delay(time);
        bcm2835_gpio_write(WHITELIGHT, HIGH);
        delay(time);
        bcm2835_gpio_write(WHITELIGHT, LOW);
        delay(time);
    }
}

void RotateALight(int time, int circle) {
    int i = 0;
    for (; i < circle; i++) {
		bcm2835_gpio_write(WHITELIGHT, HIGH);
        delay(time);
        bcm2835_gpio_write(WHITELIGHT, LOW);
        delay(time);
        bcm2835_gpio_write(GREENLIGHT, HIGH);
        delay(time);
        bcm2835_gpio_write(GREENLIGHT, LOW);
        delay(time);
        bcm2835_gpio_write(YELLOWLIGHT, HIGH);
        delay(time);
        bcm2835_gpio_write(YELLOWLIGHT, LOW);
        delay(time);
        bcm2835_gpio_write(REDLIGHT, HIGH);
        delay(time);
        bcm2835_gpio_write(REDLIGHT, LOW);
        delay(time);
        
        
        
    }
}


/////////////////////////////////////////////////////////////////////////////////////////
//To blink the 4 light (RED,YELLOW,GREEN,WHITE) circularly and indicate winning of the game
//POST: The 4 light is blinked for 20 milliseconds each circularly in 100 of times
/////////////////////////////////////////////////////////////////////////////////////////
void WINBlink() {
	int i;
	for(i=0;i<2;i++){
    RotateLight(40, 8);
    RotateALight(40,7);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//Indicate start of the game and blink all the light to check if the light is valid
//POST: All light is blinked
/////////////////////////////////////////////////////////////////////////////////////////
void StartGame() {
    StartGameSound();
    RotateLight(50, 5);
    RotateALight(50,5);
    WaitStartSound();
    StartYourTurnLightOn();
    StartCorrectLightON();
    StartWrongLightON();
    system("killall omxplayer.bin");
}

/////////////////////////////////////////////////////////////////////////////////////////
//Generate a random sequence of light in specific length
//POST: A random sequence of (length) is generated
/////////////////////////////////////////////////////////////////////////////////////////
void initSequence(enum light sequence[], int length) {
    srand(time(NULL));
    int index = 0;
    for (; index < length; index++) {
        int randColour = rand() % 4;
        sequence[index] = (enum light) randColour;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
//Print the current score of the player in binary form using corresponding lights
//POST: The current score of the player is printed by the binary counter
/////////////////////////////////////////////////////////////////////////////////////////
void printCounter(int rounds) {
    if (rounds > LEVEL_1) {
        rounds %= 15;

    } else if (rounds == LEVEL_1) {
        upgradeSound();
        difficulty++;
        RotateLight(50, 5);
    }

    int bit[4];
    int pos = 0;
    while (pos < 4) {
        bit[pos] = rounds % 2;
        rounds /= 2;
        pos++;
    }
    if (bit[0]) {
        C_0_ON();
    } else {
        C_0_OFF();
    }
    if (bit[1]) {
        C_1_ON();
    } else {
        C_1_OFF();
    }
    if (bit[2]) {
        C_2_ON();
    } else {
        C_2_OFF();
    }
    if (bit[3]) {
        C_3_ON();
    } else {
        C_3_OFF();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
//Print a sequence of light in specific length using its corresponding lights
//POST: A sequence of light is generated
/////////////////////////////////////////////////////////////////////////////////////////
void printSequence(enum light sequence[], int length, int time) {
    int index = 0;
    for (; index < length; index++) {
        switch (sequence[index]) {
            case RED:
                REDLightOn(time);
                break;
            case YELLOW:
                YELLOWLightOn(time);
                break;
            case GREEN:
                GREENLightOn(time);
                break;
            case WHITE:
                WHITELightOn(time);
                break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
//Turn off all the light
/////////////////////////////////////////////////////////////////////////////////////////
void OFFLight() {
    bcm2835_gpio_clr(REDLIGHT);
    bcm2835_gpio_clr(GREENLIGHT);
    bcm2835_gpio_clr(WHITELIGHT);
    bcm2835_gpio_clr(YELLOWLIGHT);
    bcm2835_gpio_clr(CORRECTLIGHT);
    bcm2835_gpio_clr(WRONGLIGHT);
    bcm2835_gpio_clr(YOUR_TURN);
    bcm2835_gpio_clr(COUNTER_0);
    bcm2835_gpio_clr(COUNTER_1);
    bcm2835_gpio_clr(COUNTER_2);
    bcm2835_gpio_clr(COUNTER_3);
}

/////////////////////////////////////////////////////////////////////////////////////////
//To read the input from the player using buttons and turn on the light next to the button
//PRE: A valid input is provided
//POST: The input is stored and the corresponging light is turned on for 500 miiliseconds
/////////////////////////////////////////////////////////////////////////////////////////
enum light ReadInput() {
    int time = 500;
    //the infinite loop take inputs continually
    while (1) {
        if (bcm2835_gpio_eds(RED_BOTTON)) {
            REDLightOn(time);
            bcm2835_gpio_set_eds(RED_BOTTON);
            return RED;
        }
        if (bcm2835_gpio_eds(GREEN_BOTTON)) {
            GREENLightOn(time);
            bcm2835_gpio_set_eds(GREEN_BOTTON);
            return GREEN;
        }
        if (bcm2835_gpio_eds(YELLOW_BOTTON)) {
            YELLOWLightOn(time);
            bcm2835_gpio_set_eds(YELLOW_BOTTON);
            return YELLOW;
        }
        if (bcm2835_gpio_eds(WHITE_BOTTON)) {
            WHITELightOn(time);
            bcm2835_gpio_set_eds(WHITE_BOTTON);
            return WHITE;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
//Initialize the GPIO pins to output
/////////////////////////////////////////////////////////////////////////////////////////
void initOutput() {
    bcm2835_gpio_fsel(WRONGLIGHT, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(CORRECTLIGHT, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(YOUR_TURN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(REDLIGHT, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(YELLOWLIGHT, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(GREENLIGHT, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(WHITELIGHT, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(COUNTER_0, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(COUNTER_1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(COUNTER_2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(COUNTER_3, BCM2835_GPIO_FSEL_OUTP);
}

/////////////////////////////////////////////////////////////////////////////////////////
//Initialize the GPIO pins to input
/////////////////////////////////////////////////////////////////////////////////////////
void initInput() {
    bcm2835_gpio_fsel(RED_BOTTON, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(RED_BOTTON, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_len(RED_BOTTON);
    bcm2835_gpio_fsel(YELLOW_BOTTON, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(YELLOW_BOTTON, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_len(YELLOW_BOTTON);
    bcm2835_gpio_fsel(WHITE_BOTTON, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(WHITE_BOTTON, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_len(WHITE_BOTTON);
    bcm2835_gpio_fsel(GREEN_BOTTON, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(GREEN_BOTTON, BCM2835_GPIO_PUD_UP);
    bcm2835_gpio_len(GREEN_BOTTON);

}


int main(int argc, char **argv) {

    //The infinite loop is to restart the game once the player lose
    while (1) {

        //Initialise the library by opening /dev/mem and getting pointers to the internal memory for BCM 2835 device registers
        bcm2835_init();
        //if the library can't be initialise, the program terminate
        if (!bcm2835_init()) {
            return 1;
        }
        //Initialise the game state, reserve memory for sequence and input
        enum light sequence[MAX_NUMBER_OF_LIGHT];
        enum state gamestate = WAIT;
        enum light input;
        //first round
        int round = 1;
        //Initialise the blinking time to be 450 milliseconds
        int time = INIT_BLINKING_TIME - difficulty * SCALE_OF_DIFF;

        //Turn off all light
        OFFLight();
        //set the GPIO pin to input or output
        initOutput();
        initInput();
        //generate a random sequence of light
        initSequence(sequence, MAX_NUMBER_OF_LIGHT);
        //start the game by printing a starting light sequence
        StartGame();

        while (gamestate != WRONG) {
            //print the sequence of the light generated
            printSequence(sequence, round, time);
            //initialise the current position to 0
            int pos = 0;
            //The your turn light turned on indicate, it is the player's turn
            YourTurnLightOn();
            while (gamestate == WAIT) {
                if (pos == round) {
                    //The player input correctly and the correct light is on
                    CorrectLightON();
                    //print the current score
                    printCounter(round);
                    //change the game state to correct
                    gamestate = CORRECT;
                    break;
                }
                //read the input from the player and return enum of light
                input = ReadInput();

                //if the current input match with the sequence
                if (sequence[pos] == input) {
                    //move to the next position
                    pos++;
                } else {
                    //The input didn't match the sequence
                    gamestate = WRONG;
                }
            }
            if (gamestate == CORRECT) {
                //increment the round and change the game satate
                round++;
                gamestate = WAIT;
            } else if (gamestate == WRONG) {
                //The program will terminate and restart after the wrong indicating light blinks
                EndSound();
                WrongLightON();
                difficulty = 0;
            }
            if (round >= LEVEL_2) {
                //The player win level 2 and anf win the game
                WinSound();
                WINBlink();
                break;
            }
        }
        delay(5000);
        system("killall omxplayer.bin");
        //turn off all the light and wait for restart
        OFFLight();
        //close the library, deallocating any allocated memory and closing /dev/mem
        bcm2835_close();
        
    }

    return 0;
}

