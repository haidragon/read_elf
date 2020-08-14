//
//  main.cpp
//  main
//
//  Created by haidragon on 2020/7/17.
//  Copyright © 2020 刘海龙. All rights reserved.
//
#include <dlfcn.h>
#include <inttypes.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "elf.h"
void *start_addr = NULL;
static void
print_file_type (unsigned short int e_type)
{
  if ((e_type <= ET_CORE))
    {
      static const char *const knowntypes[] =
      {
        ("NONE (None)"),
        ("REL (Relocatable file)"),
        ("EXEC (Executable file)"),
        ("DYN (Shared object file)"),
        ("CORE (Core file)")
      };
      puts ( (knowntypes[e_type]));
    }
  else if (e_type >= ET_LOOS && e_type <= ET_HIOS)
    printf ( ("OS Specific: (%x)\n"),  e_type);
  else if (e_type >= ET_LOPROC /* && e_type <= ET_HIPROC always true */)
    printf ( ("Processor Specific: (%x)\n"),  e_type);
  else
    puts ("???");
}
void print_file_header()
{
    do{
        if(start_addr==NULL){
            break;
        }
         Elf64_Ehdr *header=(Elf64_Ehdr *)start_addr;
         printf("%s \n",header->e_ident);
         print_file_type(header->e_type);
        
    }while(0);
    
}
const char *
pheader_segment_type_name (Elf64_Word p_type)
{
    char* res;
  switch(p_type)
  {
      case PT_NULL:
          res="Invalid";
          break;
      case PT_LOAD:
          res="LOAD";
          break;
      case PT_DYNAMIC:
          res="DYNAMIC";
          break;
      case PT_INTERP:
          res="INTERP";
          break;
      case PT_NOTE:
          res="NOTE";
          break;
      case PT_SHLIB:
          res="SHLIB";
          break;
      case PT_PHDR:
          res="PHDR";
          break;
      case PT_TLS:
          res="TLS";
          break;
      case PT_NUM:
          res="NUM";
          break;
      case PT_LOOS:
          res="LOOS";
          break;
      case PT_GNU_EH_FRAME:
          res="GNU_EH_FRAME  ";
          break;
      case PT_GNU_STACK:
          res="GNU_STACK  ";
          break;
      case PT_GNU_RELRO:
          res="GNU_RELRO  ";
          break;
//      case PT_L4_STACK:
//          res="L4_STACK  ";
//          break;
//      case PT_L4_KIP:
//          res="L4_KIP  ";
//          break;
//      case PT_L4_AUX:
//          res="L4_AUX  ";
//          break;
      default:
          res="Unknown  ";
          break;
  }

  return res;
}

void print_program_header()
{
    do{
       if(start_addr==NULL){
           break;
       }
        Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
        printf ( "There are %d program headers, starting at offset 0x%llx",Ehdr->e_phnum,Ehdr->e_phoff);
        printf ( ("Program Headers:\n"));
        if (Ehdr->e_ident[EI_CLASS] == ELFCLASS32)
          puts ( ("  Type           Offset   VirtAddr   PhysAddr   FileSiz  MemSiz   Flg Align"));
        else
          puts ( ("  Type           Offset   VirtAddr           PhysAddr           FileSiz  MemSiz   Flg Align"));
        Elf64_Phdr *program_header_index=NULL;
        for (int i=0;i<Ehdr->e_phnum; i++) {
            program_header_index=(Elf64_Phdr *)((char*)start_addr+sizeof(Elf64_Ehdr)+sizeof(Elf64_Phdr)*i);
            printf ("  %-14s 0x%06" PRIx64 " 0x%0*" PRIx64 " 0x%0*" PRIx64
            " 0x%06" PRIx64 " 0x%06" PRIx64 " %c%c%c 0x%" PRIx64 "\n",
            pheader_segment_type_name(program_header_index->p_type),
            program_header_index->p_offset,
            Ehdr->e_ident[EI_CLASS] == ELFCLASS32 ? 8 : 16, program_header_index->p_vaddr,
            Ehdr->e_ident[EI_CLASS] == ELFCLASS32 ? 8 : 16, program_header_index->p_paddr,
            program_header_index->p_filesz,
            program_header_index->p_memsz,
            program_header_index->p_flags & PF_R ? 'R' : ' ',
            program_header_index->p_flags & PF_W ? 'W' : ' ',
            program_header_index->p_flags & PF_X ? 'E' : ' ',
            program_header_index->p_align);
            
           
        }
        
        
    }while(0);
    
}
char* section_type_name (Elf64_Word sh_type){
    char* res = nullptr;
    switch(sh_type)
    {
        case SHT_NULL:
            res="NULL";
            break;
        case SHT_PROGBITS:
            res="PROGBITS";
            break;
        case SHT_SYMTAB:
            res="SYMTAB";
            break;
        case SHT_STRTAB:
            res="STRTAB";
            break;
        case SHT_RELA:
            res="RELA";
            break;
        case SHT_HASH:
            res="HASH";
            break;
        case SHT_DYNAMIC:
            res="DYNAMIC";
            break;
        case SHT_NOTE:
            res="NOTE";
            break;
        case SHT_NOBITS:
            res="NOBITS";
            break;
        case SHT_REL:
            res="REL";
            break;
        case SHT_SHLIB:
            res="SHLIB";
            break;
        case SHT_DYNSYM:
            res="DYNSYM";
            break;
        case SHT_LOPROC:
            res="LOPROC";
            break;
        case SHT_HIPROC:
            res="HIPROC";
            break;
        case SHT_LOUSER:
            res="LOUSER";
            break;
        case SHT_HIUSER:
            res="HIUSER";
            break;
        default:
            res="Unknown";
            break;
    }
    return res;
}
void print_section_header(){
    do{
          if(start_addr==NULL){
              break;
          }
           Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
           printf ("There are %d section headers, starting at offset 0x%llx\n",Ehdr->e_shnum,Ehdr->e_shoff);
           puts ( ("Section Headers:"));

           if (Ehdr->e_ident[EI_CLASS] == ELFCLASS32)
            puts ( ("[Nr] Name                 Type         Addr     Off    Size   ES Flags Lk Inf Al"));
           else
                puts ( ("[Nr] Name                 Type         Addr             Off      Size     ES Flags Lk Inf Al"));

           Elf64_Shdr *section_header_index=NULL;
           const char *sname;
        
//        typedef struct
//        {
//          Elf64_Word    sh_name;        /* Section name (string tbl index) */
//          Elf64_Word    sh_type;        /* Section type */
//          Elf64_Xword    sh_flags;        /* Section flags */
//          Elf64_Addr    sh_addr;        /* Section virtual addr at execution */
//          Elf64_Off    sh_offset;        /* Section file offset */
//          Elf64_Xword    sh_size;        /* Section size in bytes */
//          Elf64_Word    sh_link;        /* Link to another section */
//          Elf64_Word    sh_info;        /* Additional section information */
//          Elf64_Xword    sh_addralign;        /* Section alignment */
//          Elf64_Xword    sh_entsize;        /* Entry size if section holds table */
//        } Elf64_Shdr;
           //拿到节表字符串表头偏移
           Elf64_Shdr *shstr_table_header_addr=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff)+Ehdr->e_shstrndx;
           //拿到节表字符串表偏移
           char* shstr_table_addr=(char*)start_addr+shstr_table_header_addr->sh_offset;
           for (int i=0;i<Ehdr->e_shnum; i++) {
                
               section_header_index=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff+sizeof(Elf64_Shdr)*i);
               
               char flagbuf[20];
               char *cp = flagbuf;
               if (section_header_index->sh_flags & SHF_WRITE)
               *cp++ = 'W';
                 if (section_header_index->sh_flags & SHF_ALLOC)
               *cp++ = 'A';
                 if (section_header_index->sh_flags & SHF_EXECINSTR)
               *cp++ = 'X';
                 if (section_header_index->sh_flags & SHF_MERGE)
               *cp++ = 'M';
                 if (section_header_index->sh_flags & SHF_STRINGS)
               *cp++ = 'S';
                 if (section_header_index->sh_flags & SHF_INFO_LINK)
               *cp++ = 'I';
                 if (section_header_index->sh_flags & SHF_LINK_ORDER)
               *cp++ = 'L';
                 if (section_header_index->sh_flags & SHF_OS_NONCONFORMING)
               *cp++ = 'N';
                 if (section_header_index->sh_flags & SHF_GROUP)
               *cp++ = 'G';
                 if (section_header_index->sh_flags & SHF_TLS)
               *cp++ = 'T';
                 if (section_header_index->sh_flags & SHF_COMPRESSED)
               *cp++ = 'C';
                 if (section_header_index->sh_flags & SHF_ORDERED)
               *cp++ = 'O';
                 if (section_header_index->sh_flags & SHF_EXCLUDE)
               *cp++ = 'E';
                 *cp = '\0';
               printf ("[%2zu] %-20s %-12s %0*" PRIx64 " %0*" PRIx64 " %0*" PRIx64
               " %2" PRId64 " %-5s %2" PRId32 " %3" PRId32
               " %2" PRId64 "\n",
               i, &shstr_table_addr[section_header_index->sh_name],
               section_type_name (section_header_index->sh_type),
               Ehdr->e_ident[EI_CLASS] == ELFCLASS32 ? 8 : 16, section_header_index->sh_addr,
               Ehdr->e_ident[EI_CLASS] == ELFCLASS32 ? 6 : 8, section_header_index->sh_offset,
               Ehdr->e_ident[EI_CLASS] == ELFCLASS32 ? 6 : 8, section_header_index->sh_size,
               section_header_index->sh_entsize, flagbuf, section_header_index->sh_link, section_header_index->sh_info,
               section_header_index->sh_addralign);
              
           }

       }while(0);
}
/* Descriptor for data to be converted to or from memory format.  */
 
