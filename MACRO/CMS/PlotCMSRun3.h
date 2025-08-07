#include <iostream>
#include <TROOT.h>
#include "TVectorD.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TEfficiency.h" 
#include "TMath.h" 

// Adapted for 4 pads where the CMS text is written inside the pads
void PlotCMS(TPad *c1, TString year, bool DATA)
{
    //------Start of Copy Paste-----------------------------//
    TString cmsText     = "CMS";
    float cmsTextFont   = 61;  // default is helvetic-bold

    bool writeExtraText = true;
    TString extraText   = "Simulation Preliminary";
    float extraTextFont = 52;  // default is helvetica-italics
    if (DATA)
        {
            extraText   = "Preliminary"; 
        }
    // text sizes and text offsets with respect to the top frame
    // in unit of the top margin size
    float lumiTextSize     = 0.5;
    float lumiTextOffset   = 0.2;
    float cmsTextSize      = 0.6;
    float cmsTextOffset    = 0.1;  // only used in outOfFrame version

    float relPosX    = 0.045;
    float relPosY    = 0.035;
    float relExtraDY = 1.2;

    // ratio of "CMS" and extra text size
    float extraOverCmsTextSize  = 0.76;

    TString lumi_13TeV = "109.8 fb^{-1}";//2024
    TString lumi_sqrtS = "(13.6 TeV)";
    if (year == "2022A") {
        lumi_13TeV = "13.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    } else if (year == "2022B") {
        lumi_13TeV = "20.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    } else if (year == "2023A") {
        lumi_13TeV = "17.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    } else if (year == "2023B") {
        lumi_13TeV = "9.5 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    else if (year == "2024") {
        lumi_13TeV = "109.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    else if (year == "2023") {
        lumi_13TeV = "27.3 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    else if (year == "2022") {
        lumi_13TeV = "34.7 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    TString lumiText = lumi_13TeV+" "+lumi_sqrtS;
    float H = c1->GetWh();
    float W = c1->GetWw();
    float l = c1->GetLeftMargin();
    float t = c1->GetTopMargin();
    float r = c1->GetRightMargin();
    float b = c1->GetBottomMargin();

    TLatex latex;
    latex.SetNDC();
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);    

    float extraTextSize = extraOverCmsTextSize*cmsTextSize;

    latex.SetTextFont(42);
    latex.SetTextAlign(31); 
    latex.SetTextSize(lumiTextSize*t);    
    latex.DrawLatex(1-r,1-t+0.02,lumiText);

        latex.SetTextFont(cmsTextFont);
        latex.SetTextAlign(11); 
        latex.SetTextSize(cmsTextSize*t);    
        latex.DrawLatex(l+0.05,1-t-0.1,cmsText);

    float posX_=0;
    float posY_=0;
    int iPosX = 3;
    if( iPosX%10<=1 )
        {
        posX_ =   l + relPosX*(1-l-r);
        }
    else if( iPosX%10==2 )
        {
        posX_ =  l + 0.5*(1-l-r);
        }
    else if( iPosX%10==3 )
        {
        posX_ =  1-r - relPosX*(1-l-r);
        }
    posY_ = 1-t - relPosY*(1-t-b);
        if( writeExtraText ) 
            {
            posX_ =   l +  relPosX*(1-l-r);
            posY_ =   1-t+lumiTextOffset*t;
            int alignY_=3;
            int alignX_=2;
            if( iPosX/10==0 ) alignX_=1;
            if( iPosX==0    ) alignX_=1;
            if( iPosX==0    ) alignY_=1;
            if( iPosX/10==1 ) alignX_=1;
            if( iPosX/10==2 ) alignX_=2;
            if( iPosX/10==3 ) alignX_=3;
            //if( iPosX == 0  ) relPosX = 0.12;
            int align_ = 10*alignX_ + alignY_;
        latex.SetTextFont(extraTextFont);
        latex.SetTextSize(extraTextSize*t);
        latex.SetTextAlign(11);
        latex.DrawLatex(l+0.05,1-t-0.17, extraText);
            }
}

