include ../vars.mk

SRCS = StartrackerCommandHandlerMain.cpp StartrackerCommandHandler.cpp
OBJS = StartrackerCommandHandlerMain.o StartrackerCommandHandler.o
BIN = stch

all: $(BIN)
	make -C ../cdhlib
	make -C ../configmap

StartrackerCommandHandlerMain.o: StartrackerCommandHandlerMain.cpp
	$(CPP) $(CPPFLAGS) StartrackerCommandHandlerMain.cpp -o StartrackerCommandHandlerMain.o
   
StartrackerCommandHandler.o: StartrackerCommandHandler.cpp
	$(CPP) $(CPPFLAGS) StartrackerCommandHandler.cpp -o StartrackerCommandHandler.o

stch: StartrackerCommandHandlerMain.o StartrackerCommandHandler.o
	$(CPP) -o $(BIN) $(OBJS) $(LDFLAGS) $(CDHLIB) $(CFGMAP) 

clean:
	-rm -f $(OBJS) $(BIN) $(TMP) 
