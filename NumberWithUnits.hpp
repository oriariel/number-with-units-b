#pragma once

#include <string>
#include <utility>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
namespace ariel
{
    class NumberWithUnits
    {
    private:
        double number;
        string ans;
     	
     	//static void function_to_check();
        static double convert_to_units(double num, const string &a, const string &b);

    public:
        static map<string,map<string, double>> mapOfData;
        NumberWithUnits(double num, const string &s);
	static void read_units(ifstream &file);
	friend int compare(const NumberWithUnits &a, const NumberWithUnits &b);
        NumberWithUnits operator+(const NumberWithUnits &a);
        NumberWithUnits operator+();
        NumberWithUnits &operator+=(const NumberWithUnits &a);
        NumberWithUnits operator-(const NumberWithUnits &a);
        NumberWithUnits operator-();
        NumberWithUnits &operator-=(const NumberWithUnits &a);
        
        friend bool operator>(const NumberWithUnits &a, const NumberWithUnits &b);
        friend bool operator>=(const NumberWithUnits &a, const NumberWithUnits &b);
        friend bool operator<(const NumberWithUnits &a, const NumberWithUnits &b);
        friend bool operator<=(const NumberWithUnits &a, const NumberWithUnits &b);
        friend bool operator==(const NumberWithUnits &a, const NumberWithUnits &b);
        friend bool operator!=(const NumberWithUnits &a, const NumberWithUnits &b);
        NumberWithUnits operator++(int n);
        NumberWithUnits &operator++();
        NumberWithUnits operator--(int n);
        NumberWithUnits &operator--();
        friend NumberWithUnits operator*(const NumberWithUnits &a, double num);
        friend NumberWithUnits operator*(double num, const NumberWithUnits &a);
        NumberWithUnits &operator*=(double num);
        friend ostream &operator<<(ostream &out, const NumberWithUnits &a);
        friend istream &operator>>(istream &in, NumberWithUnits &n);
    };
}
