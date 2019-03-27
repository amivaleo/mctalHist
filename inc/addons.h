#ifndef addons_h
#define addons_h

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

#endif
