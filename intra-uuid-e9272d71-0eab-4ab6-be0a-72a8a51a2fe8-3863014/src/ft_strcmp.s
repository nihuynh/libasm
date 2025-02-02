global _ft_strcmp

_ft_strcmp:      ; rdi = s1, rsi = s2
    xor     rcx, rcx    ; reset the counter

runloop:
    mov     bl, byte [rdi + rcx]
    cmp     bl, byte [rsi + rcx]
    jne     retdiff     ; not equal so break
    cmp     byte [rdi + rcx], 0
    jz      retdiff
    inc     rcx
    jmp     runloop

retdiff:
    mov     al, byte [rdi + rcx]
    sub     al, byte [rsi + rcx]
    movsx   rax, al
    ret