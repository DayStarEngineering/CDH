include ../vars.mk

SRCS = DataCollectorMain.cpp DataCollector.cpp
OBJS = DataCollectorMain.o DataCollector.o
BIN = dcol

all: $(BIN)
	make -C ../cdhlib
	make -C ../configmap

DataCollectorMain.o: DataCollectorMain.cpp
	$(CPP) $(CPPFLAGS) DataCollectorMain.cpp -o DataCollectorMain.o
   
DataCollector.o: DataCollector.cpp
	$(CPP) $(CPPFLAGS) DataCollector.cpp -o DataCollector.o

dcol: DataCollectorMain.o DataCollector.o
	$(CPP) -o $(BIN) $(OBJS) $(LDFLAGS) $(CDHLIB) $(CFGMAP) 

clean:
	-rm -f $(OBJS) $(BIN) $(TMP) 
