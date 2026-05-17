# Text Editor Project 
  A basic TUI text editor written entirely in C++ for linux :))))
---
## What it can do :) 
  - Open and write onto text files
  - Move the cursor using arrow keys
  - Create a new file and write to it if file path specified does not exist yet
  - **Ctrl + C** to enter command mode 
	- "w [filepath]" to write to file. If no path is specified, it will write to latest opened file.  
	- "o [filepath]" to open a file.
	- "q" to exit the program.

## Known problems / limitations :( 
  - Can't maintain column position of cursor when moving up and down
  - No line numbers
  - No scrolling (Amount of text on screen depends on the size of the your terminal window)
  - prints out 'ctrl + [character]' and 'alt + [character]' 

## How to Build and Run 
  ### Install Dependencies  

  - clone google test :  ` git clone https://github.com/google/googletest.git `
  - install the ncurses library :  
    * Debian / Ubuntu : ` sudo apt install libncurses5-dev libncursesw5-dev `
    * Fedora : ` sudo dnf install ncurses-devel ` 
    * Arch : ` sudo pacman -S ncurses ` 
  - install CMake : 
    * Debian / Ubuntu : ` sudo apt install cmake`
    * Fedora : ` sudo dnf install cmake gcc-c++ make ` 
    * Arch : ` sudo pacman -S cmake ` 

  ### Build and Run 
  
  - rename googletest : ` mv googletest gtest `
  - make build folder : ` mkdir build && cd build`
  - build : ` cmake .. ` ` cmake --build . `
  - go to app directory and run : ` cd src/main && ./app ` 
