extern malloc
%ifidn __OUTPUT_FORMAT__, macho64
    extern ___error
    %define ERRNO_FN        ___error
    %define STRDUP_LABEL    _ft_strdup
    extern _ft_strlen
    %define STRLEN_LABEL    _ft_strlen
    extern _ft_strcpy
    %define STRCPY_LABEL    _ft_strcpy
%elifidn __OUTPUT_FORMAT__, elf64
    extern __errno_location
    %define ERRNO_FN        __errno_location
    %define STRDUP_LABEL    ft_strdup
    extern ft_strlen
    %define STRLEN_LABEL    ft_strlen
    extern ft_strcpy
    %define STRCPY_LABEL    ft_strcpy
%endif

global STRDUP_LABEL
STRDUP_LABEL:       ; rdi = *str duplicate

    call    STRLEN_LABEL
    push    rdi
    inc     rax
    mov     rdi, rax
    call    malloc
    cmp     rax, 0      ; Check malloc has failed
    jl      error_code
    mov     rdi, rax
    pop     rsi
    call    STRCPY_LABEL
    ret

error_code:
    neg     rax         ; get absolute value of syscall return
    mov     rdi, rax    ; back-up rax before calling ernno
    call    ERRNO_FN
    mov     [rax], rdi  ; set the value of errno
    mov     rax, 0
    ret