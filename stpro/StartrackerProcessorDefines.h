// DayStar Library Includes:
#include "../cdhlib/Logger.h"
#include "../cdhlib/SemaphoreWrapper.h"
#include "../cdhlib/DataWriter.h"
#include "../cdhlib/PortInterface.h"
#include "../cdhlib/Command.h"
#include "../cdhlib/Timer.h"
#include "../configmap/configmap.h"
#include "../imglib/MILWrapper.h"
#include "../imglib/MILObjects.h"
#include "../stlib/StartrackerData.h"
#include "../stlib/Centroid.h"

// Debug types:
#define FLIGHT 0
#define TIMETEST 1
#define MEMTEST 2
#define CNTRDTEST 3

// Debug mode:
#define DEBUG_MODE TIMETEST

// 0 for flight configuration
// 1 for timing test
// 2 for shared memory test
// 3 for Centroid debug statements
