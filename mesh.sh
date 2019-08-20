#!/bin/bash

mctalHist \
	-v \
	-W 1000 \
	-H 300 \
	--fileName meshDose \
	--tally rmesh11 \
	--tTitle "Neutron dose rate map" \
	--contour 1.5 \
	--xAxis i \
	--yAxis j \
	--zAxis k \
	-A x \
	--axisTitle "x [cm]" \
	-A y \
	--axisTitle "y [cm]" \
	-A z \
	--axisTitle "[#mu SV/h]" \
	--axisLog \
	--axisMin 13.7 \
	--axisMax 13.7 \
	--pMin 1E-3 \
	--pMax 1E+7 \
	--paletteColor "kRainBow" \
	-o pdf \
 mctal.root
