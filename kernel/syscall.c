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
typedef struct elf_info_t {
  spike_file_t *f;
  process *p;
} elf_info;
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
ssize_t sys_user_print_backtrace(uint64 times,uint64 tf_tmp) {
  //*(((uint64 *)((tf->regs).t6) + 7))
   trapframe *tf = (trapframe *)tf_tmp;
   elf_info info;
   elf_ctx elfloader;
   info.f=spike_file_open("./obj/app_print_backtrace", O_RDONLY, 0);
   //sprint("go there\n");
   //memset(&elfloader,0,sizeof(elfloader));
   //elf_ctx *ctx=&elfloader;
   // = (elf_info *)ctx->info;
   // call spike file utility to load the content of elf file into memory.
   // spike_file_pread will read the elf file (msg->f) from offset to memory (indicated by
   // *dest) for nb bytes.
  //  if(spike_file_pread(msg->f, &ctx->ehdr, sizeof(ctx->ehdr), 0) != sizeof(ctx->ehdr)){
  //      sprint("read elf_header failed");
  //  }
   sprint("t6 point to + 6 s0 %lx\n",(uint64 *)(tf->regs).t6 + 7);
   sprint("t6 point to + 6 value of s0 %lx\n",*((uint64 *)(tf->regs).t6 + 7));
   uint64 * p=(uint64 *)*((uint64 *)(tf->regs).t6 + 1);
   sprint("%lx -> %lx\n",p,*(p+0));
   sprint("%lx -> %lx\n",p+1,*(p+1));
   sprint("%lx -> %lx\n",p+2,*(p+1));
   sprint("%lx -> %lx\n",p+3,*(p+3));
   sprint("%lx -> %lx\n",p+4,*(p+4));
   sprint("%lx -> %lx\n",p+5,*(p+5));
   sprint("%lx -> %lx\n",p+6,*(p+6));
   sprint("%lx -> %lx\n",p+7,*(p+7));
   sprint("%lx -> %lx\n",p+8,*(p+8));
   sprint("%lx -> %lx\n",p+9,*(p+9));
   sprint("%lx -> %lx\n",p+10,*(p+10));
   sprint("%lx -> %lx\n",p+11,*(p+11));
   sprint("%lx -> %lx\n",p+12,*(p+12));
   sprint("%lx -> %lx\n",p+13,*(p+13));
   sprint("%lx -> %lx\n",p+14,*(p+14));
   sprint("%lx -> %lx\n",p+15,*(p+15));
   sprint("%lx -> %lx\n",p+16,*(p+16));
   sprint("%lx -> %lx\n",p+17,*(p+17));
   sprint("%lx -> %lx\n",p+18,*(p+18));
   sprint("%lx -> %lx\n",p+19,*(p+19));
   sprint("%lx -> %lx\n",p+20,*(p+20));
   sprint("%lx -> %lx\n",p+21,*(p+21));
   sprint("%lx -> %lx\n",p+22,*(p+22));

  //  sprint("ra %lx\n",(tf->regs).ra);
  //  sprint("sp %lx\n",(tf->regs).sp);
  //  sprint("epc %lx\n",tf->epc);
  //  sprint("s0(fp) %lx\n",(tf->regs).s0);
  //  sprint("s0(fp) point %lx\n",*(uint64 *)((tf->regs).s0));
  //  sprint("t6 %lx\n",(tf->regs).t6);
  //  sprint("t6 point to + 1 sp %lx\n",(uint64 *)(tf->regs).t6 + 1);
  //  sprint("t6 point to + 1 value of sp %lx\n",*((uint64 *)(tf->regs).t6 + 1));
  //  uint64* fp=(uint64 *)(fp_tmp);// change to fp pointer
  //  sprint("fp = %lx\n",fp);
  //  uint64 pagetop = ((((fp_tmp - 1)/512))+1)* 512;
  //  sprint("%lx\n",pagetop);
  //  while(times > 0 && (uint64)fp < pagetop)
  //  {
  //    sprint("%d\n",times);
  //    sprint("fp point to the ra: %lx\n",fp);
  //    sprint("the ra = %lx\n",*fp);
  //    sprint("the content of ra = %lx\n", *(uint64 *)(*fp));
  //    fp=(uint64 *)(*(fp-1));//refresh value of frame pointer
  //    sprint("fp is refreshed\n");
  //    times --;
  //  }
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


