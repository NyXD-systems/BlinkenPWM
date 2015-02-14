MCU = atmega328p
AVRDUDE_DEVICE = m328p
F_CPU = 16000000

INCLUDES = -I./include -I/usr/lib/avr/include
CFLAGS=-g -Wall -mcall-prologues -mmcu=$(MCU) $(DEVICE_SPECIFIC_CFLAGS) $(INCLUDES) -Os
CPPFLAGS=-fno-exceptions $(INCLUDES) -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -std=c++11
CC=avr-gcc
CXX=avr-g++

OBJ2HEX=avr-objcopy 
LDFLAGS=-Wl,-gc-sections -Wl,-relax 

AVRDUDE=avrdude

TARGET=main
OBJECT_FILES=main.o


all: $(TARGET).hex

clean:
	rm -f *.o *.hex *.obj *.hex

%.hex: %.obj
	$(OBJ2HEX) -R .eeprom -O ihex $< $@

main.o: main.c
uart.o: uart.c

%.obj: $(OBJECT_FILES)
	$(CXX) $(CFLAGS) $(OBJECT_FILES) $(LDFLAGS) -o $@

program: $(TARGET).hex
	$(AVRDUDE) -p $(AVRDUDE_DEVICE) -c arduino -U flash:w:$(TARGET).hex -P /dev/tty.wchusbserial5d10