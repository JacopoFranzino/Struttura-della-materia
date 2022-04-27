#include <iostream>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <iomanip>
#include <cmath>
using namespace std;

void TensioneSoglia20()
{
  //Intensità di soglia 82mV
  //V impostata 43mv mV quindi circa 0.43 microA  
  //Tempo di acquisizione 20s
  const int n=41;
  double V[] = {390,392,394,397,399,402,404,406,409,411,413,415,418,421,423,425,428,430,432,435,437,440,442,444,447,449,451,454,456,459,461,463,466,471,473,478,482,487,492,501,511};
  double Count1[]={7683,8284,9654,10286,11415,11982,12701,13219,14128,14525,15204,15813,16521,17253,17902,18227,19029,19710,20699,21681,22933,23985,25152,25940,26732,27538,28242,28559,29250,29510,29650,29933,29876,30097,30301,30655,31056,31037,31221,31193,31326,31486};
  double Count2[]={7098,8540,9734,10356,11411,11938,12663,13273,14250,14471,15194,15982,16635,17244,17384,18264,18971,19826,20602,21574,22692,23984,25050,25989,26792,27630,28288,28648,28988,29460,29704,30114,30034,30390,30756,30549,30992,31258,31024,31317,31434,31626};
  double sV[n];
    double sCount[n];
    double Count[n];
    double err[n];
    for(int j=0;j<n;j++){
      Count1[j]=Count1[j]/20;
      Count2[j]=Count2[j]/20;
      sCount[j]=abs((Count1[j]-Count2[j])/2);
      Count[j]=((Count1[j]+Count2[j])/2);
      err[j]=sCount[j]/Count[j];
      cout<<"Tensione= "<<V[j]<<"V  Numero di conteggi: "<<Count[j]<<" +- "<<sCount[j]<<"  Err rel: "<<err[j]<<endl;
      sV[j]=1;
    }

    // ----------------------------------------------------------------- //
    // Canvas

    TCanvas *Canvas = new TCanvas("Canvas", "Y(X)", 2000, 1000);
    Canvas->SetFillColor(0);
    Canvas->cd(1);
    
    TGraphErrors *gGraph = new TGraphErrors(n, V, Count, sV, sCount);
    gGraph->SetMarkerSize(0.6);
    gGraph->SetMarkerStyle(21);
    //gGraph->SetX(0);
    gGraph->SetTitle("Count(DeltaV)");
    gGraph->GetXaxis()->SetTitle("DeltaV ");
    
    gGraph->GetYaxis()->SetTitle("Count ");
    gGraph->Draw("AP");

    TF1 *funz1 = new TF1("funz1", "[0]+[1]*x", 0, 20);
    //funz2->SetParNames("a", "b");
    funz1->SetLineColor(50);
    funz1->SetRange(472,560);
    //funz1->SetParameters();
    Canvas->Update();
    gGraph->Fit(funz1, "RM+");
    //string udm[] = {"", "", ""};
     double a= funz1->GetParameter(0);
    //double sc=funz2->GetParError(0);
    double b= funz1->GetParameter(1);
    //double sd=funz2->GetParError(1);

   cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    //.........................//


    TF1 *funz2 = new TF1("funz2", "[0]+[1]*x", 0, 20);
    //funz3->SetParNames("c", "d");
    funz2->SetLineColor(9);
    funz2->SetRange(390,460);
    //funz1->SetParameters();
    Canvas->Update();
    gGraph->Fit(funz2, "RM+");
    //string udm[] = {"", "", ""};
    double c= funz2->GetParameter(0);
    //double sc=funz2->GetParError(0);
    double d= funz2->GetParameter(1);
    //double sd=funz2->GetParError(1);

   cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    //.........................//

    double Vs=abs((c-a)/(b-d));
    cout<<"Tensione soglia: "<<Vs<<"V"<<endl;
}
