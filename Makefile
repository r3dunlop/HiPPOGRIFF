.EXPORT_ALL_VARIABLES:

.SUFFIXES:

.PHONY: clean all

# := is only evaluated once

SHELL 		= /bin/sh

NAME		= MidUnpack
VERSION		= 1.0.1

LIB_DIR 	= $(ROOTSYS)/lib
BIN_DIR		= $(ROOTSYS)/bin

ROOTLIBS     	:= $(shell root-config --libs)
ROOTINC      	:= -I$(shell root-config --incdir)

COMMON_DIR 	= $(HOME)/Common

INCLUDES        = -I$(COMMON_DIR) -I. -I./MidasInterface/include

LIBRARIES	= 

CC			= /opt/local/bin/gcc
CXX         = /opt/local/bin/g++
CPPFLAGS 	= $(ROOTINC) $(INCLUDES) -fPIC
CXXFLAGS	= -std=c++11 -pedantic -lz -Wall -Wno-long-long -g -O3

LDFLAGS		= -g -fPIC

LDLIBS 		= -L$(LIB_DIR) -Wl,-rpath,/opt/gcc/lib64 $(ROOTLIBS) $(addprefix -l,$(LIBRARIES))

LOADLIBES = \
	TGriffinFragment.o\
	TFragmentQueue.o\
	MidasEventParser.o \
	Settings.o\
	TFragmentWriter.o\
	$(NAME)Dictionary.o

# -------------------- implicit rules --------------------
# n.o made from n.c by 		$(CC) -c $(CPPFLAGS) $(CFLAGS)
# n.o made from n.cc by 	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS)
# n made from n.o by 		$(CC) $(LDFLAGS) n.o $(LOADLIBES) $(LDLIBS)

# -------------------- rules --------------------

all:  lib$(NAME).so lib$(NAME).a $(NAME) 
	@echo Done

# -------------------- libraries --------------------

lib$(NAME).so: $(LOADLIBES)
	$(CXX) -install_name lib$(NAME).so $(LDFLAGS) $(CXXFLAGS) $(CPPFLAGS) -shared -o lib$(NAME).$(VERSION).so $(LOADLIBES) -lc `root-config --libs` $(LDLIBS)

lib$(NAME).a: $(LOADLIBES)
	ar rcs lib$(NAME).a $(LOADLIBES) 

#$(LIB_DIR)/libMacros.so:
#	@cd $(MACRO_DIR); make $@

# -------------------- pattern rules --------------------
# this rule sets the name of the .cc file at the beginning of the line (easier to find)

%.o: %.cc %.hh
	$(CXX) $< -c $(CPPFLAGS) $(CXXFLAGS) -o $@

# -------------------- default rule for executables --------------------

%: %.cc $(LOADLIBES)
	$(CXX) $< $(CXXFLAGS) $(CPPFLAGS) -L. -lMidUnpack MidasInterface/libraries/libMidasInterface.a $(LDLIBS) -o $@

# -------------------- Root stuff --------------------

DEPENDENCIES = \
	TGriffinFragment.hh \
	TFragmentQueue.hh
#	RootLinkDef.h

$(NAME)Dictionary.o: $(NAME)Dictionary.cc $(NAME)Dictionary.h
	 $(CXX) -fPIC $(CXXFLAGS) $(CPPFLAGS) -c $<

$(NAME)Dictionary.cc: $(DEPENDENCIES)
	 rm -f $(NAME)Dictionary.cc $(NAME)Dictionary.h; rootcint -v -f $@ -c $(CPPFLAGS) $(DEPENDENCIES)

# -------------------- tar ball --------------------

tar:
	@echo "creating zipped tar-ball ... "
	tar -chvzf $(NAME).tar.gz Makefile \
	*.hh *.cc \
#	Settings.dat

# -------------------- clean --------------------

clean:
	rm  -f $(NAME) *.o *Dict* *.a *.so
