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
    Board *board;
    Resource held_resources;
    std::vector<int> criteria;
    std::vector<int> goals;
    bool isfair = true;
    static std::vector<int> all_adjacent_goals;
    static std::vector<int> all_adjacent_criteria;
    public:
        static void add_adjacent_criteria(int criteria);
        static void add_adjacent_goal(int goal);
        Student(const std::string & colour, Board * board);
        std::string get_name() override;
        
        // win condition
        int get_criteria_count() const;

        // geese methods
        std::vector<int> resource_vector() const;
        Resource get_resource() const;
        int resource_count() const;

        // boolean check
        bool can_afford(const Resource & query) const;

        // student actions
        void buy_criteria(int id, bool set_up = false);
        void buy_goal(int id, bool set_up = false);
        void upgrade_criteria(int id);

        // method for geese (stealing and taxes when Resource count > 10)
        void goosed(Resource rchange);

        void trade(Student * colour, std::string give_r, std::string take_r);

        // main method to modify resources, inherited from IObserver
        void resource_notify(Resource rchange) override;

        // save logic
        std::string get_save_string() const;
        void read_save_string(std::string save_data);

        bool operator==(std::string other) const;
        
        // output
        std::string completions() const;
        friend std::ostream &operator<<(std::ostream& os, Student &student);
};
