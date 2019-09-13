LAST_NAME =Fagrey
FIRST_NAME =Nathaniel

CC = gcc

COBJS = main.o helpers.o blendImage.o \
	readwriteImage.o \
	subsampleImage.o 
ASMOBJS = smoothImage.o negateImage.o brightenImage.o grayscaleImage.o asmHelper.o contrastImage.o sharpenImage.o
INCLUDES = -I.
LIBDIRS = 
LIBS = 
DEFINES = 
CFLAGS = -g -Wall 
LFLAGS = -g 
DEPENDFLAGS = -M 


imagetool: $(COBJS) $(ASMOBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $(COBJS) $(ASMOBJS) $(LIBDIRS) $(LIBS)

.c.o:
	$(CC) -c $(DEFINES) $(CFLAGS) $(INCLUDES) $<

.s.o:
	$(CC) -c $(DEFINES) $(CFLAGS) $(INCLUDES) $<

.S.o:
	$(CC) -c $(DEFINES) $(CFLAGS) $(INCLUDES) $<

clean:
	rm -f *.o imagetool

realclean: clean
	rm -f *~ .depend

tarfile: realclean
	rm -f $(LAST_NAME)_$(FIRST_NAME).tgz
	cp -rp . /tmp/$(LAST_NAME)_$(FIRST_NAME)                                                                                                                                                                                                   
	cd /tmp; tar cfz $(LAST_NAME)_$(FIRST_NAME).tgz $(LAST_NAME)_$(FIRST_NAME)
	mv /tmp/$(LAST_NAME)_$(FIRST_NAME).tgz .
	rm -rf /tmp/$(LAST_NAME)_$(FIRST_NAME)
	make depend



# make depend will create a file ".depend" with all the dependencies
depend:
	rm -f .depend
	$(CC) $(DEFINES) $(INCLUDES) $(DEPENDFLAGS) $(COBJS:.o=.c) > .depend

# if we have a .depend file, include it

ifeq (.depend,$(wildcard .depend))
include .depend
endif
