//Just for testing
#ifndef INDEXCOUNTER_H
#define INDEXCOUNTER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
//#include <ctime>
//#include <ratio>
//#include <chrono>

class DataItems {
    public:
        int id;
        std::string field;
        std::string key_data;
        std::string data;
        std::string index;
        int count;
};

class Indexcounter {

    public:
        Indexcounter();
        Indexcounter(std::string sparam);
        ~Indexcounter();

        void create_index_field(std::string name, std::string type);
        void create_data_field(std::string name, std::string type);
        void add_data(std::string item, std::string key , std::string data);
        int get_cnt_read();
        int get_cnt_unique();
        int get_cnt_search();
        int get_item_count(int index);
        std::string get_item_data(int index);
        void setDebug(bool debug);
        void list_colors();
        std::string get_test_item_data(int index);
        std::string get_test_item_key_data(int index);
        bool debug = false;

    protected:

    private:
        void add_data_to_vector(int index);
        bool check_vector();
        int find_vector(int from, int to, int direction);

        std::vector<DataItems> data_items;
        std::vector<DataItems> data_index;
        int search_cnt;
        bool index = false;
        std::string status;
        std::string index_field;
        std::string data_field;
        std::string item_field;
        std::string item_key;
        std::string item_data;

        int items_count;
};

#endif

