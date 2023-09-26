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

#include "spike_interface/spike_utils.h"

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
ssize_t sys_user_print_backtrace(uint64 times, uint64 fp_tmp) {

   uint64* fp=(uint64*)(fp_tmp);
   //(uint64)fp>(((uint64)fp)&~((1L << 12) - 1))&&
   while(times > 0)
   {
     sprint("the fp = %x\n",fp);
     sprint("the address of ra = %x\n",(uint64*)(*fp));
     sprint("the ra = %x\n",*((uint64*)(*fp)));//print return address
     fp=(uint64*)(*((uint64*)(*fp)-1));//refresh value of frame pointer
     sprint("the new fp = %x\n",fp);
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
      return sys_user_print_backtrace(a1,a2);
    default:
      panic("Unknown syscall %ld \n", a0);
  }
}


