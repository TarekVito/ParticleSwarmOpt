#include<iostream>
#include"PSO.h"
using namespace std;

int main()
{
	ParticleType PType;
	PType = Default;
	PSO test(20,100,PType);
	
	test.optimize(10);
}