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
; r9 : negation
OS_FN_PREFIX(ft_atoi_base): ; rdi = *str, rsi = *base
    cmp     rdi, 0          ; Check that str is not NULL
    je      error
    cmp     rsi, 0          ; Check that base is not NULL
    je      error
    cmp     byte [rdi], 0   ; Check that str is not empty
    je      error

    push    rbx             ; save value rbx
    push    rdi             ; save value rdi

    mov     rdi, rsi        ; load *base in rdi before call to strlen
    call    OS_FN_PREFIX(ft_strlen)
    pop     rdi             ; restore rdi
    cmp     rax, 2
    jl      error           ; jump if base smaller than 2
    cmp     rax, 16
    jg      error           ; jump if base bigger than 16

    mov     rcx, rsi        ; load *base in rcx
validate_base:
    cmp     byte [rcx], ' ' ; ' '
    je      error
    cmp     byte [rcx], '+' ; '+'
    je      error
    cmp     byte [rcx], '-' ; '-'
    je      error
    inc     rcx
    cmp     byte [rcx], 0   ; '\0'
    jne     validate_base

    mov     rcx, rsi        ; load *base in rcx
    xor     rax, rax        ; reset rax
    xor     rbx, rbx        ; reset rbx
dedup:  ; rcx is a cursor, rax is the seek offset
    mov     bl, byte [rcx + rax]

seek:   ;  seek the rest of the base
    inc     rax
    cmp     bl, byte [rcx + rax]
    je      error
    cmp     byte [rcx + rax], 0
    jne     seek
        ; move to the next char in the base to check
    xor     rax, rax        ; reset rax
    inc     rcx
    cmp     byte [rcx], 0   ; '\0'
    jne     dedup
        ; prepare reg for skip space & read sign
    mov     rcx,rdi         ; load *str in rcx
    xor     r9, r9          ; reset r9
skip_space:
    cmp     byte [rcx], 0
    je      error
    cmp     byte [rcx], ' '
    jne     read_sign
    inc     rcx
    jmp     skip_space
read_sign: ; check if the char is '+' or '-'
    cmp     byte [rcx], '+'
    je      positive
    cmp     byte [rcx], '-'
    jne     convert
    inc     r9              ; Case char is '-'
positive:
    inc     rcx
    cmp     byte [rcx], 0
    je      end
    jmp     read_sign

convert:
    ; TODO: implement atoi
    mov     rax, 6          ; test value to see that we change sign

end:
    inc     r9
    and     r9, 1           ; mask r9
    shl     r9, 1           ; bit shift << 1
    sub     r9, 1           ; here r9 is -1 or 1
    mul     r9              ; mul r9*rax -> rax
    pop     rbx             ; restore rbx
    ret

error:
    pop     rbx             ; restore rbx
    xor     rax, rax        ; reset rax
    ret
