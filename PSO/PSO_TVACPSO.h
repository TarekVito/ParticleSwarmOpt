#ifndef PSO_TVACPSO_H
#define PSO_TVACPSO_H
#include<vector>
#include"PSO_AlgorithmParam.h"
using namespace std;

class PSO_TVACPSO : public PSO_AlgorithmParam
{
private:
	float Ws, We, c1s, c2s, c1e, c2e, cN;
public:
	PSO_TVACPSO(){}
	PSO_TVACPSO(float _Ws, float _We, float _c1s, float _c2s, float  _c1e, float  _c2e, float  _cN) : Ws(_Ws), We(_We), c1s(_c1s), c2s(_c2s), c1e(_c1e), c2e(_c2e), cN(_cN)
	{
	}
	void setParameters(float& _Ws, float& _We, float& _c1s, float& _c2s, float&  _c1e, float&  _c2e, float&  _cN)
	{
		_Ws = Ws; _We = We; _c1s = c1s, _c2s = c2s; _c1e = c1e, _c2e = c2e, _cN = cN;
	}
};

#endif