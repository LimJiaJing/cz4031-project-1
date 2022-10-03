# cz4031-project-1
This repository contains the implementation for project 1 of "Database Systems Principles" (CZ/CE4031) and the project manual which explains the project's requirements. 

# Installation
We have provided two ways to run the program
1. Run the windows executable file (.exe)
2. Compile the source code and run
Note: All CLI are for windows machine. For other OS, modify based on their Terminal Language.

## 1. Windows executable file

1. Download repository
2. Extract files from the downloaded zip file (cz4031-project-1.zip)
3. Enter the directory `cz4031-project-1` 
4. Double click main.exe  
Note: This method only works on windows 10 machines


## 2. Compile source code and run (for Windows)

1. Ensure you have a c++ compiler installed.
    * The compiler can be installed from [here](https://www.msys2.org/)
    * Please follow the guide from the above link to install. Make to run from the terminal for the `MINGW64 environment`:   
        ```
        pacman -S mingw-w640x86_64-gcc
        ```
    * Type `gcc --version` in terminal to check if you have the compiler installed
2. Download the repository
2. Extract files from the downloaded zip file (cz4031-project-1.zip)
3. Enter the directory `cz4031-project-1` 
4. Launch terminal in current directory (`cz4031-project-1`)
5. Type the following in the terminal:  
```
g++ main.cpp -o main
main
```
* Make sure the executable from the compilation has permission to execute. You can check by 
    1. right-clicking the file (main.exe)
    2. left-click properties
    3. click on the security tab
    4. ensure the `Read & execute` permission is allowed.




