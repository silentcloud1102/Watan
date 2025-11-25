module Criteria;

import <string>;
import <vector>;
import ISubject;
using namespace std;



string Criteria::getnum() {
    if (owner != ' ') {
        vector<char> levels = {'A','M','E'};
        return owner + levels[upgradeLevel - 1];
    }

    if (location < 10) {
      return " " + to_string(location);
    }
    return to_string(location);
}

void Criteria::upgrade() {
    if ()
}