#ifndef PARTICLE_H
#define PARTICLE_H
#include<vector>
using namespace std;

class Particle
{
private:
	Particle* pBest;
	void updatePBest();
protected:
	vector<float> features, velocity;
	vector<float> minVelocity, maxVelocity, maxPosition, minPosition;
	float fittnessValue;
	
public:
	Particle(int numberOfFeatures);
	Particle(vector<float> _features);
	virtual void initializeParticles();
	virtual void initializeParticleLimits();

	Particle* getPBest(bool update);
	vector<float>& getFeatures();
	float getFittnessVal();

	virtual void update(vector<float>& gBest, vector<float>& lBest = vector<float>(), float c1 = 1, float  c2 = 1);
	virtual Particle* updateFittness() = 0; //return this
	
};

#endif