#!/bin/bash

./mH \
	-t \
	-v \
	-f \
	-W 900 \
	-H 900 \
	--tally rmesh81 \
	--tTitle "Integrated neutron flux" \
	--xAxis j \
	--xTitle "x [cm]" \
	--yAxis k \
	--yTitle "y [cm]" \
	--zAxis i \
	--zTitle "[n/cm^{2}/sec]" \
	--zLog \
 mctal.root
