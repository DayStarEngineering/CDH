include ../vars.mk

OBJS=Logger.o SemaphoreWrapper.o MsgQueueWrapper.o DataWriter.o DataParser.o PortInterface.o GlobalLock.o Command.o SubsystemInterface.o Timer.o GlobalVar.o #BusInterface.o
LIBS=liblogger.so libsw.so libmsgqw.so libdw.so libdp.so libpi.so libgl.so libcmd.so libssi.so libtimer.so libgv.so #libbi.so
BIN=PITest GLTest GVTest #BITest DWTest DPTest

all: $(OBJS) $(LIBS) $(BIN)
	
Logger.o: Logger.cpp
	$(CPP) $(LIBFLAGS) Logger.cpp -o Logger.o	

SemaphoreWrapper.o: SemaphoreWrapper.cpp
	$(CPP) $(LIBFLAGS) SemaphoreWrapper.cpp -o SemaphoreWrapper.o

MsgQueueWrapper.o: MsgQueueWrapper.cpp
	$(CPP) $(LIBFLAGS) MsgQueueWrapper.cpp -o MsgQueueWrapper.o
		
DataWriter.o: DataWriter.cpp
	$(CPP) $(LIBFLAGS) DataWriter.cpp -o DataWriter.o

DataParser.o: DataParser.cpp
	$(CPP) $(LIBFLAGS) DataParser.cpp -o DataParser.o
	
PortInterface.o: PortInterface.cpp
	$(CPP) $(LIBFLAGS) PortInterface.cpp -o PortInterface.o
	
GlobalLock.o: GlobalLock.cpp
	$(CPP) $(LIBFLAGS) GlobalLock.cpp -o GlobalLock.o

GlobalVar.o: GlobalVar.cpp
	$(CPP) $(LIBFLAGS) GlobalVar.cpp -o GlobalVar.o
		
Command.o: Command.cpp
	$(CPP) $(LIBFLAGS) Command.cpp -o Command.o

SubsystemInterface.o: SubsystemInterface.cpp
	$(CPP) $(LIBFLAGS) SubsystemInterface.cpp -o SubsystemInterface.o

#BusInterface.o: BusInterface.cpp
#	$(CPP) $(LIBFLAGS) BusInterface.cpp -o BusInterface.o

Timer.o: Timer.cpp
	$(CPP) $(LIBFLAGS) Timer.cpp -o Timer.o
		
liblogger.so: Logger.o
	$(CPP) $(LDFLAGS) -shared -o liblogger.so Logger.o

libsw.so: SemaphoreWrapper.o
	$(CPP) $(LDFLAGS) -shared -o libsw.so SemaphoreWrapper.o

libmsgqw.so: MsgQueueWrapper.o
	$(CPP) $(LDFLAGS) -shared -o libmsgqw.so MsgQueueWrapper.o
		
libdw.so: DataWriter.o
	$(CPP) $(LDFLAGS) -shared -o libdw.so DataWriter.o

libdp.so: DataParser.o
	$(CPP) $(LDFLAGS) -shared -o libdp.so DataParser.o
	
libpi.so: PortInterface.o
	$(CPP) $(LDFLAGS) -shared -o libpi.so PortInterface.o

libgl.so: GlobalLock.o
	$(CPP) $(LDFLAGS) -shared -o libgl.so GlobalLock.o

libgv.so: GlobalVar.o
	$(CPP) $(LDFLAGS) -shared -o libgv.so GlobalVar.o
		
libcmd.so: Command.o
	$(CPP) $(LDFLAGS) -shared -o libcmd.so Command.o
	
libssi.so: SubsystemInterface.o
	$(CPP) $(LDFLAGS) -shared -o libssi.so SubsystemInterface.o
	
libbi.so: BusInterface.o
	$(CPP) $(LDFLAGS) -shared -o libbi.so BusInterface.o

libtimer.so: Timer.o
	$(CPP) $(LDFLAGS) -shared -o libtimer.so Timer.o

GLTest: GlobalLockTest.cpp GlobalLock.cpp
	$(CPP) -Wall -pthread GlobalLockTest.cpp GlobalLock.cpp -o GLTest

GVTest: GlobalVarTest.cpp GlobalVar.cpp
	$(CPP) -Wall -pthread GlobalVarTest.cpp GlobalVar.cpp -o GVTest
	
#DPTest: DataParserTest.cpp DataWriter.cpp DataParser.cpp 
#	$(CPP) -Wall DataParserTest.cpp DataWriter.cpp DataParser.cpp  -o DPTest
	
#DWTest: DataWriterTest.cpp DataWriter.cpp  Logger.cpp
#	$(CPP) -Wall DataWriter.cpp DataWriterTest.cpp Logger.cpp -o DWTest

PITest: PortInterfaceTest.cpp PortInterface.cpp Logger.cpp
	$(CPP) -Wall PortInterface.cpp PortInterfaceTest.cpp Logger.cpp GlobalLock.cpp -pthread -o PITest

#BITest: BusInterfaceTest.cpp BusInterface.cpp
#	$(CPP) -Wall BusInterface.cpp BusInterfaceTest.cpp GlobalLock.cpp PortInterface.cpp -pthread -o BITest
		
clean:
	-rm -f $(OBJS) $(LIBS) $(BIN) $(TMP) 

