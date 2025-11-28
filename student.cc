export module Student;

import <iostream>;
import <vector>;
import <string>;
import <sstream>;

import Resource;
import IObserver;
import ISubject;
import Board;

export class Student : public IObserver {
    std::string name;
    Resource held_resources;
    std::vector<int> criteria;
    std::vector<int> goals;
    int criteria_count;
    bool isfair = true;
    public:
        explicit Student(const std::string colour);
        std::string get_name() override;
        bool can_afford(const Resource & query) const;

        void buy_criteria(int id, bool set_up = false);
        void buy_goal(int id, bool set_up = false);
        void upgrade_criteria(int id);

        void trade(Student * colour, std::string give_r, std::string take_r);

        // TODO: what is goosed?
        // void goosed();

        // main method to modify resources, inherited from IObserver
        void resource_notify(Resource rchange) override;

        // save logic
        std::string get_save_string() const;
        void read_save_string(std::string save_data);

        void print_status();
};
