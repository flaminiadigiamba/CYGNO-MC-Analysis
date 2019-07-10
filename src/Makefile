# Makefile for the ROOT test programs.
# This Makefile shows nicely how to compile and link applications
# using the ROOT libraries on all supported platforms.
#
# Copyright (c) 2000 Rene Brun and Fons Rademakers
#
# Author: Fons Rademakers, 29/2/2000

#include Makefile.arch

#------------------------------------------------------------------------------
DEBUG = on

# Debug mode ?
ifeq ($(DEBUG),on)
	CXXFLAGS += -DCF__DEBUG -g
endif

ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)
 
CXX           = g++
CXXFLAGS      = -g -Wall -fPIC -Wno-deprecated
LD            = g++
LDFLAGS       = -g
SOFLAGS       = -shared

NGLIBS         = $(ROOTGLIBS) 
NGLIBS        += -lMinuit
gGLIBS          = $(filter-out -lNew, $(NGLIBS))

CXXFLAGS      += $(ROOTCFLAGS)
CXX           += -I../include
LIBS           = $(ROOTLIBS) 

NGLIBS         = $(ROOTGLIBS) 
NGLIBS        += -lMinuit
GLIBS          = $(filter-out -lNew, $(NGLIBS))

CXXFLAGS      += $(ROOTCFLAGS)
CXX           += -I../include
LIBS           = $(ROOTLIBS) 

NGLIBS         = $(ROOTGLIBS) 
NGLIBS        += -lMinuit
GLIBS          = $(filter-out -lNew, $(NGLIBS))

CXX           += -I../include
OUTLIB        = ../lib


.SUFFIXES: .cc,.C
.PREFIXES: ./lib/

CYGNOTree.o: CYGNOTree.C
	$(CXX) $(CXXFLAGS) -I$(CHIMERALD)/event -c -I../include -o CYGNOTree.o $<
CYGNOAnalysis.o: CYGNOAnalysis.C
	$(CXX) $(CXXFLAGS) -I$(CHIMERALD)/event -c -I../include -o CYGNOAnalysis.o $<

# ==================== unfolding ===========================================
obj: CYGNOTree.o CYGNOAnalysis.o 
#obs: lib/Subject.o
all:  main.cpp obj 
	$(CXX) $(CXXFLAGS) -I$(CHIMERALD)/event  -o ../CYGNOAnalysis *.o -I$(CHIMERALD)/event -L$(CHIMERALD)  -Wl,-rpath=$(CHIMERALD) $(CHIMERALIB) $(GLIBS) $<
#unfolding: unfolding.cxx lib/bayes.o
#	$(CXX) $(CXXFLAGS) -o unfolding $(OUTLIB)/*.o $(GLIBS) $<
#unfolding2D: unfolding2D.cxx lib/bayes.o
#	$(CXX) $(CXXFLAGS) -o unfolding2D $(OUTLIB)/*.o $(GLIBS) $<
#allp_spec: allp_spec.cpp lib/bayes.o
#	$(CXX) $(CXXFLAGS) -o allp_spec $(OUTLIB)/*.o $(GLIBS) $<
#unfolding.clean:
#	rm -f unfolding
#unfolding2D.clean:
#	rm -f unfolding2D
#allp_spec.clean:
#	rm -f allp_spec
# =============================================================================

clean:
	rm -f *.o
	rm -f ../CYGNOAnalysis

