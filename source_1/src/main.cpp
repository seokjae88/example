//
// Created by jsj on 2020-11-05.
//

#include "api.hpp"

carData* makeAvanteData() {
    carData *data = new carData();
    // ...
    return data;
}
carData* makeSonataData() {
    carData *data = new carData();
    // ...
    return data;
}

int main() {
    carData *avanteData = makeAvanteData();
    resultCar *result = new resultCar();
    carMaker<carMakerV1>::makeCar("avante", avanteData, result);
}