%ifidn __OUTPUT_FORMAT__, macho64
    %define STRCMP_LABEL    _ft_strcmp
%elifidn __OUTPUT_FORMAT__, elf64
    %define STRCMP_LABEL    ft_strcmp
%endif

global STRCMP_LABEL
STRCMP_LABEL:      ; rdi = s1, rsi = s2
    xor     rcx, rcx    ; reset the counter

runloop:
    mov     al, byte [rdi + rcx]
    cmp     al, byte [rsi + rcx]
    jne     retdiff     ; not equal so break
    cmp     al, 0
    je      retdiff
    inc     rcx
    jmp     runloop

retdiff:
    sub     al, byte [rsi + rcx]    ; sub the char ascii value in s1 & s2
    movsx   rax, al                 ; mov but keep the sign - or +
    ret