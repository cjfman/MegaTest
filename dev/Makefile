## Project Settings
PROJECT = MegaTest
TARGET  = $(PROJECT)
MMCU    = atmega32
AVRCC   = avr-g++
AVRAR   = avr-ar
OBJCOPY = avr-objcopy

## Sources
MAIN = MegaTest_main.cpp
SOURCES :=                \
	MegaTest.cpp          \
	MegaTestCase.cpp      \
	MegaTestLog.cpp       \
	MegaTestRegistrar.cpp \
	MegaTestSuite.cpp     \
	#Temp2.cpp             \

## Directories

AVR_STL_DIR = avr-stl/include
ARDUINO_DIR = Arduino

## Test Compiler Flags
CPPFLAGS = -I $(ARDUINO_DIR) #-I $(AVR_STL_DIR) 
CXXFLAGS = -g -Wall -Wextra
FLAGS = $(CPPFLAGS) $(CXXFLAGS) -DDESKTOP
CMND = $(CXX) $(FLAGS)

## AVR Compiler Flags
AVRFLAGS = -mmcu=$(MMCU) -Wall -I./ $(CPPFLAGS)

###############################################

all: test

run: clean all
	./test

debug: clean all
	gdb test

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

## Basic Compilations

OBJS := $(SOURCES:%.cpp=%.cpp.o) MegaTest_main.cpp.o Temp2.cpp.o 

$(OBJS): %.cpp.o: %.cpp
	$(CXX) $(FLAGS) -o $@ -c $^
 
MegaTest_run_test: $(OBJS)
	$(CXX) $(FLAGS) $^ -o $@

test: MegaTest_run_test
	./MegaTest_run_test

####################################################################

## AVR Compilations

AVR_OBJS := $(SOURCES:%.cpp=%.cpp.avr.o)

$(AVR_OBJS): %.cpp.avr.o: %.cpp
	$(AVRGCC) -c $^ -o $@

$(TARGET).hex: $(TARGET).out
	$(OBJCOPY) -j .text -O ihex $^ $@

$(TARGET).out: $(AVR_OBJS)
	$(AVRCC) $(AVRFLAGS) -o $@ $^

$(TARGET): $(MAIN) $(AVR_OBJS)
	$(AVRCC) $(AVRFLAGS) -c $^ -o $@

#AVR_Temp2.o: Temp2.cpp
#	$(CMND) -c $^ -o $@
