#include "asm/x86.h"
#include "types.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//-------------------------------LAB 4--------------------------------------

/**
 * Sets the uid of the current process
 * @argument uid -- The uid to change to.  Valid ranges are 0x0-0xFFFF
 *
 * @returns 0 on success -1 on failure
 */
int
sys_setuid(void){
  int uid;

  if(argint(0, &uid) < 0)
    return -1;
  
  return setuid(uid);
}

/**
 * Gets the uid of the currently running process.
 *
 * @returns The current process's uid.
 */
int
sys_getuid(void){
  return getuid();
}

/**
 * Changes the owner of the file at filename to uid. Returns 0 if
 * successful, and -1 on failure (on failure no permissions are changed).
 *
 * @arg filename -- A filesystem path naming the file to change
 * @arg uid -- The new owner of the file, valid range is 0x0-0xFFFF
 * 
 * @returns 0 on success, -1 on failure
 */

int 
sys_chown(void){
  char *filename;
  int uid;

  if(argstr(0, &filename) < 0)
    return -1;

  if(argint(1, &uid) < 0)
    return -1;

  return chown((const char*)filename, uid);
}

/**
 * Changes the permissions of the file at filename to perm.  Returns 0 if
 * successful, and -1 on failure (on failure no permissions are changed).
 *
 * @arg filename -- A filesystem path naming the file to change
 * @arg perm -- The new permissions for the file.
 * 
 * @returns 0 on success, -1 on failure.
 */

int 
sys_chmod(void){
  char *filename;
  int perm;

  if(argstr(0, &filename) < 0)
    return -1;

  if(argint(1, &perm) < 0)
    return -1;
  
  return chmod((const char*)filename, perm);
}

/**
 * System call for testing purposes
 *
 * @arg filename -- A filesystem path naming the file to change
 * 
 * @returns The owner uid of the file
 */

int 
sys_getown(void){
  char *filename;

  if(argstr(0, &filename) < 0)
    return -1;
  
  return getown((const char*)filename);
}

/**
 * System call for testing purposes
 *
 * @arg filename -- A filesystem path naming the file to change
 * 
 * @returns The permissions of the file
 */

int 
sys_getmod(void){
  char *filename;

  if(argstr(0, &filename) < 0)
    return -1;
  
  return getmod((const char*)filename);
}
