#ifndef functions_h
#define functions_h

bool fileExist(const char *fileName) {
	std::ifstream infile(fileName);
	return infile.good();
}

size_t getAxisIndex(const std::string element) {
	auto it = std::find(axes.begin(), axes.end(), element);
	if (it != axes.end()) return std::distance(axes.begin(), it);
	else return -1;
}

size_t getPaletteIndex(const std::string element) {
	auto it = std::find(paletteColorStyle.begin(), paletteColorStyle.end(), element);
	if (it != paletteColorStyle.end()) return std::distance(paletteColorStyle.begin(), it);
	else return -1;
}

template <typename T> std::string to_string (const T val) {
	std::ostringstream out;
	out.precision(0);
	out << std::fixed << val;
	return out.str();
}

TCanvas * generateCanvas() {
	if (fileExist(imgName.c_str())) {
		img = TImage::Open(imgName.c_str());
		cWidth = 1.25*img->GetWidth();
		cHeight = 1.25*img->GetHeight();
	}
	TCanvas * c = new TCanvas(fileName.c_str(), fileName.c_str(), cWidth, cHeight);
	c->SetWindowSize(cWidth + (cWidth - c->GetWw()), cHeight + (cHeight - c->GetWh()));
	if (tbar) c->ToggleEventStatus();
	if (edit) c->ToggleEditor();
	if (dark) gStyle->SetTitleTextColor(0);
	if (dark) c->SetFillColor(1);
	if (grid) c->SetGrid();
	if (tick) gPad->SetTicks();
	gStyle->SetOptStat(0);
	return c;
}

TLegend * generateLegend(unsigned int size = 0) {
	TLegend * legend;
	if (size < 9) legend = new TLegend(0.91, 0.9, 0.99, 0.9 - ++size*0.05);
	else legend = new TLegend(0.91, 0.1, 0.99, 0.9);
	legend->SetNColumns(1);
	legend->SetLineColor(1);
	legend->SetTextAlign(12);
	if (dark) legend->SetLineColor(1);
	if (dark) legend->SetFillColor(0);
	if (dark) legend->SetTextColor(0);
	return legend;
}

void customizeHist(TH1 * hist) {
	hist->SetTitle(tTitle.c_str());
//	hist->GetXaxis()->SetLabelSize(xLabel);
	hist->GetXaxis()->SetTitle(xTitle.c_str());
//	hist->GetXaxis()->SetTitleSize(0.04);
	
//	hist->GetYaxis()->SetLabelSize(yLabel);
	hist->GetYaxis()->SetTitle(yTitle.c_str());
//	hist->GetYaxis()->SetTitleSize(0.04);
	
//	hist->GetZaxis()->SetLabelSize(zLabel);
	hist->GetZaxis()->SetTitle(zTitle.c_str());
//	hist->GetZaxis()->SetTitleSize(0.04);
	
	canvasRightMargin = 0.15;
	
	hist->SetLineWidth(2);
	gStyle->SetNumberContours(100);
	gStyle->SetPalette(paletteColor, 0, 1.0);
	if (!xLab) {
		hist->GetXaxis()->SetLabelSize(0);
		hist->GetXaxis()->SetTitleOffset(0.5);
	}
	if (!yLab) {
		hist->GetYaxis()->SetLabelSize(0);
		hist->GetYaxis()->SetTitleOffset(0.5);
	}
	if (!zLab) {
		hist->GetZaxis()->SetLabelSize(0);
		hist->GetZaxis()->SetTitleOffset(0.5);
		canvasRightMargin = 0.1;
	}
	if (dark) hist->GetXaxis()->SetAxisColor(0);
	if (dark) hist->GetYaxis()->SetAxisColor(0);
	if (dark) hist->GetXaxis()->SetLabelColor(0);
	if (dark) hist->GetYaxis()->SetLabelColor(0);
	if (dark) hist->GetXaxis()->SetTitleColor(0);
	if (dark) hist->GetYaxis()->SetTitleColor(0);
	return;
}

