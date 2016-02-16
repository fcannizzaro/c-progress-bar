#include <stdio.h>
#include <windows.h>
#include "bin/progressbar.h"

void end(ProgressBar bar){
	printf("Completed %d%%!" , bar.progress);

	Sleep(2500);
	bar.clearWithAnimation(ANIMATION_VERTICAL,6);
	printf("\n > Do other things! :)");
}

DWORD WINAPI ThreadFunc(void* data) {

	int progress = 0;
	ProgressBar bar = ProgressBarBuilder();

	bar.setBackground(&bar, BRIGHT_BLUE );
	bar.setForeground(&bar, BRIGHT_WHITE);
	bar.setBarColor(&bar, BAR_WHITE);

	bar.setMax(&bar,100);
	bar.setSize(&bar, 50);
	bar.setText(&bar,"Loading Data...");
	bar.setOnEndProgress(&bar,end);
	bar.show(bar);

	while(progress <= bar.max){
		bar.setProgress(&bar, progress++);
		Sleep(20);
	}

	return 0;

}

int main(){

	HANDLE thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
	getchar();
	SuspendThread(thread);
	main();

}
