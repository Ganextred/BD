#include <iostream>

#include<fstream>
#include <Windows.h>
#include <valarray>
#include "ApartmentStatus.h"
#include "Apartment.h"
using namespace std;

class BD {

public:
    static int main() {
        system("chcp 65001");

        std::ofstream outfile("ApartmentStoreFile", std::ios::binary);
        outfile.clear();
        outfile.close();
        std::ofstream outfile2("ApartmentStatusStoreFile", std::ios::binary);
        outfile2.clear();
        outfile2.close();

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

//        cout<<"ut_m"<<endl;
//        ut_m();
//        cout<<"ut_s"<<endl;
//        ut_s();
//        Apartment a1 = Apartment();
//        a1.id = 1;
//        cout<<"delete_m 1"<<endl;
//        delete_m(a1);
//        ApartmentStatus as3 = ApartmentStatus();
//        as3.id = 3;
//        delete_s(as3);
//        cout<<"delete_s 3"<<endl;
//        cout<<"ut_m"<<endl;
//        ut_m();
//        cout<<"ut_s"<<endl;
//        ut_s();
//
//        Apartment a;
//        a.beds = 999;
//        a.clazz = 999;
//        a.price = 999;
//        cout<<"insert_m"<<" "<< a.clazz<<" "<< a.price<<" "<<endl;
//        int apartmentId = insert_m(a);
//        ApartmentStatus status;
//        status.arrival_day = std::chrono::system_clock::now();
//        status.end_day = status.arrival_day + std::chrono::hours(24);
//        status.pay_time_limit = status.arrival_day + std::chrono::hours(12);
//        status.apartment_id = apartmentId;
//        status.user_id = 999;
//        cout<<"insert_s"<<" "<<status.apartment_id<<" "<< status.user_id<<" "<<endl;
//        insert_s(status);
//        cout<<"ut_m"<<endl;
//        ut_m();
//        cout<<"ut_s"<<endl;
//        ut_s();
//        a.price = 777;
//        status.user_id = 777;
//        cout<<"update_m "<<a.id <<" "<< a.clazz<<" "<< a.price<<" "<<endl;
//        update_m(a);
//        cout<<"update_s "<<" "<<status.id<<" "<<status.apartment_id<<" "<< status.user_id<<" "<<endl;
//        update_s(status);
//        cout<<"ut_m"<<endl;
//        ut_m();
//        cout<<"ut_s"<<endl;
//        ut_s();

        cout<<"Команди та список параметрів:"<<endl<<
        "get_m id; get_s id;\ninsert_m beds, class, price; insert_s apartment_id, user_id"<<endl<<
        "delete_m id; delete_s id;\nupdate_m id beds, class, price; update_s id  apartment_id, user_id;"<<endl<<
        "ut_m; ut_s"<<endl;

        while(true){
            cout<<"Введіть команду:\n";
            string r;
            cin >> r;
            if (r == "get_s"){
                int id;
                cin >> id;
                if (get_s(id).id >= 0)
                    cout<<get_s(id).toString();
                else cout<<"Сутність не існує"<<endl;
            }
            else if (r == "get_m"){
                int id;
                cin >> id;
                if (get_m(id).id >= 0)
                    cout<<get_m(id).toString();
                else cout<<"Сутність не існує"<<endl;

            }
            else if (r == "insert_m"){
                Apartment a;
                cin>>a.beds;
                cin>>a.clazz;
                cin>>a.price;
                cout << "id доданої квартири " << insert_m(a)<<endl;
            }else if (r == "insert_s"){
                ApartmentStatus status;
                status.arrival_day = std::chrono::system_clock::now();
                status.end_day = status.arrival_day + std::chrono::hours(24);
                status.pay_time_limit = status.arrival_day + std::chrono::hours(12);
                cin>>status.apartment_id;
                cin>>status.user_id;
                int id = insert_s(status);
                if (id)
                    cout << "id доданого статусу " << id<<endl;
            }else if (r == "delete_m"){
                Apartment a = Apartment();
                cin >> a.id;
                if (delete_m(a) == 1)
                    cout << "Сутність видалена "<<endl;;
            }
            else if (r == "delete_s"){
                ApartmentStatus as = ApartmentStatus();
                cin >> as.id;
                if (delete_s(as) == 1)
                    cout << "Сутність видалена "<<endl;;
            }else if (r == "update_m"){
                Apartment a;
                cin>>a.id;
                cin>>a.beds;
                cin>>a.clazz;
                cin>>a.price;
                if (update_m(a) == 1)
                    cout << "Сутність оновлена "<<endl;
            }else if (r == "update_s"){
                ApartmentStatus status;
                cin >> status.id;
                cin>>status.apartment_id;
                cin>>status.user_id;
                status.arrival_day = std::chrono::system_clock::now();
                status.end_day = status.arrival_day + std::chrono::hours(24);
                status.pay_time_limit = status.arrival_day + std::chrono::hours(12);
                if (update_s(status) == 1)
                    cout << "Сутність оновлена "<<endl;;;
            }else if (r == "ut_m"){
                ut_m();
            }else if (r == "ut_s"){
                ut_s();
            }else {
                cout<<"Невірна команда"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }


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
            cout << "Неможливо додати сутність з заздалегіть визначеними ідентифікатором";
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
            cout << "Неможливо додати сутність з заздалегіть визначеними ідентифікатором"<<endl;
            return -1;
        }
        if (get_m(e.apartment_id).id < 0){
            cout << "Неможливо додати дочірню сутність без батьківської"<<endl;
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
        if (e.id < 0) {
            cout << "Неможливо оновити сутність без визначененого ідентифікатора"<<endl;
            return -1;
        }
        if (get_m(e.id).id < 0){
            cout << "Неможливо оновити неіснуючу сутність"<<endl;
            return -1;
        }
        e.serialize(e.id);
        return 1;
    };

    static int update_s(ApartmentStatus e) {
        if (e.id < 0) {
            cout << "Неможливо оновити сутність без визначененого ідентифікатора"<<endl;
            return -1;
        }
        if (get_s(e.id).id < 0){
            cout << "Неможливо оновити неіснуючу сутність"<<endl;
            return -1;
        }
        if (get_m(e.apartment_id).id < 0){
            cout << "Неможливо оновити дочірню сутність, невірна батьківська"<<endl;
            return -1;
        }
        e.serialize(e.id);
        return 1;
    };



    static int delete_s(ApartmentStatus &e) {
        if (e.id < 0) {
            cout << "Неможливо видалити сутність без визначененого ідентифікатора"<<endl;
            return -1;
        }
        if (get_s(e.id).id < 0){
            cout << "Сутність вже видалена або ніколи не існувала"<<endl;
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
        if (e.id < 0) {
            cout << "неможливо видалити сутність без визначененого ідентифікатора"<<endl;
            return -1;
        }
        if (get_m(e.id).id < 0){
            cout << "сутність вже видалена або ніколи не існувала"<<endl;
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

