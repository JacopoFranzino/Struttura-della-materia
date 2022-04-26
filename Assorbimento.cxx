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
  gStyle->SetOptFit(1);
  const int n=;
  double Count1[] ={};
  double Count2[]={};
  double x[] ={};
  double I[n];
  double sx[n];
  double sI[n];
  double ER[n];
  for(int j=0;j<n;j++){
    sx[j];
    sI[j]=abs((Count1[j]-Count2[j])/2);
    I[j]=(Count1[j]+Count2[j])/2;
    ER[j]=sI[j]/I[j];
    cout<<"Spessore= "<<x[j]<<"mm  Intensità: "<<I[j]<<" +- "<<sI[j]<<"  Err rel: "<<ER[j]<<endl;
  }
  

 
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
    funz1->SetParNames("I0", "mu");
    funz1->SetLineColor(50);
    //funz1->SetParameters();
    C1->Update();
    gGraph->Fit(funz1, "RM+");
    //string udm[] = {"", "", ""};
    double I0= funz1->GetParameter(0);
    double sI0=funz1->GetParError(0);
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
    funz3->SetRange(,);  //impostare il range
    //funz1->SetParameters();
    C3->Update();
    gGraph3->Fit(funz3, "RM+");
        //string udm[] = {"", "", ""};
    // double e= funz3->GetParameter(0);
    //double se=funz3->GetParError(0);
    //double f= funz3->GetParameter(1);
    //double sf=funz3->GetParError(1);

   cout << "Chi^2:" << funz3->GetChisquare() << ", number of DoF: " << funz3->GetNDF() << " (Probability: " << funz3->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    //.........................//
    TF1 *funz4 = new TF1("funz4", "[0]+[1]*x", 0, 20);
    funz4->SetParName(0,"c");
    funz4->SetParName(1,"d");
    funz4->SetLineColor(7);
    funz4->SetRange(,); //impostare il range
    //funz1->SetParameters();
    C3->Update();
    gGraph3->Fit(funz4, "RM+");
    //string udm[] = {"", "", ""};
    //double g= funz4->GetParameter(2);
    //double sg=funz4->GetParError(2);
    //double h= funz4->GetParameter(3);
    //double sh=funz4->GetParError(3);

   cout << "Chi^2:" << funz4->GetChisquare() << ", number of DoF: " << funz4->GetNDF() << " (Probability: " << funz4->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    //.........................//

    //TLegend* legend = new TLegend(0.49,0.71,0.89,0.85);
    //legend->AddEntry(funz3,"Spessore maggiore di ","l");
    //legend->AddEntry(funz4,"Spessore minore di ","l");
    //legend->Draw();


    
    
    
   
}
