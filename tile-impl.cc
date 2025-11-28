module Tile;

import <vector>;
import <string>;

import ISubject;
import Resource;




Tile::Tile(std::string res, int dc, int num) : resource_type(res), dice(dc), tilenum(num) {}

// Printing methods: normalize switch for easy use outside of Board << operator
std::string Tile::get_tilenum(bool normalize) const {

    // if normalize (default):
    // we want tilenum to take the same amount of space regardless of value (1 or 2 digits)
    // if single-digit, add a space in front as a buffer
    if (normalize && tilenum < 10) {
        return " " + std::to_string(tilenum);
    }
    return std::to_string(tilenum);
}

std::string Tile::get_resource(bool normalize) const {
    std::string result = resource_type;

    if(!normalize){
        return result;
    }
    // if normalize (default):
    // we want all resource strings to be of the same length, so we add the difference to end as empty spaces
    for(int i = 0; i < (11 - resource_type.length()); ++i) {
        result += " ";
    }
    return result;
}

std::string Tile::get_dice(bool normalize) const {
    // again, we want the result to be two characters long, normalize by adding space to front
    if (normalize && dice < 10) {
        return " " + std::to_string(dice);
    }
    return std::to_string(dice);
}

std::vector<std::string> Tile::adjacent_criteria_ids() const {
    std::vector<std::string> ids;
    for(auto it : course_criteria){
        ids.emplace_back(it->get_num());
    }
    return ids;
}

// Set-up methods:
void Tile::add_criteria(Criteria *v) {
    course_criteria.emplace_back(v);
}

void Tile::add_goal(Goal *e) {
    goals.emplace_back(e);
}

// Resource distribution via Criteria (Subject)
void Tile::distribute_resources() const {
      for (int i = 0; i < 6; ++i) {
        course_criteria[i]->new_resource(resource_type);
      }
}