module Resource;

import <string>;
import <sstream>;
import <iostream>;

Resource::Resource(int caffeine, int lab, int lecture, int study, int tutorial)
    : caffeine{caffeine}, lab{lab}, lecture{lecture}, study{study}, tutorial{tutorial} {}

Resource::Resource(std::string resource, int amount) {
    if (resource == "CAFFEINE") {
        caffeine = amount;
    } else if (resource == "LAB") {
        lab = amount;
    } else if (resource == "LECTURE") {
        lecture = amount;
    } else if (resource == "STUDY") {
        study = amount;
    } else if (resource == "TUTORIAL") {
        tutorial = amount;
    }
}

Resource Resource::operator+(const Resource &other) const {
    return Resource(
        caffeine + other.caffeine,
        lab + other.lab,
        lecture + other.lecture,
        study + other.study,
        tutorial + other.tutorial
    );
}

Resource Resource::operator-(const Resource &other) const {
    return Resource(
        caffeine - other.caffeine,
        lab - other.lab,
        lecture - other.lecture,
        study - other.study,
        tutorial - other.tutorial
    );
}

Resource& Resource::operator+=(const Resource &other) {
    caffeine += other.caffeine;
    lab += other.lab;
    lecture += other.lecture;
    study += other.study;
    tutorial += other.tutorial;
    return *this;
}

Resource& Resource::operator-=(const Resource &other) {
    caffeine -= other.caffeine;
    lab -= other.lab;
    lecture -= other.lecture;
    study -= other.study;
    tutorial -= other.tutorial;
    return *this;
}

bool Resource::operator<=(const Resource &other) const {
    return caffeine <= other.caffeine &&
           lab <= other.lab &&
           lecture <= other.lecture &&
           study <= other.study &&
           tutorial <= other.tutorial;
}

bool Resource::operator>=(const Resource &other) const {
    return caffeine >= other.caffeine &&
           lab >= other.lab &&
           lecture >= other.lecture &&
           study >= other.study &&
           tutorial >= other.tutorial;
}

int Resource::count() const {
    return caffeine + lab + lecture + study + tutorial;
}

std::vector<int> Resource::to_vector() const {
    int types[5] = {caffeine, lab, lecture, study, tutorial};
    std::vector<int> ret_val;
    for(int type_ind = 0; i < 5; i++){
        for(int i = 0; i < types[type_ind]; i++){
            // construct a vector containing <resource_amount> of <resource_int>
            ret_val.emplace_back(type_ind);
        }
    }
    // return by value
    return ret_val;
}


std::string Resource::get_save_string() const {
    std::ostringstream oss;
    // may need to change if we decide to use an array instead
    oss << caffeine << ' ' << lab << ' ' << lecture << ' ' << study << ' ' << tutorial;
    // turns the stringstream buffer to string
    return oss.str();
    // consider just passing oss instead of returning string
}


// output operator
std::ostream &operator<<(std::ostream &os, const Resource & resource){
    os << resource.caffeine << " caffeines, ";
    os << resource.lab << " labs, ";
    os << resource.lecture << " lectures, ";
    os << resource.study << " studies, ";
    os << "and " << resource.tutorial << " tutorials.";

    return os;
}
