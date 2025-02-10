extern malloc
%ifidn __OUTPUT_FORMAT__, macho64
    %define STRDUP_LABEL    _ft_strdup
    extern _ft_strlen
    %define STRLEN_LABEL    _ft_strlen
    extern _ft_strcpy
    %define STRCPY_LABEL    _ft_strcpy
%elifidn __OUTPUT_FORMAT__, elf64
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
    pop     rsi         ; restore the stack and the *str to rsi
    cmp     rax, 0      ; check if malloc has failed
    je      error_code
    mov     rdi, rax
    call    STRCPY_LABEL

error_code:
    ret