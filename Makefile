include vars.mk

all: 
	make -C cdhlib
	make -C configmap
	make -C stlib
	make -C imglib
	make -C pdog
	make -C stimg
	make -C stcl
	make -C dcol
	#make -C hskpr
	make -C util
	make -C ssm
	make -C sched
	# make -C stpro
	# make -C stch

cdhlib:
	make -C cdhlib

pdog:
	make -C pdog

configmap:
	make -C configmap
	
imglib:
	make -C imglib

stlib:
	make -C stlib
	
stpro:
	make -C stpro

stimg:
	make -C stimg
	
stcl:
	make -C stcl
	
stch:
	make -C stch
	
dcol:
	make -C dcol
	
hskpr:
	make -C hskpr

util:
	make -C util

ssm:
	make -C ssm
	
sched:
	make -C sched
	
install:
	# bins:
	cp ./pdog/pdog $(INSBIN)
	cp ./ssm/ssm $(INSBIN)
	cp ./stcl/stcl $(INSBIN)
	#cp ./stpro/stpro $(INSBIN)
	cp ./stimg/stimg $(INSBIN)
	#cp ./stch/stch $(INSBIN)
	cp ./dcol/dcol $(INSBIN)
	#scp ./hskpr/hskpr $(INSBIN)
	cp ./util/dpcl $(INSBIN)
	#cp ./util/asci2bin $(INSBIN)
	cp ./util/fgcl $(INSBIN)
	cp ./sched/sched $(INSBIN)
	# libs:
	cp ./cdhlib/*.so $(INSLIB)
	cp ./configmap/*.so $(INSLIB)
	cp ./imglib/*.so $(INSLIB)
	cp ./stlib/*.so $(INSLIB)
	# config:
	cp ./cdhconfig/* $(INSCNF)
	# scripts:
	chmod -R a+x $(INSSCR)/*
	chmod -R a+x $(INSETC)/*

clean:
	# make clean all directories:
	cd cdhlib && make clean
	cd pdog && make clean
	cd configmap && make clean
	cd imglib && make clean
	cd stlib && make clean
	cd stpro && make clean
	cd stimg && make clean
	cd stcl && make clean
	#cd stch && make clean
	cd ssm && make clean
	cd dcol && make clean
	#cd hskpr && make clean
	cd util && make clean
	cd sched && make clean
	# remove stuff from filesystem:
	rm -f $(INSBIN)/*
	rm -f $(INSLIB)/*
	rm -f $(INSCNF)/*
	rm -f $(TMP)
	rm -f ./cdhconfig/$(TMP) 
