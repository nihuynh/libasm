; File: ft_strlen.s
; File Created: 05/02/2025 23:12
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Description: <Desc of the file goal(s)>
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define STRLEN_LABEL    _ft_strlen
%elifidn __OUTPUT_FORMAT__, elf64
    %define STRLEN_LABEL    ft_strlen
%endif

global STRLEN_LABEL
STRLEN_LABEL:      ; rdi = *str to check
    mov     rax, rdi

runloop:
    cmp     byte [rax], 0
    je      end
    inc     rax
    jmp     runloop

end:
    sub rax, rdi
    ret