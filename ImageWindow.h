#include<wx/scrolwin.h>
#include<wx/dcmemory.h>
#include<wx/panel.h>
#include<wx/bitmap.h>
#include<wx/image.h>
#include<wx/dc.h>
#include<wx/dcclient.h>
#include<wx/dcgraph.h>
#include<wx/dcbuffer.h>
#include<wx/sashwin.h>
#include<wx/menu.h>
#include<wx/gdicmn.h>
#include<wx/fontdlg.h>
#include<vector>
#include<wx/pen.h>
#include<Layer.h>
#include<wx/checkbox.h>
#include<opencv2/opencv.hpp>
#include<ImageTrans.h>
#include<wx/affinematrix2d.h>
#include<wx/geometry.h>
#include<wx/dialog.h>
#include<wx/panel.h>
#include<wx/sizer.h>
using namespace std;
#ifdef IMAGE_H
#define IMAGE_H
#endif
const int menuitem0=0;
const int menuitem1=1;
const int menuitem2=2;
const int menuitem3=3;
const int menuitem4=45;
const int menuitem5=46;
const int menuitem6=47;
const int boxitem=49;
const int boxitem1=50;
const int boxitem2=51;
const int uniqueone=100;
const int u1=101;
const int u2=102;
const int u3=103;
long GetValidPosition(const wxImage& image,int x, int y){
   if(image.IsOk() && x>=0 && y>=0 && x<image.GetWidth() && y<image.GetHeight()){
      return y*image.GetWidth()+x;
   }
   return -1;
}

/*
Noun:ImageCanvas->This is a class designed to draw image on the screen,set images within a clipboard....
Verbs:GetBitmap()->it returns the current bitmap on display.....
       

*/
//We need to add the drawing functions within this file.....
class BlurTool{
  private:
  cv::Mat Image;
  public:
  BlurTool()=default;
  void ConstructBlurImage(const cv::Mat& Image1){
    if(Image1.empty()){
        return;
    }
    Image=Image1.clone();
    cv::blur(Image1,Image,cv::Size(3,3));
  }
  BlurTool(const cv::Mat& image){
    if(!image.empty()){
    ConstructBlurImage(image);
    }
}
 cv::Mat GetBlurImage() const{
    if(!Image.empty()){
      return Image;
    }
    return cv::Mat();
 }
};
class Renderer:public wxDialog{
   private:
  
   wxImage image1;
   void Render(wxPaintEvent& paintevent){
    wxBufferedPaintDC paintdc(this);
    paintdc.SetBrush(*wxBLACK_BRUSH);
    paintdc.Clear();
    wxBitmap bitmap(image1);
    if(!bitmap.IsOk()){
        return;
    }
    if(paintdc.CanDrawBitmap()){
        paintdc.DrawBitmap(bitmap,wxPoint(0,0));
    }
   }
   public:
   Renderer(wxWindow* win,wxImage image):wxDialog(win,wxID_ANY,wxT("PotterImage"),wxDefaultPosition,wxDefaultSize,wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER){
     image1=image;
     Bind(wxEVT_PAINT,&Render,this);
     ShowModal();
   }
  

};

class RenderBox:public wxRect{
    public:
 RenderBox(const int& x,const int& y,const int& w,const int& h):wxRect(x,y,w,h){
    

 }
 RenderBox()=default;
 bool IsDrawBox() const{
    if(height<=0 && (width<=0)){
        return false;
    }
    return true;
 }
};




