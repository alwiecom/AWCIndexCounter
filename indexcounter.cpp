#include "indexcounter.h"

Indexcounter::Indexcounter() {
    std::cout << "Create Indexcounter: " << "Default" << std::endl;
    items_count = 0;
    status = "Default";
}

Indexcounter::Indexcounter(std::string sparam) {
    std::cout << "Create Indexcounter: " << sparam << std::endl;
    items_count = 0;
    status = sparam;
}

Indexcounter::~Indexcounter() {
    std::cout << "Destruct Indexcounter: " << status << std::endl;
}

void Indexcounter::add_data(std::string item, std::string key, std::string data) {
    if (debug) std::cout << "\n" << items_count <<": add_data(" << item << "," << key << "," << data << ")" << std::endl;
    search_cnt = 0;
    item_field = item;
    item_key = key;
    item_data = data;
    if (check_vector())
        items_count++;
}

void Indexcounter::create_index_field(std::string name, std::string type) {
    index_field = name;
}

void Indexcounter::create_data_field(std::string name, std::string type) {
    data_field = name;
}

int Indexcounter::get_cnt_read() {
    return items_count;
}

int Indexcounter::get_cnt_unique() {
    return data_items.size();
}

int Indexcounter::get_cnt_search() {
    return search_cnt;
}

int Indexcounter::get_item_count(int index) {
    return data_items.at(index).count;
}

std::string Indexcounter::get_item_data(int index) {
//    std::string s1 = "{" + " \" id \" :\" " + data_items.at(index).id + "\"" + ","  + "}";
//    std::string s1 = "bp".c_str() + "id".c_str();
    std::stringstream sstream;
    sstream << "{" << "\"" << "id" << "\"" << ":" << "\"" << data_items.at(index).id << "\"";
    sstream << "," << "\"" << "field" << "\"" << ":" << "\"" << data_items.at(index).field << "\"";
    sstream << "," << "\"" << "key_data" << "\"" << ":" << "\"" << data_items.at(index).key_data << "\"";
    sstream << "," << "\"" << "data" << "\"" << ":" << "\"" << data_items.at(index).data << "\"";
    sstream << "," << "\"" << "index" << "\"" << ":" << "\"" << data_items.at(index).index << "\"";
    sstream << "," << "\"" << "count" << "\"" << ":" << "\"" << data_items.at(index).count << "\"";
    sstream << "}";
    std::string s1 = sstream.str();

    return s1;
}

std::string Indexcounter::get_test_item_data(int index) {
    return data_items.at(index).data;
}

std::string Indexcounter::get_test_item_key_data(int index) {
    return data_items.at(index).key_data;
}

void Indexcounter::setDebug(bool dbg) {
    debug = dbg;
}

//Private functions
bool Indexcounter::check_vector() {
    if (data_items.size() == 0) {
        add_data_to_vector(data_items.size());
    } else {
        int index = find_vector(0, data_items.size(), 1);
        if (index < 0)
            add_data_to_vector(0);
        if (index > 0)
            add_data_to_vector(index);
        if (index == 0)
            return false;
        //index == 0 Color update count++
    }
    return true;
}

int Indexcounter::find_vector(int from, int to, int direction) {
    int pos = 0;
    search_cnt++;
    if (data_items.at(from).key_data == item_key) {
        data_items.at(from).count++;
        return 0;
    }
    int sp = (from + to) / 2;
    if (from == sp) {
      if (debug) std::cout << "We can add: " << from << "," << to << "," << direction << "[" << item_key << "vs" << data_items.at(sp).key_data << "]" << std::endl;
        //Not found insert at to
        if (item_key < data_items.at(sp).key_data) return -1;
        return to;
    }
    if (item_key == data_items.at(sp).key_data) {
        //Found update and stop
        data_items.at(sp).count++;
        return 0;
    }
    if (item_key > data_items.at(sp).key_data) {
        //Find again forward
        pos = find_vector(sp, to, 1);
    }
    if (item_key < data_items.at(sp).key_data) {
        //Find again back
        pos = find_vector(from, sp, 0);
    }
    return pos;
}

void Indexcounter::add_data_to_vector(int index) {
    if (debug) std::cout << "! add_data_to_vector(" << index << ")" << std::endl;
    DataItems *di = new DataItems;
    di->field = item_field;
    di->key_data  = item_key;
    di->data  = item_data;
    di->count = 1;
    di->id = items_count;
    data_items.insert(data_items.begin() + index,*di);
    //std::string serialized = di->JSONSerialize();
}

void Indexcounter::list_colors() {
    if (!debug) return;
    for (int i=0; i<data_items.size(); i++) {
        std::cout << data_items.at(i).key_data << " " << data_items.at(i).data << " - " << data_items.at(i).count << std::endl;
    }
}
