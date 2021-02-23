#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TColor.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"

#include "CalcEfficiency/Utils.h"

using namespace std;
using namespace dk;

Utils::Utils() {
}

Utils::~Utils() {
}

int Utils::getNowDate() {
  int date = 0;
  time_t current;
  struct tm *local;
  time(&current);
  local     = localtime(&current);
  int year  = local->tm_year + 1900;
  int mon   = local->tm_mon+1;
  int day   = local->tm_mday;
  date      = 10000*year + 100*mon + day;
  return date;
}

/*
void Utils::myText( double x, double y, int color, double size, TString text ) {
  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  l.SetNDC();
  l.SetTextFont(42);
  l.SetTextSize(size);
  l.SetTextColor(color);
  l.DrawLatex(x,y,text);
  return;
}

void Utils::AtlasLabel( double x, double y, int color, double size, TString sub ) {
  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  l.SetNDC();
  l.SetTextFont(72);
  l.SetTextSize(size);
  l.SetTextColor(color);
  l.DrawLatex(x,y,"ATLAS");
  
  TLatex l2; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  l2.SetNDC();
  l2.SetTextFont(42);
  l2.SetTextSize(size);
  l2.SetTextColor(color);
  l2.DrawLatex(x+0.09,y,sub);
}

void Utils::AllText( double x, double y, int color, float size, 
                     TString sub, TString text, int ecm, double lumi ) {
  AtlasLabel(x,y,color,size,sub);
  myText(x,y-0.04,1,size-0.005,text);
  if(lumi!=0)myText(x,y-0.08,1,size-0.005,Form("#sqrt{s}=%1dTeV, Ldt=%.1f pb^{-1}",ecm,lumi*0.001));
} 
*/

double Utils::deltaR( const double eta1, const double phi1, const double eta2, const double phi2 ) {
  double deltaEta = fabs( eta1 - eta2 );
  double deltaPhi = acos(cos(phi1-phi2));//*acos(cos(phi1-phi2));
  return sqrt( deltaEta*deltaEta + deltaPhi*deltaPhi );
}

void Utils::lumiWeight( const double lumi, const double XS, const double entries, TH1F* h1 ) {
  
  if( XS==0 || entries==0 ) return;

  double weight = lumi/(entries/XS);
  const int nbinX = h1->GetXaxis()->GetNbins();
  
  for (int ibinX=0; ibinX<nbinX; ibinX++) {
    double entry  = h1->GetBinContent(ibinX+1)*weight;
    double error  = h1->GetBinError(ibinX+1)*weight;
    h1->SetBinContent(ibinX+1, entry);
    h1->SetBinError(ibinX+1, error);
  }
  
  return;
}

void Utils::calcHistToHist( CALC opt, TH1F* h1, TH1F* h2, TH1F* hout ) {
  
  double entry[3], error[3];
  const int nbinX = hout->GetXaxis()->GetNbins();

  if ( h1->GetXaxis()->GetNbins() != nbinX || h2->GetXaxis()->GetNbins() != nbinX ) {
    cerr << "Error in dk::calcHistToHist() : Number of bin mismatched" << endl;
    return;
  }

  for (int ibinX=0; ibinX<nbinX; ibinX++) {
    entry[0] = h1->GetBinContent(ibinX+1);
    error[0] = h1->GetBinError(ibinX+1);
    entry[1] = h2->GetBinContent(ibinX+1);
    error[1] = h2->GetBinError(ibinX+1);
    if( opt==RATIO ) {
      entry[2] = ( entry[1]!=0 )? entry[0]/entry[1]:0;
      error[2] = ( entry[1]!=0 )? sqrt( entry[0]*entry[0]*error[1]*error[1] + entry[1]*entry[1]*error[0]*error[0] )/( entry[1]*entry[1] ):0;
    }
    else if( opt==EFF ) {
      //error[0] = sqrt( entry[0] + 0.25 ) + 0.5;
      //error[1] = sqrt( entry[0] + 0.25 ) + 0.5;
      entry[2] = ( entry[1]!=0 )? entry[0]/entry[1]:0;
      error[2] = ( entry[1]!=0 )? sqrt( entry[2]*( 1. - entry[2] )/entry[1] ):0;
    }
    else if( opt==PROD ) {
      entry[2] = ( entry[1]!=0 )? entry[0]*entry[1]:0;
      error[2] = ( entry[1]!=0 )? sqrt( entry[0]*entry[0]*error[1]*error[1] + entry[1]*entry[1]*error[0]*error[0] ):0;
    }
    else if( opt==SUBT ) {
      entry[2] = entry[0]-entry[1];
      error[2] = sqrt( error[1]*error[1] + error[0]*error[0]);
    }
    else if( opt==ADD ) {
      entry[2] = entry[0]+entry[1];
      error[2] = sqrt( error[1]*error[1] + error[0]*error[0]);
    }
    else { 
      entry[2] = 0;
      error[2] = 0;
      cerr << "Error in dk::calcHistToHist() : CALC option is not found" << endl; 
    }
    hout->SetBinContent(ibinX+1, entry[2]);
    hout->SetBinError(ibinX+1, error[2]);
  }

  return;
}

