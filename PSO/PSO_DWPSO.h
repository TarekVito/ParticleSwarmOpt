#ifndef PSO_TVACPSO_H
#define PSO_TVACPSO_H
#include<vector>
#include"PSO_AlgorithmParam.h"
using namespace std;

class PSO_DWPSO : public PSO_AlgorithmParam
{
private:
	float dLow, dHigh, Ws, We, c1, c2, cN;
public:
	PSO_DWPSO(){}
	PSO_DWPSO(float _dLow, float _dHigh, float _Ws, float _We, float _c1, float  _c2, float  _cN) : dLow(_dLow), dHigh(_dHigh), Ws(_Ws), We(_We), c1(_c1), c2(_c2), cN(_cN)
	{
	}
	void setParameters(float& _dLow, float& _dHigh, float _Ws, float _We, float& _c1, float&  _c2, float&  _cN)
	{
		_dLow = dLow; _dHigh = dHigh; _Ws = Ws; _We = We; _c1 = c1; _c2 = c2; _cN = cN;
	}
};

#endif