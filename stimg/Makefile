include ../vars.mk

SRCS = StartrackerImagerMain.cpp StartrackerImager.cpp
OBJS = StartrackerImagerMain.o StartrackerImager.o
BIN = stimg

all: $(BIN)
	make -C ../cdhlib
	make -C ../configmap
	make -C ../imglib
	make -C ../stlib

StartrackerImagerMain.o: StartrackerImagerMain.cpp
	$(CPP) $(CPPFLAGS) $(MILINC) StartrackerImagerMain.cpp -o StartrackerImagerMain.o
   
StartrackerImager.o: StartrackerImager.cpp
	$(CPP) $(CPPFLAGS) $(MILINC) StartrackerImager.cpp -o StartrackerImager.o
	
stimg: $(OBJS)
	$(CPP) -o stimg $(OBJS) $(LDFLAGS) $(CDHLIB) $(CFGMAP) $(IMGLIB) $(MILLIB) $(STLIB)

clean:
	-rm -f $(OBJS) $(BIN) $(TMP) 
