// DayStar Library Includes:
#include "../cdhlib/Logger.h"
#include "../cdhlib/SemaphoreWrapper.h"
#include "../cdhlib/DataWriter.h"
#include "../cdhlib/PortInterface.h"
#include "../cdhlib/Command.h"
#include "../configmap/configmap.h"

// Defines:
#define DEBUG_MODE 0
// 0 for flight configuration
// 1 for timing test
// 2 for shared memory test
// 3 for Centroid debug statements
