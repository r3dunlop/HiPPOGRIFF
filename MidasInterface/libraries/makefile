# Makefile

ifndef BASE
BASE=..
endif

CFLAGS += -Wall -Wuninitialized

# optional ZLIB library

CFLAGS += -DHAVE_ZLIB -I$(BASE)/include

# ROOT libraries

#ifdef ROOTSYS
#ROOTLIBS  = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --libs)  -lXMLParser -lThread
#ROOTGLIBS = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --glibs) -lXMLParser -lThread
#RPATH    += -Wl,-rpath,$(ROOTSYS)/lib
CFLAGS += -DHAVE_ROOT $(shell $(ROOTSYS)/bin/root-config --cflags) -std=c++0x
#endif

ALL:= libMidasInterface.a libMidasInterface.so

OBJS:=
OBJS += TMidasEvent.o
OBJS += TMidasEventDict.o
OBJS += TMidasFile.o
OBJS += TMidasFileDict.o

#ifdef MIDASSYS
#CFLAGS += -I$(MIDASSYS)/include
#OBJS += TMidasOnline.o
#OBJS += TMidasOnlineDict.o
#endif

#ifdef ROOTSYS
OBJS += XmlOdb.o #HttpOdb.o
OBJS += XmlOdbDict.o
#endif

all: $(ALL)

libMidasInterface.a: $(OBJS)
	-rm -f $@
	ar -rv $@ $^
	#cp -p $@ $(BASE)/libraries

libMidasInterface.so: $(OBJS)
	g++ -dynamiclib -single_module -undefined dynamic_lookup -install_name $@ $(CFLAGS) -olibMidasInterface.so $(OBJS) -L$(ROOTSYS)/lib #-lNet 
	#cp -p $@ $(BASE)/libraries

#%Dict.cxx: %.h
#	LD_LIBRARY_PATH=$(ROOTSYS)/lib $(ROOTSYS)/bin/rootcint -f $@ -c $^

%.o: %.cxx
	$(CXX) $(CFLAGS) -c $<

TMidasOnlineDict.cxx: $(BASE)/include/TMidasOnline.h
	rootcint TMidasOnlineDict.cxx -c $(BASE)/include/TMidasOnline.h

TMidasFileDict.cxx: $(BASE)/include/TMidasFile.h
	rootcint TMidasFileDict.cxx -c $(BASE)/include/TMidasFile.h

TMidasEventDict.cxx: $(BASE)/include/TMidasEvent.h
	rootcint TMidasEventDict.cxx -c $(BASE)/include/TMidasEvent.h

XmlOdbDict.cxx: $(BASE)/include/XmlOdb.h
	rootcint XmlOdbDict.cxx -c $(BASE)/include/XmlOdb.h


dox:
	doxygen

clean:
	-rm -f *.o *.a *.exe *.so *Dict* $(ALL)

# end
