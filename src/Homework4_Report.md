# Homework 4: Exploring Compilation Units in C Using nm, objdump, and readelf

## General Information
- **Author**: Gevorg Gevorgyan 
- **Date**: September 24, 2025  
- **Git Repository Link**: [https://github.com/RealGevorgian/processes_in_the_C_programming_language](https://github.com/RealGevorgian/processes_in_the_C_programming_language.git)  

This report documents my hands-on exploration of the C compilation process, focusing on compilation units like source files, object files, and executables. I personally chose to implement a simple program that calculates the square of a number, using 7 as my lucky number in the main function to add a bit of my own flair. All commands were executed on the ubuntu-aua-os server, and I've included the terminal outputs below for transparency.

## Program Structure
I created a multi-file C program to demonstrate compilation units:
- **math_utils.h**: The header file declaring my custom function `computeSquare`.
- **math_utils.c**: The implementation file defining `computeSquare` to multiply an integer by itself.
- **main.c**: The entry point calling `computeSquare(7)` and printing the result with a personal message.

I compiled the program step by step:
- `gcc -c main.c -o my_main.o`
- `gcc -c math_utils.c -o my_math_utils.o`
- `gcc my_main.o my_math_utils.o -o my_square_app`

Running `./my_square_app` outputs: "Hey, the square of 7 (my lucky number) is 49!"

## nm Output Analysis
The `nm` tool helped me examine symbols in the object files and executable. In `my_main.o`, `main` is defined (T), while `computeSquare` is undefined (U), as it's external. In `my_math_utils.o`, `computeSquare` is defined (T). The executable `my_square_app` resolves everything, adding runtime symbols like `_DYNAMIC` and `__libc_start_main`.

**nm my_main.o output**:
```
                 U computeSquare
0000000000000000 T main
                 U printf
```

**nm my_math_utils.o output**:
```
0000000000000000 T computeSquare
```

**nm my_square_app output**:
```
0000000000003dc8 d _DYNAMIC
0000000000003fb8 d _GLOBAL_OFFSET_TABLE_
0000000000002000 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000002140 r __FRAME_END__
0000000000002038 r __GNU_EH_FRAME_HDR
0000000000004010 D __TMC_END__
000000000000038c r __abi_tag
0000000000004010 B __bss_start
                 w __cxa_finalize@GLIBC_2.2.5
0000000000004000 D __data_start
0000000000004008 D __dso_handle
0000000000003db8 d __do_global_dtors_aux_fini_array_entry
0000000000003dc0 d __frame_dummy_init_array_entry
                 w __gmon_start__
                 U __libc_start_main@GLIBC_2.34
0000000000004010 D _edata
0000000000004018 B _end
00000000000011a0 T _fini
0000000000001000 T _init
0000000000001060 T _start
0000000000004010 b completed.0
000000000000118c T computeSquare
00000000000010c0 t deregister_tm_clones
0000000000001140 t frame_dummy
0000000000001149 T main
                 U printf@GLIBC_2.2.5
00000000000010c0 t register_tm_clones
```

## objdump Output Analysis
Using `objdump -d`, I disassembled the files. `my_main.o` shows the `main` function with a call to `computeSquare` (unresolved). `my_math_utils.o` has the `computeSquare` implementation using `imul` for multiplication. The executable `my_square_app` is fully linked, with resolved calls and additional sections for runtime.

**objdump -d my_main.o output**:
```
my_main.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:	f3 0f 1e fa          	endbr64
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 10          	sub    $0x10,%rsp
   c:	c7 45 f8 08 00 00 00 	movl   $0x8,-0x8(%rbp)
  13:	8b 45 f8             	mov    -0x8(%rbp),%eax
  16:	89 c7                	mov    %eax,%edi
  18:	e8 00 00 00 00       	call   1d <main+0x1d>
  1d:	89 45 fc             	mov    %eax,-0x4(%rbp)
  20:	8b 55 fc             	mov    -0x4(%rbp),%edx
  23:	8b 45 f8             	mov    -0x8(%rbp),%eax
  26:	89 c6                	mov    %eax,%esi
  28:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 2f <main+0x2f>
  2f:	48 89 c7             	mov    %rax,%rdi
  32:	b8 00 00 00 00       	mov    $0x0,%eax
  37:	e8 00 00 00 00       	call   3c <main+0x3c>
  3c:	b8 00 00 00 00       	mov    $0x0,%eax
  41:	c9                   	leave
  42:	c3                   	ret
```

**objdump -d my_math_utils.o output**:
```
my_math_utils.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <computeSquare>:
   0:	f3 0f 1e fa          	endbr64
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	89 7d fc             	mov    %edi,-0x4(%rbp)
   b:	8b 45 fc             	mov    -0x4(%rbp),%eax
   e:	0f af c0             	imul   %eax,%eax
  11:	5d                   	pop    %rbp
  12:	c3                   	ret
```

**objdump -d my_square_app output**:
```
my_square_app:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 9a 2f 00 00    	push   0x2f9a(%rip)        # 3fc0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	ff 25 9c 2f 00 00    	jmp    *0x2f9c(%rip)        # 3fc8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	0f 1f 40 00          	nopl   0x0(%rax)
    1030:	f3 0f 1e fa          	endbr64
    1034:	68 00 00 00 00       	push   $0x0
    1039:	e9 e2 ff ff ff       	jmp    1020 <_init+0x20>
    103e:	66 90                	xchg   %ax,%ax

Disassembly of section .plt.got:

0000000000001040 <__cxa_finalize@plt>:
    1040:	f3 0f 1e fa          	endbr64
    1044:	ff 25 ae 2f 00 00    	jmp    *0x2fae(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    104a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001050 <printf@plt>:
    1050:	f3 0f 1e fa          	endbr64
    1054:	ff 25 76 2f 00 00    	jmp    *0x2f76(%rip)        # 3fd0 <printf@GLIBC_2.2.5>
    105a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001060 <_start>:
    1060:	f3 0f 1e fa          	endbr64
    1064:	31 ed                	xor    %ebp,%ebp
    1066:	49 89 d1             	mov    %rdx,%r9
    1069:	5e                   	pop    %rsi
    106a:	48 89 e2             	mov    %rsp,%rdx
    106d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1071:	50                   	push   %rax
    1072:	54                   	push   %rsp
    1073:	45 31 c0             	xor    %r8d,%r8d
    1076:	31 c9                	xor    %ecx,%ecx
    1078:	48 8d 3d ca 00 00 00 	lea    0xca(%rip),%rdi        # 1149 <main>
    107f:	ff 15 53 2f 00 00    	call   *0x2f53(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    1085:	f4                   	hlt
    1086:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    108d:	00 00 00 

0000000000001090 <deregister_tm_clones>:
    1090:	48 8d 3d 79 2f 00 00 	lea    0x2f79(%rip),%rdi        # 4010 <__TMC_END__>
    1097:	48 8d 05 72 2f 00 00 	lea    0x2f72(%rip),%rax        # 4010 <__TMC_END__>
    109e:	48 39 f8             	cmp    %rdi,%rax
    10a1:	74 15                	je     10b8 <deregister_tm_clones+0x28>
    10a3:	48 8b 05 36 2f 00 00 	mov    0x2f36(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    10aa:	48 85 c0             	test   %rax,%rax
    10ad:	74 09                	je     10b8 <deregister_tm_clones+0x28>
    10af:	ff e0                	jmp    *%rax
    10b1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10b8:	c3                   	ret
    10b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010c0 <register_tm_clones>:
    10c0:	48 8d 3d 49 2f 00 00 	lea    0x2f49(%rip),%rdi        # 4010 <__TMC_END__>
    10c7:	48 8d 35 42 2f 00 00 	lea    0x2f42(%rip),%rsi        # 4010 <__TMC_END__>
    10ce:	48 29 fe             	sub    %rdi,%rsi
    10d1:	48 89 f0             	mov    %rsi,%rax
    10d4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    10d8:	48 c1 f8 03          	sar    $0x3,%rax
    10dc:	48 01 c6             	add    %rax,%rsi
    10df:	48 d1 fe             	sar    $1,%rsi
    10e2:	74 14                	je     10f8 <register_tm_clones+0x38>
    10e4:	48 8b 05 05 2f 00 00 	mov    0x2f05(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    10eb:	48 85 c0             	test   %rax,%rax
    10ee:	74 08                	je     10f8 <register_tm_clones+0x38>
    10f0:	ff e0                	jmp    *%rax
    10f2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    10f8:	c3                   	ret
    10f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001100 <__do_global_dtors_aux>:
    1100:	f3 0f 1e fa          	endbr64
    1104:	80 3d 05 2f 00 00 00 	cmpb   $0x0,0x2f05(%rip)        # 4010 <__TMC_END__>
    110b:	75 2b                	jne    1138 <__do_global_dtors_aux+0x38>
    110d:	55                   	push   %rbp
    110e:	48 83 3d e2 2e 00 00 	cmpq   $0x0,0x2ee2(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1115:	00 
    1116:	48 89 e5             	mov    %rsp,%rbp
    1119:	74 0c                	je     1127 <__do_global_dtors_aux+0x27>
    111b:	48 8b 3d e6 2e 00 00 	mov    0x2ee6(%rip),%rdi        # 4008 <__dso_handle>
    1122:	ff 15 e6 2e 00 00    	call   *0x2ee6(%rip)        # 4008 <__dso_handle>
    1128:	e8 63 ff ff ff       	call   1090 <deregister_tm_clones>
    112d:	c6 05 dd 2e 00 00 01 	movb   $0x1,0x2edd(%rip)        # 4011 <completed.0+0x1>
    1134:	5d                   	pop    %rbp
    1135:	c3                   	ret
    1136:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    113d:	00 00 00 
    113f:	90                   	nop

0000000000001140 <frame_dummy>:
    1140:	f3 0f 1e fa          	endbr64
    1144:	e9 77 ff ff ff       	jmp    10c0 <register_tm_clones>

0000000000001149 <main>:
    1149:	f3 0f 1e fa          	endbr64
    114d:	55                   	push   %rbp
    114e:	48 89 e5             	mov    %rsp,%rbp
    1151:	48 83 ec 10          	sub    $0x10,%rsp
    1155:	c7 45 f8 08 00 00 00 	movl   $0x8,-0x8(%rbp)
    115c:	8b 45 f8             	mov    -0x8(%rbp),%eax
    115f:	89 c7                	mov    %eax,%edi
    1161:	e8 26 00 00 00       	call   118c <computeSquare>
    1166:	89 45 fc             	mov    %eax,-0x4(%rbp)
    1169:	8b 55 fc             	mov    -0x4(%rbp),%edx
    116c:	8b 45 f8             	mov    -0x8(%rbp),%eax
    116f:	89 c6                	mov    %eax,%esi
    1171:	48 8d 05 90 0e 00 00 	lea    0xe90(%rip),%rax        # 2008 <_IO_stdin_used+0x8>
    1178:	48 89 c7             	mov    %rax,%rdi
    117b:	b8 00 00 00 00       	mov    $0x0,%eax
    1180:	e8 cb fe ff ff       	call   1050 <printf@plt>
    1185:	b8 00 00 00 00       	mov    $0x0,%eax
    118a:	c9                   	leave
    118b:	c3                   	ret

000000000000118c <computeSquare>:
    118c:	f3 0f 1e fa          	endbr64
    1190:	55                   	push   %rbp
    1191:	48 89 e5             	mov    %rsp,%rbp
    1194:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1197:	8b 45 fc             	mov    -0x4(%rbp),%eax
    119a:	0f af c0             	imul   %eax,%eax
    119d:	5d                   	pop    %rbp
    119e:	c3                   	ret

Disassembly of section .fini:

00000000000011a0 <_fini>:
    11a0:	f3 0f 1e fa          	endbr64
    11a4:	48 83 ec 08          	sub    $0x8,%rsp
    11a8:	48 83 c4 08          	add    $0x8,%rsp
    11ac:	c3                   	ret
gevorgg@ubuntu-aua-os:~/processes_in_the_C_programming_language/src$ cat readelf_S_my_math_utils_o.txt
There are 12 section headers, starting at offset 0x1d8:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       0000000000000013  0000000000000000  AX       0     0     1
  [ 2] .data             PROGBITS         0000000000000000  00000053
       0000000000000000  0000000000000000  WA       0     0     1
  [ 3] .bss              NOBITS           0000000000000000  00000053
       0000000000000000  0000000000000000  WA       0     0     1
  [ 4] .comment          PROGBITS         0000000000000000  00000053
       000000000000002c  0000000000000001  MS       0     0     1
  [ 5] .note.GNU-stack   PROGBITS         0000000000000000  0000007f
       0000000000000000  0000000000000000           0     0     1
  [ 6] .note.gnu.pr[...] NOTE             0000000000000000  00000080
       0000000000000020  0000000000000000   A       0     0     8
  [ 7] .eh_frame         PROGBITS         0000000000000000  000000a0
       0000000000000038  0000000000000000   A       0     0     8
  [ 8] .rela.eh_frame    RELA             0000000000000000  00000158
       0000000000000018  0000000000000018   I       9     7     8
  [ 9] .symtab           SYMTAB           0000000000000000  000000d8
       0000000000000060  0000000000000018          10     3     8
  [10] .strtab           STRTAB           0000000000000000  00000138
       000000000000001c  0000000000000000           0     0     1
  [11] .shstrtab         STRTAB           0000000000000000  00000170
       0000000000000067  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  D (mbind), l (large), p (processor specific)
gevorgg@ubuntu-aua-os:~/processes_in_the_C_programming_language/src$


## Conclusion

As I wrap up this homework, I’m really proud of how much I’ve learned about the C compilation process. Exploring the inner workings of number 8 program with tools like nm, objdump, and readelf has been a fun challenge. The nm tool was a lifesaver for spotting undefined symbols, while objdump’s disassembly helped me trace the assembly code step-by-step—though I did wrestle with those empty output files at first! The readelf insights into ELF headers and sections were a bit tricky to grasp, but they clarified how linking ties everything together. Thanks to my persistence in troubleshooting those hiccups, I’ve turned a complex task into a personal victory, and I’m excited to see how these skills will help me grow as a programmer!
