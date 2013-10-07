#include <iostream>
#include <fstream>
#include "Code.h"
#include<string>
#include<sstream>

int main(int argv, char** argc){
    std::ifstream file;
    bool **matr;
    int str=0, stb=0;
    std::string filename;
    if(argv!=1){
        filename=argc[1];
    }else{
        filename="data";
    }
    file.open(filename.c_str());
    std::string tmp_str;
    while( !file.eof() ){
        std::getline(file,tmp_str);
         if(tmp_str.size()!=0){
              str++;
              if(stb==0){
                  stb=tmp_str.size();
              }else if (stb!=tmp_str.size()){
                  std::cerr<<"\nОшибка "<<filename<<":"<<str<<": кол-во эл-тов в строках в матрице должно быть одинаковым!\n";
                  file.close();
                  return 1;
              }
         }
    }
    matr = new bool*[str];
    file.close();
    file.open(filename.c_str());

    for(int k=0;k<str;++k){
        
        std::string tmp;
        std::getline(file,tmp);
        
        if(tmp.size()!=0){
            matr[k]=new bool [tmp.size()];
            for(int j=0;j<tmp.size();++j){
                if (tmp[j]=='0') {
                    matr[k][j]=0;
                }else{
                    matr[k][j]=1;
                }

            }
        }
    }
    code NewCode=code (matr,str,stb);
     std::cout<<"\n1)\n";
   NewCode.printTableCoding();
    std::cout<<"\n\n\n";
    std::cout<<"\n2)\n";
    std::cout<<"\nMin_Distance: "<<NewCode.getMinDistance();
    std::cout<<"\nP_noo= "<<NewCode.getP_noo();
    std::cout<<"\nmin_d= "<<NewCode.getMinDistance();
    std::cout<<"\nmax K_обн.= min_d-1 = "<<NewCode.getMinDistance()-1;
    std::cout<<"\nmax K_исп.=  K_обн/2 = "<<(NewCode.getMinDistance()-1)/2;
    std::cout<<"\n3)\n";
    std::cout<<"\n\t Высота табл. декод. по Лангранжу: = (2^n)/(2^m)= "<<NewCode.getLineLagrange();
    NewCode.printTableDecoding();
    std::cout<<"\n4)\n";
    std::cout<<"\n\tP_пп.= "<<NewCode.getP_pp();
    std::cout<<"\nКодом исправленны ошибки:\n"<<NewCode.getAnalyse();
    std::cout<<"\n5)\n Для выхода, введите \'q\'";
    std::string menu;
    while(true){
        std::cout<<"\n Введите код: \n";
        std::cin>>menu;
        if(menu=="q"){
            break;
        }
        std::cout<<"\n"<<menu<<" --> "<<NewCode.Decode(menu)<< " --> "<<menu.substr(0,str)<<" .";
    }
    for (int i=0; i<str;++i){
        delete matr[i];
    }
    delete[] matr;
    std::cout<<"\n";
    return 0;
}
