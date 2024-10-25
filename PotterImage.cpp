#include<wx/wx.h>
#include<wx/image.h>
#include<ID.h>
#include<wx/filedlg.h>
#include<wx/filename.h>
#include<wx/app.h>
#include<wx/dcmemory.h>
#include<wx/colordlg.h>
#include<wx/bitmap.h>
#include<cmath>
#include<wx/splitter.h>
#include<DataView.h>
#include<string>
#include<opencv2/opencv.hpp>
using namespace ID;
using namespace std;

 
 class MyApp:public wxApp{
   public:
   bool OnInit() override;

 };
 wxIMPLEMENT_APP(MyApp);


class MyFrame:public wxFrame{
   private:
   wxImage image;  //current image on the canvas.
   int scalewidth;  //Current Mask Width
   int scaleheight;  //Current Mask Height..
   wxColour colour; 
   wxString str;
   int radius;
   bool upscalestate;
   wxImage RGBimage;
   int currentbrightvalue;
   int angle;
   int gamma;
   int c;
   int hblur;
   int vblur;
   string File;
   cvImage cvimage;
   int size;
   int sigclr;
   int sigsp;
   int bsize;
   int boxfiltersize;
   bool isnormalised;
   //For Box Filter....
   int sigma;
   int ksize;
   bool isConvolve;
   int delta;
  //For Laplacian Filter
  int lsize;
  int lscale;
  int ldelta;

