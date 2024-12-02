TARGET	=	YOUR_TEST
MCU	=	atmega2560
F_CPU	=	16000000UL
# LIBS	=	ITDB02

# Location of Arudino libraries
MEGATEST = /MegaTest
BASE	= $(MEGATEST)/Arduino 
# Location of MegaTest

## DO NOT EDIT SECTION ##
ARDUINO = $(BASE)/hardware/arduino
ARDCORE = $(ARDUINO)/cores/arduino
LIBDIR  = $(BASE)/libraries
## END SECTION ##

# Arudino Libraries to be linked
# Example: LIBS = SPI
LIBS    =

# The directory that contains your tests.
TARG_SRC = ./

# Any additional directories that need to be included
USER_DIRS =

# All sources that contain or are realated to your tests
SOURCES = 

# The name of your configuration file. Leave blank if you wish to use the default configuration.
CONFIGURATION =

## DO NOT EDIT SECTION ##
INCLUDES = -I $(ARDUINO)/cores/arduino \
	-I $(LIBDIR) \
	$(LIBS:%=-I$(LIBDIR)/%) \
	-I $(ARDUINO)/variants/mega \
	-I $(MEGATEST)/include \
	-I $(TARG_SRC) \
	$(USER_DIRS:%=-I$(USER_DIRS)/%)
## END SECTION ##

# The serial port to use for programing
PORT	= 	/dev/tty.usbmodemfa141

CC	=	avr-gcc
CXX	=	avr-g++

OBJCOPY = avr-objcopy

UPLOAD_RATE = 115200
# AVRDUDE = $(BASE)/tools/avrdude
AVRDUDE = avrdude
AVRDUDE_PROGRAMMER = stk500v2
AVRDUDE_PORT = $(PORT)
AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER) -b $(UPLOAD_RATE)

# -C $(BASE)/tools/avrdude.conf

# Compiler Flags
CTUNING = -funsigned-char -funsigned-bitfields -fpack-struct \
	-fshort-enums -ffunction-sections -fdata-sections -w
WARNINGS = -Wall
ALLFLAGS= -Os \
	  -mmcu=$(MCU) -DF_CPU=$(F_CPU) \
	  -D ARDUINO=180 -D MEGATEST \
	  $(CTUNING) \
	  $(WARNINGS)
CFLAGS	= $(INCLUDES) $(ALLFLAGS) 
LDFLAGS	= $(ALLFLAGS) -Wl,-gc-sections -lm
FORMAT 	= ihex

ifdef CONFIGURATION
	ALLFLAGS += -D MEGATEST_CONFIGURATION_FILE=$(CONFIGURATION)
endif

ALIBS	= $(LIBS:%=$(LIBDIR)/%)

# Final Source Lists
# If you want to link against the Arduino core, uncomment the lines in the list
# below that say ARDUINO or ALIBS. Note that the entries in the list must be
# continuous and cannot contain comments between them.
# Don't forget to add a line extention character "\" to the previous entry!
SRC 	= #$(wildcard $(TARG_SRC)/*.c)
	  #$(wildcard $(ARDUINO)/cores/arduino/*.c) \
	  #$(wildcard $(ALIBS:%=%/*.c)) \
	  
CXXSRC	= $(SOURCES) \
	  $(MEGATEST)/src/MegaTestAll.cpp
	  #$(wildcard $(TARG_SRC)/*.cpp) \
	  #$(wildcard $(ARDUINO)/cores/arduino/*.cpp) \
	  #$(wildcard $(ALIBS:%=%/*.cpp)) \
	  #$(wildcard $(MEGATEST:%=%/*.cpp))

## DO NOT EDIT SECTION ##	  
OBJS 	= $(SRC:.c=.c.o) $(CXXSRC:.cpp=.cpp.o)


all: build


build: $(TARGET).elf $(TARGET).hex

program: upload
upload: $(TARGET).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)


$(TARGET).elf: $(OBJS)
	$(CC) -o $(TARGET).elf $(OBJS) $(LDFLAGS)

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

$(TARGET).eep: $(TARGET).elf
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O $(FORMAT) $< $@


%.cpp.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<

%.c.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -fv $(OBJS)
	rm -fv $(TARGET).o
	rm -fv $(TARGET).eep
	rm -fv $(TARGET).hex
	rm -fv $(TARGET).elf
## END SECTION ##