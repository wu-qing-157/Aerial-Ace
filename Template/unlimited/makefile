unlimited.pdf: */.* */* *.tex
	xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo $i Done. || (echo Failed. && rm unlimited.pdf || print "")

release.pdf: */.* */* *.tex
	for i in $$(seq 1 5) ; do \
		echo $$i Processing... ; \
		xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo $$i Done. ; \
	done
	cp unlimited.pdf release.pdf

clean:
	rm *.log *.aux *.synctex.gz *.toc || printf ""
