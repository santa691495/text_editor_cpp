### Text Editor Project 
  A basic TUI text editor written entirely in C++ :))))
---
## What it can do
  - Open and write onto text files
  - Move the cursor using arrow keys
  - Create a new file and write to it if file path specified does not exist yet
  - **Ctrl + C** to enter command mode - "w [filepath]" to write to file. If no path is specified, it will write to latest opened file.  - "o [filepath]" to open a file.
      - "q" to exit the program.

## How to Build and Run
  # Dependencies 

## Known problems / limitations :(
  - Can't maintain column position of cursor when moving up and down
  - No line numbers
  - No scrolling (Amount of text on screen depends on the size of the your terminal window)
  - prints out 'ctrl + [character]' and 'alt + [character]'