  cvImage cvRGB;
 //For MedianBlur.
  int MedianBlurSize;
  //For GaussianBlur...
  int GaussSize;
  int Sigmax;
  int Sigmay;
  int GaussDenom;
  //For SobelOperator
  int x_order;
  int y_order;
  int sobelsize;
  //For Grabcut Algorithm...
  cvImage BackgroundModel;
  cvImage ForegroundModel;
  cvImage MaskImage;
  //For Mask Operation...
  bool ismask;
   void Openfile(wxCommandEvent& evt){
    ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   imcanvas->Clear(); 
   wxFileDialog filedlg(this,wxEmptyString,wxT("C:\\"),wxEmptyString,wxT("*.jpg"),wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if(imcanvas->GetImage().IsOk()){  //GetImage and check if it is OK
      imcanvas->GetImage().Destroy();
    }
   
    if(filedlg.ShowModal()==wxID_OK){
      str=filedlg.GetPath();
      File=ConvertToCharString(str);
      cvimage=cv::imread(File);
      imcanvas->SetOpenCvImage(cvimage);
      cvRGB=cvimage.clone();
      image=Convert(cvimage);
      RGBimage=image;
      imcanvas->SetImage(image);
      imcanvas->Refresh();
     }
    }

   void SaveFile(wxCommandEvent& event){
      ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
      imcanvas->Clear();
    wxFileDialog filedlg(this,wxEmptyString,wxT("C:\\"),wxEmptyString,wxT("*.jpg"),wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if(filedlg.ShowModal()==wxID_OK){
      str=filedlg.GetPath();
      if(imcanvas->GetImage().IsOk()){
      if(imcanvas->GetImage().SaveFile(str,wxBITMAP_TYPE_JPEG)){
        RGBimage=ImageTransform::ConstructImage(800,800,wxColour(56,72,84));
        if(RGBimage.IsOk()){
        imcanvas->SetImage(RGBimage);
        imcanvas->Refresh();
      }
      }
      }
    }
   }
   void Draw(wxCommandEvent& evt){
     ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
     wxImage image1=imcanvas->GetImage();
     wxBitmap bitmap(image1);
     if(!bitmap.IsOk()){
        return;
     }
     wxMemoryDC dc;
     dc.SelectObject(bitmap);
     dc.SetBrush(*wxBLACK_BRUSH);
     dc.SetPen(*wxBLACK_PEN);
     if(!dc.GetPen().IsOk()){  //Get Pen and Check if pen is initialized
        return;
     }
     if(!dc.GetBrush().IsOk()){
        return;
     }
     dc.DrawLine(320,45,340,70);
     dc.SelectObject(wxNullBitmap);
     image=bitmap.ConvertToImage();
     imcanvas->SetImage(image1);
     imcanvas->Refresh();
   }
   void Scale(wxCommandEvent& evt){
      ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
      cvImage image1=cvimage.clone();
      if(image1.empty()){
         return;
      }
      cv::resize(cvimage,image1,cv::Size(cvimage.rows,cvimage.cols));
      if(image1.empty()){
      return;
    }
   wxImage image3=Convert(image1);
    if(image3.IsOk()){
   cvimage=image1.clone();
   imcanvas->SetOpenCvImage(cvimage);
   imcanvas->SetImage(image3);   //imcanvas set Image to be displayed
   imcanvas->Refresh();  //refresh imcanvas
   return;
  }
  return;
   }
  void Iconize(wxIconizeEvent& evt){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   imcanvas->AdjustScrollbars();
   return;
  }
  void Reset(wxCommandEvent& evt){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   imcanvas->SetKeyValue(0,0);
   imcanvas->Refresh();
   return;
  }
  void ComputeNegativeImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   wxImage image2=imcanvas->GetImage();
   wxImage im=ImageTransform::Negative(image2);
   if(im.IsOk()){
      imcanvas->SetImage(im);
      imcanvas->Refresh();
      return;
   }
  }
    void SetColour(wxCommandEvent& evt){
       ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
       ChangeBackgroundColourDialog dialog(this,colour);
       if(dialog.ShowModal()==wxID_OK){
            colour=dialog.GetColour();
       }
        else if(dialog.ShowModal()==wxID_CANCEL){
      return;
   }
       imcanvas->SetBackgroundColour(colour);
       imcanvas->SetColourForBackground(colour);  
      imcanvas->Refresh();
      return;
    }
    void ComputeRedChannel(wxCommandEvent& evt){
      ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
      wxImage im=RGBimage;
      wxImage im2=ImageTransform::ConstructRed(im);
      if(im2.IsOk()){
         imcanvas->SetImage(im2);
         imcanvas->Refresh();
         return;
      }
      return;
}
    void ComputeGreenChannel(wxCommandEvent& evt){
      ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
      wxImage im=RGBimage;
      wxImage im2=ImageTransform::ConstructGreen(im);
      if(im2.IsOk()){
         imcanvas->SetImage(im2);
         imcanvas->Refresh();
         return;
      }
      return;
}
  void ComputeBlueChannel(wxCommandEvent& evt){
      ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
      wxImage im=RGBimage;
      wxImage im2=ImageTransform::ConstructBlue(im);
      if(im2.IsOk()){
         imcanvas->SetImage(im2);
         imcanvas->Refresh();
         return;
      }
      return;
}
void ConstructRGB(wxCommandEvent& evt){
    ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
    wxImage image1=RGBimage;
    cvimage=cvRGB.clone();
    imcanvas->SetOpenCvImage(cvimage);
    if(image1.IsOk()){
      imcanvas->SetImage(image1);
      imcanvas->Refresh();
      return;
    }
    return;
}

 void AddBrightness(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   wxImage im=imcanvas->GetImage();
   BrightnessDialog Dialog(this,currentbrightvalue);
   if(Dialog.ShowModal()==wxID_OK){
   currentbrightvalue=Dialog.GetBrightFactor();
   }
   double bright=(double)currentbrightvalue/100;
   im.ChangeBrightness(bright);
   if(im.IsOk()){
      imcanvas->SetImage(im);
      imcanvas->Refresh();
      return;
   }
   return;
 }
void RotateImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   wxImage im=imcanvas->GetImage();
   RotateDialog dialog(this,angle);
   if(dialog.ShowModal()==wxID_OK){
      angle=dialog.GetAngle();
   }
   double radian=ConvertDegToRadians(angle);
   int middle=im.GetWidth()/2;
   int middle1=im.GetHeight()/2;
   wxPoint pt(middle,middle1);
   
   if(im.IsOk()){
      wxImage image1=im.Rotate(radian,pt);
      if(image1.IsOk()){
         imcanvas->SetImage(image1);
         imcanvas->Refresh();
      }
      return;
   }
}
void Rotate90(wxCommandEvent& event){
    ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
    wxImage im=imcanvas->GetImage(); 
    if(im.IsOk()){
      wxImage image1=im.Rotate90();
      if(image1.IsOk()){
         imcanvas->SetImage(image1);
         imcanvas->Refresh();
         return;
      }
      
    }
    return;
}
void Rotate180(wxCommandEvent& event){
    ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
    wxImage im=imcanvas->GetImage(); 
    if(im.IsOk()){
      wxImage image1=im.Rotate180();
      if(image1.IsOk()){
         imcanvas->SetImage(image1);
         imcanvas->Refresh();
         return;
      }
}
    return;
}
 void ConstructGammaCorrectedImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   wxImage image1=imcanvas->GetImage();
   GammaDialog dialog(this,gamma,c);
   if(dialog.ShowModal()==wxID_OK){
      gamma=dialog.GetGamma();
      c=dialog.GetConstant();
   }
   double value1=(double)gamma/100;
 if(image1.IsOk()){
   image1=ImageTransform::GammaCorrection(image1,value1,c);
   if(image1.IsOk()){
      imcanvas->SetImage(image1);
      imcanvas->Refresh();
      return;
   }
   }
   return;
 }
 
 void RenderColourFullImage(wxCommandEvent& event){
    ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
    int w=0;
    int h=0;
    wxColour col;
    DrawImageDialog dialog(this);
    if(dialog.ShowModal()==wxID_OK){
     w=dialog.GetDialogWidth();
     h=dialog.GetDialogHeight();
     col=dialog.GetDialogColour();
    }
    else if(dialog.ShowModal()==wxID_CANCEL){
      return;
    }
    wxImage image1=ImageTransform::ConstructImage(w,h,col);
    if(image1.IsOk()){
      imcanvas->SetImage(image1);
      imcanvas->Refresh();
      return;
    }
    return;
 }
 void ConstructSwappedImage(wxCommandEvent& evt){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   wxImage image1=imcanvas->GetImage();
   wxImage image2=ImageTransform::ConstructSwapImage(image1);
   if(image2.IsOk()){
      imcanvas->SetImage(image2);
      imcanvas->Refresh();
      return;
   }
   return;
 }
 void ConstructBRGImage(wxCommandEvent& event){
  ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   wxImage image1=imcanvas->GetImage();
   wxImage image2=ImageTransform::ConstructBRGImage(image1);
   if(image2.IsOk()){
      imcanvas->SetImage(image2);
      imcanvas->Refresh();
      return;
   }
   return;
 }
 void ConstructYUVImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   wxImage image1=imcanvas->GetImage();
   wxImage image2=ImageTransform::ConstructYUVImage(image1);
   if(image2.IsOk()){
      imcanvas->SetImage(image2);
      imcanvas->Refresh();
      return;
   }
   return;
 }
 void ConstructYIQImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   wxImage image1=imcanvas->GetImage();
   wxImage image2=ImageTransform::ConstructYIQImage(image1);
   if(image2.IsOk()){
      imcanvas->SetImage(image2);
      imcanvas->Refresh();
      return;
   }
   return;
 }
  void ConstructFilteredImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   wxImage image1=imcanvas->GetImage();
   wxImage image2=ImageFilter::ConstructFilteredImage(image1);
   if(image2.IsOk()){
      imcanvas->SetImage(image2);
      imcanvas->Refresh();
      return;
   }
   return;
 }
 void ConstructHorizontalBlurImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   wxImage image1=imcanvas->GetImage();
   wxImage image2=image1.BlurHorizontal(60);
   if(image2.IsOk()){
      imcanvas->SetImage(image2);
      imcanvas->Refresh();
      return;
   }
   return;
 }
 void HBlur(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   wxImage im=imcanvas->GetImage();
   HorizontalBlurDialog Dialog(this,hblur);
   if(Dialog.ShowModal()==wxID_OK){
   hblur=Dialog.GetBlurFactor();
   }
    else if(Dialog.ShowModal()==wxID_CANCEL){
      return;
   }
     im=im.BlurHorizontal(hblur);
   if(im.IsOk()){
      imcanvas->SetImage(im);
      imcanvas->Refresh();
   }
  
   return;
 }
  void VBlur(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   wxImage im=imcanvas->GetImage();
   VerticalBlurDialog Dialog(this,vblur);
   if(Dialog.ShowModal()==wxID_OK){
   vblur=Dialog.GetBlurFactor();
   }
    else if(Dialog.ShowModal()==wxID_CANCEL){
      return;
   }
     im=im.BlurHorizontal(vblur);
   if(im.IsOk()){
      imcanvas->SetImage(im);
      imcanvas->Refresh();
   }
   return;
 }
 void ConstructMirrorImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   wxImage image1=imcanvas->GetImage();
   wxImage image2=image1.Mirror();
   if(image2.IsOk()){
      imcanvas->SetImage(image2);
      imcanvas->Refresh();
      return;
   }
   return;
 }
 
 void ConstructBiImage(wxCommandEvent& evt){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
    cvImage im1=cvimage.clone();
    BilateralFilterDialog dlg(this,size,sigclr,sigsp);
    if(dlg.ShowModal()==wxID_OK){
      size=dlg.GetSize();
      sigclr=dlg.GetSigmaColour();
      sigsp=dlg.GetSigmaSpace();
}
   else if(dlg.ShowModal()==wxID_CANCEL){
      return;
   }
   double s1=(double)sigclr;
   double s2=(double)sigsp;
   cv::bilateralFilter(cvimage,im1,size,s1,s2);
    if(im1.empty()){
      return;
    }
    wxImage image2=Convert(im1);
    if(image2.IsOk()){
      cvimage=im1.clone();
     imcanvas->SetOpenCvImage(cvimage); 
      imcanvas->SetImage(image2);
      imcanvas->Refresh();
      return;
    }
    return;
 }
 void ConstructNormalizedBlurImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   cvImage image2=cvimage.clone();
   NormalizedBlurFilter dialog(this,bsize);
   if(dialog.ShowModal()==wxID_OK){
      bsize=dialog.GetSize();
}
   else{
      return;
   } 
  cv::blur(cvimage,image2,cv::Size(bsize,bsize));
  if(image2.empty()){
   return;
  }
  wxImage image3=Convert(image2);
  
  if(image3.IsOk()){
   cvimage=image2.clone();
   imcanvas->SetImage(image3);
   imcanvas->Refresh();
   return;
  }
  return;
 }
 void ConstructBoxFilterImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   cvImage im=cvimage.clone();
   if(im.empty()){
      return;
   }
   BoxFilter dialog(this,boxfiltersize,isnormalised);
   if(dialog.ShowModal()==wxID_OK){
      boxfiltersize=dialog.GetSize();
      isnormalised=dialog.IsNormalized();
   }
    else if(dialog.ShowModal()==wxID_CANCEL){
      return;
   }
   cv::boxFilter(cvimage,im,-1,cv::Size(boxfiltersize,boxfiltersize),cv::Point(-1,-1),isnormalised);
   if(im.empty()){
      return;
   }
   wxImage image3=Convert(im);
  if(image3.IsOk()){
   cvimage=im.clone();
   imcanvas->SetOpenCvImage(cvimage);
   imcanvas->SetImage(image3);
   imcanvas->Refresh();
   return;
  }
  return;
}
void ConstructFilter2DImage(wxCommandEvent& event){
    ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
    cvImage cvimage1=cvimage.clone();
    if(cvimage1.empty()){
      return;
    }
 Filter2D dialog(this,sigma,ksize,delta,isConvolve);
 if(dialog.ShowModal()==wxID_OK){
   sigma=dialog.GetSigma();
   ksize=dialog.GetSize();
   delta=dialog.GetDelta();
   isConvolve=dialog.IsConvolution();
 }
 else if(dialog.ShowModal()==wxID_CANCEL){
   return;
 }
 //Let's Construct the Kernel which will passed to the 2D filter....
 cvImage kernel;
 cv::Point anchor(-1,-1);
 if(isConvolve==true){
   kernel=cv::getGaussianKernel(ksize,(double)sigma);
   cv::filter2D(cvimage,cvimage1,-1,kernel,anchor,(double)delta);
 }
if(cvimage1.empty()){
   return;
 }
 wxImage image3=Convert(cvimage1);
    if(image3.IsOk()){
   cvimage=cvimage1.clone();
   imcanvas->SetOpenCvImage(cvimage);
   imcanvas->SetImage(image3);
   imcanvas->Refresh();
   return;
  }
return;
}
void ConstructLaplacianImage(wxCommandEvent& event){
ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
cvImage im=cvimage.clone();
if(im.empty()){
   return;
}
LaplacianDialog dialog(this,lsize,lscale,ldelta);
if(dialog.ShowModal()==wxID_OK){
   lsize=dialog.GetSize();
   lscale=dialog.GetScale();
   ldelta=dialog.GetDelta();
}
else if(dialog.ShowModal()==wxID_CANCEL){
   return;
}
   cv::Laplacian(cvimage,im,-1,lsize,(double)lscale,(double)ldelta);
   if(im.empty()){
      return;
   }
 wxImage image3=Convert(im);
    if(image3.IsOk()){
   cvimage=im.clone();
   imcanvas->SetOpenCvImage(cvimage);
   imcanvas->SetImage(image3);   //imcanvas set Image to be displayed
   imcanvas->Refresh();  //refresh imcanvas
   return;
  }
return;
}
void ConstructSharpenImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   cvImage image1=cvimage.clone(); //clone cvimage;
   cvImage maskimage=cvimage.clone(); //clone cvimage
   cvImage resultimage=cvimage.clone();  //clone cvimage.
   cv::medianBlur(cvimage,image1,7);
   if(image1.empty()){
      return;
   }
   maskimage=maskimage*4;
   cv::subtract(cvimage,image1,maskimage);
   if(maskimage.empty()){
      return;
   }
   cv::add(maskimage,cvimage,resultimage);
   if(resultimage.empty()){
      return;
   }
   wxImage image3=Convert(resultimage);
    if(image3.IsOk()){
   cvimage=resultimage.clone();
   imcanvas->SetOpenCvImage(cvimage);
   imcanvas->SetImage(image3);   //imcanvas set Image to be displayed
   imcanvas->Refresh();  //refresh imcanvas
   return;
  }
