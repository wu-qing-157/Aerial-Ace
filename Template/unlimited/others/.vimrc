se et ts=4 sw=4 sts=4 nu sc sm lbr is hls mouse=a popt=number:y,duplex:off
sy on
ino <tab> <c-n>
ino <s-tab> <tab>
au bufwinenter * winc L

nm <f6> ggVG"+y

nm <f7> :w<cr>:!rm ##<cr>:make<cr>
nm <f8> :!@@<cr>
nm <f9> :!@@ < in<cr>
nm <s-f9> :!(time @@ < in &> out) &>> out<cr>:sp out<cr>
au filetype cpp se cin fdm=syntax mp=make\ %< | cm @@ ./%< | cm ## %<
au filetype java se cin mp=javac\ % | cm @@ java %< | cm ## %<.class
au filetype python se si fdm=indent mp=echo\ % | cm @@ pypy3 % | cm ## .
