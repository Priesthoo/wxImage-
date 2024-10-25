#include<wx/dialog.h>
#include<wx/fontdlg.h>
#include<wx/button.h>
#include<wx/sizer.h>
#include<wx/spinctrl.h>
#include<wx/checkbox.h>
#include<wx/textctrl.h>
#include<wx/panel.h>
#include<wx/stattext.h>
#include<wx/statline.h>
#include<wx/slider.h>
#include<wx/colordlg.h>
#include<wx/gdicmn.h>
#include<wx/bitmap.h>
#include<wx/clrpicker.h>
#include<wx/checkbox.h>
#include<wx/dcgraph.h>
#include<wx/dcmemory.h>
#include<wx/dc.h>
#include<wx/fontpicker.h>
#include<wx/image.h>
#include<wx/gdicmn.h>
const int lsp=1;
const int lsp1=0;
const int lsp2=2;
const int lsp3=3;
const int lsp4=4;
const int lsp5=5;
const int lsp6=6;
const int lsp7=7;
const int lsp8=8;
const int lsp9=9;
const int lsp10=10;
const int lsp11=11;
const int lsp12=12;
const int lsp13=13;
const int lsp14=14;
const int lsp15=15;
const int lsp16=16;
const int lsp17=17;
const int lsp18=18;
class MessageBus:public wxDialog{

};
//This Class is created to manipulate the scale factor
class ScaleDialog:public wxDialog{
   private:
   int firstvalue;
   int secondvalue;
   bool currentstate;
   void PressOk(wxCommandEvent& evt){
    InitAllValues();
    EndModal(wxID_OK);
   }
   public:
   ScaleDialog(wxWindow* win,const int& a,const int& b,bool state):wxDialog(win,wxID_ANY,wxT("Scale Dialog"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
     CreateControls(a,b,state);
     Show(true);
     ShowModal();
   }
   void CreateControls(const int& a,const int& b,bool state){
    wxStaticText* stext=new wxStaticText(this,wxID_ANY,wxT("Use this dialog to Scale the Image on Display"));
    wxStaticText* stext1=new wxStaticText(this,wxID_ANY,wxT("Width:"));
    wxStaticText* stext2=new wxStaticText(this,wxID_ANY,wxT("Height:"));
    wxSpinCtrl* sptrl=new wxSpinCtrl(this,lsp,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,280000,0);
    wxSpinCtrl* sptrl1=new wxSpinCtrl(this,lsp1,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,280000,0);
    wxCheckBox* cbox=new wxCheckBox(this,lsp2,wxT("Scale State:"),wxDefaultPosition,wxDefaultSize,wxCHK_2STATE);
    cbox->SetValue(state);
    sptrl->SetValue(a);
    sptrl1->SetValue(b);
    wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
    wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
    wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
    wxBoxSizer*bsizer1=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer2=new wxBoxSizer(wxHORIZONTAL);
    SetSizer(bsizer);
    bsizer->Add(stext,0,wxLEFT|wxALL,5);
    bsizer->Add(bsizer1,0,wxLEFT|wxALL,10);
    bsizer1->Add(stext1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer1->Add(sptrl,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer1->Add(10,10,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer1->Add(stext2,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer1->Add(sptrl1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer->Add(5,5,0,wxLEFT|wxALL,5);
    bsizer->Add(cbox,0,wxLEFT|wxALL,10);
    bsizer->Add(bsizer2,0,wxLEFT|wxALL,5);
    bsizer2->Add(button,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer2->Add(button1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);

   }
   void InitAllValues(){
    wxSpinCtrl* sptrl=(wxSpinCtrl*)FindWindow(lsp);
    wxSpinCtrl* sptrl1=(wxSpinCtrl*)FindWindow(lsp1);
    wxCheckBox* cbox=(wxCheckBox*)FindWindow(lsp2);
    firstvalue=sptrl->GetValue();
    secondvalue=sptrl1->GetValue();
    if(cbox->IsChecked()){
    currentstate=cbox->GetValue();
    }
   }
   int GetFirstValue() const{
    return firstvalue;
   }
   int GetSecondValue() const{
    return secondvalue;
   }
   bool GetScaleState() const{
    return currentstate;
   }
};
class ChangeBackgroundColourDialog:public wxDialog{
  private:
  wxColour CurrentColour;
  void PressOk(wxCommandEvent& evt){
    InitAllValues();
    EndModal(wxID_OK);
  }
  public:
  ChangeBackgroundColourDialog(wxWindow* win,const wxColour& colour):wxDialog(win,wxID_ANY,wxT("Change Background Colour"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER)
  {
    CreateControls(colour);
    Show(true);
    ShowModal();
    Bind(wxEVT_BUTTON,&PressOk,this,wxID_OK);
  }
  void CreateControls(const wxColour& colour){
    wxStaticText* stext=new wxStaticText(this,wxID_ANY,wxT("Choose Colour For Background"));
    wxStaticText* stext1=new wxStaticText(this,wxID_ANY,wxT("CurrentColour:"));
    wxColourPickerCtrl* cptrl=new wxColourPickerCtrl(this,lsp);
    cptrl->SetColour(colour);
    wxButton* button=new wxButton(this,wxID_OK,wxT("Ok")); 
    wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
    wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bsizer1=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer2=new wxBoxSizer(wxHORIZONTAL);
    SetSizer(bsizer);
    bsizer->Add(stext,0,wxLEFT,10);
    bsizer->Add(5,5,0,wxLEFT|wxALL,0);
    bsizer->Add(bsizer1,0,wxLEFT|wxALL,5);
    bsizer1->Add(stext1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer1->Add(cptrl,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer->Add(5,5,wxLEFT|wxALL,0);
    bsizer->Add(bsizer2,0,wxALIGN_RIGHT|wxALL,5);
    bsizer2->Add(button,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer2->Add(button1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
  }
  wxColour GetColour() const {
    return CurrentColour;
  }
  void InitAllValues(){
    wxColourPickerCtrl* cptrl=(wxColourPickerCtrl*)FindWindow(lsp);
    CurrentColour=cptrl->GetColour();
  }
};
class BlurDialog:public wxDialog{
  private:
  int radius;
  void PressKey(wxCommandEvent& evt){
    InitAllValues();
    EndModal(wxID_OK);
  }
  public:
  BlurDialog(wxWindow* win,const int& radius1):wxDialog(win,wxID_ANY,wxT("Blur Dialog"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
     CreateControls(radius1);
     Show(true);
     ShowModal();
     Bind(wxEVT_BUTTON,&PressKey,this,wxID_OK);
  }
  void CreateControls(const int& r){
    wxStaticText* stext=new wxStaticText(this,wxID_ANY,wxT("Specify Blur radius")); 
    wxStaticText* stext1=new wxStaticText(this,wxID_ANY,wxT("Blur radius:"));
    wxSpinCtrl* sptrl=new wxSpinCtrl(this,lsp,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,1000,0);
    wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
    wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
    sptrl->SetValue(r);
    wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bsizer1=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer2=new wxBoxSizer(wxHORIZONTAL);
    SetSizer(bsizer);
    bsizer->Add(stext,0,wxLEFT|wxALL,5);
    bsizer->Add(5,5,0,wxLEFT|wxALL,0);
    bsizer->Add(bsizer1,0,wxLEFT|wxALL,10);
    bsizer1->Add(stext1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer1->Add(sptrl,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer->Add(5,5,0,wxLEFT|wxALL,5);
    bsizer->Add(bsizer2,0,wxLEFT|wxALL,5);
    bsizer2->Add(button,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer2->Add(button1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    return;
  }
  int GetGaussianRadius() const {
    return radius;
  }
  void InitAllValues(){
    wxSpinCtrl* sptrl=(wxSpinCtrl*)FindWindow(lsp);
    radius=sptrl->GetValue();
    return;
  }
};
//Writing a modeless Dialog
class BrightnessDialog:public wxDialog{
  private:
  int brightfactor;
  void PressKey(wxCommandEvent& evt){
    InitAllValues();
    EndModal(wxID_OK);
    return;
  }
  public:
  BrightnessDialog(wxWindow* win,const int& alpha):wxDialog(win,wxID_ANY,wxT("Modify Brightness"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
    CreateControls(alpha);
    Show(true);
    ShowModal();
    Bind(wxEVT_BUTTON,&PressKey,this,wxID_OK);
  }
  void CreateControls(const int& alpha){
   wxStaticText* stext=new wxStaticText(this,wxID_ANY,wxT("Current Value:"));
   wxSlider* slider=new wxSlider(this,lsp,0,-100,100,wxDefaultPosition,wxSize(300,-1),wxSL_LABELS|wxSL_TICKS); 
   slider->SetValue(alpha);
    wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
    wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
    wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bsizer1=new wxBoxSizer(wxHORIZONTAL);
    SetSizer(bsizer);
    bsizer->Add(5,5,wxALL,0);
    bsizer->Add(stext,0,wxALIGN_LEFT|wxALL,5);
    bsizer->Add(slider,0,wxTOP|wxLEFT,5);
    bsizer->Add(bsizer1,0,wxALIGN_RIGHT|wxALL,5);
    bsizer1->Add(button1,0,wxALL|wxALIGN_CENTER_VERTICAL,0);
    bsizer1->Add(button,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    return;
  }
  int GetBrightFactor() const{
    return brightfactor;
  }
  void InitAllValues(){
    wxSlider* slider=(wxSlider*)FindWindow(lsp);
    brightfactor=slider->GetValue();
    return;
  }
};
class RotateDialog:public wxDialog{
   private:
   int angle;
   void Pressok(wxCommandEvent& evt){
    InitValue();
    EndModal(wxID_OK);
    return;
   }
   public:
   RotateDialog(wxWindow* win,const int& angle):wxDialog(win,wxID_ANY,wxT("Rotate Value"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
    CreateControls(angle);
    Show(true);
    ShowModal();
    Bind(wxEVT_BUTTON,&Pressok,this,wxID_OK);
    
   }
   void CreateControls(const int& angle){
     wxStaticText* stext=new wxStaticText(this,wxID_ANY,wxT("NB:Values Specified are automatically converted to radians,Please specify between -360 to 360"));
     wxStaticText* stext1=new wxStaticText(this,wxID_ANY,wxT("Degree:"));
     wxSpinCtrl* sptrl=new wxSpinCtrl(this,lsp,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,-360,360,0);
     sptrl->SetValue(angle);
    wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
    wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
    wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bsizer1=new wxBoxSizer(wxHORIZONTAL);
    SetSizer(bsizer);
    bsizer->Add(5,5,0,wxLEFT,0);
    bsizer->Add(stext,0,wxLEFT|wxALIGN_LEFT,5);
    bsizer->Add(5,5,0,wxALL,5);
    bsizer->Add(stext1,0,wxALL,5);
    bsizer->Add(sptrl,0,wxLEFT,10);
    bsizer->Add(5,5,0,wxALL,5);
    bsizer->Add(bsizer1,0,wxALL|wxALIGN_RIGHT,5);
    bsizer1->Add(button1,0,wxALL|wxALIGN_CENTER_VERTICAL,0);
    bsizer1->Add(button,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    return;
   }
   void InitValue(){
    wxSpinCtrl* sptrl=(wxSpinCtrl*)FindWindow(lsp);
    angle=sptrl->GetValue();
    return;
   }
  int GetAngle() const{
    return angle;
  }
};
class GammaDialog:public wxDialog{
    private:
    int gamma;
    int constant;
    void PressOk(wxCommandEvent& evt){
      InitValue();
      EndModal(wxID_OK);
    }
    void PressCancel(wxCommandEvent& event){
      Destroy();
    }
    public:
    GammaDialog(wxWindow* win,const double& gamma1,const int& c):wxDialog(win,wxID_ANY,wxT("Gamma Dialog"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
       CreateControls(gamma1,c);
       Show(true);
       ShowModal();
       Bind(wxEVT_BUTTON,&PressOk,this,wxID_OK);
       Bind(wxEVT_BUTTON,&PressCancel,this,wxID_CANCEL);
    }
    void CreateControls(const int& gamma,const int& c){
     wxStaticText* stext=new wxStaticText(this,wxID_ANY,wxT("While you increase the gamma value which is the exponent,reduce the constant to get a reasonable output"));
     wxStaticText* stext1=new wxStaticText(this,wxID_ANY,wxT("Gamma:"));
     wxStaticText* stext2=new wxStaticText(this,wxID_ANY,wxT("Constant:"));
     wxSpinCtrl* sptrl=new wxSpinCtrl(this,lsp,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0);
     wxSpinCtrl* sptrl1=new wxSpinCtrl(this,lsp1,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,100,0);
     wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
     wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
     sptrl->SetValue(gamma);
     sptrl1->SetValue(c);
     wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
     wxBoxSizer* bsizer1=new wxBoxSizer(wxHORIZONTAL);
     wxBoxSizer* bsizer2=new wxBoxSizer(wxHORIZONTAL);
     SetSizer(bsizer);
     bsizer->Add(stext,0,wxALIGN_LEFT|wxALL,5);
     bsizer->Add(5,5,0,wxALIGN_CENTER_HORIZONTAL|wxALL,5);
     bsizer->Add(bsizer1,0,wxALIGN_LEFT|wxALL,5);
     bsizer1->Add(stext1,0,wxALIGN_CENTER_VERTICAL|wxLEFT,10);
     bsizer1->Add(sptrl,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
     bsizer1->Add(5,5,0,wxALL|wxALIGN_CENTER_VERTICAL,5);
     bsizer1->Add(stext2,0,wxLEFT|wxALIGN_CENTER_VERTICAL,5);
     bsizer1->Add(sptrl1,0,wxALL|wxALIGN_CENTER_VERTICAL,0);
     bsizer->Add(bsizer2,0,wxALIGN_RIGHT|wxLEFT|wxTOP|wxBOTTOM,5);
     bsizer2->Add(button,0,wxALIGN_CENTER_VERTICAL);
     bsizer2->Add(button1,0,wxALIGN_CENTER_VERTICAL);

    }
  double GetGamma() const{
    return gamma;
  }
  double GetConstant() const{
    return constant;
  }
  void InitValue(){
    wxSpinCtrl* sptrl=(wxSpinCtrl*)FindWindow(lsp);
    wxSpinCtrl* sptrl1=(wxSpinCtrl*)FindWindow(lsp1);
    gamma=sptrl->GetValue();
    constant=sptrl1->GetValue();

  }

};
class DrawImageDialog:public wxDialog{
   private:
   int width;
   int height;
   wxColour colour;
   void PressOk(wxCommandEvent& event){
    InitAllValues();
    EndModal(wxID_OK);
   }
   public:
   DrawImageDialog(wxWindow* win):wxDialog(win,wxID_ANY,wxT("DrawImage"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
     CreateControls();
     ShowModal();
     Bind(wxEVT_BUTTON,&PressOk,this,wxID_OK);
   }
   void CreateControls(){
    wxStaticText* stext=new wxStaticText(this,wxID_ANY,wxT("Construct a colourful Image "));
    wxStaticText* stext1=new wxStaticText(this,wxID_ANY,wxT("Width: "));
    wxStaticText* stext2=new wxStaticText(this,wxID_ANY,wxT("Height:"));
    wxStaticText* stext3=new wxStaticText(this,wxID_ANY,wxT("CurrentColour:"));
    wxSpinCtrl* sptrl=new wxSpinCtrl(this,lsp,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0);
     wxSpinCtrl* sptrl1=new wxSpinCtrl(this,lsp1,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0);
     wxColourPickerCtrl* cptrl=new wxColourPickerCtrl(this,lsp2);
     wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
     wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
     wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
     wxBoxSizer* bsizer1=new wxBoxSizer(wxHORIZONTAL);
     wxBoxSizer* bsizer2=new wxBoxSizer(wxHORIZONTAL);
     wxBoxSizer* bsizer3=new wxBoxSizer(wxHORIZONTAL);
     SetSizer(bsizer);
     bsizer->Add(stext,0,wxALIGN_LEFT|wxALL,5);
     bsizer->Add(bsizer1,0,wxALIGN_LEFT|wxALL,5);
     bsizer1->Add(stext1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
     bsizer1->Add(sptrl,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
     bsizer1->AddSpacer(10);
     bsizer1->Add(stext2,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
     bsizer1->Add(sptrl1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
     bsizer->Add(bsizer2,0,wxALIGN_LEFT|wxALL,5);
     bsizer2->Add(stext3,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
     bsizer2->Add(cptrl,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
     bsizer->Add(bsizer3,0,wxALIGN_RIGHT|wxALL,5);
     bsizer3->Add(button,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
     bsizer3->Add(button1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
   }
   wxColour GetDialogColour() const{
    return colour;
   }
   int GetDialogWidth() const {
    return width;
   }
   int GetDialogHeight() const{
    return height;
   }
   void InitAllValues() {
    wxSpinCtrl* sptrl=(wxSpinCtrl*)FindWindow(lsp);
    wxSpinCtrl* sptrl1=(wxSpinCtrl*)FindWindow(lsp1);
    wxColourPickerCtrl* ctrl=(wxColourPickerCtrl*)FindWindow(lsp2);
    width=sptrl->GetValue();
    height=sptrl1->GetValue();
    colour=ctrl->GetColour();

   }
};
class HorizontalBlurDialog:public wxDialog{
  private:
  int blurfactor;
  void PressKey(wxCommandEvent& evt){
    InitAllValues();
    EndModal(wxID_OK);
    return;
  }
  public:
  HorizontalBlurDialog(wxWindow* win,const int& alpha):wxDialog(win,wxID_ANY,wxT("Add Motion Blur"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
    CreateControls(alpha);
    Show(true);
    ShowModal();
    Bind(wxEVT_BUTTON,&PressKey,this,wxID_OK);
  }
  void CreateControls(const int& alpha){
   wxStaticText* stext=new wxStaticText(this,wxID_ANY,wxT("Current Value:"));
   wxSlider* slider=new wxSlider(this,lsp,0,0,1000,wxDefaultPosition,wxSize(500,-1),wxSL_LABELS|wxSL_TICKS); 
   slider->SetValue(alpha);
    wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
    wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
    wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bsizer1=new wxBoxSizer(wxHORIZONTAL);
    SetSizer(bsizer);
    bsizer->Add(5,5,wxALL,0);
    bsizer->Add(stext,0,wxALL,5);
    bsizer->Add(slider,0,wxLEFT,10);
    bsizer->Add(bsizer1,0,wxALIGN_RIGHT|wxALL,5);
    bsizer1->Add(button1,0,wxALL|wxALIGN_CENTER_VERTICAL,0);
    bsizer1->Add(button,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    return;
  }
  int GetBlurFactor() const{
    return blurfactor;
  }
  void InitAllValues(){
    wxSlider* slider=(wxSlider*)FindWindow(lsp);
    blurfactor=slider->GetValue();
    return;
  }
};
class VerticalBlurDialog:public wxDialog{
  private:
  int blurfactor;
  void PressKey(wxCommandEvent& evt){
    InitAllValues();
    EndModal(wxID_OK);
    return;
  }
  public:
  VerticalBlurDialog(wxWindow* win,const int& alpha):wxDialog(win,wxID_ANY,wxT("Add vertical Blur"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
    CreateControls(alpha);
    Show(true);
    ShowModal();
    Bind(wxEVT_BUTTON,&PressKey,this,wxID_OK);
  }
  void CreateControls(const int& alpha){
   wxStaticText* stext=new wxStaticText(this,wxID_ANY,wxT("Current Value:"));
   wxSlider* slider=new wxSlider(this,lsp,0,0,1000,wxDefaultPosition,wxSize(500,-1),wxSL_LABELS|wxSL_TICKS); 
   slider->SetValue(alpha);
    wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
    wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
    wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bsizer1=new wxBoxSizer(wxHORIZONTAL);
    SetSizer(bsizer);
    bsizer->Add(5,5,wxALL,0);
    bsizer->Add(stext,0,wxALL,5);
    bsizer->Add(slider,0,wxLEFT,10);
    bsizer->Add(bsizer1,0,wxALIGN_RIGHT|wxALL,5);
    bsizer1->Add(button1,0,wxALL|wxALIGN_CENTER_VERTICAL,0);
    bsizer1->Add(button,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    return;
  }
  int GetBlurFactor() const{
    return blurfactor;
  }
  void InitAllValues(){
    wxSlider* slider=(wxSlider*)FindWindow(lsp);
    blurfactor=slider->GetValue();
    return;
  }
};
class TextLayerDialog:public wxDialog{
  private:
  wxString textname;
  wxString layername;
  bool isvisible;
  bool showboundarybox;
  wxColour TextColour;
  wxColour ForeColour;
  int Offset_x;
  int Offset_y;
  wxFont font;
  int angle;
  wxPoint topleft;
  wxPoint topright;
  wxPoint bottomleft;
  wxPoint bottomright;
  wxPoint Top;
  wxPoint Bottom;
  wxPoint Center;
  wxPoint CenterLeft;
  wxPoint CenterRight;
  void PressOk(wxCommandEvent& event){
    InitAllValues();
    EndModal(wxID_OK);
  }
  public:
  TextLayerDialog(wxWindow* win,const wxImage& image, LayerText& layer):wxDialog(win,wxID_ANY,wxT("TextLayer Dialog"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
     CreateControls(image,layer);
     ShowModal();
     Bind(wxEVT_BUTTON,&PressOk,this,wxID_OK);

  }
  void CreateControls(const wxImage& image, LayerText& layer){
    wxStaticText* stext=new wxStaticText(this,wxID_ANY,wxT("Layername:"));
    wxStaticText* stext1=new wxStaticText(this,wxID_ANY,wxT("Textname:"));
    wxSpinCtrl* sptrl=new wxSpinCtrl(this,lsp,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0);
    wxSpinCtrl* sptrl1=new wxSpinCtrl(this,lsp1,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0);
    wxSpinCtrl* sptrl2=new wxSpinCtrl(this,lsp8,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0);
    wxStaticText* stext2=new wxStaticText(this,wxID_ANY,wxT("FontPicker:"));
    wxStaticText* stext3=new wxStaticText(this,wxID_ANY,wxT("ColourPicker:"));
    wxStaticText* stext4=new wxStaticText(this,wxID_ANY,wxT("Offset_x:"));
    wxStaticText* stext5=new wxStaticText(this,wxID_ANY,wxT("Offset_y:"));
    wxStaticText* stext6=new wxStaticText(this,wxID_ANY,wxT("Angle:"));
    wxStaticText* stext7=new wxStaticText(this,wxID_ANY,wxT("Alignment:"));
    wxColourPickerCtrl* cptrl=new wxColourPickerCtrl(this,lsp2);
    wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
    wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
    wxFontPickerCtrl* fontpicker=new wxFontPickerCtrl(this,lsp3);
    wxCheckBox* cbox=new wxCheckBox(this,lsp4,wxT("Make Visible"),wxDefaultPosition,wxDefaultSize,wxCHK_2STATE);
    wxCheckBox* cbox1=new wxCheckBox(this,lsp5,wxT("Show Boundary Box"),wxDefaultPosition,wxDefaultSize,wxCHK_2STATE);
    wxCheckBox* cbox2=new wxCheckBox(this,lsp9,wxT("Top Left"),wxDefaultPosition,wxDefaultSize,wxCHK_2STATE);
    wxCheckBox* cbox3=new wxCheckBox(this,lsp10,wxT("Top Right"),wxDefaultPosition,wxDefaultSize,wxCHK_2STATE); 
    wxCheckBox* cbox4=new wxCheckBox(this,lsp11,wxT("Top Center"),wxDefaultPosition,wxDefaultSize,wxCHK_2STATE); 
    wxCheckBox* cbox5=new wxCheckBox(this,lsp12,wxT("Center"),wxDefaultPosition,wxDefaultSize,wxCHK_2STATE);
    wxCheckBox* cbox6=new wxCheckBox(this,lsp13,wxT("Bottom Left"),wxDefaultPosition,wxDefaultSize,wxCHK_2STATE);
    wxCheckBox* cbox7=new wxCheckBox(this,lsp14,wxT("Bottom Right"),wxDefaultPosition,wxDefaultSize,wxCHK_2STATE);
    wxCheckBox* cbox8=new wxCheckBox(this,lsp15,wxT("Bottom Center"),wxDefaultPosition,wxDefaultSize,wxCHK_2STATE);
    wxCheckBox* cbox9=new wxCheckBox(this,lsp16,wxT("None"),wxDefaultPosition,wxDefaultSize,wxCHK_2STATE);
    wxCheckBox* cbox10=new wxCheckBox(this,lsp17,wxT("Center Left"),wxDefaultPosition,wxDefaultSize,wxCHK_2STATE);
    wxCheckBox* cbox11=new wxCheckBox(this,lsp18,wxT("Center Right"),wxDefaultPosition,wxDefaultSize,wxCHK_2STATE);
    sptrl->SetValue(layer.GetOrigin().x);
    sptrl1->SetValue(layer.GetOrigin().y);
    sptrl2->SetValue(layer.GetAngle());
    cptrl->SetColour(layer.GetForeColour());
    fontpicker->SetSelectedFont(layer.GetFont());
    fontpicker->SetSelectedColour(layer.GetTextColour());
    cbox->SetValue(layer.GetVisibility());
    wxRect rect(0,0,image.GetWidth(),image.GetHeight());
    topleft=rect.GetTopLeft();
    topright=rect.GetTopRight();
    bottomleft=rect.GetBottomLeft();
    bottomright=rect.GetBottomRight();
    Top=(topleft+topright)/2;
    Bottom=(bottomleft+bottomright)/2;
    wxPoint pt(image.GetWidth()/2,image.GetHeight()/2);
    Center=pt;
    wxPoint pt1(0,pt.y);
    CenterLeft=pt1;
    wxPoint pt2(image.GetWidth(),pt.y);
    CenterRight=pt2;
    wxTextCtrl* textctrl=new wxTextCtrl(this,lsp6,wxEmptyString,wxDefaultPosition,wxSize(200,30));
    wxTextCtrl* textctrl1=new wxTextCtrl(this,lsp7,wxEmptyString,wxDefaultPosition,wxSize(200,30));
    wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bsizer1=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer2=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer3=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer4=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer5=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer6=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer7=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer8=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer9=new wxBoxSizer(wxHORIZONTAL);
    SetSizer(bsizer);
    bsizer->Add(bsizer1,0,wxALL,5);
    bsizer1->Add(stext,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer1->Add(textctrl,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer->Add(bsizer2,0,wxALL,5);
    bsizer2->Add(stext1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer2->Add(textctrl1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer->Add(bsizer3,0,wxALL,5);
    bsizer3->Add(cbox,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer3->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer3->Add(cbox1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer->Add(stext7,0,wxALL,5);
    bsizer->Add(bsizer7,0,wxLEFT|wxTOP,7);
    bsizer7->Add(cbox2,0,wxALIGN_CENTER_VERTICAL,0);
    bsizer7->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer7->Add(cbox3,0,wxALIGN_CENTER_VERTICAL,0);
    bsizer7->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer7->Add(cbox4,0,wxALIGN_CENTER_VERTICAL,0);
    bsizer7->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer7->Add(cbox5,0,wxALIGN_CENTER_VERTICAL,0);
    bsizer->Add(bsizer8,0,wxLEFT|wxTOP,7);
    bsizer8->Add(cbox6,0,wxALIGN_CENTER_VERTICAL,0);
    bsizer8->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer8->Add(cbox7,0,wxALIGN_CENTER_VERTICAL,0);
    bsizer8->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer8->Add(cbox8,0,wxALIGN_CENTER_VERTICAL,0);
    bsizer8->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer8->Add(cbox9,0,wxALIGN_CENTER_VERTICAL,0);
    bsizer->Add(bsizer9,0,wxALL,5);
    bsizer9->Add(cbox10,0,wxALIGN_CENTER_VERTICAL,0);
    bsizer9->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer9->Add(cbox11,0,wxALIGN_CENTER_VERTICAL,0);
    bsizer->Add(bsizer4,0,wxALL,5);
    bsizer4->Add(stext2,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer4->Add(fontpicker,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer4->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer4->Add(stext3,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer4->Add(cptrl,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer->Add(bsizer5,0,wxALL,5);
    bsizer5->Add(stext4,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer5->Add(sptrl,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer5->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer5->Add(stext5,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer5->Add(sptrl1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer5->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer5->Add(stext6,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer5->Add(sptrl2,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer->Add(bsizer6,0,wxALIGN_RIGHT|wxALL,5);
    bsizer6->Add(button1,0,wxALL|wxALIGN_CENTER_VERTICAL,0);
    bsizer6->Add(button,0,wxALL|wxALIGN_CENTER_VERTICAL,0);
    return;
  }
  wxString GetTextName() const{
    return textname;
  }
  wxString GetLayername() const{
    return layername; 
  }
  bool GetVisibility() const{
    return isvisible;
  }
  bool ShowBoundaryBox() const{
    return showboundarybox;
  }
  wxColour GetTextColour() const{
    return TextColour;
  }
  wxColour GetForeColour() const{
    return ForeColour;
  }
  int GetOffset_Y() const{
    return Offset_y;
  }
  int GetOffset_X() const{
    return Offset_x;
  }
  wxFont Getfont() const{
    return font;
  }
  int GetAngle() const{
    return angle;
  }
  void InitAllValues(){
    wxSpinCtrl* sptrl=(wxSpinCtrl*)FindWindow(lsp);
    wxSpinCtrl* sptrl1=(wxSpinCtrl*)FindWindow(lsp1);
    wxSpinCtrl* sptrl3=(wxSpinCtrl*)FindWindow(lsp8);
    wxColourPickerCtrl* cptrl=(wxColourPickerCtrl*)FindWindow(lsp2);
    wxFontPickerCtrl* fontpicker=(wxFontPickerCtrl*)FindWindow(lsp3);
    wxCheckBox* cbox=(wxCheckBox*)FindWindow(lsp4);
    wxCheckBox* cbox1=(wxCheckBox*)FindWindow(lsp5);
    wxTextCtrl* textctrl=(wxTextCtrl*)FindWindow(lsp6);
    wxTextCtrl* textctrl1=(wxTextCtrl*)FindWindow(lsp7);
    wxCheckBox* cbox2=(wxCheckBox*)FindWindow(lsp9);
    wxCheckBox* cbox3=(wxCheckBox*)FindWindow(lsp10);
    wxCheckBox* cbox4=(wxCheckBox*)FindWindow(lsp11);
    wxCheckBox* cbox5=(wxCheckBox*)FindWindow(lsp12);
    wxCheckBox* cbox6=(wxCheckBox*)FindWindow(lsp13);
    wxCheckBox* cbox7=(wxCheckBox*)FindWindow(lsp14);
    wxCheckBox* cbox8=(wxCheckBox*)FindWindow(lsp15);
    wxCheckBox* cbox9=(wxCheckBox*)FindWindow(lsp16);
    wxCheckBox* cbox10=(wxCheckBox*)FindWindow(lsp17);
    wxCheckBox* cbox11=(wxCheckBox*)FindWindow(lsp18);
    int textwidth=0;
    int textheight=0;
    wxMemoryDC memdc;
    memdc.SetFont(fontpicker->GetSelectedFont());
    memdc.GetTextExtent(textctrl1->GetValue(),&textwidth,&textheight);
    if(cbox2->IsChecked()){
      Offset_x=topleft.x+sptrl->GetValue();
      Offset_y=topleft.y+sptrl1->GetValue();
    }
    else if(cbox3->IsChecked()){
      Offset_x=topright.x+sptrl->GetValue()-textwidth;
      Offset_y=topright.y+sptrl1->GetValue();
    }
    else if(cbox4->IsChecked()){
      Offset_x=Top.x+sptrl->GetValue();
      Offset_y=Top.y+sptrl1->GetValue();
    }
     else if(cbox5->IsChecked()){
      Offset_x=Center.x+sptrl->GetValue();
      Offset_y=Center.y+sptrl1->GetValue();
    }
     else if(cbox6->IsChecked()){
      Offset_x=bottomleft.x+sptrl->GetValue();
      Offset_y=bottomleft.y-textheight-sptrl1->GetValue();
    }
     else if(cbox7->IsChecked()){
      Offset_x=bottomright.x-sptrl->GetValue()-textwidth;
      Offset_y=bottomright.y-textheight-sptrl1->GetValue();
    }
     else if(cbox8->IsChecked()){
      Offset_x=Bottom.x+sptrl->GetValue()-textwidth;
      Offset_y=Bottom.y-sptrl1->GetValue()-textheight;
    }
     else if(cbox9->IsChecked()){
      Offset_x=sptrl->GetValue();
      Offset_y=sptrl1->GetValue();
    }
    else if(cbox10->IsChecked()){
      Offset_x=CenterLeft.x+sptrl->GetValue();
      Offset_y=CenterLeft.y+sptrl1->GetValue();
    }
     else if(cbox11->IsChecked()){
      Offset_x=CenterRight.x-sptrl->GetValue()-textwidth;
      Offset_y=CenterRight.y+sptrl1->GetValue();
    }
    
    layername=textctrl->GetValue();
    textname=textctrl1->GetValue();
    font=fontpicker->GetSelectedFont();
    TextColour=fontpicker->GetSelectedColour();
    ForeColour=cptrl->GetColour();
    isvisible=cbox->GetValue();
    showboundarybox=cbox1->GetValue();
    angle=sptrl3->GetValue();
    return;
  }
};
class BilateralFilterDialog:public wxDialog{
   private:
   int size;
   int sigmacolour;
   int sigmaspace;
   void PressOk(wxCommandEvent& event){
    InitAllValues();
    EndModal(wxID_OK);
   }
   public:
   BilateralFilterDialog(wxWindow* win,const int& size,const int& sigma,const int& sigma1):wxDialog(win,wxID_ANY,wxT("Bilateral Filter Dialog"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
     CreateControls(size,sigma,sigma1);
     ShowModal();
     Bind(wxEVT_BUTTON,&PressOk,this,wxID_OK);
   }
   void CreateControls(const int& sz1,const int& sigma,const int& sigma2){
    wxStaticText* stext=new wxStaticText(this,wxID_ANY,wxT("size:"));
    wxStaticText* stext1=new wxStaticText(this,wxID_ANY,wxT("sigma space:"));
    wxStaticText* stext2=new wxStaticText(this,wxID_ANY,wxT("sigma colour:"));
    wxSpinCtrl* sptrl=new wxSpinCtrl(this,lsp,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0);
    wxSpinCtrl* sptrl1=new wxSpinCtrl(this,lsp1,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0);
    wxSpinCtrl* sptrl2=new wxSpinCtrl(this,lsp8,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0);
     wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
     wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
     wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
     wxBoxSizer* bsizer1=new wxBoxSizer(wxHORIZONTAL);
     wxBoxSizer* bsizer2=new wxBoxSizer(wxHORIZONTAL);
     SetSizer(bsizer);
     bsizer->Add(bsizer2,0,wxALIGN_LEFT|wxALL,5);
     bsizer2->Add(stext,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
     bsizer2->Add(sptrl,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
     bsizer2->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
     bsizer2->Add(stext1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
     bsizer2->Add(sptrl1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
     bsizer2->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
     bsizer2->Add(stext2,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
     bsizer2->Add(sptrl2,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
     bsizer->Add(bsizer1,0,wxALIGN_RIGHT|wxALL,5);
     bsizer1->Add(button,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer1->Add(button1,wxALIGN_CENTER_VERTICAL|wxALL,0);
    return;
}
int GetSize() const{
  return size;
}
int GetSigmaColour() const{
  return sigmacolour;
}
int GetSigmaSpace() const{
  return sigmaspace;
}
void InitAllValues(){
   wxSpinCtrl* sptrl=(wxSpinCtrl*)FindWindow(lsp);
   wxSpinCtrl* sptrl1=(wxSpinCtrl*)FindWindow(lsp1);
   wxSpinCtrl* sptrl3=(wxSpinCtrl*)FindWindow(lsp8);
  size=sptrl->GetValue();
  sigmacolour=sptrl1->GetValue();
  sigmaspace=sptrl3->GetValue();
  return;
}
};
class NormalizedBlurFilter:public wxDialog{
   private:
   int size;
  
   void PressOk(wxCommandEvent& event){
    InitAllValue();
    EndModal(wxID_OK);
   }
   public:
    NormalizedBlurFilter(wxWindow* win,const int& size1):wxDialog(win,wxID_ANY,wxT("Normalized blur Filter"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
    CreateControls(size1);
    ShowModal();
    Bind(wxEVT_BUTTON,&PressOk,this,wxID_OK);
   }
   void CreateControls(const int& sz){
    wxStaticText* stext=new wxStaticText(this,wxID_ANY,wxT("size:"));
    wxStaticText* stext1=new wxStaticText(this,wxID_ANY,wxT("Specify odd numbers for the size"));
    wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
    wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
    wxSpinCtrl* sptrl=new wxSpinCtrl(this,lsp,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0);
    
    sptrl->SetValue(sz);
    wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bsizer1=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer2=new wxBoxSizer(wxHORIZONTAL);
    SetSizer(bsizer);
    bsizer->Add(stext1,0,wxALL,5);
    bsizer->Add(bsizer1,0,wxALL,5);
    bsizer1->Add(stext,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer1->Add(sptrl,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer->Add(bsizer2,0,wxALIGN_RIGHT|wxALL,5);
    bsizer2->Add(button,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer2->Add(button1,wxALIGN_CENTER_VERTICAL|wxALL,0);
    return;
}
  int GetSize() const{
    return size;
  }
  void InitAllValue() {
    wxSpinCtrl* sptrl=(wxSpinCtrl*)FindWindow(lsp);
    size=sptrl->GetValue();
    return;
  }
};
class BoxFilter:public wxDialog{
   private:
   int size;
   bool isnormalized;
   void PressOk(wxCommandEvent& event){
    InitAllValue();
    EndModal(wxID_OK);
   }
   public:
  BoxFilter(wxWindow* win,const int& size1,bool normal ):wxDialog(win,wxID_ANY,wxT("Box Filter"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
    CreateControls(size1,normal);
    ShowModal();
    Bind(wxEVT_BUTTON,&PressOk,this,wxID_OK);
   }
   void CreateControls(const int& sz,bool normal){
    wxStaticText* stext=new wxStaticText(this,wxID_ANY,wxT("size:"));
    wxStaticText* stext1=new wxStaticText(this,wxID_ANY,wxT("Specify odd numbers for the size"));
    wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
    wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
    wxSpinCtrl* sptrl=new wxSpinCtrl(this,lsp,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0); 
    wxCheckBox* cbox=new wxCheckBox(this,lsp4,wxT("Normalize"),wxDefaultPosition,wxDefaultSize,wxCHK_2STATE);
    sptrl->SetValue(sz);
    cbox->SetValue(normal);
    wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bsizer1=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer2=new wxBoxSizer(wxHORIZONTAL);
    SetSizer(bsizer);
    bsizer->Add(stext1,0,wxALL,5);
    bsizer->Add(bsizer1,0,wxALL,5);
    bsizer1->Add(stext,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer1->Add(sptrl,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer1->Add(5,5,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer1->Add(cbox,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer->Add(bsizer2,0,wxALIGN_RIGHT|wxALL,5);
    bsizer2->Add(button,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer2->Add(button1,wxALIGN_CENTER_VERTICAL|wxALL,0);
    return;
}
  int GetSize() const{
    return size;
  }
  bool IsNormalized() const{
    return isnormalized;
  }
  void InitAllValue() {
    wxSpinCtrl* sptrl=(wxSpinCtrl*)FindWindow(lsp);
    wxCheckBox* cbox=(wxCheckBox*)FindWindow(lsp4);
    size=sptrl->GetValue();
    isnormalized=cbox->GetValue();
    return;
  }
};
class Filter2D:public wxDialog{
 private:
 //To construct the gaussian filter....
 int sigma;
 int ksize;
 bool isConvolution;
 //delta value that wil be added to the destination of the output image.
 int delta;
 void PressOk(wxCommandEvent& event){
  InitAllValue();
  EndModal(wxID_OK);
 }
 public:
 Filter2D(wxWindow* win,const int& sigma1,const int& ksize1,const int& delta1,bool convolve):wxDialog(win,wxID_ANY,wxT("Filter2D"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
  CreateControls(sigma,ksize1,delta,convolve);
  ShowModal();
  Bind(wxEVT_BUTTON,&PressOk,this,wxID_OK);
 } 
 void CreateControls(const int& sig,const int& k,const int& del,bool convolve){
   wxStaticText* stext=new wxStaticText(this,wxID_ANY,wxT("Specify the sigma,size and delta and Choose either convolution or correlation "));
   wxStaticText* stext1=new wxStaticText(this,wxID_ANY,wxT("Construct Kernel:"));
   wxStaticText* stext2=new wxStaticText(this,wxID_ANY,wxT("Input Delta:"));
   wxStaticText* stext3=new wxStaticText(this,wxID_ANY,wxT("Sigma:"));
   wxStaticText* stext4=new wxStaticText(this,wxID_ANY,wxT("Size:"));
   wxStaticText* stext5=new wxStaticText(this,wxID_ANY,wxT("Delta:"));
   wxSpinCtrl* sptrl=new wxSpinCtrl(this,lsp,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0); 
   wxSpinCtrl* sptrl1=new wxSpinCtrl(this,lsp1,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0);  
   wxSpinCtrl* sptrl2=new wxSpinCtrl(this,lsp2,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0); 
   sptrl->SetValue(sig);
   sptrl1->SetValue(k);
   sptrl2->SetValue(del);
   wxCheckBox* cbox=new wxCheckBox(this,lsp4,wxT("Convolution"),wxDefaultPosition,wxDefaultSize,wxCHK_2STATE);
   cbox->SetValue(convolve);
   wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
    wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
    wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bsizer1=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer2=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer3=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer4=new wxBoxSizer(wxHORIZONTAL);
    SetSizer(bsizer);
    bsizer->Add(stext,0,wxALIGN_LEFT|wxALL,5);
    bsizer->Add(stext1,0,wxALIGN_LEFT|wxALL,5);
    bsizer->Add(bsizer1,0,wxALL,5);
    bsizer1->Add(stext3,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer1->Add(sptrl,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer1->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
    bsizer1->Add(stext4,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer1->Add(sptrl1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer->Add(bsizer2,0,wxALL,5);
    bsizer2->Add(cbox,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer->Add(stext2,0,wxALL,5);
    bsizer->Add(bsizer3,0,wxALL,5);
    bsizer3->Add(stext5,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer3->Add(sptrl2,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer->Add(bsizer4,0,wxALIGN_RIGHT|wxALL,5);
    bsizer4->Add(button,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer4->Add(button1,wxALIGN_CENTER_VERTICAL|wxALL,0);
    return;
}
void InitAllValue(){
  wxSpinCtrl* sptrl=(wxSpinCtrl*)FindWindow(lsp);
  wxSpinCtrl* sptrl1=(wxSpinCtrl*)FindWindow(lsp1);
  wxSpinCtrl* sptrl2=(wxSpinCtrl*)FindWindow(lsp2);
  wxCheckBox* cbox=(wxCheckBox*)FindWindow(lsp4);
  
  sigma=sptrl->GetValue();
  ksize=sptrl1->GetValue();
  delta=sptrl2->GetValue();
  isConvolution=cbox->GetValue();
  
  return;
  }
int GetSigma() const{
  return sigma;
}
int GetSize() const{
  return ksize;
}
int GetDelta() const {
  return delta;
}
bool IsConvolution() const {
  return isConvolution;
}
};

class LaplacianDialog:public wxDialog{
  private:
  int ksize;
  int scale;
  int delta;
  void PressOk(wxCommandEvent& event){
    Init();
    EndModal(wxID_OK);
  }
  public:
  LaplacianDialog(wxWindow* win,const int& ksize1,const int& scale1,const int& delta1):wxDialog(win,wxID_ANY,wxT("LaplacianDialog"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
   CreateControls(ksize,scale1,delta1);
   ShowModal();
   Bind(wxEVT_BUTTON,&PressOk,this,wxID_OK);
}
 void CreateControls(const int& k,const int& s,const int& del){
 wxStaticText* stext=new wxStaticText(this,wxID_ANY,wxT("Specify Size(NB: size must be odd number),scale(Optional parameter),delta(this is Optional)"));
 wxStaticText* stext1=new wxStaticText(this,wxID_ANY,wxT("Parameter:"));
 wxStaticText* stext2=new wxStaticText(this,wxID_ANY,wxT("Size:"));
 wxStaticText* stext3=new wxStaticText(this,wxID_ANY,wxT("Scale:"));
 wxStaticText* stext4=new wxStaticText(this,wxID_ANY,wxT("Delta:"));
 wxSpinCtrl* sptrl=new wxSpinCtrl(this,lsp,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0); 
 wxSpinCtrl* sptrl1=new wxSpinCtrl(this,lsp1,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0);  
 wxSpinCtrl* sptrl2=new wxSpinCtrl(this,lsp2,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0); 
 sptrl->SetValue(k);
 sptrl1->SetValue(s);
 sptrl2->SetValue(del);
  wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
  wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
  wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* bsizer1=new wxBoxSizer(wxHORIZONTAL);
  wxBoxSizer* bsizer2=new wxBoxSizer(wxHORIZONTAL);
  SetSizer(bsizer);
  bsizer->Add(stext,0,wxALL,5);
  bsizer->Add(stext1,0,wxALL,5);
  bsizer->Add(bsizer1,0,wxALL,5);
  bsizer1->Add(stext2,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
  bsizer1->Add(sptrl,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
  bsizer1->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
  bsizer1->Add(stext3,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
  bsizer1->Add(sptrl1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
  bsizer1->Add(5,5,0,wxALIGN_CENTER_VERTICAL|wxALL,5);
  bsizer1->Add(stext4,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
  bsizer1->Add(sptrl2,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
  bsizer->Add(bsizer2,0,wxALIGN_RIGHT|wxALL,5);
  bsizer2->Add(button,wxALIGN_CENTER_VERTICAL|wxALL,0);
  bsizer2->Add(button1,wxALIGN_CENTER_VERTICAL|wxALL,0);
    return;
}
void Init(){
  wxSpinCtrl* sptrl=(wxSpinCtrl*)FindWindow(lsp);
  wxSpinCtrl* sptrl1=(wxSpinCtrl*)FindWindow(lsp1);
  wxSpinCtrl* sptrl2=(wxSpinCtrl*)FindWindow(lsp2);
  ksize=sptrl->GetValue();
  scale=sptrl1->GetValue();
  delta=sptrl2->GetValue();
  return;
}
int GetSize() const {
  return ksize;
}
int GetScale() const {
  return scale;
}
int GetDelta() const{
  return delta;
}
};
class MedianBlurDialog:public wxDialog{
  private:
  int ksize;
  void PressOk(wxCommandEvent& event){
    Init();
    EndModal(wxID_OK);
  }
  public:
  MedianBlurDialog(wxWindow* win,const int& k):wxDialog(win,wxID_ANY,wxT("MedianBlurDialog"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
   CreateControls(k);
   ShowModal();
   Bind(wxEVT_BUTTON,&PressOk,this,wxID_OK);
  }
  void CreateControls(const int& ksize){
    wxStaticText* stext1=new wxStaticText(this,wxID_ANY,wxT("MedianSize:"));
    wxSpinCtrl* sptrl=new wxSpinCtrl(this,lsp,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0); 
    wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bsizer1=new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* bsizer2=new wxBoxSizer(wxHORIZONTAL);
    wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
    wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
    SetSizer(bsizer);
    sptrl->SetValue(ksize);
    bsizer->Add(bsizer1,0,wxALIGN_LEFT|wxALL,5);
    bsizer1->Add(stext1,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer1->Add(sptrl,0,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer->Add(bsizer2,0,wxALIGN_RIGHT|wxALL,5);
    bsizer2->Add(button,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer2->Add(button1,wxALIGN_CENTER_VERTICAL|wxALL,0);
    return;
  }
  void Init(){
  wxSpinCtrl* sptrl=(wxSpinCtrl*)FindWindow(lsp);
  ksize=sptrl->GetValue();
  return;
  }
  int GetMedianSize() const{
    return ksize;
  }
};
class GaussianBlurDialog:public wxDialog{
 private:
int ksize;
int sigmax;
int sigmay;
int denom;
void PressOk(wxCommandEvent& event){
  Initialize();
  EndModal(wxID_OK);
  return;
}
 public:
GaussianBlurDialog(wxWindow* win,const int& sz,const int& sigmax1,const int& sigmay1):wxDialog(win,wxID_ANY,wxT("GaussianBlurDialog"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
  CreateControls(sz,sigmax1,sigmay1);
  ShowModal();
  Bind(wxEVT_BUTTON,&PressOk,this,wxID_OK);
}
void CreateControls(const int& a,const int& x,const int& y){
  wxStaticText* stext1=new wxStaticText(this,wxID_ANY,wxT("KernelSize:"));
   wxStaticText* stext2=new wxStaticText(this,wxID_ANY,wxT("sigma-x:"));
   wxStaticText* stext3=new wxStaticText(this,wxID_ANY,wxT("sigma-y:"));
   wxStaticText* stext4=new wxStaticText(this,wxID_ANY,wxT("denominator:"));
   wxSpinCtrl* sptrl=new wxSpinCtrl(this,lsp,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0); 
   wxSpinCtrl* sptrl1=new wxSpinCtrl(this,lsp1,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0);
   wxSpinCtrl* sptrl2=new wxSpinCtrl(this,lsp2,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0); 
   wxSpinCtrl* sptrl3=new wxSpinCtrl(this,lsp3,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0); 
   sptrl->SetValue(a);
   sptrl1->SetValue(x);
   sptrl2->SetValue(y);
   wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
    wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
   wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* bsizer2=new wxBoxSizer(wxHORIZONTAL);
  SetSizer(bsizer);
  bsizer->Add(stext1,0,wxALL,5);
  bsizer->Add(sptrl,0,wxALL,5);
  bsizer->Add(stext2,0,wxALL,5);
  bsizer->Add(sptrl1,0,wxALL,5);
  bsizer->Add(stext3,0,wxALL,5);
  bsizer->Add(sptrl2,0,wxALL,5);
  bsizer->Add(stext4,0,wxALL,5);
  bsizer->Add(sptrl3,0,wxALL,5);
   bsizer->Add(bsizer2,0,wxALIGN_RIGHT|wxALL,5);
    bsizer2->Add(button,wxALIGN_CENTER_VERTICAL|wxALL,0);
    bsizer2->Add(button1,wxALIGN_CENTER_VERTICAL|wxALL,0);
    return;
}
void Initialize(){
  wxSpinCtrl* sptrl=(wxSpinCtrl*)FindWindow(lsp);
  wxSpinCtrl* sptrl1=(wxSpinCtrl*)FindWindow(lsp1);
  wxSpinCtrl* sptrl2=(wxSpinCtrl*)FindWindow(lsp2);
  wxSpinCtrl* sptrl3=(wxSpinCtrl*)FindWindow(lsp3);
  ksize=sptrl->GetValue();
  sigmax=sptrl1->GetValue();
  sigmay=sptrl2->GetValue();
  denom=sptrl3->GetValue();
  return;
}
int GetSize() const{
  return ksize;
}
int GetSigmaX() const{
  return sigmax;
}
int GetSigmaY() const{
  return sigmay;
}
int GetDenominator() const{
  return denom;
}
};
class SobelDialog:public wxDialog{
 private:
 int x_order;
 int y_order;
 int size;
 void PressOk(wxCommandEvent& event){
  Initialize();
  EndModal(wxID_OK);
 }
 public:
 SobelDialog(wxWindow* win,const int& x,const int& y,const int& sz):wxDialog(win,wxID_ANY,wxT("SobelDialog"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
  CreateControls(x,y,sz);
  ShowModal();
  Bind(wxEVT_BUTTON,&PressOk,this,wxID_OK);
 }
 void CreateControls(const int& xorder,const int& yorder,const int& sz){
  wxStaticText* stext1=new wxStaticText(this,wxID_ANY,wxT("Specify the order of derivative for both x and y"));
  wxStaticText* stext2=new wxStaticText(this,wxID_ANY,wxT("X-order:"));
  wxStaticText* stext3=new wxStaticText(this,wxID_ANY,wxT("Y-order:"));
  wxStaticText* stext4=new wxStaticText(this,wxID_ANY,wxT("KernelSize:"));
  wxSpinCtrl* sptrl=new wxSpinCtrl(this,lsp,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0); 
  wxSpinCtrl* sptrl1=new wxSpinCtrl(this,lsp1,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0);
  wxSpinCtrl* sptrl2=new wxSpinCtrl(this,lsp2,wxEmptyString,wxDefaultPosition,wxDefaultSize,wxSP_ARROW_KEYS,0,10000,0); 
  sptrl->SetValue(xorder);
  sptrl1->SetValue(yorder);
  sptrl2->SetValue(sz);
   wxButton* button=new wxButton(this,wxID_OK,wxT("Ok"));
  wxButton* button1=new wxButton(this,wxID_CANCEL,wxT("Cancel"));
  wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
  wxBoxSizer* bsizer2=new wxBoxSizer(wxHORIZONTAL);
  SetSizer(bsizer);
  bsizer->Add(stext1,0,wxALL,5);
  bsizer->Add(5,5,0,wxALIGN_LEFT|wxALL,5);
  bsizer->Add(stext2,0,wxALL,5);
  bsizer->Add(sptrl,0,wxALL,5);
  bsizer->Add(stext3,0,wxALL,5);
  bsizer->Add(sptrl1,0,wxALL,5);
  bsizer->Add(stext4,0,wxALL,5);
  bsizer->Add(sptrl2,0,wxALL,5);
  bsizer->Add(bsizer2,0,wxALIGN_RIGHT|wxALL,5);
  bsizer2->Add(button,wxALIGN_CENTER_VERTICAL|wxALL,0);
  bsizer2->Add(button1,wxALIGN_CENTER_VERTICAL|wxALL,0);
  return;
}
void Initialize(){
  wxSpinCtrl* sptrl=(wxSpinCtrl*)FindWindow(lsp);
  wxSpinCtrl* sptrl1=(wxSpinCtrl*)FindWindow(lsp1);
  wxSpinCtrl* sptrl2=(wxSpinCtrl*)FindWindow(lsp2);
  x_order=sptrl->GetValue();
  y_order=sptrl1->GetValue();
  size=sptrl2->GetValue();
  return;
}
int GetXOrder() const {
  return x_order;
}
int GetYOrder() const {
  return y_order;
}
int GetSize() const {
  return size;
}
};
class PencilSketchDialog:public wxDialog{
  
};