#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include"Node.h"
#include"Pp.h"
class genealogy {
private:
    int idnum;
    Node* ancestor;
    vector<Pp*>all;
    int male;
    int female;
    int AveHeight;
public:
    genealogy();
    void menu();
    Pp* NewPp();
    int FindFromAll(string pname);
    void FindFromTree(Node* root, int id, bool& res, Node*& tar);
    void DelFromTree(Node* root);
    void printsb(Pp* a);
    void readTree();
    void CreatG();
    void save();
    void SaveForTree(Node* root, ofstream& ofs);
    void SaveForTree2(Node* root, ofstream& ofs, string str);
    void readPp();
    void InsPp();
    void DelPp();
    void inquire();
    void ModPp();
    void showtree(Node* root,string str);
};
