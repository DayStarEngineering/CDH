include ../vars.mk

OBJS=Centroid.o StartrackerData.o
LIBS=libcentroid.so libstdata.so
BIN=CentroidTest StartrackerDataTest

all: $(OBJS) $(LIBS) $(BIN)

Centroid.o: Centroid.cpp
	$(CPP) $(LIBFLAGS) Centroid.cpp -o Centroid.o
	
libcentroid.so: Centroid.o
	$(CPP) $(LDFLAGS) -shared Centroid.o -o libcentroid.so
	
CentroidTest: CentroidTest.cpp
	$(CPP) -Wall StartrackerData.cpp Centroid.cpp CentroidTest.cpp -pthread -o CentroidTest

StartrackerData.o: StartrackerData.cpp
	$(CPP) $(LIBFLAGS) StartrackerData.cpp -o StartrackerData.o
	
libstdata.so: StartrackerData.o
	$(CPP) $(LDFLAGS) -shared StartrackerData.o -o libstdata.so
	
StartrackerDataTest: StartrackerDataTest.cpp
	$(CPP) -Wall StartrackerData.cpp StartrackerDataTest.cpp -pthread -o StartrackerDataTest
	
clean:
	-rm -f $(OBJS) $(LIBS) $(BIN) $(TMP) 
