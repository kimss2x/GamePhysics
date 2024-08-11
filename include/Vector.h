#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
    float x, y, z;

    Vector(void);
    Vector(float xi, float yi, float zi);

    float Magnitude(void) const;
    void Normalize(void);
    void Reverse(void);

    Vector& operator+=(const Vector& u);
    Vector& operator-=(const Vector& u);
    Vector& operator*=(float s);
    Vector& operator/=(float s);

    Vector operator-(void) const;
};

Vector operator+(const Vector& u, const Vector& v);
Vector operator-(const Vector& u, const Vector& v);
Vector operator^(const Vector& u, const Vector& v);  // 외적
float operator*(const Vector& u, const Vector& v);  // 내적
Vector operator*(const Vector& u, float s);
Vector operator*(float s, const Vector& u);
Vector operator/(const Vector& u, float s);

float ScalarTripleProduct(const Vector& u, const Vector& v, const Vector& w);  // 스칼라 삼중곱
Vector VectorTripleProduct(const Vector& u, const Vector& v, const Vector& w);  // 벡터 삼중곱

#endif // VECTOR_H
