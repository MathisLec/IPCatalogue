## Dependencies
### BASH
- cmake
- make

### C
- stdlib.h
- stdio.h
- string.h

## Install
```bash
./install.sh
```
This script will automatically compile and assemble the c files

## Clean
```bash
./clean.sh
```
This script will remove build files and executable

## How to use
This tool can be used with in command line.
To use it, please launch install.sh script, then:
```
./ip_catalog
```
You can choose among 3 options;
1. Rentrer une IP: add an IP in the catalog. The typo is for example: 192.168.0.1/24
2. Filtrer les IP par masque: show you only IP that match with the mask you specified.
3. Quitter: Quit the application. Please, use this option instead of Ctrl-C to keep your memory.

You can just type the number of the option in the prompt and press enter.

## Architecture

in src directory, you can find:
- CMakeLists.txt: the file used by install.sh to compile the project. Do not remove it please.
- commons.h: declare the libraries used in commons.c and functions to be used by the other files.
- commons.c: implements main conversion function between the differents formats of an IP.
- IP.h: declare the libraries used in IP.c, the main structure used in this application, an enumeration of type and functions to be used by the other files.
- IP.c: implements the way to get an IP object, included the allocation, and a free function to free IP objets.
- main.c: the file which contain the main function and manages the command-line interface.

## Functioning

In order to have an easy way to treat IP addresses, we have implemented a structure IP that contain the IP address in different formats (decimal, binary and hexadecimal), in string representation, and the "type" of the address. It is located in IP.h. you can also find the "type" enumeration that define which value an IP type can get.

To facilitate the development of the application, a function in IP.c produce an IP object from an IP string representation that must follow this typo: "xxx.xxx.xxx.xxx/yy" which "x" fields are the number of doted part and "y" the mask in number representation.

The details of the functions are mentionned as a "JavaDoc" style documentation in the files.

There are not a complete error management, so you could encounter some bugs but in the traditional way to use our tool, it could be ok.