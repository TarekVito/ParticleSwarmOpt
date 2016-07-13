#ifndef PARTICLE_RPSO_H
#define PARTICLE_RPSO_H
#include<vector>
#include"Particle.h"
#include"PSO_DWPSO.h"
using namespace std;

class Particle_DWPSO : public Particle
{
private:
	float dLow, dHigh, Ws, We, c1, c2, cN;
public:
	Particle_DWPSO(int numberOfFeatures) : Particle(numberOfFeatures)
	{}
	virtual void Particle::update(vector<float>& gBest, vector<float>& lBest, PSO_AlgorithmParam* psoAlg)
	{
		PSO_DWPSO* dwpso = (PSO_DWPSO*)psoAlg;
		dwpso->setParameters(dLow, dHigh, Ws, We, c1, c2, cN);
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
	virtual Particle* updateFittness() = 0; //return this

};

#endif