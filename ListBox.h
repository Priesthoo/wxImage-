#include<wx/listctrl.h>
#include<wx/imaglist.h>
#include<wx/bitmap.h>
#include<opencv2/opencv.hpp>
#include<ImageWindow.h>
class ImageListCtrl:public wxListCtrl{
  private:
  wxImageList imagelist;
  size_t imagecount;
  int index;
  int imageindex;
  void ClickListItem(wxListEvent& event){
    wxPoint currentposition=event.GetPoint();
    wxMenu* menu=new wxMenu;
    if(menu==NULL){
      return;
    }
    index=event.GetIndex();  //This returns the index of the element chosen;
    imageindex=event.GetImage();//This Gets the image index within the imagelist
    menu->Append(200,wxT("Render"));
    menu->Append(201,wxT("Delete"));
    PopupMenu(menu,currentposition);
    return;
  }
  void Delete(wxCommandEvent& event){
    if(index==-1){
      return;
    }
    if(imageindex==-1){
      return;
    }
    DeleteItem(index);
    imagelist.Remove(imageindex);
    imagecount--;
    if(imagecount<0){
      imagecount=0;
    }
    return;
  }
  public:
  ImageListCtrl(wxWindow* win,wxWindowID id):wxListCtrl(win,id,wxDefaultPosition,wxDefaultSize,wxLC_ICON){
    cv::Mat image=cv::imread("c://Users//KITS//Pictures//af92e6578551686bfcc4e161579e60f0.jpg");
    cv::Mat image1=image.clone();
    cv::resize(image,image1,cv::Size(100,100));
    wxImage im=Convert(image1);
    wxBitmap bitmap(im);
    imagelist.Create(100,100);
    imagelist.Add(bitmap);
    imagecount=0;
   AssignImageList(&imagelist,wxIMAGE_LIST_NORMAL);
   InsertItem(0,wxT("String name"),0);
    RefreshItem(0);
    Bind(wxEVT_LIST_ITEM_SELECTED,&ClickListItem,this);
    Bind(wxEVT_MENU,&Delete,this,201);
}
  void AddImage(const cv::Mat& cvimage){
    if(cvimage.empty()){
      return;
    }
    cv::Mat cvimage1=cvimage.clone();
    cv::resize(cvimage,cvimage1,cv::Size(100,100));
    if(cvimage1.empty()){
      return;
    }
    wxImage image=Convert(cvimage1);
    if(!image.IsOk()){
      return;
    }
    wxBitmap bitmap(image);
    imagelist.Add(bitmap);
    ++imagecount;
    InsertItem(imagecount,wxT("Mask Image"),imagecount);
    RefreshItem(imagecount);
  }
  void AddMaskImage(const cv::Mat& cvimage){
    if(cvimage.type()!=CV_8UC1){
      return;
    }
  if(cvimage.empty()){
      return;
    }
    cv::Mat cvimage1=cvimage.clone();
    cv::resize(cvimage,cvimage1,cv::Size(100,100));
    if(cvimage1.empty()){
      return;
    }
    wxImage image=ConvertToThreeChannelMask(cvimage1);
    if(!image.IsOk()){
      return;
    }
    wxBitmap bitmap(image);
    imagelist.Add(bitmap);
    ++imagecount;
    InsertItem(imagecount,wxT("Mask Image"),imagecount);
    RefreshItem(imagecount);
  }
};