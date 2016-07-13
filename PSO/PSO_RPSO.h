#ifndef PSO_RPSO_H
#define PSO_RPSO_H
#include<vector>
#include"PSO_AlgorithmParam.h"
using namespace std;

class PSO_RPSO : public PSO_AlgorithmParam
{
private:
	float dLow, dHigh, w, c1, c2, cN;
public:
	PSO_RPSO(){}
	PSO_RPSO(float _dLow, float _dHigh,  float _w, float _c1, float  _c2, float  _cN) : dLow(_dLow), dHigh(_dHigh), w(_w), c1(_c1), c2(_c2), cN(_cN)
	{
	}
	void setParameters( float& _dLow, float& _dHigh, float& _w, float& _c1, float&  _c2, float&  _cN)
	{
		_dLow = dLow; _dHigh = dHigh; _w = w; _c1 = c1; _c2 = c2; _cN = cN;
	}
};

#endif