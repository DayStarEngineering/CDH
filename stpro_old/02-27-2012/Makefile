include ../vars.mk

SRCS = StartrackerProcessorMain.cpp StartrackerProcessor.cpp Centroid.cpp CentroidTest.cpp StartrackerProcessorData.cpp
OBJS = StartrackerProcessorMain.o StartrackerProcessor.o Centroid.o StartrackerProcessorData.o
BIN = stpro CentroidTest

all: $(BIN)
	make -C ../cdhlib
	make -C ../configmap
	make -C ../imglib

StartrackerProcessorData.o: StartrackerProcessorData.cpp
	$(CPP) $(CPPFLAGS) StartrackerProcessorData.cpp -o StartrackerProcessorData.o

StartrackerProcessorMain.o: StartrackerProcessorMain.cpp
	$(CPP) $(CPPFLAGS) StartrackerProcessorMain.cpp -o StartrackerProcessorMain.o
   
StartrackerProcessor.o: StartrackerProcessor.cpp
	$(CPP) $(CPPFLAGS) StartrackerProcessor.cpp -o StartrackerProcessor.o

Centroid.o: Centroid.cpp
	$(CPP) $(CPPFLAGS) Centroid.cpp -o Centroid.o

CentroidTest: CentroidTest.cpp Centroid.cpp StartrackerProcessorData.cpp
	$(CPP) -O2 -mtune=core2 -march=core2 -m64 -pipe CentroidTest.cpp Centroid.cpp StartrackerProcessorData.cpp -o CentroidTest $(CDHLIB) $(CFGMAP)

stpro: $(OBJS)
	$(CPP) -o stpro $(OBJS) $(LDFLAGS) $(CDHLIB) $(CFGMAP) 

clean:
	-rm -f $(OBJS) $(BIN) 
