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

#define VERSIONTEXT "version 1.2"

#include "ufoedit.hpp"

// []-----------------------[]
// |  all buildings in game  |
// []-----------------------[]
static char building_names[][19] = {"Empty","Access Lift","Living Quarters","Laboratory",\
    "Workshop","Small Radar System","Large Radar System","Missile Defences","General Stores",\
    "Alien Containment","Laser Defences","Plasma Defences","Fusion Ball","Grav shield",\
    "Mind Shield","Psionic Laboratory","Hyper-wave Decoder","Hangar"};
#define TOTAL_BUILDINGS 18


// []------------------------------------------[]
// |  lookup table base identification numbers  |
// []------------------------------------------[]
static int base_id[] = {0,4,5,6,7,8,20,15};


// []---------------------------[]
// |  structure of soldier data  |
// []---------------------------[]
struct soldier_type {
    unsigned rank, location, craft, unknown1;
    unsigned missions, kills, recovery, unknown2;
    char name[26];
    unsigned char time, health, stamina, reactions, strength, firing, \
        throwing, unknown3, psionicstr, psionicsk, bravery;
    unsigned char inctime, inchealth, incstamina, increactions, incstrength, \
        incfiring, incthrowing, unknown4, incbravery, armour, \
        incpsionicsk, intraining, unknown5, unknown6, unknown7;
};


// []---------------------[]
// |  all objects in game  |
// []---------------------[]
static struct object_type {
    char name[21];
    int id;
} objects[] = {{"Stingray Launcher",1},{"Avalanche Launcher",2},{"Cannon",3},\
    {"Fusion Ball Launcher",4},{"Laser Cannon",5},{"Plasma Beam",6},{"Stingray Missile",7},\
    {"Avalanche Missile",8},{"Cannon Rounds (x50)",9},{"Fusion Ball",10},{"Tank/Cannon",11},\
    {"HWP Cannon Shells",94},{"Tank/Rocket Launcher",12},{"HWP Rockets",95},\
    {"Tank/Laser Cannon",13},{"Hovertank/Plasma",14},{"Hovertank/Launcher",15},\
    {"HWP Fusion Bomb",96},{"Pistol",16},{"Pistol Clip",17},{"Rifle",18},{"Rifle Clip",19},\
    {"Heavy Cannon",20},{"HC-AP Ammo",21},{"HC-HE Ammo",22},{"HC-I Ammo",23},\
    {"Auto-Cannon",24},{"AC-AP Ammo",25},{"AC-HE Ammo",26},{"AC-I Ammo",27},\
    {"Rocket Launcher",28},{"Small Rocket",29},{"Large Rocket",30},{"Incendiary Rocket",31},\
    {"Laser Pistol",32},{"Laser Rifle",33},{"Heavy Laser",34},{"Grenade",35},\
    {"Smoke Grenade",36},{"Proximity Grenade",37},{"High Explosive",38},{"Motion Scanner",39},\
    {"Medi-Kit",40},{"Psi-Amp",41},{"Stun Rod",42},{"Electro-Flare",43},{"Elerium-115",61},\
    {"Heavy Plasma",50},{"Heavy Plasma Clip",51},{"Plasma Rifle",52},{"Plasma Rifle Clip",53},\
    {"Plasma Pistol",54},{"Plasma Pistol Clip",55},{"Blaster Launcher",56},\
    {"Blaster Bomb",57},{"Small Launcher",58},{"Stun Bomb",59},{"Alien Grenade",60},\
    {"Mind Probe",62},{"Sectoid Corpse",66},{"Snakeman Corpse",67},{"Ethereal Corpse",68},\
    {"Muton Corpse",69},{"Floater Corpse",70},{"Celatid Corpse",71},{"Silacoid Corpse",72},\
    {"Chryssalid Corpse",73},{"Reaper Corpse",74},{"Sectopod Corpse",75},{"Cyberdisc Corpse",76},\
    {"UFO Power Source",81},{"UFO Navigation",82},{"UFO Construction",83},{"Alien Food",84},\
    {"Alien Reproduction",85},{"Alien Entertainment",86},{"Alien Surgery",87},\
    {"Examination Room",88},{"Alien Alloys",89},{"Alien Habitat",90},{"Personal Armour",91},\
    {"Power Suit",92},{"Flying Suit",93}};
#define TOTAL_ITEMS 83
#define TOTAL_SLOTS 96


// []-------------------------------------[]
// |  define all global variables/classes  |
// []-------------------------------------[]
screentype screen;
mousetype mouse;


