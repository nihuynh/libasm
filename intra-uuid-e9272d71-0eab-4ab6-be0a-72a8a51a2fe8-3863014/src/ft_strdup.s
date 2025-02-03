%ifidn __OUTPUT_FORMAT__, macho64
    %define FN_LABEL        _ft_strdup
%elifidn __OUTPUT_FORMAT__, elf64
    %define FN_LABEL        ft_strdup
%endif

global FN_LABEL
FN_LABEL:
    retl