void customizeGraph(TGraphErrors * graph) {
	graph->SetTitle(tTitle.c_str());
	graph->GetXaxis()->SetLabelSize(0.03);
	graph->GetXaxis()->CenterTitle(true);
	graph->GetXaxis()->SetTitle(xTitle.c_str());
	graph->GetYaxis()->SetLabelSize(0.03);
	graph->GetYaxis()->CenterTitle(true);
	graph->GetYaxis()->SetTitle(yTitle.c_str());
	graph->SetLineWidth(3);
	graph->SetMarkerSize(1);
	graph->SetMarkerStyle(20);
	if (!xLab) graph->GetXaxis()->SetLabelSize(0);
	if (!yLab) graph->GetYaxis()->SetLabelSize(0);
	if (dark) graph->GetXaxis()->SetAxisColor(0);
	if (dark) graph->GetXaxis()->SetLabelColor(0);
	if (dark) graph->GetXaxis()->SetTitleColor(0);
	if (dark) graph->GetYaxis()->SetAxisColor(0);
	if (dark) graph->GetYaxis()->SetLabelColor(0);
	if (dark) graph->GetYaxis()->SetTitleColor(0);
	return;
}

void customizeGraph2D(TGraph2D * graph) {
	graph->SetTitle(tTitle.c_str());
	graph->GetXaxis()->SetLabelSize(0.05);
	graph->GetXaxis()->CenterTitle(true);
	graph->GetXaxis()->SetTitle(xTitle.c_str());
	graph->GetYaxis()->SetLabelSize(0.05);
	graph->GetYaxis()->CenterTitle(true);
	graph->GetYaxis()->SetTitle(yTitle.c_str());
	graph->GetZaxis()->SetLabelSize(0.05);
	graph->GetZaxis()->CenterTitle(true);
	graph->GetZaxis()->SetTitle(zTitle.c_str());
	graph->SetLineWidth(3);
	graph->SetMarkerSize(1);
	graph->SetMarkerStyle(20);
	if (!xLab) graph->GetXaxis()->SetLabelSize(0);
	if (!yLab) graph->GetYaxis()->SetLabelSize(0);
	if (!zLab) graph->GetZaxis()->SetLabelSize(0);
	if (dark) graph->GetXaxis()->SetAxisColor(0);
	if (dark) graph->GetXaxis()->SetLabelColor(0);
	if (dark) graph->GetXaxis()->SetTitleColor(0);
	if (dark) graph->GetYaxis()->SetAxisColor(0);
	if (dark) graph->GetYaxis()->SetLabelColor(0);
	if (dark) graph->GetYaxis()->SetTitleColor(0);
	if (dark) graph->GetZaxis()->SetAxisColor(0);
	if (dark) graph->GetZaxis()->SetLabelColor(0);
	if (dark) graph->GetZaxis()->SetTitleColor(0);
	return;
}

void customizeMultiGraph(TMultiGraph * graph) {
	graph->SetTitle(tTitle.c_str());
	graph->GetXaxis()->SetLabelSize(0.03);
	graph->GetXaxis()->CenterTitle(true);
	graph->GetXaxis()->SetTitle(xTitle.c_str());
	graph->GetYaxis()->SetLabelSize(0.03);
	graph->GetYaxis()->CenterTitle(true);
	graph->GetYaxis()->SetTitle(yTitle.c_str());
	if (!xLab) graph->GetXaxis()->SetLabelSize(0);
	if (!yLab) graph->GetYaxis()->SetLabelSize(0);
	if (dark) graph->GetXaxis()->SetAxisColor(0);
	if (dark) graph->GetXaxis()->SetLabelColor(0);
	if (dark) graph->GetXaxis()->SetTitleColor(0);
	if (dark) graph->GetYaxis()->SetAxisColor(0);
	if (dark) graph->GetYaxis()->SetLabelColor(0);
	if (dark) graph->GetYaxis()->SetTitleColor(0);
	return;
}

void save(TCanvas * c, TObject * obj) {
	std::string output;
	
	if (file) {
		std::rename(".output.dat", (fileName + ".dat").c_str());
		fileOutput.close();
	} else if (!file) {
		std::remove(".output.dat");
	}
	
	if (imgFormat.size() == 0) {
		output = fileName + ".png";
		c->SaveAs(output.c_str());	
	} else if (imgFormat.size() > 0) {
		for (size_t i = 0; i < imgFormat.size(); ++i) {
			output = fileName + "." + imgFormat[i];
			if (imgFormat[i] == "root")
				obj->SaveAs(output.c_str());
			else 
				c->SaveAs(output.c_str());
		}
	}
	return;
}

#endif
