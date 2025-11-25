module Resource;


import <string>;


int caffeine;
int lab;
int lecture;
int study;
int tutorial;

Resource::Resource(int caffeine, int lab,  int lecture, int study, int tutorial): caffeine{caffeine}, lab{lab}, 
                                                            lecture{lecture}, study{study}, tutorial{tutorial} {}
Resource::Resource(std::string resource) {
    if (resource == "CAFFEINE") {
        caffeine = 1;
    } else if (resource == "LAB") {
        lab = 1
    } else if (resource == "LAB") {
        lecture = 1;
    } else if (resource == "STUDY") {
        study = 1;
    } else if (resource == "TUTORIAL") {
        tutorial = 1;
    }
}


Resource operator+(Resource &other);
Resource operator-(Resource &other);

Resource& operator-=(Resource &other);
Resource& operator+=(Resource &other);
auto operator<=>(const Resource &other) const = default;

int count();
