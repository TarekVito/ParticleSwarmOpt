#ifndef PARTICLE_RPSO_H
#define PARTICLE_RPSO_H
#include<vector>
#include"Particle.h"
#include"PSO_RPSO.h"
#include"PSO.h"
using namespace std;

class Particle_RPSO : public Particle
{
private: 
	float dLow, dHigh, w, c1, c2, cN;
public:
	Particle_RPSO(int numberOfFeatures) : Particle(numberOfFeatures)
	{}
	virtual void Particle::update(vector<float>& gBest, vector<float>& lBest, PSO_AlgorithmParam* psoAlg)
	{
		PSO_RPSO* rpso = (PSO_RPSO*)psoAlg;
		rpso->setParameters(dLow, dHigh, w, c1, c2, cN);
		int NOfFeatures = features.size();
		vector<float> pBestF = pBest->getFeatures();
		for (int i = 0; i < NOfFeatures; ++i)
		{
			int dir = -1;
			float diversity = getDiversity();
			if (diversity < dLow)
				dir = -1;
			else if (diversity > dHigh)
				dir = 1;

			velocity[i] = w*velocity[i] + dir * c1 *  (rand() / (float)RAND_MAX)* (gBest[i] - features[i])
				+ dir * c2 *  (rand() / (float)RAND_MAX)*(pBestF[i] - features[i])
				+ (lBest.size() ? (dir * cN *  (rand() / (float)RAND_MAX)*(lBest[i] - features[i])) : 0);
			features[i] += velocity[i];

			velocity[i] = velocity[i] > maxVelocity[i] ? maxVelocity[i] : velocity[i];
			velocity[i] = velocity[i]<minVelocity[i] ? minVelocity[i] : velocity[i];
			features[i] = features[i]>maxPosition[i] ? maxPosition[i] : features[i];
			features[i] = features[i] < minPosition[i] ? minPosition[i] : features[i];
		}
	}
	virtual Particle* updateFittness() = 0; //return this
	float getDiversity()
	{
		vector<Particle*> particles = PSO::getParticles();
		int NOfFeatures = features.size();
		float NOfParticles = particles.size();
		vector<float> meanP;
		for (int i = 0; i < NOfFeatures; ++i){
			float meanI = 0;
			for (int j = 0; j <NOfParticles; ++j)
				meanI += particles[j]->getFeatures()[i];
			meanP.push_back(meanI / NOfParticles);
		}
		float sumSq = 0;
		for (int i = 0; i <NOfParticles; ++i)
		{
			float subSum = 0;
			for (int j = 0; j < NOfFeatures; ++j)
				subSum += (particles[i]->getFeatures()[j] - meanP[j])*(particles[i]->getFeatures()[j] - meanP[j]);
			sumSq += sqrt(subSum);
		}
		return 0;// sumSq;
	}
};

#endif