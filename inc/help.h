#ifndef help_h
#define help_h

const char* const short_opts = "hvbedGgW:H:F:eS:T:O:q:o:X:Y:Z:L:B:A:t:Vlc:m:M:p:P:K:C:";
const option long_opts[] = {
	{"help",		no_argument,		nullptr,	'h'},
	{"verb",		no_argument,		nullptr,	'v'},
	{"tbar",		no_argument,		nullptr,	'b'},
	{"dark",		no_argument,		nullptr,	'd'},
	{"tick",		no_argument,		nullptr,	'G'},
	{"grid",		no_argument,		nullptr,	'g'},
	{"cWidth",		required_argument,	nullptr,	'W'},
	{"cHeight",		required_argument,	nullptr,	'H'},
	{"tally",		required_argument,	nullptr,	'F'},
	{"error",		no_argument,		nullptr,	'e'},
	{"projection",		required_argument,		nullptr,	'S'},
	{"tTitle",		required_argument,	nullptr,	'T'},
	{"fileName",		required_argument,	nullptr,	'O'},
	{"imgName",		required_argument,	nullptr,	'q'},
	{"imgFormat",		required_argument,	nullptr,	'o'},
	{"xAxis",		required_argument,	nullptr,	'X'},
	{"yAxis",		required_argument,	nullptr,	'Y'},
	{"zAxis",		required_argument,	nullptr,	'Z'},
	{"axisLabelSize",		required_argument,	nullptr,	'L'},
	{"axisBin",		required_argument,	nullptr,	'B'},
	{"whichAxis",		required_argument,	nullptr,	'A'},
	{"axisTitle",		required_argument,	nullptr,	't'},
	{"axisValues",		no_argument,		nullptr,	'V'},
	{"axisLog",		no_argument,		nullptr,	'l'},
	{"axisMul",		required_argument,	nullptr,	'c'},
	{"axisMin",		required_argument,	nullptr,	'm'},
	{"axisMax",		required_argument,	nullptr,	'M'},
	{"pMin",		required_argument,	nullptr,	'p'},
	{"pMax",		required_argument,	nullptr,	'P'},
	{"paletteColor",		required_argument,	nullptr,	'K'},
	{"contour",		required_argument,	nullptr,	'C'},

	{nullptr,		no_argument,		nullptr,	0}
	};

const std::string optionDescription[] = {
	"Show help",
	
	"Verbose output",
	"Dark variant",
	"Show ticks",
	"Show grid",
	
	"Set canvas width",
	"Set canvas height",
	
	"Select the tally to plot",
	
	"Draw the profile at a desired position",
	
	"Draw the error map (only for meshes)",
	"Set the graph title",
	
	"Set output files name",
	"Specify the name for the background image",
	
	"Select the output file formats [dat, eps, gif, jpg, pdf, png, ps, root, svg]",
	
	"Set what the x axis will represent",
	"Set what the y axis will represent",
	"Set what the z axis will represent",
	
	"Set x label font size",
	"Set y label font size",
	"Set z label font size",
	
	"Select the axis for which you want to set options",
	"Set axis title",
	"Hide values",
	"Set log scale",
	"Multiply values by a constant factor",
	"Set axis user range [minimum value]",
	"Set axis user range [maximum value]",
	
	"Set coloured palette minimum value",
	"Set coloured palette maximum value",
	"Set the palette color style. Default: kRainBow. Possible values: kDeepSea, kGreyScale, kDarkBodyRadiator, kBlueYellow, kRainBow, kInvertedDarkBodyRadiator, kBird, kCubehelix, kGreenRedViolet, kBlueRedYellow, kOcean, kColorPrintableOnGrey, kAlpine, kAquamarine, kArmy, kAtlantic, kAurora, kAvocado, kBeach, kBlackBody, kBlueGreenYellow, kBrownCyan, kCMYK, kCandy, kCherry, kCoffee, kDarkRainBow, kDarkTerrain, kFall, kFruitPunch, kFuchsia, kGreyYellow, kGreenBrownTerrain, kGreenPink, kIsland, kLake, kLightTemperature, kLightTerrain, kMint, kNeon, kPastel, kPearl, kPigeon, kPlum, kRedBlue, kRose, kRust, kSandyTerrain, kSienna, kSolar, kSouthWest, kStarryNight, kSunset, kTemperatureMap, kThermometer, kValentine, kVisibleSpectrum, kWaterMelon, kCool, kCopper, kGistEarth, kViridis, kCividis"
	
	"Draw a contour line at given value"
	};


