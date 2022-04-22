#include <iostream>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <iomanip>
#include <cmath>
using namespace std;

void TensioneSoglia()
{
  const int n=;
  double V[] = {};

  double Count[] = {};
  double sV[n];
    double sCount[n];
    for(int j=0;j<n;j++){
      sCount[j]=sqrt(Count[j]);
    }

    // ----------------------------------------------------------------- //
    // Canvas

    TCanvas *Canvas = new TCanvas("Canvas", "Y(X)", 2000, 1000);
    Canvas->SetFillColor(0);
    Canvas->cd(1);
    gStyle->SetOptStat(10);
    gStyle->SetOptFit(111);
    
    TGraphErrors *gGraph = new TGraphErrors(n, V, Count, sV, sCount);
    gGraph->SetMarkerSize(0.6);
    gGraph->SetMarkerStyle(21);
    gGraph->SetTitle("Count(DeltaV)");
    gGraph->GetXaxis()->SetTitle("DeltaV ");
    gGraph->GetYaxis()->SetTitle("Count ");
    gGraph->Draw("AP");
}
