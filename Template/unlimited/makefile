release.pdf: */* *.tex
	for i in $$(seq 1 5) ; do \
		echo $$i Processing... ; \
		xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo $$i Done. || (echo Failed. && rm release.pdf || print "") ; \
	done

unlimited.pdf: */* *.tex
	xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo $i Done. || (echo Failed. && rm unlimited.pdf || print "")

clean:
	rm *.log *.aux *.synctex.gz *.toc || printf ""
