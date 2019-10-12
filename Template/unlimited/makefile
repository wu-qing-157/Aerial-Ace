single: ./*/.* ./*/* *.tex
	xelatex -shell-escape unlimited.tex || (rm unlimited.pdf ; return 1)

pre-release.pdf: ./*/.* ./*/* *.tex
	for i in $$(seq 1 5) ; do \
		echo $$i Processing... ; \
		xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo $$i Done. ; \
	done
	cp unlimited.pdf pre-release.pdf

release.pdf: ./*/.* ./*/* *.tex
	for i in $$(seq 1 5) ; do \
		echo $$i Processing... ; \
		xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo $$i Done. ; \
	done
	cp unlimited.pdf release.pdf

clean:
	rm *.log *.aux *.synctex.gz *.toc || printf ""
