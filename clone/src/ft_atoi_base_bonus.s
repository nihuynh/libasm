; File: ft_atoi_base.s
; File Created: 12/02/2025 20:25
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%include "os_support.s"
extern OS_FN_PREFIX(ft_strlen)
global OS_FN_PREFIX(ft_atoi_base)

; r8 : negation
; r9 : base length
OS_FN_PREFIX(ft_atoi_base): ; rdi = *str, rsi = *base
    cmp     rdi, 0          ; Check that str is not NULL
    je      error
    cmp     rsi, 0          ; Check that base is not NULL
    je      error
    cmp     byte [rdi], 0   ; Check that str is not empty
    je      error
    cmp     byte [rsi], 0   ; Check that base is not empty
    je      error
; Check the base length
    push    rdi             ; save value rdi
    mov     rdi, rsi        ; load *base in rdi before call to strlen
    call    OS_FN_PREFIX(ft_strlen)
    pop     rdi             ; restore rdi
    cmp     rax, 2
    jl      error           ; jump if base smaller than 2
    cmp     rax, 16
    jg      error           ; jump if base bigger than 16
    mov     r9, rax         ; save the length of the base
    mov     rcx, rsi        ; load *base in rcx
validate_base:
    cmp     byte [rcx], ' ' ; ' '
    je      error
    cmp     byte [rcx], '+' ; '+'
    je      error
    cmp     byte [rcx], '-' ; '-'
    je      error
    cmp     byte [rcx], 13  ; keep checking if *base > than 13
    jg      inc_base
    cmp     byte [rcx], 9   ; Error if 9 < *base <= than 13
    jge     error
inc_base:
    inc     rcx
    cmp     byte [rcx], 0   ; '\0'
    jne     validate_base
; Check if the base has no duplicate char
    mov     rcx, rsi        ; load *base in rcx
    xor     rax, rax        ; reset rax
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
    xor     r8, r8          ; reset r8
skip_space:
    cmp     byte [rcx], 0
    je      error
    cmp     byte [rcx], ' '
    je      keep_skip
    cmp     byte [rcx], 9   ; jmp read if *str < than 9
    jl      read_sign
    cmp     byte [rcx], 13  ; jmp read if *str > than 13
    jg      read_sign
keep_skip:
    inc     rcx
    jmp     skip_space

read_sign: ; check if the char is '+' or '-'
    cmp     byte [rcx], '+'
    je      positive
    cmp     byte [rcx], '-'
    jne     convert
    inc     r8              ; Case char is '-'
positive:
    inc     rcx
    cmp     byte [rcx], 0
    je      end
    jmp     read_sign

convert: ; rcx is the cursor of the str , r10 is the seek offset, r11b hold the current char
    xor     r10, r10
    mov     r11b, byte[rcx]
seek_char:
    cmp     byte[rsi + r10], 0
    je      end
    cmp     byte[rsi + r10], r11b
    je      use_idx
    inc     r10
    jmp     seek_char

use_idx:
    mul     r9              ; mul r9*rax -> rax (r9: base length)
    add     rax, r10
    inc     rcx
    cmp     byte [rcx], 0
    je      end
    jmp     convert

end:
    inc     r8
    and     r8, 1           ; mask r8
    shl     r8, 1           ; bit shift << 1
    sub     r8, 1           ; here r8 is -1 or 1
    mul     r8              ; mul r8*rax -> rax
    ret

error:
    xor     rax, rax        ; reset rax
    ret
