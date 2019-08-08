single: */.* */* *.tex
	xelatex -shell-escape unlimited.tex || (rm unlimited.pdf ; return 1)

release.pdf: */.* */* *.tex
	for i in $$(seq 1 5) ; do \
		echo $$i Processing... ; \
		xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo $$i Done. ; \
	done
	cp unlimited.pdf release.pdf

clean:
	rm *.log *.aux *.synctex.gz *.toc || printf ""
