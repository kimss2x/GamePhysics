#include <cstdlib>  // rand()를 사용하기 위해 필요
#include <ctime>    // time()을 사용해 시드를 설정하기 위해 필요
#include <cmath>    // round()를 사용하기 위해 필요

// 0과 1 사이의 랜덤 값을 반환하는 함수 (정수형)
int tb_Rnd() {
    return rand() % 2; // 0 또는 1 반환
}

// min과 max 사이의 랜덤 값을 반환하는 함수 (정수형)
int tb_Rnd(int min, int max) {
    return min + (rand() % (max - min + 1)); // min과 max 사이의 정수 반환
}

// 실수를 가장 가까운 정수로 반올림하는 함수
int tb_Round(float value) {
    return static_cast<int>(std::round(value)); // 반올림된 정수를 반환
}
