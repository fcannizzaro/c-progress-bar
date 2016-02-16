#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
#include <string.h>
#include "progressbar.h"

void screenSize(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
};

void moveCursorFromTo(int moreH, int moreV, bool fromPos){
	
	int x,y;

	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		x = csbi.dwCursorPosition.X;
		y = csbi.dwCursorPosition.Y;
	}

	COORD coord;
	coord.X = (fromPos ? x : 0) + moreH;
	coord.Y = (fromPos ? y : 0) + moreV;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, coord);

}

void printHUI(ProgressBar bar, int more){
	
	int counter = 0;

	while(counter++ < columns/2 - bar.width/2 + more)
		printf(" ");

}

void printVUI(ProgressBar bar, bool space){

	int counter = 0;
	
	if(space){

		while(counter++ < rows/2 - 4)
			printf("\n");
		
	}
	else{
		
		printf("\n");

		printHUI(bar, 0);

		while(counter++ < bar.width)
			printf("_");

		printf("\n");
	}
}


void printCenterText(char * text){

	int counter = 0;

	while(counter++ < columns/2 - strlen(text)/2 )
		printf(" ");

	printf("%s\n", text);

}

void fn_setBackground(ProgressBar * bar, char background){
	bar->colors[6] = background;
}

void fn_setForeground(ProgressBar * bar, char foreground){
	bar->colors[7] = foreground;
}

void fn_setBarColor(ProgressBar * bar, char barcolor){
	bar->barcolor =  ((unsigned)(barcolor- '0')<<4)|(unsigned)(barcolor-'0')|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY;
}

void fn_setProgress(ProgressBar * bar, int progress){

	bar->progress = progress;

	if(progress >= bar->max){	

		SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), currentConsoleAttr);
		moveCursorFromTo( -bar->width , 4, true );

		if(bar->onEndProgress != NULL)
			bar->onEndProgress(*bar);
	}
	else if(! ( progress % (bar->max/bar->width) ) )
		printf(bar->barcolor == -1 ? "|" : " ");

}

void fn_setMax(ProgressBar * bar, int max){
	bar->max = max;
}

void fn_setSize(ProgressBar * bar, int width){
	bar->width = width < columns ? width : columns-20;
}

void fn_setText(ProgressBar * bar, char * text){
	strcpy(bar->text, text);
}

void fn_setOnEndProgress(ProgressBar * bar , void (*f)(ProgressBar bar) ){
	bar->onEndProgress = f;
}

void getDefaultConfig(bool start){

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	
	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)){
		
		if(start)
			startConfig = csbi.wAttributes;
		else
			currentConsoleAttr = csbi.wAttributes;

	}

}

void fn_show(ProgressBar bar){

	system("cls");
	printVUI(bar,true);
	getDefaultConfig(true);
	system(bar.colors);

	if(strcmp(bar.text , "") != 0)
		printCenterText(bar.text);

	printVUI(bar,false);
	printf("\n");
	printHUI(bar, 1);
	printVUI(bar,false);
	moveCursorFromTo( columns/2 - bar.width/2 , -2, true );

	getDefaultConfig(false);

	if(bar.barcolor != -1)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bar.barcolor);

}

void fn_clearWithAnimation(int animation ,int ms){

	int i,j;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), startConfig);
	moveCursorFromTo(0,0,false);

	if(animation == 0){

		for(j = 0; j < rows; j++){

			for (i = 0; i < columns; i++){
				
				if(j&1)
					moveCursorFromTo(columns-i-2,j,false);

				printf("  ");
				i++;	
				Sleep(ms != 0 ? ms : 4);
			}

			if(j&1)
				moveCursorFromTo(0,j,false);

			if(j == rows-2)
				system("Color 07"); 

			printf("\n");

		}

	}

	else{



		char line[columns+1];

		for (i = 0; i < columns; ++i)
			line[i] = ' ';

		line[i] = '\0';

		for ( i = 0; i < rows; i++){

			printf(line);
			Sleep(ms != 0 ? ms : 4);

		}

	}


	system("Color 07"); 
	moveCursorFromTo(0,0,false);
}

ProgressBar ProgressBarBuilder(){
	screenSize();
	ProgressBar bar;
	bar.max = 0;
	bar.progress = 0;
	bar.setProgress = fn_setProgress;
	bar.setMax = fn_setMax;
	bar.setSize = fn_setSize;
	bar.setText = fn_setText;
	bar.show = fn_show;
	bar.setOnEndProgress = fn_setOnEndProgress;
	bar.setForeground = fn_setForeground;
	bar.setBackground= fn_setBackground;
	bar.setBarColor = fn_setBarColor;
	bar.onEndProgress = NULL;
	bar.clearWithAnimation = fn_clearWithAnimation;
	bar.barcolor = -1;
	char colors[] = {'C','o','l','o','r',' ', BLACK , WHITE, '\0'};
	strcpy(bar.colors, colors);
	strcpy(bar.text, "");
	return bar;
}