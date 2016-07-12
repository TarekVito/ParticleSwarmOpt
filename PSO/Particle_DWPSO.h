#ifndef PARTICLE_H
#define PARTICLE_H
#include<vector>
using namespace std;

class Particle
{
private:
	Particle* pBest = NULL;
	void updatePBest();
protected:
	float fittnessValue;
	vector<float> features, velocity;
	vector<float> minVelocity, maxVelocity, maxPosition, minPosition;

public:
	Particle(int numberOfFeatures);
	Particle(vector<float> _features);
	virtual void initializeParticles();
	virtual void initializeParticleLimits();

	Particle* getPBest(bool update);
	vector<float>& getFeatures();
	float getFittnessVal();
	float linearDecay(float s, float e, float N, float i);
	float getDiversity();

	virtual void update(vector<float>& gBest, vector<float>& lBest = vector<float>(), float w = 1, float c1 = 1, float  c2 = 1, float  cN = 1);
	virtual void updateDWPSO(vector<float>& gbest, vector<float>& lbest = vector<float>(), float ws = 1, float we = 1, float c1 = 1, float  c2 = 1, float  cn = 1);
	virtual void updateTVACPSO(vector<float>& gbest, vector<float>& lbest = vector<float>(), float ws = 1, float we = 1,
		float c1s = 1, float  c2s = 1, float c1e = 1, float  c2e = 1, float  cn = 1);
	void updateRPSO(vector<float>& gbest, float dlow, float dhigh, vector<float>& lbest = vector<float>(), float w = 1, float c1 = 1, float  c2 = 1, float  cn = 1);
	virtual Particle* updateFittness() = 0; //return this

};

#endif