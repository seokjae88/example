//
// Created by jsj on 2020-11-05.
//

#ifndef PORTFOLIO_MAKECARFUNC_HPP
#define PORTFOLIO_MAKECARFUNC_HPP

class makeSedanFunc {
public:
    static bool avante(const std::string &carName, CarData* data, ResultCar* resultCar);
    static bool sonata(const std::string &carName, CarData* data, ResultCar* resultCar);
}
class makeSuvFunc {
public:
    static bool trax(const std::string &carName, CarData* data, ResultCar* resultCar);
}

#endif //PORTFOLIO_MAKECARFUNC_HPP
