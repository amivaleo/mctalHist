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
 
# --help       -h     :: Show help
# --verb       -v     :: Verbose output
# --file       -f     :: Produce an output data file
# --tbar       -t     :: Show toolbar
# --edit       -e     :: Show editor
# --dark       -d     :: Dark variant
# --tick       -G     :: Show ticks
# --grid       -g     :: Show grid
# --leth       -L     :: Multiply the y axis values by a constant factor in order to give results in lethargy units

# --cWeight    -W     :: Set canvas width
# --cHeight    -H     :: Set canvas height

# --tally      -F     :: Select the tally to plot

# --tTitle     -T     :: Set the graph title
# --fileName   -o     :: Set output files name
# --imgName    -q     :: Specify the name for the background image

# --xAxis      -x     :: Set x axis
# --xTitle     -X     :: Set x axis title
# --xLab       -l     :: Hide x values
# --xLog       -i     :: Set log scale on x axis
# --xMul       -I     :: Multiply the x axis values by a constant factor
# --xMin       -a     :: Set x axis user range [minimum value]
# --xMax       -A     :: Set x axis user range [maximum value]

# --yAxis      -y     :: Set y axis
# --yTitle     -Y     :: Set y axis title
# --yLab       -m     :: Hide y values
# --yLog       -j     :: Set log scale on y axis
# --yMul       -J     :: Multiply the y axis values by a constant factor
# --yMin       -b     :: Set y axis user range [minimum value]
# --yMax       -B     :: Set y axis user range [maximum value]

# --zAxis      -z     :: Set z axis
# --zTitle     -Z     :: Set z axis title
# --zLab       -n     :: Hide z values
# --zLog       -k     :: Set log scale on z axis
# --zMul       -K     :: Multiply the z axis values by a constant factor
# --zMin       -c     :: Set z axis user range [minimum value]
# --zMax       -C     :: Set z axis user range [maximum value]

# --pMin       -p     :: Set coloured palette minimum value
# --pMax       -P     :: Set coloured palette maximum value
