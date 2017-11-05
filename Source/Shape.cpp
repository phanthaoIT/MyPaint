#include "Shape.h"
#include "Header.h"


RECT* CShape::getPoint()
{
	RECT* toado = new RECT();
	toado->left = this->batdau.x;
	toado->top = this->batdau.y;
	toado->right = this->ketthuc.x;
	toado->bottom = this->ketthuc.y;
	return toado;
}

void CShape::setPen(HPEN pen)
{
	this->pen = pen;
}
void CShape::setBrush(HBRUSH brush)
{
	this->brush = brush;
}
HPEN CShape::getpen()
{
	return this->pen;
}
HBRUSH CShape::getbrush()
{
	return this->brush;
}

CShape* CLine::Create()
{
	return new CLine;
}
void CLine::Draw(HDC hdc)
{
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	MoveToEx(hdc, batdau.x, batdau.y, NULL);
	LineTo(hdc, ketthuc.x, ketthuc.y);
}
void CLine::SetData(POINT bd, POINT kt, HPEN pen, HBRUSH brush)
{
	this->batdau = bd;
	this->ketthuc = kt;
	this->pen = pen;
	this->brush = brush;
}
int CLine::gettype()
{
	return line;
}

CShape* CRectangle::Create()
{
	return new CRectangle;
}
void CRectangle::Draw(HDC hdc)
{
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	Rectangle(hdc, batdau.x, batdau.y, ketthuc.x, ketthuc.y);
}
void CRectangle::SetData(POINT bd, POINT kt, HPEN pen, HBRUSH brush)
{
	this->batdau = bd;
	this->ketthuc = kt;
	this->pen = pen;
	this->brush = brush;
}
int CRectangle::gettype()
{
	return rectangle;
}

CShape* CEllipse::Create()
{
	return new CEllipse;
}
void CEllipse::Draw(HDC hdc)
{
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	Ellipse(hdc, batdau.x, batdau.y, ketthuc.x, ketthuc.y);
}
void CEllipse::SetData(POINT bd, POINT kt, HPEN pen,HBRUSH brush)
{
	this->batdau = bd;
	this->ketthuc = kt;
	this->pen = pen;
	this->brush = brush;
}

int CEllipse::gettype()
{
	return ellipse;
}
