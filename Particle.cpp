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
void Particle::update(vector<float>& gBest, vector<float>& lBest, float w, float c1, float  c2, float cN)
{
	int NOfFeatures = features.size();
	vector<float> pBestF = pBest->getFeatures();
	for (int i = 0; i < NOfFeatures; ++i)
	{
		velocity[i] = w*velocity[i] + c1 *  (rand() / (float)RAND_MAX)* (gBest[i] - features[i])
			+ c2 *  (rand() / (float)RAND_MAX)*(pBestF[i] - features[i])
			+ (lBest.size() ? (cN *  (rand() / (float)RAND_MAX)*(lBest[i] - features[i])) : 0);
		features[i] += velocity[i];

		velocity[i] = velocity[i]>maxVelocity[i] ? maxVelocity[i] : velocity[i];
		velocity[i] = velocity[i]<minVelocity[i] ? minVelocity[i] : velocity[i];
		features[i] = features[i]>maxPosition[i] ? maxPosition[i] : features[i];
		features[i] = features[i]<minPosition[i] ? minPosition[i] : features[i];
	}
}
void Particle::updateDWPSO(vector<float>& gBest, vector<float>& lBest, float Ws, float We, float c1, float  c2, float cN)
{ 
	int NOfFeatures = features.size();
	vector<float> pBestF = pBest->getFeatures();
	for (int i = 0; i < NOfFeatures; ++i)
	{
		velocity[i] = linearDecay(Ws, We, NOfFeatures,i)*velocity[i] + c1 *  (rand() / (float)RAND_MAX)* (gBest[i] - features[i])
			+ c2 *  (rand() / (float)RAND_MAX)*(pBestF[i] - features[i])
			+(lBest.size() ? (cN *  (rand() / (float)RAND_MAX)*(lBest[i] - features[i])) : 0);
		features[i] += velocity[i];
		
		velocity[i] = velocity[i]>maxVelocity[i] ? maxVelocity[i] : velocity[i];
		velocity[i] = velocity[i]<minVelocity[i] ? minVelocity[i] : velocity[i];
		features[i] = features[i]>maxPosition[i] ? maxPosition[i] : features[i];
		features[i] = features[i]<minPosition[i] ? minPosition[i] : features[i];
	}
}
void Particle::updateTVACPSO(vector<float>& gBest, vector<float>& lBest = vector<float>(), float Ws = 1, float We = 1,
	float c1s = 1, float  c2s = 1, float c1e = 1, float  c2e = 1, float  cN = 1)
{
	int NOfFeatures = features.size();
	vector<float> pBestF = pBest->getFeatures();
	for (int i = 0; i < NOfFeatures; ++i)
	{
		velocity[i] = linearDecay(Ws, We, NOfFeatures, i)*velocity[i] + linearDecay(c1s, c1e, NOfFeatures, i) *  (rand() / (float)RAND_MAX)* (gBest[i] - features[i])
			+ linearDecay(c2s, c2e, NOfFeatures, i) *  (rand() / (float)RAND_MAX)*(pBestF[i] - features[i])
			+ (lBest.size() ? (cN *  (rand() / (float)RAND_MAX)*(lBest[i] - features[i])) : 0);
		features[i] += velocity[i];

		velocity[i] = velocity[i]>maxVelocity[i] ? maxVelocity[i] : velocity[i];
		velocity[i] = velocity[i]<minVelocity[i] ? minVelocity[i] : velocity[i];
		features[i] = features[i]>maxPosition[i] ? maxPosition[i] : features[i];
		features[i] = features[i]<minPosition[i] ? minPosition[i] : features[i];
	}
}
void Particle::updateRPSO(vector<float>& gBest, vector<float>& lBest = vector<float>(), float dLow, float dHigh, float w, float c1, float  c2, float cN)
{
	int NOfFeatures = features.size();
	vector<float> pBestF = pBest->getFeatures();
	for (int i = 0; i < NOfFeatures; ++i)
	{
		int dir = -1, diversity = getDiversity();
		if (diversity < dLow)
			dir = -1;
		else if (diversity > dHigh)
			dir = 1;


		velocity[i] = linearDecay(Ws, We, NOfFeatures, i)*velocity[i] + linearDecay(c1s, c1e, NOfFeatures, i) *  (rand() / (float)RAND_MAX)* (gBest[i] - features[i])
			+ linearDecay(c2s, c2e, NOfFeatures, i) *  (rand() / (float)RAND_MAX)*(pBestF[i] - features[i])
			+ (lBest.size() ? (cN *  (rand() / (float)RAND_MAX)*(lBest[i] - features[i])) : 0);
		features[i] += 

		velocity[i] = velocity[i]>maxVelocity[i] ? maxVelocity[i] : velocity[i];
		velocity[i] = velocity[i]<minVelocity[i] ? minVelocity[i] : velocity[i];
		features[i] = features[i]>maxPosition[i] ? maxPosition[i] : features[i];
		features[i] = features[i]<minPosition[i] ? minPosition[i] : features[i];
	}
}

float Particle::getDiversity()
{
	int sumSq = 0;
	int NOfFeatures = features.size();
	for (int i = 0; i < NOfFeatures; ++i)

}
float Particle::linearDecay(float s, float e, float N, float i)
{
	return (s - (s - e)*(i / (N - 1)));
}
