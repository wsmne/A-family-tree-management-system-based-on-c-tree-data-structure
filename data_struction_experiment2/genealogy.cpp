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
        cout << "0.退出" << endl;
        cout << "1.查询成员" << endl;
        cout << "2.加入成员" << endl;
        cout << "3.修改成员" << endl;
        cout << "4.删除成员" << endl;
        cout << "5.展示树" << endl;
        int choice;
        string str="";
        cout << "请输入0-4" << endl;
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
    cout << "请输入查询方式" << endl;
    cout << "1.查询所有" << endl;
    cout << "2.查询单个成员" << endl;
    int ch;
    cin >> ch;
    switch (ch)
    {
    case 1:
        for (auto& a : all)printsb(a);
        break;
    case 2: {
        cout << "请输入要查找的成员姓名：" << endl;
        string name;
        cin >> name;
        int pos = FindFromAll(name);
        if (pos == -1) {
            cout << "查无此人" << endl;
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
    cout << "请输入父或母姓名" << endl;
    string pname;
    cin >> pname;
    int k = FindFromAll(pname);
    if (k == -1) {
        cout << "不存在该父母" << endl;
        return nullptr;
    }
    cout << "请依次输入姓名，出生日期，死亡日期，性别，身高，学历，职业，最高职称：" << "(日期用：xx-xx-xx格式）" << endl;
    cout << "该成员编号:" << idnum << endl;
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
    cout << "创建新家谱" << endl;
    cout << "请输入唯一祖先:" << endl;
    cout << "请依次输入姓名，出生日期，死亡日期，性别，身高，学历，职业，最高职称：" << "(日期用：xx-xx-xx格式）" << endl;
    cout << "该成员编号:" << idnum << endl;
    string name;
    string birth_date;
    string death_date;
    string pname = "-1";
    string gender;
    int height;
    string degree;
    string occupation;
    string highest_position;
    pname = "无";
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
    cout << "请输入要修改的成员的姓名" << endl;
    string name;
    cin >> name;
    int pos=FindFromAll(name);
    if (pos == -1) {
        cout << "查无此人" << endl;
        return;
    }
    cout << "请依次输入该成员出生日期，死亡日期，性别，身高，学历，职业，最高职称：" << "(日期用：xx-xx-xx格式）" << endl;
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
    cout << "修改成功" << endl;
}
void genealogy::DelPp() {
    cout << "请输入要删除的成员的姓名" << endl;
    string name;
    cin >> name;
    bool res = 0;
    int pos = FindFromAll(name);
    if (pos == -1) {
        cout << "查无此人" << endl;
        return;
    }
    Pp* p = all[pos];
    Node* pp = nullptr;
    FindFromTree(ancestor,p->id,res,pp);//找到父母节点
    all.erase(all.begin() + pos);//在线性表中删除该成员

    Node* tar = pp->parents;//在父母结点的孩子表中删除该结点
    for (int i = 0; i < tar->child.size(); ++i) {
        if (tar->child[i]->id == p->id)tar->child.erase(tar->child.begin() + i);
    }
    DelFromTree(pp);
    delete p;
    cout << "删除成功" << endl;
    save();
}
void genealogy::InsPp() {
    Pp* p = NewPp();
    if (p == nullptr)return;
    int k = FindFromAll(p->pname);
    int pid = all[k]->id;
    bool res = 0;
    Node* tar = nullptr;
    FindFromTree(ancestor, pid, res, tar);//找到父母结点
    if (!res) {
        cout << "插入失败" << endl;
        idnum--;
        return;

    }
    Node* q = new Node(p->id);
    tar->child.push_back(q);//插入到父母结点的孩子表中
    q->parents = tar;
    cout << "插入成功" << endl;
    save();
}