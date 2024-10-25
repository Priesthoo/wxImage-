#ifndef DATAVIEW
#define DATAVIEW
#endif
/*
This class is intended to hold layers created in the scene,and if clicked,it will render the layer within the layerpanel....

*/
#include<wx/dataview.h>
#include<wx/variant.h>
#include<ListBox.h>
#include<wx/vector.h>
#include<wx/menu.h>
#include<wx/window.h>
#include<map>
#include<wx/image.h>
#include<ImageDialog.h>
const int v1=50;
const int v2=51;
enum LAYER_TYPE{
 TEXT_LAYER,
 ARC_LAYER,
 RECT_LAYER,
 BITMAP_LAYER,
 ELLIPSE_LAYER,
 BRUSH_LAYER
};
class LayerTextType{
  private:
  LayerText textlayer;
  wxString Type;
  
  public:
  LayerTextType()=default;
  LayerTextType(const LayerText& layer,const wxString& str):textlayer{layer},Type{str}{}
LayerText GetTextLayer() const{
    return textlayer;
  }
  wxString GetType() const{
    return Type;
  }
};
class LayerManager:public wxDataViewListCtrl{
 private:
 int no_of_element;
 std::map<wxString,LayerText&>textlayertype;
 wxImage image;
 void DataViewItemClicked(wxDataViewEvent& event){
    if(GetSelectedRow()!=wxNOT_FOUND){
      no_of_element=event.GetColumn();
      wxMenu*menu=new wxMenu;
      menu->Append(v1,wxT("View"));
     menu->Append(v2,wxT("Delete"));
      PopupMenu(menu,event.GetPosition());
      }
 }
 void ClickItemMenu(wxCommandEvent& evt){
    if(GetSelectedRow()!=wxNOT_FOUND){
      int found=GetSelectedRow();
      wxString val=GetTextValue(found,no_of_element);
       if(val!=wxT("")){
        std::map<wxString,LayerText&>::iterator pos;
        pos=textlayertype.find(val);
        if(pos!=textlayertype.end()){
          TextLayerDialog dlg(this,GetImage(),pos->second);
          if(dlg.ShowModal()==wxID_OK){
            pos->second.SetTextname(dlg.GetTextName());
            pos->second.SetFont(dlg.Getfont());
            pos->second.SetShowBoundaryBox(dlg.ShowBoundaryBox());
            pos->second.SetVisibility(dlg.GetVisibility());
            pos->second.SetOrigin(wxPoint(dlg.GetOffset_X(),dlg.GetOffset_Y()));
            pos->second.SetForeColour(dlg.GetForeColour());
            pos->second.SetTextColour(dlg.GetTextColour());
          }
        }
}
}
    }
  void ClickDelete(wxCommandEvent& event){
    if(GetSelectedRow()!=wxNOT_FOUND){
      int f=GetSelectedRow();
      DeleteItem(f);
      return;
    }
    return;
  }
 
 public:
 LayerManager(wxWindow* win,wxWindowID id=-1,const wxPoint& point=wxDefaultPosition,const wxSize& size=wxDefaultSize,long style=wxDV_ROW_LINES|wxDV_HORIZ_RULES):wxDataViewListCtrl(win,id,point,size,style){
   AppendTextColumn(wxT("Layer Item"));
   AppendTextColumn(wxT("Type"));
   
   Bind(wxEVT_DATAVIEW_ITEM_ACTIVATED,&DataViewItemClicked,this);
   Bind(wxEVT_MENU,&ClickItemMenu,this,v1);
   Bind(wxEVT_MENU,&ClickDelete,this,v2);

 }
 void AppendTextLayer(LayerText& type,const wxString& layername){
  wxString str=wxT("Text");
  textlayertype.insert(std::map<wxString,LayerText&>::value_type(layername,type));
  wxVector<wxVariant> data;
  data.push_back(wxVariant(layername));
  data.push_back(wxVariant(str));
  AppendItem(data);
  data.clear();
 }
 void Clear(){
  textlayertype.clear();
  return;
 }
  int Get_No_of_Element() const{
    return no_of_element;
  }
  void Set_No_of_Element(const int& element){
    no_of_element=element;
  }
  void SetImage(const wxImage& image1){
    image=image1;
    return;
  }

  wxImage GetImage() const{
    return image;
  }
   
};