include ../vars.mk

SRCS = SubsystemMessengerMain.cpp SubsystemMessenger.cpp
OBJS = SubsystemMessengerMain.o SubsystemMessenger.o
BIN = ssm

all: $(BIN)
	make -C ../cdhlib
	make -C ../configmap

SubsystemMessengerMain.o: SubsystemMessengerMain.cpp
	$(CPP) $(CPPFLAGS) SubsystemMessengerMain.cpp -o SubsystemMessengerMain.o
   
SubsystemMessenger.o: SubsystemMessenger.cpp
	$(CPP) $(CPPFLAGS) SubsystemMessenger.cpp -o SubsystemMessenger.o

ssm: SubsystemMessenger.o SubsystemMessengerMain.o
	$(CPP) -o $(BIN) $(OBJS) $(LDFLAGS) $(CDHLIB) $(CFGMAP) 

clean:
	-rm -f $(OBJS) $(BIN) $(TMP) 
