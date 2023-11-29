#ifndef _ELF_H_
#define _ELF_H_

#include "util/types.h"
#include "process.h"

#define MAX_CMDLINE_ARGS 64

#define STT_FUNC  2    //st_info
#define STB_GLOBAL (1<<4)   //st_info

typedef struct symbol_tab{
	char name[16];
	uint64 off;
} Symbols;

// elf header structure
typedef struct elf_header_t {
  uint32 magic;
  uint8 elf[12];
  uint16 type;      /* Object file type */
  uint16 machine;   /* Architecture */
  uint32 version;   /* Object file version */
  uint64 entry;     /* Entry point virtual address */
  uint64 phoff;     /* Program header table file offset */
  uint64 shoff;     /* Section header table file offset */
  uint32 flags;     /* Processor-specific flags */
  uint16 ehsize;    /* ELF header size in bytes */
  uint16 phentsize; /* Program header table entry size */
  uint16 phnum;     /* Program header table entry count */
  uint16 shentsize; /* Section header table entry size */
  uint16 shnum;     /* Section header table entry count */
  uint16 shstrndx;  /* Section header string table index */
} elf_header;

typedef struct elf_sect_header_t {
  uint32 sh_name;		  /* Section name, index in string tbl */
  uint32 sh_type;		  /* Type of section */
  uint64 sh_flags;		/* Miscellaneous section attributes */
  uint64 sh_addr;		  /* Section virtual addr at execution */
  uint64 sh_offset;		/* Section file offset */
  uint64 sh_size;		  /* Size of section in bytes */
  uint32 sh_link;		  /* Index of another section */
  uint32 sh_info;		  /* Additional section information */
  uint64 sh_addralign;/* Section alignment */
  uint64 sh_entsize;	/* Entry size if section holds table */
} elf_sect_header;

// Program segment header.
typedef struct elf_prog_header_t {
  uint32 type;   /* Segment type */
  uint32 flags;  /* Segment flags */
  uint64 off;    /* Segment file offset */
  uint64 vaddr;  /* Segment virtual address */
  uint64 paddr;  /* Segment physical address */
  uint64 filesz; /* Segment size in file */
  uint64 memsz;  /* Segment size in memory */
  uint64 align;  /* Segment alignment */
} elf_prog_header;

// elf symbol table structure
typedef struct elf_sym_t {
  uint32   st_name;
  uint8    st_info;      /* the type of symbol */
  uint8    st_other;
  uint16   st_shndx;
  uint64   st_value;     // address maybe
  uint64   st_size;
} elf_sym;

#define ELF_MAGIC 0x464C457FU  // "\x7FELF" in little endian
#define ELF_PROG_LOAD 1

typedef enum elf_status_t {
  EL_OK = 0,

  EL_EIO,
  EL_ENOMEM,
  EL_NOTELF,
  EL_ERR,

} elf_status;

typedef struct elf_ctx_t {
  void *info;
  elf_header ehdr;
} elf_ctx;

elf_status elf_init(elf_ctx *ctx, void *info);
elf_status elf_load(elf_ctx *ctx);

void load_bincode_from_host_elf(process *p);

#endif
