#include <pthread.h>
#include <conio.h>
#include <unistd.h>
#include <stdio.h>


unsigned char gchRobotCmdStatus;
void askInput(){
	char userInput;
	userInput = 'Q' ;
	printf("MOVEMENTS:\nNorth [N]\nSouth [S]\nEast [E]\nWest [W]\n\nInput Move:\n");
	while(!(userInput == 'N' || userInput == 'S' || userInput == 'E' || userInput == 'W')){
		scanf("%c",&userInput);
	}
	
	switch(userInput){
		case 'N':
			gchRobotCmdStatus='1';
			printf("Code: 00");
			break;
		case 'S':
			/*robotDirection('01')*/
			printf("Code: 01");
			break;
		case 'E':
			/*robotDirection('10')*/
			printf("Code: 10");
			break;
		case 'W':
			/*robotDirection('11')*/
			printf("Code: 11");
			break;
		default:
			printf("Not Valid");
	}
}

void *controlThread(void *vargp) 
{ 
    askInput();
    printf("gchRobotCmdStatus:%c",gchRobotCmdStatus);
    return NULL; 
} 
  


int main () {
	gchRobotCmdStatus = '0000000';
	pthread_t thread_id; 
    printf("Before Thread\n"); 
    pthread_create(&thread_id, NULL, controlThread, NULL); 
    pthread_join(thread_id, NULL); 
    printf("After Thread\n"); 
	return 0;
}

