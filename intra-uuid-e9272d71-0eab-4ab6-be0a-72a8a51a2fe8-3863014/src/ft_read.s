global _ft_read
extern ___error

%ifidn __OUTPUT_FORMAT__, macho64
    %define READ_SYSCALL 0x2000003
%elifidn __OUTPUT_FORMAT__, elf32
    %define READ_SYSCALL 0
%endif

_ft_read:       ; rdi = fd, rsi = buf, rdx = count
    mov     eax, READ_SYSCALL   ; System call number for sys_read
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