#ifndef PARTICLE_H
#define PARTICLE_H
#include<vector>
#include"PSO_AlgorithmParam.h"

using namespace std;

class Particle
{
private:
	void updatePBest();
protected:
	Particle* pBest = NULL;
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
	float linearDecay(float s,float e,float N,float i);

	virtual void Particle::update(vector<float>& gBest, vector<float>& lBest, PSO_AlgorithmParam* psoAlg) = 0;
	virtual Particle* updateFittness() = 0; //return this
	
};

#endif