// Adapted for single pass where the CMS text is written inside the pads
void PlotCMSv2(TPad *c1, TString year, bool DATA)
{
    //------Start of Copy Paste-----------------------------//
    TString cmsText     = "CMS";
    float cmsTextFont   = 61;  // default is helvetic-bold

    bool writeExtraText = true;
    TString extraText   = "Simulation Preliminary";
    if (DATA)
        {
            extraText   = "Preliminary"; 
        }
    float extraTextFont = 52;  // default is helvetica-italics

    // text sizes and text offsets with respect to the top frame
    // in unit of the top margin size
    float lumiTextSize     = 0.65;
    float lumiTextOffset   = 0.2;
    float cmsTextSize      = 0.7;
    float cmsTextOffset    = 0.1;  // only used in outOfFrame version

    float relPosX    = 0.045;
    float relPosY    = 0.035;
    float relExtraDY = 1.2;

    // ratio of "CMS" and extra text size
    float extraOverCmsTextSize  = 0.76;

      TString lumi_13TeV = "109.8 fb^{-1}";//2024
    TString lumi_sqrtS = "(13.6 TeV)";
    if (year == "2022A") {
        lumi_13TeV = "13.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    } else if (year == "2022B") {
        lumi_13TeV = "20.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    } else if (year == "2023A") {
        lumi_13TeV = "17.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    } else if (year == "2023B") {
        lumi_13TeV = "9.5 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    else if (year == "2024") {
        lumi_13TeV = "109.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    else if (year == "2023") {
        lumi_13TeV = "27.3 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    else if (year == "2022") {
        lumi_13TeV = "34.7 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    TString lumiText = lumi_13TeV+" "+lumi_sqrtS;
    float H = c1->GetWh();
    float W = c1->GetWw();
    float l = c1->GetLeftMargin();
    float t = c1->GetTopMargin();
    float r = c1->GetRightMargin();
    float b = c1->GetBottomMargin();

    TLatex latex;
    latex.SetNDC();
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);    

    float extraTextSize = extraOverCmsTextSize*cmsTextSize;

    latex.SetTextFont(42);
    latex.SetTextAlign(31); 
    latex.SetTextSize(lumiTextSize*t);    
    latex.DrawLatex(1-r,1-t+0.02,lumiText);

        latex.SetTextFont(cmsTextFont);
        latex.SetTextAlign(11); 
        latex.SetTextSize(cmsTextSize*t);    
        latex.DrawLatex(l+0.05,1-t-0.1,cmsText);

    float posX_=0;
    float posY_=0;
    int iPosX = 3;
    if( iPosX%10<=1 )
        {
        posX_ =   l + relPosX*(1-l-r);
        }
    else if( iPosX%10==2 )
        {
        posX_ =  l + 0.5*(1-l-r);
        }
    else if( iPosX%10==3 )
        {
        posX_ =  1-r - relPosX*(1-l-r);
        }
    posY_ = 1-t - relPosY*(1-t-b);
        if( writeExtraText ) 
            {
            posX_ =   l +  relPosX*(1-l-r);
            posY_ =   1-t+lumiTextOffset*t;
            int alignY_=3;
            int alignX_=2;
            if( iPosX/10==0 ) alignX_=1;
            if( iPosX==0    ) alignX_=1;
            if( iPosX==0    ) alignY_=1;
            if( iPosX/10==1 ) alignX_=1;
            if( iPosX/10==2 ) alignX_=2;
            if( iPosX/10==3 ) alignX_=3;
            //if( iPosX == 0  ) relPosX = 0.12;
            int align_ = 10*alignX_ + alignY_;
        latex.SetTextFont(extraTextFont);
        latex.SetTextSize(extraTextSize*t);
        latex.SetTextAlign(11);
        latex.DrawLatex(l+0.05,1-t-0.17, extraText);
            }
}

