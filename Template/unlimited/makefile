single: ./*/.* ./*/* *.tex
	xelatex -shell-escape unlimited.tex || (rm unlimited.pdf ; return 1)

pre-release.pdf: ./*/.* ./*/* *.tex
	xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo Done.
	xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo Done.
	xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo Done.
	xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo Done.
	xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo Done.
	cp unlimited.pdf pre-release.pdf

release.pdf: ./*/.* ./*/* *.tex
	xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo Done.
	xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo Done.
	xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo Done.
	xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo Done.
	xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo Done.
	cp unlimited.pdf release.pdf

clean:
	rm *.log *.aux *.synctex.gz *.toc || printf ""
