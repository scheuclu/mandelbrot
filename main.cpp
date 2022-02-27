#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <complex>
#include <omp.h>

#define MAXITER 512

class Image{
    public:
      Image(int H, int W): H(H), W(W) {
          for(int h=0; h<H; ++h){
              data.push_back(std::vector<int> (W, 0));
          }
      }

      void set_pixel(int h, int w, int val){
          data[h][w]=val;
      }

      void print(){
        for(int h=0; h<this->H; h++){
            for (int w=0; w<this->W; w++){
               std::cout<<this->data[h][w]<<" ";
            }
            std::cout<<std::endl;
        }
      }

      void to_file(std::string path){
        std::ofstream myfile;
        myfile.open(path);
        myfile << "P3\n";
        myfile << this->W<<" "<<this->H<<std::endl;
        myfile << MAXITER;
        
        for(int h=0; h<this->H; h++){ //Loop over rows
            myfile<<std::endl;
            for (int w=0; w<this->W; w++){ //Loop over columns
              int val = data[h][w];
              double frac = val/255.0;
              int r = (int)(pow(frac,4)*255);
              int g = (int)(pow(frac,2)*255);
              int b = val;
              myfile<<r<<" "<<g<<" "<<b;
              myfile<<std::endl; 
            }
        }
        myfile.close();
      }

      int getH(){
          return this->H;
      }

      int getW(){
          return this->W;
      }

    private:
      int W, H;
      std::vector<std::vector<int> > data;
};


int test_mandelbrot(std::complex<double> cnum){
    std::complex<double> z(0.0, 0.0);
    double oldabs = 0.0;
    double newabs;
    for(int i=0; i<MAXITER/2; i++){
        z=z*z+cnum;
        z=z*z+cnum;
        newabs=std::abs(z);
        if (std::abs(z)>2.0){
            return i*2;
        }
        if(i%5==0){
            if (newabs/oldabs>0.99 && newabs/oldabs<1.01){
                return MAXITER;
            }
        }
    }
    return MAXITER;
}



Image* getMandelbrot(double loc_x, double loc_y, double size_x, double size_y, int H, int W){
    
    Image *img = new Image(H, W);
    double l= loc_x-size_x*0.5;
    double t= loc_y-size_y*0.5;
    double r= loc_x+size_x*0.5;
    double b= loc_y+size_y*0.5;    

    for(int h=0; h<img->getH(); h++){
        //int tid = omp_get_thread_num();
        //printf("Hello world from omp thread %d\n", tid);
        for (int w=0; w<img->getW(); w++){
            double pos_real = l+(r-l)/W*w;
            double pos_imag = t+(b-t)/H*h;
            std::complex<double> cnum(pos_real, pos_imag);

            int val = test_mandelbrot(cnum);
            //img->set_pixel(h, w, (int)(255-255*(float)val/MAXITER));
            //std::cout<<val<<" "<<255.0-255.0*(float)val/MAXITER<<std::endl;
            //img->set_pixel(h, w, 255.0-255.0*(float)val/(float)MAXITER);
            img->set_pixel(h, w, MAXITER-val);
        }
    }
  
  return img;
}


int main(){
    
    int W=1920*2;
    int H=1080*2;
    int N=1000;//672

    double loc_x=-0.745158;
    double loc_y=0.1125747;
    //double size_x=0.000002;
    //double size_y=0.000002;
    double size_x=1.92*2;
    double size_y=1.08*2;
    // double size_x=0.2;
    // double size_y=0.2;

    int count=0;

    #pragma omp parallel for
    for(int i=0; i<N; ++i){
        std::stringstream ss;
        ss << "output/image_"<< std::setfill('0') << std::setw(5) << i<<".ppm";
        std::string outpath = ss.str();

        Image* img = getMandelbrot(loc_x, loc_y, size_x, size_y, H, W);
        img->to_file(outpath);

        size_x*=0.98;
        size_y*=0.98;
        count++;
        std::cout<<count<<"/"<<N<<std::endl;

    }

    return 0;
}