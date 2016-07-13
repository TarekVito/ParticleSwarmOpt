#include<iostream>
#include"PSO.h"
#include"PSO_AlgorithmParam.h"
#include"PSO_RPSO.h"
using namespace std;

int main()
{
	ParticleType PType;
	PType = Default;
	PSO test(5,1,PType);
	PSO_AlgorithmParam* param = new PSO_RPSO(0.5, 0.3, 0.4, 0.5, 0.9, 0.4);
	test.optimize(param,10);
}