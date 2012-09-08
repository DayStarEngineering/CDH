include ../vars.mk

SRCS = StartrackerProcessorMain.cpp StartrackerProcessor.cpp TriBuffer.cpp
OBJS = StartrackerProcessorMain.o StartrackerProcessor.o TriBuffer.o
BIN = stpro

all: $(BIN)
	make -C ../cdhlib
	make -C ../configmap
	make -C ../imglib
	make -C ../stlib

#StartrackerProcessorData.o: StartrackerProcessorData.cpp
#	$(CPP) $(CPPFLAGS) $(MILINC) StartrackerProcessorData.cpp -o StartrackerProcessorData.o

StartrackerProcessorMain.o: StartrackerProcessorMain.cpp
	$(CPP) $(CPPFLAGS) $(MILINC) StartrackerProcessorMain.cpp -o StartrackerProcessorMain.o
   
StartrackerProcessor.o: StartrackerProcessor.cpp
	$(CPP) $(CPPFLAGS) $(MILINC) StartrackerProcessor.cpp -o StartrackerProcessor.o

Centroid.o: Centroid.cpp
	$(CPP) $(CPPFLAGS) $(MILINC) Centroid.cpp -o Centroid.o
	
TriBuffer.o: TriBuffer.cpp
	$(CPP) $(CPPFLAGS) $(MILINC) TriBuffer.cpp -o TriBuffer.o
	
stpro: $(OBJS)
	$(CPP) -o stpro $(OBJS) $(LDFLAGS) $(CDHLIB) $(CFGMAP) $(IMGLIB) $(MILLIB) $(STLIB)

clean:
	-rm -f $(OBJS) $(BIN) $(TMP) 
