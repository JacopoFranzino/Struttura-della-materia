#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <iomanip>
#include <cmath>
using namespace std;

void IntensitaSoglia()
{
   const int n=;
   double I[] = {};
   double Count1[] = {};
   double Count2[]={};
   double Count[n];
   double err[n];
   double sI[n];
   double sCount[n];
   for(int j=0;j<n;j++){
     sCount[j]=abs((Count1[j]-Count2[j])/2);
      Count[j]=(Count1[j]+Count2[j])/2;
      err[j]=sCount[j]/Count[j];
      cout<<"Intensità= "<<I[j]<<"microA  Numero di conteggi: "<<Count[j]<<" +- "<<sCount[j]<<"  Err rel: "<<err[j]<<endl;
      sI[j]=1;
    }

    // ----------------------------------------------------------------- //
    // Canvas

    TCanvas *Canvas1 = new TCanvas("Canvas1", "Y(X)", 2000, 1000);
    Canvas1->SetFillColor(0);
    Canvas1->cd(1);
    gStyle->SetOptStat(10);
    gStyle->SetOptFit(111);
    
    TGraphErrors *gGraph = new TGraphErrors(n, I, Count, sI, sCount);
    gGraph->SetMarkerSize(0.6);
    gGraph->SetMarkerStyle(21);
    gGraph->SetTitle("Count(DeltaV)");
    gGraph->GetXaxis()->SetTitle("DeltaV ");
    gGraph->GetYaxis()->SetTitle("Count ");
    gGraph->Draw("AP");
}

