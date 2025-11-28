export module Resource;

import <string>;
import <iostream>;
import <vector>;

export class Resource {
    int caffeine = 0;
    int lab = 0;
    int lecture = 0;
    int study = 0;
    int tutorial = 0;
    public:
        Resource() = default;
        explicit Resource(int caffeine, int lab,  int lecture, int study, int tutorial);

        explicit Resource(std::string resource, int amount = 1);
        
        Resource operator+(const Resource &other) const;
        Resource operator-(const Resource &other) const;

        Resource& operator-=(const Resource &other);
        Resource& operator+=(const Resource &other);
        bool operator<=(const Resource &other) const;
        bool operator>=(const Resource &other) const;
        int count() const;
        
        // output helper methods
        std::vector<int> to_vector() const;
        std::string print_output(int type, int amount) const;

        // save method
        std::string get_save_string() const;

        friend std::ostream &operator<<(std::ostream &os, const Resource & resource);
};