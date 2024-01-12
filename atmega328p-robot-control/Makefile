FILENAME	= main
#PORT		= /dev/tty.wchusbserial110
PORT		= /dev/ttyUSB0
DEVICE		= atmega328p
PROGRAMMER	= arduino
BAUD		= 115200
COMPILE		= avr-gcc -Os -mmcu=$(DEVICE) -I inc # Add 'inc' folder to include path

default: compile upload clean

compile:
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
	$(COMPILE) -c src/motors.c -o motors.o		# Compile motors.c file
	$(COMPILE) -c src/lcd.c -o lcd.o			# Compile lcd.c file
	$(COMPILE) -c src/adc.c -o adc.o			# Compile adc.c file
	$(COMPILE) -c src/usart.c -o usart.o		# Compile usart.o file
	$(COMPILE) -c src/HC-SR04.c -o HC-SR04.o	# Compile HC-SR04.c file
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o motors.o lcd.o adc.o HC-SR04.o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
	avr-size $(FILENAME).elf

upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i

clean:
	rm $(FILENAME).o
	rm motors.o
	rm lcd.o
	rm adc.o
	rm usart.o
	rm HC-SR04.o
	rm $(FILENAME).elf
	rm $(FILENAME).hex







