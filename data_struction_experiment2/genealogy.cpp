#include"genealogy.h"
genealogy::genealogy() {
    idnum = 0;
    readPp();
    if (all.size() == 0) {
        idnum = 0;
        CreatG();
    }
    else readTree();
}
void genealogy::menu() {
    while (1) {
        system("cls");
        cout << "0.�˳�" << endl;
        cout << "1.��ѯ��Ա" << endl;
        cout << "2.�����Ա" << endl;
        cout << "3.�޸ĳ�Ա" << endl;
        cout << "4.ɾ����Ա" << endl;
        cout << "5.չʾ��" << endl;
        int choice;
        string str="";
        cout << "������0-4" << endl;
        cin >> choice;
        switch (choice)
        {
        case 0:
            save();
            exit(0);
            break;
        case 1:
            inquire();
            system("pause");
            break;
        case 2:
            InsPp();
            system("pause");
            break;
        case 3:
            ModPp();
            system("pause");
            break;
        case 4:
            DelPp();
            system("pause");
            break;
        case 5:
            showtree(ancestor,str);
            system("pause");
            break;
        default:
            break;
        }
    }
    
}
void genealogy::printsb(Pp* a) {
    cout << a->id << " " << a->pname << " " << a->name << " " << a->birth_date << " "
        << a->death_date << " " << a->gender << " " << a->height << " "
        << a->degree << " " << a->occupation << " " << a->highest_position << endl;
}
void genealogy::inquire() {
    cout << "�������ѯ��ʽ" << endl;
    cout << "1.��ѯ����" << endl;
    cout << "2.��ѯ������Ա" << endl;
    int ch;
    cin >> ch;
    switch (ch)
    {
    case 1:
        for (auto& a : all)printsb(a);
        break;
    case 2: {
        cout << "������Ҫ���ҵĳ�Ա������" << endl;
        string name;
        cin >> name;
        int pos = FindFromAll(name);
        if (pos == -1) {
            cout << "���޴���" << endl;
            return;
        }
        printsb(all[pos]);
        break;
    }
    }
}
void genealogy::showtree(Node* root,string str) {
    if (root == nullptr)return;
    if (root->parents == nullptr)str += to_string(root->id);
    else str = str + " " + to_string(root->id);
    if (root->child.size() == 0) cout << str << endl;
    else {
        for (auto& a : root->child) {
            showtree(a, str);
        }
    }
}
Pp* genealogy::NewPp() {
    cout << "�����븸��ĸ����" << endl;
    string pname;
    cin >> pname;
    int k = FindFromAll(pname);
    if (k == -1) {
        cout << "�����ڸø�ĸ" << endl;
        return nullptr;
    }
    cout << "�����������������������ڣ��������ڣ��Ա���ߣ�ѧ����ְҵ�����ְ�ƣ�" << "(�����ã�xx-xx-xx��ʽ��" << endl;
    cout << "�ó�Ա���:" << idnum << endl;
    string name;
    string birth_date;
    string death_date;
    string gender;
    int height;
    string degree;
    string occupation;
    string highest_position;
    cin >> name >> birth_date >> death_date >> gender >> height >> degree >> occupation >> highest_position;
    Pp* p = new Pp(idnum, pname, name, birth_date, death_date,
        gender, height, degree, occupation, highest_position);
    all.push_back(p);
    idnum++;
    return p;
}
void genealogy::DelFromTree(Node* root) {
    if (root == nullptr)return;
    int n = root->child.size();
    for (int i = n-1; i >=0;--i) {
        DelFromTree(root->child[i]);
        delete root->child[i];
        root->child.erase(root->child.begin() + i);
    }
    delete root;
}

int genealogy::FindFromAll(string name) {
    for (int i = 0; i < all.size();++i) {
        if (all[i]->name == name)return i;
    }
    return -1;
}
void genealogy::FindFromTree(Node* root, int id, bool& res, Node*& tar) {
    if (res == 1)return;
    if (root == nullptr)return;
    if (root->id == id) {
        tar = root;
        res = 1;
        return;
    }
    for (int i = 0; i < root->child.size(); ++i) {
        FindFromTree(root->child[i], id, res, tar);
    }
    return;
}

