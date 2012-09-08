#include "MILWrapper.h"
#include "MILObjects.h"
#include "../stlib/StartrackerData.h"
#include "../cdhlib/Timer.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "starting test" << endl;
	MILWrapper MILWrapper1;
	
	// Logger:
	/*
	Logger myLogger("test log");
	myLogger.setlim(5);
	myLogger.setmaxlen(50 KB,SINGLEFILE);
	myLogger.open("/home/log/test.log");
	myLogger.lw(SPAM,"Starting test...");
	*/
	cout << "Configure return: " << MILWrapper1.create() << endl;
	
	
	MIL_ID sysID = MILWrapper1.SysID;
	/*MILDigitizer dig;
	MILImage img;*/
	MILDisplay dsp;
	
	//cout << "Create dig: " << dig.create(sysID, "/home/conf/sCMOSTopSingleBase.dcf") << endl;
	//cout << "Create img: " << img.create(sysID, 2560, 2160) << endl;
	cout << "Create dsp: " << dsp.create(sysID) << endl;
	/*
	cout << "ID dig: " << dig.ID << endl;
	cout << "ID img: " << img.ID << endl;
	cout << "ID dsp: " << dsp.ID << endl;
	
	dispImg(dsp.ID,img.ID);
	sleep(1);
	clearDisp(dsp.ID);
	
	clearImg(img.ID,0x7FF/2);
	dispImg(dsp.ID,img.ID);
	sleep(1);
	
	saveImg(img.ID, "/data/img.bmp");
	clearDisp(dsp.ID);
	clearImg(img.ID, 0x7FF);
	saveImg(img.ID, "/data/img2.bmp");
	digGrab(dig.ID,img.ID);
	dispImg(dsp.ID,img.ID);
	sleep(1);
	loadImg(img.ID, "/data/img.bmp");
	dispImg(dsp.ID,img.ID);
	*/
	
	int size1 = 15;
	int size2 = 10;
	image img, img2;
	img.create(size1,size2);
	img2.create(size1,size2);
	int cnt = 0;
	
	for (unsigned int i = 0; i < img.xlen; i++)
	{
		for (unsigned int j = 0; j < img.ylen; j++)
		{
			img.pixel[i][j] = cnt/**(0x7FF/(size*size))*/; cnt++;
		}
	}
	
	//printImg(&img);
	
	MILImage milimg;
	milimg.create(sysID, size1, size2);
	
	cout << copyImg(&img, milimg.ID) << endl;
	
	//printImg(milimg.ID, size1, size2);
	
	//cout << copyImg(milimg.ID, &img) << endl;
	
	timerStruct timer;
	
	//printImg(&img2);
	
	gettimeofday(&timer.start,NULL);
	copyImg(milimg.ID, &img2);
	gettimeofday(&timer.stop,NULL);

	cout.precision(10);
			cout.setf(ios::fixed,ios::floatfield);   // floatfield set to fixed
		cout << "copy time: " << calcTime(&timer) << endl;
	
	//printImg(&img2);
	
	dispImg(dsp.ID,milimg.ID);
	
	sleep(100);
	
	return 0;
}
