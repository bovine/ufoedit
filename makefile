# makefile MAKE V2.0 or higher
.autodepend

# to enable debugging information, set "DEBUG" to "yes"
DEBUG = no

##############################################################################

ufoed12.zip:    ufoedit.exe file_id.diz ufoedit.txt
                @if exist $< del $<
                for %a in ($**) do fd %a /d /t1:20
                pkzip $< $** /ex /! /z < file_id.diz

##############################################################################

BCC_ARGS = /v /ml /c /2 /Os
TLINK_ARGS = /x

!if ($(DEBUG) == yes)
BCC_ARGS = $(BCC_ARGS)
TLINK_ARGS = $(TLINK_ARGS) /v
!endif

##############################################################################

.cpp.obj:
    bcc $(BCC_ARGS) $*.cpp

.c.obj:
    bcc $(BCC_ARGS) $*.c

##############################################################################

ufoedit.exe:    ufoedit.obj farewell.obj errormsg.obj
        tlink $(TLINK_ARGS) @&&|
c0l.obj $**
$<
nul
cl.lib tui.lib noehl.lib
|
!if ($(DEBUG) != yes)
        pklite $<
        unp l -h $<
        tinyprog /F /Mb "\_" /Ut _STEALTH /K $<
        unp l -h $<
        crcset $<
!endif

##############################################################################

farewell.obj:   farewell.bin
                2obj b farewell.bin .large:_Farewell

##############################################################################