// Adapted for 4 pads where the CMS text is written outside the pads
void PlotCMSv3(TPad *c1, TString year, bool DATA)
{
    //------Start of Copy Paste-----------------------------//
    TString cmsText     = "CMS";
    float cmsTextFont   = 61;  // default is helvetic-bold

    bool writeExtraText = true;

    TString extraText   = "Simulation Preliminary";
    if (DATA)
        {
            extraText   = "Preliminary"; 
        }
    float extraTextFont = 52;  // default is helvetica-italics

    // text sizes and text offsets with respect to the top frame
    // in unit of the top margin size
    float lumiTextSize     = 0.7;
    float lumiTextOffset   = 0.2;
    float cmsTextSize      = 0.8;
    float cmsTextOffset    = 0.1;  // only used in outOfFrame version

    float relPosX    = 0.045;
    float relPosY    = 0.035;
    float relExtraDY = 1.2;

    // ratio of "CMS" and extra text size
    float extraOverCmsTextSize  = 0.76;

    TString lumi_13TeV = "109.8 fb^{-1}";//2024
    TString lumi_sqrtS = "(13.6 TeV)";
    if (year == "2022A") {
        lumi_13TeV = "13.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    } else if (year == "2022B") {
        lumi_13TeV = "20.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    } else if (year == "2023A") {
        lumi_13TeV = "17.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    } else if (year == "2023B") {
        lumi_13TeV = "9.5 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    else if (year == "2024") {
        lumi_13TeV = "109.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    else if (year == "2023") {
        lumi_13TeV = "27.3 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    else if (year == "2022") {
        lumi_13TeV = "34.7 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    TString lumiText = lumi_13TeV+" "+lumi_sqrtS;
    float H = c1->GetWh();
    float W = c1->GetWw();
    float l = c1->GetLeftMargin();
    float t = c1->GetTopMargin();
    float r = c1->GetRightMargin();
    float b = c1->GetBottomMargin();

    TLatex latex;
    latex.SetNDC();
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);    

    float extraTextSize = extraOverCmsTextSize*cmsTextSize;

    latex.SetTextFont(42);
    latex.SetTextAlign(31); 
    latex.SetTextSize(lumiTextSize*t);    
    latex.DrawLatex(1-r,1-t+0.02,lumiText);

        latex.SetTextFont(cmsTextFont);
        latex.SetTextAlign(11); 
        latex.SetTextSize(cmsTextSize*t);    
        latex.DrawLatex(l,1-t+0.02,cmsText);

    float posX_=0;
    float posY_=0;
    int iPosX = 3;
    if( iPosX%10<=1 )
        {
        posX_ =   l + relPosX*(1-l-r);
        }
    else if( iPosX%10==2 )
        {
        posX_ =  l + 0.5*(1-l-r);
        }
    else if( iPosX%10==3 )
        {
        posX_ =  1-r - relPosX*(1-l-r);
        }
    posY_ = 1-t - relPosY*(1-t-b);
        if( writeExtraText ) 
            {
            posX_ =   l +  relPosX*(1-l-r);
            posY_ =   1-t+lumiTextOffset*t;
            int alignY_=3;
            int alignX_=2;
            if( iPosX/10==0 ) alignX_=1;
            if( iPosX==0    ) alignX_=1;
            if( iPosX==0    ) alignY_=1;
            if( iPosX/10==1 ) alignX_=1;
            if( iPosX/10==2 ) alignX_=2;
            if( iPosX/10==3 ) alignX_=3;
            //if( iPosX == 0  ) relPosX = 0.12;
            int align_ = 10*alignX_ + alignY_;
        latex.SetTextFont(extraTextFont);
        latex.SetTextSize(extraTextSize*t);
        latex.SetTextAlign(11);
        latex.DrawLatex(posX_+0.08, posY_+0.005, extraText);
            }
}
// Adapted for single pass where the CMS text is written outside the pads
void PlotCMSv4(TPad *c1, TString year, bool DATA)
{
    //------Start of Copy Paste-----------------------------//
    TString cmsText     = "CMS";
    float cmsTextFont   = 61;  // default is helvetic-bold

    bool writeExtraText = true;
    TString extraText   = "Simulation Preliminary";
    if (DATA)
        {
            extraText   = "Preliminary"; 
        }
    float extraTextFont = 52;  // default is helvetica-italics

    // text sizes and text offsets with respect to the top frame
    // in unit of the top margin size
    float lumiTextSize     = 0.55;
    float lumiTextOffset   = 0.2;
    float cmsTextSize      = 0.6;
    float cmsTextOffset    = 0.1;  // only used in outOfFrame version

    float relPosX    = 0.045;
    float relPosY    = 0.035;
    float relExtraDY = 1.2;

    // ratio of "CMS" and extra text size
    float extraOverCmsTextSize  = 0.76;


    TString lumi_13TeV = "109.8 fb^{-1}";//2024
    TString lumi_sqrtS = "(13.6 TeV)";
    if (year == "2022A") {
        lumi_13TeV = "13.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    } else if (year == "2022B") {
        lumi_13TeV = "20.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    } else if (year == "2023A") {
        lumi_13TeV = "17.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    } else if (year == "2023B") {
        lumi_13TeV = "9.5 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    else if (year == "2024") {
        lumi_13TeV = "109.8 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    else if (year == "2023") {
        lumi_13TeV = "27.3 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    else if (year == "2022") {
        lumi_13TeV = "34.7 fb^{-1}";
        lumi_sqrtS = "(13.6 TeV)";
    }
    TString lumiText = lumi_13TeV+" "+lumi_sqrtS;
    float H = c1->GetWh();
    float W = c1->GetWw();
    float l = c1->GetLeftMargin();
    float t = c1->GetTopMargin();
    float r = c1->GetRightMargin();
    float b = c1->GetBottomMargin();

    TLatex latex;
    latex.SetNDC();
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);    

    float extraTextSize = extraOverCmsTextSize*cmsTextSize;

    latex.SetTextFont(42);
    latex.SetTextAlign(31); 
    latex.SetTextSize(lumiTextSize*t);    
    latex.DrawLatex(1-r,1-t+0.02,lumiText);

        latex.SetTextFont(cmsTextFont);
        latex.SetTextAlign(11); 
        latex.SetTextSize(cmsTextSize*t);    
        latex.DrawLatex(l,1-t+0.02,cmsText);

    float posX_=0;
    float posY_=0;
    int iPosX = 3;
    if( iPosX%10<=1 )
        {
        posX_ =   l + relPosX*(1-l-r);
        }
    else if( iPosX%10==2 )
        {
        posX_ =  l + 0.5*(1-l-r);
        }
    else if( iPosX%10==3 )
        {
        posX_ =  1-r - relPosX*(1-l-r);
        }
    posY_ = 1-t - relPosY*(1-t-b);
        if( writeExtraText ) 
            {
            posX_ =   l +  relPosX*(1-l-r);
            posY_ =   1-t+lumiTextOffset*t;
            int alignY_=3;
            int alignX_=2;
            if( iPosX/10==0 ) alignX_=1;
            if( iPosX==0    ) alignX_=1;
            if( iPosX==0    ) alignY_=1;
            if( iPosX/10==1 ) alignX_=1;
            if( iPosX/10==2 ) alignX_=2;
            if( iPosX/10==3 ) alignX_=3;
            //if( iPosX == 0  ) relPosX = 0.12;
            int align_ = 10*alignX_ + alignY_;
        latex.SetTextFont(extraTextFont);
        latex.SetTextSize(extraTextSize*t);
        latex.SetTextAlign(11);
        latex.DrawLatex(posX_+0.1, posY_+0.005, extraText);
            }
}
