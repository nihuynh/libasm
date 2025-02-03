%ifidn __OUTPUT_FORMAT__, macho64
    %define FN_LABEL        _ft_add
%elifidn __OUTPUT_FORMAT__, elf64
    %define FN_LABEL        ft_add
%endif

global FN_LABEL
FN_LABEL:
    add rdi, rsi
    mov rax, rdi
    ret