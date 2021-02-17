#!/bin/bash

mctalHist \
	-W 640 -H 480 \
	--tally rmesh11 \
	--fileName mctal.root.rmesh11 \
	--tTitle "Plot Title" \
	--xAxis i --yAxis j --zAxis k \
	-A x --projection 15.5 \
	-A x --axisTitle "x" \
	-A y --axisTitle "y" \
	-A z --axisTitle "z" --axisLog --axisMin 15.5 --axisMax 15.5 \
	--paletteColor "kRainBow" \
	-o pdf \
mctal.root


mctalHist \
	-W 640 -H 480 \
	--tally rmesh11 --error \
	--fileName mctal.root.rmesh11 \
	--tTitle "Plot Title" \
	--xAxis i --yAxis j --zAxis k \
	-A x --projection 15.5 \
	-A x --axisTitle "x" \
	-A y --axisTitle "y" \
	-A z --axisTitle "z" --axisMin 15.5 --axisMax 15.5 \
	--paletteColor "kRainBow" --pMin 0 --pMax 1\
	-o pdf \
mctal.root