void genealogy::CreatG() {
    cout << "�����¼���" << endl;
    cout << "������Ψһ����:" << endl;
    cout << "�����������������������ڣ��������ڣ��Ա���ߣ�ѧ����ְҵ�����ְ�ƣ�" << "(�����ã�xx-xx-xx��ʽ��" << endl;
    cout << "�ó�Ա���:" << idnum << endl;
    string name;
    string birth_date;
    string death_date;
    string pname = "-1";
    string gender;
    int height;
    string degree;
    string occupation;
    string highest_position;
    pname = "��";
    cin >>  name >> birth_date >> death_date >> gender >> height >> degree >> occupation >> highest_position;
    Pp* p = new Pp(idnum, pname, name, birth_date, death_date,
        gender, height, degree, occupation, highest_position);
    all.push_back(p);
    idnum++;
    
    ancestor = new Node(p->id);
    return;
}
void genealogy::readTree() {
    ifstream ifs;
    ifs.open("TreeNode.txt", ios::in);
    int a, b;
    while (ifs >> a >> b) {
        Node* p = new Node(b);
        if (a == -1) {    
            ancestor = p;
        }
        else {
            bool res = 0;
            Node* tar = nullptr;
            FindFromTree(ancestor, a, res, tar);
            tar->child.push_back(p);
            p->parents = tar;
        }
    }
}
void genealogy::readPp() {
    ifstream ifs;
    ifs.open("genealogy.txt", ios::in);
    if (!ifs.is_open()) {
        ifs.close();
        return;
    }
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
    while (ifs >> id && ifs >> pname && ifs >> name && ifs >> birth_date && ifs >> death_date && ifs >> gender
        && ifs >> height && ifs >> degree && ifs >> occupation && ifs >> highest_position) {
        idnum = id + 1;
        Pp* p = new Pp(id, pname, name, birth_date, death_date,
            gender, height, degree, occupation, highest_position);
        all.push_back(p);
    }
    ifs.close();
}
void genealogy::SaveForTree(Node* root,ofstream& ofs) {
    if (root == nullptr)return;
    if (root->parents == NULL) {
        ofs << "-1";
    }
    else {
        ofs << root->parents->id;
    }
    ofs << " " << root->id;
    ofs << endl;
    for (auto& a : root->child) {
        SaveForTree(a,ofs);
    }
}
void genealogy::SaveForTree2(Node* root, ofstream& ofs, string str) {
    if (root == nullptr)return;
    if (root->parents == nullptr)str += to_string(root->id);
    else str = str + " " + to_string(root->id);
    if (root->child.size() == 0) ofs << str << endl;
    else {
        for (auto& a : root->child) {
            SaveForTree2(a, ofs, str);
        }
    }
}

void genealogy::save() {
    ofstream ofs;
    ofs.open("genealogy.txt", ios::out);
    for (auto& a : all) {
        ofs << a->id <<" " <<a->pname<<" "<< a->name << " " << a->birth_date << " "
            << a->death_date << " " << a->gender << " " << a->height << " " 
            << a->degree << " " << a->occupation << " " << a->highest_position << endl;
    }
    ofs.close();
    ofstream  ofs1;
    ofs.open("TreeNode.txt", ios::out);
    ofs1.open("Tree.txt", ios::out);
    SaveForTree(ancestor,ofs);
    string str = "";
    SaveForTree2(ancestor, ofs1, str);
    ofs.close(); ofs1.close();
}

void genealogy::ModPp() {
    cout << "������Ҫ�޸ĵĳ�Ա������" << endl;
    string name;
    cin >> name;
    int pos=FindFromAll(name);
    if (pos == -1) {
        cout << "���޴���" << endl;
        return;
    }
    cout << "����������ó�Ա�������ڣ��������ڣ��Ա���ߣ�ѧ����ְҵ�����ְ�ƣ�" << "(�����ã�xx-xx-xx��ʽ��" << endl;
    string birth_date;
    string death_date;
    string gender;
    int height;
    string degree;
    string occupation;
    string highest_position;
    cin >> birth_date >> death_date >> gender >> height >> degree >> occupation >> highest_position;
    all[pos]->birth_date = birth_date;
    all[pos]->death_date = death_date;
    all[pos]->gender = gender;
    all[pos]->height = height;
    all[pos]->degree = degree;
    all[pos]->occupation = occupation;
    all[pos]->highest_position = highest_position;
    save();
    cout << "�޸ĳɹ�" << endl;
}
void genealogy::DelPp() {
    cout << "������Ҫɾ���ĳ�Ա������" << endl;
    string name;
    cin >> name;
    bool res = 0;
    int pos = FindFromAll(name);
    if (pos == -1) {
        cout << "���޴���" << endl;
        return;
    }
    Pp* p = all[pos];
    Node* pp = nullptr;
    FindFromTree(ancestor,p->id,res,pp);//�ҵ���ĸ�ڵ�
    all.erase(all.begin() + pos);//�����Ա���ɾ���ó�Ա

    Node* tar = pp->parents;//�ڸ�ĸ���ĺ��ӱ���ɾ���ý��
    for (int i = 0; i < tar->child.size(); ++i) {
        if (tar->child[i]->id == p->id)tar->child.erase(tar->child.begin() + i);
    }
    DelFromTree(pp);
    delete p;
    cout << "ɾ���ɹ�" << endl;
    save();
}
void genealogy::InsPp() {
    Pp* p = NewPp();
    if (p == nullptr)return;
    int k = FindFromAll(p->pname);
    int pid = all[k]->id;
    bool res = 0;
    Node* tar = nullptr;
    FindFromTree(ancestor, pid, res, tar);//�ҵ���ĸ���
    if (!res) {
        cout << "����ʧ��" << endl;
        idnum--;
        return;

    }
    Node* q = new Node(p->id);
    tar->child.push_back(q);//���뵽��ĸ���ĺ��ӱ���
    q->parents = tar;
    cout << "����ɹ�" << endl;
    save();
}