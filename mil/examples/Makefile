SUBDIRS := $(sort $(dir $(shell find . -name 'Makefile' | egrep -v '(distributedmil)|(odysseydtk)|(board-specific)|(^\./Makefile)')))

.PHONY: all $(SUBDIRS) clean
all: $(SUBDIRS)

clean:
	for i in $(SUBDIRS); do $(MAKE) -C $$i clean; done

$(SUBDIRS):
	$(MAKE) -C $@