//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
// return true if the specified file name exists
int file_exists (char *filename)
{
    struct ffblk f;
    return (!findfirst(filename, &f, 0));
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
#pragma argsused
void main (int argc, char *argv[])
{
    activescreenclass->registerfarewell(Farewell);

    // check our CRC
    #if !defined(NO_CRC_CHECK)
        FILE *fp;
        filecrc crc;
        if ((fp = fopen(argv[0], "rb")) == NULL) bad_crc();
        fseek(fp, 0x23, SEEK_SET); fread(&crc, sizeof(filecrc), 1, fp); fclose(fp);
        if (stealth_file_check(argv[0], crc)) bad_crc();
    #endif

    // do the shareware stuff
    shareware_annoyance();

    // main loop
    while (TRUE) {
        // select which saved game to edit
        int savedgame_number = main_screen();
        if (savedgame_number == 0) break;

        // select what to modify
        int option, base;
        while ((option = select_function()) != 0) {
            switch (option) {
                case 1: // edit money
                    money_edit(savedgame_number);
                    break;
                case 2: // edit base inventory
                    base = select_base(savedgame_number);
                    if (base) edit_inventory(savedgame_number, base);
                    break;
                case 3: // edit base buildings
                    base = select_base(savedgame_number);
                    if (base) edit_buildings(savedgame_number, base);
                    break;
                case 4: // edit soldiers
                    edit_soldiers(savedgame_number);
                    break;
                default: break;
            }
        }
    }

    exit(0);
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
int main_screen (void)
{
    int i, j;

    // []------------------[]
    // |  clear the screen  |
    // []------------------[]
    screen.drawrepeat('�', 80*25, 1, 1, COLOR(LIGHT_WHITE, LIGHT_BLUE));
    screen.refresh();

    // []--------------------------------------[]
    // |  read in all of the saved games names  |
    // []--------------------------------------[]
    int length = 1;
    char *buffer = new char[length], filename[25];
    if (buffer == NULL) no_memory();
    strcpy(buffer, "");
    for (i = 1; i <= 10; i++) {
        sprintf(filename, "GAME_%i\\SAVEINFO.DAT", i);
        if (file_exists(filename)) {
            char title[81], *temp;
            FILE *fp;

            if ((fp = fopen(filename, "rb")) == NULL) file_error();
            memset(title, 0, 80);
            fseek(fp, 2, SEEK_SET);
            fread(title, sizeof(char), 80, fp);
            fclose(fp);

            length += 4 + strlen(title) + 1; temp = new char[length];
            if (temp == NULL) no_memory();
            sprintf(temp, "%s%2i. %s\n", buffer, i, title);
            delete buffer; buffer = temp;
        }
    }
    if (length == 1) no_games();


    // []------------------------------------[]
    // |  create all controls that we'll use  |
    // []------------------------------------[]
    buttontype quit_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY),\
        3, 60, "Quit editor");
    buttontype about_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY),\
        9, 60, "About editor");
    menuboxtype saved_games(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, BLACK), \
        COLOR(GRAY, LIGHT_WHITE), 10, 23, buffer);
    screen.drawstring(VERSIONTEXT, 25, 1, COLOR(LIGHT_WHITE, LIGHT_BLUE));
    delete buffer;


    // []-----------------[]
    // |  main input loop  |
    // []-----------------[]
    while (TRUE) {
        // []-------------[]
        // |  quit button  |
        // []-------------[]
        quit_button.handle();
        if (quit_button.pressed) {
            #define QUIT_ROW 9
            #define QUIT_COL 20
            screen.save();
            textboxtype message(COLOR(LIGHT_WHITE, BLUE), COLOR(LIGHT_YELLOW, BLUE), \
                QUIT_ROW, QUIT_COL, 31, 10, "\nDo you really want to quit?\n");
            menuboxtype yesno(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, BLACK), \
                COLOR(GRAY, LIGHT_WHITE), QUIT_ROW + 4, QUIT_COL + 11, "Yes\nNo\n");
            screen.refresh();
            while (yesno.currentchoice == 0 || mouse.button) {
                message.handle();
                yesno.handle();
            }
            if (yesno.currentchoice == 1) return(0);
            screen.restore();
        }

        // []--------------[]
        // |  about button  |
        // []--------------[]
        about_button.handle();
        if (about_button.pressed) {
            activescreenclass->save();
            activescreenclass->locate(1, 1, 0);
            #define ABOUT_ROW 2
            #define ABOUT_COL 20
            textboxtype message(COLOR(LIGHT_WHITE, BLUE), COLOR(LIGHT_YELLOW, BLUE), \
                ABOUT_ROW, ABOUT_COL, 42, 23, "\n"
                "This program was written in C++ using\n"
                "the author's own user interface and\n"
                "screen and mouse handling classes.\n"
                "This specific version was compiled on\n"
                __DATE__ " at " __TIME__ " using Borland\n"
                "C++ version 3.1.  If you want to talk\n"
                "to the author, you may email him at\n"
                "\2JeffLawson@Aol.Com\1 or at the following\n"
                "surface mail address:\n\n"
                "    \2JL Enterprises\n"
                "    1893 Kaweah Drive\n"
                "    Pasadena, CA 91105-2174\n"
                "    USA\1\n\n"
                "We appreciate getting mail and enjoy\n"
                "reading what you have to say.\n"
                );
            buttontype ok_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY),\
                ABOUT_ROW + 19, ABOUT_COL + 17, "OK");
            while (!ok_button.pressed) {
                message.handle();
                ok_button.handle();
            }
            activescreenclass->restore();
        }


        // []---------------------[]
        // |  handle the menu box  |
        // []---------------------[]
        saved_games.handle();
        if (saved_games.currentchoice) {
            while (mouse.button) saved_games.handle();
            break;
        }
    }


    // []-------------------------------------[]
    // |  return the correct save game number  |
    // []-------------------------------------[]
    for (i = 1, j = 0; i <= 10; i++) {
        sprintf(filename, "GAME_%i\\SAVEINFO.DAT", i);
        if (file_exists(filename)) {
            if (++j == saved_games.currentchoice) return(i);
        }
    }
    return(0);
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
int select_function(void)
{
    // []------------------[]
    // |  clear the screen  |
    // []------------------[]
    screen.drawrepeat('�', 80*25, 1, 1, COLOR(LIGHT_WHITE, LIGHT_BLUE));
    screen.refresh();


    // []------------------------------------[]
    // |  create all controls that we'll use  |
    // []------------------------------------[]
    buttontype ok_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY),\
        3, 70, "OK");
    buttontype money_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY),\
        3, 20, "Edit money");
    buttontype inventory_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY),\
        9, 20, "Edit base inventory");
    buttontype buildings_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY),\
        15, 20, "Edit base buildings");
    buttontype soldier_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY),\
        21, 20, "Edit soldiers");


    // []-----------------[]
    // |  main input loop  |
    // []-----------------[]
    while (TRUE) {
        // ok button
        ok_button.handle();
        if (ok_button.pressed) return(0);

        // edit money button
        money_button.handle();
        if (money_button.pressed) return(1);

        // edit base inventory button
        inventory_button.handle();
        if (inventory_button.pressed) return(2);

        // edit base buildings button
        buildings_button.handle();
        if (buildings_button.pressed) return(3);

        // edit soldier button
        soldier_button.handle();
        if (soldier_button.pressed) return(4);
    }
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
// returns a number from 1 to 8, indicating the selected base
//
int select_base(int savedgame)
{
    // []------------------[]
    // |  clear the screen  |
    // []------------------[]
    screen.drawrepeat('�', 80*25, 1, 1, COLOR(LIGHT_WHITE, LIGHT_BLUE));
    screen.refresh();


    // []-------------------------------[]
    // |  read in all of the base names  |
    // []-------------------------------[]
    int i, j, length = 1, index[8] = {0,0,0,0,0,0,0,0};
    char *buffer = new char[length], filename[25], *temp, title[14];
    FILE *fp;
    if (buffer == NULL) no_memory();
    strcpy(buffer, "");
    sprintf(filename, "GAME_%i\\BASE.DAT", savedgame);
    if ((fp = fopen(filename, "rb")) == NULL) file_error();
    for (i = j = 0; i < 8; i++) {
        fseek(fp, i * 0x124, SEEK_SET);
        fread(title, sizeof(char), 13, fp); title[13] = 0;
        if (strlen(title)) {
            length += strlen(title) + 1; temp = new char[length];
            if (temp == NULL) no_memory();
            sprintf(temp, "%s%s\n", buffer, title);
            delete buffer; buffer = temp;
            index[j++] = i + 1;
        }
    }
    fclose(fp);
    if (length == 1) return(0);


    // []------------------------------------[]
    // |  create all controls that we'll use  |
    // []------------------------------------[]
    #define BASE_ROW 5
    #define BASE_COL 20
    textboxtype message(COLOR(LIGHT_WHITE, BLUE), COLOR(LIGHT_YELLOW, BLUE), \
        BASE_ROW, BASE_COL, 30, 15, "\nSelect base to edit:\n");
    menuboxtype base_names(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, BLACK), \
        COLOR(GRAY, LIGHT_WHITE), BASE_ROW + 4, BASE_COL + 6, buffer);
    delete buffer;


    // []-----------------[]
    // |  main input loop  |
    // []-----------------[]
    while (base_names.currentchoice == 0 || mouse.button) {
        message.handle();
        base_names.handle();
    }


    // []--------------------------[]
    // |  return the selected base  |
    // []--------------------------[]
    return(index[base_names.currentchoice - 1]);
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
// savedgame is a number from 1 to 10 indicating the saved game to edit
//
void money_edit (int savedgame)
{
    // []------------------[]
    // |  clear the screen  |
    // []------------------[]
    screen.drawrepeat('�', 80*25, 1, 1, COLOR(LIGHT_WHITE, LIGHT_BLUE));
    screen.refresh();

    // create all controls that we'll use
    #define MONEY_ROW 9
    #define MONEY_COL 20
    textboxtype message(COLOR(LIGHT_WHITE, BLUE), COLOR(LIGHT_YELLOW, BLUE), \
        MONEY_ROW, MONEY_COL, 35, 11, "\nHow much money do you want?\n");
    textinputtype money_text(COLOR(BLACK, LIGHT_WHITE), \
        MONEY_ROW + 4, MONEY_COL + 7, 15, NULL);
    buttontype max_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY), \
        MONEY_ROW + 6, MONEY_COL + 2, "Lots");
    buttontype ok_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY), \
        MONEY_ROW + 6, MONEY_COL + 15, "OK");
    buttontype cancel_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY), \
        MONEY_ROW + 6, MONEY_COL + 23, "Cancel");

    // read in how much money the user currently has
    char filename[25]; FILE *fp; long money;
    sprintf(filename, "GAME_%i\\LIGLOB.DAT", savedgame);
    if ((fp = fopen(filename, "rb")) == NULL) file_error();
    fread(&money, sizeof(long), 1, fp);
    fclose(fp);
    if (money < 0) money = 0;
    sprintf(money_text.message, "%lu", money);

    // main input loop
    while (TRUE) {
        message.handle();
        money_text.handle();

        // maximum button
        max_button.handle();
        if (max_button.pressed) {
            sprintf(money_text.message, "%lu", 0x7FF00000);
            money_text.needupdate = TRUE;
        }

        // ok button
        ok_button.handle();
        if (ok_button.pressed) {
            // save out the changes
            sscanf(money_text.message, "%lu", &money);
            if (money < 0) money = -money;
            if ((fp = fopen(filename, "rb+")) == NULL) file_error();
            fwrite(&money, sizeof(long), 1, fp);
            fclose(fp);
            break;
        }

        // cancel button
        cancel_button.handle();
        if (cancel_button.pressed) break;
    }
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
// savedgame is a number from 1 to 10 indicating the saved game to edit
// base is a number from 1 to 8 indicating the base number to edit
//
void edit_inventory(int savedgame, int base)
{
    // clear the screen
    screen.drawrepeat('�', 80*25, 1, 1, COLOR(LIGHT_WHITE, LIGHT_BLUE));
    screen.refresh();

    // read in the current inventory
    char filename[25]; FILE *fp; int inventory[TOTAL_SLOTS];
    sprintf(filename, "GAME_%i\\BASE.DAT", savedgame);
    if ((fp = fopen(filename, "rb")) == NULL) file_error();
    fseek(fp, (base - 1) * 0x124 + 0x60, SEEK_SET);
    fread(inventory, sizeof(int), TOTAL_SLOTS, fp);
    fclose(fp);

    // create all controls that we'll use
    menuboxtype *item_names = NULL;
    buttontype ok_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY),\
        3, 50, "OK");
    buttontype cancel_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY),\
        7, 50, "Cancel");
    buttontype single_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY),\
        18, 50, "Change single quantity");
    buttontype all_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY),\
        22, 50, "Change all quantities");

    // main input loop
    int regenerate_list = TRUE;
    while (TRUE) {
        // build new page of items, if necessary
        if (regenerate_list) {
            // delete old list, if present
            int oldtoprow = 1, oldchoice = 0;
            if (item_names) {
                oldtoprow = item_names->toprow;
                oldchoice = item_names->currentchoice;
                delete item_names; item_names = NULL;
            }
            // generate new list
            int i, length = 1; char *buffer = new char[length];
            strcpy(buffer, "");
            for (i = 0; i < TOTAL_ITEMS; i++) {
                length += 41; char *temp = new char[length];
                if (temp == NULL) no_memory();
                sprintf(temp, "%s%-34.34s%6i\n", buffer, \
                    objects[i].name, inventory[objects[i].id - 1]);
                delete buffer; buffer = temp;
            }
            item_names = new menuboxtype(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, BLACK), \
                COLOR(GRAY, LIGHT_WHITE), 2, 3, 21, buffer);
            item_names->toprow = oldtoprow;
            item_names->currentchoice = oldchoice;
            regenerate_list = FALSE; delete buffer;
            // clear screen
            for (i = 2; i <= 24; i++) {
                screen.drawrepeat('�', 44, i, 3, COLOR(LIGHT_WHITE, LIGHT_BLUE));
            }
            screen.refresh();
        }

        // update the controls
        item_names->handle();

        // single button
        single_button.handle();
        if (single_button.pressed && item_names->currentchoice) {
            int i = quantity_edit (inventory[objects[item_names->currentchoice - 1].id - 1]);
            if (i != -1) inventory[objects[item_names->currentchoice - 1].id - 1] = i;
            regenerate_list = TRUE;
        }

        // all button
        all_button.handle();
        if (all_button.pressed) {
            int i, count = quantity_edit(0);
            if (count != -1)
                for (i = 0; i < TOTAL_ITEMS; i++)
                    inventory[objects[i].id - 1] = count;
            regenerate_list = TRUE;
        }

        // ok button
        ok_button.handle();
        if (ok_button.pressed) {
            // write out changes
            if ((fp = fopen(filename, "rb+")) == NULL) file_error();
            fseek(fp, (base - 1) * 0x124 + 0x60, SEEK_SET);
            fwrite(inventory, sizeof(int), TOTAL_SLOTS, fp);
            fclose(fp);
            break;
        }

        // cancel button
        cancel_button.handle();
        if (cancel_button.pressed) break;
    }

    // free everything
    if (item_names) delete item_names;
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
int quantity_edit (int initial)
{
    // save the screen
    screen.save();

    // create all controls that we'll use
    #define QUANTITY_ROW 9
    #define QUANTITY_COL 20
    textboxtype message(COLOR(LIGHT_WHITE, BLUE), COLOR(LIGHT_YELLOW, BLUE), \
        QUANTITY_ROW, QUANTITY_COL, 35, 11, "\nHow many do you want?\n");
    textinputtype quantity_text(COLOR(BLACK, LIGHT_WHITE), \
        QUANTITY_ROW + 4, QUANTITY_COL + 7, 15, NULL);
    buttontype max_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY), \
        QUANTITY_ROW + 6, QUANTITY_COL + 2, "Lots");
    buttontype ok_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY), \
        QUANTITY_ROW + 6, QUANTITY_COL + 15, "OK");
    buttontype cancel_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY), \
        QUANTITY_ROW + 6, QUANTITY_COL + 23, "Cancel");

    // set how many the user currently has
    if (initial < 0) initial = 0;
    sprintf(quantity_text.message, "%u", initial);

    // main input loop
    while (TRUE) {
        message.handle();
        quantity_text.handle();

        // maximum button
        max_button.handle();
        if (max_button.pressed) {
            sprintf(quantity_text.message, "%u", 32000);
            quantity_text.needupdate = TRUE;
        }

        // ok button
        ok_button.handle();
        if (ok_button.pressed) {
            // return the new amount
            sscanf(quantity_text.message, "%u", &initial);
            if (initial < 0) initial = -initial;
            break;
        }

        // cancel button
        cancel_button.handle();
        if (cancel_button.pressed) {initial = -1; break;}
    }

    // restore the screen
    screen.restore();
    return(initial);
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
// savedgame is a number from 1 to 10 indicating the saved game to edit
// base is a number from 1 to 8 indicating the base number to edit
//
void edit_buildings(int savedgame, int base)
{
    int i, j; char filename[25]; FILE *fp;
    char buildings[6][6], completion[6][6];

    // []------------------[]
    // |  clear the screen  |
    // []------------------[]
    screen.drawrepeat('�', 80*25, 1, 1, COLOR(LIGHT_WHITE, LIGHT_BLUE));
    screen.refresh();


    // []------------------------------------------[]
    // |  read in the current building information  |
    // []------------------------------------------[]
    sprintf(filename, "GAME_%i\\BASE.DAT", savedgame);
    if ((fp = fopen(filename, "rb")) == NULL) file_error();
    fseek(fp, (base - 1) * 0x124 + 0x16, SEEK_SET);
    fread(buildings, sizeof(char), 6*6, fp);
    fread(completion, sizeof(char), 6*6, fp);
    fclose(fp);


    // []------------------------------------[]
    // |  create all controls that we'll use  |
    // []------------------------------------[]
    buttontype ok_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, \
        GRAY), 2, 57, "OK");
    buttontype cancel_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, \
        GRAY),2, 65, "Cancel");
    checkboxtype set_box(COLOR(BLACK, LIGHT_WHITE), 6, 57, "Set");
    buttontype *building_buttons[6][6];


    // []----------------------------[]
    // |  generate the building list  |
    // []----------------------------[]
    int length = 1; char *buffer = new char[length];
    if (buffer == NULL) no_memory();
    buffer[0] = 0;
    for (i = 0; i < TOTAL_BUILDINGS; i++) {
        length += 20; char *temp = new char[length];
        if (temp == NULL) no_memory();
        sprintf(temp, "%s%-19.19s\n", buffer, building_names[i]);
        delete buffer; buffer = temp;
    }
    menuboxtype building_list(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, \
        BLACK), COLOR(GRAY, LIGHT_WHITE), 8, 57, 15, buffer);
    delete buffer;


    // []---------------------------------------------[]
    // |  mark the builing buttons as all unallocated  |
    // []---------------------------------------------[]
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            building_buttons[i][j] = NULL;
        }
    }

    // []-----------------[]
    // |  main input loop  |
    // []-----------------[]
    int regenerate_buildings = TRUE;
    while (TRUE) {
        // []------------------------------------------[]
        // |  build screenful of buttons, if necessary  |
        // []------------------------------------------[]
        if (regenerate_buildings) {
            // clear the screen
            for (i = 1; i <= 25; i++) {
                screen.drawrepeat('�', 55, i, 1, COLOR(LIGHT_WHITE, LIGHT_BLUE));
            }
            screen.refresh();
            // generate new buttons to replace the old ones
            for (i = 0; i < 6; i++) {
                for (j = 0; j < 6; j++) {
                    // delete this button if one already exists
                    if (building_buttons[i][j]) {
                        delete building_buttons[i][j];
                        building_buttons[i][j] = NULL;
                    }
                    // now create a new updated one
                    char buffer[30];
                    if (buildings[i][j] == 0x10) {
                        strcpy(buffer, "\n\n    Hangar    \n\n\n");
                    } else if (buildings[i][j] == 0x11 || buildings[i][j] == 0x12 || buildings[i][j] == 0x13) {
                        continue;
                    } else {
                        sprintf(buffer, "%-5.5s", building_names[buildings[i][j] + 1]);
                    }
                    if (completion[i][j] == -1) {
                        // nothing
                        building_buttons[i][j] = new buttontype(COLOR(BLACK, LIGHT_YELLOW), \
                            COLOR(LIGHT_YELLOW, GRAY), i * 4 + 2, j * 9 + 2, buffer);
                    } else if (completion[i][j] > 0) {
                        // not completed building
                        building_buttons[i][j] = new buttontype(COLOR(BLACK, LIGHT_RED), \
                            COLOR(LIGHT_RED, GRAY), i * 4 + 2, j * 9 + 2, buffer);
                    } else {
                        // already completed building
                        building_buttons[i][j] = new buttontype(COLOR(BLACK, LIGHT_GREEN), \
                            COLOR(LIGHT_GREEN, GRAY), i * 4 + 2, j * 9 + 2, buffer);
                    }
                }
            }
            regenerate_buildings = FALSE;
        }


        // []---------------------[]
        // |  update the controls  |
        // []---------------------[]
        building_list.handle();


        // []---------[]
        // |  set box  |
        // []---------[]
        set_box.handle();


        // []-----------------------------[]
        // |  update the building buttons  |
        // []-----------------------------[]
        for (i = 0; i < 6; i++) {
            for (j = 0; j < 6; j++) {
                if (building_buttons[i][j]) {
                    building_buttons[i][j]->handle();
                    if (building_buttons[i][j]->pressed) {
                        if (set_box.checked && building_list.currentchoice) {
                            // the user is trying to change a building
                            if (buildings[i][j] == 0x10) {
                                // if it was a hangar, distroy all 4 blocks
                                buildings[i][j+1] = -1; completion[i][j+1] = -1;
                                buildings[i+1][j] = -1; completion[i+1][j] = -1;
                                buildings[i+1][j+1] = -1; completion[i+1][j+1] = -1;
                            }
                            if (building_list.currentchoice - 2 == 0x10) {
                                // if we're changing it to a hangar...
                                if (i < 5 && j < 5) {
                                    // make sure it will fit where selected
                                    if (buildings[i][j+1] == 0x10 && j < 4) {  // left side
                                        buildings[i][j+1] = -1; completion[i][j+1] = -1;
                                        buildings[i][j+2] = -1; completion[i][j+2] = -1;
                                        buildings[i+1][j+1] = -1; completion[i+1][j+1] = -1;
                                        buildings[i+1][j+2] = -1; completion[i+1][j+2] = -1;
                                    }
                                    if (buildings[i-1][j+1] == 0x10 && j < 4 && i > 0) { // upper-left
                                        buildings[i-1][j+1] = -1; completion[i-1][j+1] = -1;
                                        buildings[i-1][j+2] = -1; completion[i-1][j+2] = -1;
                                        buildings[i][j+1] = -1; completion[i][j+1] = -1;
                                        buildings[i][j+2] = -1; completion[i][j+2] = -1;
                                    }
                                    if (buildings[i+1][j+1] == 0x10 && j < 4 && i < 4) { // lower-left
                                        buildings[i+1][j+1] = -1; completion[i+1][j+1] = -1;
                                        buildings[i+1][j+2] = -1; completion[i+1][j+2] = -1;
                                        buildings[i+2][j+1] = -1; completion[i+2][j+1] = -1;
                                        buildings[i+2][j+2] = -1; completion[i+2][j+2] = -1;
                                    }
                                    if (buildings[i+1][j] == 0x10 && i < 4) { // top
                                        buildings[i+1][j] = -1; completion[i+1][j] = -1;
                                        buildings[i+1][j+1] = -1; completion[i+1][j+1] = -1;
                                        buildings[i+2][j] = -1; completion[i+2][j] = -1;
                                        buildings[i+2][j+1] = -1; completion[i+2][j+1] = -1;
                                    }
                                    if (buildings[i+1][j-1] == 0x10 && i < 4 && j > 0) { // upper-right
                                        buildings[i+1][j-1] = -1; completion[i+1][j-1] = -1;
                                        buildings[i+1][j] = -1; completion[i+1][j] = -1;
                                        buildings[i+2][j-1] = -1; completion[i+2][j-1] = -1;
                                        buildings[i+2][j] = -1; completion[i+2][j] = -1;
                                    }
                                    buildings[i][j] = 0x10; completion[i][j] = 0;
                                    buildings[i][j+1] = 0x11; completion[i][j+1] = 0;
                                    buildings[i+1][j] = 0x12; completion[i+1][j] = 0;
                                    buildings[i+1][j+1] = 0x13; completion[i+1][j+1] = 0;
                                } else {
                                    // otherwise ignore the request
                                    continue;
                                }
                            } else if (building_list.currentchoice - 2 == -1) {
                                // if we're changing it to nothing...
                                buildings[i][j] = -1;
                                completion[i][j] = -1;
                            } else {
                                // else we're changing it to something else
                                buildings[i][j] = building_list.currentchoice - 2;
                                completion[i][j] = 0;
                            }
                            regenerate_buildings = TRUE;
                        } else {
                            // the user is querying us about a building
                            if (buildings[i][j] == -1) {
                                building_list.currentchoice = 1;
                                building_list.needupdate = TRUE;
                            } else {
                                building_list.currentchoice = buildings[i][j] + 2;
                                building_list.needupdate = TRUE;
                            }
                        }
                    }
                }
            }
        }

        // []-----------[]
        // |  ok button  |
        // []-----------[]
        ok_button.handle();
        if (ok_button.pressed) {
            // write out changes
            if ((fp = fopen(filename, "rb+")) == NULL) file_error();
            fseek(fp, (base - 1) * 0x124 + 0x16, SEEK_SET);
            fwrite(buildings, sizeof(char), 6*6, fp);
            fwrite(completion, sizeof(char), 6*6, fp);
            fclose(fp);
            break;
        }

        // []---------------[]
        // |  cancel button  |
        // []---------------[]
        cancel_button.handle();
        if (cancel_button.pressed) break;
    }


    // []-----------------[]
    // |  free everything  |
    // []-----------------[]
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 6; j++) {
            if (building_buttons[i][j]) delete building_buttons[i][j];
        }
    }
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
// savedgame is a number from 1 to 10 indicating the saved game to edit
//
void edit_soldiers(int savedgame)
{
    char filename[25]; FILE *fp; int i, j;
    struct soldier_type *soldiers = new struct soldier_type[250];
    if (soldiers == NULL) no_memory();


    // []------------------[]
    // |  clear the screen  |
    // []------------------[]
    screen.drawrepeat('�', 80*25, 1, 1, COLOR(LIGHT_WHITE, LIGHT_BLUE));
    screen.refresh();


    // []------------------------------------[]
    // |  create all controls that we'll use  |
    // []------------------------------------[]
    buttontype ok_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, \
        GRAY), 2, 50, "OK");
    buttontype cancel_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, \
        GRAY), 2, 58, "Cancel");
    buttontype edit_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, \
        GRAY), 12, 31, "Edit stat");
    menuboxtype *soldier_names = NULL, *statistics = NULL;
    checkboxtype *base_box[8];
    dropdowntype rank(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, BLACK), \
        3, 13, 15, "dead\n" "rookie\n" "squaddie\n" "sergeant\n" "captain\n" \
        "colonel\n" "commander\n");
    dropdowntype armour(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, \
        BLACK), 5, 13, 20, "none\n" "personal armour\n" "power suit\n" \
        "flying suit\n");


    // []--------------------------------------[]
    // |  create as many base boxes as we need  |
    // []--------------------------------------[]
    sprintf(filename, "GAME_%i\\BASE.DAT", savedgame);
    if ((fp = fopen(filename, "rb")) == NULL) file_error();
    int basedroplength = 1; char *basedroplist = new char[basedroplength];
    if (basedroplist == NULL) no_memory();
    basedroplist[0] = 0;
    for (i = 0; i < 8; i++) {
        char title[14];
        fseek(fp, i * 0x124, SEEK_SET);
        fread(title, sizeof(char), 13, fp); title[13] = 0;
        if (strlen(title) != 0) {
            base_box[i] = new checkboxtype(COLOR(BLACK, LIGHT_WHITE), \
                16 + i, 31, title);
        } else {
            sprintf(title, "(base %i)", i + 1);
            base_box[i] = new checkboxtype(COLOR(WHITE, LIGHT_WHITE), \
                16 + i, 31, title);
        }
        basedroplength += strlen(title) + 1;
        char *newlist = new char[basedroplength];
        if (newlist == NULL) no_memory();
        sprintf(newlist, "%s%s\n", basedroplist, title);
        delete basedroplist;
        basedroplist = newlist;
    }
    fclose(fp);
    dropdowntype location(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, \
        BLACK), 4, 13, 15, basedroplist);
    delete basedroplist;


    // []----------------------[]
    // |  read in the soldiers  |
    // []----------------------[]
    sprintf(filename, "GAME_%i\\SOLDIER.DAT", savedgame);
    if ((fp = fopen(filename, "rb")) == NULL) file_error();
    fread(soldiers, sizeof(struct soldier_type), 250, fp);
    fclose(fp);


    // []-----------------------------[]
    // |  validate the soldier fields  |
    // []-----------------------------[]
    for (i = 0; i < 250; i++) {
        soldiers[i].name[25] = 0;
        if (!isalpha(soldiers[i].name[0])) soldiers[i].name[0] = 0;
        if (soldiers[i].rank > 6) soldiers[i].rank = 0xFFFF;
        switch (soldiers[i].location) {
            case 0: case 4: case 5: case 6: case 7: case 8: case 20: case 15:
                break;
            default:
                soldiers[i].location = 0;
                break;
        }
        soldiers[i].time += soldiers[i].inctime; soldiers[i].inctime = 0;
        soldiers[i].health += soldiers[i].inchealth; soldiers[i].inchealth = 0;
        soldiers[i].stamina += soldiers[i].incstamina; soldiers[i].incstamina = 0;
        soldiers[i].reactions += soldiers[i].increactions; soldiers[i].increactions = 0;
        soldiers[i].strength += soldiers[i].incstrength; soldiers[i].incstrength = 0;
        soldiers[i].firing += soldiers[i].incfiring; soldiers[i].incfiring = 0;
        soldiers[i].throwing += soldiers[i].incthrowing; soldiers[i].incthrowing = 0;
        soldiers[i].incpsionicsk = 0; soldiers[i].incbravery = 0;
        if (soldiers[i].armour > 3) soldiers[i].armour = 0;
    }


    // []-----------------[]
    // |  main input loop  |
    // []-----------------[]
    int regenerate_list = TRUE;
    int regenerate_soldier = TRUE, soldier_number = -1;
    while (TRUE) {
        // []------------------------------------------[]
        // |  build new page of soldiers, if necessary  |
        // []------------------------------------------[]
        if (regenerate_list) {
            // delete old list, if necessary
            if (soldier_names) {delete soldier_names; soldier_names = NULL;}
            // erase screen
            for (i = 6; i <= 24; i++) {
                screen.drawrepeat('�', 30, i, 50, COLOR(LIGHT_WHITE, LIGHT_BLUE));
            }
            screen.refresh();
            // generate new list buffer
            int total_matching = 0, length = 1, active[250];
            char *buffer = new char[length]; strcpy(buffer, "");
            for (i = 0; i < 250; i++) {
                for (j = 0; j < 8; j++) {
                    if (soldiers[i].name[0] > ' ' && soldiers[i].location == base_id[j] && base_box[j]->checked) {
                        length += 26; char *temp = new char[length];
                        if (temp == NULL) no_memory();
                        sprintf(temp, "%s%-25.25s\n", buffer, soldiers[i].name);
                        active[total_matching] = (soldiers[i].rank != 0xFFFF);
                        delete buffer; buffer = temp;
                        total_matching++;
                    }
                }
            }
            // create new list
            if (total_matching > 0) soldier_names = new menuboxtype(COLOR(BLACK, LIGHT_WHITE), \
                COLOR(LIGHT_WHITE, BLACK), COLOR(GRAY, LIGHT_WHITE), 6, 50, 17, buffer);
            for (i = 0; i < total_matching; i++) {
                soldier_names->setchoiceinfo(i + 1, FALSE, active[i] == 0);
            }
            regenerate_list = FALSE; delete buffer;
            soldier_number = -1; regenerate_soldier = TRUE;
        }


        // []---------------------------------------------[]
        // |  regenerate soldier statistics, if necessary  |
        // []---------------------------------------------[]
        if (regenerate_soldier) {
            // delete the old statistics, if necessary
            if (statistics) {delete statistics; statistics = NULL;}
            // erase the screen
            for (i = 1; i < 10; i++)
                screen.drawrepeat('�', 45, i, 1, COLOR(LIGHT_WHITE, LIGHT_BLUE));
            for (i = 10; i <= 25; i++)
                screen.drawrepeat('�', 30, i, 1, COLOR(LIGHT_WHITE, LIGHT_BLUE));
            screen.refresh();
            // create the new statistics
            if (soldier_number >= 0) {
                // update name
                screen.drawstring("name:", 2, 6, COLOR(BLACK, LIGHT_WHITE));
                screen.drawrepeat(' ', 25, 2, 13, COLOR(BLACK, LIGHT_WHITE));
                screen.drawstring(soldiers[soldier_number].name, 2, 13, COLOR(BLACK, LIGHT_WHITE));
                // update rank
                screen.drawstring("rank:", 3, 6, COLOR(BLACK, LIGHT_WHITE));
                rank.currentchoice = soldiers[soldier_number].rank + 2;
                rank.needupdate = TRUE;
                // update location
                screen.drawstring("location:", 4, 2, COLOR(BLACK, LIGHT_WHITE));
                switch (soldiers[soldier_number].location) {
                    case 0: location.currentchoice = 1; break;
                    case 4: location.currentchoice = 2; break;
                    case 5: location.currentchoice = 3; break;
                    case 6: location.currentchoice = 4; break;
                    case 7: location.currentchoice = 5; break;
                    case 8: location.currentchoice = 6; break;
                    case 20: location.currentchoice = 7; break;
                    case 15: location.currentchoice = 8; break;
                    default: location.currentchoice = 0; break;
                }
                location.needupdate = TRUE;
                // update armour
                screen.drawstring("armour:", 5, 4, COLOR(BLACK, LIGHT_WHITE));
                armour.currentchoice = soldiers[soldier_number].armour + 1;
                armour.needupdate = TRUE;
                // update statistics box
                char *buffer = new char[350];
                if (buffer == NULL) no_memory();
                sprintf(buffer, "missions: %u\n"
                                "kills: %u\n"
                                "recovery: %u days\n\n"
                                "time units: %hu\n"
                                "stamina: %hu\n"
                                "health: %hu\n"
                                "bravery: %hu\n"
                                "reactions: %hu\n"
                                "firing accuracy: %hu\n"
                                "throwing accuracy: %hu\n"
                                "strength: %hu\n"
                                "psionic strength: %hu\n"
                                "psionic skill: %hu\n",
                    soldiers[soldier_number].missions, soldiers[soldier_number].kills,
                    soldiers[soldier_number].recovery, soldiers[soldier_number].time,
                    soldiers[soldier_number].stamina, soldiers[soldier_number].health,
                    100 - 10 * (soldiers[soldier_number].bravery - 1),
                    soldiers[soldier_number].reactions, soldiers[soldier_number].firing,
                    soldiers[soldier_number].throwing, soldiers[soldier_number].strength,
                    soldiers[soldier_number].psionicstr, soldiers[soldier_number].psionicsk);
                statistics = new menuboxtype(COLOR(BLACK, LIGHT_WHITE), \
                    COLOR(LIGHT_WHITE, BLACK), COLOR(GRAY, LIGHT_WHITE), \
                    9, 2, buffer);
                statistics->setchoiceinfo(4, TRUE, FALSE);
                delete buffer;
            }
            regenerate_soldier = FALSE;
        }


        // []-----------[]
        // |  ok button  |
        // []-----------[]
        ok_button.handle();
        if (ok_button.pressed) {
            // write out changes
            if ((fp = fopen(filename, "rb+")) == NULL) file_error();
            fwrite(soldiers, sizeof(struct soldier_type), 250, fp);
            fclose(fp);
            break;
        }


        // []---------------[]
        // |  cancel button  |
        // []---------------[]
        cancel_button.handle();
        if (cancel_button.pressed) break;


        // []-------------[]
        // |  edit button  |
        // []-------------[]
        edit_button.handle();
        if ((edit_button.pressed || mouse.button & 2) && statistics->currentchoice) {
            unsigned temp;

            switch (statistics->currentchoice) {
                case 1: // missions
                    stat_edit(soldiers[soldier_number].missions, \
                        0, 0x7FFF, "\nNumber of missions?\n", 32000);
                    break;
                case 2: // kills
                    stat_edit(soldiers[soldier_number].kills, \
                        0, 0x7FFF, "\nNumber of kills?\n", 32000);
                    break;
                case 3: // recovery
                    stat_edit(soldiers[soldier_number].recovery, \
                        0, 0x7FFF, "\nDays until recovery?\n", 0);
                    break;
                case 5: // time units
                    temp = soldiers[soldier_number].time;
                    stat_edit(temp, 0, 0xFF, "\nNumber of time units?\n", 0xFF);
                    soldiers[soldier_number].time = temp;
                    break;
                case 6: // stamina
                    temp = soldiers[soldier_number].stamina;
                    stat_edit(temp, 0, 0xFF, "\nAmount of stamina?\n", 0xFF);
                    soldiers[soldier_number].stamina = temp;
                    break;
                case 7: // health
                    temp = soldiers[soldier_number].health;
                    stat_edit(temp, 0, 0xFF, "\nAmount of health?\n", 0xFF);
                    soldiers[soldier_number].health = temp;
                    break;
                case 8: // bravery
                    temp = 100 - 10 * (soldiers[soldier_number].bravery - 1);
                    stat_edit(temp, 20, 100, "\nAmount for bravery?\n", 100);
                    soldiers[soldier_number].bravery = (temp - 100) / 10 + 1;
                    break;
                case 9: // reactions
                    temp = soldiers[soldier_number].reactions;
                    stat_edit(temp, 0, 0xFF, "\nAmount for reactions?\n", 0xFF);
                    soldiers[soldier_number].reactions = temp;
                    break;
                case 10: // firing accuracy
                    temp = soldiers[soldier_number].firing;
                    stat_edit(temp, 0, 0xFF, "\nFiring accuracy?\n", 0xFF);
                    soldiers[soldier_number].firing = temp;
                    break;
                case 11: // throwing accuracy
                    temp = soldiers[soldier_number].throwing;
                    stat_edit(temp, 0, 0xFF, "\nThrowing accuracy?\n", 0xFF);
                    soldiers[soldier_number].throwing = temp;
                    break;
                case 12: // strength
                    temp = soldiers[soldier_number].strength;
                    stat_edit(temp, 0, 0xFF, "\nAmount of strength?\n", 0xFF);
                    soldiers[soldier_number].strength = temp;
                    break;
                case 13: // psionic strength
                    temp = soldiers[soldier_number].psionicstr;
                    stat_edit(temp, 0, 0xFF, "\nPsionic strength?\n", 0xFF);
                    soldiers[soldier_number].psionicstr = temp;
                    break;
                case 14: // psionic skill
                    temp = soldiers[soldier_number].psionicsk;
                    stat_edit(temp, 0, 0xFF, "\nPsionic skill?\n", 0xFF);
                    soldiers[soldier_number].psionicsk = temp;
                    break;
                default: break;
            }
            regenerate_soldier = TRUE;
        }


        // []-----------------[]
        // |  base checkboxes  |
        // []-----------------[]
        for (i = 0; i < 8; i++) {
            int k = base_box[i]->checked;
            base_box[i]->handle();
            if (k != base_box[i]->checked) {
                regenerate_list = TRUE; break;
            }
        }


        // []--------------------------------------------[]
        // |  statistics list and other editing controls  |
        // []--------------------------------------------[]
        if (statistics) {
            // update rank
            i = rank.currentchoice;
            rank.handle();
            if (i != rank.currentchoice) {
                if (rank.currentchoice != 1) {
                    soldiers[soldier_number].rank = rank.currentchoice - 2;
                } else {
                    soldiers[soldier_number].rank = 0xFFFF;
                }
                soldier_names->setchoiceinfo(soldier_names->currentchoice, \
                    FALSE, soldiers[soldier_number].rank != 0xFFF);
                soldier_names->needupdate = TRUE;
            }

            // update location
            i = location.currentchoice;
            location.handle();
            if (i != location.currentchoice) {
                soldiers[soldier_number].location = base_id[location.currentchoice - 1];
                regenerate_list = TRUE;
            }

            // update armour
            armour.handle();
            soldiers[soldier_number].armour = armour.currentchoice - 1;

            // update statistics box
            statistics->handle();
        }


        // []-------------------[]
        // |  soldier name list  |
        // []-------------------[]
        if (soldier_names) {
            i = soldier_names->currentchoice;
            soldier_names->handle();
            if (i != soldier_names->currentchoice) {
                int k = 1; soldier_number = -1;
                for (i = 0; i < 250; i++) {
                    for (j = 0; j < 8; j++) {
                        if (soldiers[i].location == base_id[j] && base_box[j] != NULL && base_box[j]->checked) {
                            if (k++ == soldier_names->currentchoice) soldier_number = i;
                        }
                    }
                }
                regenerate_soldier = TRUE;
            }
        }
    }


    // []-----------------[]
    // |  free everything  |
    // []-----------------[]
    delete soldiers;
    if (statistics) delete statistics;
    if (soldier_names) delete soldier_names;
    for (i = 0; i < 8; i++) delete base_box[i];
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
// minmax should be 0 if there should be a "minimum" button, or it should be
//      the value specified by maximum for a "maximum" button to be present,
//      otherwise, a "lots" button will be made and will be assigned that.
//
void stat_edit (unsigned &initial, unsigned minimum, unsigned maximum, \
    char *text, unsigned minmax)
{
    // []-----------------[]
    // |  save the screen  |
    // []-----------------[]
    screen.save();

    // []------------------------------------[]
    // |  create all controls that we'll use  |
    // []------------------------------------[]
    #define STAT_ROW 9
    #define STAT_COL 20
    textboxtype message(COLOR(LIGHT_WHITE, BLUE), COLOR(LIGHT_YELLOW, BLUE), \
        STAT_ROW, STAT_COL, 35, 11, text);
    textinputtype stat_text(COLOR(BLACK, LIGHT_WHITE), \
        STAT_ROW + 4, STAT_COL + 7, 15, NULL);
    sprintf(stat_text.message, "%u", initial);
    buttontype max_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY), \
        STAT_ROW + 6, STAT_COL + 2, (minmax ? (minmax == maximum ? "Maximum" : \
        "Lots") : "Minimum"));
    buttontype ok_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY), \
        STAT_ROW + 6, STAT_COL + 15, "OK");
    buttontype cancel_button(COLOR(BLACK, LIGHT_WHITE), COLOR(LIGHT_WHITE, GRAY), \
        STAT_ROW + 6, STAT_COL + 23, "Cancel");


    // []-----------------[]
    // |  main input loop  |
    // []-----------------[]
    unsigned newvalue = initial;
    while (TRUE) {
        message.handle();
        stat_text.handle();

        // maximum button
        max_button.handle();
        if (max_button.pressed) {
            sprintf(stat_text.message, "%u", (minmax ? minmax : minimum));
            stat_text.needupdate = TRUE;
        }

        // ok button
        ok_button.handle();
        if (ok_button.pressed) {
            // return the new amount
            sscanf(stat_text.message, "%u", &newvalue);
            if (newvalue < minimum) newvalue = minimum;
            if (newvalue > maximum) newvalue = maximum;
            break;
        }

        // cancel button
        cancel_button.handle();
        if (cancel_button.pressed) {newvalue = initial; break;}
    }


    // []--------------------[]
    // |  restore the screen  |
    // []--------------------[]
    screen.restore();
    initial = newvalue;
}
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
//같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같같
