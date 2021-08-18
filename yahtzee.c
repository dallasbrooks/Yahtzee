#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5
#define M 6
#define MP 15

int dice[N] = {0};

const char* moves[MP] = {
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"Sum",
	"Bonus",
	"3 of a kind",
	"4 of a kind",
	"Full House",
	"Small Straight",
	"Large Straight",
	"Yahtzee",
	"Chance"
};
int scores[MP] = {0};
int movecounter[MP] = {0};
int movesleft = MP-2;

void printMoves();
void printDice(int k);
void rollDice();

int evaluateDice(int move){
	int multiples[M] = {0};
	for(int a = 0; a < M; a++){
		multiples[dice[a]-1]++;
	}
	int score = 0;
	int success = 0;
	switch(move){
		case 1:
		//singles
		score += multiples[0] * 1;
		break;
		
		case 2:
		//singles
		score += multiples[1] * 1;
		break;
		
		case 3:
		//singles
		score += multiples[2] * 2;
		break;
		
		case 4:
		//singles
		score += multiples[3] * 3;
		break;
		
		case 5:
		//singles
		score += multiples[4] * 4;
		break;
		
		case 6:
		//singles
		score += multiples[5] * 5;
		break;
		
		case 9:
		//3 of a kind
		for(int a = 0; a < M; a++){
			if(multiples[a] >= 3){
				success++;
			}
		}
		if(success > 0){
			for(int a = 0; a < N; a++){
				score += dice[a];
			}
		}
		break;
		
		case 10:
		//4 of a kind
		for(int a = 0; a < M; a++){
			if(multiples[a] >= 4){
				success++;
			}
		}
		if(success > 0){
			for(int a = 0; a < N; a++){
				score += dice[a];
			}
		}
		break;
		
		case 11:
		//full house
		for(int a = 0; a < M; a++){
			if(multiples[a] == 2 || multiples[a] == 3){
				success++;
			}
		}
		if(success > 1){
			score += 25;
		}
		break;
		
		case 12:
		//small straight
		for(int a = 0; a < M; a++){
			if(multiples[a] > 0){
				success++;
			}
		}
		if(success > 3){
			score += 30;
		}
		break;
		
		case 13:
		//large straight
		for(int a = 0; a < M; a++){
			if(multiples[a] > 0){
				success++;
			}
		}
		if(success > 4){
			score += 40;
		}
		break;
		
		case 14:
		//yahtzee
		for(int a = 0; a < M; a++){
			if(multiples[a] == 5){
				score += 50;
			}
		}
		break;
		
		case 15:
		//chance
		for(int a = 0; a < N; a++){
			score += dice[a];
		}
		break;
		
		default:
		//not valid
		break;
		
	}
	return score;
}

int main(){
	srand(time(NULL));
	int move = 0;
	int goodmove = 0;
	while(movesleft > 0){
		printMoves();
		rollDice();
		printDice(0);
		while(goodmove == 0){
			printf("What is your move?: ");
			scanf("%d", &move);
			if(move > 0 && move < MP+1){
				goodmove = 1;
			}
			if(move == 7 || move == 8 || movecounter[move-1] > 0){
				goodmove = 0;
				printf("Move is no good.\n");
			}
		}
		scores[move-1] = evaluateDice(move);
		movecounter[move-1]++;
		movesleft--;
		goodmove = 0;
	}
	int score = 0;
	for(int a = 0; a < MP; a++){
		score += scores[a];
		if(a < 6){
			scores[6] += scores[a];
			scores[7] = 0;
		}else if(a == 6){
			score = scores[a];
		}
		printf("%s\t%d\n", moves[a], scores[a]);
	}
	printf("Total:\t%d\n", score);
	return 0;
}

void printMoves(){
	for(int a = 0; a < MP; a++){
		if(movecounter[a] == 0 && a != 6 && a != 7){
			printf("%s\t%d\n", moves[a], a+1);;
		}
	}
}

void printDice(int k){
	if(k >= N){
		printf("\n");
		return;
	}
	printf("%d ", dice[k]);
	printDice(k+1);
}

void rollDice(){
	for(int a = 0; a < N; a++){
		dice[a] = rand()%M+1;
	}
}
