#include<iostream>
#include"PSO.h"
using namespace std;

int main()
{
	ParticleType PType;
	PType = Default;
	PSO test(5,1,PType);
	
	test.optimize(10);
}