se et ts=4 sw=4 sts=4 nu sc sm lbr is hls mouse=a cin fdm=syntax mp=make\ %<
sy on
ino <tab> <c-n>
ino <s-tab> <tab>
au bufwinenter * winc L

nm <f6> ggVG"+y

nm <F7> :w<cr>:make<cr>
nm <F8> :!./%<<cr>
nm <F9> :!./%< < in<cr>
nm <S-F9> :!(time ./%< < in &> out) &>> out<cr>:sp out<cr>

sy keyword Type point line circle info data
