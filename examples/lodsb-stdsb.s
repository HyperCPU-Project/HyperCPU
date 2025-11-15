// Example of using LODSB/STDSB instructions

.attr(entry) main:
    mov xsp, 0u512;
    mov xbp, xsp;
    mov xlll1, 'H';
    stdsb xlll1, 0s-12;
    lodsb xlll2, 0s-12;
    write xlll0, xlll2;
    halt;