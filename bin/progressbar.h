#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#define ANIMATION_ZIG_ZAG 0      
#define ANIMATION_VERTICAL 1 

#define BLACK '0'       
#define BLUE '1'        
#define GREEN '2'     
#define CYAN '3'      
#define RED '4'       
#define PURPLE '5'   
#define YELLOW '6'     
#define WHITE '7'       
#define GRAY '8'
#define BRIGHT_BLUE '9'
#define BRIGHT_GREEN 'A'
#define BRIGHT_CYAN 'B'
#define BRIGHT_RED 'C'
#define BRIGHT_PURPLE 'D'
#define BRIGHT_YELLOW 'E'
#define BRIGHT_WHITE 'F'

#define BAR_BLACK BLACK       
#define BAR_BLUE BLUE         
#define BAR_GREEN GREEN     
#define BAR_CYAN CYAN
#define BAR_RED RED     
#define BAR_PURPLE PURPLE   
#define BAR_YELLOW YELLOW
#define BAR_WHITE WHITE       
#define BAR_GRAY GRAY

typedef void (*Listener)();

typedef struct ProgressBar{

	int progress;
	int max;
	char text[50];
	int width;
	char colors[9];
	int barcolor;
	void (*setProgress)(struct ProgressBar * self, int progress ); 
	void (*setMax)(struct ProgressBar * self, int max ); 
	void (*setSize)(struct ProgressBar * self, int width); 
	void (*setText)(struct ProgressBar * self, char * text); 
	void (*setBackground)(struct ProgressBar * self, char background); 
	void (*setForeground)(struct ProgressBar * self, char foreground); 
	void (*setBarColor)(struct ProgressBar * self, char barcolor); 
	void (*show)(struct ProgressBar self); 
	void (*clearWithAnimation)(int animation,int ms); 
	void (*setOnEndProgress)(struct ProgressBar * bar , void (*f)(struct ProgressBar bar) );
	Listener onEndProgress;

} ProgressBar;

int columns, rows;
WORD currentConsoleAttr, startConfig;

ProgressBar ProgressBarBuilder();

#endif
