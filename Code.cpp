#include"Code.h"
#include<cmath>
#include<iostream>
#include<bitset>
#include <boost/dynamic_bitset.hpp>
#include<vector>
#include<map>
code::code(bool **matr, const int str, const int stb){
    this->str=str;
    this->stb=stb;
    this->lenCode=pow(2,str);
    //Make Input Str
    for(int i=0;i<this->lenCode;++i){
        boost::dynamic_bitset<>  bitset(str,i);
        InputStr.push_back(bitset);
    }
    //Make Code Str
    for(const auto &ptr:InputStr){
        std::string code;
            for(int j=0;j<stb;++j){
                int tmp=0;
                for(int k=0;k<str;++k){
                    tmp+=ptr[str-1-k]*matr[k][j];// В битсете обратный порядок!
                }
                code.append(std::to_string(tmp%2));
            }
        boost::dynamic_bitset<>  bitset_code(code);
        CodeStr.push_back(bitset_code);
    }
    //make Decode Table
    DecodeTbl.resize(getLineLagrange());
    for(auto &ptr:DecodeTbl){
        ptr.resize(this->lenCode);
    }
    for(int i=0;i<DecodeTbl[0].size();++i){
        DecodeTbl[0][i]=CodeStr[i];
    }
    //make Liders
    for(int i=0; i<this->stb;i++){
        makeLiders(0,i+1,this->stb);    
    }
    for(int i=1;i<DecodeTbl.size();++i){
        DecodeTbl[i][0]=searchLider(i);
        for(int j=0;j<DecodeTbl[i].size();++j){
            DecodeTbl[i][j]=(DecodeTbl[i][0] ^ DecodeTbl[0][j]);
        }
       // if(findDublicate(0,i+1)){
       //     std::cerr<<"Find Dublicate in table Decode!";
       //     i--;
       //     continue;
       // }
    }

        if(!findDublicate(0,DecodeTbl.size())){
            std::cerr<<"\nDublicate in table Decode Not Founded!!\n";
        }else{
            std::cerr<<"\nFind Dublicate in table Decode!\n";
        }

}

void code::makeLiders(int maxBits, int bits, int numBits) {
    static const int all=numBits;
    if (bits) {
        for(int i=bits-1;i<numBits;i++)
            makeLiders(maxBits+(1<<i),bits-1, i); 
    } else {
        boost::dynamic_bitset<>  btset(all,maxBits);
        Liders.push_back(btset);
    }
}




boost::dynamic_bitset<> code::searchLider(int ind){
            boost::dynamic_bitset<> nulled(stb,0);
            for(int i=0;i<Liders.size();++i){
                boost::dynamic_bitset<>  bits_tmp=Liders[i];
                bool flag =false;
                for(int j=0;j<this->lenCode && !flag;++j){
                    for(int i=0;i<DecodeTbl.size();++i){
                        if (DecodeTbl[i][j]==bits_tmp){
                            flag=true;
                            break;
                        }
                    }
                }
                    if (flag){
                        continue;
                    }else{
                        return bits_tmp;
                    }
                
            }
            return nulled;
}


int code::getDistance( boost::dynamic_bitset<>  bitset){
    int val=0;
    for(int j=0;j<this->stb;++j){
        val+=bitset[j];
    }
    return val;

}

int code::getMinDistance(){
    int min=this->stb;
    for(const auto &ptr:CodeStr){
        int val=getDistance(ptr);
        if (val !=0 && val<min){
            min=val;
        }
    }
    return min;
}

std::string code::getP_pp(){
   std::string result;
   int val=1;
   int i=1;
   result.append("p^"+std::to_string(this->stb));
   while(val<DecodeTbl.size()){
        int all=0;
        for(int j=0;j<DecodeTbl.size();++j){
            if(i==getDistance(DecodeTbl[j][0])){
                all++;
            }
        }
        if(all!=0){
            if (result.size()!=0){
                result.append(" + ");
            }
            result.append(std::to_string(all)+"p^"+std::to_string(this->stb-i)+"q^"+std::to_string(i));
        }
        i++;
        val+=all;
   }
   return result;
}

std::string code::getAnalyse(){
    std::string result;

    std::map<int ,int, std::less<int> > maps;
    for(int i=1;i<DecodeTbl.size();++i){
        int n = getDistance(DecodeTbl[i][0]);
        if (maps.find(n)!=maps.end()){
            maps[n]+=1;
        }else{
            maps[n]=1;
        }
    }
    for(auto &ptr: maps){
        result.append("\n\t("+std::to_string(ptr.first)+"): "\
        +" "+std::to_string(ptr.second)
        +"\tTotal: "+std::to_string(fact(this->stb)/(fact(ptr.first)*fact(this->stb-ptr.first))));
    }
    return result;
}

std::string code::Decode(std::string inp){
    std::string result ;
    boost::dynamic_bitset<> input(inp);
    if(input.size()!=this->stb){
        return "Err: Uncorrect len";
    }
    for(int i=0;i<DecodeTbl.size();++i){
        for(int j=0;j<DecodeTbl[i].size();++j){
            if(input== DecodeTbl[i][j]){
                boost::to_string(DecodeTbl[0][j],result);
                return result;
            }
        }
    }
    return result;
}

std::string code::getP_noo(){
    std::string result;
    int val=1; // запоминаем нулевой код;
    int i=1; // кратность с 1
    while(val<this->lenCode){
        int all=0;
        for(const auto &ptr:CodeStr){
            if(i==getDistance(ptr)){
                all++;
            }
        }
        if(all!=0){
            if (result.size()!=0){
                result.append(" + ");
            }
            result.append(std::to_string(all)+"p^"+std::to_string(this->stb-i)+"q^"+std::to_string(i));
        }
        i++;
        val+=all;
                
    }
    return result;
}

void code::printTableCoding(){
    std::cout<<"\n\t\tTable Coding: \n";
    for(int i=0;i<this->lenCode;++i){
        std::cout<<"\n"<<InputStr[i]<<" ==> "<<CodeStr[i];
    }
}

void code::printTableDecoding(){
    std::cout<<"\n\t\tTable Decoding: \n";
    for(int i=0;i<DecodeTbl.size();++i){
        for(int j=0;j<DecodeTbl[i].size();++j){
            std::cout<<DecodeTbl[i][j]<<"  ";
        }
        std::cout<<"\n";
    }
}
bool code::findDublicate(int imin, int imax){
    for(int i=imin;i<imax;++i){
        for(int j=0;j<DecodeTbl[imin].size();++j){
            for(int i2=imin;i2<imax;++i2){
                for(int j2=0;j2<DecodeTbl[imin].size();++j2){
                    if(DecodeTbl[i][j]==DecodeTbl[i2][j2]&& (i!=i2 && j!=j2)){

                        return true;
                    }
                }
            }
        }
    }
    return false;
}


int code::getLineLagrange(){
    return pow(2,this->stb)/pow(2,this->str);
}

int fact(int n){
    return(n==1||n==0)?1:fact(n-1)*n;
}
