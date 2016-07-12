#ifndef PSO_H
#define PSO_H

#include<vector>
#include"Particle.h"
#include <fstream>

using namespace std;
enum ParticleType { Default };
class PSO
{
private:
	static vector<Particle*> particles;
	pair<vector<float>&, float> getLocalBest(int particleIdx, int NoNeighbors);
	pair<vector<float>&, float> getGlobalBest();
	float getDistance(Particle* p1, Particle* p2);
	bool checkConstraint(float minChangeDistance, float prev, float now, float targetValue, float targetValError);
	void writeToFile(vector<float>& vec, ofstream* file);
public:
	static vector<Particle*> getParticles();
	PSO(int NoParticles, int numberOfFeatures, ParticleType type);
	const vector<float>& optimize(int NoIterations = numeric_limits<int>::max(), float minChangeDistance = 0, float targetValue = numeric_limits<float>::max(),
		float targetValError = 0, int LocalNoNeighbors = 0, float c1 = 1, float c2 = 1);
};

#endif