%ifidn __OUTPUT_FORMAT__, macho64
    %define STRCMP_LABEL    _ft_strcmp
%elifidn __OUTPUT_FORMAT__, elf64
    %define STRCMP_LABEL    ft_strcmp
%endif

global STRCMP_LABEL
STRCMP_LABEL:      ; rdi = s1, rsi = s2
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