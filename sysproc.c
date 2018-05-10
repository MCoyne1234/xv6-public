#include "types.h"
#include "x86.h"
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
sys_exit()
{
  int status;
  argint(0, &status);
  exit(status);
  return -2;  // not reached
}

int
sys_wait(void)
{
  int *status;
  argptr(0,(char**) &status, sizeof(int*) );
  return wait(status);
}

int
sys_waitpid(void) // Lab01
{
  int pid; 
  int *status; 
  int options;

  argint(0, &pid);
  argptr(1,(char**) &status, sizeof(int*) );
  argint(2, &options);
  return waitpid(pid, status, options);
}
///*
int
sys_changePriority(void)
{
 int priority;
 int pid;

 argint(0,&pid);
 argint(1,&priority);
  
  return changePriority(pid, priority);   
}
//*/
/*
int
sys_changePriority(void) // LAB02
{
//cprintf("CHANGEPRIORTY: IN\n");
  int newPriority, oldPriority;
  oldPriority = myproc()->priority;
//cprintf("FROM: %d\n", oldPriority);
  if(argint(0, &newPriority) < 0)
    return -1;
//cprintf("TO: %d\n", newPriority);
  if( newPriority >= 0 && newPriority < 64){
    myproc()->priority = newPriority;  
  }else return -1;
  
  if( newPriority > oldPriority ){ 
//cprintf("YIELDING\n");
    yield();
    cprintf("RETURN FROM YIELD.\n");
  }
  //return changePriority( newPriority );
  return oldPriority;   
}
*/
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
int
sys_getPri(void)
{
  return myproc()->priority;
}
