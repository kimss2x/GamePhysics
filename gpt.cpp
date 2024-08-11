// 유저가 입력한 변수를 가져와 아래의 전역변수에 저장
// Vm, Alpha, Gamma, L, Yb, X, Y, Z, Length, Width, Height

// time과 status 변수를 초기화 한다.
status = 0;
time = 0;

// 목표물을 맞히거나, 포탄이 땅에 떨어지거나,
// 타임아웃 될 때까지 시간단계별로 시뮬레이션을 돌린다.
while(status == 0)
{
    // 다음 시간단계를 시뮬레이션한다.
    status = DoSimulation();

    화면 업데이트
}

// 결과를 보고 한다.
if(status == 1)
    // Direct Hit 메시지를 유저에게 보여준다.
if(status == 2)
    // Missed Target 메시지를 유저에게 보여준다.
if(status == 3)
    // Simulation Timed Out 메시지를 유저에게 보여준다.

// --------------------------------
// 3차원 벡터의 3 성분을 담는 구조체
// i는 x 성분, j는 y성분, k는 z성분을 나타낸다. 
// --------------------------------

typedef struct TVectorTag
{
    double i;
    double j;
    double k;
} TVectorTag;

// --------------------------------
// 시뮬레이션에 필요한 변수
// --------------------------------

double Vm;      // 투사체의 탄속, m/s
double Alpha;   // Pitch
double Gamma;   // Yaw 0일때 포신은 정면(Z축)을 향한다. 

double L;       // 대포의 길이, m
double Yb;      // 대포의 높이, m

double X;       // 목표물의 중심좌표 중 x 값, m
double Y;       // 목표물의 중심좌표 중 y 값, m
double Z;       // 목표물의 중심좌표 중 z 값, m
double Length;  // 목표물의 길이(x축), m
double Width;   // 목표물의 너비(z축), m
double Height;  // 목표물의 높이(y축), m

TVector s;      // 투사체의 위치(변위) 벡터

double time;    // 포탄이 대포에서 발사된 순간의 시간, seconds
double tInc;    // 시뮬레이션 중에 한 단계마다 증가시킬 시간 값, seconds

double g;       // 중력에 의한 가속도, m/s^2