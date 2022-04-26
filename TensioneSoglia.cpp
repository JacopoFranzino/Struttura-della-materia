#include <iostream>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <iomanip>
#include <cmath>
using namespace std;

void TensioneSoglia()
{
  //Intensità di soglia 82mV
  //V impostata 26mv mV quindi circa 0.26 microA  
  //Tempo di acquisizione 20s
  const int n=50;
  double V[] = {390,392,394,397,399,402,404,406,409,411,413,416,418,421,423,425,428,430,432,435,437,440,442,444,447,449,451,454,456,459,461,463,466,468,471,473,475,478,480,482,485,487,490,494,499,504,509,516,525,551};
  double Count1[]={5013,7088,9068,10278,11299,11998,12703,13567,14366,15132,15825,16494,17295,18167,18911,19522,20225,21021,21653,22571,23542,24731,26028,27490,28908,30020,31205,32397,32984,33886,34751,34873,35370,36235,36498,36805,37112,36762,37110,37094,37355,37764,37742,38376,38646,38202,38985,39195,39184,38720};
  double Count2[]={4443,7615,9089,10234,11181,12080,12770,13717,14361,15115,15768,16601,17380,18172,18884,19601,20155,20914,21627,22334,23414,24742,26003,27259,28833,30062,31228,32285,33197,33928,34734,35295,35572,35849,36521,36930,36126,36482,37432,37330,37237,37586,37545,38215,38279,38051,38478,38952,39111,38860};
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

    TF1 *funz2 = new TF1("funz2", "[0]+[1]*x", 0, 20);
    //funz2->SetParNames("a", "b");
    funz2->SetLineColor(50);
    funz2->SetRange(479,560);
    //funz1->SetParameters();
    Canvas->Update();
    gGraph->Fit(funz2, "RM+");
    //string udm[] = {"", "", ""};
     double a= funz2->GetParameter(0);
    //double sc=funz2->GetParError(0);
    double b= funz2->GetParameter(1);
    //double sd=funz2->GetParError(1);

   cout << "Chi^2:" << funz2->GetChisquare() << ", number of DoF: " << funz2->GetNDF() << " (Probability: " << funz2->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    //.........................//

    TF1 *funz3 = new TF1("funz3", "[0]+[1]*x", 0, 20);
    //funz3->SetParNames("c", "d");
    funz3->SetLineColor(9);
    funz3->SetRange(390,472);
    //funz1->SetParameters();
    Canvas->Update();
    gGraph->Fit(funz3, "RM+");
    //string udm[] = {"", "", ""};
    double c= funz3->GetParameter(0);
    //double sc=funz2->GetParError(0);
    double d= funz3->GetParameter(1);
    //double sd=funz2->GetParError(1);

   cout << "Chi^2:" << funz3->GetChisquare() << ", number of DoF: " << funz3->GetNDF() << " (Probability: " << funz3->GetProb() << ")." << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
    //.........................//

    double Vs=abs((c-a)/(b-d));
    cout<<Vs<<endl;
}