void Utils::calcHistToHist( CALC opt, TH2F* h1, TH2F* h2, TH2F* hout ) {
  
  double entry[3], error[3];
  const int nbinX = hout->GetXaxis()->GetNbins();
  const int nbinY = hout->GetYaxis()->GetNbins();

  if ( h1->GetXaxis()->GetNbins() != nbinX || h2->GetXaxis()->GetNbins() != nbinX ) {
    cerr << "Error in dk::calcHistToHist() : Number of Xbin mismatched" << endl;
    return;
  }
  if ( h1->GetYaxis()->GetNbins() != nbinY || h2->GetYaxis()->GetNbins() != nbinY ) {
    cerr << "Error in dk::calcHistToHist() : Number of Ybin mismatched" << endl;
    return;
  }

  for (int ibinX=0; ibinX<nbinX; ibinX++) {
    for (int ibinY=0; ibinY<nbinY; ibinY++) {
      entry[0] = h1->GetBinContent(ibinX+1, ibinY+1);
      error[0] = h1->GetBinError(ibinX+1, ibinY+1);
      entry[1] = h2->GetBinContent(ibinX+1, ibinY+1);
      error[1] = h2->GetBinError(ibinX+1, ibinY+1);
      if( opt==RATIO ) {
        entry[2] = ( entry[1]!=0 )? entry[0]/entry[1]:0;
        error[2] = ( entry[1]!=0 )? sqrt( entry[0]*entry[0]*error[1]*error[1] + entry[1]*entry[1]*error[0]*error[0] )/( entry[1]*entry[1] ):0;
      }
      else if( opt==EFF ) {
        error[0] = sqrt( entry[0] + 0.25 ) + 0.5;
        error[1] = sqrt( entry[0] + 0.25 ) + 0.5;
        entry[2] = ( entry[1]!=0 )? entry[0]/entry[1]:0;
        error[2] = ( entry[1]!=0 )? sqrt( entry[0]*entry[0]*error[1]*error[1] + entry[1]*entry[1]*error[0]*error[0] )/( entry[1]*entry[1] ):0;
      }
      else if( opt==PROD ) {
        entry[2] = ( entry[1]!=0 )? entry[0]*entry[1]:0;
        error[2] = ( entry[1]!=0 )? sqrt( entry[0]*entry[0]*error[1]*error[1] + entry[1]*entry[1]*error[0]*error[0] ):0;
      }
      else if( opt==SUBT ) {
        entry[2] = entry[0]-entry[1];
        error[2] = sqrt( error[1]*error[1] + error[0]*error[0]);
      }
      else if( opt==ADD ) {
        entry[2] = entry[0]+entry[1];
        error[2] = sqrt( error[1]*error[1] + error[0]*error[0]);
      }
      else { 
        entry[2] = 0;
        error[2] = 0;
        cerr << "Error in dk::calcHistToHist() : CALC option is not found" << endl; 
      }
      hout->SetBinContent(ibinX+1, ibinY+1, entry[2]);
      hout->SetBinError(ibinX+1, ibinY+1, error[2]);
    }
  }

  return;
}

bool Utils::selectRegion( double eta, REGION reg ) {
  bool pass = false;
  if( reg==ALL ) pass = true;
  else if( reg==ENDCAP ) pass = ( fabs(eta)>1.05 );
  else if( reg==BARREL ) pass = ( fabs(eta)<=1.05 );
  else pass = false;
  return pass;
}

