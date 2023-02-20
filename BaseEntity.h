//
// Created by User on 14.02.2023.
//

#ifndef BD_BASEENTITY_H
#define BD_BASEENTITY_H
#include <istream>
using namespace std;
class BaseEntity
{
public:
    int id = -2;
    virtual void serialize(ostream& stream, int  i) {};
};


#endif //BD_BASEENTITY_H
