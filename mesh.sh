#!/bin/bash

mctal2root mctal

mctalHist \
	-v \
	-W 1600 \
	-H 400 \
	--fileName meshDose \
	--error \
	--tally rmesh61 \
	--tTitle "Neutron dose rate map" \
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
	--pMin 1 \
	--pMax 1E8 \
	-o dat \
	-o eps \
	-o gif \
	-o root \
 mctal.root
