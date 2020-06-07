FILENAME   = blinky
PORT       = usb
DEVICE     = atmega32
PROGRAMMER = USBasp
COMPILE    = avr-gcc -Wall -Os -mmcu=$(DEVICE) 
HFUSE      = hfuse:w:0b10011001:m
LFUSE      = lfuse:w:0b11100001:m


compile:
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex 
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf


flash: upload clean

upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -U flash:w:$(FILENAME).hex:i

clean:
	rm $(FILENAME).o
	rm $(FILENAME).elf
	rm $(FILENAME).hex

fuse:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -U $(HFUSE) -U $(LFUSE)