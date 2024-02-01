#include "code.hpp"
#include <random>

using namespace std;

Code::Code(int l, int r) {
    n = l;
    m = r;
}

void Code::randomInitial() {
    for(int i = 0; i < n; i++) {
        int randVal = rand() % (m);
        secretCode.push_back(randVal);
    }
}

int Code::checkCorrect(const Code &code) {
    return 0;
}

int Code::checkIncorrect(const Code &code) {
    return 0;
}