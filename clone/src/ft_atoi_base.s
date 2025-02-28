; File: ft_atoi_base.s
; File Created: 12/02/2025 20:25
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Description: <Desc of the file goal(s)>
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define OS_FN_PREFIX(fn_call) _%+ fn_call
%elifidn __OUTPUT_FORMAT__, elf64
    %define OS_FN_PREFIX(fn_call) fn_call
%endif

extern OS_FN_PREFIX(ft_strlen)

global OS_FN_PREFIX(ft_atoi_base)
; rax : hold the result
; rbx : negation
OS_FN_PREFIX(ft_atoi_base): ; rdi = *str, rsi = *base
    cmp     rdi, 0          ; Check that str is not NULL
    je      error
    cmp     rsi, 0          ; Check that base is not NULL
    je      error
    mov     r8, rdi         ; store *str in r8 for now
    mov     rdi, rsi        ; load *base in rdi before call to strlen
    call    OS_FN_PREFIX(ft_strlen)
    cmp     rax, 2
    jl      error           ; jump if base smaller than 2
    cmp     rax, 16
    jg      error           ; jump if base bigger than 16
    mov     rcx, rsi        ; load *base in rcx

validate_base:
    cmp     byte [rcx], 0   ; '\0'
    je      dedup
    cmp     byte [rcx], ' '  ; ' '
    je      error
    cmp     byte [rcx], '+'  ; '+'
    je      error
    cmp     byte [rcx], '-'  ; '-'
    je      error
    inc     rcx
    jmp     validate_base

dedup:
    ; TODO: Check duplicate in the base -> error
;     mov     rbx, rsi        ; load *base in rbx
;     xor     rcx, rcx        ; reset the counter

    xor     rbx, rbx        ; reset rbx
    mov     rcx, r8        ; load *str in rcx
skip_space:
    cmp     byte [rcx], 0
    je      end
    cmp     byte [rcx], ' '
    inc     rcx
    jne     skip_space
    mov     rax, 1      ; test value to see that we change sign

read_sign:
;     ; check if the char is '+' or '-'
    cmp     byte [rcx], 0
    je      end
    cmp     byte [rcx], '+'
    je      positive
    cmp     byte [rcx], '-'
    jne     convert
negative:
    add     rbx,1
positive:
    inc     rcx
    jmp     read_sign

convert:
    ret
    ; inc     rcx
    ; cmp     byte [rcx], 0
    ; jne     convert

end:
    and     rbx, 1      ; mask rbx
    shl     rbx, 1      ; bit shift << 1
    sub     rbx, -1     ; here rbx is -1 or 1
    ; mul     rax
    mov     rax, rbx
    ret

error:
    xor     rax, rax        ; reset rax
    ret
