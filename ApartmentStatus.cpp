#include "ApartmentStatus.h"
void ApartmentStatus::serialize(int i) {
    std::ofstream stream(getName() + "StoreFile", std::ios::in);
    stream.seekp(i * getStoreSize());

    auto arrival_day_ns = arrival_day.time_since_epoch().count();
    auto end_day_ns = end_day.time_since_epoch().count();
    auto pay_time_limit_ns = pay_time_limit.time_since_epoch().count();
    stream.write(reinterpret_cast<const char*>(&arrival_day_ns), 8);
    stream.write(reinterpret_cast<const char*>(&end_day_ns), 8);
    stream.write(reinterpret_cast<const char*>(&pay_time_limit_ns), 8);
    stream.write(reinterpret_cast<const char*>(&id), 4);
    stream.write(reinterpret_cast<const char*>(&apartment_id), 4);
    stream.write(reinterpret_cast<const char*>(&user_id), 4);
    stream.write(reinterpret_cast<const char*>(&user_id), 4);
    cout<<stream.tellp()<<" test ";

    stream.close();
}

ApartmentStatus ApartmentStatus::deserialize(int i) {
    std::ifstream stream(getName() + "StoreFile", std::ios::out);
    ApartmentStatus e = ApartmentStatus();

    stream.seekg(0, ios::end);
    if ((i + 1) * getStoreSize() > stream.tellg()) {
        return e;
    }

    stream.seekg(i * getStoreSize());
    chrono::system_clock::duration::rep arrival_day_ns, end_day_ns, pay_time_limit_ns;
    stream.read(reinterpret_cast<char*>(&arrival_day_ns), 8);
    stream.read(reinterpret_cast<char*>(&end_day_ns), 8);
    stream.read(reinterpret_cast<char*>(&pay_time_limit_ns), 8);
    e.arrival_day = std::chrono::time_point<std::chrono::system_clock>(
            chrono::system_clock::duration(arrival_day_ns));
    e.end_day = std::chrono::time_point<std::chrono::system_clock>(
            chrono::system_clock::duration(end_day_ns));
    e.pay_time_limit = std::chrono::time_point<std::chrono::system_clock>(
            chrono::system_clock::duration(pay_time_limit_ns));
    stream.read(reinterpret_cast<char*>(&e.id), 4);
    stream.read(reinterpret_cast<char*>(&e.apartment_id), 4);
    stream.read(reinterpret_cast<char*>(&e.user_id), 4);

    stream.close();
    return e;
}