CCFLAGS = -std=gnu99 -Wall -Werror
LDFLAGS = 
LIBS	=

.PHONY: all clean

all:: i2c initIO readSwitch setLED copy

i2c: i2c.o vend_i2c.o
	${CC} ${LDFLAGS} -o i2c i2c.o vend_i2c.o ${LIBS}
	
initIO: initIO.o vend_i2c.o
	${CC} ${LDFLAGS} -o initIO initIO.o vend_i2c.o ${LIBS}

setLED: setLED.o vend_i2c.o
	${CC} ${LDFLAGS} -o setLED setLED.o vend_i2c.o ${LIBS}

readSwitch: readSwitch.o vend_i2c.o
	${CC} ${LDFLAGS} -o readSwitch readSwitch.o vend_i2c.o ${LIBS}

readSwitch.o: readSwitch.c vend_i2c.h
	${CC} ${CCFLAGS} -c readSwitch.c
	
i2c.o: i2c.c vend_i2c.h
	${CC} ${CCFLAGS} -c i2c.c

setLED.o: setLED.c vend_i2c.h
	${CC} ${CCFLAGS} -c setLED.c

initIO.o: initIO.c vend_i2c.h
	${CC} ${CCFLAGS} -c initIO.c

vend_i2c.o: vend_i2c.c vend_i2c.h
	${CC} ${CCFLAGS} -c vend_i2c.c

copy:
	cp i2c ../
	cp initIO ../
	cp setLED ../
	cp readSwitch ../

clean::
	rm -f *.o *~
	
distclean:: clean
	rm -f i2c
	rm -f setLED
	rm -f initIO
	rm -f readSwitch