class ImageCanvas:public wxScrolled<wxPanel>{      //Anytime object.Refresh() is called, object of this class calls the paint event handler
    private:  
    wxImage image;
    cv::Mat Image; //OpenCv Image
    wxImageResizeQuality quality;
    float zoomfactor;
    wxPoint origin;
    bool isLoaded;
    wxColour BrushColour;
    wxPoint current;
    int Keyvalue_x;
    int Keyvalue_y;
    bool upscale;
    int upscalewidth;
    int upscaleheight;
    bool can_draw_text;
    LayerText TextLayer;
    std::vector<LayerText> TextLayerArray;
    bool isblur;
    bool canErase;
    RenderBox DrawBox;
    bool can_draw_rect;
    //This represent changes in the origin of the draw of rectangle     rect.draw().
    int dx;
    int dy;
    wxPoint currentpos;
    bool iszoomfactor;
    public:
    void OnDraw(wxPaintEvent& evt){
      //Get Bitmap,then convert it to image...
        wxBrush backgroundbrush;
        wxBitmap bitmap(image);
        wxBufferedPaintDC paintdc(this);
        DoPrepareDC(paintdc);
        backgroundbrush.SetColour(BrushColour);
        paintdc.SetBrush(backgroundbrush);
        paintdc.SetDeviceOrigin(0,0);
        paintdc.Clear();
        if(bitmap.IsOk()){
        wxBitmap bitmap1=GetBitmapFromImage();
        if(can_draw_text==true){
          if(!TextLayerArray.empty()){
            for(int i=0;i<TextLayerArray.size();i++){
                if(TextLayerArray.at(i).GetVisibility()==true){
                  wxMemoryDC memdc;
                  memdc.SelectObject(bitmap1);
                  memdc.SetFont(TextLayerArray.at(i).GetFont());
                  memdc.SetTextBackground(TextLayerArray.at(i).GetTextColour());
                  memdc.SetTextForeground(TextLayerArray.at(i).GetForeColour());
                  if(TextLayerArray.at(i).ShowBoundaryBox()==true){
                    wxPoint point=TextLayerArray.at(i).GetOrigin();
                    point.x=point.x;
                    point.y=point.y+0;
                    wxPen drawpen(wxColour(10,10,10));
                    memdc.SetPen(drawpen);
                    memdc.SetBrush(*wxTRANSPARENT_BRUSH);
                    int width=0;
                    int height=0;
                    memdc.GetTextExtent(TextLayerArray.at(i).GetTextname(),&width,&height);
                    wxRect rect(wxPoint(point.x,point.y),wxSize(width,height));
                    memdc.DrawPoint(rect.GetTopLeft());
                    memdc.DrawPoint(rect.GetBottomLeft());
                    memdc.DrawPoint(rect.GetBottomRight());
                    memdc.DrawPoint(rect.GetTopRight());
                    memdc.DrawPoint(rect.GetTop(),rect.GetBottom());
                   memdc.DrawRectangle(wxRect(wxPoint(point.x,point.y),wxSize(width,height)));
                }
                wxPoint point=TextLayerArray.at(i).GetOrigin();
                point.x=point.x;
                point.y=point.y+0;
                memdc.DrawRotatedText(TextLayerArray.at(i).GetTextname(),point,TextLayerArray.at(i).GetAngle());
                memdc.SelectObject(wxNullBitmap);
                if(paintdc.CanDrawBitmap()){
                 paintdc.DrawBitmap(bitmap1,wxPoint(300+Keyvalue_x,0+Keyvalue_y));
                }
            }
          }
}
}      if(can_draw_rect==true){
        wxMemoryDC memdc;
        memdc.SelectObject(bitmap1);
        memdc.SetBrush(*wxTRANSPARENT_BRUSH);
        memdc.SetPen(*wxWHITE_PEN);
        if(DrawBox.IsDrawBox()==false){
           DrawBox.width=100;
           DrawBox.height=100;
           DrawBox.x=0;
           DrawBox.y=0;
           dx=0;
           dy=0;
        }
        memdc.DrawRectangle(DrawBox);
        memdc.SelectObject(wxNullBitmap);
        
}
        if(zoomfactor<=0){
            iszoomfactor=false;
            if(bitmap1.IsOk()){
                paintdc.DrawBitmap(bitmap1,wxPoint(300+Keyvalue_x,Keyvalue_y+0));
            }
            return;
        }
        if(zoomfactor>0){
        wxMemoryDC memdc;
        iszoomfactor=true;
        memdc.SelectObject(bitmap1);   
        paintdc.StretchBlit(300+Keyvalue_x,0+Keyvalue_y,bitmap1.GetWidth()*zoomfactor,bitmap1.GetHeight()*zoomfactor,&memdc,0,0,bitmap1.GetWidth(),bitmap.GetHeight());
        memdc.SelectObject(wxNullBitmap);
        return;
        }
    }
    }
    void MouseKeyPressed(wxMouseEvent& event){
      if(event.GetWheelRotation()>0){
        ++zoomfactor;
    }
      else{
        --zoomfactor;
    }
      Refresh();
        return;
    }
    
