#include <pthread.h>
#include <conio.h>
#include <unistd.h>
#include <stdio.h>


unsigned char gchRobotCmdStatus;
char * game;
void askInput(){
	/*Ask input from user*/
	gchRobotCmdStatus = '0';
	char userInput;
	userInput = 'Q' ;
	printf("\nMOVEMENTS:\nNorth [N]\nSouth [S]\nEast [E]\nWest [W]\n\nInput Move:\n");
	while(!(userInput == 'N' || userInput == 'S' || userInput == 'E' || userInput == 'W')){
		scanf("%c",&userInput);
	}
	
	switch(userInput){
		case 'N':
			gchRobotCmdStatus=gchRobotCmdStatus|'0';
			setDirection(0);
			break;
		case 'S':
			setDirection(8);
			break;
		case 'E':
			setDirection(16);
			break;
		case 'W':
			setDirection(24);
			break;
		default:
			printf("Not Valid");
	}
}

void setDirection(int direct){
	/*Set direction; convert char to int and apply bitwise OR then convert back to char*/
	gchRobotCmdStatus=gchRobotCmdStatus-48;
	int newStatus = gchRobotCmdStatus | direct;
	gchRobotCmdStatus=newStatus+48;
	
}
void setCMD_TX(){
	gchRobotCmdStatus=gchRobotCmdStatus-48;
	int newStatus = gchRobotCmdStatus | 128;
	gchRobotCmdStatus=newStatus+48;
}
void printBinary(){
	/*Just for printing the status in binary form*/
	int n = gchRobotCmdStatus-48;
	int c,k;
	printf("\nBinary Form:");
	for (c = 7; c >= 0; c--){
    	k = n >> c;
    	if (k & 1)
      		printf("1");
    	else
      		printf("0");
  	}	
}

void checkMOV_END_ERR(){
	int n = gchRobotCmdStatus-48;
	int c,k;
	for (c = 7; c >= 0; c--){
    	k = n >> c;
    	if (k & 1){
    		/*1*/
    		if(c==6){
    			game="wall";
			}
			else if(c==5){
				game="end";
			}
		}
		else{	/*0*/
			if(c==5){
				game="proceed";
			}	
		}	
  	}
}

void *controlThread(void *vargp) 
{
	while(game!="end"){
		askInput();
    	setCMD_TX();
    	sleep(5);
		checkMOV_END_ERR();
    	printBinary();
    	if(game=="wall"){
    		printf("\nHit a wall! Try another Direction.");
		}
		else if(game=="proceed"){
			printf("\nStill a long way to go! Input direction.");
		}
	}
    printf("Maze Solved!");
    return NULL; 
}


  


int main () {
	pthread_t thread_id;
	/*Create Control Thread*/
    pthread_create(&thread_id, NULL, controlThread, NULL); 
    pthread_join(thread_id, NULL); 
    printf("\nDone Control Thread\n"); 
	return 0;
}

