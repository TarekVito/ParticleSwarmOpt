#ifndef ParticleSinTest_H
#define ParticleSinTest_H

#include<vector>
#include"Particle_RPSO.h"

using namespace std;
class ParticleSinTest : public Particle_RPSO
{
public:
	ParticleSinTest(int numberOfFeatures) : Particle_RPSO(numberOfFeatures)
	{
		for (int i = 0; i < numberOfFeatures; ++i)
			maxPosition[i] = 50, minPosition[i] = 0, maxVelocity[i] = 0.01, minVelocity[i] = -0.01;
		initializeParticles();
	}

	Particle* updateFittness()
	{
		fittnessValue = sin(features[0]) + sin((features[0]) * 10);
		return this;
	}
};
#endif