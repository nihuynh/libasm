%ifidn __OUTPUT_FORMAT__, macho64
    %define FN_LABEL        _ft_strcpy
%elifidn __OUTPUT_FORMAT__, elf64
    %define FN_LABEL        ft_strcpy
%endif

global FN_LABEL
FN_LABEL:      ; rdi = dst, rsi = src
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