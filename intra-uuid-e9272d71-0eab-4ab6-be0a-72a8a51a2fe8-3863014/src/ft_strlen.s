%ifidn __OUTPUT_FORMAT__, macho64
    %define FN_LABEL        _ft_strlen
%elifidn __OUTPUT_FORMAT__, elf64
    %define FN_LABEL        ft_strlen
%endif

global FN_LABEL
FN_LABEL:      ; rdi = str to check
    mov     rax, rdi

runloop:
    cmp     byte [rax], 0
    jz      end
    inc     rax
    jmp     runloop

end:
    sub rax, rdi
    ret