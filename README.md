# C Progress Bar
Simple Animated ProgressBar (Terminal | Windows)

## Preview
![Preview](https://github.com/FrancisCan/CProgressBar/blob/master/preview/preview.gif)
![Preview](https://github.com/FrancisCan/CProgressBar/blob/master/preview/preview1.gif)

## Simple Usage
import "lib/progressbar.h" and execute code inside a Win Thread ( [see example](https://github.com/FrancisCan/CProgressBar/blob/master/example.c) )


## Compile and Link library
```bash
gcc sample.c bin/progressbar.c
```

## Methods
```C

// define onProgressEnd function
void end(ProgressBar bar){

     printf("Completed %d%%!", bar.progress);
     Sleep(2500);

     // hide with animation (animation type , animation speed in milliseconds)
     bar.clearWithAnimation(ANIMATION_ZIG_ZAG, 6);

     // do other
}

// create new progressbar
ProgressBar bar = ProgressBarBuilder();

bar.setBackground(&bar, BRIGHT_RED );
bar.setForeground(&bar, BRIGHT_WHITE);
bar.setBarColor(&bar, BAR_WHITE);

bar.setMax(&bar,100); //  [REQUIRED] Max Value of Bar
bar.setSize(&bar, 50); // [REQUIRED] Width of Bar
bar.setText(&bar,"Loading Data...");  // [Optional]
bar.setOnEndProgress(&bar,end); // [Optional] Void Function to execute at the end of progress
bar.show(bar);

// change progress
while(progress <= bar.max){
		bar.setProgress(&bar, progress++);
		Sleep(20);  // pause progress
}
```

## Colors

###### Background and Foreground

* BLACK
* BLUE
* GREEN
* CYAN
* RED
* PURPLE
* YELLOW
* WHITE
* GRAY
* BRIGHT_BLUE
* BRIGHT_GREEN
* BRIGHT_CYAN
* BRIGHT_RED
* BRIGHT_PURPLE
* BRIGHT_YELLOW
* BRIGHT_WHITE

###### Bar Tint

* BAR_BLUE
* BAR_GREEN
* BAR_CYAN
* BAR_RED
* BAR_PURPLE
* BAR_YELLOW
* BAR_WHITE
* BAR_GRAY

## Author
Francesco Cannizzaro francisthemoderator@gmail.com
