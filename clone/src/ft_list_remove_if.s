; File: ft_list_remove_if.s
; File Created: 12/02/2025 20:25
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Description: <Desc of the file goal(s)>
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define LIST_REMOVE_IF_LABEL      _ft_list_remove_if
%elifidn __OUTPUT_FORMAT__, elf64
    %define LIST_REMOVE_IF_LABEL      ft_list_remove_if
%endif

global LIST_REMOVE_IF_LABEL
LIST_REMOVE_IF_LABEL:       ; rdi = ?, rsi = ?, rdx = ?
    ret
