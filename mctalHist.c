/*
g++ mctalHist.c `root-config --cflags --ldflags --libs` -o mctalHist
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <getopt.h>

#include "inc/libraries.h"
#include "inc/addons.h"
#include "inc/variables.h"
#include "inc/functions.h"
#include "inc/help.h"

int main (int argc, char** argv) {

	std::string tmp;
	
	if (argc < 2) {
		std::cerr << red << "ERROR :: arguments missing!" << reset << std::endl;
		std::cerr << blue << "Usage: mctalHist [-option VALUE] file.root" << reset << std::endl;
		std::cout << blue << "The content in square brackets [ ] is optional" << reset << std::endl;
		PrintHelp();
		return 1;
	}

	std::string input = ProcessArgs(argc, argv);
	if (!fileExist(input.c_str())) {
		std::cerr << red << "ERROR :: input file doesn't exist!" << reset << std::endl;
		return 1;
	}
	
	// read input file mctal.root
	TFile *file = new TFile(input.c_str());
	THnSparseF *s;
	
	// select the tally to plot
	if (tally == "") {
		// list the content of the root input file
		file->ls();
		do {
			std::cout << green << "Select the THnSparse: " << reset;
			std::cin >> tally;
			s = (THnSparseF *)file->Get(tally.c_str());
		} while (!s);
	} else s = (THnSparseF *)file->Get(tally.c_str());
	
	if (s->GetNdimensions() == 11) std::cout << yellow << "WARNING :: the selected tally is a tmesh" << reset << std::endl;
	
	// print all THnSparse axes if they were not declared in the input bash script
	if ((xAxis == -1) || (zAxis == -1)) s->Print("all");
	
	TCanvas *c;
	
	// MESH --------------------------------------------------------------------
	if (s->GetNdimensions() == 11) {
		
		fileName = fileName == "" ? tally : fileName;
		
		// select the axis to plot
		while ((zAxis < 0) || (zAxis > 10)) {
			std::cout << green << "Select the axis perpendicular to the map you are going to plot [f, d, u, s, m, c, e, t, i, j, k]: " << reset;
			std::cin >> tmp;
			zAxis = getAxisIndex(tmp);
		}
		std::cout << std::endl;
		
		// if the axis perpendicular to the map has more than 1 bin, let the user decide what to plot
		if (s->GetAxis(zAxis)->GetNbins() > 1) {

			if ((zMin == zMax) && (zMin == -99999)) {
				std::cout << blue << tab << "The selected axis has " << s->GetAxis(zAxis)->GetNbins() << " bins." << reset << std::endl;
				
				// print all the bins edges for the axis perpendicular to the map
				std::cout << blue << tab << "Bins edges for axis " << axes[zAxis] << ": " << reset;
				for (size_t i = 0; i <= s->GetAxis(zAxis)->GetNbins(); i++) std::cout << blue << s->GetAxis(zAxis)->GetBinUpEdge(i) << reset << "  ";
				std::cout << std::endl;
				
				if (verb) {
					std::cout << yellow << "WARNING :: note that for each bin, the following logic apply: [a; b)" << reset << std::endl;
					std::cout << yellow << tab << "for example, if you have ... 3  -  4  -  5  -  6 ... and you enter 5, then you get this bin: [5; 10)" << reset << std::endl;
				}
				
				// let the user select to sum all bins content or not
				std::cout << green << "Select the minimum [a :: all bins]: " << reset;
				std::cin >> tmp;
				
				if (tmp != "a") {
					zMin = std::stod(tmp);
					std::cout << green << "Select the maximum: " << reset;
					std::cin >> zMax;
					zMin = s->GetAxis(zAxis)->GetBinLowEdge(s->GetAxis(zAxis)->FindFixBin(zMax));
					zMax = s->GetAxis(zAxis)->GetBinUpEdge(s->GetAxis(zAxis)->FindFixBin(zMax));
					s->GetAxis(zAxis)->SetRangeUser(zMin, zMax);
					std::cout << blue << "The selected bin boundaries for the " << axes[zAxis] << " axis are: [" << zMin << "; " << zMax << "]" << reset << std::endl;
				} else std::cout << yellow << "WARNING :: all bins will be plotted" << reset << std::endl;
			} else {
				zMin = s->GetAxis(zAxis)->GetBinLowEdge(s->GetAxis(zAxis)->FindFixBin(zMax));
				zMax = s->GetAxis(zAxis)->GetBinUpEdge(s->GetAxis(zAxis)->FindFixBin(zMax));
				s->GetAxis(zAxis)->SetRangeUser(zMin, zMax);
				std::cout << blue << "The selected bin boundaries for the " << axes[zAxis] << " axis are: [" << zMin << "; " << zMax << "]" << reset << std::endl;
			}
		
		}
		
		// select abscissae and ordinates axes
		if (xAxis == -1) {
			do {
				std::cout << green << "Select the abscissae axis [f, d, u, s, m, c, e, t, i, j, k]: " << reset;
				std::cin >> tmp;
				xAxis = getAxisIndex(tmp);
			} while ((!xAxis) || (!std::cin) || (xAxis > 10));
		}
		if (yAxis == -1) {
			do {
				std::cout << green << "Select the ordinates axis [f, d, u, s, m, c, e, t, i, j, k]: " << reset;
				std::cin >> tmp;
				yAxis = getAxisIndex(tmp);
			} while ((!yAxis) || (!std::cin) || (yAxis > 10));
			if (verb) std::cout << yellow << "WARNING :: no validation is performed on the inserted values" << reset << std::endl;
		}
		
		if (xLog) {
			gPad->SetLogx();
			if (verb) std::cout << yellow << "WARNING :: setting log-scale for x axis" << reset << std::endl;
		}
		if (yLog) {
			gPad->SetLogy();
			if (verb) std::cout << yellow << "WARNING :: setting log-scale for y axis" << reset << std::endl;
		}
		
		c = generateCanvas();
		c->SetMargin(0.1, 0.1, 0.1, 0.1);
		// use a background image if available
		if (img) {
			TPad *p1 = new TPad("p1","p1",0.1, 0.1, .9, .9);
			p1->Draw();
			p1->cd();
			img->Draw();
			c->cd();
			TPad *p2 = new TPad("p2","p2",0., 0., 1., 1.);
			if (zLog) {p2->SetLogz();}
			p2->SetFillStyle(4000);
			p2->SetFrameFillColor(0);
			p2->SetFrameFillStyle(0);
			p2->Draw();
			p2->cd();
		}
		
		if (xLog) {
			gPad->SetLogx();
			if (verb) std::cout << yellow << "WARNING :: setting log-scale for x axis" << reset << std::endl;
		}
		if (yLog) {
			gPad->SetLogy();
			if (verb) std::cout << yellow << "WARNING :: setting log-scale for y axis" << reset << std::endl;
		}
		if (zLog) {
			gPad->SetLogz();
			if (verb) std::cout << yellow << "WARNING :: setting log-scale for z axis" << reset << std::endl;
		}
		

		if ((xMin == xMax) && (xMin = -99999)) {
			xMin = s->GetAxis(xAxis)->GetBinLowEdge(s->GetAxis(xAxis)->GetFirst());
			xMax = s->GetAxis(xAxis)->GetBinUpEdge(s->GetAxis(xAxis)->GetLast());
		}

		if ((yMin == yMax) && (yMin = -99999)) {
			yMin = s->GetAxis(yAxis)->GetBinLowEdge(s->GetAxis(yAxis)->GetFirst());
			yMax = s->GetAxis(yAxis)->GetBinUpEdge(s->GetAxis(yAxis)->GetLast());
		}

		if (verb) {
			std::cout << blue << "The following TH2 will be drawn:" << reset << std::endl;
			std::cout << blue << tab << yMax << tab << "┐" << reset << std::endl;
			std::cout << blue <<    tab << tab << "│" << reset << std::endl;
			std::cout << blue << axes[yAxis] << ": '" << yTitle << "'" << tab << "│" << tab << tab << "☉ " << axes[zAxis] << " [" << zMin << ", " << zMax << "] : '" << zTitle << "'" << reset << std::endl;
			std::cout << blue <<    tab << tab << "│" << reset << std::endl;
			std::cout << blue << tab << yMin << tab << "┼───────────────────────┐" << reset << std::endl;
			std::cout << blue <<   tab << tab << xMin << tab << axes[xAxis] << ": '" << xTitle << "'" << tab << xMax << reset << std::endl;
			std::cout << green << "Press ⏎ to continue…" << reset << std::endl;
			std::cin.ignore();
		}
			
			
		TH2D * h = (TH2D *)s->Projection(yAxis, xAxis)->Clone("clone");
		customizeHist(h);
		
		int entries = h->GetEntries();
		
		h->SetTitle(tTitle.c_str());
		
		tmp = fileName + ".dat";
		if (file) std::rename(".output.dat", tmp.c_str());
		
		// set a constant multiplicative factor
		if (zMul != 1) {
			std::cout << yellow << "WARNING :: the z axis is multiplied by the constant factor " << zMul << reset << std::endl;
			for (int i = 1; i < entries; i++) {
				h->SetBinContent(i, h->GetBinContent(i)*zMul);
				h->SetBinError(i, h->GetBinError(i)*zMul);
				if (file) {
					fileOutput << std::scientific
					 << i << tab 
					 << h->GetBinContent(i) << tab 
					 << h->GetBinError(i) << std::endl;
				}
			}
		}
		
		// change palette range
		if (pMin != pMax) {
			h->GetZaxis()->SetRangeUser(pMin, pMax);
			if (verb) std::cout << blue << std::scientific << "User defined range for the palette: [" << pMin << ", " << pMax << "]" << reset << std::endl;
		}
		
		// write the output file if requested // this must be ameliorated
		if (file) {
			fileOutput << "# " << tTitle.c_str() << std::endl;
			fileOutput << "# abiscissae axis: " << tab << xAxis << std::endl;
			if (xMin != xMax) fileOutput << "#  - from " << xMin << " to " << xMax << std::endl;
			if (xMul != 1) fileOutput << "#" << tab << "multiplied by" << xMul << std::endl;
			fileOutput << "# ordinates axis: " << tab << yAxis << std::endl;
			if (yMin != yMax) fileOutput << "#  - from " << yMin << " to " << yMax << std::endl;
			if (yMul != 1) fileOutput << "#" << tab << "multiplied by" << yMul << std::endl;
			fileOutput << "# perpendicular axis: " << tab << zAxis << std::endl;
			if (zMin != zMax) fileOutput << "#  - from " << zMin << " to " << zMax << std::endl;
			if (zMul != 1) fileOutput << "#" << tab << "multiplied by" << zMul << std::endl;
			if (pMin != pMax) fileOutput << "# palette range - from " << pMin << " to " << pMax << std::endl;
		}
		if (file) fileOutput << "#---" << tab << "Value-------" << tab << "Stat_err----" << std::endl;
		
		
		h->Draw("colz");
		
		// draw contours if any
		if (sizeof(contours)/sizeof(double) != 0) {
			h->SetContour(sizeof(contours)/sizeof(double),contours);
			h->SetLineColor(kRed);
			h->SetLineWidth(2);
			h->SetMarkerSize(8);
			h->Draw("cont3 same");
		}

		save(c, h);
	
	// =========================================================================
	} else {	// TALLY -------------------------------------------------------
	// =========================================================================
		
		double bin;
		fileName = fileName == "" ? tally : fileName;
		
		// select the axis to plot
		while ((xAxis < 0) || (xAxis > 7)) {
			std::cout << green << "Select the abiscissae axis [f, d, u, s, m, c, e, t]: " << reset;
			std::cin >> tmp;
			xAxis = getAxisIndex(tmp);
		}
		fileName += "_" + axes[xAxis];
		
		// set ranges for all the other axes if they have more than 1 bin
		for (size_t i = 0; i < s->GetNdimensions(); i++) {
			if ((i != xAxis) && (s->GetAxis(i)->GetNbins() > 1)) {
				fileName += "-" + axes[i];
				std::cout << blue << "Axis " << axes[i] << " has " << s->GetAxis(i)->GetNbins() << " bins" << reset << std::endl;
				std::cout << green << tab << "Select the bin for the " << axes[i] << " axis [a :: all bins] [1-" << s->GetAxis(i)->GetNbins() << "]: " << reset;
				std::cin >> tmp;
				
				if (tmp != "a") {
					bin = std::stoi(tmp);
					fileName += to_string(bin);
					s->GetAxis(i)->SetRange(bin, bin);
				} else std::cout << yellow << "WARNING :: all bins will be plotted" << reset << std::endl;
			}
		}
		
		c = generateCanvas();
		TH1D * h = (TH1D *)s->Projection(xAxis)->Clone("clone");
		customizeHist(h);
		
		if (xLog) {
			gPad->SetLogx();
			if (verb) std::cout << yellow << "WARNING :: setting log-scale for x axis" << reset << std::endl;
		}
		if (yLog) {
			gPad->SetLogy();
			if (verb) std::cout << yellow << "WARNING :: setting log-scale for y axis" << reset << std::endl;
		}
		
		// set x and y user ranges
		if ((xMin == xMax) && (xMin = -99999)) {
			xMin = h->GetXaxis()->GetBinUpEdge(h->GetXaxis()->GetFirst());
			xMax = h->GetXaxis()->GetBinUpEdge(h->GetXaxis()->GetLast());
		} else {
			std::cout << blue << "User defined range for the x axis: [" << xMin << "; " << xMax << "]" << reset << std::endl;
			h->GetXaxis()->SetRangeUser(xMin, xMax);
		}
		
		if ((yMin == yMax) && (yMin = -99999)) {
			yMin = h->GetYaxis()->GetBinLowEdge(h->GetYaxis()->GetFirst());
			yMax = h->GetYaxis()->GetBinUpEdge(h->GetYaxis()->GetLast());
		} else {
			std::cout << blue << "User defined range for the y axis: [" << yMin << "; " << yMax << "]" << reset << std::endl;
			h->GetYaxis()->SetRangeUser(yMin, yMax);
		}
		
		if (verb) {
			std::cout << blue << "The following TH1 will be drawn:" << reset << std::endl;
			std::cout << blue << tab << yMax << tab << "┐" << reset << std::endl;
			std::cout << blue <<    tab << tab << "│" << reset << std::endl;
			std::cout << blue << "y: '" << yTitle << "'" << tab << tab << "│" << reset << std::endl;
			std::cout << blue <<    tab << tab << "│" << reset << std::endl;
			std::cout << blue << tab << yMin << tab << "┼───────────────────────┐" << reset << std::endl;
			std::cout << blue <<   tab << tab << xMin << tab << axes[xAxis] << ": '" << xTitle << "'" << tab << xMax << reset << std::endl;
			std::cout << green << "Press ⏎ to continue…" << reset << std::endl;
			std::cin.ignore();
		}
		
		tTitle = tTitle == "" ? s->GetTitle() : tTitle;
		h->SetTitle(tTitle.c_str());
		
		tmp = fileName + ".dat";
		if (file) std::rename(".output.dat", tmp.c_str());
		
		// set a constant multiplicative factor
		if (xMul != 1) std::cout << yellow << "WARNING :: the x axis is multiplied by the constant factor " << xMul << reset << std::endl;
		if (yMul == leth) std::cout << yellow << "WARNING :: the y axis is multiplied by the leth constant factor" << reset << std::endl;
		else if ((yMul != leth) && (yMul != 1)) std::cout << yellow << "WARNING :: the y axis is multiplied by the constant factor " << yMul << reset << std::endl;
		
		// write the output file if requested
		if (file) fileOutput << "#---" << tab << "xup---------" << tab << "Value-------" << tab << "Stat_err----" << tab << "Rel_err-" << std::endl;
		for (size_t i = 1; i <= h->GetNbinsX(); i++) {
			h->SetBinError(i, h->GetBinError(i)*yMul);		// mctal2root export abs errors before scaling values by yMul
			h->SetBinContent(i, h->GetBinContent(i)*yMul);
			if (file) fileOutput << std::scientific 
			 << std::setfill('0') << std::setw(4) << h->GetBin(i) << tab 
			 << h->GetBinLowEdge(i+1) << tab 
			 << h->GetBinContent(i) << tab 
			 << h->GetBinError(i) << tab;
			if (h->GetBinContent(i) == 0) {
				fileOutput << std::fixed << "0.000000" << std::endl;
			} else {
				fileOutput << std::fixed << h->GetBinError(i)/h->GetBinContent(i) << std::endl;
			}
		}
		
		if (file) std::cout << "Info in <FileOutput::File>: dat file " << tmp.c_str() << " has been created" << std::endl;
		h->Draw("E1 hist");
		save(c, h);
	}
	
	return 0;
}
