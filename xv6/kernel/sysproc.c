#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"
#include <pstat.h>

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return proc->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (proc->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

/* The following code is added by Asvataman Venkatesan, NetID: axv230014
** Implement the settickets system call, which allows the process to set its
** number of tickets. This is used to control the process's share of CPU time.
** The number of tickets must be >= 1. If invalid, the system call returns -1.
*/
int sys_settickets(void)
{
  int n;
  if (argint(0, &n) < 0) // Retrieve the argument passed to settickets
    return -1;

  return setproctickets(n);
}
/* End of code added */

/* The following code is added by Asvataman Venkatesan, NetID: axv230014
** This system call implementation fills the pstat structure with statistics about each process,
** such as whether it is in use, its PID, ticket count, and tick count.
*/
int sys_getpinfo(void)
{
  struct pstat *pstat;

  // get the pstat from user
  int check = argptr(0, (void *)&pstat, sizeof(*pstat));

  // Validate the pointer passed from user space.
  if (pstat == NULL || check < 0) //
    return -1;

  return getpstat(pstat);
}
/* End of code added */