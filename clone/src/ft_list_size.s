; File: ft_list_size.s
; File Created: 12/02/2025 20:25
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Description: <Desc of the file goal(s)>
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define LIST_SIZE_LABEL      _ft_list_size
%elifidn __OUTPUT_FORMAT__, elf64
    %define LIST_SIZE_LABEL      ft_list_size
%endif

global LIST_SIZE_LABEL
LIST_SIZE_LABEL:       ; rdi = ?, rsi = ?, rdx = ?
    ret
