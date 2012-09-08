include ../vars.mk

SRCS = pdogmain.cpp ProcessWatchdog.cpp
OBJS = pdogmain.o ProcessWatchdog.o
BIN = pdog

all: $(BIN)
	make -C ../cdhlib
	make -C ../configmap

pdogmain.o: pdogmain.cpp
	$(CPP) $(CPPFLAGS) pdogmain.cpp -o pdogmain.o
   
ProcessWatchdog.o: ProcessWatchdog.cpp
	$(CPP) $(CPPFLAGS) ProcessWatchdog.cpp -o ProcessWatchdog.o

pdog: pdogmain.o ProcessWatchdog.o
	$(CPP) -o $(BIN) $(OBJS) $(LDFLAGS) $(CDHLIB) $(CFGMAP) 

clean:
	-rm -f $(OBJS) $(BIN) $(TMP) 
