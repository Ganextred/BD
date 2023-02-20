//
// Created by User on 14.02.2023.
//

#ifndef BD_APARTMENTSTATUS_H
#define BD_APARTMENTSTATUS_H
#include "BaseEntity.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include<fstream>
#include <iostream>

class ApartmentStatus : public BaseEntity{
public:
    std::chrono::time_point<std::chrono::system_clock> arrival_day;
    std::chrono::time_point<std::chrono::system_clock> end_day;
    std::chrono::time_point<std::chrono::system_clock> pay_time_limit;
    int apartment_id;
    int user_id;

    ApartmentStatus(){
        arrival_day = std::chrono::system_clock::now();
        end_day = arrival_day + std::chrono::hours(24);
        pay_time_limit = arrival_day + std::chrono::hours(12);
        id = -2;
        apartment_id = -2;
        user_id = -2;
    }

    static string getName(){
        return "ApartmentStatus";
    }

    void serialize(int i);
    static ApartmentStatus deserialize(int i);

    std::string toString() const {
        std::ostringstream ss;
        ss << "ApartmentStatus{" << std::endl;
        ss << "  arrival_day: " << timeToString(arrival_day) << std::endl;
        ss << "  end_day: " << timeToString(end_day) << std::endl;
        ss << "  pay_time_limit: " << timeToString(pay_time_limit) << std::endl;
        ss << "  id: " << id << std::endl;
        ss << "  apartment_id: " << apartment_id << std::endl;
        ss << "  user_id: " << user_id << std::endl;
        ss << "}";
        return ss.str();
    }



private:
    static int getStoreSize(){
        chrono::system_clock::duration::rep exampleTime;
        return 8*3+4*4;
    }

    static std::string timeToString(std::chrono::time_point<std::chrono::system_clock> time) {
        auto time_t = std::chrono::system_clock::to_time_t(time);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%c");
        return ss.str();
    }
};





#endif //BD_APARTMENTSTATUS_H
