//
// Created by klc116 on 6/13/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

enum lights{
    RED,
    YELLOW,
    GREEN,
    WHITE
};

enum state{
    CORRECT,
    WRONG,
    WAIT
};

void initSequence(enum lights sequence[], int length) {
    for(int index = 0; index < length; index++) {
        int randColour = rand() % 4;
        sequence[index] = (enum lights) randColour;
    }
}

void printSequence(enum lights sequence[], int length) {
    for(int index = 0; index < length; index++) {
        switch(sequence[index]) {
            case RED:
                printf("R");
                break;
            case YELLOW:
                printf("Y");
                break;
            case GREEN:
                printf("G");
                break;
            case WHITE:
                printf("W");
        }
    }
    printf("\n");
}

void printSequenceDelay(enum lights sequence[], int length,unsigned int delay) {
    for(int index = 0; index < length; index++) {
        switch(sequence[index]) {
            case RED:
                printf("R\n\n\n\n\n");
                sleep(delay);
                break;
            case YELLOW:
                printf("Y\n\n\n\n\n");
                sleep(delay);
                break;
            case GREEN:
                printf("G\n\n\n\n\n");
                sleep(delay);
                break;
            case WHITE:
                printf("W\n\n\n\n\n");
                sleep(delay);
        }
    }
    printf("\n\n\n\n\n\n\n\n");
}
/*
void inputSequence(enum lights in[], char input[], int length) {
    for(int index = 0; index < length; index++) {
        switch(input[index]) {
            case 'R':
                in[index] = RED;
                break;
            case 'Y':
                in[index] = YELLOW;
                break;
            case 'G':
                in[index] = GREEN;
                break;
            case 'W':
                in[index] = WHITE;
        }
    }
}
*/
int main1() {
    srand((unsigned int)time(NULL));

    enum state gameState = WAIT;
    enum lights sequence[100];
    enum lights in[100];
    enum lights input;
    char buffer[100];
    char c;
    int rounds = 1;

    initSequence(sequence, 100);
    printSequence(sequence, 100);
    while(gameState != WRONG) {

        int pos = 0;
        printSequenceDelay(sequence, rounds, 1);

        while(gameState == WAIT) {



//            printf("pos = %d, rounds = %d\n", pos, rounds);
            if(pos == rounds) {
                printf("CORRECT\n");
                gameState = CORRECT;
                break;
            }

            scanf("%c", &c);

            switch (c) {
                case 'R':
                    input = RED;
                    break;
                case 'Y':
                    input = YELLOW;
                    break;
                case 'G':
                    input = GREEN;
                    break;
                case 'W':
                    input = WHITE;
                    break;
                default:
                    continue;
            }

            if(sequence[pos] == input) {
                pos++;
            } else {
                gameState = WRONG;
            }
        }

        if(gameState == CORRECT) {
            rounds++;
            gameState = WAIT;
        } else if(gameState == WRONG) {
            printf("Wrong answer\n");
        }
    }

    printf("Score = %d", rounds);
}