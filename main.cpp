#include <iostream>

#include "Classifier.h"
#include "Dataframe.h"

int main() {
    Dataframe df = Dataframe();
    df.load_from_file("./data/data.csv");
    df.fix_data_types();

    df.shuffle_dataframe();
    //df.print_dataframe();
    Classifier cls = Classifier(df);
    cls.evaluate();
}
