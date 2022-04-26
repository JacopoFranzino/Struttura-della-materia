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

  double Count1[] = {};
  double Count2[]={};
  double sV[n];
    double sCount[n];
    double Count[n];
    double err[n];
    for(int j=0;j<n;j++){
      sCount[j]=abs((Count1[j]-Count2[j])/2);
      Count[j]=(Count1[j]+Count2[j])/2;
      err[j]=sCount[j]/Count[j];
      cout<<"Tensione= "<<V[j]<<"V  Numero di conteggi: "<<Count[j]<<" +- "<<sCount[j]<<"  Err rel: "<<err[j]<<endl;
      sV[j]=1;
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
