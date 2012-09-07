ARCH := $(shell uname -m)
TARGET	= mdispoverlay
CFLAGS   = -I$(MILDIR)/include -I/usr/X11R6/inlcude -g
CXXFLAGS = $(CFLAGS)
LDFLAGS  = -L$(MILDIR)/lib -lmil -L/usr/X11R6/lib -lX11

ifeq ($(ARCH),x86_64)
LDFLAGS  = -L$(MILDIR)/lib -lmil -L/usr/X11R6/lib64 -lX11
endif

.PHONY   = clean

all: $(TARGET)

clean:
	-rm -f $(TARGET) $(TARGET).o

$(TARGET) : $(TARGET).o
