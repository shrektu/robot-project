FILENAME	= main
PORT		= /dev/tty.wchusbserial10
DEVICE		= atmega328p
PROGRAMMER	= arduino
BAUD		= 115200
COMPILE		= avr-gcc -Wall -Os -mmcu=$(DEVICE) -I inc # Add 'inc' folder to include path

default: compile upload clean

compile:
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
	$(COMPILE) -c src/motors.c -o motors.o	# Compile motors.c file
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o motors.o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size $(FILENAME).elf

upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i

clean:
	rm $(FILENAME).o
	rm motors.o
	rm $(FILENAME).elf
	rm $(FILENAME).hex







