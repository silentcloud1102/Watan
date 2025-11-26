export module Student;

import <iostream>;
import <vector>;
import <string>;

import Resource;
import IObserver;

export class Student : public IObserver {
    std::string colour;
    Resource held_resources;
    std::vector<IObserver *> criteria;
    public:
        explicit Student(const std::string colour);
        std::string get_colour() const;
        std::string get_save() const;
        std::string read_save(std::string save_data);
        void buy_criteria(int id);
        void buy_goal(int id);
        void upgrade_criteria(int id);
        bool can_afford(Resource query);

        // TODO: what is goosed?
        // void goosed();

        // main method to modify resources
        void resource_notify(Resource rchange) override;
};
