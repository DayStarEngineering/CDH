include ../vars.mk

SRCS = SchedulerMain.cpp Scheduler.cpp
OBJS = SchedulerMain.o Scheduler.o
BIN = sched

all: $(BIN)
	make -C ../cdhlib
	make -C ../configmap

SchedulerMain.o: SchedulerMain.cpp
	$(CPP) $(CPPFLAGS) SchedulerMain.cpp -o SchedulerMain.o
   
Scheduler.o: Scheduler.cpp
	$(CPP) $(CPPFLAGS) Scheduler.cpp -o Scheduler.o

sched: Scheduler.o SchedulerMain.o
	$(CPP) -o $(BIN) $(OBJS) $(LDFLAGS) $(CDHLIB) $(CFGMAP) 

clean:
	-rm -f $(OBJS) $(BIN) $(TMP) 
