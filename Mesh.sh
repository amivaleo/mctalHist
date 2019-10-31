#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Usage: ./script.sh mctal.root"
	exit 1
fi

mctalHist \
	--verb \
	-W 1000 -H 300 \
	--tally rmesh11 \
	--fileName $1.rmesh11 \
	--tTitle "Neutron dose rate map" \
	--contour 1.5 \
	--xAxis i --yAxis j --zAxis k \
	-A x --axisTitle "x [cm]" \
	-A y --axisTitle "y [cm]" \
	-A z --axisTitle "[#mu SV/h]" --axisLog --axisMin 13.7 --axisMax 13.7 \
	--pMin 1E-3 --pMax 1E+7 --paletteColor "kRainBow" \
	-o pdf \
$1
