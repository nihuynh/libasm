# libasm
- [libasm](#libasm)
  - [Setup](#setup)
    - [Install](#install)
    - [Formatting](#formatting)
    - [Using debugger](#using-debugger)
    - [Patch mac to linux](#patch-mac-to-linux)
    - [Testers](#testers)
  - [Ressources](#ressources)
    - [Assembly Calling conventions](#assembly-calling-conventions)
    - [Links](#links)
      - [Lessons:](#lessons)
      - [Documentations:](#documentations)
      - [Great readme from other students:](#great-readme-from-other-students)
      - [More about asm:](#more-about-asm)
      - [SSE:](#sse)
      - [GDB on MACarm:](#gdb-on-macarm)
      - [time cpu op:](#time-cpu-op)
      - [Unit testing:](#unit-testing)
      - [Static analysis:](#static-analysis)

## Setup

### Install
```bash
# Linux:
sudo apt update && sudo apt install -y build-essential gdb clang nasm
# Mac:
brew install nasm
# Install brew if needed
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

### Formatting
```shell
    # Generate basic uncrust config
    uncrustify --update-config-with-doc -o uncrust.conf
    # apply
    make format
```

### Using debugger
```shell
make test && ./obj/main.out
./obj/test_gbrunet.out
# Debug
lldb  ./obj/main.out
```

### Patch mac to linux 
```bash
# Generate the patch:
git diff > linux.patch
# Apply the diff:
git apply linux.patch
# Update the patch:
git diff HEAD > linux2.patch && mv linux2.patch linux.patch
```

### Testers
```bash
make run_test
```
[Thanks cacharle, for the awesome tests](https://github.com/cacharle/libasm_test)   
[Thanks vitoriagalli, for the awesome tests](https://github.com/vitoriagalli/42libasm_tester)   
[Thanks Tripouille, for the awesome tests](https://github.com/Tripouille/libasmTester)   
```bash
make -C libasm_test bonus
make -C libasmTester va
cd 42libasm_tester/
bash runtest.sh && bash runtest.sh bonus
bash runtest.sh leak && bash runtest.sh bonus leak
```
## Ressources
### Assembly Calling conventions

- The first four integer or pointer parameters are passed in the rcx, rdx, r8, and r9 registers.
- The first four floating-point parameters are passed in the first four SSE registers, xmm0-xmm3.
- The caller reserves space on the stack for arguments passed in registers. The called function can use this space to spill the contents of registers to the stack.
- Any additional arguments are passed on the stack.
- An integer or pointer return value is returned in the rax register, while a floating-point return value is returned in xmm0.
- rax, rcx, rdx, r8-r11 are volatile.
- rbx, rbp, rdi, rsi, r12-r15 are nonvolatile.
The x64 ABI considers the registers RAX, RCX, RDX, R8, R9, R10, R11, and XMM0-XMM5 volatile. When present, the upper portions of YMM0-YMM15 and ZMM0-ZMM15 are also volatile. On AVX512VL, the ZMM, YMM, and XMM registers 16-31 are also volatile. When AMX support is present, the TMM tile registers are volatile. Consider volatile registers destroyed on function calls unless otherwise safety-provable by analysis such as whole program optimization.
The x64 ABI considers registers RBX, RBP, RDI, RSI, RSP, R12, R13, R14, R15, and XMM6-XMM15 nonvolatile. They must be saved and restored by a function that uses them.

| 64-bit register | Lower 32 bits | Lower 16 bits | Lower 8 bits |
|----------------|---------------|---------------|-------------|
| rax            | eax           | ax            | al          |
| rbx            | ebx           | bx            | bl          |
| rcx            | ecx           | cx            | cl          |
| rdx            | edx           | dx            | dl          |
| rsi            | esi           | si            | sil         |
| rdi            | edi           | di            | dil         |
| rbp            | ebp           | bp            | bpl         |
| rsp            | esp           | sp            | spl         |
| r8             | r8d           | r8w           | r8b         |
| r9             | r9d           | r9w           | r9b         |
| r10            | r10d          | r10w          | r10b        |
| r11            | r11d          | r11w          | r11b        |
| r12            | r12d          | r12w          | r12b        |
| r13            | r13d          | r13w          | r13b        |
| r14            | r14d          | r14w          | r14b        |
| r15            | r15d          | r15w          | r15b        |

### Links
#### Lessons:

- <https://asmtutor.com/>
- <https://beta.hackndo.com/assembly-basics/>
- <https://medium.com/@leogaudin/libasm-a-guide-to-get-familiar-with-assembly-in-42-830f619f4c5e>
- <https://sonictk.github.io/asm_tutorial/>
- <https://www.unilim.fr/pages_perso/tristan.vaccon/cours_nasm.pdf>

#### Documentations:
- <https://pacman128.github.io/static/pcasm-book-french.pdf>
- <https://www.bencode.net/blob/nasmcheatsheet.pdf>
- <https://c9x.me/x86/>
- <https://www.cs.uaf.edu/2017/fall/cs301/lecture/09_11_registers.html>
- <https://www.felixcloutier.com/x86/index.html>
- <https://www.nasm.us/xdoc/2.16.03/html/nasmdoc0.html>
- <https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/x64-architecture#registers>

#### Great readme from other students:
- <https://gitlab.com/uotiug42/asm/libasm>
- <https://github.com/agavrel/LibftASM>

#### More about asm:
- <https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/>
- <https://g3tsyst3m.github.io/shellcoding/assembly/debugging/x64-Assembly-&-Shellcoding-101/>
- <https://www.agner.org/optimize/optimizing_assembly.pdf>
- <https://www.chromium.org/chromium-os/developer-library/reference/linux-constants/syscalls/>
- <https://www.ic.unicamp.br/~pannain/mc404/aulas/pdfs/Art%20Of%20Intel%20x86%20Assembly.pdf>
- <https://gaultier.github.io/blog/x11_x64.html>
- <https://github.com/below/HelloSilicon>

#### SSE:
- <https://www.strchr.com/strcmp_and_strlen_using_sse_4.2>

#### GDB on MACarm:
- <https://stackoverflow.com/questions/67310123/how-to-install-gdb-on-mac-m1-apple-silicon>

#### time cpu op:
- <http://ithare.com/infographics-operation-costs-in-cpu-clock-cycles/>

#### Unit testing:
- <https://github.com/Snaipe/Criterion>
- <https://github.com/PalmeseMattia/Xtal/blob/main/xtal.h>
- <https://github.com/ollelogdahl/ihct>
- <https://github.com/silentbicycle/greatest?tab=readme-ov-file>

#### Static analysis:
- <https://splint.org>
