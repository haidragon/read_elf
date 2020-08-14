# read_elf
字符串得自己理解代码修改
```
ELF 
DYN (Shared object file)
There are 11 program headers, starting at offset 0x40Program Headers:
  Type           Offset   VirtAddr           PhysAddr           FileSiz  MemSiz   Flg Align
  LOAD           0x000000 0x0000000000000000 0x0000000000000000 0x000d20 0x000d20 R   0x1000
  LOAD           0x001000 0x0000000000001000 0x0000000000001000 0x001ab5 0x001ab5 R E 0x1000
  LOAD           0x003000 0x0000000000003000 0x0000000000003000 0x000c2c 0x000c2c R   0x1000
  LOAD           0x003df8 0x0000000000004df8 0x0000000000004df8 0x000310 0x000328 RW  0x1000
  DYNAMIC        0x003e10 0x0000000000004e10 0x0000000000004e10 0x0001c0 0x0001c0 RW  0x8
  NOTE           0x0002a8 0x00000000000002a8 0x00000000000002a8 0x000020 0x000020 R   0x8
  NOTE           0x0002c8 0x00000000000002c8 0x00000000000002c8 0x000024 0x000024 R   0x4
  Unknown        0x0002a8 0x00000000000002a8 0x00000000000002a8 0x000020 0x000020 R   0x8
  GNU_EH_FRAME   0x0039cc 0x00000000000039cc 0x00000000000039cc 0x00007c 0x00007c R   0x4
  GNU_STACK      0x000000 0x0000000000000000 0x0000000000000000 0x000000 0x000000 RW  0x10
  GNU_RELRO      0x003df8 0x0000000000004df8 0x0000000000004df8 0x000208 0x000208 R   0x1
There are 31 section headers, starting at offset 0x4e18
Section Headers:
[Nr] Name                 Type         Addr             Off      Size     ES Flags Lk Inf Al
[ 0]                      NULL         0000000000000000 00000000 00000000  0        0   0  0
[ 1] .note.gnu.property   NOTE         00000000000002a8 000002a8 00000020  0 A      0   0  8
[ 2] .note.gnu.build-id   NOTE         00000000000002c8 000002c8 00000024  0 A      0   0  4
[ 3] .gnu.hash            Unknown      00000000000002f0 000002f0 00000060  0 A      4   0  8
[ 4] .dynsym              DYNSYM       0000000000000350 00000350 000003c0 24 A      5   1  8
[ 5] .dynstr              STRTAB       0000000000000710 00000710 000001d6  0 A      0   0  1
[ 6] .gnu.version         Unknown      00000000000008e6 000008e6 00000050  2 A      4   0  2
[ 7] .gnu.version_r       Unknown      0000000000000938 00000938 00000040  0 A      5   1  8
[ 8] .rela.dyn            RELA         0000000000000978 00000978 000000f0 24 A      4   0  8
[ 9] .rela.plt            RELA         0000000000000a68 00000a68 000002b8 24 AI     4  24  8
[10] .init                PROGBITS     0000000000001000 00001000 0000001b  0 AX     0   0  4
[11] .plt                 PROGBITS     0000000000001020 00001020 000001e0 16 AX     0   0 16
[12] .plt.got             PROGBITS     0000000000001200 00001200 00000010 16 AX     0   0 16
[13] .plt.sec             PROGBITS     0000000000001210 00001210 000001d0 16 AX     0   0 16
[14] .text                PROGBITS     00000000000013e0 000013e0 000016b7  0 AX     0   0 16
[15] .mytext              PROGBITS     0000000000002a97 00002a97 00000011  0 AX     0   0  1
[16] .fini                PROGBITS     0000000000002aa8 00002aa8 0000000d  0 AX     0   0  4
[17] .rodata              PROGBITS     0000000000003000 00003000 000009ca  0 A      0   0  8
[18] .eh_frame_hdr        PROGBITS     00000000000039cc 000039cc 0000007c  0 A      0   0  4
[19] .eh_frame            PROGBITS     0000000000003a48 00003a48 000001e4  0 A      0   0  8
[20] .init_array          Unknown      0000000000004df8 00003df8 00000010  8 WA     0   0  8
[21] .fini_array          Unknown      0000000000004e08 00003e08 00000008  8 WA     0   0  8
[22] .dynamic             DYNAMIC      0000000000004e10 00003e10 000001c0 16 WA     5   0  8
[23] .got                 PROGBITS     0000000000004fd0 00003fd0 00000030  8 WA     0   0  8
[24] .got.plt             PROGBITS     0000000000005000 00004000 00000100  8 WA     0   0  8
[25] .data                PROGBITS     0000000000005100 00004100 00000008  0 WA     0   0  8
[26] .bss                 NOBITS       0000000000005108 00004108 00000018  0 WA     0   0  8
[27] .comment             PROGBITS     0000000000000000 00004108 00000024  1 MS     0   0  1
[28] .symtab              SYMTAB       0000000000000000 00004130 00000810 24       29  47  8
[29] .strtab              STRTAB       0000000000000000 00004940 000003bd  0        0   0  1
[30] .shstrtab            STRTAB       0000000000000000 00004cfd 00000115  0        0   0  1
Dynamic section:
Dynamic segment contains 28 entries:
Addr: 0000000000000710   Offset: 00000710 Link to section: [ 5] section name: .dynstr             
Tag        Type                                                             Name/Value
0x00000001 String table offset of a needed shared library                   [ libc.so.6 ]
0x0000000c Address of initialization function                               0x00001000 
0x0000000d Address of finalization function                                 0x00002aa8 
0x00000019 Address of the array of pointers to initialization functions     0x00004df8 
0x0000001b Size in bytes of the array of initialization functions           16 (bytes) 
0x0000001a Address of the array of pointers to termination functions        0x00004e08 
0x0000001c Size in bytes of the array of termination functions              8 (bytes) 
0x6ffffef5 GNU-style hash table                                             0x000002f0 
0x00000005 Address of string table                                          0x00000710 
0x00000006 Address of symbol table                                          0x00000350 
0x0000000a Size of string table                                             470 (bytes) 
0x0000000b Size of each symbol table entry                                  24 (bytes) 
0x00000003 Processor-dependent address                                      0x00005000 
0x00000002 Total size in bytes of PLT relocations                           696 (bytes) 
0x00000014 Type of relocation used for PLT                                  REL 0x07 
0x00000017 Address of PLT relocations                                       0x00000a68 
0x00000007 Address of ElfNN_Rela relocations                                0x00000978 
0x00000008 Total size of ElfNN_Rela relocations                             240 (bytes) 
0x00000009 Size of each ElfNN_Rela relocation entry                         24 (bytes) 
0x6ffffffe Address of verneed section                                       0x00000938 
0x6fffffff Number of elems in verneed section                               1 
0x6ffffff0 Address of versym section                                        0x000008e6 
0x6ffffff9 number of RELATIVE relocations                                   3 
0x00000000 Terminating entry                                                0x0 
Relocation section '.rela.dyn' at offset 0x00000978 contains 8 entries:
Offset     Info     Type               Sym.Value  Sym.Name                                 index
0x00004df8 00000008      R_X86_64_RELATIVE  0000000b   __gmon_start__                           0
0x00004e08 00000008      R_X86_64_RELATIVE  0000000b   __gmon_start__                           0
0x00005100 00000008      R_X86_64_RELATIVE  0000000b   __gmon_start__                           0
0x00004e00 00000001      R_X86_64_64      00000000   fgets                                    33
0x00004fd0 00000006      R_X86_64_GLOB_DAT  00000000   __cxa_finalize                           3
0x00004fd8 00000006      R_X86_64_GLOB_DAT  00000001   strtoul                                  32
0x00004fe0 00000006      R_X86_64_GLOB_DAT  00000001   getLibAddr                               28
0x00004fe8 00000006      R_X86_64_GLOB_DAT  00000004   strstr                                   16
0x00004ff0 00000006      R_X86_64_GLOB_DAT  00000001   lseek                                    24
0x00004ff8 00000006      R_X86_64_GLOB_DAT  00000000   write                                    25
Relocation section '.rela.plt' at offset 0x00000a68 contains 9 entries:
Offset     Info     Type               Sym.Value  Sym.Name                                 index
0x00005018 00000007      R_X86_64_JUMP_SLOT  00000000   GLIBC_2.14                               37
0x00005020 00000007      R_X86_64_JUMP_SLOT  00000000   _ITM_deregisterTMCloneTable              1
0x00005028 00000007      R_X86_64_JUMP_SLOT  00000000   _ITM_registerTMCloneTable                2
0x00005030 00000007      R_X86_64_JUMP_SLOT  00000003   mytext_shift                             4
0x00005038 00000007      R_X86_64_JUMP_SLOT  00000000   start_addr                               5
0x00005040 00000007      R_X86_64_JUMP_SLOT  00000000   pheader_segment_type_name                6
0x00005048 00000007      R_X86_64_JUMP_SLOT  00000000   print_program_header                     7
0x00005050 00000007      R_X86_64_JUMP_SLOT  00000000   strtok                                   31
0x00005058 00000007      R_X86_64_JUMP_SLOT  6fffffff   puts                                     8
0x00005060 00000007      R_X86_64_JUMP_SLOT  00000000   section_type_name                        9
0x00005068 00000007      R_X86_64_JUMP_SLOT  00000000   print_section_header                     10
0x00005070 00000007      R_X86_64_JUMP_SLOT  00000000   __stack_chk_fail                         11
0x00005078 00000007      R_X86_64_JUMP_SLOT  6ffffffe   show_header                              12
0x00005080 00000007      R_X86_64_JUMP_SLOT  00000000   putchar                                  13
0x00005088 00000007      R_X86_64_JUMP_SLOT  00000000   init_getString                           27
0x00005090 00000007      R_X86_64_JUMP_SLOT  00000000   handle_text_opcode                       14
0x00005098 00000007      R_X86_64_JUMP_SLOT  00000000   GLIBC_2.4                                38
0x000050a0 00000007      R_X86_64_JUMP_SLOT  00000000   sprintf                                  15
0x000050a8 00000007      R_X86_64_JUMP_SLOT  00000000   malloc                                   17
0x000050b0 00000007      R_X86_64_JUMP_SLOT  00000000   memcpy                                   18
0x000050b8 00000007      R_X86_64_JUMP_SLOT  00000000   memset                                   19
0x000050c0 00000007      R_X86_64_JUMP_SLOT  00000000   getpid                                   29
0x000050c8 00000007      R_X86_64_JUMP_SLOT  00000004   mprotect                                 20
0x000050d0 00000007      R_X86_64_JUMP_SLOT  00000000   free                                     21
0x000050d8 00000007      R_X86_64_JUMP_SLOT  00000000   print_text_opcode                        22
0x000050e0 00000007      R_X86_64_JUMP_SLOT  00000000   syscall                                  23
0x000050e8 00000007      R_X86_64_JUMP_SLOT  00000000   get_String                               35
0x000050f0 00000007      R_X86_64_JUMP_SLOT  00000000   fopen                                    30
0x000050f8 00000007      R_X86_64_JUMP_SLOT  00000000   mmap                                     26
.dynstr    name
[0  ]      __gmon_start__  
[1  ]      _ITM_deregisterTMCloneTable  
[2  ]      _ITM_registerTMCloneTable  
[3  ]      __cxa_finalize  
[4  ]      mytext_shift  
[5  ]      start_addr  
[6  ]      pheader_segment_type_name  
[7  ]      print_program_header  
[8  ]      puts        
[9  ]      section_type_name  
[10 ]      print_section_header  
[11 ]      __stack_chk_fail  
[12 ]      show_header  
[13 ]      putchar     
[14 ]      handle_text_opcode  
[15 ]      sprintf     
[16 ]      strstr      
[17 ]      malloc      
[18 ]      memcpy      
[19 ]      memset      
[20 ]      mprotect    
[21 ]      free        
[22 ]      print_text_opcode  
[23 ]      syscall     
[24 ]      lseek       
[25 ]      write       
[26 ]      mmap        
[27 ]      init_getString  
[28 ]      getLibAddr  
[29 ]      getpid      
[30 ]      fopen       
[31 ]      strtok      
[32 ]      strtoul     
[33 ]      fgets       
[34 ]      fclose      
[35 ]      get_String  
[36 ]      libc.so.6   
[37 ]      GLIBC_2.14  
[38 ]      GLIBC_2.4   
[39 ]      GLIBC_2.2.5  
[40 ]                  
Symbol table :
Symbol table '.symtab' contains 86 entries:
Num:  Value    Size   Type                          Bind                                 Vis       Ndx       Name
  0:  00000000 0      Unspecified type              Local symbol                         DEFAULT   UNDEF     
  1:  000002a8 0      Section                       Local symbol                         DEFAULT   1         
  2:  000002c8 0      Section                       Local symbol                         DEFAULT   2         
  3:  000002f0 0      Section                       Local symbol                         DEFAULT   3         
  4:  00000350 0      Section                       Local symbol                         DEFAULT   4         
  5:  00000710 0      Section                       Local symbol                         DEFAULT   5         
  6:  000008e6 0      Section                       Local symbol                         DEFAULT   6         
  7:  00000938 0      Section                       Local symbol                         DEFAULT   7         
  8:  00000978 0      Section                       Local symbol                         DEFAULT   8         
  9:  00000a68 0      Section                       Local symbol                         DEFAULT   9         
 10:  00001000 0      Section                       Local symbol                         DEFAULT   10        
 11:  00001020 0      Section                       Local symbol                         DEFAULT   11        
 12:  00001200 0      Section                       Local symbol                         DEFAULT   12        
 13:  00001210 0      Section                       Local symbol                         DEFAULT   13        
 14:  000013e0 0      Section                       Local symbol                         DEFAULT   14        
 15:  00002a97 0      Section                       Local symbol                         DEFAULT   15        
 16:  00002aa8 0      Section                       Local symbol                         DEFAULT   16        
 17:  00003000 0      Section                       Local symbol                         DEFAULT   17        
 18:  000039cc 0      Section                       Local symbol                         DEFAULT   18        
 19:  00003a48 0      Section                       Local symbol                         DEFAULT   19        
 20:  00004df8 0      Section                       Local symbol                         DEFAULT   20        
 21:  00004e08 0      Section                       Local symbol                         DEFAULT   21        
 22:  00004e10 0      Section                       Local symbol                         DEFAULT   22        
 23:  00004fd0 0      Section                       Local symbol                         DEFAULT   23        
 24:  00005000 0      Section                       Local symbol                         DEFAULT   24        
 25:  00005100 0      Section                       Local symbol                         DEFAULT   25        
 26:  00005108 0      Section                       Local symbol                         DEFAULT   26        
 27:  00000000 0      Section                       Local symbol                         DEFAULT   27        
 28:  00000000 0      Source file                   Local symbol                         DEFAULT   ABS       crtstuff.c
 29:  000013e0 0      Function                      Local symbol                         DEFAULT   14        deregister_tm_clones
 30:  00001410 0      Function                      Local symbol                         DEFAULT   14        register_tm_clones
 31:  00001450 0      Function                      Local symbol                         DEFAULT   14        __do_global_dtors_aux
 32:  00005108 1      Data object                   Local symbol                         DEFAULT   26        completed.8059
 33:  00004e08 0      Data object                   Local symbol                         DEFAULT   21        __do_global_dtors_aux_fini_array_entry
 34:  00001490 0      Function                      Local symbol                         DEFAULT   14        frame_dummy
 35:  00004df8 0      Data object                   Local symbol                         DEFAULT   20        __frame_dummy_init_array_entry
 36:  00000000 0      Source file                   Local symbol                         DEFAULT   ABS       dylib.c
 37:  00000000 0      Source file                   Local symbol                         DEFAULT   ABS       crtstuff.c
 38:  00003c28 0      Data object                   Local symbol                         DEFAULT   19        __FRAME_END__
 39:  00000000 0      Source file                   Local symbol                         DEFAULT   ABS       
 40:  00002aa8 0      Function                      Local symbol                         DEFAULT   16        _fini
 41:  00005100 0      Data object                   Local symbol                         DEFAULT   25        __dso_handle
 42:  00004e10 0      Data object                   Local symbol                         DEFAULT   22        _DYNAMIC
 43:  000039cc 0      Unspecified type              Local symbol                         DEFAULT   18        __GNU_EH_FRAME_HDR
 44:  00005108 0      Data object                   Local symbol                         DEFAULT   25        __TMC_END__
 45:  00005000 0      Data object                   Local symbol                         DEFAULT   24        _GLOBAL_OFFSET_TABLE_
 46:  00001000 0      Function                      Local symbol                         DEFAULT   10        _init
 47:  00002a97 17     Function                      Global symbol                        DEFAULT   15        getString
 48:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     free@@GLIBC_2.2.5
 49:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     putchar@@GLIBC_2.2.5
 50:  00000000 0      Unspecified type              like global - lower precedence       DEFAULT   UNDEF     _ITM_deregisterTMCloneTable
 51:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     puts@@GLIBC_2.2.5
 52:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     write@@GLIBC_2.2.5
 53:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     getpid@@GLIBC_2.2.5
 54:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     fclose@@GLIBC_2.2.5
 55:  000015ff 522    Function                      Global symbol                        DEFAULT   14        print_program_header
 56:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     __stack_chk_fail@@GLIBC_2.4
 57:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     mmap@@GLIBC_2.2.5
 58:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     printf@@GLIBC_2.2.5
 59:  00005110 8      Data object                   Global symbol                        DEFAULT   26        mytext_shift
 60:  00002893 127    Function                      Global symbol                        DEFAULT   14        init_getString
 61:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     lseek@@GLIBC_2.2.5
 62:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     memset@@GLIBC_2.2.5
 63:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     close@@GLIBC_2.2.5
 64:  00001d47 1455   Function                      Global symbol                        DEFAULT   14        show_header
 65:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     fgets@@GLIBC_2.2.5
 66:  00005118 8      Data object                   Global symbol                        DEFAULT   26        start_addr
 67:  000022f6 1186   Function                      Global symbol                        DEFAULT   14        handle_text_opcode
 68:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     syscall@@GLIBC_2.2.5
 69:  00000000 0      Unspecified type              like global - lower precedence       DEFAULT   UNDEF     __gmon_start__
 70:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     memcpy@@GLIBC_2.14
 71:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     malloc@@GLIBC_2.2.5
 72:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     mprotect@@GLIBC_2.2.5
 73:  00001499 358    Function                      Global symbol                        DEFAULT   14        pheader_segment_type_name
 74:  00001997 944    Function                      Global symbol                        DEFAULT   14        print_section_header
 75:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     fopen@@GLIBC_2.2.5
 76:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     strtok@@GLIBC_2.2.5
 77:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     strtoul@@GLIBC_2.2.5
 78:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     sprintf@@GLIBC_2.2.5
 79:  00002912 369    Function                      Global symbol                        DEFAULT   14        getLibAddr
 80:  00000000 0      Unspecified type              like global - lower precedence       DEFAULT   UNDEF     _ITM_registerTMCloneTable
 81:  00001809 398    Function                      Global symbol                        DEFAULT   14        section_type_name
 82:  00002a83 20     Function                      Global symbol                        DEFAULT   14        get_String
 83:  00002798 251    Function                      Global symbol                        DEFAULT   14        print_text_opcode
 84:  00000000 0      Function                      like global - lower precedence       DEFAULT   UNDEF     __cxa_finalize@@GLIBC_2.2.5
 85:  00000000 0      Function                      Global symbol                        DEFAULT   UNDEF     strstr@@GLIBC_2.2.5
f3 
0f 
1e 
fa 
55 
48 
89 
e5 
48 
8d 
05 
5a 
05 
00 
00 
5d 
c3 
00 
functions 
name:deregister_tm_clones                                 addr:13e0                    offset:13e0                  opcode len:0                   
name:register_tm_clones                                   addr:1410                    offset:1410                  opcode len:0                   
name:__do_global_dtors_aux                                addr:1450                    offset:1450                  opcode len:0                   
name:frame_dummy                                          addr:1490                    offset:1490                  opcode len:0                   
name:_fini                                                addr:2aa8                    offset:2aa8                  opcode len:0                   
name:_init                                                addr:1000                    offset:1000                  opcode len:0                   
name:getString                                            addr:2a97                    offset:2a97                  opcode len:11                  
name:free@@GLIBC_2.2.5                                    addr:0                       offset:0                     opcode len:0                   
name:putchar@@GLIBC_2.2.5                                 addr:0                       offset:0                     opcode len:0                   
name:puts@@GLIBC_2.2.5                                    addr:0                       offset:0                     opcode len:0                   
name:write@@GLIBC_2.2.5                                   addr:0                       offset:0                     opcode len:0                   
name:getpid@@GLIBC_2.2.5                                  addr:0                       offset:0                     opcode len:0                   
name:fclose@@GLIBC_2.2.5                                  addr:0                       offset:0                     opcode len:0                   
name:print_program_header                                 addr:15ff                    offset:15ff                  opcode len:20a                 
name:__stack_chk_fail@@GLIBC_2.4                          addr:0                       offset:0                     opcode len:0                   
name:mmap@@GLIBC_2.2.5                                    addr:0                       offset:0                     opcode len:0                   
name:printf@@GLIBC_2.2.5                                  addr:0                       offset:0                     opcode len:0                   
name:init_getString                                       addr:2893                    offset:2893                  opcode len:7f                  
name:lseek@@GLIBC_2.2.5                                   addr:0                       offset:0                     opcode len:0                   
name:memset@@GLIBC_2.2.5                                  addr:0                       offset:0                     opcode len:0                   
name:close@@GLIBC_2.2.5                                   addr:0                       offset:0                     opcode len:0                   
name:show_header                                          addr:1d47                    offset:1d47                  opcode len:5af                 
name:fgets@@GLIBC_2.2.5                                   addr:0                       offset:0                     opcode len:0                   
name:handle_text_opcode                                   addr:22f6                    offset:22f6                  opcode len:4a2                 
name:syscall@@GLIBC_2.2.5                                 addr:0                       offset:0                     opcode len:0                   
name:memcpy@@GLIBC_2.14                                   addr:0                       offset:0                     opcode len:0                   
name:malloc@@GLIBC_2.2.5                                  addr:0                       offset:0                     opcode len:0                   
name:mprotect@@GLIBC_2.2.5                                addr:0                       offset:0                     opcode len:0                   
name:pheader_segment_type_name                            addr:1499                    offset:1499                  opcode len:166                 
name:print_section_header                                 addr:1997                    offset:1997                  opcode len:3b0                 
name:fopen@@GLIBC_2.2.5                                   addr:0                       offset:0                     opcode len:0                   
name:strtok@@GLIBC_2.2.5                                  addr:0                       offset:0                     opcode len:0                   
name:strtoul@@GLIBC_2.2.5                                 addr:0                       offset:0                     opcode len:0                   
name:sprintf@@GLIBC_2.2.5                                 addr:0                       offset:0                     opcode len:0                   
name:getLibAddr                                           addr:2912                    offset:2912                  opcode len:171                 
name:section_type_name                                    addr:1809                    offset:1809                  opcode len:18e                 
name:get_String                                           addr:2a83                    offset:2a83                  opcode len:14                  
name:print_text_opcode                                    addr:2798                    offset:2798                  opcode len:fb                  
name:__cxa_finalize@@GLIBC_2.2.5                          addr:0                       offset:0                     opcode len:0                   
name:strstr@@GLIBC_2.2.5                                  addr:0                       offset:0                     opcode len:0                   
Program ended with exit code: 0
```