bool Utils::muonEFThreshold( double eta, double pt, const string& chain ) {
  const double EFeta[5] = { 0, 1.05, 1.5, 2.0, 9.9 }; 
  const double EF_mu4_pt[4]     = { 3.93,  3.91,  3.88,  3.88 }; 
  const double EF_mu6_pt[4]     = { 5.88,  5.81,  5.78,  5.76 }; 
  const double EF_mu6ms_pt[4]   = { 5.4,  4.5,  4.9,  5.3 }; 
  const double EF_mu8_pt[4]     = { 7.82,  7.74,  7.70,  7.72 }; 
  const double EF_mu10_pt[4]    = { 9.77,  9.67,  9.62,  9.57 }; 
  const double EF_mu11_pt[4]    = { 10.74, 10.64, 10.58, 10.53 }; 
  const double EF_mu14_pt[4]    = { 12.67, 12.55, 12.49, 12.46 }; 
  const double EF_mu18_pt[4]    = { 17.53, 17.39, 17.34, 17.28 }; 
  const double EF_mu20_pt[4]    = { 19.47, 19.33, 19.30, 19.22 }; 
  const double EF_mu20ms_pt[4]  = { 17.5, 18.5, 17.0, 18.0 }; 
  const double EF_mu24_pt[4]    = { 23.34, 23.19, 23.14, 23.06 }; 
  const double EF_mu26_pt[4]    = { 25.29, 25.15, 25.14, 25.05 };
  const double EF_mu40_pt[4]    = { 38.76, 38.54, 38.38, 38.31 };
  const double EF_mu50_pt[4]    = { 45.00, 45.00, 45.00, 45.00 };
  const double EF_mu60msbr_pt[4] = { 54.00, 1000.00, 1000.00, 1000.00 };
  
  bool pass = false;
  for( int i=0; i<4; i++ ) {
    if( EFeta[i]<=fabs(eta) && fabs(eta)<EFeta[i+1] ) {
      if( chain=="HLT_mu4" && pt>EF_mu4_pt[i] ) pass=true;
      else if( chain=="HLT_noalg_L1MU4" && pt>EF_mu4_pt[i] ) pass=true;
      else if( chain=="HLT_mu4_r1extr" && pt>EF_mu4_pt[i] ) pass=true;
      else if( chain=="HLT_2mu4" && pt>EF_mu4_pt[i] ) pass=true;
      else if( chain=="HLT_2mu4_nomucomb" && pt>EF_mu4_pt[i] ) pass=true;
      else if( chain=="HLT_mu6" && pt>EF_mu6_pt[i] ) pass=true;
      else if( chain=="HLT_noalg_L1MU6" && pt>EF_mu6_pt[i] ) pass=true;
      else if( chain=="HLT_2mu6" && pt>EF_mu6_pt[i] ) pass=true;
      else if( chain=="HLT_2mu6_nomucomb" && pt>EF_mu6_pt[i] ) pass=true;
      else if( chain=="HLT_mu6_msonly" && pt>EF_mu6ms_pt[i] ) pass=true;
      else if( chain=="HLT_2mu6_msonly" && pt>EF_mu6ms_pt[i] ) pass=true;
      else if( chain=="HLT_mu10" && pt>EF_mu10_pt[i] ) pass=true;
      else if( chain=="HLT_mu10_nomucomb" && pt>EF_mu10_pt[i] ) pass=true;
      else if( chain=="HLT_2mu10" && pt>EF_mu10_pt[i] ) pass=true;
      else if( chain=="HLT_2mu10_nomucomb" && pt>EF_mu10_pt[i] ) pass=true;
      else if( chain=="HLT_mu11" && pt>EF_mu11_pt[i] ) pass=true;
      else if( chain=="HLT_mu11_nomucomb" && pt>EF_mu11_pt[i] ) pass=true;
      else if( chain=="HLT_mu14" && pt>EF_mu14_pt[i] ) pass=true;
      else if( chain=="HLT_2mu14" && pt>EF_mu14_pt[i] ) pass=true;
      else if( chain=="HLT_mu18" && pt>EF_mu18_pt[i] ) pass=true;
      else if( chain=="HLT_mu20" && pt>EF_mu20_pt[i] ) pass=true;
      else if( chain=="HLT_mu20_mu8noL1" && pt>EF_mu20_pt[i] ) pass=true;
      else if( chain=="HLT_mu20_nomucomb_mu6noL1_nscan03" && pt>EF_mu20_pt[i] ) pass=true;
      else if( chain=="HLT_mu20_iloose_L1MU15" && pt>EF_mu20_pt[i] ) pass=true;
      else if( chain=="HLT_mu20_msonly" && pt>EF_mu20ms_pt[i] ) pass=true;
      else if( chain=="HLT_mu24_iloose_L1MU15" && pt>EF_mu24_pt[i] ) pass=true;
      else if( chain=="HLT_mu24_imedium" && pt>EF_mu24_pt[i] ) pass=true;
      else if( chain=="HLT_mu26_imedium" && pt>EF_mu26_pt[i] ) pass=true;
      else if( chain=="HLT_mu26_ivarmedium" && pt>EF_mu26_pt[i] ) pass=true;
      else if( chain=="HLT_mu40" && pt>EF_mu40_pt[i] ) pass=true;
      else if( chain=="HLT_mu50" && pt>EF_mu50_pt[i] ) pass=true;
      else if( chain=="HLT_mu60_0eta105_msonly" && pt>EF_mu60msbr_pt[i] ) pass=true;
      else if( chain=="mu4FS" && pt>EF_mu4_pt[i] ) pass=true;
      else if( chain=="mu4FSMU6" && pt>EF_mu4_pt[i] ) pass=true;
      else if( chain=="mu6FS" && pt>EF_mu6_pt[i] ) pass=true;
      else if( chain=="mu6FSMU6" && pt>EF_mu6_pt[i] ) pass=true;
      else if( chain=="mu6FSMS" && pt>EF_mu6ms_pt[i] ) pass=true;
      else if( chain=="mu8FS" && pt>EF_mu8_pt[i] ) pass=true;
      else if( chain=="mu8FSMU6" && pt>EF_mu8_pt[i] ) pass=true;
      else if( chain=="mu11mu6" && pt>EF_mu6_pt[i] ) pass=true;
      //else std::cout << "Warning in Utils::EFthreshold: " << chain << " is not found!" << std::endl;
      break;
    }
  }
  return pass;
}

