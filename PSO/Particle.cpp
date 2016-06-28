#include"Particle.h"
#include<iostream>
using namespace std;
/////////////////Constructor/////////////////////
Particle::Particle(int NumberOfFeatures)
{
	velocity=features=minPosition=maxPosition=minVelocity=maxVelocity= vector<float>(NumberOfFeatures,0);
}
Particle::Particle(vector<float> _features)
{
	features = _features;
}


/////////////////Initialization//////////////////
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
////////////////////////Getter//////////////////////////
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

////////////////////////Update//////////////////////////
void Particle::update(vector<float>& gBest, vector<float>& lBest, float c1, float  c2)
{ 
	int NOfFeatures = features.size();
	for (int i = 0; i < NOfFeatures; ++i)
	{
		velocity[i] += c1 *  (rand() / (float)RAND_MAX)* (gBest[i] - features[i])
			+ (lBest.size() ? (c2 *  (rand() / (float)RAND_MAX)*(lBest[i] - features[i])) : 0);
		features[i] += velocity[i];
		
		velocity[i] = velocity[i]>maxVelocity[i] ? maxVelocity[i] : velocity[i];
		velocity[i] = velocity[i]<minVelocity[i] ? minVelocity[i] : velocity[i];
		features[i] = features[i]>maxPosition[i] ? maxPosition[i] : features[i];
		features[i] = features[i]<minPosition[i] ? minPosition[i] : features[i];
	}
}
