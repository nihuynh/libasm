global _ft_write
extern ___error

%ifidn __OUTPUT_FORMAT__, macho64
    %define WRITE_SYSCALL 0x2000004
%elifidn __OUTPUT_FORMAT__, elf32
    %define WRITE_SYSCALL 4
%endif

_ft_write:       ; rdi = fd, rsi = buf, rdx = count
    mov     eax, WRITE_SYSCALL  ; System call number for sys_write
    syscall
    cmp     rax, 0
    jl      error_code
    ret

error_code:
    neg     rax         ; get absolute value of syscall return
    mov     rdi, rax    ; back-up rax before calling ernno
    call    ___error
    mov     [rax], rdi  ; set the value of errno
    mov     rax, -1
    ret