#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <iomanip>
#include <cmath>
using namespace std;

void IntensitaSoglia30()
{
  //HV=485V
  //Soglia 62mV
   const int n=21;
   double V[]={0.0108,0.017,0.021,0.026,0.031,0.041,0.046,0.052,0.068,0.081,0.104,0.143,0.193,0.252,0.300,0.405,0.503,0.604,0.765,0.930,1.120};
   double sV[n];
   double I[n];
   double Count1[]={19039,28585,32985,38591,44188,50807,54155,56376,61273,62999,64567,65929,69205,72903,76625,81350,84335,85903,87203,88072,88119};
   double Count2[]={19092,28452,33078,38233,44111,50694,54347,56411,61059,62880,64388,65924,68966,73062,76630,81595,84329,86047,87354,88027,88232};
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


