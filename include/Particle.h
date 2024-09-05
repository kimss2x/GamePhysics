typedef struct _TParticle
{
	float x;
	float y;
	float vi;
	float angle;
	int life;
	int r;
	int g;
	int b;
	int time;
	float gravity;
	bool Active;
} TParticle;

#define _MAXPARICLES 50

typedef struct _TParticleExplosion
{
	TParticle p[_MAXPARICLES];
	int V0;
	int x;
	int y;
	bool Active;
} TParticleExplosion;
