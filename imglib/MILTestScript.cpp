/******************************************************************************/
/*
 * File name: MILTestScript.cpp 
 * Written by: Kevin Dinkel
 */
#include <mil.h>
// same as using a "-I compile option with the 'includes' directory & #include "../mil/include/mil.h" in the header"
#include <iostream>

using namespace std;

struct ErrorStruct
{
	int TaskNum;
	int ERROR;
};

MIL_INT MFTYPE ReportError(MIL_INT HookType, MIL_ID EventId, void MPTYPE *UserStructPtr)
{
	ErrorStruct* local = (ErrorStruct*) UserStructPtr;
	MIL_TEXT_CHAR errorStr[M_ERROR_MESSAGE_SIZE];
	MIL_INT numErroStr = 0;
	local->ERROR = 1;
	
	cout << "Error. Hooktype: " << HookType << " EventID " << EventId << " num: " << local->TaskNum << endl;
	
	MappGetHookInfo(EventId,M_CURRENT_SUB_NB,&numErroStr);
	cout <<" number of errors: " << numErroStr << endl;
	
	if(!MappGetHookInfo(EventId,M_CURRENT + M_MESSAGE,errorStr))
	{
	cout << "         Message: " << errorStr << endl;
	}
	else
		cout << "SHIT" << endl;
	if(!MappGetHookInfo(EventId,M_CURRENT_SUB_1 + M_MESSAGE,errorStr))
	{
	cout << "         Message: " << errorStr << endl;
	}
	else
		cout << "SHIT" << endl;
	if(!MappGetHookInfo(EventId,M_CURRENT_SUB_2 + M_MESSAGE,errorStr))
	{
	cout << "         Message: " << errorStr << endl;
	}
	else
		cout << "SHIT" << endl;
	if(!MappGetHookInfo(EventId,M_CURRENT_SUB_3 + M_MESSAGE,errorStr))
	{
	cout << "         Message: " << errorStr << endl;
	}
	else
		cout << "SHIT" << endl;
		
	return 0;
}

