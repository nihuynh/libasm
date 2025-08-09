; File: ft_list_size.s
; File Created: 12/02/2025 20:25
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define OS_FN_PREFIX(fn_call) _%+ fn_call
%elifidn __OUTPUT_FORMAT__, elf64
    %define OS_FN_PREFIX(fn_call) fn_call
%endif

global OS_FN_PREFIX(ft_list_size)
OS_FN_PREFIX(ft_list_size):       ; rdi = *list node
    xor     rcx, rcx    ; reset the counter
    mov     r8, rdi
follow:
    cmp     r8, 0
    je      end
    inc     rcx
    mov     r8, [r8 + 8]
    jmp     follow
end:
    mov     rax, rcx
    ret
