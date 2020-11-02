#
# setup control
#
#DEBUG = TRUE
TOP     := $(shell pwd)/
OBJ     := $(TOP)obj/
BIN     := $(TOP)bin/
SRC     := $(TOP)src/
INCLUDE  := $(TOP)include/

#ROOTCFLAGS    = $(shell root-config --cflags)
#ROOTLIBS      = $(shell root-config --libs)
#ROOTGLIBS     = $(shell root-config --glibs)

#	
# set up compilers
#	
CPP     = g++
CPPFLAGS = -O -Wall -fPIC -I$(INCLUDE)
#if other package, ROOT for example, is needed to be included, use the following line.
#CPPFLAGS = -O -Wall -fPIC -I$(INCLUDE) -I$(ROOTCFLAGS)
#CPPFLAGS = -Wall -ansi -pedantic -Wno-long-long -I$(INCLUDE) -I$(ROOTCFLAGS) -I. $(LCIOINCLUDES) -D_REENTRANT

#CPPLIBS = $(ROOTLIBS) $(ROOTGLIBS)
#CC      = gcc

ifeq ($(DEBUG), TRUE)
CPPFLAGS += -g
endif

ifeq ($(PURIFY), TRUE)
LD = purify $(CPP)
else
LD     = $(CPP)
endif

############## Make Executables ####################################
all: ex22

ex22	: $(patsubst $(SRC)%.cc,$(OBJ)%.o,$(wildcard $(SRC)*.cc))
	$(LD) $^ $(CPPLIBS) -o $(BIN)$(notdir $@)
	@echo

######################################################
$(OBJ)%.o : 	$(SRC)%.cc
	$(CPP)  $(CPPFLAGS) -c $(SRC)$(notdir $<) -o $(OBJ)$(notdir $@)
	@echo	

.PHONY:clean
clean:
	rm -f $(OBJ)*.o 
	rm -f $(BIN)*
