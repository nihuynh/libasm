global _ft_strlen

_ft_strlen:      ; rdi = str to check
    mov     rax, rdi

runloop:
    cmp     byte [rax], 0
    jz      end
    inc     rax
    jmp     runloop

end:
    sub rax, rdi
    ret