# Makefile tutorial: https://www.gnu.org/software/make/manual/html_node/index.html#SEC_Contents
 
# Make variables ----------------------------------------------------

# Setup for wxWidgets and ROOT
WXCONF=$(shell wx-config --cxxflags --libs)

# Code position directories
SRC=./src
BIN=.
IDIR=./include

# Compiler options
COMPOPT=-fPIC -g -std=c++11 -Wno-deprecated

# Include directories
INC=-I. -I$(IDIR)

# Filenames for source files
FILES=$(wildcard $(SRC)/*.cpp)
# -------------------------------------------------------------------

# General make options
all: $(BIN)/fd_shift_clock

# Make for the FD shift clock program
$(BIN)/fd_shift_clock: $(FILES)
	@echo "# Compiling the FD shift clock program ------------------------------------------"
	$(CXX) $(INC) $(COMPOPT) $(FILES) $(CPPFLAGS) -o $@ $(WXCONF)

# Rules for cleaning the installation
clean:
	@echo "# Cleaning the installation directory -----------------------------------------"
	rm -fr $(BIN)/fd_shift_clock
