#ifndef _DK_Utils
#define _DK_Utils

#include <time.h>

#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TStyle.h"
#include "TString.h"
#include "TLatex.h"

#define SegmentMaxNumber 10

using namespace std;

namespace dk {
  class Utils {
    public:
	Utils();
	~Utils();
    
    enum CALC { RATIO, EFF, PROD, SUBT, ADD };
    enum REGION { ALL, ENDCAP, BARREL, EC_C, EC_A };
   
    int getNowDate();
    //void myText( double x, double y, int color, double size, TString text );
    //void AtlasLabel( double x, double y, int color, double size, TString sub );
    //void AllText(double x,double y, int color, float size, 
    //             TString sub, TString text, int ecm, double lumi );
    double deltaR( const double eta1, const double phi1, const double eta2, const double phi2 );
    void lumiWeight ( const double lumi, const double XS, const double entries, TH1F* h1 );
    void calcHistToHist ( CALC opt, TH1F* h1, TH1F* h2, TH1F* hout );
    void calcHistToHist ( CALC opt, TH2F* h1, TH2F* h2, TH2F* hout );
    //void calcHistToHist ( CALC opt, TH3F* h1, TH3F* h2, TH3F* hout );
    bool selectRegion( double eta, REGION reg );
    bool muonEFThreshold( double eta, double pt, const string& chain );
    
    // System Setteings
    void setPalette();
    void setAtlasStyle();
    TStyle* AtlasStyle();
  };
}

#endif

// eof
