#ifndef variables_h
#define variables_h

bool edit(true);	// show editor?
bool tbar(true);	// show toolbar?
bool file(false);	// write file with hist/graph data?
bool verb(false);	// verbose?
bool dark(false);	// dark hist/graph?
bool tick(true);	// show ticks?
bool grid(true);	// show grid?
bool xLab(true);	// show values on x axis?
bool yLab(true);	// show values on y axis?
bool zLab(true);	// show values on z axis?
bool xLog(false);	// x axis log-scale?
bool yLog(false);	// y axis log-scale?
bool zLog(false);	// z axis log-scale?

int xAxis = -1;
int yAxis = -1;
int zAxis = -1;

double xMin(-99999);
double xMax(-99999);
double yMin(-99999);
double yMax(-99999);
double zMin(-99999);
double zMax(-99999);

double pMin(1);
double pMax(1);

double xMul(1);
double yMul(1);
double zMul(1);

double contours[] = {};

std::string legendItem[] = {};

std::string fileName = "";
std::string imgName = "";

std::string tTitle = "";
std::string xTitle = "x";
std::string yTitle = "y";
std::string zTitle = "z";

int cWidth = 1200;
int cHeight = 800;

std::string tally = "";

std::vector<std::string> imgFormat;
TImage * img;
std::ofstream fileOutput (".output.dat");

#endif