void PrintHelp() {
	for (size_t i = 0; i < sizeof(long_opts)/sizeof(long_opts[0]); ++i) {
		std::cout << blue << " --" << std::setw(10) << std::left << long_opts[i].name << reset;
		std::cout << blue << " -" << std::setw(6) << std::left << (char) long_opts[i].val << reset;
		std::cout << blue << ":: " << optionDescription[i] << reset << std::endl;
	}
	exit(1);
}

std::string ProcessArgs(int argc, char** argv) {

	if (argc < 2) {
		std::cout << blue << "Usage: mctalHist [options…] file.root" << reset << std::endl;
		return "breakmaincode";
	}

	std::string whichAxis = "";
	std::string input;
	
	while (true) {
		const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);
		
		if (opt == -1) {
			input = std::string(argv[argc - 1]);
			break;
		}

		switch (opt) {
		
		case 'h':	PrintHelp();	break;
		case 'v':	verb = 1;	break;
		case 'd':	dark = 1;	break;
		case 'G':	tick = 1;	break;
		case 'g':	grid = 1;	break;
		case 'W':	cWidth = std::stoi(optarg);	break;
		case 'H':	cHeight = std::stoi(optarg);	break;
		case 'F':	tally = std::string(optarg);	break;
		case 'e':	error = 1;	break;
		
		case 'S':
			projection = 1;
			if (whichAxis == "x") constantY = std::stod(optarg);
			else if (whichAxis == "y") constantX = std::stod(optarg);
		break;
		
		case 'T':	tTitle = std::string(optarg);	break;
		case 'O':	fileName = std::string(optarg);	break;
		case 'q':	imgName = std::string(optarg);	break;
		case 'o':
			if (std::string(optarg) == "dat") {
				file = 1;
			} else {
				imgFormat.push_back(std::string(optarg));
			}
			break;
		
		case 'X':	xAxis = getAxisIndex(std::string(optarg));	break;
		
		case 'Y':	yAxis = getAxisIndex(std::string(optarg));	break;
		
		case 'Z':	zAxis = getAxisIndex(std::string(optarg));	break;
		
		case 'B':	axesBin[getAxisIndex(whichAxis)] = std::stoi(optarg);	break;
		
		case 'A':	whichAxis = std::string(optarg);	break;
		
		case 't':
			if (whichAxis == "x") xTitle = std::string(optarg);
			else if (whichAxis == "y") yTitle = std::string(optarg);
			else if (whichAxis == "z") zTitle = std::string(optarg);
		break;

		case 'V':
			if (whichAxis == "x") xLab = true;
			else if (whichAxis == "y") yLab = true;
			else if (whichAxis == "z") zLab = true;
		break;
		
		case 'l':
			if (whichAxis == "x") xLog = true;
			else if (whichAxis == "y") yLog = true;
			else if (whichAxis == "z") zLog = true;
		break;
		
		case 'c':
			if (whichAxis == "x") xMul = std::stod(optarg);
			else if (whichAxis == "y") yMul = std::stod(optarg);
			else if (whichAxis == "z") zMul = std::stod(optarg);
		break;
		
		case 'm':
			if (whichAxis == "x") xMin = std::stod(optarg);
			else if (whichAxis == "y") yMin = std::stod(optarg);
			else if (whichAxis == "z") zMin = std::stod(optarg);
		break;
		
		case 'M':
			if (whichAxis == "x") xMax = std::stod(optarg);
			else if (whichAxis == "y") yMax = std::stod(optarg);
			else if (whichAxis == "z") zMax = std::stod(optarg);
		break;
		
		case 'L':
			if (whichAxis == "x") xLabel = std::stod(optarg);
			else if (whichAxis == "y") yLabel = std::stod(optarg);
			else if (whichAxis == "z") zLabel = std::stod(optarg);
		break;
		
		case 'p':	pMin = std::stod(optarg);	break;
		case 'P':	pMax = std::stod(optarg);	break;
		case 'K':
			if (getPaletteIndex(std::string(optarg)) != -1)
				paletteColor = getPaletteIndex(std::string(optarg)) + 51;
			else {
				std::cout << yellow << "Invalid palette color entry. Setting kRainBow." << reset << std::endl;
				paletteColor = 55;
			}
		break;
		
		case 'C':	contour.push_back(std::stod(optarg));	break;
		}
		
		input = std::string(argv[argc - 1]);
	}
	
	return input;
}

#endif