void Utils::setPalette()
{
  //Palet Set
  const Int_t NRGBs = 5;
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, 256);
}
  
void Utils::setAtlasStyle ()
{
  static TStyle* atlasStyle = 0;
  std::cout << "\nApplying ATLAS style settings...\n" << std::endl ;
  if ( atlasStyle==0 ) atlasStyle = AtlasStyle();
  gROOT->SetStyle("ATLAS");
  gROOT->ForceStyle();
}

TStyle* Utils::AtlasStyle() 
{
  TStyle *atlasStyle = new TStyle("ATLAS","Atlas style");

  // use plain black on white colors
  Int_t icol=0; // WHITE
  atlasStyle->SetFrameBorderMode(icol);
  atlasStyle->SetFrameFillColor(icol);
  atlasStyle->SetCanvasBorderMode(icol);
  atlasStyle->SetCanvasColor(icol);
  atlasStyle->SetPadBorderMode(icol);
  atlasStyle->SetPadColor(icol);
  atlasStyle->SetStatColor(icol);
  //atlasStyle->SetFillColor(icol); // don't use: white fill color for *all* objects

  // set the paper & margin sizes
  atlasStyle->SetPaperSize(20,26);

  // set margin sizes
  atlasStyle->SetPadTopMargin(0.05);
  atlasStyle->SetPadRightMargin(0.15);
  atlasStyle->SetPadBottomMargin(0.15);
  atlasStyle->SetPadLeftMargin(0.15);

  // set title offsets (for axis label)
  atlasStyle->SetTitleXOffset(1.2);
  atlasStyle->SetTitleYOffset(1.2);
  atlasStyle->SetLabelOffset(0.01,"x");
  atlasStyle->SetLabelOffset(0.01,"y");

  // use large fonts
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.035;
  Double_t tsize2=0.045;
  atlasStyle->SetTextFont(font);

  atlasStyle->SetTextSize(tsize);
  atlasStyle->SetLabelFont(font,"x");
  atlasStyle->SetTitleFont(font,"x");
  atlasStyle->SetLabelFont(font,"y");
  atlasStyle->SetTitleFont(font,"y");
  atlasStyle->SetLabelFont(font,"z");
  atlasStyle->SetTitleFont(font,"z");
  
  atlasStyle->SetLabelSize(tsize,"x");
  atlasStyle->SetTitleSize(tsize2,"x");
  atlasStyle->SetLabelSize(tsize,"y");
  atlasStyle->SetTitleSize(tsize2,"y");
  atlasStyle->SetLabelSize(tsize,"z");
  atlasStyle->SetTitleSize(tsize2,"z");

  // use bold lines and markers
  atlasStyle->SetMarkerStyle(20);
  atlasStyle->SetMarkerSize(1.2);
  atlasStyle->SetHistLineWidth(2.);
  atlasStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  // get rid of X error bars 
  //atlasStyle->SetErrorX(0.001);
  // get rid of error bar caps
  atlasStyle->SetEndErrorSize(0.);

  // do not display any of the standard histogram decorations
  atlasStyle->SetOptTitle(0);
  //atlasStyle->SetOptStat(1111);
  atlasStyle->SetOptStat(0);
  //atlasStyle->SetOptFit(1111);
  atlasStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  atlasStyle->SetPadTickX(1);
  atlasStyle->SetPadTickY(1);

  return atlasStyle;

}

// eof
