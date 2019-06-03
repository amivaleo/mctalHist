#ifndef variables_h
#define variables_h

const std::string tab("\t");

const std::string blue("\033[1;34m");	// info
const std::string green("\033[1;32m");	// request
const std::string pink("\033[1;35m");	// test
const std::string red("\033[1;31m");	// errors
const std::string yellow("\033[1;33m");	// warnings

const std::string reset("\033[0m\e[0m");

const double leth = 10/TMath::Log(10);	// mcnp2lethargy conversion factor

const size_t color[] = {
	kRed - 3,
	kRed,
	kRed + 3,
	kGreen - 3,
	kGreen,
	kGreen + 3,
	kBlue - 3,
	kBlue,
	kBlue + 3,
	kYellow - 3,
	kYellow,
	kYellow + 3,
	kMagenta - 3,
	kMagenta,
	kMagenta + 3,
	kCyan - 3,
	kCyan,
	kCyan + 3,
	kOrange - 3,
	kOrange,
	kOrange + 3,
	kSpring - 3,
	kSpring,
	kSpring + 3,
	kTeal - 3,
	kTeal,
	kTeal + 3,
	kAzure - 3,
	kAzure,
	kAzure + 3,
	kViolet - 3,
	kViolet,
	kViolet + 3,
	kPink - 3,
	kPink,
	kPink + 3
	};

const std::vector<std::string> axes =	{"f", "d", "u", "s", "m", "c", "e", "t", "i", "j", "k"};
std::vector<size_t> axesBin = 			{ 0,   0,   0,   0,   0,   0,   0,};


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

bool error(false);

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

std::vector<double> contour;
std::string legendItem[] = {};

std::string fileName = "";
std::string imgName = "";

std::string tTitle = "";
std::string xTitle = "x";
std::string yTitle = "y";
std::string zTitle = "z";

Int_t cWidth = 1200;
Int_t cHeight = 800;

std::string tally = "";

std::vector<std::string> imgFormat;
TImage * img;
std::ofstream fileOutput (".output.dat");

#endif