int main(void) //MosMain before?
{
	// CLASS SHOULD HAVE A HANDLE ERROR FUNCTION FOR ANY ERRORS!! REMEMBER
	// CHILD BUFFER FOR CENTROIDS?????!!!!!?!!
	
	
   ///////////////////////// Definitions //////////////////////////////
   
   // Declare MIL Application IDs:
   MIL_ID MilApplication,  /* Application identifier.                */
          MilSystem,       /*   --> System identifier.               */
          MilImage,        /*         --> Image buffer identifier.   */
          MilDisplay,      /*         --> Display identifier.        */
   		  MilDigitizer;    /*         --> Digitizer identifier.      */
   		  
   MIL_INT InitFlag;       /* For Function Options                   */
   MIL_ID TestID;          /* For Learning                           */
   MIL_TEXT_CHAR errorStr[M_ERROR_MESSAGE_SIZE]; /* For Catching Errors                    */
   
   // For system allocation:
   MIL_CONST_TEXT_PTR SystemDescriptor; /* Specifies the type of system to allocate */
   MIL_INT SystemNum;
          
   // For buffer allocation:
   MIL_INT SizeX = 512; // x-pixels
   MIL_INT SizeY = 512; // y-pixels
   MIL_INT Type = 16 + M_UNSIGNED; // bitres (1,8,16,32) + type (M_FLOAT,M_SIGNED,M_UNSIGNED)
   MIL_INT64 Attribute = M_IMAGE + M_DISP + M_PROC + M_GRAB;// + M_LINUX_MXIMAGE;
   
   // Display MIL_ID Addresses:
   cout << "MilApplication: " << &MilApplication << endl;
   cout << "MilSystem     : " << &MilSystem << endl;
   cout << "MilImage      : " << &MilImage << endl;
   cout << "MilDisplay    : " << &MilDisplay << endl;
   cout << endl;

   ////////////////////////////////////////////////////////////////////
      
   ///////////////////////// Allocations //////////////////////////////
    
   // Allocate MIL Application, must be allocated prior to using any other MIL functions:
   cout << "Allocating MilApplication... " << endl;
   InitFlag = M_DEFAULT; // Default initialization, reported error messages are displayed
   // InitFlag = M_QUIET; // Suppress error messages during allocation
   if( ( TestID = MappAlloc(InitFlag, &MilApplication) ) == M_NULL )
   {
   		cout << "Failure" << endl;
   }
   else
   {
   		cout << "Success: Returned with address: " << &TestID << endl;
   }
   // Check for Errors:
   cout << "Checking for errors... " << endl;
   // InitFlag = M_GLOBAL; // Returns first error that has occured since last call to MappGetError
   InitFlag = M_CURRENT + M_MESSAGE; // Returns the error code returned by the last function call, and returns text message to errorstr
   TestID = MappGetError(InitFlag, &errorStr);
	printf("Error Code: 0x%x\n",(unsigned int)TestID);
	cout << "Message: " << errorStr << endl;

	// Setup error handler using "HookFunction":
	ErrorStruct ES;
	ES.TaskNum = 5;
	ES.ERROR = 0;
	// Gets any current or fatal errors and limits errors to the thread that calls
	MappHookFunction(M_ERROR_CURRENT + M_THREAD_CURRENT, ReportError, (void*)&ES);
   
   // Disable Error messages: (we will check for them)
   MappControl(M_ERROR,M_PRINT_DISABLE); // enable: M_PRINT_ENABLE (default)
   // look into M_PROCESSING eventually...
   
   // Allocate MIL System
   cout << "Allocating MilSystem... " << endl;
   SystemDescriptor = M_SYSTEM_SOLIOS; // Helios system for solios board
   // SystemDescriptor = M_SYSTEM_SOLIOS_GIGE; // Helios system for solios Gig-E board
   // SystemDescriptor = M_SYSTEM_HOST; // Host type system using cpu/memory (no image acquisition capabilities)
   
   SystemNum = M_DEFAULT; // Specifies the default board of type "SystemDescriptor" (we only have a single board so no worries with the default)
   InitFlag = M_DEFAULT; // Performs same as "M_COMPLETE" - initializes system to default state
   if( ( TestID = MsysAlloc(SystemDescriptor, SystemNum, InitFlag, &MilSystem) ) == M_NULL )
   {
   		cout << "Failure" << endl;
   }
   else
   {
   		cout << "Success: Returned with address: " << &TestID << endl;
   }
   // Check for Errors:
   cout << "Checking for errors... " << endl;
   // InitFlag = M_GLOBAL; // Returns first error that has occured since last call to MappGetError
   InitFlag = M_CURRENT; // Returns the error code returned by the last function call
   InitFlag = M_CURRENT + M_MESSAGE; // Returns the error code returned by the last function call, and returns text message to errorstr
   TestID = MappGetError(InitFlag, &errorStr);
	printf("Error Code: 0x%x\n",(unsigned int)TestID);
	cout << "Message: " << errorStr << endl;
   
   // Allocate MIL Display:
   cout << "Allocating MilDisplay.. " << endl;
   SystemDescriptor = M_SYSTEM_SOLIOS; // Helios system for solios board
   // SystemDescriptor = M_SYSTEM_SOLIOS_GIGE; // Helios system for solios Gig-E board
   // SystemDescriptor = M_SYSTEM_HOST; // Host type system using cpu/memory (no image acquisition capabilities)
   
   SystemNum = M_DEFAULT; // Specifies where to display image - defailt alows MIL to find the best device
   InitFlag = M_DEFAULT; // Performs same as "M_COMPLETE" - initializes system to default state
   if( ( TestID = MdispAlloc(MilSystem, SystemNum, MIL_TEXT("M_DEFAULT"), M_WINDOWED, &MilDisplay) ) == M_NULL )
   {
   		cout << "Failure" << endl;
   }
   else
   {
   		cout << "Success: Returned with address: " << &TestID << endl;
   }
   // Check for Errors:
   cout << "Checking for errors... " << endl;
   // InitFlag = M_GLOBAL; // Returns first error that has occured since last call to MappGetError
   InitFlag = M_CURRENT + M_MESSAGE; // Returns the error code returned by the last function call, and returns text message to errorstr
   TestID = MappGetError(InitFlag, &errorStr);
	printf("Error Code: 0x%x\n",(unsigned int)TestID);
	cout << "Message: " << errorStr << endl;
   
   // Setting display to handle 16bit images!!
   // Display can only display black and white values between 0 and 255
   // To compensate use an auto_scale function. Min of image becomes 0, Max of image becomes 255
   //MdispControl(MilDisplay,M_VIEW_MODE,M_AUTO_SCALE); 
   // Or use bit shift to map 16 bit resolution to a corresponding 8-bit value:
   MdispControl(MilDisplay,M_VIEW_BIT_SHIFT,16-8); // shift 16 to 8
   MdispControl(MilDisplay,M_VIEW_MODE,M_BIT_SHIFT); // shift 16 to 8
   
   // Allocate MIL Image:
   cout << "Allocating MilImage.. " << endl;
   SystemDescriptor = M_SYSTEM_SOLIOS; // Helios system for solios board
   // SystemDescriptor = M_SYSTEM_SOLIOS_GIGE; // Helios system for solios Gig-E board
   // SystemDescriptor = M_SYSTEM_HOST; // Host type system using cpu/memory (no image acquisition capabilities)
   
   SystemNum = M_DEFAULT; // Specifies where to display image - defailt alows MIL to find the best device
   InitFlag = M_DEFAULT; // Performs same as "M_COMPLETE" - initializes system to default state
   if( ( TestID = MbufAlloc2d(MilSystem, SizeX, SizeY, Type, Attribute, &MilImage) ) == M_NULL )
   {
   		cout << "Failure" << endl;
   }
   else
   {
   		cout << "Success: Returned with address: " << &TestID << endl;
   }
   // Check for Errors:
   cout << "Checking for errors... " << endl;
   // InitFlag = M_GLOBAL; // Returns first error that has occured since last call to MappGetError
   InitFlag = M_CURRENT + M_MESSAGE; // Returns the error code returned by the last function call, and returns text message to errorstr
   TestID = MappGetError(InitFlag, &errorStr);
	printf("Error Code: 0x%x\n",(unsigned int)TestID);
	cout << "Message: " << errorStr << endl;
   
   // Allocate MIL Digitizer:
   cout << "Allocating MilDigitizer.. " << endl;
   
   SystemNum = M_DEFAULT; // Specifies default device number set up during MIL installation using MilConfig.
   InitFlag = M_DEFAULT; // Should always be default.
   if( ( TestID = MdigAlloc(MilSystem, SystemNum, MIL_TEXT("/home/conf/sCMOSTopSingleBase.dcf")/*MIL_TEXT("M_DEFAULT")*/, InitFlag, &MilDigitizer) ) == M_NULL )
   {
   		cout << "Failure" << endl;
   }
   else
   {
   		cout << "Success: Returned with address: " << &TestID << endl;
   }
   // Check for Errors:
   cout << "Checking for errors... " << endl;
   // InitFlag = M_GLOBAL; // Returns first error that has occured since last call to MappGetError
   InitFlag = M_CURRENT + M_MESSAGE; // Returns the error code returned by the last function call, and returns text message to errorstr
   TestID = MappGetError(InitFlag, &errorStr);
	printf("Error Code: 0x%x\n",(unsigned int)TestID);
	cout << "Message: " << errorStr << endl;
   
   // Digitizer settings!
   MdigControl(MilDigitizer,M_BRIGHTNESS,M_DEFAULT); // or value
   MdigControl(MilDigitizer,M_CAMERA_LOCK,M_ENABLE); // causes mDigGrab to wait until digitizer is locked with the camera before sarting the grab
   // also lock and unlock sensativities
   MdigControl(MilDigitizer,M_CAPTURE_QUALITY,M_DEFAULT); // or value
   MdigControl(MilDigitizer,M_CAPTURE_SIZE,M_DEFAULT);
   MdigControl(MilDigitizer,M_CORRUPTED_FRAME_ERROR,M_ENABLE);
   MdigControl(MilDigitizer,M_CAMERA_LOCK,M_ENABLE);
   MdigControl(MilDigitizer,M_GRAB_DIRECTION_X,M_DEFAULT); // can flip images in y or x direction!!
   MdigControl(MilDigitizer,M_GRAB_DIRECTION_Y,M_DEFAULT); // can flip images in y or x direction!!
   MdigControl(MilDigitizer,M_GRAB_FAIL_CHECK,M_DEFAULT);
   MdigControl(MilDigitizer,M_GRAB_FAIL_RETRY_NUMBER,M_DEFAULT); // default = 1, or value (number of times to retry after bad grab)
   MdigControl(MilDigitizer,M_GRAB_MODE,M_DEFAULT); // default = M_SYNCHRONOUS, grab function returns after image has been captured
   MdigControl(MilDigitizer,M_GRAB_TIMEOUT,100); // default is infinite... value > 0 is wait time in msec
   MdigControl(MilDigitizer,M_INPUT_FILTER,M_DEFAULT); // lots of filter options!!
   MdigControl(MilDigitizer,M_LAST_GRAB_IN_TRUE_BUFFER, M_DEFAULT); // look at this later... seems useful
   MdigControl(MilDigitizer,M_SATURATION, M_DEFAULT);
   MdigControl(MilDigitizer,M_SHARPNESS, M_DEFAULT);
   // stuff for white balance coefficients??
   MdigControl(MilDigitizer,M_GRAB_INPUT_GAIN, M_DEFAULT); // or value 0 255 or voltage gain
   // axuillery signals all in here as well!!
   MdigControl(MilDigitizer,M_USER_BIT_FORMAT, M_DEFAULT); // same as one specified by DCF (also TTL, M_LVDS)
   MdigControl(MilDigitizer,M_USER_IN_FORMAT, M_DEFAULT); // "same as above"
   MdigControl(MilDigitizer,M_USER_OUT_FORMAT, M_DEFAULT); // "same as above"
   MdigControl(MilDigitizer,M_GRAB_TRIGGER_FORMAT, M_DEFAULT); // "same as above"
   MdigControl(MilDigitizer,M_GRAB_TRIGGER_MODE, M_DEFAULT); // "Rising edge, falling edge etc"
   MdigControl(MilDigitizer,M_AUTO_EXPOSURE, M_DEFAULT);
   
   ////////////////////////////////////////////////////////////////////
   
   ///////////////////////// Manipulation //////////////////////////////
   
   // Set buffer to all maxes:
   cout << endl << "Setting image values to max..." << endl;
   MbufClear(MilImage, 65535);
   cout << "Displaying image..." << endl;
   MdispSelect(MilDisplay, MilImage); // display image
   sleep(2);
   MdispSelect(MilDisplay, M_NULL); // stop displaying image
   
   // Clear buffer to all zeros:
   cout << endl << "Setting image values to zero..." << endl;
   MbufClear(MilImage, 0);
   TestID = MappGetError(InitFlag, &errorStr);
	printf("Error Code: 0x%x\n",(unsigned int)TestID);
	cout << "Message: " << errorStr << endl;
   cout << "Displaying image..." << endl;
   MdispSelect(MilDisplay, MilImage); // display image
   sleep(2);
   MdispSelect(MilDisplay, M_NULL); // stop displaying image
   
   // Build array of shorts to fill image buffer:
   // Cannot use new!! -> this creates an array of pointers that wont let copy work correctly!!
   //unsigned short** myArray = new unsigned short*[SizeX];
   //for(int i = 0; i < SizeX; i++)
   //		myArray[i] = new unsigned short[SizeY];
   
   int inc = (65535)/(SizeX+SizeY);
   unsigned short myArray[16][16];
   for(int k = 0; k < SizeX; k+=16)
   {
   		for(int l = 0; l < SizeY; l+=16)
   		{
		   for(int i = 0; i < 16; i++)
		   		for(int j = 0; j < 16; j++)
   					myArray[i][j] = (k + l)*inc;
   			MbufPut2d(MilImage,k,l,16,16,myArray);
   		}
   	}		
   // Clear buffer to all zeros:
   cout << endl << "Filling buffer with user gradient: "<< SizeX << " x " << SizeY << endl;
   
   cout << "Displaying image..." << endl;
   MdispSelect(MilDisplay, MilImage); // display image
   sleep(2);
   MdispSelect(MilDisplay, M_NULL); // stop displaying image
   
   // Grab an image... or attempt to:
   cout << endl << "Grabbing image with MdigGrab()." << endl;
   MdigGrab(MilDigitizer, MilImage);
  TestID = MappGetError(M_CURRENT + M_MESSAGE, &errorStr);
  	printf("Error Code: 0x%x\n",(unsigned int)TestID);
	cout << "Message: " << errorStr << endl;
     TestID = MappGetError(M_CURRENT_SUB_1 + M_MESSAGE, &errorStr);
  	printf("Error Code: 0x%x\n",(unsigned int)TestID);
	cout << "Message: " << errorStr << endl;
	TestID = MappGetError(M_CURRENT_SUB_2 + M_MESSAGE, &errorStr);
  	printf("Error Code: 0x%x\n",(unsigned int)TestID);
	cout << "Message: " << errorStr << endl;
	TestID = MappGetError(M_CURRENT_SUB_3 + M_MESSAGE, &errorStr);
  	printf("Error Code: 0x%x\n",(unsigned int)TestID);
	cout << "Message: " << errorStr << endl;
   MdispSelect(MilDisplay, MilImage); // display image
   sleep(2);
   MdispSelect(MilDisplay, M_NULL); // stop displaying image
   
   cout << endl << "Grabbing image with MdigGrabContinuous()." << endl;
  MdigGrabContinuous(MilDigitizer, MilImage);
  TestID = MappGetError(M_CURRENT + M_MESSAGE, &errorStr);
  	printf("Error Code: 0x%x\n",(unsigned int)TestID);
	cout << "Message: " << errorStr << endl;
     TestID = MappGetError(M_CURRENT_SUB_1 + M_MESSAGE, &errorStr);
  	printf("Error Code: 0x%x\n",(unsigned int)TestID);
	cout << "Message: " << errorStr << endl;
	TestID = MappGetError(M_CURRENT_SUB_2 + M_MESSAGE, &errorStr);
  	printf("Error Code: 0x%x\n",(unsigned int)TestID);
	cout << "Message: " << errorStr << endl;
	TestID = MappGetError(M_CURRENT_SUB_3 + M_MESSAGE, &errorStr);
  	printf("Error Code: 0x%x\n",(unsigned int)TestID);
	cout << "Message: " << errorStr << endl;
   MdispSelect(MilDisplay, MilImage); // display image
   sleep(2);
   MdispSelect(MilDisplay, M_NULL); // stop displaying image
   
   
   // Safe buffer to file:
   //MbufExport
   
   /////////////////////////////////////////////////////////////////////
   
   ///////////////////////// Deallocations ////////////////////////////
   
   // Free Image:
   cout << endl << "Deallocating MILImage." << endl;
   MbufFree(MilImage);
   
   // Free Display:
   cout << "Deallocating MILDisplay." << endl;
   MdispFree(MilDisplay);
   
   // Free System:
   cout << "Deallocating MILSystem." << endl;
   MsysFree(MilSystem);
   
   // Free Application:
   // This MUST be called in the same thread in which it was allocated.
   // This MUST be the ABSOLUTE LAST Mil Call in the program's execution.
   cout << "Deallocating MILApplication." << endl;
   MappFree(MilApplication);
   
   // Free defaults.
   //MappFreeDefault(MilApplication, MilSystem, MilDisplay, M_NULL, MilImage);
   
   ////////////////////////////////////////////////////////////////////
   return 0;
}

