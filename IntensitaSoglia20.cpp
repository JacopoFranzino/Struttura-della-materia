#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <iomanip>
#include <cmath>
using namespace std;

void IntensitaSoglia20()
{
   const int n=22;
   double V[]={0.002,0.010,0.019,0.023,0.029,0.038,0.045,0.057,0.064,0.077,0.090,0.108,0.155,0.194,0.30,0.408,0.503,0.609,0.716,0.815,0.907,1.025};
   double sV[n];
   double I[n];
   double Count1[]={2301,9111,16110,18623,23168,28429,31969,37491,40464,45089,48268,51121,54345,54819,56626,60668,64061,66634,69295,70899,72194,74292};
   double Count2[]={2234,9100,15757,18156,22928,28428,32248,37811,40296,45165,48445,50638,54260,54965,56474,60529,63752,67038,69495,71290,72813,74580};
   double Count[n];
   double err[n];
   double sI[n];
   double sCount[n];
   for(int j=0;j<n;j++){
     sV[j]=0.001;
     I[j]=V[j]*10;
     Count1[j]=Count1[j]/20;
     Count2[j]=Count2[j]/20;
     sCount[j]=abs((Count1[j]-Count2[j])/2);
      Count[j]=(Count1[j]+Count2[j])/2;
      err[j]=sCount[j]/Count[j];
      cout<<"Intensità= "<<I[j]<<"microA  Numero di conteggi: "<<Count[j]<<" +- "<<sCount[j]<<"  Err rel: "<<err[j]<<endl;
      sI[j]=sV[j]*10;
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
    TF1 *funz1 = new TF1("funz1", "[0]+[1]*x", 0, 20);
    //funz2->SetParNames("a", "b");
    funz1->SetLineColor(50);
    funz1->SetRange(5,12);
    //funz1->SetParameters();
    Canvas1->Update();
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
    funz2->SetRange(0,1);
    //funz1->SetParameters();
    Canvas1->Update();
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
