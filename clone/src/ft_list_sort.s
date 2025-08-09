; File: ft_list_sort.s
; File Created: 12/02/2025 20:25
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define OS_FN_PREFIX(fn_call) _%+ fn_call
%elifidn __OUTPUT_FORMAT__, elf64
    %define OS_FN_PREFIX(fn_call) fn_call
%endif
; r8 head
; r9 runner x
; r10 runner y
; r11 fn ptr
global OS_FN_PREFIX(ft_list_sort)
OS_FN_PREFIX(ft_list_sort):       ; t_list **head, rsi = fnptr
    cmp     rdi, 0
    je      end
    mov     r8, [rdi]       ; Save head *list node to r8
    mov     r11, rsi        ; Save fnptr to r11
    mov     r9, r8
x_loop: ; change r9
    cmp     r9, 0
    je      end
    mov     r10, r8
y_loop: ; change r10
    mov     rdi, [r9]
    mov     rsi, [r10]
    call    r11
    cmp     rax, 0
    jl      inc_loop
swap_val:
    mov     [r9], rsi
    mov     [r10], rdi

inc_loop:
    mov     r10, [r10 + 8]
    cmp     r10, 0
    jne     y_loop
    mov     r9, [r9 + 8]
    cmp     r9, 0
    jne     x_loop
end:
    ret


