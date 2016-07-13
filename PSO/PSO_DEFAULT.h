#ifndef PSO_DEFAULT_H
#define PSO_DEFAULT_H
#include<vector>
#include"PSO_AlgorithmParam.h"
using namespace std;

class PSO_DEFAULT : public PSO_AlgorithmParam
{
private:
	float w, c1, c2, cN;
public:
	PSO_DEFAULT(){}
	PSO_DEFAULT(float _w, float _c1, float  _c2, float  _cN) : w(_w), c1(_c1), c2(_c2), cN(_cN)
	{
	}
	void setParameters(float& _w, float& _c1, float&  _c2, float&  _cN)
	{
		_w = w; _c1 = c1; _c2 = c2; _cN = cN;
	}
};

#endif