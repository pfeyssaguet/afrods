#---------------------------------------------------------------------------------
# PAlib Project Makefile by Scognito, Tom, crash and fincs
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# Please uncomment (i.e. delete the '#') only one "ARM7_SELECTED" line. If unsure,
# leave it as is (with ARM7_MP3 uncommented).
#---------------------------------------------------------------------------------

ARM7_SELECTED = ARM7_MP3
#ARM7_SELECTED = ARM7_MP3_DSWIFI
#ARM7_SELECTED = ARM7_MAXMOD_DSWIFI

#---------------------------------------------------------------------------------
# If you're using EFS uncomment "USE_EFS = YES" here.
#---------------------------------------------------------------------------------

#USE_EFS = YES

PATH := $(DEVKITARM)/bin:$(PATH)
PROGNAME = PAlib
OFILES +=
ADD_LIBS +=

#---------------------------------------------------------------------------------
# Be sure to change these default banner TEXTs. This is the name your project will
# display in the DS menu (including some flash cards). Create a custom logo.bmp
# icon for your project too!
#---------------------------------------------------------------------------------

TEXT1 	:= AfroDS
TEXT2 	:= dev by deuspi & yodapunk
TEXT3 	:= 
ICON 	:= -b $(CURDIR)/../logo.bmp

#---------------------------------------------------------------------------------
# TARGET is the name of the file to output
# BUILD is the directory where object files and intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
# MUSIC is a list of directories containing music files
#---------------------------------------------------------------------------------

TARGET		:= $(shell basename $(CURDIR))
BUILD		:= build
SOURCES		:= source data gfx/bin
INCLUDES	:= include build data gfx
MUSIC		:= music

#---------------------------------------------------------------------------------
# If you need to change other parts of the make process, see the PA_Makefile:
#---------------------------------------------------------------------------------

include $(DEVKITPRO)/PAlib/lib/PA_Makefile
