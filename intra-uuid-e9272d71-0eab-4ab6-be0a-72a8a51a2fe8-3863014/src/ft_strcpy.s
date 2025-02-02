global _ft_strcpy

_ft_strcpy:      ; rdi = dst, rsi = src
    xor     rcx, rcx    ; reset the counter

runloop:
    mov     al, byte [rsi + rcx]
    mov     byte [rdi + rcx], al
    cmp     byte [rsi + rcx], 0
    jz      end
    inc     rcx
    jmp     runloop

end:
    mov     rax, rdi
    ret