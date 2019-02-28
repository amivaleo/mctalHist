#ifndef settings_h
#define settings_h

#include "variables.h"

edit = true;	// show editor?
tbar(true);	// show toolbar?
file(true);	// write file with hist/graph data?
verb(true);	// verbose?
dark(false);	// dark hist/graph?
tick(true);	// show ticks?
grid(true);	// show grid?
xLab(true);	// show values on x axis?
yLab(true);	// show values on y axis?
zLab(true);	// show values on z axis?
xLog(false);	// x axis log-scale?
yLog(false);	// y axis log-scale?
zLog(false);	// z axis log-scale?

xMul(1);	xMin(1);	xMax(1);
yMul(1);	yMin(1);	yMax(1);
zMul(1);	zMin(1);	zMax(1);

pMin(1);	pMax(1);	// palette color range

contours[] = {};
legendItem[] = {};

fileName = "";
imgName = "";

tTitle = "";
xTitle = "x";
yTitle = "y";
zTitle = "z";

canvasWidth = 1200;	canvasHeight = 800;

tTitle =
	"Neutron dose rate [#muSv/h]";
//	"Neutron flux [n/cm^{2}/sec]";
//	"Neutron flux per unit lethargy [n/cm^{2}/sec] @ Bunker Wall exit";
//	"Neutron flux per unit lethargy [n/cm^{2}/sec] @ Bunker Wall exit (z: 13.7 cm)";
//	"Neutron flux per unit lethargy [n/cm^{2}/sec] @ 25m from TCS";
//	"Conversion functions from flux to dose rate";
//	"2GeV neutron transmittivity in natural Cu";
//	"#xi as a function of x";
//	"Conversion function from flux to dose rate";
//	"Neutron flux @ (x, y, z) = (550.0, 0.0, 13.7) (units in cm) (monolith exit)";
//	"Proton and STERM comparison";
xTitle =
//	"E [MeV]";
	"x [cm]";
yTitle =
//	"Neutron flux per unit lethargy [n/cm^{2}/sec]";
	"z [cm]";
//	"y [cm]";
//	"(#muSv/h) / (# / cm^{2} / sec)";
zTitle =
	"";
//	"[#mu Sv / h]";

gStyle->SetOptStat(0);

#endif
