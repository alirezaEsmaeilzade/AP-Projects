#ifndef __MANUAL_WEIGHT_H__
#define __MANUAL_WEIGHT_H__
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "error.hpp"
#define INITIALIZE_WIGHT 1
#define SETPRECISION_NUMBER 2
typedef std::pair <std::string, double> weight_element;
typedef std::vector< std::pair <std::string, double> > manual_weights_elements;
class Manual_weights{
    public:
        Manual_weights();
        void set_rating_weights(double location_w, double cleanliness_w, double staff_w, double facilities_w, double value_for_money_w);
        void set_estimulat_weight(std::vector<double> est_weight);
        void set_activity_condition(std::string acctivity_conditoin);
        void print();
        void print_estimated();
        bool activity_condition();
        bool check_input(double input);
        manual_weights_elements get_elements();
        std::vector<double> get_double_elements();
        private:
            double location_w;
            double cleanliness_w;
            double staff_w;
            double facilities_w;
            double value_for_money_w;
            bool activity;
            manual_weights_elements elements;
};
#endif