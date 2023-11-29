/*
 * contains the implementation of all syscalls.
 */

#include <stdint.h>
#include <errno.h>

#include "util/types.h"
#include "syscall.h"
#include "string.h"
#include "process.h"
#include "util/functions.h"
#include "elf.h"
#include "spike_interface/spike_utils.h"

extern Symbols symbols[64];
extern int count;

//
// implement the SYS_user_print syscall
//
ssize_t sys_user_print(const char* buf, size_t n) {
  sprint(buf);
  return 0;
}

//
// implement the SYS_user_exit syscall
//
ssize_t sys_user_exit(uint64 code) {
  sprint("User exit with code:%d.\n", code);
  // in lab1, PKE considers only one app (one process). 
  // therefore, shutdown the system when the app calls exit()
  shutdown(code);
}

//
// implement the SYS_user_backtrace
//
ssize_t sys_user_print_backtrace(uint64 times) {

   uint64 * sp = (uint64 *)*((uint64 *)(current->trapframe->regs).t6 + 1);
   uint64 * s0 = sp + 3; //in do_user_call --> sd    s0, 24(sp)  
   // s0 point to the stack of print_backtrace 
   uint64 * fp = (uint64 *) (*s0);
   while(times > 0 && (uint64)fp < (((((uint64) s0 - 1)/512))+1)* 512)
   {
      uint64 ra = *(fp - 1);
      for(int j=0; j<count-1;j++){
      if (symbols[j+1].off<ra && ra<symbols[j].off)
        sprint("%s\n",symbols[j+1].name);
    }
      fp = (uint64 *) (*(fp - 2));
      times --;
   }
   return 0;
}
//
// [a0]: the syscall number; [a1] ... [a7]: arguments to the syscalls.
// returns the code of success, (e.g., 0 means success, fail for otherwise)
//
long do_syscall(long a0, long a1, long a2, long a3, long a4, long a5, long a6, long a7) {
  switch (a0) {
    case SYS_user_print:
      return sys_user_print((const char*)a1, a2);
    case SYS_user_exit:
      return sys_user_exit(a1);
    case SYS_user_print_backtrace:
      return sys_user_print_backtrace(a1);
    default:
      panic("Unknown syscall %ld \n", a0);
  }
}