    void MoveScreenContent(wxKeyEvent& event){
        int keycode=event.GetKeyCode();
        if(keycode==WXK_LEFT){
            Keyvalue_x-=30;
            Refresh();
            return;
        }
        else if(keycode==WXK_UP){
            Keyvalue_y-=30;
            Refresh();
          return;
        }
        else if(keycode==WXK_RIGHT){
            Keyvalue_x+=30;
            Refresh();
            return;
        }
        else if(keycode==WXK_DOWN){
            Keyvalue_y+=30;
            Refresh();
            return;
        }
        else if(keycode==WXK_NUMPAD8){
            dy-=2;
            if(dy<0){
                dy=dy;
            }
            else{
                dy=-dy;
            }
          DrawBox.y+=dy;
            Refresh();
            return;
        }
        else if(keycode==WXK_NUMPAD2){
            dy+=2;
            if(dy<0){
                dy=-dy+dy+2;
            }
            else{
                dy=dy;
            }
            DrawBox.y+=dy;
            Refresh();
            return;
        }
        else if(keycode==WXK_NUMPAD6){
            dx+=2;
             if(dx<0){
                dx=-dx+dx+2;
            }
            else{
                dx=dx;
            }
            DrawBox.x+=dx;
            Refresh();
            return;
        }
        else if(keycode==WXK_NUMPAD4){
            dx-=2;
             if(dx<0){
                dx=dx;
            }
            else{
                dx=-dx;
            }
            DrawBox.x+=dx;
       Refresh();
            return;
        }
        else if(keycode==WXK_NUMPAD_LEFT){
            if(DrawBox.width<=0){
                DrawBox.width=10;
            }
            DrawBox.width-=2;
            Refresh();
            return;
    }
     else if(keycode==WXK_NUMPAD_RIGHT){
            DrawBox.width+=2;
            Refresh();
            return;
    }
     else if(keycode==WXK_NUMPAD_UP){
            if(DrawBox.height<=0){
                DrawBox.height=10;
            }
            DrawBox.height-=2;
            Refresh();
            return;
    }
     else if(keycode==WXK_NUMPAD_DOWN){
            DrawBox.height+=2;
            Refresh();
            return;
    }
}
    void SetFont(wxCommandEvent& event){
    wxFontData fontdata;
    fontdata.SetChosenFont(TextLayer.GetFont());
    fontdata.SetColour(TextLayer.GetTextColour());
   wxFontDialog dialog(this,fontdata);
     if(dialog.ShowModal()==wxID_OK){
        TextLayer.SetFont(dialog.GetFontData().GetChosenFont());
        TextLayer.SetTextColour(dialog.GetFontData().GetColour());
        TextLayer.SetForeColour(dialog.GetFontData().GetColour());
     }
     Refresh();
     return;
    }
    void DisableText(wxCommandEvent& event){
        CanDrawText(false);
        Refresh();
        return;
    }
    void RefreshContent(wxCommandEvent& evt){
        Refresh();
        return;
    }
    void ResetDrawBox(wxCommandEvent& evt){
        DrawBox.x=0;
        DrawBox.y=0;
        dx=0;
        dy=0;
        DrawBox.width=100;
        DrawBox.height=100;
        Refresh();
    }
   void ClickMouseButton(wxMouseEvent& event){
    wxRect bound;
    int width;
    int height;
    width=DrawBox.width;
    height=DrawBox.height;
    if(zoomfactor<=0){
        bound.x=300+Keyvalue_x;
        bound.y=0+Keyvalue_y;
        bound.width=GetImageWidth();
        bound.height=GetImageHeight();
       
    }
    else{  // zoomfactor>=0
      bound.x=300+Keyvalue_x;
        bound.y=0+Keyvalue_y;
        bound.width=GetImageWidth()*zoomfactor;
        bound.height=GetImageHeight()*zoomfactor;
        width=DrawBox.width*zoomfactor;
        height=DrawBox.height*zoomfactor;
    }
     wxRect rect(DrawBox.x+300+Keyvalue_x,DrawBox.y+0+Keyvalue_y,width,height);
     if(can_draw_rect==true && (rect.Contains(event.GetPosition()))){
        wxMenu* menu=new wxMenu;
        menu->Append(boxitem2,wxT("Render Covered Image"));
        menu->Append(u1,wxT("Blur Section"));
        menu->Append(u2,wxT("Sharpen Section"));
        PopupMenu(menu,event.GetPosition());

        return;
     }

    wxPoint point(event.GetPosition());
    if(bound.Contains(point.x,point.y)){
        wxMenu* menu=new wxMenu;
        menu->Append(menuitem0,wxT("Draw Circle"));
        menu->Append(menuitem1,wxT("Open File"));
        menu->Append(menuitem3,wxT("Save File"));
        menu->Append(menuitem4,wxT("Disable RenderBox"));
        menu->Append(menuitem5,wxT("Disable Text"));
        menu->Append(menuitem6,wxT("Refresh"));
        menu->Append(boxitem,wxT("Render DrawBox"));
        menu->Append(boxitem1,wxT("Reset DrawBox"));
        PopupMenu(menu,point);
    }
      return;
   }
   void RenderCoveredImage(wxCommandEvent& event){
   wxImage image1=GetSubsetOfImage(DrawBox,image);
   if(!image1.IsOk()){
      return;
   }
    Renderer render(this,image1);
    render.Refresh();
     return;
   }
   void DisableRenderBox(wxCommandEvent& event){
    can_draw_rect=false;
    dx=0;
    dy=0;
    DrawBox.x=0;
    DrawBox.y=0;
    DrawBox.width=0;
    DrawBox.height=0;
    Refresh();

   }
   void BlurSubsetOfImage(wxCommandEvent& event){
    cv::Rect roi(DrawBox.x,DrawBox.y,DrawBox.width,DrawBox.height);
    cv::Mat subsetimage(Image,roi);
    cv::Mat copyimage=subsetimage.clone();
    cv::medianBlur(subsetimage,copyimage,11);
    if(copyimage.empty()){
        return;
    }
    wxImage image2=Convert(copyimage);
    if(!image2.IsOk()){
        return;
    }
    SetSubsetOfImage(image,image2,wxPoint(DrawBox.x,DrawBox.y));
    Refresh();
    return;

   }
 void SharpenSubsetOfImage(wxCommandEvent& event){
     cv::Rect roi(DrawBox.x,DrawBox.y,DrawBox.width,DrawBox.height);
    cv::Mat subsetimage(Image,roi);
    wxImage image2=ConstructSharpenedImage(subsetimage);
    if(!image2.IsOk()){
       return;
    }
    SetSubsetOfImage(image,image2,wxPoint(DrawBox.x,DrawBox.y));
    Refresh();
    return;
}
   void RenderRectangle(wxCommandEvent& event){
    can_draw_rect=true;
    Refresh();
   }
    public:
    ImageCanvas()=default;
    ImageCanvas(wxWindow* win,wxWindowID id=-1,const wxImage& image1=wxImage()):wxScrolled<wxPanel>(win,id,wxDefaultPosition,wxDefaultSize,wxBORDER_SUNKEN|wxFULL_REPAINT_ON_RESIZE){
        image=image1;
        
        SetBackgroundColour(wxColour(10,7,10));
        Bind(wxEVT_MOUSEWHEEL,&MouseKeyPressed,this);
        Bind(wxEVT_KEY_DOWN,&MoveScreenContent,this);
        Bind(wxEVT_PAINT,&OnDraw,this);
        Bind(wxEVT_RIGHT_DOWN,&ClickMouseButton,this);
        Bind(wxEVT_MENU,&DisableRenderBox,this,menuitem4);
        Bind(wxEVT_MENU,&DisableText,this,menuitem5);
        Bind(wxEVT_MENU,&RefreshContent,this,menuitem6);
        Bind(wxEVT_MENU,&RenderRectangle,this,boxitem);
        Bind(wxEVT_MENU,&ResetDrawBox,this,boxitem1);
        Bind(wxEVT_MENU,&RenderCoveredImage,this,boxitem2);
        Bind(wxEVT_MENU,&BlurSubsetOfImage,this,u1);
        Bind(wxEVT_MENU,&SharpenSubsetOfImage,this,u2);
        
    }
  void SetOpenCvImage(const cv::Mat& image1){
    if(image1.empty()){
      return;
    }
    Image=image1.clone();
    return;
  } 
   
