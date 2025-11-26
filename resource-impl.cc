module Resource;

import <string>;
import <sstream>;

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


void get_save_string() const {
    std::ostringstream oss;
    // may need to change if we decide to use an array instead
    oss << caffeine << ' ' << lab << ' ' << lecture << ' ' << study << ' ' << tutorial;
    // turns the stringstream buffer to string
    return oss.str();
    // consider just passing oss instead of returning string
}