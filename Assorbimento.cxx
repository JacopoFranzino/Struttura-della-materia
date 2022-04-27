#include <iostream>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TF1.h>
#include <iomanip>
#include <cmath>
using namespace std;

void Assorbimento()
{
  //Intensità 0.81 microA 
  const int n=19;
  double s[]={20,20,20,20,20,20,20,20,20,20,20,20,30,40,40,40,60,80,80};
  double Count1[]={62542,39627,15168,9827,6769,5446,4488,3836,3097,2847,2465,2183,2856,3456,3023,2442,2563,2345,1906};
  double Count2[]={62443,40030,15215,9921,6748,5545,4255,3881,3080,2886,2445,2236,2866,3447,3074,2478,2721,2422,1879};
  double x[] ={0,0.1,0.25,0.35,0.5,0.6,0.75,0.85,1,1.10,1.25,1.35,1.50,1.60,1.75,2,2.5,3,3.5}; // espressi in mm
  double sx[n];
  double I[n];
  double sI[n];
  double ER[n];
  for(int j=0;j<n;j++){
    sx[j]=0.01;
    Count1[j]=Count1[j]/s[j];
    Count2[j]=Count2[j]/s[j];
    sI[j]=abs((Count1[j]-Count2[j])/2);
    I[j]=(Count1[j]+Count2[j])/2;
    ER[j]=sI[j]/I[j];
    cout<<"Spessore= "<<x[j]<<"mm  Intensità: "<<I[j]<<" +- "<<sI[j]<<"  Err rel: "<<ER[j]<<endl;
  }

  double I0=(Count1[0]+Count2[0])/2;
  double sI0=(Count1[0]-Count2[0])/2;
  

 
    // ----------------------------------------------------------------- //
    //Esponenziale//
    // Canvas

    TCanvas *C1 = new TCanvas("C1", "Esponenziale", 2000, 1000);
    C1->SetFillColor(0);
    C1->cd(1);
    
   TGraphErrors *gGraph = new TGraphErrors(n, x, I, sx, sI);
    gGraph->SetMarkerSize(0.6);
    gGraph->SetMarkerStyle(21);
    gGraph->SetTitle("I(x)");
    gGraph->GetXaxis()->SetTitle("spessore ");
    gGraph->GetYaxis()->SetTitle("Intensita' ");
    gGraph->Draw("AP");
    
    // ----------------------------------------------------------------- //
    // Fit 1
    cout << "\n\n --- Ipotesi  [0]*exp(-[1]*x) --- \n"
         << endl;
    TF1 *funz1 = new TF1("funz1", "[0]*exp(-[1]*x)", 0, 20);
    funz1->SetRange(0.1,0.5);
    funz1->SetParNames("I0", "mu");
    funz1->SetLineColor(50);
    funz1->SetParameters(0,62500);
    funz1->SetParameters(1,1.5);
    C1->Update();
    gGraph->Fit(funz1, "RM+");
    //string udm[] = {"", "", ""};
    //double I0= funz1->GetParameter(0);
    //double sI0=funz1->GetParError(0);
    //double b= funz1->GetParameter(1);
    //double sb=funz1->GetParError(1);

    cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    //.........................//

 double y[n];
   double sy[n];
     for(int j=0;j<n;j++){
       y[j]=log(I0/I[j]);
       sy[j]=sI[j]/I[j];
     }


    //Lineare//
    
     
    TCanvas *C2 = new TCanvas("C2", "Lineare", 2000, 1000);
    C2->SetFillColor(0);
    C2->cd(1);

    TGraphErrors *gGraph2 = new TGraphErrors(n, x, y, sx, sy);
    gGraph2->SetMarkerSize(0.6);
    gGraph2->SetMarkerStyle(21);
    gGraph2->SetTitle("I(x)");
    gGraph2->GetXaxis()->SetTitle("spessore  ");
    gGraph2->GetYaxis()->SetTitle("Intensita' ");
    gGraph2->Draw("AP");

    // ----------------------------------------------------------------- //
    // Fit 2
    cout << "\n\n --- Ipotesi  [0]+[1]*x) --- \n"
       << endl;
    TF1 *funz2 = new TF1("funz2", "[0]+[1]*x", 0, 20);
    funz2->SetParNames("a", "b");
    funz2->SetLineColor(50);
    //funz1->SetParameters();
    C2->Update();
    gGraph2->Fit(funz2, "RM+");
    //string udm[] = {"", "", ""};
    // double c= funz2->GetParameter(0);
    //double sc=funz2->GetParError(0);
    //double d= funz2->GetParameter(1);
    //double sd=funz2->GetParError(1);

   cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    //.........................//



    //due rette//
     TCanvas *C3 = new TCanvas("C3", "Due rette", 2000, 1000);
    C3->SetFillColor(0);
    C3->cd(1);
    // ----------------------------------------------------------------- //
     TGraphErrors *gGraph3 = new TGraphErrors(n, x, y, sx, sy);
    gGraph3->SetMarkerSize(0.6);
    gGraph3->SetMarkerStyle(21);
    gGraph3->SetTitle("I(x)");
    gGraph3->GetXaxis()->SetTitle("spessore  ");
    gGraph3->GetYaxis()->SetTitle("Intensita' ");
    gGraph3->Draw("AP");
    // Fit 3

    cout << "\n\n --- Ipotesi  [0]+[1]*x --- \n"
       << endl;
    TF1 *funz3 = new TF1("funz3", "[0]+[1]*x", 0, 20);
    funz3->SetParNames("a", "b");
    funz3->SetLineColor(3);
    funz3->SetRange(0.1,0.5);  //impostare il range
    //funz1->SetParameters();
    C3->Update();
    gGraph3->Fit(funz3, "RM+");
        //string udm[] = {"", "", ""};
    // double e= funz3->GetParameter(0);
    //double se=funz3->GetParError(0);
    double mu1= funz3->GetParameter(1);
    //double sf=funz3->GetParError(1);

   cout << "Chi^2:" << funz3->GetChisquare() << ", number of DoF: " << funz3->GetNDF() << " (Probability: " << funz3->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    //.........................//
    TF1 *funz4 = new TF1("funz4", "[0]+[1]*x", 0, 20);
    funz4->SetParName(0,"c");
    funz4->SetParName(1,"d");
    funz4->SetLineColor(7);
     funz4->SetRange(1.6,4); //impostare il range
    //funz1->SetParameters();
    C3->Update();
    gGraph3->Fit(funz4, "RM+");
    //string udm[] = {"", "", ""};
    //double g= funz4->GetParameter(2);
    //double sg=funz4->GetParError(2);
    double mu2= funz4->GetParameter(1);
    //double sh=funz4->GetParError(3);

   cout << "Chi^2:" << funz4->GetChisquare() << ", number of DoF: " << funz4->GetNDF() << " (Probability: " << funz4->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    //.........................//


    
    
   
}
