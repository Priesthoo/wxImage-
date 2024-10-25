#include<wx/image.h>
#include<cmath>
#include<Filter.h>
#include<opencv2/opencv.hpp>
#include<wx/bitmap.h>
#include<string>

/*
   There are different types of image manipulation Algorithm.
   1).Intensity Transformation 
   2).Spatial filtering.






*/
typedef cv::Mat cvImage;
typedef cv::Vec<unsigned char,3> vec3u;
long XYToPos(const wxImage& image,int x, int y){
   if(image.IsOk() && x>=0 && y>=0 && x<image.GetWidth() && y<image.GetHeight()){
      return y*image.GetWidth()+x;
   }
   return -1;
}
unsigned char GammaPower(const unsigned char& input,const int& c,const double& power){
   unsigned char newvalue=c*pow(input,power);
   return newvalue;
}
double ConvertDegToRadians(const double& angle ){
 const double pi=3.14159265;
   double value=angle*(pi/180);
   return value;
}
template<class T>
T clampToRange(const T& first,const  T& value,const T& second){
   if(value<first){
      return first;
   }
   else if(value>second){
      return second;
   }
   else{
      return value;
   }
}
class ImageTransform{
    public:
    static wxImage Negative(const wxImage& image){
      wxImage image1(image.GetSize().GetWidth(),image.GetSize().GetHeight());
      if(!image.IsOk()){
         return wxNullImage;
      }
      for(int i=0;i<image.GetSize().GetWidth();i++){
         for(int j=0;j<image.GetSize().GetHeight();j++){
            unsigned char red=255-image.GetRed(i,j);
            red=clampToRange<unsigned char>(0,red,255);
            unsigned char green=255-image.GetGreen(i,j);
            green=clampToRange<unsigned char>(0,green,255);
            unsigned char blue=255-image.GetBlue(i,j);
            blue=clampToRange<unsigned char>(0,blue,255);
            image1.SetRGB(i,j,red,green,blue);
         }
      }
    
    if(image1.IsOk()){
      return image1;
    }
    return wxNullImage;
    }
   static wxImage ConstructRed(const wxImage& image){
      wxImage image1(image.GetSize().GetWidth(),image.GetSize().GetHeight());
      if(!image.IsOk()){
        return wxNullImage;
      }
      for(int i=0;i<image.GetSize().GetWidth();i++){
         for(int j=0;j<image.GetSize().GetHeight();j++){
            unsigned char red=image.GetRed(i,j);
            image1.SetRGB(i,j,red,0,0);
         }
      }
      if(image1.IsOk()){
         return image1;
      }
      return wxNullImage;
   }
    static wxImage ConstructGreen(const wxImage& image){
      wxImage image1(image.GetSize().GetWidth(),image.GetSize().GetHeight());
      if(!image.IsOk()){
        return wxNullImage;
      }
      for(int i=0;i<image.GetSize().GetWidth();i++){
         for(int j=0;j<image.GetSize().GetHeight();j++){
            unsigned char green=image.GetGreen(i,j);
            image1.SetRGB(i,j,0,green,0);
         }
      }
      if(image1.IsOk()){
         return image1;
      }
      return wxNullImage;
   }
   static wxImage ConstructBlue(const wxImage& image){
      wxImage image1(image.GetSize().GetWidth(),image.GetSize().GetHeight());
      if(!image.IsOk()){
        return wxNullImage;
      }
      for(int i=0;i<image.GetSize().GetWidth();i++){
         for(int j=0;j<image.GetSize().GetHeight();j++){
            unsigned char blue=image.GetBlue(i,j);
            image1.SetRGB(i,j,0,0,blue);
         }
      }
      if(image1.IsOk()){
         return image1;
      }
      return wxNullImage;
   }
    static wxImage PowerTransform(const wxImage& image,const int& c){
       wxImage image1(image.GetWidth(),image.GetHeight());
       if(!image.IsOk()){
         return wxNullImage;
       }
       for(int i=0;i<image.GetWidth();i++){
         for(int j=0;j<image.GetHeight();j++){
            unsigned char red=1+image.GetRed(i,j);
            red=c*log(red);
           image1.SetRGB(i,j,red,0,0);
         }
       }
       if(image1.IsOk()){
         return image1;
       }
       return wxNullImage;
    }
static wxImage GammaCorrection(const wxImage& image,const double& exp,const int& c){
   wxImage image1(image.GetWidth(),image.GetHeight());
   if(!image.IsOk()){
      return wxNullImage;
   }
   for(int i=0;i<image.GetWidth();i++){
      for(int j=0;j<image.GetHeight();j++){
         unsigned char red=GammaPower(image.GetRed(i,j),c,exp);
         unsigned char green=GammaPower(image.GetGreen(i,j),c,exp);
         unsigned char blue=GammaPower(image.GetBlue(i,j),c,exp);
         image1.SetRGB(i,j,red,green,blue);
      }
   }
   if(image1.IsOk()){
      return image1;
   }
   return wxNullImage;

}
//It creates an Image of random colour.....
 static wxImage ConstructImage(const int& width,const int& height,const wxColour& colour ){
   wxImage image(width,height);
   if(!image.IsOk()){
      return wxNullImage;
   }
   for(int i=0;i<width;i++){
      for(int j=0;j<height;j++){
         image.SetRGB(i,j,colour.GetRed(),colour.GetGreen(),colour.GetBlue());
      }
   }
   if(image.IsOk()){
      return image;
   }
   return wxNullImage;
 }
 static wxImage ConstructSwapImage(const wxImage& image){
   wxImage image1(image.GetWidth(),image.GetHeight());
   if(!image.IsOk()){
      return wxNullImage;
   }
   for(int i=0;i<image.GetWidth();i++){
      for(int j=0;j<image.GetHeight();j++){
         image1.SetRGB(i,j,image.GetGreen(i,j),image.GetBlue(i,j),image.GetRed(i,j));
      }
}
   if(image1.IsOk()){
      return image1;
   }
   return wxNullImage;
 }
 static wxImage ConstructBRGImage(const wxImage& image){
   wxImage image1(image.GetWidth(),image.GetHeight());
   if(!image.IsOk()){
      return wxNullImage;
   }
   for(int i=0;i<image.GetWidth();i++){
      for(int j=0;j<image.GetHeight();j++){
         image1.SetRGB(i,j,image.GetBlue(i,j),image.GetRed(i,j),image.GetGreen(i,j));
      }
}
   if(image1.IsOk()){
      return image1;
   }
   return wxNullImage;
 }
 static wxImage ConstructYUVImage(const wxImage& image){
   wxImage image1(image.GetWidth(),image.GetHeight());
   if(!image.IsOk()){
      return wxNullImage;
   }
   for(int i=0;i<image.GetWidth();i++){
      for(int j=0;j<image.GetHeight();j++){
         unsigned char red=(0.299*image.GetRed(i,j))+(0.587*image.GetGreen(i,j))+(0.114*image.GetBlue(i,j));
         unsigned char green=(-0.147*image.GetRed(i,j))+(-0.289*image.GetGreen(i,j))+(0.436*image.GetBlue(i,j));
         unsigned char blue=(0.615*image.GetRed(i,j))+(-0.515*image.GetGreen(i,j))+(-0.100*image.GetBlue(i,j));
         image1.SetRGB(i,j,red,green,blue);
      }
   }
   if(image1.IsOk()){
      return image1;
   }
   return wxNullImage;
 }
  static wxImage ConstructYIQImage(const wxImage& image){
   wxImage image1(image.GetWidth(),image.GetHeight());
   if(!image.IsOk()){
      return wxNullImage;
   }
   for(int i=0;i<image.GetWidth();i++){
      for(int j=0;j<image.GetHeight();j++){
         unsigned char red=(0.299*image.GetRed(i,j))+(0.587*image.GetGreen(i,j))+(0.114*image.GetBlue(i,j));
         unsigned char green=(0.596*image.GetRed(i,j))+(-0.275*image.GetGreen(i,j))+(-0.321*image.GetBlue(i,j));
         unsigned char blue=(0.212*image.GetRed(i,j))+(-0.528*image.GetGreen(i,j))+(0.311*image.GetBlue(i,j));
         image1.SetRGB(i,j,red,green,blue);
      }
   }
   if(image1.IsOk()){
      return image1;
   }
   return wxNullImage;
 }
};
class ImageFilter{
   public:
/*
  Illustration of the application of smoothing Filter.... with radius of 2 from the filter center..
           |--------------------------------------------------->
           |
           |
           |
           |
           |
           |
           |   

   The top-left corner is at (0,0)...which helps us to define the coordinate system of the image...,
  Also for the FilterMask, we use this coordinate system defined above, which simplifies the calculation
   

   we are going to use this coordinate system to define the FilterMask..
   [    0,                     1,                            2        ]
   [    3,                      4,                           5        ]
   [    6,                       7,                           8       ]   //3x3 filter mask

   

*/
   static wxImage ConstructFilteredImage(const wxImage& image){
     wxImage image1(image.GetWidth(),image.GetHeight());
     if(!image.IsOk()){
      return wxNullImage;
     }
     SmoothingFilter smoothfilter;
     if(!smoothfilter.empty() && image1.IsOk()){ //At this point,we are checking if the second image created is okay and if the smooth filter is not empty
         for(int j=0;j<image1.GetHeight();j++){
            for(int i=0;i<image1.GetWidth();i++){
               int x=i-1;
               int y=j-1;
               unsigned char red=0;
               unsigned char green=0;
               unsigned char blue=0;
               unsigned char rowred=0;
               unsigned char rowblue=0;
               unsigned char rowgreen=0;
               for(int h=-1;h<2;h=h+1){
                  long pos=XYToPos(image1,x,y);
                  if(pos==-1){
                     red=0;
                     green=0;
                     blue=0;
                  }
                  else{
                     red=image.GetRed(x,y);
                     green=image.GetGreen(x,y);
                     blue=image.GetBlue(x,y);
                  }
                  rowred+=(red*1);
                  rowgreen+=(green* 1);
                  rowblue+=(blue* 1);
                  x=x+1;     //row reading
               }
             x=i-1;
             y=j;
             red=0;
             green=0;
             blue=0;
             for(int h=-1;h<2;h=h+1){
                  long pos=XYToPos(image1,x,y);
                  if(pos==-1){
                     red=0;
                     green=0;
                     blue=0;
                  }
                  else{
                     red=image.GetRed(x,y);
                     green=image.GetGreen(x,y);
                     blue=image.GetBlue(x,y);
                  }
                 rowred+=(red* 1);
                 rowgreen+=(green* 1);
                 rowblue+=(blue* 1);
                  x=x+1;
               }
             x=i-1;
             y=j+1;
             red=0;
             green=0;
             blue=0;
             for(int h=-1;h<2;h=h+1){
                  long pos=XYToPos(image1,x,y);
                  if(pos==-1){
                     red=0;
                     green=0;
                     blue=0;
                  }
                  else{
                     red=image.GetRed(x,y);
                     green=image.GetGreen(x,y);
                     blue=image.GetBlue(x,y);
                  }
                   rowred+=(red* 1);
                  rowgreen+=(green* 1);
                  rowblue+=(blue*1);
                  x=x+1;
               }
               rowred=rowred/9;
               rowgreen=rowgreen/9;
               rowblue=rowblue/9;
             image1.SetRGB(i,j,rowred,rowgreen,rowblue);
            }
         }
         if(image1.IsOk()){
            return image1;
         }
         return wxNullImage;
     }
     return wxNullImage;
   }
};
wxImage Convert(const cvImage& image){
   cvImage image2;
   if(!image.empty()){
   cvtColor(image,image2,cv::COLOR_BGR2RGB);
   }
   if(image2.empty()){
      return wxNullImage;
   }
   wxImage image1(image2.rows,image2.cols);
   if(!image1.IsOk()){
      return wxNullImage; 
   }
   for(int i=0;i<image2.rows;i++){
      for(int j=0;j<image2.cols;j++){
         unsigned char red=image2.at<vec3u>(i,j)[0];
         unsigned char green=image2.at<vec3u>(i,j)[1];
         unsigned char blue=image2.at<vec3u>(i,j)[2];
         image1.SetRGB(i,j,red,green,blue);
      }
   }
   image1=image1.Rotate90();
   image1=image1.Mirror();
   if(image1.IsOk()){
      return image1;
   }
   return wxNullImage;
}
const char* ConvertToCharString(const wxString& str){
 return static_cast<const char*>(str.mb_str());
}
cvImage ConvertToCvImage(const wxImage& image){
   cvImage cvimage(image.GetWidth(),image.GetHeight(),CV_8UC(3),cv::Scalar::all(1));
   if(cvimage.empty()){
      return cv::Mat();
   }
   for(int i=0;i<image.GetWidth();i++){
      for(int j=0;j<image.GetHeight();j++){
         cvimage.at<vec3u>(i,j)[0]=image.GetBlue(i,j);
         cvimage.at<vec3u>(i,j)[1]=image.GetGreen(i,j);
         cvimage.at<vec3u>(i,j)[2]=image.GetRed(i,j);
    }
}
  if(!cvimage.empty()){
   return cvimage;
  }   
  return cv::Mat();

}
wxImage GetSubsetOfImage(const wxRect rect,const wxImage& image){
    wxImage newimage(rect.width,rect.height);
    if(!newimage.IsOk()){
      return wxNullImage;
    }
    for(int i=0;i<newimage.GetWidth();i++){
      for(int j=0;j<newimage.GetHeight();j++){
         newimage.SetRGB(i,j,image.GetRed(rect.x+i,rect.y+j),image.GetGreen(rect.x+i,rect.y+j),image.GetBlue(rect.x+i,rect.y+j));
      }
    }
    if(newimage.IsOk()){
      return newimage;
    }
    return wxNullImage;
}
//purpose:To set the color of a rectangular portion of an image,starting from a particular offset provided that the offset is within the image
//param1:The image that will have it's colour changed
//param2: The image from which the colors are read,NB: this image forms the rectangle section that will be used in param1.
//param3: the starting offset from which read will start..NB: the offset must be within image dimension(image.GetWidth() and image.GetHeight());

