export module Student;

import <vector>;
import <string>;
import <sstream>;
import <iostream;

import Board;
import ISubject;
import Resource;
import IObserver

export class Student : public IObserver {
    std::string name;
    Resource held_resources;
    std::vector<int> criteria;
    std::vector<int> goals;
    public:
        explicit Student(const std::string colour);
        std::string get_name() override;
        bool can_afford(const Resource & query) const;

        void buy_criteria(int id, bool set_up = false);
        void buy_goal(int id, bool set_up = false);
        void upgrade_criteria(int id);


        // TODO: what is goosed?
        // void goosed();

        // main method to modify resources, inherited from IObserver
        void resource_notify(Resource rchange) override;

        // save logic
        std::string get_save_string() const;
        void read_save_string(std::string save_data);

        void print_status();
};
