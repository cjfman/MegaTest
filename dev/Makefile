## Project Settings
PROJECT = AVRTest
MMCU    = atmega32
AVRCC   = avr-g++
AVRAR   = avr-ar
OBJCOPY = avr-objcopy

## Sources
SOURCES = Temp2.cpp AVRTestAll_main.cpp

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

test: Temp2.o AVRTestAll_main.o
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

AVRTestAll_main.o: AVRTestAll_main.cpp
#AVRTest.o AVRTestCase.o AVRTestLog.o AVRTestRegistrar.o AVRTestSuite.o 
	$(CMND) -c $^ -o $@

Temp2.o: Temp2.cpp
	$(CMND) -c $^ -o $@

AVRTest.o: AVRTest.cpp
	$(CMND) -c $^ -o $@
 
AVRTestCase.o: AVRTestCase.cpp
	$(CMND) -c $^ -o $@

AVRTestLog.o: AVRTestLog.cpp
	$(CMND) -c $^ -o $@

AVRTestRegistrar.o: AVRTestRegistrar.cpp
	$(CMND) -c $^ -o $@

AVRTestSuite.o: AVRTestSuite.cpp
	$(CMND) -c $^ -o $@

####################################################################

## AVR Compilations

$(PROJECT).hex: $(PROJECT).out
	$(OBJCOPY) -j .text -O ihex $^ $@

$(PROJECT).out: $(SOURCES)
	$(AVRCC) $(AVRFLAGS) -o $@ $^

AVR_AVRTestAll.o: AVRTestAll.cpp
	$(AVRCC) $(AVRFLAGS) -c $^ -o $@

AVR_Temp2.o: Temp2.cpp
	$(CMND) -c $^ -o $@
