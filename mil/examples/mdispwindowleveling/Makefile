TARGET	= mdispwindowleveling

CFLAGS   = -I$(MILDIR)/include -g
CXXFLAGS = $(CFLAGS)
LDFLAGS  = -L$(MILDIR)/lib -lmil -lmilim -lm 
.PHONY   = clean

all: $(TARGET)

clean:
	-rm -f $(TARGET) $(TARGET).o

$(TARGET) : $(TARGET).o