static void
handle_dynamic (Elf64_Shdr * dynamic_header)
{
  char buf[75];
  //获取个数
  long long  size =dynamic_header->sh_size/dynamic_header->sh_entsize;
  //拿到偏移
  Elf64_Dyn* pDyncMem=(Elf64_Dyn*)((char*)start_addr+dynamic_header->sh_offset);
  //拿到.dynstr
  Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
  Elf64_Shdr *shdr_start_addr=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff);
  Elf64_Shdr* dynstr_header= (Elf64_Shdr *)((char*)shdr_start_addr+sizeof(Elf64_Shdr)*dynamic_header->sh_link);
  char * dynstr_start_addr=(char*)start_addr+dynstr_header->sh_offset;
  //拿到节表字符串表头偏移
  Elf64_Shdr *shstr_table_header_addr=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff)+Ehdr->e_shstrndx;
  //拿到节表字符串表偏移
  char* shstr_table_addr=(char*)start_addr+shstr_table_header_addr->sh_offset;
  printf("Dynamic section:\n");
  printf("Dynamic segment contains %d entries:\n",size);
  printf("Addr: %0*" PRIx64 "   Offset: %0*" PRIx64 " Link to section: [ %d] section name: %-20s\n",
         Ehdr->e_ident[EI_CLASS] == ELFCLASS32 ? 8 : 16, dynstr_header->sh_addr,
         Ehdr->e_ident[EI_CLASS] == ELFCLASS32 ? 6 : 8, dynstr_header->sh_offset,
         dynamic_header->sh_link,&shstr_table_addr[dynstr_header->sh_name]);
    
    
    
    
   
    
    
  printf("Tag        Type                                                             Name/Value\n");
  for(int i=0 ; i < size ; i++ ){
      printf("0x%.8x ",pDyncMem[i].d_tag);
      switch(pDyncMem[i].d_tag){
      case DT_NULL:
          printf("%-65s","Terminating entry");
          printf("0x%d ",pDyncMem[i].d_un.d_val);
          break;
      case DT_NEEDED:
          printf("%-65s","String table offset of a needed shared library");
          printf("[ %s ]",(dynstr_start_addr + sizeof(char)*pDyncMem[i].d_un.d_val));//because @1 ,so in here not check the section
          break;
      case DT_PLTRELSZ:
          printf("%-65s","Total size in bytes of PLT relocations");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
      case DT_PLTGOT:
          printf("%-65s","Processor-dependent address");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_HASH:
          printf("%-65s","Address of symbol hash table");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_STRTAB:
          printf("%-65s","Address of string table");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_SYMTAB:
          printf("%-65s","Address of symbol table");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_RELA:
          printf("%-65s","Address of ElfNN_Rela relocations");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_RELASZ:
          printf("%-65s","Total size of ElfNN_Rela relocations");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
      case DT_RELAENT:
          printf("%-65s","Size of each ElfNN_Rela relocation entry");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
      case DT_STRSZ:
          printf("%-65s","Size of string table");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
      case DT_SYMENT:
          printf("%-65s","Size of each symbol table entry");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
      case DT_INIT:
          printf("%-65s","Address of initialization function");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_FINI:
          printf("%-65s","Address of finalization function");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_SONAME:
          printf("%-65s","String table offset of shared object name");
          printf("[ %s ]",(dynstr_start_addr + pDyncMem[i].d_un.d_val));
          break;
      case DT_RPATH:
          printf("%-65s","String table offset of library path. [sup]");
          printf("[ %s ]",(dynstr_start_addr + pDyncMem[i].d_un.d_val));
          break;
      case DT_SYMBOLIC:
          printf("%-65s","Indicates \"symbolic\" linking. [sup]");
          printf("%d ",pDyncMem[i].d_un.d_val);
          // TODO
          break;
      case DT_REL:
          printf("%-65s","Address of ElfNN_Rel relocations");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_RELSZ:
          printf("%-65s","Total size of ElfNN_Rel relocations");
          printf("%d ",pDyncMem[i].d_un.d_val);
          break;
      case DT_RELENT:
          printf("%-65s","Size of each ElfNN_Rel relocation");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
      case DT_PLTREL:
          printf("%-65s","Type of relocation used for PLT");
          printf("REL 0x%.2x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_DEBUG:
          printf("%-65s","Reserved debug");
          printf("%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_TEXTREL:
          printf("%-65s","Indicates there may be relocations in non-writable segments. [sup]");
          break;
      case DT_JMPREL:
          printf("%-65s","Address of PLT relocations");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_BIND_NOW:
          printf("%-65s","BIND_NOW");
          printf("0x%.8x",pDyncMem[i].d_un.d_ptr);
          //TODO
          break;
      case DT_INIT_ARRAY:
          printf("%-65s","Address of the array of pointers to initialization functions");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_FINI_ARRAY:
          printf("%-65s","Address of the array of pointers to termination functions ");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_INIT_ARRAYSZ:
          printf("%-65s","Size in bytes of the array of initialization functions");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
      case DT_FINI_ARRAYSZ:
          printf("%-65s","Size in bytes of the array of termination functions");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
      case DT_RUNPATH:
          printf("%-65s","String table offset of a null-terminated library search path string");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          printf("[ %s ]",(dynstr_start_addr + pDyncMem[i].d_un.d_val));
          break;
      case DT_FLAGS:
          printf("%-65s","Object specific flag values");
          memset(buf,0,75);
          if(pDyncMem[i].d_un.d_val & DF_ORIGIN){
              strcat(buf,"ORIGIN ");
          }
          if(pDyncMem[i].d_un.d_val & DF_SYMBOLIC){
              strcat(buf,"SYMBOLIC ");
          }
          if(pDyncMem[i].d_un.d_val & DF_TEXTREL){
              strcat(buf,"TEXTREL ");
          }
          if(pDyncMem[i].d_un.d_val & DF_BIND_NOW){
              strcat(buf,"BIND_NOW ");
          }
          if(pDyncMem[i].d_un.d_val & DF_STATIC_TLS){
              strcat(buf,"STATIC_TLS ");
          }
          printf("%s",buf);
          break;
      case DT_PREINIT_ARRAY:
          printf("%-65s","Address of the array of pointers to pre-initialization functions");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_PREINIT_ARRAYSZ:
          printf("%-65s","Size in bytes of the array of pre-initialization functions");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
//      case DT_MAXPOSTAGS:
//          printf("%-65s","number of positive tags");
//          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
//          break;
      case DT_LOOS:
          printf("%-65s","First OS-specific");
          break;
//      case DT_SUNW_RTLDINF:
//          printf("%-65s","ld.so.1 info (private)");
//          break;
//      case DT_SUNW_FILTER:
//          printf("%-65s","symbol filter name");
//          printf("[ %s ]",(pLookupSection->base + pDyncMem[i].d_un.d_val));
//          // TODO
//          break;
//      case DT_SUNW_CAP:
//          printf("%-65s","hardware/software");
//          break;
      case DT_HIOS:
          printf("%-65s","Last OS-specific");
          break;
      case DT_VALRNGLO:
          printf("%-65s","VALRNGLO");
          break;
      case DT_CHECKSUM:
          printf("%-65s","elf checksum");
          printf("0x%.8x ",pDyncMem[i].d_un.d_val);
          break;
      case DT_PLTPADSZ:
          printf("%-65s","pltpadding size");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
      case DT_MOVEENT:
          printf("%-65s","move table entry size ");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
      case DT_MOVESZ:
          printf("%-65s","move table size");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
      case DT_FEATURE_1:
          printf("%-65s","feature holder");
          memset(buf,0,75);
          if(pDyncMem[i].d_un.d_val & DTF_1_PARINIT){
              strcat(buf,"PARINIT ");
          }
          if(pDyncMem[i].d_un.d_val & DTF_1_CONFEXP){
              strcat(buf,"CONFEXP ");
          }
          printf("%s",buf);
          break;
      case DT_POSFLAG_1:
          printf("%-65s","flags for DT_* entries, effecting     the following DT_* entry See DF_P1_* definitions");
          memset(buf,0,75);
          if(pDyncMem[i].d_un.d_val & DF_P1_LAZYLOAD){
              strcat(buf,"LAZYLOAD ");
          }
          if(pDyncMem[i].d_un.d_val & DF_P1_GROUPPERM){
              strcat(buf,"GROUPPERM ");
          }
          printf("%s",buf);
          break;
      case DT_SYMINSZ:
          printf("%-65s","syminfo table size (in bytes)");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
      case DT_SYMINENT:
          printf("%-65s","syminfo entry size (in bytes)");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
      case DT_ADDRRNGLO:
          printf("%-65s","");
          break;
      case DT_GNU_HASH:
          printf("%-65s","GNU-style hash table");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_CONFIG:
          printf("%-65s","configuration information");
          break;
      case DT_DEPAUDIT:
          printf("%-65s","dependency auditing");
          break;
      case DT_AUDIT:
          printf("%-65s","object auditing");
          break;
      case DT_PLTPAD:
          printf("%-65s","pltpadding (sparcv9)");
          break;
      case DT_MOVETAB:
          printf("%-65s","move table");
          break;
      case DT_SYMINFO:
          printf("%-65s","yminfo table");
          break;
      case DT_VERSYM:
          printf("%-65s","Address of versym section");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_RELACOUNT:
          printf("%-65s","number of RELATIVE relocations");
          printf("%d ",pDyncMem[i].d_un.d_val);
          break;
      case DT_RELCOUNT:
          printf("%-65s","number of RELATIVE relocations");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
      case DT_FLAGS_1:
          printf("%-65s","state flags - see DF_1_* defs");
          memset(buf,0,75);
          strcat(buf,"Flags: ");
//          if(pDyncMem[i].d_un.d_val & DF_1_BIND_NOW){
//              strcat(buf,"NOW ");
//          }
          if(pDyncMem[i].d_un.d_val & DF_1_GLOBAL){
              strcat(buf,"GLOBAL ");
          }
          if(pDyncMem[i].d_un.d_val & DF_1_NODELETE){
              strcat(buf,"NODELETE ");
          }
          if(pDyncMem[i].d_un.d_val & DF_1_LOADFLTR){
              strcat(buf,"LOADFLTR ");
          }
          if(pDyncMem[i].d_un.d_val & DF_1_NOOPEN){
              strcat(buf,"NOOPEN ");
          }
          if(pDyncMem[i].d_un.d_val & DF_1_ORIGIN){
              strcat(buf,"ORIGIN ");
          }
          if(pDyncMem[i].d_un.d_val & DF_1_NODEFLIB){
              strcat(buf,"NODEFLIB ");
          }
          printf("%s",buf);
          break;
      case DT_VERDEF:
          printf("%-65s","Address of verdef section");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_VERDEFNUM:
          printf("%-65s","Number of elems in verdef section ");
          printf("%d (bytes) ",pDyncMem[i].d_un.d_val);
          break;
      case DT_VERNEED:
          printf("%-65s","Address of verneed section");
          printf("0x%.8x ",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_VERNEEDNUM:
          printf("%-65s","Number of elems in verneed section");
          printf("%d ",pDyncMem[i].d_un.d_val);
          break;
      case DT_LOPROC:
          printf("%-65s","First processor-specific type");
          break;
//      case DT_DEPRECATED_SPARC_REGISTER:
//          printf("%-65s","DEPRECATED_SPARC_REGISTER");
//          break;
      case DT_AUXILIARY:
          printf("%-65s","shared library auxiliary name");
          // TODO
          printf("[ %s ]",(dynstr_start_addr + pDyncMem[i].d_un.d_val));
          break;
//      case DT_USED:
//          printf("%-65s","ignored - same as needed");
//          break;
      case DT_FILTER:
          printf("%-65s","shared library filter name");
          printf("[ %s ]",(dynstr_start_addr + pDyncMem[i].d_un.d_val));
          //TODO
          break;
//      case DT_GNU_PRELINKED:
//          printf("%-65s","GNU_PRELINKED");
//          u1 time[STR_TIME_LEN];
//          memset(time,0,STR_TIME_LEN);
//          if(get_pre_link_time(pDyncMem[i].d_un.d_val,time) != 0){
//              goto Exit;
//          }
//          printf("%-65s ",time);
//          break;
      case DT_GNU_LIBLIST:
          printf("%-65s","GNU_LIBLIST");
          printf("0x%.8x",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_GNU_LIBLISTSZ:
          printf("%-65s","GNU_LIBLISTSZ");
          printf("%d (bytes)",pDyncMem[i].d_un.d_val);
          break;
      case DT_GNU_CONFLICT:
          printf("%-65s","GNU_CONFLICT");
          printf("0x%.8x",pDyncMem[i].d_un.d_ptr);
          break;
      case DT_GNU_CONFLICTSZ:
          printf("%-65s","GNU_CONFLICTSZ");
          printf("%d (bytes)",pDyncMem[i].d_un.d_val);
          break;
      default:
          printf("%-65s","");
          printf("0x%.8x",pDyncMem[i].d_un.d_ptr);
          break;
      }
      printf("\n");
      if(pDyncMem[i].d_tag == DT_NULL)
          break;
  }
}

void print_dynamic(){
     do{
              if(start_addr==NULL){
                  break;
              }
               Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
               
               Elf64_Shdr *section_header_index=NULL;
              
               //拿到节表字符串表头偏移
               Elf64_Shdr *shstr_table_header_addr=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff)+Ehdr->e_shstrndx;
               //拿到节表字符串表偏移
               char* shstr_table_addr=(char*)start_addr+shstr_table_header_addr->sh_offset;
               for (int i=0;i<Ehdr->e_shnum; i++) {
                    
                   section_header_index=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff+sizeof(Elf64_Shdr)*i);
                   char p_name[]=".dynamic";
                   char p_name_buf[100];
                   const char * s_name=(const char *)shstr_table_addr[section_header_index->sh_name];
                   if(i>2){
                       sprintf(p_name_buf,"%-20s",&shstr_table_addr[section_header_index->sh_name]);
                       //printf("%s\n", p_name_buf);
                       if((strstr((const char *)p_name_buf,(const char *)p_name)!=NULL)&&(section_header_index->sh_type==SHT_DYNAMIC)){
                           handle_dynamic((Elf64_Shdr *)section_header_index);
                       }
                   }
               }

           }while(0);
}
static void get_rel_dyn_type(Elf64_Half machineType,int rInfo,char* type){
    switch(machineType){
    case EM_386:
        switch(rInfo){
        case    R_386_NONE:
            memcpy(type,"R_386_NONE",strlen("R_386_NONE"));
            break;
        case    R_386_32:
            memcpy(type,"R_386_32",strlen("R_386_32"));
            break;
        case    R_386_PC32:
            memcpy(type,"R_386_NONE",strlen("R_386_PC32"));
            break;
        case    R_386_GOT32:
            memcpy(type,"R_386_GOT32",strlen("R_386_GOT32"));
            break;
        case    R_386_PLT32:
            memcpy(type,"R_386_PLT32",strlen("R_386_PLT32"));
            break;
        case    R_386_COPY:
            memcpy(type,"R_386_COPY",strlen("R_386_COPY"));
            break;
        case    R_386_GLOB_DAT:
            memcpy(type,"R_386_GLOB_DAT",strlen("R_386_GLOB_DAT"));
            break;
        case    R_386_JMP_SLOT:
            memcpy(type,"R_386_JMP_SLOT",strlen("R_386_JMP_SLOT"));
            break;
        case    R_386_RELATIVE:
            memcpy(type,"R_386_RELATIVE",strlen("R_386_RELATIVE"));
            break;
        case    R_386_GOTOFF:
            memcpy(type,"R_386_GOTOFF",strlen("R_386_GOTOFF"));
            break;
        case    R_386_GOTPC:
            memcpy(type,"R_386_GLOB_DAT",strlen("R_386_GOTPC"));
            break;
        case    R_386_TLS_TPOFF:
            memcpy(type,"R_386_TLS_TPOFF",strlen("R_386_TLS_TPOFF"));
            break;
        case    R_386_TLS_IE:
            memcpy(type,"R_386_TLS_IE",strlen("R_386_TLS_IE"));
            break;
        case    R_386_TLS_GOTIE:
            memcpy(type,"R_386_TLS_GOTIE",strlen("R_386_TLS_GOTIE"));
            break;
        case    R_386_TLS_LE:
            memcpy(type,"R_386_TLS_LE",strlen("R_386_TLS_LE"));
            break;
        case    R_386_TLS_GD:
            memcpy(type,"R_386_TLS_GD",strlen("R_386_TLS_GD"));
            break;
        case    R_386_TLS_LDM:
            memcpy(type,"R_386_TLS_LDM",strlen("R_386_TLS_LDM"));
            break;
        case    R_386_16:
            memcpy(type,"R_386_16",strlen("R_386_16"));
            break;
        case    R_386_PC16:
            memcpy(type,"R_386_PC16",strlen("R_386_PC16"));
            break;
        case    R_386_8:
            memcpy(type,"R_386_8",strlen("R_386_8"));
            break;
        case    R_386_PC8:
            memcpy(type,"R_386_PC8",strlen("R_386_PC8"));
            break;
        case    R_386_TLS_GD_32:
            memcpy(type,"R_386_TLS_GD_32",strlen("R_386_TLS_GD_32"));
            break;
        case    R_386_TLS_GD_PUSH:
            memcpy(type,"R_386_TLS_GD_PUSH",strlen("R_386_TLS_GD_PUSH"));
            break;
        case    R_386_TLS_GD_CALL:
            memcpy(type,"R_386_TLS_GD_CALL",strlen("R_386_TLS_GD_CALL"));
            break;
        case    R_386_TLS_GD_POP:
            memcpy(type,"R_386_TLS_GD_POP",strlen("R_386_TLS_GD_POP"));
            break;
        case    R_386_TLS_LDM_32:
            memcpy(type,"R_386_TLS_LDM_32",strlen("R_386_TLS_LDM_32"));
            break;
        case    R_386_TLS_LDM_PUSH:
            memcpy(type,"R_386_TLS_LDM_PUSH",strlen("R_386_TLS_LDM_PUSH"));
            break;
        case    R_386_TLS_LDM_CALL:
            memcpy(type,"R_386_TLS_LDM_CALL",strlen("R_386_TLS_LDM_CALL"));
            break;
        case    R_386_TLS_LDM_POP:
            memcpy(type,"R_386_TLS_LDM_POP",strlen("R_386_TLS_LDM_POP"));
            break;
        case    R_386_TLS_LDO_32:
            memcpy(type,"R_386_TLS_LDO_32",strlen("R_386_TLS_LDO_32"));
            break;
        case    R_386_TLS_IE_32:
            memcpy(type,"R_386_TLS_IE_32",strlen("R_386_TLS_IE_32"));
            break;
        case    R_386_TLS_LE_32:
            memcpy(type,"R_386_TLS_LE_32",strlen("R_386_TLS_LE_32"));
            break;
        case    R_386_TLS_DTPMOD32:
            memcpy(type,"R_386_TLS_DTPMOD32",strlen("R_386_TLS_DTPMOD32"));
            break;
        case    R_386_TLS_DTPOFF32:
            memcpy(type,"R_386_TLS_DTPOFF32",strlen("R_386_TLS_DTPOFF32"));
            break;
        case    R_386_TLS_TPOFF32:
            memcpy(type,"R_386_TLS_TPOFF32",strlen("R_386_TLS_TPOFF32"));
            break;
        case    R_386_IRELATIVE:
            memcpy(type,"R_386_IRELATIVE",strlen("R_386_IRELATIVE"));
            break;
        default:
            break;
        }
        break;
    case EM_ARM:
        switch(rInfo){
        case    R_ARM_NONE:
            memcpy(type,"R_ARM_NONE",strlen("R_ARM_NONE"));
            break;
        case    R_ARM_PC24:
            memcpy(type,"R_ARM_PC24",strlen("R_ARM_PC24"));
            break;
        case    R_ARM_ABS32:
            memcpy(type,"R_ARM_ABS32",strlen("R_ARM_ABS32"));
            break;
        case    R_ARM_REL32:
            memcpy(type,"R_ARM_REL32",strlen("R_ARM_REL32"));
            break;
        case    R_ARM_PC13:
            memcpy(type,"R_ARM_PC13",strlen("R_ARM_PC13"));
            break;
        case    R_ARM_ABS16:
            memcpy(type,"R_ARM_ABS16",strlen("R_ARM_ABS16"));
            break;
        case    R_ARM_ABS12:
            memcpy(type,"R_ARM_ABS12",strlen("R_ARM_ABS12"));
            break;
        case    R_ARM_THM_ABS5:
            memcpy(type,"R_ARM_THM_ABS5",strlen("R_ARM_THM_ABS5"));
            break;
        case    R_ARM_ABS8:
            memcpy(type,"R_ARM_ABS8",strlen("R_ARM_ABS8"));
            break;
        case    R_ARM_SBREL32:
            memcpy(type,"R_ARM_SBREL32",strlen("R_ARM_SBREL32"));
            break;
        case    R_ARM_THM_PC22:
            memcpy(type,"R_ARM_THM_PC22",strlen("R_ARM_THM_PC22"));
            break;
        case    R_ARM_THM_PC8:
            memcpy(type,"R_ARM_THM_PC8",strlen("R_ARM_THM_PC8"));
            break;
        case    R_ARM_AMP_VCALL9:
            memcpy(type,"R_ARM_AMP_VCALL9",strlen("R_ARM_AMP_VCALL9"));
            break;
        case    R_ARM_SWI24:
            memcpy(type,"R_ARM_SWI24",strlen("R_ARM_SWI24"));
            break;
        case    R_ARM_THM_SWI8:
            memcpy(type,"R_ARM_THM_SWI8",strlen("R_ARM_THM_SWI8"));
            break;
        case    R_ARM_XPC25:
            memcpy(type,"R_ARM_XPC25",strlen("R_ARM_XPC25"));
            break;
        case    R_ARM_THM_XPC22:
            memcpy(type,"R_ARM_THM_XPC22",strlen("R_ARM_THM_XPC22"));
            break;
        case    R_ARM_TLS_DTPMOD32:
            memcpy(type,"R_ARM_TLS_DTPMOD32",strlen("R_ARM_TLS_DTPMOD32"));
            break;
        case    R_ARM_TLS_DTPOFF32:
            memcpy(type,"R_ARM_TLS_DTPOFF32",strlen("R_ARM_TLS_DTPOFF32"));
            break;
        case    R_ARM_TLS_TPOFF32:
            memcpy(type,"R_ARM_TLS_TPOFF32",strlen("R_ARM_TLS_TPOFF32"));
            break;
        case    R_ARM_COPY:
            memcpy(type,"R_ARM_COPY",strlen("R_ARM_COPY"));
            break;
        case    R_ARM_GLOB_DAT:
            memcpy(type,"R_ARM_GLOB_DAT",strlen("R_ARM_GLOB_DAT"));
            break;
        case    R_ARM_JUMP_SLOT:
            memcpy(type,"R_ARM_JUMP_SLOT",strlen("R_ARM_JUMP_SLOT"));
            break;
        case    R_ARM_RELATIVE:
            memcpy(type,"R_ARM_RELATIVE",strlen("R_ARM_RELATIVE"));
            break;
        case    R_ARM_GOTOFF:
            memcpy(type,"R_ARM_GOTOFF",strlen("R_ARM_GOTOFF"));
            break;
        case    R_ARM_GOTPC:
            memcpy(type,"R_ARM_GOTPC",strlen("R_ARM_GOTPC"));
            break;
        case    R_ARM_GOT32:
            memcpy(type,"R_ARM_GOT32",strlen("R_ARM_GOT32"));
            break;
        case    R_ARM_PLT32:
            memcpy(type,"R_ARM_PLT32",strlen("R_ARM_PLT32"));
            break;
        case    R_ARM_GNU_VTENTRY:
            memcpy(type,"R_ARM_GNU_VTENTRY",strlen("R_ARM_GNU_VTENTRY"));
            break;
        case    R_ARM_GNU_VTINHERIT:
            memcpy(type,"R_ARM_GNU_VTINHERIT",strlen("R_ARM_GNU_VTINHERIT"));
            break;
        case    R_ARM_RSBREL32:
            memcpy(type,"R_ARM_RSBREL32",strlen("R_ARM_RSBREL32"));
            break;
        case    R_ARM_THM_RPC22:
            memcpy(type,"R_ARM_THM_RPC22",strlen("R_ARM_THM_RPC22"));
            break;
        case    R_ARM_RREL32:
            memcpy(type,"R_ARM_RREL32",strlen("R_ARM_RREL32"));
            break;
//        case    R_ARM_RABS32:
//            memcpy(type,"R_ARM_RABS32",strlen("R_ARM_RABS32"));
//            break;
        case    R_ARM_RPC24:
            memcpy(type,"R_ARM_RPC24",strlen("R_ARM_RPC24"));
            break;
        case    R_ARM_RBASE:
            memcpy(type,"R_ARM_RBASE",strlen("R_ARM_RBASE"));
            break;
        default:
            break;
        }
        break;
//    #define R_X86_64_NONE        0    /* No reloc */
//    #define R_X86_64_64        1    /* Direct 64 bit  */
//    #define R_X86_64_PC32        2    /* PC relative 32 bit signed */
//    #define R_X86_64_GOT32        3    /* 32 bit GOT entry */
//    #define R_X86_64_PLT32        4    /* 32 bit PLT address */
//    #define R_X86_64_COPY        5    /* Copy symbol at runtime */
//    #define R_X86_64_GLOB_DAT    6    /* Create GOT entry */
//    #define R_X86_64_JUMP_SLOT    7    /* Create PLT entry */
//    #define R_X86_64_RELATIVE    8    /* Adjust by program base */
//    #define R_X86_64_GOTPCREL    9    /* 32 bit signed PC relative
//                           offset to GOT */
//    #define R_X86_64_32        10    /* Direct 32 bit zero extended */
//    #define R_X86_64_32S        11    /* Direct 32 bit sign extended */
//    #define R_X86_64_16        12    /* Direct 16 bit zero extended */
//    #define R_X86_64_PC16        13    /* 16 bit sign extended pc relative */
//    #define R_X86_64_8        14    /* Direct 8 bit sign extended  */
//    #define R_X86_64_PC8        15    /* 8 bit sign extended pc relative */
//    #define R_X86_64_DTPMOD64    16    /* ID of module containing symbol */
//    #define R_X86_64_DTPOFF64    17    /* Offset in module's TLS block */
//    #define R_X86_64_TPOFF64    18    /* Offset in initial TLS block */
//    #define R_X86_64_TLSGD        19    /* 32 bit signed PC relative offset
//                           to two GOT entries for GD symbol */
//    #define R_X86_64_TLSLD        20    /* 32 bit signed PC relative offset
//                           to two GOT entries for LD symbol */
//    #define R_X86_64_DTPOFF32    21    /* Offset in TLS block */
//    #define R_X86_64_GOTTPOFF    22    /* 32 bit signed PC relative offset
//                           to GOT entry for IE symbol */
//    #define R_X86_64_TPOFF32    23    /* Offset in initial TLS block */
//    #define R_X86_64_PC64        24    /* PC relative 64 bit */
//    #define R_X86_64_GOTOFF64    25    /* 64 bit offset to GOT */
//    #define R_X86_64_GOTPC32    26    /* 32 bit signed pc relative
//                           offset to GOT */
//    #define R_X86_64_GOT64        27    /* 64-bit GOT entry offset */
//    #define R_X86_64_GOTPCREL64    28    /* 64-bit PC relative offset
//                           to GOT entry */
//    #define R_X86_64_GOTPC64    29    /* 64-bit PC relative offset to GOT */
//    #define R_X86_64_GOTPLT64    30     /* like GOT64, says PLT entry needed */
//    #define R_X86_64_PLTOFF64    31    /* 64-bit GOT relative offset
//                           to PLT entry */
//    #define R_X86_64_SIZE32        32    /* Size of symbol plus 32-bit addend */
//    #define R_X86_64_SIZE64        33    /* Size of symbol plus 64-bit addend */
//    #define R_X86_64_GOTPC32_TLSDESC 34    /* GOT offset for TLS descriptor.  */
//    #define R_X86_64_TLSDESC_CALL   35    /* Marker for call through TLS
//                           descriptor.  */
//    #define R_X86_64_TLSDESC        36    /* TLS descriptor.  */
//    #define R_X86_64_IRELATIVE    37    /* Adjust indirectly by program base */
//    #define R_X86_64_RELATIVE64    38    /* 64-bit adjust by program base */
//                        /* 39 Reserved was R_X86_64_PC32_BND */
//                        /* 40 Reserved was R_X86_64_PLT32_BND */
 
  //没写完
     case EM_X86_64:
            switch(rInfo){
            case    R_X86_64_NONE:
                memcpy(type,"R_X86_64_NONE",strlen("R_X86_64_NONE"));
                break;
            case    R_X86_64_64:
                memcpy(type,"R_X86_64_64",strlen("R_X86_64_64"));
                break;
            case    R_X86_64_PC32:
                memcpy(type,"R_X86_64_PC32",strlen("R_X86_64_PC32"));
                break;
            case    R_ARM_REL32:
                memcpy(type,"R_ARM_REL32",strlen("R_ARM_REL32"));
                break;
            case    R_ARM_PC13:
                memcpy(type,"R_ARM_PC13",strlen("R_ARM_PC13"));
                break;
            case    R_X86_64_COPY:
                memcpy(type,"R_X86_64_COPY",strlen("R_X86_64_COPY"));
                break;
            case    R_X86_64_GLOB_DAT:
                memcpy(type,"R_X86_64_GLOB_DAT",strlen("R_X86_64_GLOB_DAT"));
                break;
            case    R_X86_64_JUMP_SLOT:
                memcpy(type,"R_X86_64_JUMP_SLOT",strlen("R_X86_64_JUMP_SLOT"));
                break;
            case    R_X86_64_RELATIVE:
                memcpy(type,"R_X86_64_RELATIVE",strlen("R_X86_64_RELATIVE"));
                break;
            case    R_ARM_SBREL32:
                memcpy(type,"R_ARM_SBREL32",strlen("R_ARM_SBREL32"));
                break;
            case    R_ARM_THM_PC22:
                memcpy(type,"R_ARM_THM_PC22",strlen("R_ARM_THM_PC22"));
                break;
            case    R_ARM_THM_PC8:
                memcpy(type,"R_ARM_THM_PC8",strlen("R_ARM_THM_PC8"));
                break;
            case    R_ARM_AMP_VCALL9:
                memcpy(type,"R_ARM_AMP_VCALL9",strlen("R_ARM_AMP_VCALL9"));
                break;
            case    R_ARM_SWI24:
                memcpy(type,"R_ARM_SWI24",strlen("R_ARM_SWI24"));
                break;
            case    R_ARM_THM_SWI8:
                memcpy(type,"R_ARM_THM_SWI8",strlen("R_ARM_THM_SWI8"));
                break;
            case    R_ARM_XPC25:
                memcpy(type,"R_ARM_XPC25",strlen("R_ARM_XPC25"));
                break;
            case    R_ARM_THM_XPC22:
                memcpy(type,"R_ARM_THM_XPC22",strlen("R_ARM_THM_XPC22"));
                break;
            case    R_ARM_TLS_DTPMOD32:
                memcpy(type,"R_ARM_TLS_DTPMOD32",strlen("R_ARM_TLS_DTPMOD32"));
                break;
            case    R_ARM_TLS_DTPOFF32:
                memcpy(type,"R_ARM_TLS_DTPOFF32",strlen("R_ARM_TLS_DTPOFF32"));
                break;
            case    R_ARM_TLS_TPOFF32:
                memcpy(type,"R_ARM_TLS_TPOFF32",strlen("R_ARM_TLS_TPOFF32"));
                break;
            case    R_ARM_COPY:
                memcpy(type,"R_ARM_COPY",strlen("R_ARM_COPY"));
                break;
            case    R_ARM_GLOB_DAT:
                memcpy(type,"R_ARM_GLOB_DAT",strlen("R_ARM_GLOB_DAT"));
                break;
            case    R_ARM_JUMP_SLOT:
                memcpy(type,"R_ARM_JUMP_SLOT",strlen("R_ARM_JUMP_SLOT"));
                break;
            case    R_ARM_RELATIVE:
                memcpy(type,"R_ARM_RELATIVE",strlen("R_ARM_RELATIVE"));
                break;
            case    R_ARM_GOTOFF:
                memcpy(type,"R_ARM_GOTOFF",strlen("R_ARM_GOTOFF"));
                break;
            case    R_ARM_GOTPC:
                memcpy(type,"R_ARM_GOTPC",strlen("R_ARM_GOTPC"));
                break;
            case    R_ARM_GOT32:
                memcpy(type,"R_ARM_GOT32",strlen("R_ARM_GOT32"));
                break;
            case    R_ARM_PLT32:
                memcpy(type,"R_ARM_PLT32",strlen("R_ARM_PLT32"));
                break;
            case    R_ARM_GNU_VTENTRY:
                memcpy(type,"R_ARM_GNU_VTENTRY",strlen("R_ARM_GNU_VTENTRY"));
                break;
            case    R_ARM_GNU_VTINHERIT:
                memcpy(type,"R_ARM_GNU_VTINHERIT",strlen("R_ARM_GNU_VTINHERIT"));
                break;
            case    R_ARM_RSBREL32:
                memcpy(type,"R_ARM_RSBREL32",strlen("R_ARM_RSBREL32"));
                break;
            case    R_X86_64_RELATIVE64:
                memcpy(type,"R_X86_64_RELATIVE64",strlen("R_X86_64_RELATIVE64"));
                break;
            case    R_X86_64_GOTPCRELX:
                memcpy(type,"R_X86_64_GOTPCRELX",strlen("R_X86_64_GOTPCRELX"));
                break;
    //        case    R_ARM_RABS32:
    //            memcpy(type,"R_ARM_RABS32",strlen("R_ARM_RABS32"));
    //            break;
            case    R_X86_64_REX_GOTPCRELX:
                memcpy(type,"R_X86_64_REX_GOTPCRELX",strlen("R_X86_64_REX_GOTPCRELX"));
                break;
            case    R_X86_64_NUM:
                memcpy(type,"R_X86_64_NUM",strlen("R_X86_64_NUM"));
                break;
            default:
                break;
            }
            break;
    default :
        //TODO other  ellipsis...
        break;
    }
}
void printf_Relplt_name(int num){
    do{
       if(start_addr==NULL){
           break;
       }
        Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
        
        Elf64_Shdr *section_header_index=NULL;
       
        //拿到节表字符串表头偏移
        Elf64_Shdr *shstr_table_header_addr=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff)+Ehdr->e_shstrndx;
        //拿到节表字符串表偏移
        char* shstr_table_addr=(char*)start_addr+shstr_table_header_addr->sh_offset;
        for (int i=0;i<Ehdr->e_shnum; i++) {
             
            section_header_index=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff+sizeof(Elf64_Shdr)*i);
            char p_name[]=".dynstr";
            char p_name_buf[100];
            //const char * s_name=(const char *)shstr_table_addr[section_header_index->sh_name];
            if(i>2){
                sprintf(p_name_buf,"%-20s",&shstr_table_addr[section_header_index->sh_name]);
                //printf("%s\n", p_name_buf);
                if((strstr((const char *)p_name_buf,(const char *)p_name)!=NULL)&&(section_header_index->sh_type==SHT_STRTAB)){
                       long long size=section_header_index->sh_size;
                       //    Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
                           //拿到偏移
                           char* pdynstr=(char*)((char*)start_addr+section_header_index->sh_offset);
                           char* old=pdynstr;
                           for (int i=0; pdynstr-old<size;i++ ) {
                               if(num==i){
                                   printf("%-40s %d",&pdynstr[1],i);
                               }
                               pdynstr=pdynstr+strlen(pdynstr+1)+1;
                           }
                   // handle_dynstr((Elf64_Shdr *)section_header_index,i);
                }
            }
        }

    }while(0);
    
       
}
void handle_relocation (Elf64_Shdr * relocation_header,int n){
    char buf[55];
    long long size=relocation_header->sh_size/relocation_header->sh_entsize;
    Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
    //拿到偏移
     Elf64_Rela* pRelplt=(Elf64_Rela*)((char*)start_addr+relocation_header->sh_offset);
     
    //sh 所有表偏移
     Elf64_Shdr *shdr_start_addr=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff);

     Elf32_Sym* Relplt_str_header= (Elf32_Sym *)((char*)shdr_start_addr+sizeof(Elf64_Shdr)*relocation_header->sh_link);
     Elf64_Shdr* Relplt_header= (Elf64_Shdr *)((char*)shdr_start_addr+sizeof(Elf64_Shdr)*((Elf64_Shdr*)Relplt_str_header)->sh_link);
     
     Elf32_Sym* Relplt_str_start_addr=(Elf32_Sym*)((char*)start_addr+Relplt_header->sh_offset);
     //拿到节表字符串表头偏移
     
     Elf64_Shdr *shstr_table_header_addr=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff)+Ehdr->e_shstrndx;
     //拿到节表字符串表偏移
     char* shstr_table_addr=(char*)start_addr+shstr_table_header_addr->sh_offset;
    printf("Relocation section '%s' at offset 0x%.8x contains %d entries:\n",&(shstr_table_addr[relocation_header->sh_name]),relocation_header->sh_offset,n);
     printf("Offset     Info     Type               Sym.Value  Sym.Name                                 index\n");
    for (int i=0; i<size; i++) {
         printf("0x%.8x ",pRelplt[i].r_offset);
         printf("%.8x ",pRelplt[i].r_info);
         //printf("%.8x",pRelplt[i].r_addend);
         memset(&buf,0,55);
         get_rel_dyn_type(Ehdr->e_machine,(int)ELF64_R_TYPE(pRelplt[i].r_info),buf);
         printf("     %-15s ",buf);
          
         {
              printf(" %.8x   ",Relplt_str_header[ELF64_R_SYM(pRelplt[i].r_info)].st_value);
              //printf(" %-10s  ",&Relplt_str_start_addr[ELF64_R_SYM(pRelplt[i].r_info)].st_name);
              //打印名字
              printf_Relplt_name(ELF64_R_SYM(pRelplt[i].r_info));
              
         }
 
          printf("\n");
    }
    
    
}

