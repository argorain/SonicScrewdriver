# COMPILERS
CC = avr-gcc
CXX = avr-g++
AS = avr-as
LD = avr-gcc
COPY = avr-objcopy

# BUILD FLAGS
ARCH_FLAGS	= -mmcu=atmega328p -DF_CPU=16000000UL

CFLAGS		+= -Os
CFLAGS		+= -Wextra -Wshadow -Wimplicit-function-declaration
CFLAGS		+= -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes
CFLAGS		+= -fno-common -ffunction-sections -fdata-sections

CXXFLAGS	+= -Os
CXXFLAGS	+= -Wextra -Wshadow -Wredundant-decls  -Weffc++
CXXFLAGS	+= -fno-common -ffunction-sections -fdata-sections

CPPFLAGS	+= -Wall -Wundef

ASFLAGS     += -MD -Wall

LDFLAGS		+= -Wl,-Map=$(BINARY).map
LDFLAGS		+= -Wl,--gc-sections

# BUILD RULES
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(ARCH_FLAGS) -o $(*).o -c $(*).c

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(ARCH_FLAGS) -o $(*).o -c $(*).cpp

%.o: %.s
	$(AS) $(ASFLAGS) $(ARCH_FLAGS) -o $(*).o -c $(*).s

# PROJECT DEFINES
BINARY = sonic
SOURCE = main.c drivers/usart.c
OBJS = main.o drivers/usart.o
HEADERS = drivers/usart.h

all: $(BINARY).elf

$(OBJS): $(SOURCE)

$(BINARY).elf: $(OBJS) $(HEADERS)
	$(LD) $(ARCH_FLAGS)  $(CPPFLAGS) $(LDFLAGS) $(OBJS) -o $(BINARY).elf
	$(COPY) -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "$(BINARY).elf" "$(BINARY).hex"

flash:
	@echo "Flashing into chip..."
	sudo avrdude -v -patmega328p -carduino -P/dev/ttyUSB0 -b57600 -D -Uflash:w:$(BINARY).hex:i

do:
	clean all flash

clean:
	$(RM) *.o *.d *.elf *.bin *.hex *.srec *.list *.map
	$(RM) drivers/*.o