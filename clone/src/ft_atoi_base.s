; File: ft_atoi_base.s
; File Created: 12/02/2025 20:25
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Description: <Desc of the file goal(s)>
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define ATOI_LABEL      _ft_atoi_base
%elifidn __OUTPUT_FORMAT__, elf64
    %define ATOI_LABEL      ft_atoi_base
%endif

.data
basestr    db      '0123456789ABCDEF', 0h

.text
global ATOI_LABEL
; rax : hold the result
; rbx : negation
ATOI_LABEL:       ; rdi = *str, rsi = base
    ; xor     rax, rax        ; reset rax
    xor     rbx, rbx        ; reset rbx
    cmp     rdi, 0          ; Check that str is not NULL
    je      end
    cmp     rsi, 2
    jl      end             ; jump if base smaller than 2
    cmp     rsi, 16
    jg      end             ; jump if base bigger than 16
    xor     rcx, rcx        ; reset the counter
    ; skip spaces in str
skip_space:
    cmp     byte [rdi + rcx], 0
    je      end
    cmp     byte [rdi + rcx], 32
    inc     rcx
    jne     skip_space
    mov     rax, 1
read_sign:
    ; check if the char is '+' or '-'
    cmp     byte [rdi + rcx], 0
    je      end
    cmp     byte [rdi + rcx], 43 ; +
    je      positive
    cmp     byte [rdi + rcx], 45 ; -
    je      negative
    jmp     convert
negative:
    add     rbx,1
positive:
    inc     rcx
    jmp     read_sign

convert:
    cmp     byte [rdi + rcx], 0
    je      end
    inc     rcx
    jmp     convert

end:
    ; mask rbx
    and     rbx, 1
    shl     rbx, 1
    sub     rbx, -1
    mul     rax
    ret
