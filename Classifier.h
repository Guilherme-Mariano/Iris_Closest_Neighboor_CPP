#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include "Dataframe.h"


class Classifier {
public:
    Classifier(Dataframe df);
    Dataframe dataframe;
    vector<Line> test_set;
    void evaluate();
    void print_test_set();
private:
    void populate_test_set(int test_size);
    vector<string> get_common_columns(Line l1, Line l2);
    double get_distance(Line l1, Line l2);
    double get_distance_betw_elements(double d1, double d2);
    Line get_closest_neighboor(Line test_line);
};



#endif //CLASSIFIER_H
