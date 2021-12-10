#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>

#define COURSE_WITHOUT_PRE 0
#define LIMIT_MARK_OF_FAULE 10
#define MAX_UNIT_FOR_A_MARK 24
#define MAX_UNIT_FOR_LESS_THAN_A_MARK 20
#define A_MARK 17

using namespace std;


struct Clock_time{
    int hour;
    int minut;
};
typedef Clock_time clock_time;
struct Date_and_time{
    string day;
    clock_time begin_class_time;
    clock_time end_class_time;
};
typedef Date_and_time date_and_time;
struct Schedule{
    vector <date_and_time> sessions;
};
typedef Schedule schudule;
struct Prerequisites{
    vector<int> pre_id;
};
typedef Prerequisites prerequisites;
struct Course{
    int id;
    string name;
    int units;
    schudule sch;
    prerequisites pre;
};
typedef Course course;
struct Grades {
    int id;
    float grade;
};
typedef Grades grades;
void split_string(vector<string> &splited_string_part, string unsplit, char separator){
    stringstream ss(unsplit);
    while(ss.good()){
        string substr;
        getline(ss, substr, separator);
        if(substr[0] == ' ')
            substr.erase(substr.begin());
        splited_string_part.push_back(substr);
    }
}
clock_time make_clock_for_date(string input_string){
    clock_time convert_string_to_clock;
    vector<string> part_of_split_string;
    split_string(part_of_split_string, input_string, ':');
    convert_string_to_clock.hour = stoi(part_of_split_string[0]);
    convert_string_to_clock.minut = stoi(part_of_split_string[1]);
    return convert_string_to_clock;
}
date_and_time make_date_and_time(string input_string){
    date_and_time convert_string_to_date;
    vector<string> part_of_split_sring;
    split_string(part_of_split_sring, input_string, '-');
    convert_string_to_date.day = part_of_split_sring[0];
    convert_string_to_date.begin_class_time = make_clock_for_date(part_of_split_sring[1]);
    convert_string_to_date.end_class_time = make_clock_for_date(part_of_split_sring[2]);
    return convert_string_to_date;
}
schudule make_shudule_structur(string input_string){
    schudule convert;
    vector<string> date;
    split_string(date, input_string, '/');
    for(int i = 0; i < date.size(); i++){
        convert.sessions.push_back(make_date_and_time(date[i])); 
    }
    return convert;
}
prerequisites make_prerequisites_structur(string input_string){
    prerequisites convert;
    vector<string> id;
    split_string(id, input_string, '-');
    for(int i = 0; i < id.size(); i++){
        int tabdil = stoi(id[i]);
        convert.pre_id.push_back(tabdil);
    }
    return convert;
}
course make_lesson(vector<string> splited_part){
    course convert;
    convert.id = stoi(splited_part[0]);
    convert.name = splited_part[1];
    convert.units = stoi(splited_part[2]);
    convert.sch = make_shudule_structur(splited_part[3]);
    convert.pre = make_prerequisites_structur(splited_part[4]);
    return convert;
}
grades make_grades_structur(vector<string> splited_part){
    grades convert;
    convert.id = stoi(splited_part[0]);
    convert.grade = stof(splited_part[1]);
    return convert;
}
int read_cours_info(vector <course> &lessons, string file_name){
    string head_of_table;
    int inp;
    ifstream Course_file;
    Course_file.open(file_name);
    if(!Course_file.is_open()){
        cout<<"Error opening file, check input file exit or no"<<endl;
        return 0;
    }
    getline(Course_file,head_of_table);
    while(!Course_file.eof()){
        vector <string> splited_part;
        string input;
        getline(Course_file,input);
        if(!input.empty()){
        split_string(splited_part, input, ',');
        lessons.push_back(make_lesson(splited_part));
        }
    }
    return 1;
}
int read_grades(vector<grades> &grades_of_all_lessons, string file_name){
    string head_of_table;
    ifstream grades_file;
    grades_file.open(file_name);
    if(!grades_file.is_open()){
        cout<<"Error opening file, check input file exit or no"<<endl;
        return 0;
    }
    grades_file>>head_of_table;
    while(!grades_file.eof()){
        string input;
        vector<string> go_to_split;
        grades_file>>input;
        if(!input.empty()){
            split_string(go_to_split, input, ',');
            grades_of_all_lessons.push_back(make_grades_structur(go_to_split));
        }
    }
    return 1;
}
bool is_passed_or_failed(float mark){
    if(mark < LIMIT_MARK_OF_FAULE)
        return false;
    else
        return true;
}
void returned_passed_lessons(vector <grades> grades_of_all_lessons ,vector<int> &passed_course){
    for(int i = 0; i < grades_of_all_lessons.size(); i++){
        if(is_passed_or_failed(grades_of_all_lessons[i].grade))
            passed_course.push_back(grades_of_all_lessons[i].id);
    }
}
bool is_passed_previos_term_or_no(int course_id, vector<int> passed_course){
    for(int i = 0; i < passed_course.size(); i++){
        if(course_id == passed_course[i])
            return true;
    }
    return false;
}
bool is_passed_lessons_prerequisites( prerequisites lesson, vector <int>passed_course){
    for(int i = 0; i < lesson.pre_id.size(); i++){
        if(lesson.pre_id[i] != COURSE_WITHOUT_PRE){
            if(!is_passed_previos_term_or_no(lesson.pre_id[i], passed_course))
                return false;
        }
    }
    return true;
}
void find_allowed_course_for_current_term(vector<course> lessons, vector<grades> grades_of_all_lessons, vector <course> &allowed_course){
    vector<int> passed_course;
    returned_passed_lessons(grades_of_all_lessons, passed_course);
    for(int i = 0; i < lessons.size(); i++){
        if(!is_passed_previos_term_or_no(lessons[i].id, passed_course)){
            if(is_passed_lessons_prerequisites(lessons[i].pre, passed_course))
                allowed_course.push_back(lessons[i]);
        }
    }
}
void sort_course_by_lessons_name(vector<course> allowed_course, vector<string> &for_allphebetically_sort){
    for(int i = 0; i < allowed_course.size(); i++)
        for_allphebetically_sort.push_back(allowed_course[i].name);
    sort(for_allphebetically_sort.begin(), for_allphebetically_sort.end());
}
void find_course_id_by_name(vector<course> &allowed_course, vector<string> for_allphebetically_sort){
    vector<course> sorted_allowed_course;
    for(int i = 0; i < for_allphebetically_sort.size(); i++){
        for(int j = 0; j < allowed_course.size(); j++){
            if(for_allphebetically_sort[i] == allowed_course[j].name){
                sorted_allowed_course.push_back(allowed_course[j]);
                break;
            }
        }
    }
    allowed_course = sorted_allowed_course;
}
void print_sorted_course(vector<course> sorted_allowed_course){
    for(int i = 0; i < sorted_allowed_course.size(); i++)
        cout<<sorted_allowed_course[i].id<<endl;
}
void sort_course(vector<course> &allowed_course){
    vector <string> for_allphebetically_sort;
    sort_course_by_lessons_name(allowed_course, for_allphebetically_sort);
    find_course_id_by_name(allowed_course, for_allphebetically_sort);
}
float average(vector<float> inputs){
    return accumulate(inputs.begin(), inputs.end(), 0.0)/inputs.size();
}
void make_array_to_average(vector<grades> grades_all_lessons, vector<float> &grades_of_each_id){
    for(int i = 0; i < grades_all_lessons.size(); i++)
        grades_of_each_id.push_back(grades_all_lessons[i].grade); 
}
int return_max_units_can_take(vector<grades> grades_all_lessons){
    vector<float> grades_of_each_id;
    make_array_to_average(grades_all_lessons, grades_of_each_id);
    float average_of_grades = average(grades_of_each_id);
    if(average_of_grades >= A_MARK)
        return MAX_UNIT_FOR_A_MARK;
    else
        return MAX_UNIT_FOR_LESS_THAN_A_MARK;
}
int maximum_unit_in_course(vector<course> allowed_course){
    int max_unit = allowed_course[0].units;
    for(int i = 0; i < allowed_course.size(); i++){
        if(allowed_course[i].units > max_unit)
            max_unit = allowed_course[i].units;
    }
    return max_unit;
}
void sort_allowed_course_by_unit(vector<course> &allowed_course){
    vector <course> sorted_allowed_course_by_unit;
    int max_course_unit = maximum_unit_in_course(allowed_course);
    for(int i = max_course_unit; i >= 0; i--){
        for(int j = 0; j < allowed_course.size(); j++){
            if(allowed_course[j].units == i)
                sorted_allowed_course_by_unit.push_back(allowed_course[j]);
        }
    }
    allowed_course = sorted_allowed_course_by_unit;
}
bool is_unit_limit_observe(int suggest_unit_sum_check, int unchecked_course_unit, int max_unit){
    if((suggest_unit_sum_check + unchecked_course_unit) > max_unit)
        return false;
    return true;
}

