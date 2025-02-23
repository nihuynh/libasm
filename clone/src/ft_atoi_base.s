; File: ft_atoi_base.s
; File Created: 12/02/2025 20:25
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Description: <Desc of the file goal(s)>
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define OS_PREFIX(fn_call) _%+ fn_call
%elifidn __OUTPUT_FORMAT__, elf64
    %define OS_PREFIX(fn_call) fn_call
%endif

extern OS_PREFIX(ft_strlen)

global OS_PREFIX(ft_atoi_base)
; rax : hold the result
; rbx : negation
OS_PREFIX(ft_atoi_base):       ; rdi = *str, rsi = *base
    cmp     rdi, 0          ; Check that str is not NULL
    je      error
    cmp     rsi, 0          ; Check that base is not NULL
    je      error
    call    OS_PREFIX(ft_strlen)
    cmp     rax, 2
    jl      error             ; jump if base smaller than 2
    cmp     rax, 16
    jg      error             ; jump if base bigger than 16
    ; TODO: Check duplicate in the base -> error
    ; TODO: Check white spaces or -/+ -> error


    xor     rax, rax        ; reset rax
    xor     rbx, rbx        ; reset rbx
    xor     rcx, rcx        ; reset the counter
    mov     rax, 1 ; early test return
    ret

; skip_space:
;     cmp     byte [rdi + rcx], 0
;     je      end
;     cmp     byte [rdi + rcx], 32
;     inc     rcx
;     jne     skip_space
;     mov     rax, 1
; read_sign:
;     ; check if the char is '+' or '-'
;     cmp     byte [rdi + rcx], 0
;     je      end
;     cmp     byte [rdi + rcx], 43 ; +
;     je      positive
;     cmp     byte [rdi + rcx], 45 ; -
;     je      negative
;     jmp     convert
; negative:
;     add     rbx,1
; positive:
;     inc     rcx
;     jmp     read_sign

; convert:
;     cmp     byte [rdi + rcx], 0
;     je      end
;     inc     rcx
;     jmp     convert
; end:
;     ; mask rbx
;     ; and     rbx, 1
;     ; shl     rbx, 1
;     ; sub     rbx, -1
;     ; mul     rax
;     ret

error:
    xor     rax, rax        ; reset rax
    ret
