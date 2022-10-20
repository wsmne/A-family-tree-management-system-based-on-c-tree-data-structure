#include"Pp.h"

Pp::Pp(int id, string pname, string name, string birth_date, string death_date, string gender, int height, string degree, string occupation, string highest_position) {
    this->id = id;
    this->pname = pname;
    this->name = name;
    this->birth_date = birth_date;
    this->death_date = death_date;
    this->gender = gender;
    this->height = height;
    this->degree = degree;
    this->occupation = occupation;
    this->highest_position = highest_position;
}
Pp::Pp(const Pp& a) {
    this->id = a.id;
    this->name = a.name;
    this->birth_date = a.birth_date;
    this->death_date = a.death_date;
    this->gender = a.gender;
    this->height = a.height;
    this->degree = a.degree;
    this->occupation = a.occupation;
    this->highest_position = a.highest_position;
}
ostream& Pp::operator<<(ostream& out) {
    out << this->id << " " << this->name << " " << this->birth_date << " " << this->death_date << " " << this->gender << " " << this->height << " "
        << this->degree << " " << this->occupation << " " << this->highest_position << endl;
    return out;
}
