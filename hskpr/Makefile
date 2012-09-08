include ../vars.mk

SRCS = HouseKeeperMain.cpp HouseKeeper.cpp
OBJS = HouseKeeperMain.o HouseKeeper.o
BIN = hskpr

all: $(BIN)
	make -C ../cdhlib
	make -C ../configmap

HouseKeeperMain.o: HouseKeeperMain.cpp
	$(CPP) $(CPPFLAGS) HouseKeeperMain.cpp -o HouseKeeperMain.o
   
HouseKeeper.o: HouseKeeper.cpp
	$(CPP) $(CPPFLAGS) HouseKeeper.cpp -o HouseKeeper.o

hskpr: HouseKeeperMain.o HouseKeeper.o
	$(CPP) -o $(BIN) $(OBJS) $(LDFLAGS) $(CDHLIB) $(CFGMAP) 

clean:
	-rm -f $(OBJS) $(BIN) $(TMP) 