void SetSubsetOfImage(wxImage& image,const wxImage& RectImage,const wxPoint& offset){
  if(!image.IsOk()){
   return;
  }
  if(!RectImage.IsOk()){
    return;
  }
  wxRect rect(0,0,image.GetWidth(),image.GetHeight());
  if(!rect.Contains(offset)){
    return;
  }
  int x=offset.x;
  int y=offset.y;
  for(int i=0;i<RectImage.GetWidth();i++){
   for(int j=0;j<RectImage.GetHeight();j++){
       image.SetRGB(i+x,j+y,RectImage.GetRed(i,j),RectImage.GetGreen(i,j),RectImage.GetBlue(i,j));
   }
  }
}
wxImage ConstructSharpenedImage(const cvImage& cvimage){
   cvImage image1=cvimage.clone(); //clone cvimage;
   cvImage maskimage=cvimage.clone(); //clone cvimage
   cvImage resultimage=cvimage.clone();  //clone cvimage.
   cv::medianBlur(cvimage,image1,7);
   if(image1.empty()){
      return wxNullImage;
   }
   maskimage=maskimage*4;
   cv::subtract(cvimage,image1,maskimage);
   if(maskimage.empty()){
      return wxNullImage;
   }
   cv::add(maskimage,cvimage,resultimage);
   if(resultimage.empty()){
      return wxNullImage;
   }
   wxImage image3=Convert(resultimage);
   return image3;
}
wxImage ConvertToThreeChannelMask(const cvImage& maskimage){
   if(maskimage.type()!=CV_8UC1){
      return wxNullImage;
   }
   if(maskimage.empty()){
      return wxNullImage;
   }
   wxImage image(maskimage.rows,maskimage.cols);
   if(!image.IsOk()){
       return wxNullImage;
   }
   cvImage cvimage=maskimage.clone(); //still analogous to clone(maskimage).....
   for(int i=0;i<cvimage.rows;i++){
      for(int j=0;j<cvimage.cols;j++){
         unsigned char colour=cvimage.at<unsigned char>(i,j);
         image.SetRGB(i,j,colour,colour,colour);
      }
   }
   image=image.Rotate90();
   image=image.Mirror();
   if(image.IsOk()){
     return image;
   }
   return wxNullImage;
}
cvImage ComputeMaskedImage(const cvImage& image){
   if(image.type()!=CV_8UC1){
      return cv::Mat();   //if it fails,return an empty constructor;
   }
   cvImage cvimage=image.clone();
   if(cvimage.empty()){
      return cv::Mat();
   }
   for(int i=0;i<image.rows;i++){
      for(int j=0;j<image.cols;j++){
         if(cvimage.at<unsigned char>(i,j)==cv::GC_BGD || cvimage.at<unsigned char>(i,j)==cv::GC_PR_BGD){
            cvimage.at<unsigned char>(i,j)=0;
         }
         else{
            cvimage.at<unsigned char>(i,j)=1;
         }
      }
   }
   if(!cvimage.empty()){
      return cvimage;
   }
   return cv::Mat();
}
wxImage ConstructPencilSketchImage(const cvImage& cvimage){
   if(cvimage.empty()){
      return wxNullImage;
   }
   cvImage Channel(cvimage.rows,cvimage.cols,CV_8UC1,cv::Scalar::all(0));
   cvImage cvimage1=cvimage.clone();
   cv::pencilSketch(cvimage,Channel,cvimage1);
   if(cvimage1.empty()){
      return wxNullImage;
   }
   wxImage image=Convert(cvimage1);
   if(image.IsOk()){
      return image;
   }
   return wxNullImage;
}