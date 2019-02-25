#ifndef help_h
#define help_h

	const std::string optionDescription[] = {
		"Show help",
		
		"Verbose output",
		"Produce an output data file",
		"Show toolbar",
		"Show editor",
		"Dark variant",
		"Show ticks",
		"Show grid",
		"Multiply the y axis values by a constant factor in order to give results in lethargy units",
		
		"Select the tally to plot",
		"Set the graph title",
		
		"Set output files name",
		"Specify the name for the background image",
		
		"Set x axis",
		"Set x axis title",
		"Hide x values",
		"Set log scale on x axis",
		"Multiply the x axis values by a constant factor",
		"Set x axis user range [minimum value]",
		"Set x axis user range [maximum value]",
		
		"Set y axis",
		"Set y axis title",
		"Hide y values",
		"Set log scale on y axis",
		"Multiply the y axis values by a constant factor",
		"Set y axis user range [minimum value]",
		"Set y axis user range [maximum value]",
		
		"Set z axis",
		"Set z axis title",
		"Hide z values",
		"Set log scale on z axis",
		"Multiply the z axis values by a constant factor",
		"Set z axis user range [minimum value]",
		"Set z axis user range [maximum value]",
		
		"Set coloured palette minimum value",
		"Set coloured palette maximum value"
		};


void PrintHelp() {
	std::vector<std::vector<std::string>> options {
		{"help", "h"},
		{"verb", "v"},
		{"file", "f"},
		{"tbar", "t"},
		{"edit", "e"},
		{"dark", "d"},
		{"tick", "G"},
		{"grid", "g"},
		{"leth", "L"},
		{"tally", "F"},
		{"title", "T"},
		{"fName", "N"},
		{"iName", "W"},
		
		{"xAxis", "x"},
		{"xTitle", "X"},
		{"xLab", "l"},
		{"xLog", "i"},
		{"xMul", "I"},
		{"xMin", "a"},
		{"xMax", "A"},
		{"yAxis", "y"},		
		{"yTitle", "Y"},
		{"yLab", "m"},
		{"yLog", "j"},
		{"yMul", "J"},
		{"yMin", "b"},
		{"yMax", "B"},
		{"zAxis", "z"},		
		{"zTitle", "Z"},
		{"zLab", "n"},
		{"zLog", "k"},
		{"zMul", "K"},
		{"zMin", "c"},
		{"zMax", "C"},		
		{"pMin", "p"},
		{"pMax", "P"}
		};
		
	std::cout << blue << "Usage :: mctalHist [OPTIONS]... [FILE]" << reset << std::endl;
	for (size_t i = 0; i < options.size(); ++i) {
		std::cout << blue << " --" << std::setw(10) << std::left << options[i][0] << reset;
		std::cout << blue << " -" << std::setw(6) << std::left << options[i][1] << reset;
		std::cout << blue << ":: " << optionDescription[i] << reset << std::endl;
	}
	exit(1);
}

