; File: ft_list_push_front.s
; File Created: 12/02/2025 20:25
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define OS_FN_PREFIX(fn_call) _%+ fn_call
%elifidn __OUTPUT_FORMAT__, elf64
    %define OS_FN_PREFIX(fn_call) fn_call
%endif

global OS_FN_PREFIX(ft_list_push_front)
OS_FN_PREFIX(ft_list_push_front):       ; rdi = **head rsi = *list node
    cmp     rsi, 0
    je      end
    mov     r8, [rdi]       ; Save head *list node to r8
    mov     [rsi + 8], r8   ; Link new elt.next to r8
    mov     [rdi], rsi      ; Change head value to *elt
end:
    ret
