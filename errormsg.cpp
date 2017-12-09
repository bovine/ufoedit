// Ufoedit
// Copyright (c) 1996, Jeff Lawson <jeff@bovine.net>
// All rights reserved.
// See LICENSE for distribution information.

#include "ufoedit.hpp"

//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
void no_memory (void)
{
    if (activemouseclass) delete activemouseclass;
    if (activescreenclass) {activescreenclass->registerfarewell(NULL); delete activescreenclass;}
    cout << "Insufficient free conventional memory to run program. Try\n"
            "removing any unnecessary TSR programs and then run this\n"
            "program again.\n";
    exit(1);
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
void no_mouse (void)
{
    if (activemouseclass) delete activemouseclass;
    if (activescreenclass) {activescreenclass->registerfarewell(NULL); delete activescreenclass;}
    cout << "This program requires a mouse to be installed in the system.\n"
            "If a mouse is already installed, make sure that you also\n"
            "load an appropriate Microsoft compatible mouse driver.\n";
    exit(1);
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
void no_display (void)
{
    if (activemouseclass) delete activemouseclass;
    if (activescreenclass) {activescreenclass->registerfarewell(NULL); delete activescreenclass;}
    cout << "Cannot identify monitor installed in the system.  At least\n";
            "a monochrome monitor is required, however a VGA monitor is\n";
            "recommended for best results.\n";
    exit(1);
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
void no_games (void)
{
    if (activemouseclass) delete activemouseclass;
    if (activescreenclass) {activescreenclass->registerfarewell(NULL); delete activescreenclass;}
    cout << "No saved games found in current directory.  Please make sure\n"
            "that you have put this program into your main UFO directory\n"
            "and are running it from that location.\n";
    exit(1);
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
void file_error (void)
{
    if (activemouseclass) delete activemouseclass;
    if (activescreenclass) {activescreenclass->registerfarewell(NULL); delete activescreenclass;}
    cout << "Error accessing saved game or other data file.\n";
    exit(1);
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
void bad_crc (void)
{
    if (activemouseclass) delete activemouseclass;
    if (activescreenclass) {activescreenclass->registerfarewell(NULL); delete activescreenclass;}
    cout << "Load Checksum Error\n";
    exit(1);
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
void no_copies (void)
{
    if (activemouseclass) delete activemouseclass;
    if (activescreenclass) {activescreenclass->registerfarewell(NULL); delete activescreenclass;}
    cout << "Internal program error!  Attempt to create another non-reentrant class.\n";
    exit(1);
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
