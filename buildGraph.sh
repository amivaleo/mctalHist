#!/bin/bash

./mctalHist \
	-t \
	-v \
	-f \
	--tally f135 \
	--xAxis e \
	--xTitle "x [cm]" \
	--xLog \
	--yTitle "[n/cm^{2}/sec/u]" \
	--yLog \
	--yMin 1 \
	--yMax 1E+8 \
 mctal.root
 
#		--help		-h \
#		--verb		-v \
#		--file		-f \
#		--tbar		-t \
#		--edit		-e \
#		--dark		-d \
#		--tick		-G \
#		--grid		-g \
#		--leth		-L \
#		--tally		-F [] \
#		--title		-T [] \
#		--fileName	-o [] \
#		--imgName	-W [] \

#		--xAxis		-x [] \
#		--xTitle	-X [] \
#		--xLab		-l \
#		--xLog		-i \
#		--xMul		-I [] \
#		--xMin		-a [] \
#		--xMax		-A [] \

#		--yAxis		-y [] \
#		--yTitle	-Y [] \
#		--yLab		-m \
#		--yLog		-j \
#		--yMul		-J [] \
#		--yMin		-b [] \
#		--yMax		-B [] \

#		--zAxis		-z [] \
#		--zTitle	-Z [] \
#		--zLab		-n \
#		--zLog		-k \
#		--zMul		-K [] \
#		--zMin		-c [] \
#		--zMax		-C [] \

#		--pMin		-p [] \
#		--pMax		-P [] \
