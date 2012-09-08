#ifndef GLOBAL_LOCK_H     // Prevent duplicate definition
#define GLOBAL_LOCK_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

// Command Lock Paths:
#define ALL_CMD_LOCK_PATH "/tmp/all_cmd_lock.mut"
#define STPRO_CMD_LOCK_PATH "/tmp/stpro_cmd_lock.mut"
#define STIMG_CMD_LOCK_PATH "/tmp/stimg_cmd_lock.mut"
#define STCH_CMD_LOCK_PATH "/tmp/stch_cmd_lock.mut"
#define HSKPR_CMD_LOCK_PATH "/tmp/hskpr_cmd_lock.mut"
#define PDOG_CMD_LOCK_PATH "/tmp/pdog_cmd_lock.mut"
#define DCOL_CMD_LOCK_PATH "/tmp/dcol_cmd_lock.mut"
#define EPS_CMD_LOCK_PATH "/tmp/eps_cmd_lock.mut"

using namespace std;

pthread_mutex_t* globallock_open(const char* lock_path);

#endif

