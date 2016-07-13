#include"Particle.h"
#include"PSO.h"
#include"PSO_AlgorithmParam.h"
#include<iostream>
using namespace std;
/////////////Constructor/////////////////////
Particle::Particle(int NumberOfFeatures)
{
	velocity=features=minPosition=maxPosition=minVelocity=maxVelocity= vector<float>(NumberOfFeatures,0);
}
Particle::Particle(vector<float> _features)
{
	features = _features;
}


/////////////Initialization//////////////////
void Particle::initializeParticleLimits()
{
	int NOfFeatures = features.size();
	for (int i = 0; i < NOfFeatures; ++i)
	{
		maxPosition[i] = maxVelocity[i] = 100;
		minPosition[i] = minVelocity[i] = -100;
	}
}
void Particle::initializeParticles()
{
	int NOfFeatures = features.size();
	for (int i = 0; i < NOfFeatures; ++i)
	{
		features[i] =  (rand() / (float)RAND_MAX)*(maxPosition[i] - minPosition[i]) + minPosition[i];
		velocity[i] =  (rand() / (float)RAND_MAX)*(maxVelocity[i] - minVelocity[i]) + minVelocity[i];
	}
}
////////////////////Getter//////////////////////////
vector<float>& Particle::getFeatures()
{
	return features;
}
Particle* Particle::getPBest(bool update)
{
	if (pBest == NULL || (update && updateFittness()->getFittnessVal() > pBest->getFittnessVal()))
		pBest = this;
	return pBest;
}
float Particle::getFittnessVal()
{
	return fittnessValue;
}


float Particle::linearDecay(float s, float e, float N, float i)
{
	return (s - (s - e)*(i / (N - 1)));
}

