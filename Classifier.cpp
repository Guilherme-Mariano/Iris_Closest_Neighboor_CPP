#include "Classifier.h"

#include <complex>

Classifier::Classifier(Dataframe df) {
    dataframe = df;
}

vector<string> Classifier::get_common_columns(Line l1, Line l2) {
    vector<string> common_cols;
    if(l1.elements.size() > l2.elements.size()) {
        for(int i = 0; i < l1.elements.size(); i++) {
            for(int j = 0; j < l2.elements.size(); j++) {
                if(l1.elements.at(i).label == l2.elements.at(j).label) {
                    common_cols.insert(common_cols.end(), l1.elements.at(i).label);
                }
            }
        }
        return common_cols;
    }

    for(int i = 0; i < l2.elements.size(); i++) {
        for(int j = 0; j < l1.elements.size(); j++) {
            if(l2.elements.at(i).label == l1.elements.at(j).label) {
                common_cols.insert(common_cols.end(), l2.elements.at(i).label);
            }
        }
    }
    return common_cols;
}


void Classifier::populate_test_set(int test_size) {
    for(int i = dataframe.dataframe.size() - 1; i >= dataframe.dataframe.size() - test_size; i--) {
        test_set.insert(test_set.end(), dataframe.dataframe.at(i));
    }
    for(int i = 0; i < test_size; i++) {
        dataframe.dataframe.pop_back();
    }
}

void Classifier::print_test_set() {
    for(int i = 0; i < test_set.size(); i++) {
        dataframe.print_line(test_set.at(i));
    }
}

double Classifier::get_distance_betw_elements(double d1, double d2) {
    double ans = d1 - d2;
    ans *= ans;
    return ans;
}

double Classifier::get_distance(Line l1, Line l2) {
    vector<string> common_cols = get_common_columns(l1, l2);
    double res = 0;
    for(int i = 0; i < common_cols.size(); i++) {
        res += get_distance_betw_elements(l1.elements.at(i).number, l2.elements.at(i).number);
    }
    res = sqrt(res);
    return res;
}

Line Classifier::get_closest_neighboor(Line test_line) {
    Line cn;
    double dist = 100000.5;
    for(int i = 0; i < dataframe.dataframe.size(); i++) {
        double distance = get_distance(dataframe.dataframe.at(i), test_line);
        if(distance < dist) {
            dist = distance;
            cn = dataframe.dataframe.at(i);
        }
    }

    cout << "\n" << "Distance: " << dist << "\n";

    return cn;
}


void Classifier::evaluate() {
    populate_test_set(5);
    print_test_set();
    Line test_line = test_set.at(2);
    Line cn = get_closest_neighboor(test_line);
    dataframe.print_line(test_line);
    dataframe.print_line(cn);
}



