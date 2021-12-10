#ifndef __JSON_BUILDER_H__
#define __JSON_BUILDER_H__
#include "Data_without_name.hpp"
#include "Object.hpp"
#include "Array.hpp"
#include "Container.hpp"
#include "Data_with_name.hpp"
#include "Element.hpp"
#include "error.hpp"
#include <iostream>

#define ID_ERROR "invalid id."
#define KEY_ERROR "Duplicate key."
#define TYPE_ERROR "Undefined type."
class JsonBuilder{
    public:
        JsonBuilder();
        ~JsonBuilder();
        void addStringToObject(int parentId, std::string key, std::string value);
        void addIntegerToObject(int parentId, std::string key, int value);
        int addContainerToObject(int parentId, std::string key, std::string type);
        void addStringToArray(int parentId, std::string value);
        void addIntegerToArray(int parentId, int value);
        int addContainerToArray(int parentId, std::string type);
        void print(int id);
    private:
        void make_container_for_object(Container* object, std::string key, std::string type);
        Object_without_key* mother_object;
        int number_of_container;
};
#endif