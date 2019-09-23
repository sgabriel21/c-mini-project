#include <pthread.h>
#include <conio.h>
#include <unistd.h>
#include <stdio.h>

unsigned char gchRobotCmdStatus;
int currentX, currentY;

	
void getMaze(){
FILE *fp;
char line;
int length = 0, i;
char *size;
char *maze;
char *column;
char *startX;
char *startY;
char *endX;
char *endY;

int row, mazeColumn, x, y, pointer;
int MOV_END = 0;
int point = 0;
fp = fopen("maze.txt", "r");
if (fp == NULL){
	printf("Maze file is empty.\n");
	return 1;
}


size = (char*) malloc(sizeof(char)*length);
maze = (char*) malloc(sizeof(char)*length);
column = (char*) malloc(sizeof(char)*length);
startX = (char*) malloc(sizeof(char)*length);
startY = (char*) malloc(sizeof(char)*length);
endX = (char*) malloc(sizeof(char)*length);
endY = (char*) malloc(sizeof(char)*length);
	
	
if(fp != NULL){
	fgets(size, 40, fp);
	fgets(maze, 40, fp);
	fgets(column, 40, fp);
	fgets(startX, 3, fp);
	fgets(startY, 4, fp);
	fgets(endX, 3, fp);
	fgets(endY, 4, fp);
	printf("The size of maze is: %sThe maze data is: %sThe number of columns is: %s", size, maze, column);
	printf("The starting coordinate is: %s %s", startX, startY);
	printf("The ending coordinate is: %s %s\n", endX, endY);
}
	
row = atoi(size);
mazeColumn = atoi(column);

printf("\nThe maze is: \n");
for (x = 0; x<= row/mazeColumn; x++){
	for(y = 0; y< mazeColumn; y++){
		printf("%c", maze[pointer]);
		pointer++;
	}
	printf("\n");
} 
return startX;
return startY;
return endX;
return endY;
	
fclose(fp);
}

void getMove(){
	gchRobotCmdStatus = gchRobotCmdStatus - 48;
	int direction = gchRobotCmdStatus & 24;
	
	if (gchRobotCmdStatus == 0){
		currentY =- 1;
	} 
	if (gchRobotCmdStatus == 8){
		currentY =+ 1;
	}
	if (gchRobotCmdStatus == 24){
		currentX =- 1;
	}
	if (gchRobotCmdStatus == 16){
		currentX =+ 1;
	}
	
	if(currentX == endX && currentY == endY){
		gchRobotCmdStatus = gchRobotCmdStatus | 32) 
	}
}

void unsetCMD_TX(){
	gchRobotCmdStatus=gchRobotCmdStatus-48;
	int newStatus = gchRobotCmdStatus - 128;
	gchRobotCmdStatus=newStatus+48;
}

void *robotThread(){
	currentX = startX;
	currentY = startY;	
	endX = endX;
	endY = endY;
	while (gchCmdStatus&32 != 32){
		getMaze();
		getMove();
		unsetCMD_TX();	
	}
	
}


int main () {
	pthread_t thread_id;
	/*Create Control Thread*/
    pthread_create(&thread_id, NULL, robotThread, NULL); 
    pthread_join(thread_id, NULL); 
    printf("\nDone Robot Thread\n"); 
	return 0;
}
