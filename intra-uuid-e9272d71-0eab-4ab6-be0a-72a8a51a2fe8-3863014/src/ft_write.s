global _ft_write

%ifidn __OUTPUT_FORMAT__, macho64
    extern ___error
    %define ERRNO_FN        ___error
    %define WRITE_SYSCALL   0x2000004
%elifidn __OUTPUT_FORMAT__, elf32
    extern __errno_location
    %define ERRNO_FN        __errno_location
    %define WRITE_SYSCALL   4
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
    call    ERRNO_FN
    ; call    __errno_locati`on
    mov     [rax], rdi  ; set the value of errno
    mov     rax, -1
    ret