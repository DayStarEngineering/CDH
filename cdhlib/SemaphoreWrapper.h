#ifndef SEMAPHORE_WRAPPER_H
#define SEMAPHORE_WRAPPER_H

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

// Sem locations:
#define STPRO_PATH "/tmp/stpro.sem"
#define STIMG_PATH "/tmp/stimg.sem"
#define STCH_PATH "/tmp/stch.sem"
#define HSKPR_PATH "/tmp/hskpr.sem"
#define PDOG_PATH "/tmp/pdog.sem"
#define DCOL_PATH "/tmp/dcol.sem"
#define CMD_PATH "/tmp/cmd.sem"
#define SCHED_PATH "/tmp/sched.sem"
#define KICK_PATH "/tmp/kick.sem"

// Number of sems:
#define NUM_STPRO       2
#define NUM_STIMG       6
#define NUM_STCH        2
#define NUM_HSKPR       2
#define NUM_PDOG        2
#define NUM_DCOL        2
#define NUM_SCHED       3
#define NUM_KICK        8

// Kick Defines (For PDOG)
#define STPRO_KICK_SEM 0
#define STCL_KICK_SEM  1
#define STCH_KICK_SEM  2
#define HSKPR_KICK_SEM 3
#define DCOL_KICK_SEM  4
#define STIMG_KICK_SEM 5
#define SSM_KICK_SEM   6
#define SCHED_KICK_SEM 7

union semun
{
  int val;               /* value for SETVAL */
  struct semid_ds *buf;  /* buffer for IPC_STAT, IPC_SET */
  ushort  *array;        /* array for GETALL, SETALL */
                         /* Linux specific part: */
  struct seminfo *__buf; /* buffer for IPC_INFO */ 
};

union semunUL
{
  unsigned long int val;
  struct semid_ds *buf;
  ushort  *array;
  struct seminfo *__buf;
};

union semunD
{
  double val;
  struct semid_ds *buf;
  ushort  *array;
  struct seminfo *__buf;
};

// Create num_of_sem semaphores assoc. with the path.
// Returns the semid
int initSemaphores(const char *path, int num_of_sem);

// Delete the semaphores associated with semid
int deleteSemaphores(int semid);

// Returns the semaphore ID for the path specified
int getSemaphoreID(const char *path, int number_of_sem);

// Sets semaphore_number assoc. with the semid to value
int setSemaphore(int semid, int semaphore_number, int value);

// Gets the semaphore value from semaphore_number assoc. with the semid
int getSemaphore(int semid, int semaphore_number);



// Returns the semid
int initSemaphoresUL(const char *path, int num_of_sem);

// Delete the semaphores associated with semid
int deleteSemaphoresUL(int semid);

// Returns the semaphore ID for the path specified
int getSemaphoreIDUL(const char *path, int number_of_sem);

// Sets semaphore_number assoc. with the semid to value
int setSemaphoreUL(int semid, int semaphore_number, unsigned long int value);

// Gets the semaphore value from semaphore_number assoc. with the semid
unsigned long int getSemaphoreUL(int semid, int semaphore_number);


// Returns the semid
int initSemaphoresD(const char *path, int num_of_sem);

// Delete the semaphores associated with semid
int deleteSemaphoresD(int semid);

// Returns the semaphore ID for the path specified
int getSemaphoreIDD(const char *path, int number_of_sem);

// Sets semaphore_number assoc. with the semid to value
int setSemaphoreD(int semid, int semaphore_number, double value);

// Gets the semaphore value from semaphore_number assoc. with the semid
double getSemaphoreD(int semid, int semaphore_number);

#endif
