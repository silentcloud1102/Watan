export module Resource;

import <string>;

class Resource {
    int caffeine;
    int lab;
    int lecture;
    int study;
    int tutorial;

    Resource(int caffeine = 0, int lab = 0,  int lecture = 0, int study = 0, int tutorial = 0);
    
    Resource operator+(Resource &other);
    Resource operator-(Resource &other);

    Resource& operator-=(Resource &other);
    Resource& operator+=(Resource &other);
    auto operator<=>(const Resource &other) const = default;

    int count();
};