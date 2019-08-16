/*
g++ mctalHist.c `root-config --cflags --ldflags --libs` -o mctalHist && mv mctalHist ~/.local/bin
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <getopt.h>
#include <limits>

#include "inc/libraries.h"
#include "inc/variables.h"
#include "inc/functions.h"
#include "inc/help.h"

int main (int argc, char** argv) {
	std::string tmp;
	std::string input = ProcessArgs(argc, argv);
	
	if (!fileExist(input.c_str())) {
		std::cerr << red << "ERROR :: input file doesn't exist!" << reset << std::endl;
		return 1;
	}
	
	TCanvas * c = generateCanvas();
	// use a background image if available
	if (img) {
		TPad * background = new TPad("background", "background", 0.1, 0.1, .9, .9);
		background->Draw();
		background->cd();
		img->Draw();

		c->cd();
		TPad * p2 = new TPad("p2", "p2", 0., 0., 1., 1.);
		p2->SetFillStyle(4000);
		p2->SetFrameFillColor(0);
		p2->SetFrameFillStyle(0);
		p2->Draw();
		p2->cd();
	}
	gStyle->SetOptStat(0);
	
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
	
	fileName = fileName == "" ? tally : fileName;
	
	// MESH --------------------------------------------------------------------
	if (s->GetNdimensions() == 11) {
		
		// select the axis to plot
		while ((zAxis < 0) || (zAxis > 10)) {
			std::cout << green << "Select the axis perpendicular to the map you are going to plot [f, d, u, s, m, c, e, t, i, j, k]: " << reset;
			std::cin >> tmp;
			zAxis = getAxisIndex(tmp);
		}
		std::cout << std::endl;
		
		// if the axis perpendicular to the map has more than 1 bin, let the user decide what to plot
		if (s->GetAxis(zAxis)->GetNbins() > 1) {

			if ((zMin == -99999) && (zMax == -99999)) {
				std::cout << blue << tab << "The selected axis has " << s->GetAxis(zAxis)->GetNbins() << " bins." << reset << std::endl;
				
				// print all the bins edges for the axis perpendicular to the map
				std::cout << blue << tab << "Bins edges for axis " << axes[zAxis] << ": " << reset;
				for (size_t i = 0; i <= s->GetAxis(zAxis)->GetNbins(); i++) std::cout << blue << s->GetAxis(zAxis)->GetBinUpEdge(i) << reset << "  ";
				std::cout << std::endl;
				
				std::cout << yellow << "WARNING :: do not select exact bin edge values. If you want to select bin [1, 2], insert 1.001 and 1.999" << reset << std::endl;
				std::cout << yellow << tab << "You can preferentially select one single value in the bin of interest. If you want to select bin [1, 2], you can insert 1.5 and 1.5" << reset << std::endl;
				
				// let the user select to sum all bins content or not
				std::cout << green << "Select the low edge [a :: all bins]: " << reset;
				std::cin >> tmp;
				
				if (tmp != "a") {
					zMin = std::stod(tmp);
					std::cout << green << "Select the up edge: " << reset;
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
			if (verb) std::cout << yellow << "WARNING :: no validation is performed on the inserted values" << reset << std::endl;
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
		if (zLog) {
			gPad->SetLogz();
			if (verb) std::cout << yellow << "WARNING :: setting log-scale for z axis" << reset << std::endl;
		}
		
		if ((xMin == -99999) && (xMax = -99999)) {
			xMin = s->GetAxis(xAxis)->GetBinLowEdge(s->GetAxis(xAxis)->GetFirst());
			xMax = s->GetAxis(xAxis)->GetBinUpEdge(s->GetAxis(yAxis)->GetLast());
		} else {
			std::cout << blue << "User defined range for the x axis: [" << xMin << "; " << xMax << "]" << reset << std::endl;
			s->GetAxis(xAxis)->SetRangeUser(xMin, xMax);
		}
		
		if ((yMin == -99999) && (yMax = -99999)) {
			yMin = s->GetAxis(yAxis)->GetBinLowEdge(s->GetAxis(yAxis)->GetFirst());
			yMax = s->GetAxis(yAxis)->GetBinUpEdge(s->GetAxis(yAxis)->GetLast());
		} else {
			std::cout << blue << "User defined range for the y axis: [" << yMin << "; " << yMax << "]" << reset << std::endl;
			s->GetAxis(yAxis)->SetRangeUser(yMin, yMax);
		}
		
		TH2D * h = (TH2D *)s->Projection(yAxis, xAxis)->Clone(fileName.c_str());
		customizeHist(h);
		
		h->SetTitle(tTitle.c_str());
		
		// set a constant multiplicative factor
		if (zMul != 1) {
			std::cout << yellow << "WARNING :: the z axis is multiplied by the constant factor " << zMul << reset << std::endl;
			h->Scale(zMul);
		}
		
		if (error)
			for (Int_t i = 1; i <= h->GetNbinsX(); i++)
				for (Int_t j = 1; j <= h->GetNbinsY(); j++)
					h->SetBinContent(i, j, h->GetBinError(h->GetBin(i, j)) / h->GetBinContent(h->GetBin(i, j)));
			
		// change palette range
		if (pMin != pMax) {
			h->GetZaxis()->SetRangeUser(pMin, pMax);
			if (verb) std::cout << blue << std::scientific << "User defined range for the palette: [" << pMin << ", " << pMax << "]" << reset << std::endl;
		}
		
		// write the output file if requested // this must be ameliorated
		if (file) {
			fileOutput << "# " << tTitle.c_str() << std::endl;
			
			fileOutput << "# abiscissae axis: " << tab << xAxis;
			if (xMin != xMax) fileOutput << tab <<  "[" << xMin << ", " << xMax << "]";
			if (xMul != 1) fileOutput << tab << "multiplied by " << xMul;
			fileOutput << std::endl;
			
			fileOutput << "# ordinates axis: " << tab << yAxis;
			if (yMin != yMax) fileOutput << tab <<  "[" << yMin << ", " << yMax << "]";
			if (yMul != 1) fileOutput << tab << "multiplied by " << yMul;
			fileOutput << std::endl;
			
			fileOutput << "# perpendicular axis: " << tab << zAxis;
			if (zMin != zMax) fileOutput << tab <<  "[" << zMin << ", " << zMax << "]";
			if (zMul != 1) fileOutput << tab << "multiplied by " << zMul;
			fileOutput << std::endl;
			if (pMin != pMax) fileOutput << "# palette range [" << pMin << ", " << pMax << "]" << std::endl;
		}
		if (file) fileOutput << std::setw(12) << std::setfill('-') << std::left << "#" << tab << std::setw(12) << std::setfill('-') << std::left << "Value" << tab << std::setw(12) << std::setfill('-') << std::left << "AbsErr" << std::endl;
		
//		if (pMax == pMin) {
//			pMax = h->GetMaximum();
//			pMin = h->GetMinimum();
//		}
//		Double_t vCut = 1.5;
//		Double_t pCut = (vCut - pMin)/(pMax - pMin);
//		
//		std::cout << "asdas " << pCut << std::endl;
//		
//		const Int_t N = 4;
//		const Int_t NCont = 800;
//		Double_t R[N] = {0.00, 0.00, 0.20, 1.00};
//		Double_t G[N] = {1.00, 0.20, 0.00, 0.00};
//		Double_t B[N] = {0.00, 0.00, 0.00, 0.00};
//		Double_t s[N] = {0.00, pCut, pCut + 0.0001, 1.00};
//		
//		TColor::CreateGradientColorTable(N, s, R, G, B, NCont);
//		gStyle->SetNumberContours(NCont);
		
		h->SetMarkerSize(0.5);
		gStyle->SetTextSize(0.08);
		h->DrawCopy("colz");
		
		if (contour.size() > 0) {
			h->SetContour(contour.size(), &contour[0]);
			h->SetLineWidth(1);
			h->SetLineColor(dark);
			h->Draw("cont3 same");
		}
		
		save(c, h);
		
	// =========================================================================
	} else {	// TALLY -------------------------------------------------------
	// =========================================================================
		
		double bin;

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
				std::cout << blue << "Axis " << axes[i] << " has " << s->GetAxis(i)->GetNbins() << " bins" << reset;
				
				if (axesBin[i] == 0) {
					std::cout << std::endl;
					std::cout << green << tab << "Select the bin for the " << axes[i] << " axis [a :: all bins] [1-" << s->GetAxis(i)->GetNbins() << "]: " << reset;
					std::cin >> tmp;
				
					if (tmp != "a") {
						bin = std::stoi(tmp);
						fileName += to_string(bin);
						s->GetAxis(i)->SetRange(bin, bin);
					} else std::cout << yellow << "WARNING :: all bins will be plotted" << reset << std::endl;
				
				} else {
					fileName += to_string(axesBin[i]);
					s->GetAxis(i)->SetRange(axesBin[i], axesBin[i]);
					std::cout << blue << ". Selected bin " << axesBin[i] << reset << std::endl;
				}
			}
		}
		
		TH1D * h = (TH1D *)s->Projection(xAxis)->Clone(fileName.c_str());
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
		if ((xMin == -99999) && (xMax = -99999)) {
			xMin = h->GetXaxis()->GetBinUpEdge(h->GetXaxis()->GetFirst());
			xMax = h->GetXaxis()->GetBinUpEdge(h->GetXaxis()->GetLast());
		} else {
			std::cout << blue << "User defined range for the x axis: [" << xMin << "; " << xMax << "]" << reset << std::endl;
			h->GetXaxis()->SetRangeUser(xMin, xMax);
		}
		
		if ((yMin == -99999) && (yMax = -99999)) {
			yMin = h->GetYaxis()->GetBinLowEdge(h->GetYaxis()->GetFirst());
			yMax = h->GetYaxis()->GetBinUpEdge(h->GetYaxis()->GetLast());
		} else {
			std::cout << blue << "User defined range for the y axis: [" << yMin << "; " << yMax << "]" << reset << std::endl;
			h->GetYaxis()->SetRangeUser(yMin, yMax);
		}
		
		if (verb) {
			std::cout << blue << "The following TH1 will be drawn:" << reset << std::endl;
			std::cout << blue << std::setw(5) << std::right << " "  << "y: '" << yTitle << "'" << reset << std::endl;
			std::cout << blue << std::setw(5) << std::right << yMax << "┐" << reset << std::endl;
			std::cout << blue << std::setw(5) << std::right << " "  << "│" << reset << std::endl;
			std::cout << blue << std::setw(5) << std::right << " "  << "│" << reset << std::endl;
			std::cout << blue << std::setw(5) << std::right << yMin << "┼─────────┐" << tab << "x: '" << xTitle << "'" << reset << std::endl;
			std::cout << blue << std::setw(5) << std::right << " " << std::setw(10) << std::left << xMin << xMax << reset << std::endl;
		}
		
		tTitle = tTitle == "" ? s->GetTitle() : tTitle;
		h->SetTitle(tTitle.c_str());
		
		// set a constant multiplicative factor
		if (xMul != 1) std::cout << yellow << "WARNING :: the x axis is multiplied by the constant factor " << xMul << reset << std::endl;
		if (yMul == leth) std::cout << yellow << "WARNING :: the y axis is multiplied by the leth constant factor" << reset << std::endl;
		else if ((yMul != leth) && (yMul != 1)) std::cout << yellow << "WARNING :: the y axis is multiplied by the constant factor " << yMul << reset << std::endl;
		
		// write the output file if requested
		if (file) fileOutput << "# Title: " << tTitle << std::endl;
		if (file) fileOutput << "# x axis: " << axes[xAxis] << tab << "Title: " << xTitle << tab << "Range: [" << xMin << ", " << xMax << "] * " << xMul << std::endl;
		if (file) fileOutput << "# y axis: " << tab << "Title: " << yTitle << tab << "Range: [" << yMin << ", " << yMax << "] * " << yMul << std::endl;
		if (file) fileOutput << std::setw(12) << std::setfill('-') << std::left << "#xup" << tab << std::setw(12) << std::setfill('-') << std::left << "Value" << tab << std::setw(12) << std::setfill('-') << std::left << "AbsErr" << tab << std::setw(12) << std::setfill('-') << std::left << "RelErr" << std::endl;
		for (size_t i = 1; i <= h->GetNbinsX(); i++) {
			h->SetBinError(i, h->GetBinError(i)*yMul);		// mctal2root export abs errors before scaling values by yMul
			h->SetBinContent(i, h->GetBinContent(i)*yMul);
			if (file) fileOutput << std::scientific 
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
	
	if (file) std::rename(".output.dat", (fileName + ".dat").c_str());
	if (file) fileOutput.close();
	
	return 0;
}
