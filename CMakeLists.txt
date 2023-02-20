cmake_minimum_required(VERSION 3.22)
project(BD)

set(CMAKE_CXX_STANDARD 14)

add_executable(BD main.cpp ApartmentStatus.cpp ApartmentStatus.h BaseEntity.cpp BaseEntity.h Apartment.cpp Apartment.h)
