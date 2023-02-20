//
// Created by User on 14.02.2023.
//

#include "Apartment.h"
void Apartment::serialize(int i){
    std::ofstream stream(getName() + "StoreFile", std::ios::in);
    stream.seekp(i * getStoreSize());

    stream.write(reinterpret_cast<const char*>(&id), sizeof(id));
    stream.write(reinterpret_cast<const char*>(&beds), sizeof(beds));
    stream.write(reinterpret_cast<const char*>(&clazz), sizeof(clazz));
    stream.write(reinterpret_cast<const char*>(&price), sizeof(price));
    stream.close();
}

Apartment Apartment::deserialize(int i) {
    std::ifstream stream(getName() + "StoreFile", std::ios::out);
    Apartment e = Apartment();

    stream.seekg(0, ios::end);
    if ((i + 1) * getStoreSize() > stream.tellg()) {
        return e;
    }

    stream.seekg(i * getStoreSize());
    stream.read(reinterpret_cast<char*>(&e.id), sizeof(id));
    stream.read(reinterpret_cast<char*>(&e.beds), sizeof(beds));
    stream.read(reinterpret_cast<char*>(&e.clazz), sizeof(clazz));
    stream.read(reinterpret_cast<char*>(&e.price), sizeof(price));

    stream.close();
    return e;


}

