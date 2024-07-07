#include "Dataframe.h"

#include <random>

void Dataframe::extract_labels(string line) {
    string str = "";
    for(int i = 0; i < line.length() + 1; i++) {
        if(line[i] == '\0') {
            labels.insert(labels.end(), str);
            break;
        }
        if(line[i] == ',') {
            labels.insert(labels.end(), str);
            str = "";
            continue;
        }
        str += line[i];
    }
}

void Dataframe::populate_dataframe(string line, int line_index) {
    string str = "";
    int label_index = 0;
    Line df_line;
    df_line.index = line_index;
    for(int i = 0; i < line.length() + 1; i++) {
        if(line[i] == '\0') {
            Element elem;
            elem.label = labels.at(label_index);
            elem.object = str;
            df_line.elements.insert(df_line.elements.end(), elem);
        }
        if(line[i] == ',') {
            Element elem;
            elem.label = labels.at(label_index);
            elem.object = str;
            df_line.elements.insert(df_line.elements.end(), elem);
            label_index++;
            str = "";
            continue;
        }
        str += line[i];
    }

    dataframe.insert(dataframe.end(), df_line);
}

void Dataframe::print_line(Line line) {
    //cout << "Line index: " << line.index;
    for(int i = 0; i < line.elements.size(); i++) {
        if(line.elements.at(i).numeric) {
            cout << " ||" << line.elements.at(i).label << " " << line.elements.at(i).number << " || ";
        }else {
            cout << " ||" << line.elements.at(i).label << " " << line.elements.at(i).object << " || ";
        }
    }
    cout << "\n";
}


void Dataframe::print_dataframe(vector<Line> df) {
    for(int i = 0 ; i < df.size(); i++) {
        print_line(df.at(i));
    }
}

void Dataframe::print_dataframe() {
    for(int i = 0 ; i < dataframe.size(); i++) {
        print_line(dataframe.at(i));
    }
}

bool Dataframe::check_numeric_element(string obj) {
    for(int i = 0; i < obj.length(); i++) {
        if(!(isdigit(obj[i])) && obj[i] != '.' && obj[i] !=' ') {
            return false;
        }
    }
    return true;
}

Line Dataframe::correct_line(Line line, string col_remove) {
    Line new_line;
    new_line.index = line.index;
    for(int i = 0; i < line.elements.size(); i++) {
        if(line.elements.at(i).label == col_remove) continue;
        new_line.elements.insert(new_line.elements.end(), line.elements.at(i));
    }
    return new_line;
}


void Dataframe::remove_column(string col_name) {
    // Criar novo dataframe sem a coluna
    vector<Line> new_df;
    for(int i = 0; i < dataframe.size(); i++) {
        Line nl = correct_line(dataframe.at(i), col_name);
        new_df.insert(new_df.end(), nl);
    }
    dataframe = new_df;
}

vector<Line> Dataframe::remove_column(vector<Line> df,string col_name) {
    // Criar novo dataframe sem a coluna
    vector<Line> new_df;
    for(int i = 0; i < df.size(); i++) {
        Line nl = correct_line(df.at(i), col_name);
        new_df.insert(new_df.end(), nl);
    }
    return new_df;
}


vector<string> Dataframe::get_numeric_columns() {
    vector<string> numeric;
    bool flag = true;
    for(int i = 1; i < labels.size(); i++) {
        string label = labels.at(i);
        for(int j = 0; j < dataframe.size(); j++) {
            if(!(check_numeric_element(dataframe.at(j).elements.at(i).object))) {
                flag = false;
                break;
            }
        }
        if(flag) numeric.insert(numeric.end(), label);
    }

    return numeric;
}

int Dataframe::get_column_index(string col_name) {
    for(int i = 0; i < labels.size(); i++) {
        if(labels.at(i) == col_name) return i;
    }
    return -1;
}


void Dataframe::fix_data_types() {
    vector<string> numeric = get_numeric_columns();

    for(int i = 0; i < numeric.size(); i++) {
        string label = numeric.at(i);
        int col_index = get_column_index(label);
        for(int j = 0; j < dataframe.size(); j++) {
            dataframe.at(j).elements.at(col_index).numeric = true;
            string numeric_str = dataframe.at(j).elements.at(col_index).object;
            if(numeric_str == "") numeric_str = "0";
            dataframe.at(j).elements.at(col_index).number = stod(numeric_str);
            dataframe.at(j).elements.at(col_index).object = "";
        }
    }
}

void Dataframe::shuffle_dataframe() {
    auto rd = random_device {};
    auto rng = default_random_engine { rd() };
    shuffle(begin(dataframe), end(dataframe), rng);
}


int Dataframe::load_from_file(string filepath) {
    ifstream inputFile(filepath);
    if(!inputFile) {
        cerr << "Error opening file";
        return -1;
    }

    int i = 0;
    string line = "";
    while(getline(inputFile, line)) {
        if(i == 0) {
            extract_labels(line);
        }else {
            populate_dataframe(line, i - 1);
        }
        i++;
    }
    inputFile.close();

    return 0;
}

