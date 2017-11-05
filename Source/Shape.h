#pragma once
#include <Windows.h>

class CShape
{
protected:
	POINT batdau;
	POINT ketthuc;
	HPEN pen;
	HBRUSH brush;
public:
	virtual CShape* Create()=0;
	virtual void Draw(HDC) = 0;
	virtual void SetData(POINT, POINT,HPEN,HBRUSH) = 0;
	void setPen(HPEN);
	void setBrush(HBRUSH);
	virtual int gettype() = 0;
	RECT* getPoint();
	HPEN getpen();
	HBRUSH getbrush();
};
// đường thẳng
class CLine : public CShape
{
public:
	CShape* Create();
	void Draw(HDC);
	void SetData(POINT bd, POINT kt,HPEN,HBRUSH);
	int gettype();
};
// HCN
class CRectangle :public CShape
{
public:
	CShape* Create();
	void Draw(HDC);
	void SetData(POINT bd, POINT kt,HPEN, HBRUSH);
	int gettype();
};
//elip
class CEllipse :public CShape
{
public:
	CShape* Create();
	void Draw(HDC);
	void SetData(POINT bd, POINT kt, HPEN, HBRUSH);
	int gettype();
};

