// Ufoedit
// Copyright (c) 1996, Jeff Lawson <jeff@bovine.net>
// All rights reserved.
// See LICENSE for distribution information.

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

