; File: ft_strlen.s
; File Created: 05/02/2025 23:12
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Description: <Desc of the file goal(s)>
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define OS_FN_PREFIX(fn_call) _%+ fn_call
%elifidn __OUTPUT_FORMAT__, elf64
    %define OS_FN_PREFIX(fn_call) fn_call
%endif

global OS_FN_PREFIX(ft_strlen)
OS_FN_PREFIX(ft_strlen):      ; rdi = *str to check
    mov     rax, rdi

runloop:
    cmp     byte [rax], 0
    je      end
    inc     rax
    jmp     runloop

end:
    sub rax, rdi
    ret