return;
}
void ConstructMedianBlurImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   cvImage image1=cvimage.clone();
   if(image1.empty()){
      return;
   }
   MedianBlurDialog dialog(this,MedianBlurSize);
   if(dialog.ShowModal()==wxID_OK){
      MedianBlurSize=dialog.GetMedianSize();
   }
   else{
      return;
   }
   cv::medianBlur(cvimage,image1,MedianBlurSize);
    wxImage image3=Convert(image1);
    if(image3.IsOk()){
   cvimage=image1.clone();
   imcanvas->SetOpenCvImage(cvimage);
   imcanvas->SetImage(image3);   //imcanvas set Image to be displayed
   imcanvas->Refresh();  //refresh imcanvas
   return;
  }
}
void ConvertToGreyScale(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
    cvImage image1=cvimage.clone();
    if(image1.empty()){
      return;
    }
    cv::cvtColor(cvimage,image1,cv::COLOR_BGR2GRAY);
    if(image1.empty()){
      return;
    }
    wxImage image3=Convert(image1);
    if(image3.IsOk()){
   cvimage=image1.clone();
   imcanvas->SetOpenCvImage(cvimage);
   imcanvas->SetImage(image3);   //imcanvas set Image to be displayed
   imcanvas->Refresh();  //refresh imcanvas
   return;
  }
}
void ConstructGaussianImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
    cvImage image1=cvimage.clone();
    if(image1.empty()){
      return;
    }
    GaussianBlurDialog dialog(this,GaussSize,Sigmax,Sigmay);
    if(dialog.ShowModal()==wxID_OK){
      GaussSize=dialog.GetSize();
      Sigmax=dialog.GetSigmaX();
      Sigmay=dialog.GetSigmaY();
      GaussDenom=dialog.GetDenominator();
    }
    else{
      return;
    }
    double sx=(double)Sigmax/GaussDenom;
    double sy=(double)Sigmay/GaussDenom;
    cv::GaussianBlur(cvimage,image1,cv::Size(GaussSize,GaussSize),sx,sy);
    if(image1.empty()){
      return;
    }
   wxImage image3=Convert(image1);
    if(image3.IsOk()){
   cvimage=image1.clone();
   imcanvas->SetOpenCvImage(cvimage);
   imcanvas->SetImage(image3);   //imcanvas set Image to be displayed
   imcanvas->Refresh();  //refresh imcanvas
   return;
  }
  return;
}
void ConvertToHSV(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   cvImage image1=cvimage.clone();
   if(image1.empty()){
      return;
   }
   cv::cvtColor(cvimage,image1,cv::COLOR_BGR2HSV);
   if(image1.empty()){
      return;
   }
   wxImage image3=Convert(image1);
    if(image3.IsOk()){
   cvimage=image1.clone();
   imcanvas->SetOpenCvImage(cvimage);
   imcanvas->SetImage(image3);   //imcanvas set Image to be displayed
   imcanvas->Refresh();  //refresh imcanvas
   return;
  }
  return;
}
void ConstructSobelImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   cvImage image1=cvimage.clone();
   SobelDialog dialog(this,x_order,y_order,sobelsize);
   if(dialog.ShowModal()==wxID_OK){
      x_order=dialog.GetXOrder();
      y_order=dialog.GetYOrder();
      sobelsize=dialog.GetSize();
   }
   else{
      return;
   }
   cv::Sobel(cvimage,image1,-1,x_order,y_order,sobelsize,1.0,0.5);
   if(image1.empty()){
      return;
   }
   wxImage image3=Convert(image1);
    if(image3.IsOk()){
   cvimage=image1.clone();
   imcanvas->SetOpenCvImage(cvimage);
   imcanvas->SetImage(image3);   //imcanvas set Image to be displayed
   imcanvas->Refresh();  //refresh imcanvas
   return;
  }
  return;

}
void ConstructImageMask(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   ImageListCtrl* imagelist=(ImageListCtrl*)FindWindow(t19);
   if(MaskImage.empty()){
      MaskImage=cv::Mat(imcanvas->GetOpenCvImage().rows,imcanvas->GetOpenCvImage().cols,CV_8UC1,cv::Scalar::all(0));
   }
  RenderBox rect=imcanvas->GetDrawBox();
  cv::Rect rect1(rect.x,rect.y,rect.width,rect.height); 
  cv::grabCut(cvimage,MaskImage,rect1,BackgroundModel,ForegroundModel,10,cv::GC_INIT_WITH_RECT);
  MaskImage=ComputeMaskedImage(MaskImage);
  MaskImage*=255;
  if(MaskImage.empty()){
   return;
  }
  imagelist->AddMaskImage(MaskImage);
   return;
}
void DisplayMaskImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   wxImage image3=ConvertToThreeChannelMask(MaskImage);
   if(image3.IsOk()){
      imcanvas->SetImage(image3);
      imcanvas->Refresh();
      return;
   }
   return;
}
void ConstructSketchImage(wxCommandEvent& event){
   ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
   wxImage image3=ConstructPencilSketchImage(cvimage);
   if(image3.IsOk()){
    imcanvas->SetImage(image3);
    imcanvas->Refresh();
    return;
   }
   return;
}
void ConstructAdaptiveThresholdImage(wxCommandEvent& event){
     ImageCanvas* imcanvas=(ImageCanvas*)FindWindow(t0);
     cvImage cvimage1=cvimage.clone();
     if(cvimage1.empty()){
      return;
     }
     cv::cvtColor(cvimage,cvimage1,cv::COLOR_BGR2GRAY);
     if(cvimage1.empty()){
      return;
     }
     cvImage cvimage2=cvimage1.clone();
     if(cvimage2.empty()){
      return;
     }
     cv::medianBlur(cvimage1,cvimage1,5);
     cv::adaptiveThreshold(cvimage1,cvimage2,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY,11,2);
     if(cvimage2.empty()){
      return;
     }
     wxImage image3=Convert(cvimage2);
     if(image3.IsOk()){
      cvimage=cvimage2.clone();
      imcanvas->SetOpenCvImage(cvimage);
      imcanvas->SetImage(image3);
      imcanvas->Refresh();
      return;
     }
     return;
}

   public:
   MyFrame():wxFrame(NULL,wxID_ANY,wxT("PotterImage"),wxDefaultPosition,wxDefaultSize,wxFULL_REPAINT_ON_RESIZE|wxDEFAULT_FRAME_STYLE){
      delta=0;
      wxImage create=ImageTransform::ConstructImage(800,800,wxColour(56,72,84));  
      wxSplitterWindow* splitwindow=new wxSplitterWindow(this,wxID_ANY,wxPoint(0,0),wxSize(400,400));
      ImageCanvas* imcanvas=new ImageCanvas(splitwindow,ID::t0,create);
      wxPanel*panel=new wxPanel(splitwindow,wxID_ANY);
      panel->SetBackgroundColour(wxColour(5,10,5));
      ImageListCtrl* imagelist=new ImageListCtrl(panel,t19); 
      imcanvas->Show(true);
      panel->Show(true);
      splitwindow->SplitVertically(panel,imcanvas);
      splitwindow->SetMinimumPaneSize(5);
      wxBoxSizer* bsizer=new wxBoxSizer(wxVERTICAL);
      bsizer->Add(imagelist,1,wxEXPAND|wxALL,5);
      panel->SetSizerAndFit(bsizer);
      wxMenu* nmenu=new wxMenu;
      nmenu->Append(ID::t1,wxT("Open File \tCtrl+O"));
      nmenu->Append(ID::t2,("Draw Line"));
      nmenu->Append(ID::t3,wxT("Save File"));
      wxMenu* nmenu1=new wxMenu;
      nmenu1->Append(ID::t4,wxT("Resize"));
      nmenu1->Append(ID::t5,wxT("Change BackgroundColour"));
      nmenu1->Append(ID::t6,wxT("Reset"));
      nmenu1->Append(ID::t7,wxT("Negative Image"));
      nmenu1->Append(ID::t8,wxT("Horizontal Blur"));
      nmenu1->Append(ID::t26,wxT("Vertical Blur"));
      nmenu1->Append(ID::t9,wxT("Red Channel"));
      nmenu1->Append(ID::t10,wxT("Green Channel"));
      nmenu1->Append(ID::t11,wxT("Blue Channel"));
      nmenu1->Append(ID::t12,wxT("RGB image"));
      nmenu1->Append(ID::t13,wxT("Greyscale Image"));
      nmenu1->Append(ID::t14,wxT("Brightness"));
      nmenu1->Append(ID::t18,wxT("Gamma Correction"));
      nmenu1->Append(ID::t22,wxT("GBR image"));
      nmenu1->Append(ID::t23,wxT("BRG image"));
      nmenu1->Append(ID::t24,wxT("YUV image"));
      nmenu1->Append(ID::t25,wxT("YIQ image"));
      nmenu1->Append(ID::t27,wxT("Mirror Image"));
      wxMenu* nmenu2=new wxMenu;
      nmenu2->Append(ID::t28,wxT("Filtered Image"));
      nmenu2->Append(ID::t30,wxT("Bilateral Filter"));
      nmenu2->Append(ID::t31,wxT("Normalized Box Filter"));
      nmenu2->Append(ID::t32,wxT("Box Filter"));
      nmenu2->Append(t33,wxT("2D Filter"));
      nmenu2->Append(t34,wxT("Laplacian Filter")); //This is a sharpening filter
      nmenu2->Append(t39,wxT("Sobel Filter"));
      nmenu2->Append(t35,wxT("Sharpen Image"));
      nmenu2->Append(t36,wxT("Median Blur"));
      nmenu2->Append(t37,wxT("Gaussian Blur"));
      nmenu1->AppendSubMenu(nmenu2,wxT("Filters"));
      nmenu1->Append(t151,wxT("Adaptive Thresholding"));
      nmenu1->Append(t38,wxT("HSV"));  //hue,saturation and value......
      nmenu1->Append(t150,wxT("Sketch Image"));
      wxMenu* menu=new wxMenu;
      menu->Append(ID::t15,wxT("Rotate"));
      menu->Append(ID::t16,wxT("Rotate90"));
      menu->Append(ID::t17,wxT("Rotate180"));
      wxMenu* menu1=new wxMenu;
      menu1->Append(ID::t21,wxT("Render Image"));
      menu1->Append(ID::t20,wxT("Render Mask Image"));
      menu1->Append(ID::t29,wxT("Display Mask Image"));
      
      
      wxMenuBar* nmbar=new wxMenuBar();
      nmbar->Append(nmenu,wxT("File"));
      nmbar->Append(nmenu1,wxT("Edit"));
      nmbar->Append(menu,wxT("Transform"));
      nmbar->Append(menu1,wxT("Tools"));
      SetMenuBar(nmbar);
      CreateStatusBar();
      
      CreateToolBar();
      Bind(wxEVT_MENU,&Openfile,this,ID::t1);
      Bind(wxEVT_MENU,&Draw,this,ID::t2);
      Bind(wxEVT_MENU,&SetColour,this,ID::t5);
      Bind(wxEVT_MENU,&Scale,this,ID::t4);
      Bind(wxEVT_MENU,&Reset,this,t6);
      Bind(wxEVT_MENU,&ComputeNegativeImage,this,t7);
      Bind(wxEVT_MENU,&HBlur,this,t8);
      Bind(wxEVT_MENU,&ComputeRedChannel,this,t9);
      Bind(wxEVT_MENU,&ComputeGreenChannel,this,t10);
      Bind(wxEVT_MENU,&ComputeBlueChannel,this,t11);
      Bind(wxEVT_MENU,&ConstructRGB,this,t12);
      Bind(wxEVT_MENU,&ConvertToGreyScale,this,t13);
      Bind(wxEVT_ICONIZE,&Iconize,this);
      Bind(wxEVT_MENU,&AddBrightness,this,t14);
      Bind(wxEVT_MENU,&RotateImage,this,t15);
      Bind(wxEVT_MENU,&Rotate90,this,t16);
      Bind(wxEVT_MENU,&Rotate180,this,t17);
      Bind(wxEVT_MENU,&ConstructGammaCorrectedImage,this,t18);
      Bind(wxEVT_MENU,&RenderColourFullImage,this,t21);
      Bind(wxEVT_MENU,&ConstructSwappedImage,this,t22);
      Bind(wxEVT_MENU,&ConstructBRGImage,this,t23);
      Bind(wxEVT_MENU,&ConstructYUVImage,this,t24);
      Bind(wxEVT_MENU,&ConstructYIQImage,this,t25);
      Bind(wxEVT_MENU,&VBlur,this,t26);
      Bind(wxEVT_MENU,&ConstructMirrorImage,this,t27);
      Bind(wxEVT_MENU,&SaveFile,this,t3);
      Bind(wxEVT_MENU,&ConstructFilteredImage,this,t28);
      Bind(wxEVT_MENU,&ConstructBiImage,this,t30);
      Bind(wxEVT_MENU,&ConstructNormalizedBlurImage,this,t31);
      Bind(wxEVT_MENU,&ConstructBoxFilterImage,this,t32);
      Bind(wxEVT_MENU,&ConstructFilter2DImage,this,t33);
      Bind(wxEVT_MENU,&ConstructLaplacianImage,this,t34);
      Bind(wxEVT_MENU,&ConstructSharpenImage,this,t35);
      Bind(wxEVT_MENU,&ConstructMedianBlurImage,this,t36);
      Bind(wxEVT_MENU,&ConstructGaussianImage,this,t37);  
      Bind(wxEVT_MENU,ConvertToHSV,this,t38);   
      Bind(wxEVT_MENU,&ConstructSobelImage,this,t39);
      Bind(wxEVT_MENU,&ConstructImageMask,this,t20);
      Bind(wxEVT_MENU,&DisplayMaskImage,this,t29);
      Bind(wxEVT_MENU,&ConstructSketchImage,this,t150);
      Bind(wxEVT_MENU,&ConstructAdaptiveThresholdImage,this,t151);
      
   }
};
bool MyApp::OnInit(){
   wxInitAllImageHandlers();
   MyFrame* myframe=new MyFrame;
   myframe->SetSize(400,400);
   myframe->Show(true);
   return true;

}