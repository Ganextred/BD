//
// Created by User on 14.02.2023.
//

#ifndef BD_APARTMENT_H
#define BD_APARTMENT_H


#include "BaseEntity.h"
#include <sstream>
#include <iomanip>
#include<fstream>
#include <iostream>
class Apartment : public BaseEntity
{
public:
    int beds;
    int clazz;
    int price;
    static string getName() { return "Apartment"; };
    void serialize(int i);
    static Apartment deserialize(int i);

    Apartment(){
        id = -2;
        clazz = -2;
        price = -2;
        beds = -2;
    }

    string toString(){
        ostringstream ss;
        ss << "Apartment{" << std::endl;
        ss << "  beds: " << beds << std::endl;
        ss << "  clazz: " << clazz << std::endl;
        ss << "  price: " << price << std::endl;
        ss << "  id: " << id << std::endl;
        ss << "}";
        return ss.str();
    }

private:
    static int getStoreSize(){
        return sizeof(id)*4;
    }

};


#endif //BD_APARTMENT_H