    wxImage GetImage() const{    //current image on display.....
        return image;
    }
    void SetImage(const wxImage& image1){
        image=image1;     //Assign an image to it...
    }
    wxBitmap GetBitmapFromImage() const {   //Return a bitmap
        if(image.IsOk()){
            wxBitmap bitmap(image);
            return bitmap;
        }
        return wxNullBitmap;
    }
    
    wxImageResizeQuality& GetQuality(){
        return quality;
    }
    wxImageResizeQuality GetQuality() const{
        return quality;
    }
    float& GetZoomFactor() {
        return zoomfactor;
    }
    float GetZoomFactor() const{
      return zoomfactor;
    }
   
    void SetColourForBackground(const wxColour& colour){
        BrushColour=colour;
    }
    void SetOrigin(const wxPoint& point){
        origin=point;
    }
    wxPoint GetOrigin() const{
        return origin;
    }
    wxPoint GetCurrentValue() const{
        return current;
    }
    void SetKeyValue(const int& k,const int& k1){
        Keyvalue_x=k;
        Keyvalue_y=k1;
        return;
    }
    void SetUpScale( bool upscale_state,const int& width,const int& height){
        upscale=upscale_state;
        upscalewidth=width;
        upscaleheight=height;
 
    }
    
    int GetImageWidth() const {
        return GetImage().GetWidth();
    }
    int GetImageHeight() const{
        return GetImage().GetHeight();
    }
    
    void CanDrawText(bool truth){
        can_draw_text=truth;
    }
   void AppendTextLayer(const LayerText& layer){
    TextLayerArray.push_back(layer);
    return;
   }
   void Clear(){
    TextLayerArray.clear();
   }
   cv::Mat GetOpenCvImage() const{
    return Image;
   }
   RenderBox GetDrawBox() const{
    return DrawBox;
   }
};
