export module Student;

import <iostream>;
import <vector>;
import <string>;

import Resource;
import IObserver;

export class Student : public IObserver {
    std::string colour;
    Resource held_resources;
    std::vector<int> criteria;
    std::vector<int> goals;
    public:
        explicit Student(const std::string colour);
        std::string get_colour() const;
        
        void buy_criteria(int id);
        void buy_goal(int id);
        void upgrade_criteria(int id);
        bool can_afford(Resource query);

        // TODO: what is goosed?
        // void goosed();

        // main method to modify resources, inherited from IObserver
        void resource_notify(Resource rchange) override;

        // save logic
        std::string get_save_string() const;
        void read_save_string(std::string save_data);
};
