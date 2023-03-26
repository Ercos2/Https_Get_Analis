# Https_Get_Analis

## Project Description
A shared library and a CLI utility for it (main), which:
1) receives lists of binary packages of 2 branches. For example, sisyphus and p10.
2) makes a comparison of the received package lists and outputs JSON, which will display:
- all packages that are in the 1st but not in the 2nd
- all packages that are in the 2nd but are not in the 1st
- all packages whose version-release is greater in the 1st than in the 2nd

## How to Install and Run the Project
The project is installed and launched via Qt Creator. Open the Get_analis.pro file in the editor, set the required values in the first_branch and second_branch fields in main, and start building and compiling the program.

## How to Use the Project
In the first_branch and second_branch fields, you must set the values ​​to choose from (from the list: "sisyphus", "p10", "p9", "p8", "c9f2", "c9f1", "c8.1", "c8", "c7 ", "icarus") and run the program, then you will get the result.

### P.S. 
the project files were not sorted into folders so as not to face cross-platform restrictions.