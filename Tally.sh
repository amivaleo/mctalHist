#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Usage: ./script.sh mctal.root"
	exit 1
fi

mctalHist \
	--verb \
	--tick --grid \
	--tally f135 \
	--fileName $1.f135 \
	--tTitle " " \
	--xAxis e \
	-A x --axisLog --axisTitle "x [cm]" \
	-A y --axisLog --axisTitle "Flux" --axisMin 1E+0 --axisMax 1E+8 \
	-o pdf -o dat \
$1