void handle_dynstr (Elf64_Shdr * dynstr_header,int n){
    long long size=dynstr_header->sh_size;
//    Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
    //拿到偏移
    char* pdynstr=(char*)((char*)start_addr+dynstr_header->sh_offset);
    char* old=pdynstr;
    printf(".dynstr    name\n");
    for (int i=0; pdynstr-old<size;i++ ) {
        printf("[%-3d]      %-10s  ",i,&pdynstr[1]);
        printf("\n");
        pdynstr=pdynstr+strlen(pdynstr+1)+1;
    }
}
void handle_symtab (Elf64_Shdr * symtab_header,int n){
    
//    Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
    //拿到偏移
    Elf64_Sym* pSymMem=(Elf64_Sym*)((char*)start_addr+symtab_header->sh_offset);
    Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
     
    //sh 所有表偏移
     Elf64_Shdr *shdr_start_addr=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff);
    // link strtab
    Elf64_Shdr* strtab_header= (Elf64_Shdr *)((char*)shdr_start_addr+sizeof(Elf64_Shdr)*symtab_header->sh_link);
    //strtab addr
    char *strtab_start_addr=(char *)((char*)start_addr+strtab_header->sh_offset);
    
    
    
    long long size=symtab_header->sh_size/symtab_header->sh_entsize;
    //
    //printf(".dynstr    name\n");
           printf("Symbol table :\n");
           printf("Symbol table '.symtab' contains %d entries:\n",size);
           printf("Num:  Value    Size   Type                          Bind                                 Vis       Ndx       Name\n");
           long long i = 0;
           for(; i < size ; i++){
               printf("%3d:  ",i);
               printf("%.8x ",pSymMem[i].st_value);
               printf("%-7d",pSymMem[i].st_size);
               switch(ELF32_ST_TYPE(pSymMem[i].st_info)){
               case STT_NOTYPE:
                   printf("%-30s","Unspecified type");
                   break;
               case STT_OBJECT:
                   printf("%-30s","Data object");
                   break;
               case STT_FUNC:
                   printf("%-30s","Function");
                   break;
               case STT_SECTION:
                   printf("%-30s","Section");
                   break;
               case STT_FILE:
                   printf("%-30s","Source file");
                   break;
               case STT_COMMON:
                   printf("%-30s","Uninitialized common block");
                   break;
               case STT_TLS:
                   printf("%-30s","TLS object");
                   break;
               case STT_NUM:
                   printf("%-30s","NUM");
                   break;
               case STT_LOOS:
                   printf("%-30s","TLS object");
                   break;
               case STT_HIOS:
                   printf("%-30s","specific semantics");
                   break;
               case STT_LOPROC:
                   printf("%-30s","reserved range for processor");
                   break;
               case STT_HIPROC:
                   printf("%-30s","specific semantics");
                   break;
               default:
                   printf("%-30s","");
                   break;
               }
               switch(ELF32_ST_BIND(pSymMem[i].st_info)){
               case STB_LOCAL:
                   printf("%-37s","Local symbol");
                   break;
               case STB_GLOBAL:
                   printf("%-37s","Global symbol");
                   break;
               case STB_WEAK:
                   printf("%-37s","like global - lower precedence");
                   break;
               case STB_LOOS:
                   printf("%-37s","Reserved range for operating system");
                   break;
               case STB_HIOS:
                   printf("%-37s","specific semantics");
                   break;
               case STB_LOPROC:
                   printf("%-37s","reserved range for processor");
                   break;
               case STB_HIPROC:
                   printf("%-37s","specific semantics");
                   break;
               default:
                   printf("%-37s","");
                   break;
               }
               switch(ELF32_ST_VISIBILITY(pSymMem[i].st_other)){
               case STV_DEFAULT:
                   printf("%-10s","DEFAULT");
                   break;
               case STV_INTERNAL:
                   printf("%-10s","INTERNA");
                   break;
               case STV_HIDDEN:
                   printf("%-10s","HIDDEN");
                   break;
               case STV_PROTECTED:
                   printf("%-10s","PROTECTED");
                   break;
               default:
                   printf("%-10s","");
                   break;
               }
               switch(pSymMem[i].st_shndx){
               case SHN_UNDEF:
                   printf("%-10s","UNDEF");
                   break;
               case SHN_LORESERVE:
                   printf("%-10s","LORESERVE");
                   break;
               case SHN_HIPROC:
                   printf("%-10s","HIPROC");
                   break;
               case SHN_LOOS:
                   printf("%-10s","LOOS");
                   break;
               case SHN_HIOS:
                   printf("%-10s","HIOS");
                   break;
               case SHN_ABS:
                   printf("%-10s","ABS");
                   break;
               case SHN_COMMON:
                   printf("%-10s","COMMON");
                   break;
               case SHN_XINDEX:
                   printf("%-10s","XINDEX");
                   break;
               default:
                   printf("%-10d",pSymMem[i].st_shndx);
                   break;
               }
               Elf64_Sym temp=pSymMem[i];
               if(pSymMem[i].st_name>0)
                   printf("%s",(strtab_start_addr+pSymMem[i].st_name));
 
               printf("\n");
           }
}
void print_rela(){
     do{
              if(start_addr==NULL){
                  break;
              }
               Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
               
               Elf64_Shdr *section_header_index=NULL;
              
               //拿到节表字符串表头偏移
               Elf64_Shdr *shstr_table_header_addr=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff)+Ehdr->e_shstrndx;
               //拿到节表字符串表偏移
               char* shstr_table_addr=(char*)start_addr+shstr_table_header_addr->sh_offset;
               for (int i=0;i<Ehdr->e_shnum; i++) {
                    
                   section_header_index=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff+sizeof(Elf64_Shdr)*i);
                    
                   //const char * s_name=(const char *)shstr_table_addr[section_header_index->sh_name];
                   if(i>2){
                       //sprintf(p_name_buf,"%-20s",&shstr_table_addr[section_header_index->sh_name]);
                       //printf("%s\n", p_name_buf);
                       if((section_header_index->sh_type==SHT_RELA)){
                           handle_relocation((Elf64_Shdr *)section_header_index,i);
                       }
                   }
               }

           }while(0);
}
void print_rel(){
     do{
              if(start_addr==NULL){
                  break;
              }
               Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;

               Elf64_Shdr *section_header_index=NULL;

               //拿到节表字符串表头偏移
               Elf64_Shdr *shstr_table_header_addr=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff)+Ehdr->e_shstrndx;
               //拿到节表字符串表偏移
               char* shstr_table_addr=(char*)start_addr+shstr_table_header_addr->sh_offset;
               for (int i=0;i<Ehdr->e_shnum; i++) {

                   section_header_index=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff+sizeof(Elf64_Shdr)*i);

                   //const char * s_name=(const char *)shstr_table_addr[section_header_index->sh_name];
                   if(i>2){
                       //sprintf(p_name_buf,"%-20s",&shstr_table_addr[section_header_index->sh_name]);
                       //printf("%s\n", p_name_buf);
                       if((section_header_index->sh_type==SHT_REL)){
                           handle_relocation((Elf64_Shdr *)section_header_index,i);
                       }
                   }
               }

           }while(0);
}
void print_dynstr(){
    do{
                if(start_addr==NULL){
                    break;
                }
                 Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
                 
                 Elf64_Shdr *section_header_index=NULL;
                
                 //拿到节表字符串表头偏移
                 Elf64_Shdr *shstr_table_header_addr=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff)+Ehdr->e_shstrndx;
                 //拿到节表字符串表偏移
                 char* shstr_table_addr=(char*)start_addr+shstr_table_header_addr->sh_offset;
                 for (int i=0;i<Ehdr->e_shnum; i++) {
                      
                     section_header_index=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff+sizeof(Elf64_Shdr)*i);
                     char p_name[]=".dynstr";
                     char p_name_buf[100];
                     //const char * s_name=(const char *)shstr_table_addr[section_header_index->sh_name];
                     if(i>2){
                         sprintf(p_name_buf,"%-20s",&shstr_table_addr[section_header_index->sh_name]);
                         //printf("%s\n", p_name_buf);
                         if((strstr((const char *)p_name_buf,(const char *)p_name)!=NULL)&&(section_header_index->sh_type==SHT_STRTAB)){
                             handle_dynstr((Elf64_Shdr *)section_header_index,i);
                         }
                     }
                 }

             }while(0);
}
void print_symtab(){
    do{
                if(start_addr==NULL){
                    break;
                }
                 Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
                 
                 Elf64_Shdr *section_header_index=NULL;
                
                 //拿到节表字符串表头偏移
                 Elf64_Shdr *shstr_table_header_addr=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff)+Ehdr->e_shstrndx;
                 //拿到节表字符串表偏移
                 char* shstr_table_addr=(char*)start_addr+shstr_table_header_addr->sh_offset;
                 for (int i=0;i<Ehdr->e_shnum; i++) {
                      
                     section_header_index=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff+sizeof(Elf64_Shdr)*i);
                     char p_name[]=".symtab";
                     char p_name_buf[100];
                     //const char * s_name=(const char *)shstr_table_addr[section_header_index->sh_name];
                     if(i>2){
                         sprintf(p_name_buf,"%-20s",&shstr_table_addr[section_header_index->sh_name]);
                         //printf("%s\n", p_name_buf);
                         if((strstr((const char *)p_name_buf,(const char *)p_name)!=NULL)&&(section_header_index->sh_type==SHT_SYMTAB)){
                             handle_symtab((Elf64_Shdr *)section_header_index,i);
                         }
                     }
                 }

             }while(0);
}
void print_text_opcode(){
     do{
                    if(start_addr==NULL){
                        break;
                    }
                     Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
                     
                     Elf64_Shdr *section_header_index=NULL;
                    
                     //拿到节表字符串表头偏移
                     Elf64_Shdr *shstr_table_header_addr=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff)+Ehdr->e_shstrndx;
                     //拿到节表字符串表偏移
                     char* shstr_table_addr=(char*)start_addr+shstr_table_header_addr->sh_offset;
                     for (int i=0;i<Ehdr->e_shnum; i++) {
                          
                         section_header_index=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff+sizeof(Elf64_Shdr)*i);
                         char p_name[]=".mytext";
                         char p_name_buf[100];
                         //const char * s_name=(const char *)shstr_table_addr[section_header_index->sh_name];
                         if(i>2){
                             sprintf(p_name_buf,"%-20s",&shstr_table_addr[section_header_index->sh_name]);
                             //printf("%s\n", p_name_buf);
                             if((strstr((const char *)p_name_buf,(const char *)p_name)!=NULL)&&(section_header_index->sh_type==SHT_PROGBITS)){
                                 //handle_symtab((Elf64_Shdr *)section_header_index,i);
                                 //printf("xxx\n");
                                 char* buffer=NULL;
                                 buffer=(char*)malloc(section_header_index->sh_size+1);
                                 if (buffer!=NULL) {
                                     memcpy(buffer,(char*)start_addr+section_header_index->sh_offset,section_header_index->sh_size);
                                     for (int i=0; i<=section_header_index->sh_size; i++) {
                                         printf("%02x \n",(unsigned char)buffer[i]);
                                         //printf("%02x \n",(char)buffer[i]);
                                     }
                                 }
                                 free(buffer);
                             }
                         }
                     }

                 }while(0);
}
struct Elf64_Func_s {
    char *f_name;
    Elf64_Off f_offset;
    Elf64_Addr f_addr;
};
typedef struct Elf64_Func_s Elf64_Func;
void handle_functions (Elf64_Shdr * symtab_header,int n){
    
//    Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
    //拿到偏移
    Elf64_Sym* pSymMem=(Elf64_Sym*)((char*)start_addr+symtab_header->sh_offset);
    Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
     
    //sh 所有表偏移
     Elf64_Shdr *shdr_start_addr=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff);
    // link strtab
    Elf64_Shdr* strtab_header= (Elf64_Shdr *)((char*)shdr_start_addr+sizeof(Elf64_Shdr)*symtab_header->sh_link);
    //strtab addr
    char *strtab_start_addr=(char *)((char*)start_addr+strtab_header->sh_offset);
    
    
    
    long long size=symtab_header->sh_size/symtab_header->sh_entsize;
    long long i = 0;
   printf("functions \n");
   for(; i < size ; i++){
       if((pSymMem[i].st_info & 0x0F) == STT_FUNC){
           
//           Elf64_Off get_func_offset(ELF *bin, Elf64_Addr f_addr, Elf64_Sym *sym) {
//               Elf64_Shdr *shr = bin->shr[sym->st_shndx];
//               return shr->sh_offset + (f_addr - shr->sh_addr);
//           }
//
            printf("name:%-50s   addr:%-20x    offset:%-20x  opcode len:%-20x\n",strtab_start_addr+pSymMem[i].st_name,
                   pSymMem[i].st_value,
                   shdr_start_addr[pSymMem[i].st_shndx].sh_offset+(pSymMem[i].st_value-shdr_start_addr[pSymMem[i].st_shndx].sh_addr),
                   pSymMem[i].st_size);
       }
//       Elf64_Sym temp=pSymMem[i];
//       if(pSymMem[i].st_name>0)
//           printf("%s",(strtab_start_addr+pSymMem[i].st_name));
//
//       printf("\n");
   }
}
void enum_functions(){
    do{
       if(start_addr==NULL){
           break;
       }
        Elf64_Ehdr *Ehdr=(Elf64_Ehdr *)start_addr;
        
        Elf64_Shdr *section_header_index=NULL;
       
        //拿到节表字符串表头偏移
        Elf64_Shdr *shstr_table_header_addr=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff)+Ehdr->e_shstrndx;
        //拿到节表字符串表偏移
        char* shstr_table_addr=(char*)start_addr+shstr_table_header_addr->sh_offset;
        for (int i=0;i<Ehdr->e_shnum; i++) {
             
            section_header_index=(Elf64_Shdr *)((char*)start_addr+Ehdr->e_shoff+sizeof(Elf64_Shdr)*i);
            char p_name[]=".symtab";
            char p_name_buf[100];
            //const char * s_name=(const char *)shstr_table_addr[section_header_index->sh_name];
            if(i>2){
                sprintf(p_name_buf,"%-20s",&shstr_table_addr[section_header_index->sh_name]);
                //printf("%s\n", p_name_buf);
                if((strstr((const char *)p_name_buf,(const char *)p_name)!=NULL)&&(section_header_index->sh_type==SHT_SYMTAB)){
                    handle_functions((Elf64_Shdr *)section_header_index,i);
                }
            }
        }

    }while(0);
}
int fd=NULL;
//后面的字符串打印有写错需要自己修改
int main(int argc, const char * argv[]) {
    //dladdr
    //dlinfo
    long long flength =0;
    fd = open("/Volumes/haidragon-E/haidragon_study/study_executable_file_formats/ELF/page3/shelldemo/libdylib.so",S_IRWXU);
     //fd = open("/Volumes/haidragon-E/haidragon_study/study_executable_file_formats/ELF/ls",S_IRWXU);
    do{
        flength = lseek(fd, 1, SEEK_END);
        write(fd, "\0", 1);                                      /* 在文件最后添加一个空字符，以便下面printf正常工作 */
        lseek(fd, 0, SEEK_SET);
        start_addr = mmap(NULL, flength, PROT_READ,              //允许读
                          MAP_PRIVATE,                           //不允许其它进程访问此内存区域
                          fd, 0);
        print_file_header();
        print_program_header();
        print_section_header();
        print_dynamic();
        print_rela();
        print_rel();
        print_dynstr();
        print_symtab();
        print_text_opcode();
        enum_functions();
        
    }while (0);
    close(fd);
    munmap(start_addr, flength);
    return 0;
}


