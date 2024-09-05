#include <cstdlib>  // rand()�� ����ϱ� ���� �ʿ�
#include <ctime>    // time()�� ����� �õ带 �����ϱ� ���� �ʿ�
#include <cmath>    // round()�� ����ϱ� ���� �ʿ�

// 0�� 1 ������ ���� ���� ��ȯ�ϴ� �Լ� (������)
int tb_Rnd() {
    return rand() % 2; // 0 �Ǵ� 1 ��ȯ
}

// min�� max ������ ���� ���� ��ȯ�ϴ� �Լ� (������)
int tb_Rnd(int min, int max) {
    return min + (rand() % (max - min + 1)); // min�� max ������ ���� ��ȯ
}

// �Ǽ��� ���� ����� ������ �ݿø��ϴ� �Լ�
int tb_Round(float value) {
    return static_cast<int>(std::round(value)); // �ݿø��� ������ ��ȯ
}
