; File: os_support.s
; File Created: 12/08/2025 01:25
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define OS_FN_PREFIX(fn_call) _%+ fn_call
%elifidn __OUTPUT_FORMAT__, elf64
    %define OS_FN_PREFIX(fn_call) fn_call
%endif

%ifidn __OUTPUT_FORMAT__, macho64
    %define ERRNO_FN        ___error
    %define READ_SYSCALL    0x2000003
    %define WRITE_SYSCALL   0x2000004
%elifidn __OUTPUT_FORMAT__, elf64
    %define ERRNO_FN        __errno_location
    %define READ_SYSCALL    0
    %define WRITE_SYSCALL   1
%endif
