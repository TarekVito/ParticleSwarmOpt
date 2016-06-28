#ifndef PARTICLE1_H
#define PARTICLE1_H

#include<vector>
#include"Particle.h"

using namespace std;
class Particle1 : public Particle
{
public:
	Particle1(int numberOfFeatures) : Particle(numberOfFeatures)
	{
		for (int i = 0; i < numberOfFeatures; ++i)
			maxPosition[i] = 1, minPosition[i] = -1, maxVelocity[i] = 0.01, minVelocity[i] = -0.01;
		initializeParticles();
	}
	Particle* updateFittness()
	{
		fittnessValue = 0;
		for (int i = 0; i < features.size();++i)
			fittnessValue = features[i];
		fittnessValue = cos(fittnessValue);
		return this;
	}

};
#endif