#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

#include <TCanvas.h>
#include <TGraph.h>
#include <TMath.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TMarker.h>
#include <TLatex.h>
#include <TColor.h>

void bethe_bloch_all() {
  gStyle->SetOptStat(0);

  // === Silicon parameters ===
  double Z = 14, A = 28;
  double I = 173e-6;
  double rho = 2.3290;
  double x0 = 0.2014, x1 = 2.8715;
  double a = 0.14921, delta0 = 0.14;
  double C = 4.4351, k = 3.2546;

  // === Global constants ===
  double K = 0.307075;
  double z = -1;
  double me = 0.511;
  double h_w = 28.816 * sqrt(rho * Z / A) * 1e-6;

  // === Particles: name and mass in MeV ===
  std::vector<std::pair<std::string, double>> particles = {
    {"muon", 105.6},
    {"pion", 139.57},
    {"kaon", 493.68},
    {"proton", 938.0}
  };

  TCanvas* c1 = new TCanvas("c1", "Bethe-Bloch All Particles", 900, 700);
  c1->SetLogx();
  c1->SetLogy();
  c1->SetGrid();

  TLegend* leg = new TLegend(0.5, 0.65, 0.88, 0.85);
  leg->SetBorderSize(1);
  leg->SetFillColor(kWhite);
  leg->SetTextFont(82);
  leg->SetTextSize(0.04);
  leg->SetMargin(0.1);


  leg->SetHeader("Bethe-Bloch in Silicon");

  std::vector<int> colors = {kRed + 1, kBlue + 1, kGreen + 2, kMagenta + 2};

  for (size_t ipart = 0; ipart < particles.size(); ++ipart) {
    std::string name = particles[ipart].first;
    double M = particles[ipart].second;

    double a1 = K * z * z * Z / A;

    std::vector<double> beta, gamma, beta_gamma, Tmax, delta, dedx;

    double step = pow(10, -5);
    for (double b = 0.1; b < 1.0 - step; b += step) {
      double g = 1.0 / sqrt(1 - b * b);
      double bg = b * g;

      double tmax = 2 * me * bg * bg / (1 + 2 * g * me / M + pow(me / M, 2));
      double x = log10(bg);
      double delta_i;
      if (x > x1)
        delta_i = 2 * log(10) * x - C;
      else if (x >= x0)
        delta_i = 2 * log(10) * x - C + a * pow(x1 - x, k);
      else
        delta_i = delta0 * pow(10, 2 * (x - x0));

      double dedx_i = a1 / (b * b) * (0.5 * log(2 * me * bg * bg * tmax / (I * I)) - b * b - 0.5 * delta_i);

      beta_gamma.push_back(bg);
      dedx.push_back(dedx_i);
    }

    // Create TGraph
    TGraph* gr = new TGraph(beta_gamma.size(), &beta_gamma[0], &dedx[0]);
    gr->SetLineColor(colors[ipart % colors.size()]);
    gr->SetLineWidth(2);
    gr->SetTitle("");

      // Axes
    TAxis* ax = gr->GetXaxis();
    TAxis* ay = gr->GetYaxis();
    ax->SetTitle("#beta#gamma");
    ay->SetTitle("<-dE/dx> [MeV.g^{-1}.cm^{2}]");

    gPad->Modified();
    ax->SetTitleSize(0.045);
    ay->SetTitleSize(0.045);
    ax->SetTitleFont(82);
    ay->SetTitleFont(82);
    ax->SetTitleOffset(1.);
    ay->SetTitleOffset(1.);

    gr->Draw(ipart == 0 ? "AL" : "L SAME");
    leg->AddEntry(gr, name.c_str(), "l");

    // Mark minimum
    auto min_it = std::min_element(dedx.begin(), dedx.end());
    int idx = std::distance(dedx.begin(), min_it);
    double min_bg = beta_gamma[idx];
    double min_dedx = dedx[idx];

    TMarker* mark = new TMarker(min_bg, min_dedx, 20);
    mark->SetMarkerColor(colors[ipart % colors.size()]);
    mark->SetMarkerSize(1.5);
    mark->Draw();
  }



//   // Title
//   TLatex latex;
//   latex.SetTextSize(0.04);
//   latex.DrawLatexNDC(0.15, 0.94, "Bethe-Bloch in Silicon");

  // Legend and save
  leg->Draw();
  c1->SaveAs("bethebloch_allparticles.pdf");
}
