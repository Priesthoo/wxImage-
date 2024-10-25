/*
Image Manipulation.....
Image Arithmetic............
Add,Subtract,Multiply,divide...
Operators,There are different operators that can be used in image manipulation...
class Operator{  This is class frow which all other operator class will inherited..,we hereby proceed the define the verbs(member functions)...
public:
  Operator()=default
}; 
    There are different types of image operators which are used to manipulate images giving results....,And they are:
1).Creation operators.
2).Channel operators.
3).Information operators.
4).Intensity operators.
5).Geometry operators.
6).Transformation operators.
7).Expansion operators.

*/
#include<wx/vector.h>

template<class T=double>
class GuassianFilter:public wxVector<T>{

    public:
    GuassianFilter():wxVector<T>(){

    }
    void Push_back(const T& value){
      this->push_back(value);
    }
    void Clear(){
      this->clear();
    }
    T& operator[](const size_t& idx){
      return this->at(idx);
    }
    T operator[](const size_t& idx) const{
      return this->at(idx);
    }
    void ConstructGuassianFilter();
};
template<class T=int>
class SmoothingFilter:public wxVector<T>{
   public:
   SmoothingFilter():wxVector<T>(){
     ConstructSmoothingFilter();
   }
   void ConstructSmoothingFilter(){
    for(int i=0;i<9;i++){
      this->push_back(1);
    }
    return;
   }
   T& operator[](const size_t& idx){
      return this->at(idx);
    }
    T operator[](const size_t& idx) const{
      return this->at(idx);
    }
    size_t GetFilterSize() const{
      return this->size();
    }
};
