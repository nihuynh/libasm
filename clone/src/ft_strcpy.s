; File: ft_strcpy.s
; File Created: 05/02/2025 23:12
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Description: <Desc of the file goal(s)>
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define STRCPY_LABEL    _ft_strcpy
%elifidn __OUTPUT_FORMAT__, elf64
    %define STRCPY_LABEL    ft_strcpy
%endif

global STRCPY_LABEL
STRCPY_LABEL:      ; rdi = dst, rsi = src
    xor     rcx, rcx    ; reset the counter

runloop:
    mov     al, byte [rsi + rcx]    ; store byte of src
    mov     byte [rdi + rcx], al    ; write the byte to dest
    cmp     al, 0                   ; check if the last char was a null-char
    je      end
    inc     rcx
    jmp     runloop

end:
    mov     rax, rdi
    ret