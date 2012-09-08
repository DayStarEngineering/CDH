TARGET	= distributedmilsyncasync
TARGET_OBJECTS  = DistributedMilSyncAsyncMaster.o DistributedMilSyncAsyncMain.o
TARGET_INCLUDES =

CFLAGS   = -I$(MILDIR)/include -g
CXXFLAGS = $(CFLAGS)
LDFLAGS  = -L$(MILDIR)/lib -lmil -lmilim

.PHONY   = clean


%.o: %.cpp $(TARGET_INCLUDES)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(TARGET): $(TARGET_OBJECTS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

all: $(TARGET)

clean:
	-rm -f $(TARGET) $(TARGET_OBJECTS)

