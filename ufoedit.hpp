// []-----------------------------------------------------------------------[]
// |                                                                         |
// |                                                                         |
// |  This source and its associated executable are copyright by Jeff Lawson |
// |  of JL Enterprises, however some portions of this code may or may not   |
// |  have been originally inspired by other authors and credit is given if  |
// |  due.  You are encouraged to redistribute this package, but you must    |
// |  include all files originally distributed in this archive in their      |
// |  original state and format and without modifications of any kind.       |
// |  Under no circumstances may you make modifications to this product and  |
// |  redistribute the resulting code or executables.  If you believe you    |
// |  have made some useful or otherwise important enhancements and you      |
// |  would like to share these changes with others, please contact the      |
// |  author through one of the methods listed below.  Additionally, no      |
// |  fees may be charged for the usage of this product by anyone other than |
// |  the author of this file, except for fees (not to exceed US $10) by     |
// |  disk distributors to cover disk duplication and handling.  If there    |
// |  is any need to question this policy, please contact the author.        |
// |  This source code and its executable are distributed without any kind   |
// |  of warranty and the author may not be held accountable for damages of  |
// |  any kind.                                                              |
// |                                                                         |
// |                                                                         |
// |  I can reached via postal mail at:                                      |
// |                                                                         |
// |          Jeff Lawson                                                    |
// |          1893 Kaweah Drive                                              |
// |          Pasadena, CA 91105-2174                                        |
// |          USA                                                            |
// |                                                                         |
// |  or through E-mail at:                                                  |
// |                                                                         |
// |          jlawson@hmc.edu    or   JeffLawson@Aol.Com                     |
// |                                                                         |
// |  also via phone at:                                                     |
// |                                                                         |
// |          (213) 258-5604     or   (213) 258-4264                         |
// |                                                                         |
// []-----------------------------------------------------------------------[]

#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <dir.h>
#include <string.h>
#include <iostream.h>
#include <ctype.h>
#include "mouse.hpp"
#include "screen.hpp"
#include "colors.hpp"
#include "button.hpp"
#include "menubox.hpp"
#include "textbox.hpp"
#include "txtinput.hpp"
#include "checkbox.hpp"
#include "dropdown.hpp"
#include "stealth.h"

#define REGFILE "UFOEDIT.REG"
#define REGCODE "04QZE77M2A"
#define APPNAME "UFOEDIT"

// []-------------------------[]
// |  define any other macros  |
// []-------------------------[]
#define TRUE 1
#define FALSE 0

// []----------------------[]
// |  define external data  |
// []----------------------[]
extern far char Farewell[];


// []----------------------------------------[]
// |  prototype all error messages we'll use  |
// []----------------------------------------[]
void no_memory (void);
void no_games (void);
void file_error (void);
void bad_crc (void);


// []-------------------------[]
// |  prototype all functions  |
// []-------------------------[]
int file_exists (char *filename);
int main_screen (void);
int select_function (void);
void money_edit (int savedgame);
int select_base(int savedgame);
void edit_inventory(int savedgame, int base);
int quantity_edit (int initial);
void edit_buildings(int savedgame, int base);
void edit_soldiers(int savedgame);
void stat_edit (unsigned &initial, unsigned minimum, unsigned maximum, \
    char *text, unsigned minmax);

