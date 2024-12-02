## Project Settings
PROJECT = MegaTest
MMCU    = atmega32
AVRCC   = avr-g++
AVRAR   = avr-ar
OBJCOPY = avr-objcopy

## Sources
SOURCES = Temp2.cpp MegaTestAll_main.cpp

## Directories

AVR_STL_DIR = avr-stl/include
ARDUINO_DIR = Arduino

## Test Compiler Flags
CPPFLAGS = -I $(ARDUINO_DIR) #-I $(AVR_STL_DIR) 
CXXFLAGS = -g -Wall -Wextra
FLAGS = $(CPPFLAGS) $(CXXFLAGS)
CMND = $(CXX) $(FLAGS)

## AVR Compiler Flags
AVRFLAGS = -mmcu=$(MMCU) -Wall -I./ $(CPPFLAGS)

###############################################

all: test

run: clean all
	./test

debug: clean all
	gdb test

test: Temp2.o MegaTestAll_main.o
	$(CMND) $^ -o $@

avr: avrclean $(PROJECT).hex

clean:
	rm -rf *.o *.dSYM test

avrclean:
	rm -rf $(PROJECT).out $(PROJECT).hex

defines:
	echo "main(){}" | $(CXX) -E -x c -dM - 


avrdefines:
	echo "main(){}" | $(AVRCC) $(AVRFLAGS) -E -dM -
 
####################################################################

## Test Compilations

MegaTestAll_main.o: MegaTestAll_main.cpp
#MegaTest.o MegaTestCase.o MegaTestLog.o MegaTestRegistrar.o MegaTestSuite.o 
	$(CMND) -c $^ -o $@

Temp2.o: Temp2.cpp
	$(CMND) -c $^ -o $@

MegaTest.o: MegaTest.cpp
	$(CMND) -c $^ -o $@
 
MegaTestCase.o: MegaTestCase.cpp
	$(CMND) -c $^ -o $@

MegaTestLog.o: MegaTestLog.cpp
	$(CMND) -c $^ -o $@

MegaTestRegistrar.o: MegaTestRegistrar.cpp
	$(CMND) -c $^ -o $@

MegaTestSuite.o: MegaTestSuite.cpp
	$(CMND) -c $^ -o $@

####################################################################

## AVR Compilations

$(PROJECT).hex: $(PROJECT).out
	$(OBJCOPY) -j .text -O ihex $^ $@

$(PROJECT).out: $(SOURCES)
	$(AVRCC) $(AVRFLAGS) -o $@ $^

AVR_MegaTestAll.o: MegaTestAll.cpp
	$(AVRCC) $(AVRFLAGS) -c $^ -o $@

AVR_Temp2.o: Temp2.cpp
	$(CMND) -c $^ -o $@
