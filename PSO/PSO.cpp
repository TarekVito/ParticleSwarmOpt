#include<vector>
#include<algorithm>
#include <limits>
#include"Particle.h"
#include"Particle1.h"
#include"PSO.h"

using namespace std;

PSO::PSO(int NoParticles, int numberOfFeatures, ParticleType type)
{
	
	for (int i = 0; i < NoParticles; ++i)
	{
		switch (type)
		{
		case Default:
			particles.push_back(new Particle1(numberOfFeatures));
			break;
		default:
			return;
		}
	}
}

float PSO::getDistance(Particle* p1, Particle* p2)
{
	vector<float> pF1 = p1->getFeatures();
	vector<float> pF2 = p2->getFeatures();
	float dist= 0;
	int NoFeatures = pF1.size();
	for (int i = 0; i < NoFeatures; ++i)
		dist += (pF1[i] - pF2[i])*(pF1[i] - pF2[i]);
	return sqrt(dist);
}

pair<vector<float>&, float> PSO::getGlobalBest()
{
	int NoParticles = particles.size();
	float curMin = numeric_limits<float>::max();
	int bestIdx = -1;
	for (int i = 0; i < NoParticles; ++i)
	{
		float curFittness = particles[i]->getPBest(true)->updateFittness()->getFittnessVal();
		if (curFittness < curMin)
			curMin = curFittness, bestIdx = i;
	}
	return pair<vector<float>&, float>(particles[bestIdx]->getFeatures(), particles[bestIdx]->getFittnessVal());
}
pair<vector<float>&, float> PSO::getLocalBest(int pIdx, int NoNeighbors)
{
	if (!NoNeighbors)
		return pair<vector<float>&, float>(vector<float>(), 0);
	
	int NoParticles = particles.size();
	vector<pair<int,float>> dists;
	for (int i = 0; i < NoParticles; ++i)
		dists.push_back(pair<float,float>(i,getDistance(particles[pIdx], particles[i])));
	sort(dists.begin(), dists.end(), [&dists](pair<float, float> a, pair<float, float> b)
	{
		return a.second < b.second;
	});
	
	vector<float> lBest;
	float curMin = numeric_limits<float>::max();
	int bestIdx = -1;
	for (int i = 0; i < NoNeighbors; ++i)
	{
		float curFittness = particles[dists[i].first]->getPBest(false)->updateFittness()->getFittnessVal();
		if (curFittness < curMin)
			curMin = curFittness, bestIdx = i;
	}
	return pair<vector<float>&, float>(particles[bestIdx]->getFeatures(), particles[bestIdx]->getFittnessVal());
}


bool PSO::checkConstraint(float minChangeDistance, float prev, float now, float targetValue, float targetValError)
{
	if (minChangeDistance > 1e-7)
		return abs(prev - now) < minChangeDistance;
	if (targetValue != numeric_limits<float>::max())
		return abs(targetValue - now) < targetValError;
	return false;
}

const vector<float>& PSO::optimize(int NoIterations , float minChangeDistance, float targetValue ,
	float targetValError , int LocalNoNeighbors , float c1 , float c2 )
{
	int NoParticles = particles.size();
	float oldFittnessVal = particles[0]->updateFittness()->getFittnessVal();
	pair<vector<float>, float> gBest;
	for (int i = 0; i < NoIterations; ++i)
	{
		gBest = getGlobalBest();
		if (checkConstraint(minChangeDistance, oldFittnessVal, gBest.second, targetValue, targetValError))
			break;
		int NoParticles = particles.size();
		for (int i = 0; i < NoParticles; ++i)
		{
			pair<vector<float>&, float> lBest = getLocalBest(i, LocalNoNeighbors);
			particles[i]->update(gBest.first, lBest.first, c1, c2);
		}
	}
	return gBest.first;
}