//
//Relocation section [10] '.rela.dyn' at offset 0x638 contains 10 entries:
//  Offset              Type            Value               Addend Name
//  0x0000000000003d78  <INVALID RELOC> 000000000000000000   +4608
//  0x0000000000003d80  <INVALID RELOC> 000000000000000000   +4544
//  0x0000000000004008  <INVALID RELOC> 000000000000000000  +16392
//  0x0000000000004010  <INVALID RELOC> 000000000000000000   +8200
//  0x0000000000003fd8  <INVALID RELOC> 000000000000000000      +0 _ITM_deregisterTMCloneTable
//  0x0000000000003fe0  <INVALID RELOC> 000000000000000000      +0 __libc_start_main
//  0x0000000000003fe8  <INVALID RELOC> 000000000000000000      +0 __gmon_start__
//  0x0000000000003ff0  <INVALID RELOC> 000000000000000000      +0 _ITM_registerTMCloneTable
//  0x0000000000003ff8  <INVALID RELOC> 000000000000000000      +0 __cxa_finalize
//  0x0000000000004020  <INVALID RELOC> 0x0000000000004020      +0 stderr
//
//Relocation section [11] '.rela.plt' for section [24] '.got' at offset 0x728 contains 7 entries:
//  Offset              Type            Value               Addend Name
//  0x0000000000003fa0  <INVALID RELOC> 000000000000000000      +0 puts
//  0x0000000000003fa8  <INVALID RELOC> 000000000000000000      +0 fprintf
//  0x0000000000003fb0  <INVALID RELOC> 000000000000000000      +0 dlopen
//  0x0000000000003fb8  <INVALID RELOC> 000000000000000000      +0 dlclose
//  0x0000000000003fc0  <INVALID RELOC> 000000000000000000      +0 exit
//  0x0000000000003fc8  <INVALID RELOC> 000000000000000000      +0 dlsym
//  0x0000000000003fd0  <INVALID RELOC> 000000000000000000      +0 dlerror


