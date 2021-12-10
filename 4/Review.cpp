#include "Review.h"
void Review::print(){
    std::cout << "id: " << id;
    std::cout << " Rating: " << rating << " Likes: " << number_of_like << " Date: " << date << std::endl;
}
