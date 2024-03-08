# cpp-tictactoe

Unwinnable Tic-Tac-Toe game in c++. The program precalculates best moves for an AI.

# Installation

To compile ttt.cpp on Linux, use one of those commands:

```g++ ttt.cpp -o ttt -O3 -s```
or
```clang++ ttt.cpp -o ttt -O3 -s```

(Hint: Don't forget to remove system("CLS"))

To get Windows version, go to the release tab and download one of the files (ttt.cpp or tttc.cpp). If you want to compile it on Windows, setup MSYS2 environment and add your compiler to the PATH, then locate your file in cmd and enter this command: ```g++ ttt.cpp -o ttt -O3 -s```

# Usage

To submit a move to an AI enter 1-9 on your keyboard.

# Features

Nothing really special, just simple precalculations. More like a school project. Unfortunately I couldn't get it working without explicitly setting some values in array. Unlike the previous implementation, this one doesn't really feature any special optimizations or things, but it still was pretty funny to optimize random approach. You can still check out those versions in previous commits.
