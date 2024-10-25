#include<wx/colour.h>
#include<wx/font.h>
#include<wx/string.h>
#include<wx/gdicmn.h>
class LayerText{
private:
  wxString textname;
  wxColour Textcolour;
  wxColour Forecolour;
  double angle;
  wxPoint origin;
  wxFont font;
  bool isvisible;    //This type makes the layer visible on the screen
  bool showboundarybox;  //This object shows the boundary box of the text Layer..
  public:
 static double Convert(const double& ang ){
 const double pi=3.14159265;
   double value=ang*(pi/180);
   return value;
}

  LayerText()=default;
  LayerText(const wxString& str,const wxColour& colour,const wxColour& colour1,const double angle1,const wxPoint origin1,const wxFont font1,bool visible,bool show ){
    textname=str;
    Textcolour=colour;
    Forecolour=colour1;
    angle=angle1;
    origin=origin1;
    font=font1;
    isvisible=visible;
    showboundarybox=show;
  }
  LayerText(const LayerText& layer){
    *this={layer.GetTextname(),layer.GetTextColour(),layer.GetForeColour(),layer.GetAngle(),layer.GetOrigin(),layer.GetFont(),layer.GetVisibility(),layer.ShowBoundaryBox()};
  }
  void SetTextname(const wxString& str){
    textname=str;
    return;
  }
  wxString GetTextname() const{
    return textname;
  }
  void SetTextColour(const wxColour& colour){
    Textcolour=colour;
  }
  wxColour GetTextColour() const{
    return Textcolour;
  }
  void SetForeColour(const wxColour& colour){
    Forecolour=colour;
  }
  wxColour GetForeColour() const{
    return Forecolour;
  }
  void SetAngle(const int& ang){
   angle=LayerText::Convert((double)ang);

  }
  double GetAngle() const{
    return angle;
  }
  void SetOrigin(const wxPoint& point){
    origin=point;
  }
  wxPoint GetOrigin() const{
    return origin;
  }
  void SetFont(const wxFont& font1){
    font=font1;
    return;
  }
  wxFont GetFont() const{
    return font;
  }
  void SetVisibility(bool truth){
    isvisible=truth;
    return;
  }
  bool GetVisibility() const{
    return isvisible;
  }
 
  bool ShowBoundaryBox() const{
    return showboundarybox;
  }
  void SetShowBoundaryBox(bool show) {
    showboundarybox=show;
    return;
  }
};