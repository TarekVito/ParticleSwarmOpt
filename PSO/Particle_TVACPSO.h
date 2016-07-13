#ifndef PARTICLE_TVACPSO_H
#define PARTICLE_TVACPSO_H
#include<vector>
#include"Particle.h"
#include"PSO_TVACPSO.h"
using namespace std;

class Particle_TVACPSO : public Particle
{
private:
	float Ws, We, c1s, c2s, c1e, c2e, cN;
public:
	Particle_TVACPSO(int numberOfFeatures) : Particle(numberOfFeatures)
	{}
	virtual void Particle::update(vector<float>& gBest, vector<float>& lBest, PSO_AlgorithmParam* psoAlg)
	{
		PSO_TVACPSO* tvacpso = (PSO_TVACPSO*)psoAlg;
		tvacpso->setParameters(Ws, We, c1s, c2s, c1e, c2e, cN);
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
	virtual Particle* updateFittness() = 0; //return this

};

#endif