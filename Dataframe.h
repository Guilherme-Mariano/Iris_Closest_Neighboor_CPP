#ifndef DATAFRAME_H
#define DATAFRAME_H
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

typedef struct Element {
    string label;
    bool numeric = false;
    string object;
    double number;
}Element;

typedef struct Line {
    int index;
    vector<Element> elements;
}Line;

class Dataframe {
public:
    vector<Line> dataframe;
    vector<string> labels;
    int load_from_file(string filepath);
    void print_dataframe(vector<Line> df);
    void print_dataframe();
    void fix_data_types();
    void shuffle_dataframe();
    void remove_column(string col_name);
    vector<Line> remove_column(vector<Line> df,string col_name);
    int get_column_index(string col_name);
    void print_line(Line line);

private:
    void extract_labels(string line);
    void populate_dataframe(string line, int line_index);
    vector<string> get_numeric_columns();
    bool check_numeric_element(string obj);
    Line correct_line(Line line, string col_remove);
};



#endif //DATAFRAME_H
