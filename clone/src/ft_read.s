%ifidn __OUTPUT_FORMAT__, macho64
    extern ___error
    %define ERRNO_FN        ___error
    %define READ_SYSCALL    0x2000003
    %define READ_LABEL      _ft_read
%elifidn __OUTPUT_FORMAT__, elf64
    extern __errno_location
    %define ERRNO_FN        __errno_location
    %define READ_SYSCALL    0
    %define READ_LABEL      ft_read
%endif

global READ_LABEL
READ_LABEL:       ; rdi = fd, rsi = buf, rdx = count
    mov     eax, READ_SYSCALL   ; System call number for sys_read
    syscall
    cmp     rax, 0
    jl      error_code
    ret

error_code:
    neg     rax         ; get absolute value of syscall return
    mov     rdi, rax    ; back-up rax before calling ernno
    call    ERRNO_FN
    mov     [rax], rdi  ; set the value of errno
    mov     rax, -1
    ret