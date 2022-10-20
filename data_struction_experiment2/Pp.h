#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<fstream>

class Pp {
public:
    int id;
    string pname;
    string name;
    string birth_date;
    string death_date;
    string gender;
    int height;
    string degree;
    string occupation;
    string highest_position;

public:
    Pp() {}
    Pp(int id, string pname, string name, string birth_date, string death_date, string gender, int height, string degree, string occupation, string highest_position);
    Pp(const Pp& a);
    ostream& operator<<(ostream& out);
};
