#include "SemaphoreWrapper.h"

int initSemaphores(const char *path, int number_of_sem)
{
  key_t key;
  int semid;

  if ((key = ftok(path,'E')) ==-1)
    {
      return -1;
    }

  if ((semid =semget(key, number_of_sem, 0666 | IPC_CREAT)) == -1)
    {
      return -1;
    }

  return semid;
}

int deleteSemaphores(int semid)
{
  union semun arg;

  if (semctl(semid, 0, IPC_RMID, arg) == -1)
    {
      return -1;
    }
  
  return 0;
}

// Returns the semaphore ID for the path specified                             
int getSemaphoreID(const char *path, int number_of_sem)
{
  key_t key;
  int semid;

  if ((key = ftok(path,'E')) == -1)
    {
      return -1;
    }

  if ((semid = semget(key, number_of_sem, 0666)) == -1)
    {
      return -1;
    }

  return semid;
  
}

// Sets semaphore_number assoc. with the semid to value                        
int setSemaphore(int semid, int semaphore_number, int value)
{
  union semun arg;

  arg.val = value;

  return semctl(semid, semaphore_number, SETVAL, arg);
}

// Gets the semaphore value from semaphore_number assoc. with the semid        
int getSemaphore(int semid, int semaphore_number)
{
  union semun arg;

  return semctl(semid, semaphore_number, GETVAL, arg);
}

//////////////////////////////////////////////////////////////////////////
// Set of semaphores set up for unsigned long int values
int initSemaphoresUL(const char *path, int number_of_sem)
{
  key_t key;
  int semid;

  if ((key = ftok(path,'E')) ==-1)
    {
      return -1;
    }

  if ((semid =semget(key, number_of_sem, 0666 | IPC_CREAT)) == -1)
    {
      return -1;
    }

  return semid;
}

int deleteSemaphoresUL(int semid)
{
  union semunUL arg;

  if (semctl(semid, 0, IPC_RMID, arg) == -1)
    {
      return -1;
    }
  
  return 0;
}

// Returns the semaphore ID for the path specified                             
int getSemaphoreIDUL(const char *path, int number_of_sem)
{
  key_t key;
  int semid;

  if ((key = ftok(path,'E')) == -1)
    {
      return -1;
    }

  if ((semid = semget(key, number_of_sem, 0666)) == -1)
    {
      return -1;
    }

  return semid;
  
}

// Sets semaphore_number assoc. with the semid to value                        
int setSemaphoreUL(int semid, int semaphore_number, unsigned long int value)
{
  union semunUL arg;

  arg.val = value;

  return semctl(semid, semaphore_number, SETVAL, arg);
}

// Gets the semaphore value from semaphore_number assoc. with the semid        
unsigned long int getSemaphoreUL(int semid, int semaphore_number)
{
  union semunUL arg;

  return semctl(semid, semaphore_number, GETVAL, arg);
}

//////////////////////////////////////////////////////////////////////////
// Set of semaphores set up for double values
int initSemaphoresD(const char *path, int number_of_sem)
{
  key_t key;
  int semid;

  if ((key = ftok(path,'E')) ==-1)
    {
      return -1;
    }

  if ((semid =semget(key, number_of_sem, 0666 | IPC_CREAT)) == -1)
    {
      return -1;
    }

  return semid;
}

int deleteSemaphoresD(int semid)
{
  union semunD arg;

  if (semctl(semid, 0, IPC_RMID, arg) == -1)
    {
      return -1;
    }
  
  return 0;
}

// Returns the semaphore ID for the path specified                             
int getSemaphoreIDD(const char *path, int number_of_sem)
{
  key_t key;
  int semid;

  if ((key = ftok(path,'E')) == -1)
    {
      return -1;
    }

  if ((semid = semget(key, number_of_sem, 0666)) == -1)
    {
      return -1;
    }

  return semid;
  
}

// Sets semaphore_number assoc. with the semid to value                        
int setSemaphoreD(int semid, int semaphore_number, double value)
{
  union semunD arg;

  arg.val = value;

  return semctl(semid, semaphore_number, SETVAL, arg);
}

// Gets the semaphore value from semaphore_number assoc. with the semid        
double getSemaphoreD(int semid, int semaphore_number)
{
  union semunD arg;

  return semctl(semid, semaphore_number, GETVAL, arg);
}
