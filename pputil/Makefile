
SRCS = DataParserCmdLine.cpp
OBJS = dpcl.o
BIN  = dpcl

all: $(OBJS) $(BIN)

dpcl.o: DataParserCmdLine.cpp
	g++ -O2 -pipe -c -Wall -Wextra DataParserCmdLine.cpp -o dpcl.o
	
dpcl: dpcl.o
	g++ -pipe -Wall -Wextra dpcl.o $ -o dpcl
	
clean:
	-rm -f $(OBJS) $(BIN) *~
