# libasm

## Overview

## TODO

- [ ] Setup gdb debug
- [ ] Setup vsc debug
- [x] Rework tests
- [x] Bonus: atoi base
- [ ] Bonus: list size
- [ ] Bonus: list others
- [ ] Add 42 Headers
- [ ] Retry project (before 01/09/25)
- [ ] ...

## Assembly

### Calling conventions

- The first four integer or pointer parameters are passed in the rcx, rdx, r8, and r9 registers.
- The first four floating-point parameters are passed in the first four SSE registers, xmm0-xmm3.
- The caller reserves space on the stack for arguments passed in registers. The called function can use this space to spill the contents of registers to the stack.
- Any additional arguments are passed on the stack.
- An integer or pointer return value is returned in the rax register, while a floating-point return value is returned in xmm0.
- rax, rcx, rdx, r8-r11 are volatile.
- rbx, rbp, rdi, rsi, r12-r15 are nonvolatile.
The x64 ABI considers the registers RAX, RCX, RDX, R8, R9, R10, R11, and XMM0-XMM5 volatile. When present, the upper portions of YMM0-YMM15 and ZMM0-ZMM15 are also volatile. On AVX512VL, the ZMM, YMM, and XMM registers 16-31 are also volatile. When AMX support is present, the TMM tile registers are volatile. Consider volatile registers destroyed on function calls unless otherwise safety-provable by analysis such as whole program optimization.
The x64 ABI considers registers RBX, RBP, RDI, RSI, RSP, R12, R13, R14, R15, and XMM6-XMM15 nonvolatile. They must be saved and restored by a function that uses them.

## Ressources

Lessons:

- <https://asmtutor.com/>
- <https://beta.hackndo.com/assembly-basics/>
- <https://medium.com/@leogaudin/libasm-a-guide-to-get-familiar-with-assembly-in-42-830f619f4c5e>
- <https://sonictk.github.io/asm_tutorial/>
- <https://www.unilim.fr/pages_perso/tristan.vaccon/cours_nasm.pdf>

Documentations:
- <https://pacman128.github.io/static/pcasm-book-french.pdf>
- <https://www.bencode.net/blob/nasmcheatsheet.pdf>
- <https://c9x.me/x86/>
- <https://www.cs.uaf.edu/2017/fall/cs301/lecture/09_11_registers.html>
- <https://www.felixcloutier.com/x86/index.html>
- <https://www.nasm.us/xdoc/2.16.03/html/nasmdoc0.html>
- <https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/x64-architecture#registers>

other students repo:
- <https://gitlab.com/uotiug42/asm/libasm>
- <https://github.com/agavrel/LibftASM>

More about asm:
- <https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/>
- <https://g3tsyst3m.github.io/shellcoding/assembly/debugging/x64-Assembly-&-Shellcoding-101/>
- <https://www.agner.org/optimize/optimizing_assembly.pdf>
- <https://www.chromium.org/chromium-os/developer-library/reference/linux-constants/syscalls/>
- <https://www.ic.unicamp.br/~pannain/mc404/aulas/pdfs/Art%20Of%20Intel%20x86%20Assembly.pdf>
- <https://gaultier.github.io/blog/x11_x64.html>
- <https://github.com/below/HelloSilicon>

SSE:
- <https://www.strchr.com/strcmp_and_strlen_using_sse_4.2>

GDB on MACarm:
- <https://stackoverflow.com/questions/67310123/how-to-install-gdb-on-mac-m1-apple-silicon>

time cpu op:
- <http://ithare.com/infographics-operation-costs-in-cpu-clock-cycles/>

Unit testing:
- <https://github.com/Snaipe/Criterion>
- <https://github.com/PalmeseMattia/Xtal/blob/main/xtal.h>
- <https://github.com/ollelogdahl/ihct>
- <https://github.com/silentbicycle/greatest?tab=readme-ov-file>

Static analysis:
- <https://splint.org>

## Installation

```shell
    sudo apt update && sudo apt install -y build-essential gdb clang nasm
```

## Formatting

```shell
    # Generate basic uncrust config
    uncrustify --update-config-with-doc -o uncrust.conf
```
