#ifndef CODE_H
#define CODE_H
#include<vector>
#include <boost/dynamic_bitset.hpp>

class code{
    int str, stb, lenCode;
    std::vector< boost::dynamic_bitset<> > InputStr;
    std::vector< boost::dynamic_bitset<> > CodeStr;
    std::vector< boost::dynamic_bitset<> > Liders;
    std::vector< std::vector< boost::dynamic_bitset<> > > DecodeTbl;
    int getDistance(boost::dynamic_bitset<>  bitset);
    boost::dynamic_bitset<> searchLider(int i);
    void makeLiders(int maxBits, int bits, int numBits);
    bool findDublicate(int imin, int imax);
public:
    code(bool **matr, const int str,const int stb);
    int getMinDistance();
    std::string getP_noo();
    std::string getP_pp();
    std::string getAnalyse();
    std::string Decode(std::string);
    void printTableCoding();
    void printTableDecoding();
    int getLineLagrange();
};
int fact(int n);
#endif