std::string ProcessArgs(int argc, char** argv) {

	std::string input;
	
	const char* const short_opts = "hvftedGgLF:T:N:W:x:X:liI:a:A:y:Y:mjJ:b:B:z:Z:nkK:c:C:p:P:";
	const option long_opts[] = {

		{"help",		no_argument,		nullptr,	'h'},

		{"verb",		no_argument,		nullptr,	'v'},
		{"file",		no_argument,		nullptr,	'f'},
		{"tbar",		no_argument,		nullptr,	't'},
		{"edit",		no_argument,		nullptr,	'e'},
		{"dark",		no_argument,		nullptr,	'd'},
		{"tick",		no_argument,		nullptr,	'G'},
		{"grid",		no_argument,		nullptr,	'g'},
		{"leth",		no_argument,		nullptr,	'L'},

		{"tally",		required_argument,	nullptr,	'F'},
		{"title",		required_argument,	nullptr,	'T'},

		{"fName",		required_argument,	nullptr,	'N'},
		{"iName",		required_argument,	nullptr,	'W'},
		
		{"xAxis",		required_argument,	nullptr,	'x'},
		{"xTitle",		required_argument,	nullptr,	'X'},
		{"xLab",		no_argument,		nullptr,	'l'},
		{"xLog",		no_argument,		nullptr,	'i'},
		{"xMul",		required_argument,	nullptr,	'I'},
		{"xMin",		required_argument,	nullptr,	'a'},
		{"xMax",		required_argument,	nullptr,	'A'},
		
		{"yAxis",		required_argument,	nullptr,	'y'},		
		{"yTitle",		required_argument,	nullptr,	'Y'},
		{"yLab",		no_argument,		nullptr,	'm'},
		{"yLog",		no_argument,		nullptr,	'j'},
		{"yMul",		required_argument,	nullptr,	'J'},
		{"yMin",		required_argument,	nullptr,	'b'},
		{"yMax",		required_argument,	nullptr,	'B'},

		{"zAxis",		required_argument,	nullptr,	'z'},		
		{"zTitle",		required_argument,	nullptr,	'Z'},
		{"zLab",		no_argument,		nullptr,	'n'},
		{"zLog",		no_argument,		nullptr,	'k'},
		{"zMul",		required_argument,	nullptr,	'K'},
		{"zMin",		required_argument,	nullptr,	'c'},
		{"zMax",		required_argument,	nullptr,	'C'},		

		{"pMin",		required_argument,	nullptr,	'p'},
		{"pMax",		required_argument,	nullptr,	'P'},

		{nullptr,		no_argument,		nullptr,	0}
	};
		
	while (true) {
		const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);
		
		if (opt == -1) {
			input = std::string(argv[argc - 1]);
			break;
		}

		switch (opt) {
		case 'h':
			PrintHelp();
			break;
		case 'v':
			verb = 1;
			break;
		case 'f':
			file = 1;
			break;
		case 't':
			tbar = 1;
			break;
		case 'e':
			edit = 1;
			break;

		case 'd':
			dark = 1;
			break;
		case 'G':
			tick = 1;
			break;
		case 'g':
			grid = 1;
			break;
		case 'L':
			yMul *= leth;
			break;

		case 'F':
			tally = std::string(optarg);
			break;
		case 'T':
			tTitle = std::string(optarg);
			break;
			
		case 'N':
			fileName = std::string(optarg);
			break;
		case 'W':
			imgName = std::string(optarg);
			break;
			
		case 'x':
			xAxis = getAxisIndex(optarg);
			break;
		case 'X':
			xTitle = std::string(optarg);
			break;
		case 'l':
			xLab = true;
			break;
		case 'i':
			xLog = true;
			break;
		case 'I':
			xMul = std::stod(optarg);
			break;
		case 'a':
			xMin = std::stod(optarg);
			break;
		case 'A':
			xMax = std::stod(optarg);
			break;
			

		case 'y':
			yAxis = getAxisIndex(optarg);
			break;
		case 'Y':
			yTitle = std::string(optarg);
			break;
		case 'm':
			yLab = true;
			break;
		case 'j':
			yLog = true;
			break;
		case 'J':
			yMul = std::stod(optarg);
			break;
		case 'b':
			yMin = std::stod(optarg);
			break;
		case 'B':
			yMax = std::stod(optarg);
			break;

		case 'z':
			zAxis = getAxisIndex(optarg);
			break;
		case 'Z':
			zTitle = std::string(optarg);
			break;
		case 'n':
			zLab = true;
			break;
		case 'k':
			zLog = true;
			break;
		case 'K':
			zMul = std::stod(optarg);
			break;
		case 'c':
			zMin = std::stod(optarg);
			break;
		case 'C':
			zMax = std::stod(optarg);
			break;
			
		case 'p':
			pMin = std::stod(optarg);
			break;
		case 'P':
			pMax = std::stod(optarg);
			break;
		}
		
		input = std::string(argv[argc - 1]);
	}
	
	return input;
}

#endif
