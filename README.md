# cz4031-project-1
This repository contains the implementation for Project 1 of "Database Systems Principles (CZ/CE4031)". 

# Requirements
* C++ Standard Library is installed
* A C++ compiler installed
    * Instructions in this guide use g++  
    * Any C++ compiler will work
* Refer to [guide](#install-requirements) to install the required files (only if not yet installed)

# Installation
Two ways to run the program
1. Run the windows executable file (.exe)
    * Only works for Windows 10 machine  
  2. Compile the source code and run


## 1. Windows executable file

1. Extract files from zip file `cz4031-project-1.zip`  
2. Enter directory `cz4031-project-1`
3. Double click `main.exe` to run the program  

![image](images/Run%20program.png)

Note:
* This method only works on Windows 10 machines  

* Make sure `main.exe` has permission to execute. You can check by:   
    1. Right-click the file (main.exe)
    2. Left-click properties
    3. Left-click the security tab
    4. Ensure the `Read & execute` permission is allowed.

## 2. Compile source code and run

1. Extract files from the zip file `cz4031-project-1.zip`  
3. Enter the directory `cz4031-project-1` 
4. Launch terminal in current directory
5. Compile the program
    ```bash
    g++ main.cpp -o main
    ```
6. Run the program
    ```bash
        main
    ```  

![image](images/Compile%20and%20run%20program.png)  
Note:
* All CLI used here are for Windows machine. For other OS, modify correspondingly.  

* Ensure the executable from the compilation (main.exe) has permission to execute. You can check by: 
    1. Right-click the file (main.exe)
    2. Left-click properties
    3. Left-click the security tab
    4. Ensure the `Read & execute` permission is allowed.
    


# Appendix
## Install Requirements
1. Download MSYS2 installer [here](https://www.msys2.org/)
2. Run the installer. MSYS2 requires 64-bit Windows 7 or newer.
3. Launch the program and install the required files 
![image](images/Install%20toolchain.png)
4. Add `<Mingw-w64 destination folder>\mingw64\bin` to PATH
    *  Using the default installation settings: `C:\msys64\mingw64\bin`
5. Check compiler has been correctly installed added to PATH
![image](images/Complier%20version.png)



