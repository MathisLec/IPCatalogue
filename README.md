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
You can choose among 3 options:
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
### Structure
In order to have an easy way to treat IP addresses, we have implemented a structure IP that contain the IP address in different formats (decimal, binary and hexadecimal), in string representation, and the "type" of the address. It is located in IP.h. you can also find the "type" enumeration that define which value an IP type can get.

To facilitate the development of the application, a function in IP.c produce an IP object from an IP string representation that must follow this typo: "xxx.xxx.xxx.xxx/yy" which "x" fields are the number of doted part and "y" the mask in number representation.

The details of the functions are mentionned as a "JavaDoc" style documentation in the files.
### Import/Save
We integrate a save system to import and export IPs from a file. The saved IPs are stored in "save.csv" file in the root directory of the executable. We chose the CSV format in order if the user wants to re-use it. The first line of the file is the number of IP in the file. From the second line to the EOF, we have all IPs in "xxx.xxx.xxx.xxx/yy" format separated with '\n' character. We have managed main I/O errors with the file in the code.

### Add address
When the user type '1', the prompt indicate that the user must enter an IP. When done, the save file is refreshed to include the new IP.

### IP Filtering
The filtering is performed when user type '2' in the prompt and when he type a mask to filter with. The filtering don't save data by default to let the choice to the user to save that filtering or not. The user must save by himself by typing '3' in the prompt. The filtering is performed by comparing the binary representation of the mask bit to bit.

### Address type determination
The "type" of the IP is fixed first if it is a network, broadcast or loopback address, then, if it is a public or private address. We based our IP type determination on this document: https://phoenixnap.com/kb/public-vs-private-ip-address. This document regroup main ranges attributed to public IP in the "Public IP Ranges" section. If the IP is not between those ranges, it is considered as private.

### Disclamer
There are not a complete error management, so you could encounter some bugs but in the traditional way to use our tool, it could be ok. For example when the prompt ask you to enter an IP like "192.168.0.1/24", please don't try to enter "192.168.0.1/11111111.11111111.11111111.00000000", it will crash the program.
