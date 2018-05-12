#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
#include <time.h>
#define MAXWORDS 100
#define WORDLEN 13
#define width 120
#define height 120

int readWords(char* wl[MAXWORDS], char* filename);
void trimws(char* s) ;
void insertWord(char array[width][height],char* wordlist[MAXWORDS], int D, int x, int y, int wordcount);

int main(int argc, char* argv[]){
	int direction;
	int i,j,x,y;
	int k=0;
	int random=0;
	int wordCount;
	int across=0;
	int h=0;
	int startx=0;
	int starty=0;
	int tempx;
	int tempy;
	int spacecheck=1;
	char c;
	char answers[width][height];
	char puzzle[width][height];
	char words[width][height];
	char* wordlist[MAXWORDS];
	
	
	printf("What is the dimension? Width then Height.\n");
	scanf("%d",&x);
	scanf("%d",&y);
	
	if (x>width){
		x=width;
	}
	if (y>height){
		y=height;
	}
	
	
	srand(time(NULL));
	wordCount = readWords(wordlist, argv[1]);

	
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			answers[i][j]=' ';
		}
	}
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			words[i][j]=' ';
		}
	}
		
	for(i=0;i<wordCount;i++){
		for(j=0;j<WORDLEN;j++){
			if(wordlist[i][j]!='\0'){
				words[i][j]=wordlist[i][j];
			}
		}
	}


	for(i=0;i<wordCount;i++){
		spacecheck=1;
		for(k=0;k<100 && spacecheck==1;k++){
			spacecheck=0;
			startx = rand()%(x-WORDLEN);
			starty = rand()%(y-WORDLEN);
			tempx = startx;
			tempy = starty;
			random = rand()%3;
			for(h=0;h<WORDLEN;h++){
				if(random==0){
					if(answers[tempy][tempx]!=' '){
						spacecheck=1;
					}
					tempx=tempx+1;
				}
				else if(random==1){
					if(answers[tempy][tempx]!=' '){
							spacecheck=1;
					}
					tempx=tempx+1;
					tempy=tempy+1;
				}
				else if(random==2){
					if(answers[tempy][tempx]!=' '){
						spacecheck=1;
					}
					tempy=tempy+1;
				}
			}
		}
		for(j=0;j<WORDLEN && words[i][j]!='!'&& spacecheck==0;j++){
			if(random==0){
				answers[starty][startx]=words[i][j];
				startx=startx+1;
			}
			else if(random==1){
				answers[starty][startx]=words[i][j];
				startx=startx+1;
				starty=starty+1;
			}
			else if(random==2){
				answers[starty][startx]=words[i][j];
				starty=starty+1;
			}
		}
	}
	printf("\n\nANSWER KEY:\n");
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			printf("%c",answers[i][j]);
		}
		printf("\n");
	}
	printf("PUZZLE:\n");
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			puzzle[i][j]=answers[i][j];
			if(puzzle[i][j]==' '){
				c = 'A' + (rand() % 26);
				puzzle[i][j]=c;
			}
			printf("%c",puzzle[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}


int readWords(char* wl[MAXWORDS], char* filename) {
	int numread =0;
	char line[WORDLEN];
	char *p;
	
	FILE* fp = fopen(filename,"r");
	
	while (!feof(fp)) {
		p  =fgets(line, WORDLEN, fp);
		if (!feof(fp) && p !=NULL) {
			trimws(line);
			wl[numread] = (char *)  malloc(strlen(line)+1);
			strcpy(wl[numread], line);
			numread++;
			}
		} 
	fclose(fp);
	return numread;	
}


	
void trimws(char* s) {
	int len = strlen(s) ;
	int x;
	if (len ==0) {
		return;
	}
	x = len-1;
	while (isspace(s[x]) && (x>=0)) {
		s[x] = '!';
		x--;
	}
}