bool check_time_interference(date_and_time lesson[]){
    if(lesson[0].day == lesson[1].day){
        vector <int> data_of_classes_time;
        if(lesson[0].begin_class_time.hour > lesson[1].begin_class_time.hour){
            swap(lesson[0], lesson[1]);
        }
        for(int i = 0; i < 2; i++){
            data_of_classes_time.push_back(lesson[i].begin_class_time.hour);
            data_of_classes_time.push_back(lesson[i].end_class_time.hour);
        }
        vector<int> sorted_data = data_of_classes_time; 
        sort(data_of_classes_time.begin(), data_of_classes_time.end());
        if(data_of_classes_time == sorted_data){
            if(lesson[0].end_class_time.hour == lesson[1].begin_class_time.hour){
                if(lesson[0].end_class_time.minut > lesson[1].begin_class_time.minut)
                    return true;
            }
        }
        else
            return true;
    }
    return false;
}
bool check_all_time(vector<course> suggest_course, course unchecked_course){
    for(int i = 0; i < unchecked_course.sch.sessions.size(); i++){
        for(int j = 0; j < suggest_course.size(); j++){
            for(int k = 0; k < suggest_course[j].sch.sessions.size(); k++){
                date_and_time lesson[2] = {unchecked_course.sch.sessions[i], suggest_course[j].sch.sessions[k]};
                if(check_time_interference(lesson)){
                    return false;
                }
            }
        }
    }
    return true;
}
void suggest_term_programm(vector<course> &allowed_course, vector<course> &suggest_course,vector<grades> grades_of_all_lessons){
    int max_unit_can_take = return_max_units_can_take(grades_of_all_lessons);
    sort_allowed_course_by_unit(allowed_course);
    int suggest_unit_sum = allowed_course[0].units;
    suggest_course.push_back(allowed_course[0]);
    for(int i = 1; i < allowed_course.size(); i++){
        if(is_unit_limit_observe(suggest_unit_sum,allowed_course[i].units,max_unit_can_take)){
            if(check_all_time(suggest_course, allowed_course[i])){
                suggest_unit_sum += allowed_course[i].units;
                suggest_course.push_back(allowed_course[i]);
            }
        }
    }
}
void print_suggest_programm(vector<course> suggest_course){
    for(int i = 0; i < suggest_course.size(); i++)
        cout<<suggest_course[i].id<<endl;
}
int main(int argc, char *argv[]){
    vector <course> lessons;
    vector <grades> grades_of_all_lessons;
    vector<course> allowed_course;
    vector<course> suggest_course;
    if(!read_cours_info(lessons, argv[1]))
        return 1;
    if(!read_grades(grades_of_all_lessons, argv[2]))
        return 1;
    find_allowed_course_for_current_term(lessons, grades_of_all_lessons, allowed_course);
    sort_course(allowed_course);
    suggest_term_programm(allowed_course, suggest_course, grades_of_all_lessons);
    sort_course(suggest_course);
    print_suggest_programm(suggest_course);
    return 0;
}