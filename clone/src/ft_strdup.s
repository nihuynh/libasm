; File: ft_strdup.s
; File Created: 05/02/2025 23:12
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Description: <Desc of the file goal(s)>
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    extern _malloc
    %define MALLOC_FN        _malloc
    %define STRDUP_LABEL    _ft_strdup
    extern _ft_strlen
    %define STRLEN_LABEL    _ft_strlen
    extern _ft_strcpy
    %define STRCPY_LABEL    _ft_strcpy
%elifidn __OUTPUT_FORMAT__, elf64
    extern malloc
    %define MALLOC_FN        malloc
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
    call    MALLOC_FN
    pop     rsi         ; restore the stack and the *str to rsi
    cmp     rax, 0      ; check if malloc has failed
    je      error_code
    mov     rdi, rax
    call    STRCPY_LABEL

error_code:
    ret