#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "NumberWithUnits.hpp"
using namespace std;

static vector<pair<string, string>> mapOfUnits;

namespace ariel{
 	map<string, map<string, double>> NumberWithUnits::mapOfData;
    	NumberWithUnits::NumberWithUnits(double num, const string &s){
        if (mapOfData.count(s) == 0) {
            throw invalid_argument("the unit is invalid");
        }
        this->number = num;
        this->ans = s;
    }
    void NumberWithUnits::read_units(ifstream &file){
    	 double num = 0,num2 =0;
        string line,n1,n2;
        string a,b,c;
        while (file >> num >> n1 >> line >> num2 >> n2){
            mapOfData[n1][n2] = num2 / 1;
            mapOfData[n2][n1] = 1 / num2;
           mapOfUnits.emplace_back(n1, n2);
           mapOfUnits.emplace_back(n2, n1); 
        	for (auto &it : mapOfUnits){
            	a = it.first;
            	b = it.second;
            	for (auto &it2 : NumberWithUnits::mapOfData[b]){
                c = it2.first;
                if (c != a){
                NumberWithUnits::mapOfData[a][c] = NumberWithUnits::mapOfData[b][c] * NumberWithUnits::mapOfData[a][b];
                NumberWithUnits::mapOfData[c][a] = 1 / NumberWithUnits::mapOfData[a][c];
                }
            }
        }
        }
    }
    double NumberWithUnits::convert_to_units(double num, const string &a, const string &b){
        if (a == b){
            return num;
        }
      	 if(a != b){
           return (num * NumberWithUnits::mapOfData.at(a).at(b));
        }
            throw invalid_argument("Units Error");
       
    }
    int compare(const NumberWithUnits &a, const NumberWithUnits &b){
        double n = NumberWithUnits::convert_to_units(b.number, b.ans, a.ans);
        static const double t = 0.0001;
        int ans = 0;
        double d = n - a.number;
        double c  = a.number - n;
        if (d > t){
            ans = -1;
        }
        else if (c > t){
            ans = 1;
        }
        else{
            ans = 0;
        }
        return ans;
    }
    ostream &operator<<(ostream &out, const NumberWithUnits &a) {
        return (out << a.number << '[' << a.ans << ']');
    }
    istream& operator>>(istream& in, NumberWithUnits& n){
        
        double a = 0;
        char left=' ',right=' ';
        string t;
        in >> skipws >> a >> left >> t;
        unsigned int len = t.length();
        char temp = t.at(len - 1);
        if (temp != ']'){

            in >> right;
        }
        else{
            t = t.substr(0, len-1);
        }
        if (NumberWithUnits::mapOfData.count(t) == 0)
        {
            throw invalid_argument("UNKNOWN UNIT");
        }
        n.number = a;
        n.ans = t;
        return in;
    }
    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &a){
        double n = NumberWithUnits::convert_to_units(a.number,a.ans, this->ans);
        
         return NumberWithUnits(this->number+n, this->ans);
    }

    NumberWithUnits NumberWithUnits::operator+(){
    	NumberWithUnits t{this->number,this->ans};
    	return t;
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &a)
    {
        double answer = NumberWithUnits::convert_to_units(a.number, a.ans, this->ans);
        return NumberWithUnits(this->number - answer, this->ans);
    }

    NumberWithUnits NumberWithUnits::operator-(){
    	NumberWithUnits t{-(this->number), this->ans};
   	 return t;
 
    }
NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &a){
    	double n = NumberWithUnits::convert_to_units(a.number, a.ans, this->ans);
    	this->number +=n;
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &a){
    double n = NumberWithUnits::convert_to_units(a.number, a.ans, this->ans);
        this->number -= n;
        return *this;
    }

    bool operator>(const NumberWithUnits &a, const NumberWithUnits &b){
      bool flag = false;
      if(!(a <= b)){
      	flag=true;
      }
      return flag;
    }

    bool operator>=(const NumberWithUnits &a, const NumberWithUnits &b)
    {
    bool flag = false;
    if(compare(a, b) >= 0){
    	flag=true;
    	}
    	return flag;
    }

    bool operator<(const NumberWithUnits &a, const NumberWithUnits &b){
    bool flag = false;
    if(!(a >= b)){
    	flag=true;
    	}
    	return flag;
        
    }

    bool operator<=(const NumberWithUnits &a, const NumberWithUnits &b)
    {
    bool flag=false;
    if(compare(a, b) <= 0){
    	flag=true;
    	}
    	return flag;
       
    }

    bool operator==(const NumberWithUnits &a, const NumberWithUnits &b)
    {
    bool flag = false;
    if(compare(a, b) == 0){
    	flag=true;
    	}
    	return flag;
    
    }

    bool operator!=(const NumberWithUnits &a, const NumberWithUnits &b)
    {
    bool flag = false;
    if(!(a == b)){
    	flag=true;
    	}
    	return flag;
    }
     NumberWithUnits &NumberWithUnits::operator++(){
        ++(this->number);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int n){
        return NumberWithUnits((this->number)++, this->ans);
    }
     NumberWithUnits &NumberWithUnits::operator--(){
        --(this->number);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int n){
        return NumberWithUnits((this->number)--, this->ans);
    }
    NumberWithUnits operator*(const NumberWithUnits &a, double num){
        return NumberWithUnits(a.number * num, a.ans);
    }
    NumberWithUnits operator*(double num, const NumberWithUnits &a){
        return NumberWithUnits(a.number * num, a.ans);
    }
    NumberWithUnits &NumberWithUnits::operator*=(double num){
        this->number *= num;
        return *this;
    }
}
