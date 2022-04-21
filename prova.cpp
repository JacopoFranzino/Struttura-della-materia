#include <iostream>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TF1.h>
#include <iomanip>
#include <cmath>
using namespace std;

void prova()
{
  double X[] = {};
    double Y[] = {};
    double sigX[] = {};
    double sigY[] = {};

    // ----------------------------------------------------------------- //
    // Canvas

    TCanvas *Canvas = new TCanvas("Canvas", "Y(X)", 2000, 1000);
    Canvas->SetFillColor(0);
    Canvas->cd(1);
    gStyle->SetOptStat(10);
    gStyle->SetOptFit(111);
    
    TGraphErrors *gGraph = new TGraphErrors(4, X, Y, sigX, sigY);
    gGraph->SetMarkerSize(0.6);
    gGraph->SetMarkerStyle(21);
    gGraph->SetTitle("Y(X)");
    gGraph->GetXaxis()->SetTitle(" ");
    gGraph->GetYaxis()->SetTitle(" ");
    gGraph->Draw("AP");

    // ----------------------------------------------------------------- //
    // Fit 1
    cout << "\n\n --- Ipotesi  [0]+[1]*x --- \n"
         << endl;
    TF1 *funz1 = new TF1("funz1", "[0]+[1]*x", 0, 10);
    funz1->SetParNames("a", "b");
    funz1->SetLineColor(50);
    //funz1->SetParameters();
    Canvas->Update();
    gGraph->Fit(funz1, "RM+");
    string udm[] = {"", "", ""};
    double a= funz1->GetParameter(0);
    double sa=funz1->GetParError(0);

    cout << "Chi^2:" << funz1->GetChisquare() << ", number of DoF: " << funz1->GetNDF() << " (Probability: " << funz1->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    //.........................//
   
}

//const int nmisure=189;
//Char_t filnamres[189];
//sprintf(filnamres,"Americio.txt"); // nome del file che contiene i dati
//FILE *input = fopen(filnamres, "r" ); // apertura file in input
//Float_t nCHN=0;
//Float_t nCount=0; 
//double CHN[nmisure]; 
//double Count[nmisure];
//Int_t npoints=0;
//if(!input) {
//    cerr << "Error: file could not be opened" << endl;
//    exit(1);
//}
  //inizio lettura file di input
  //  while(!feof(input)) {
//  fscanf(input,"%f %f\n",&nCHN,&nCount); //scan del file di input, riga per riga
//    CHN[npoints]=nCHN;
//    Count[npoints]=nCount;
//    ++npoints; //incremento della variabile numero punto
//  }

//  fclose(input); // chiusura del file di input
    
