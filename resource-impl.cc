module Resource;

import <string>;

Resource::Resource(int caffeine, int lab, int lecture, int study, int tutorial)
    : caffeine{caffeine}, lab{lab}, lecture{lecture}, study{study}, tutorial{tutorial} {}

Resource::Resource(std::string resource) {
    if (resource == "CAFFEINE") {
        caffeine = 1;
    } else if (resource == "LAB") {
        lab = 1;
    } else if (resource == "LECTURE") {
        lecture = 1;
    } else if (resource == "STUDY") {
        study = 1;
    } else if (resource == "TUTORIAL") {
        tutorial = 1;
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
