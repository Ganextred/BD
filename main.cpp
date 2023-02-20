#include <iostream>

#include<fstream>
#include "ApartmentStatus.h"
#include "Apartment.h"
using namespace std;

class BD {

public:
    static int main() {
//        ApartmentStatus status;
//        status.arrival_day = std::chrono::system_clock::now();
//        status.end_day = status.arrival_day + std::chrono::hours(24);
//        status.pay_time_limit = status.arrival_day + std::chrono::hours(12);
//        status.id = 0;
//        status.apartment_id = 2;
//        status.user_id = 3;
//
//        // Serialize to a file
//        status.serialize(0);

        std::ofstream outfile("ApartmentStoreFile", std::ios::binary);
        outfile.clear();
        outfile.close();
        std::ofstream outfile2("ApartmentStatusStoreFile", std::ios::binary);
        outfile2.clear();
        outfile2.close();

        // Deserialize from a file
        //std::ifstream infile("file", std::ios::app);
//        ApartmentStatus deserialized_status = ApartmentStatus::deserialize(1);
        //infile.close();
//        cout << deserialized_status.toString();

        for(int i = 0; i<5; i++){
            Apartment a;
            a.beds = i+5;
            a.clazz = i;
            a.price = i*1000;
            insert_m(a);
        }

        for(int i = 0; i<3; i++){
            for (int j=0; j<=i; j++) {
                ApartmentStatus status;
                status.arrival_day = std::chrono::system_clock::now();
                status.end_day = status.arrival_day + std::chrono::hours(24);
                status.pay_time_limit = status.arrival_day + std::chrono::hours(12);
                status.apartment_id = i;
                status.user_id = i + 8;
                insert_s(status);
            }
        }

        ut_m();
        cout<<"1111111111111111111111111111111111111111111111111"<<endl;
        ut_s();
        Apartment a1 = Apartment();
        a1.id = 1;
        delete_m(a1);
        ApartmentStatus as3 = ApartmentStatus();
        as3.id = 3;
        delete_s(as3);
        cout<<"/////////////////////////////////////////////////"<<endl;
        ut_m();
        cout<<"2222222222222222222222222222222222222222222222222"<<endl;
        ut_s();

        Apartment a;
        a.beds = 999;
        a.clazz = 999;
        a.price = 999;
        int apartmentId = insert_m(a);
        ApartmentStatus status;
        status.arrival_day = std::chrono::system_clock::now();
        status.end_day = status.arrival_day + std::chrono::hours(24);
        status.pay_time_limit = status.arrival_day + std::chrono::hours(12);
        status.apartment_id = apartmentId;
        status.user_id = 999;
        insert_s(status);
        cout<<"/////////////////////////////////////////////////"<<endl;
        ut_m();
        cout<<"3333333333333333333333333333333333333333333333333"<<endl;
        ut_s();
        a.price = 777;
        status.user_id = 777;
        update_m(a);
        update_s(status);
        cout<<"/////////////////////////////////////////////////"<<endl;
        ut_m();
        cout<<"4444444444444444444444444444444444444444444444444"<<endl;
        ut_s();




        return 0;
    }

    static Apartment get_m(int i) {
        Apartment entity = Apartment::deserialize(i);
        return entity;
    };

    static ApartmentStatus get_s(int i) {
        ApartmentStatus entity = ApartmentStatus::deserialize(i);
        return entity;
    };

    static int insert_m(Apartment &e) {
        if (e.id >= 0) {
            cout << "неможливо додати сутність з заздалегіть визначеними ідентифікатором";
            return -1;
        }
        int i = 0;
        Apartment a= get_m(i);
        while(a.id >= 0){
            i++;
            a = get_m(i);
        }
        e.id = i;
        e.serialize(i);
        return i;
    };

    static int insert_s(ApartmentStatus &e) {
        if (e.id >= 0) {
            cout << "неможливо додати сутність з заздалегіть визначеними ідентифікатором";
            return -1;
        }
        if (get_m(e.apartment_id).id < 0){
            cout << "неможливо додати дочірню сутність без батьківської";
            return -1;
        }
        int i = 0;
        ApartmentStatus as = get_s(i);
        while(as.id >= 0){
            i++;
            as = get_s(i);
        }
        e.id = i;
        e.serialize(i);
        return i;
    };

    static int update_m(Apartment e) {
        if (e.id <= 0) {
            cout << "неможливо оновити сутність без визначененого ідентифікатора";
            return -1;
        }
        if (get_m(e.id).id < 0){
            cout << "неможливо оновити неіснуючу сутність";
            return -1;
        }
        e.serialize(e.id);
        return 1;
    };

    static int update_s(ApartmentStatus e) {
        if (e.id <= 0) {
            cout << "неможливо оновити сутність без визначененого ідентифікатора";
            return -1;
        }
        if (get_s(e.id).id < 0){
            cout << "неможливо оновити неіснуючу сутність";
            return -1;
        }
        e.serialize(e.id);
        return 1;
    };



    static int delete_s(ApartmentStatus &e) {
        if (e.id <= 0) {
            cout << "неможливо видалити сутність без визначененого ідентифікатора";
            return -1;
        }
        if (get_s(e.id).id < 0){
            cout << "сутність вже видалена або ніколи не існувала";
            return -1;
        }
        int i = e.id;
        e.id = -1;
        e.serialize(i);
        return 1;
    };

    static void deleteSlaves(Apartment &apartment) {
        int i = 0;
        ApartmentStatus as = get_s(i);
        while (as.id != -2 ){
            if (as.apartment_id == apartment.id)
                delete_s(as);
            i++;
            as = get_s(i);
        };
    }

    static int delete_m(Apartment &e) {
        if (e.id <= 0) {
            cout << "неможливо видалити сутність без визначененого ідентифікатора";
            return -1;
        }
        if (get_s(e.id).id < 0){
            cout << "сутність вже видалена або ніколи не існувала";
            return -1;
        }
        deleteSlaves(e);
        int i = e.id;
        e.id = -1;
        e.serialize(i);
        return 1;
    };

    static void ut_m(){
        int i = 0;
        Apartment a = get_m(i);
        while (a.id != -2 ){
            if (a.id != -1 )
                cout << a.toString()<<" ";
            i++;
            a = get_m(i);
        }
        cout<<endl;
    }

    static void ut_s(){
        int i = 0;
        ApartmentStatus a = get_s(i);
        while (a.id != -2 ){
            if (a.id != -1 )
                cout << a.toString()<<" ";
            i++;
            a = get_s(i);
        }
        cout<<endl;
    }
};


int main() {
    return BD::main();
}
