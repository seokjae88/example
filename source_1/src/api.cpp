//
// Created by jsj on 2020-11-05.
//

#include "api.hpp"

const tsl::hopscotch_map<std::string, carInfo> carMakerV1::carInfoMap = carMakerV1::initailize();

// car maker V1
const tsl::hopscotch_map<std::string, carInfo> carMakerV1::initailize() {
    tsl::hopscotch_map<std::string, carInfo> initMap;
    initMap.insert(std::make_pair(
            "avante", std::make_tuple(logoType::Hyundai, carType::Sedan, (void*)makeFuncList::avante)));
    initMap.insert(std::make_pair(
            "sonata", std::make_tuple(logoType::Hyundai, carType::Sedan, (void*)makeFuncList::sonata)));
    return initMap;
}
// car maker V2
const tsl::hopscotch_map<std::string, carInfo> carMakerV2::initailize() {
    tsl::hopscotch_map<std::string, carInfo> initMap;
    initMap.insert(std::make_pair(
            "avante", std::make_tuple(logoType::Hyundai, carType::Sedan, (void*)makeFuncList::avante)));
    initMap.insert(std::make_pair(
            "sonata", std::make_tuple(logoType::Hyundai, carType::Sedan, (void*)makeFuncList::sonata)));
    return initMap;
}

bool makeLogo(logoType lType, ResultCar* resultCar) {
    ...
}


// =============================================================================================================================================

template bool carMaker<carMakerV1>::makeCar(const std::string &carName, CarData* data, ResultCar* resultCar);
template bool carMaker<carMakerV2>::makeCar(const std::string &carName, CarData* data, ResultCar* resultCar);

template <typename T>
bool carMaker<T>::makeCar(const std::string &carName, CarData* data, ResultCar* resultCar) {
    bool result = false;
    if (T::carInfoMap.count(carName)) {
        logoType lType;
        carType cType;
        void* makeFunc;
        std::tie(lType, cType, makeFunc) = T::carInfoMap.at(carName);
        switch (cType) {
            case carType::Sedan: {
                if (makeFunc != nullptr) {
                    if (makeLogo(lType, resultCar)) {
                        result = (*(makeSedanFunc)makeFunc)(carName, data, resultCar);
                    }
                }
                break;
            }
            case carType::SUV: {
                if (makeFunc != nullptr) {
                    if (makeLogo(lType, resultCar)) {
                        result = (*(makeSuvFunc)makeFunc)(carName, data, resultCar);
                    }
                }
                break;
            }
            default:
                result = false;
                break;
        }
    }

    return result;
}