// libdl.so.2 _ITM_deregisterTMCloneTable __gmon_start__ _ITM_registerTMCloneTable dlclose dlsym dlopen dlerror libc.so.6 exit puts stderr fprintf __cxa_finalize __libc_start_main GLIBC_2.2.5      

//
//[0  ]      libdl.so.2
//[1  ]      _ITM_deregisterTMCloneTable
//[2  ]      __gmon_start__
//[3  ]      _ITM_registerTMCloneTable
//[4  ]      dlclose
//[5  ]      dlsym
//[6  ]      dlopen
//[7  ]      dlerror
//[8  ]      exit
//[9  ]      puts
//[10 ]      stderr
//[11 ]      fprintf
//[12 ]      __cxa_finalize
//[13 ]      __libc_start_main
//[14 ]      GLIBC_2.2.5
//[15 ]

 
//* --- 1. ELF 介绍.mp4
//* --- 2. ELF 打印文件头信息.mp4
//* --- 3. ELF 打印程序头信息.mp4
//* --- 4. ELF 打印节表头信息.mp4
//* --- 5. ELF 打印动态节信息(dynamic dynstr).mp4
//* --- 6. ELF 打印重定位表(rela).mp4
//* --- 7. ELF 打印重定位表(rel).mp4
//* --- 8. ELF 打印符号表(symtab).mp4
//* --- 9. ELF dump plt/got函数.mp4
//* --- 10. 获取内存中ELF模块.mp4
//* --- 11. 内存中ELF与实体文件区别(装载).mp4
//* --- 12. 打印内存中ELF信息.mp4
//* --- 13. 打印内存中的ELF代码段.mp4
//* --- 14. 劫持执行文件入口函数.mp4
//* --- 15. 无依赖shellcode编写.mp4
//* --- 16. ELF代码段抽取.mp4
//* --- 17. ELF代码运行前代码段还原.mp4
//* --- 18. ELF函数地址查找.mp4
//* --- 19. ELF单个函数抽取.mp4
//* --- 20. ELF单个函数运行前还原.mp4
//* --- 21. ELF单个函数运行后抽取.mp4
//* --- 22. UPX实现介绍.mp4
//* --- 23. ELF添加节实现.mp4
//* --- 24. opcode反汇编原理.mp4
//* --- 25. 虚拟指令(vmp)原理.mp4
//* --- 26. ELF函数虚拟执行实现.mp4
//* --- 27. ELF装载器实现(上).mp4
//* --- 28. ELF装载器实现(下).mp4
//* --- 29. so模块隐藏实现.mp4
// 




