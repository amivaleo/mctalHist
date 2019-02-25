#!/bin/bash

./mctalHist \
	-t \
	-v \
	-f \
	--fName "output" \
	--title "Neutron #muSv/h" \
	--xTitle "x [cm]" \
	--yTitle "y [cm]" \
	--tally rmesh1 \
 t.m.root
