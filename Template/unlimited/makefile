release.pdf: */* *.tex
	for i in $(seq 1 5)
	do
		echo $i Processing...
		xelatex -shell-escape -interaction=nonstopmode unlimited.tex >> xelatex.log && echo $i Done. || echo Failed.
	done

clean:
	rm *.log *.aux *.synctex.gz *.toc || printf ""
