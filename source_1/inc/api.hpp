//
// Created by jsj on 2020-11-05.
//

#ifndef PORTFOLIO_API_HPP
#define PORTFOLIO_API_HPP

enum logoType {
    Hyundai,
    KIA,
    Chevrolet,
    BMW,
    Audi,
    Benz,
    Volvo,
    Ferrari
};

enum carType {
    Sedan,
    Hatchback,
    SUV,
    Coupe
};

typedef std::tuple<logoType, carType, void*> carInfo;
typedef bool(*makeCarFunc)(const std::string &carName, CarData* data, ResultCar* resultCar);

template <typename T>
class carMaker : T {
public:
    static void makeCar(const std::string &carName, CarData* data, ResultCar* resultCar);
};

class carMakerV1 {
protected:
    static const tsl::hopscotch_map<std::string, carInfo> carInfoMap;
public:
    static const tsl::hopscotch_map<std::string, carInfo> initailize();
};

class carMakerV2 {
protected:
    static const tsl::hopscotch_map<std::string, carInfo> carInfoMap;
public:
    static const tsl::hopscotch_map<std::string, carInfo> initailize();
};

bool makeLogo(logoType lType, ResultCar* resultCar);
#endif //PORTFOLIO_API_HPP
