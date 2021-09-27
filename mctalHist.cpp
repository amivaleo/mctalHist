/*
g++ mctalHist.c `root-config --cflags --ldflags --libs` -o mctalHist
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
		std::cerr << red << "Input file doesn't exist!" << reset << std::endl;
		return 1;
	}
	
	TCanvas *c = generateCanvas();
	
//	if (img) {
//		if (verb) std::cout << blue << "Picture " << imgName << " found" << reset << std::endl;
//		TPad * background = new TPad("background", "background", 0, 0, 1, 1);
//		background->Draw();
//		background->cd();
//		img->Draw();
//		
//		c->cd();
//		TPad * p2 = new TPad("p2", "p2", 0, 0, 1, 1);
//		p2->SetFillStyle(4000);
//		p2->SetFrameFillColor(0);
//		p2->SetFrameFillStyle(0);
//		p2->Draw();
//		p2->cd();
//	}
	
	TFile *file = new TFile(input.c_str());
	THnSparseF *s;
	
	if (tally == "") {
		file->ls();
		do {
			std::cout << green << "Select the THnSparse: " << reset;
			std::cin >> tally;
			s = (THnSparseF *)file->Get(tally.c_str());
		} while (!s);
	} else {
		s = (THnSparseF *)file->Get(tally.c_str());
	}
	
	if (s->GetNdimensions() == 11) {
		std::cout << yellow << "The selected tally is a tmesh" << reset << std::endl;
	}
	
	// print all THnSparse axes if they were not declared in the input bash script
	if ((xAxis == -1) || (zAxis == -1)) {
		s->Print("all");
	}
	
	fileName = fileName == "" ? input.c_str() + tally : fileName;
	
	// =========================================================================
	// MESH --------------------------------------------------------------------
	// =========================================================================
	if (s->GetNdimensions() == 11) {
		
		//           L    R    D    U
		c->SetMargin(0.1, 0.1, 0.1, 0.1);
		
		// select the axis to plot
		if ((zAxis < 0) || (zAxis > 10)) {
			do {
				std::cout << green << "Select the axis perpendicular to the map you are going to plot [f, d, u, s, m, c, e, t, i, j, k]: " << reset;
				std::cin >> tmp;
				zAxis = getAxisIndex(tmp);
			} while ((zAxis < 0) || (zAxis > 10));
			std::cout << std::endl;
		}
		
		// if the axis perpendicular to the map has more than 1 bin, let the user decide what to plot
		if (s->GetAxis(zAxis)->GetNbins() > 1) {

			if ((zMin == -99999) && (zMax == -99999)) {
				std::cout << blue << "The selected axis has " << s->GetAxis(zAxis)->GetNbins() << " bins" << reset << std::endl;
				
				// print all the bins edges for the axis perpendicular to the map
				std::cout << blue << "Bins edges for axis " << axes[zAxis] << ": " << reset;
				for (size_t i = 0; i <= s->GetAxis(zAxis)->GetNbins(); i++) {
					std::cout << blue << s->GetAxis(zAxis)->GetBinUpEdge(i) << "  ";
				}
				std::cout << reset << std::endl;
				
				std::cout << yellow << "Do not select exact bin edge values. If you want to select bin [1, 2], insert 1.001 and 1.999" << reset << std::endl;
				std::cout << yellow << "You can preferentially select one single value in the bin of interest. If you want to select bin [1, 2], you can insert 1.5 and 1.5" << reset << std::endl;
				
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
				} else {
					std::cout << yellow << "⚠ :: all bins will be plotted" << reset << std::endl;
				}
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
			if (verb) std::cout << yellow << "No validation is performed on the inserted values" << reset << std::endl;
		}
		if (yAxis == -1) {
			do {
				std::cout << green << "Select the ordinates axis [f, d, u, s, m, c, e, t, i, j, k]: " << reset;
				std::cin >> tmp;
				yAxis = getAxisIndex(tmp);
			} while ((!yAxis) || (!std::cin) || (yAxis > 10));
			if (verb) std::cout << yellow << "⚠ :: no validation is performed on the inserted values" << reset << std::endl;
		}
		
		if (xLog) {
			gPad->SetLogx();
			if (verb) std::cout << yellow << "Setting log-scale for x axis" << reset << std::endl;
		}
		if (yLog) {
			gPad->SetLogy();
			if (verb) std::cout << yellow << "Setting log-scale for y axis" << reset << std::endl;
		}
		if (zLog) {
			gPad->SetLogz();
			if (verb) std::cout << yellow << "Setting log-scale for z axis" << reset << std::endl;
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
			std::cout << yellow << "The z axis is multiplied by the constant factor " << zMul << reset << std::endl;
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
			fileOutput << "# title: " << tTitle.c_str() << std::endl;
			
			fileOutput << std::setw(20) << std::setfill(' ') << std::left << "# abiscissae axis: " << tab << xAxis;
			if (xMin != xMax) fileOutput << tab <<  "[" << xMin << ", " << xMax << "]";
			if (xMul != 1) fileOutput << tab << "multiplied by " << xMul;
			fileOutput << std::endl;
			
			fileOutput << std::setw(20) << std::setfill(' ') << "# ordinates axis: " << tab << yAxis;
			if (yMin != yMax) fileOutput << tab <<  "[" << yMin << ", " << yMax << "]";
			if (yMul != 1) fileOutput << tab << "multiplied by " << yMul;
			fileOutput << std::endl;
			
			fileOutput << std::setw(20) << std::setfill(' ') << "# perpendicular axis: " << tab << zAxis;
			if (zMin != zMax) fileOutput << tab <<  "[" << zMin << ", " << zMax << "]";
			if (zMul != 1) fileOutput << tab << "multiplied by " << zMul;
			fileOutput << std::endl;
			if (pMin != pMax) fileOutput << "# palette range [" << pMin << ", " << pMax << "]" << std::endl;

			fileOutput << std::setw(12) << std::setfill('-') << std::left << "# value" << std::endl;
			for (Int_t j = 1; j <= h->GetNbinsY(); j++)
				for (Int_t i = 1; i <= h->GetNbinsX(); i++) {
					fileOutput << std::scientific << std::setw(13) << std::setfill(' ') << std::left << h->GetBinContent(h->GetBin(i, j));
					if (i == h->GetNbinsX())
						fileOutput << std::endl;
				}
				
			fileOutput << std::endl;
			
			fileOutput << std::setw(12) << std::setfill('-') << std::left << "# absErr" << std::endl;
			for (Int_t j = 1; j <= h->GetNbinsY(); j++)
				for (Int_t i = 1; i <= h->GetNbinsX(); i++) {
					fileOutput << std::fixed << std::setw(13) << std::setfill(' ') << std::left << h->GetBinError(h->GetBin(i, j)) / h->GetBinContent(h->GetBin(i, j));
					if (i == h->GetNbinsX())
						fileOutput << std::endl;
				}
			
		}
		
		h->DrawCopy("COLZ");
		if (contour.size() > 0) {
			h->SetContour(contour.size(), &contour[0]);
			h->SetLineWidth(1);
			h->SetLineColor(dark);
			h->Draw("cont3 same");
		}
		save(c, h);

		if (projection && constantY != -99999) {
			TH1D *hP = h->ProjectionX("hP", h->GetXaxis()->FindFixBin(constantY), h->GetXaxis()->FindFixBin(constantY));
			
			for (Int_t i = 1; i <= hP->GetNbinsX(); i++)
				std::cout << hP->GetBinContent(i) << tab;
				
			hP->SetLineWidth(1);
//			hP->SetLineColor(dark);
			hP->Draw("HIST E0");
			fileName += "_Xprojection";
			save(c, hP);
		} else if (projection && constantX != -99999) {
			TH1D *hP = h->ProjectionY("hP", h->GetYaxis()->FindFixBin(constantX), h->GetYaxis()->FindFixBin(constantX));
			hP->SetLineWidth(1);
//			hP->SetLineColor(dark);
			hP->Draw("HIST E0");
			fileName += "_Yprojection";
			save(c, hP);
		}
		
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
					} else std::cout << yellow << "All bins will be plotted" << reset << std::endl;
				
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
			if (verb) std::cout << yellow << "Setting log-scale for x axis" << reset << std::endl;
		}
		if (yLog) {
			gPad->SetLogy();
			if (verb) std::cout << yellow << "Setting log-scale for y axis" << reset << std::endl;
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
		
		tTitle = tTitle == "" ? s->GetTitle() : tTitle;
		h->SetTitle(tTitle.c_str());
		
		// set a constant multiplicative factor
		if (xMul != 1) std::cout << yellow << "The x axis is multiplied by the constant factor " << xMul << reset << std::endl;
		if (yMul != 1) std::cout << yellow << "The y axis is multiplied by the constant factor " << yMul << reset << std::endl;
		
		// write the output file if requested
		if (file) {
			fileOutput << "# title: " << tTitle << std::endl;
			fileOutput << std::setw(20) << std::setfill(' ') << "# x axis: " << axes[xAxis] << tab << "Title: " << xTitle << tab << "Range: [" << xMin << ", " << xMax << "] * " << xMul << std::endl;
			fileOutput << std::setw(20) << std::setfill(' ') << "# y axis: " << "Title: " << yTitle << tab << "Range: [" << yMin << ", " << yMax << "] * " << yMul << std::endl;
			fileOutput << std::setw(12) << std::setfill('-') << std::left << "#xup" << tab;
			fileOutput << std::setw(12) << std::setfill('-') << std::left << "value" << tab;
			fileOutput << std::setw(12) << std::setfill('-') << std::left << "absErr" << tab;
			fileOutput << std::setw(12) << std::setfill('-') << std::left << "relErr" << std::endl;
		}
		
		for (size_t i = 1; i <= h->GetNbinsX(); i++) {
			h->SetBinError(i, h->GetBinError(i)*yMul);		// mctal2root export abs errors before scaling values by yMul
			h->SetBinContent(i, h->GetBinContent(i)*yMul);
			if (file) {
				fileOutput << std::scientific;
				fileOutput << h->GetBinLowEdge(i+1) << tab;
				fileOutput << h->GetBinContent(i) << tab;
				fileOutput << h->GetBinError(i) << tab;
				if (h->GetBinContent(i) == 0) {
					fileOutput << std::fixed << "0.000000" << std::endl;
				} else {
					fileOutput << std::fixed << h->GetBinError(i)/h->GetBinContent(i) << std::endl;
				}
			}
		}
		
		if (file) {
			std::cout << "Info in <FileOutput::File>: dat file " << tmp.c_str() << " has been created" << std::endl;
		}
		
		h->Draw("E1 hist");
		save(c, h);
	}
	
	return 0;
}
