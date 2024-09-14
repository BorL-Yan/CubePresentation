
// MFCDrawBoxView.cpp : implementation of the CMFCDrawBoxView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCDrawBox.h"
#endif

#include "MFCDrawBoxDoc.h"
#include "MFCDrawBoxView.h"
#include "iostream"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

#define Pi 3.14

// CMFCDrawBoxView

IMPLEMENT_DYNCREATE(CMFCDrawBoxView, CView)

BEGIN_MESSAGE_MAP(CMFCDrawBoxView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_LBUTTONDOWN()
//	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONUP()

	ON_WM_TIMER()

	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CMFCDrawBoxView construction/destruction

CMFCDrawBoxView::CMFCDrawBoxView() noexcept
: m_xPos(50), m_bRight(true), m_angleY(0.0f)
{
	// TODO: add construction code here
	m_Dragging = false;
	m_HCross = AfxGetApp()->LoadStandardCursor(IDC_CROSS);

	m_backGroundColor = RGB(0, 0, 0);

}

CMFCDrawBoxView::~CMFCDrawBoxView()
{
	if (m_nTimer != 0)
	{	
		//KillTimer(m_nTimer);
	}
}

BOOL CMFCDrawBoxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}


struct Vec3 {
	float x, y, z;
	Vec3(float X, float Y, float Z) :x(X), y(Y), z(Z) {};
};



Vec3 RotationX(Vec3 rotating ,float angle) {
	return Vec3(rotating.x,
				rotating.y * (float)cos(angle * Pi / 180.0f) - rotating.z * (float)sin(angle * Pi / 180.0f),
				rotating.z * (float)cos(angle * Pi / 180.0f) + rotating.y * (float)sin(angle * Pi / 180.0f));
}

Vec3 RotationY(Vec3 rotating, float angle) {
	return Vec3(rotating.x * (float)cos(angle * Pi / 180.0f) + rotating.z * (float)sin(angle * Pi / 180.0f),
				rotating.y,
				rotating.z * (float)cos(angle * Pi / 180.0f) - rotating.x * (float)sin(angle * Pi / 180.0f));
}

Vec3 RotationZ(Vec3 rotating, float angle) {
	return Vec3(rotating.x * (float)cos(angle * Pi / 180.0f) - rotating.y * (float)sin(angle * Pi / 180.0f),
				rotating.y * (float)cos(angle * Pi / 180.0f) + rotating.x * (float)sin(angle * Pi / 180.0f),
				rotating.z);
}


void CMFCDrawBoxView::OnDraw(CDC* pDC)
{
	CMFCDrawBoxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect clientRect;
	GetClientRect(&clientRect);
	int centerX = clientRect.Width() / 2;// +m_xPos;
	int centerY = clientRect.Height() / 2;// +m_xPos;

	CPoint CubeFaces[6][4];
	float zDistance[6] = {0};

	int size = 200; //m_xPos;
	for (int j = 0; j < 6; j++)
	{
		Vec3 Vertecs[4]{
			{-1,-1,1},
			{ 1,-1,1},
			{ 1, 1,1},
			{-1, 1,1}
		};

		for (int k = 0; k < 4; k++){
			// index :: 0 - Up, 1 - Down, 2 - Left, 3 - Front, 4 - Right, 5 - Back
			switch (j)
			{
			case 0:
				Vertecs[k] = RotationX(Vertecs[k], 10);
				Vertecs[k] = RotationX(Vertecs[k], 90);
				break;

			case 1:
				Vertecs[k] = RotationX(Vertecs[k], 10);
				Vertecs[k] = RotationX(Vertecs[k], -90);
				break;

			case 2:
				Vertecs[k] = RotationZ(Vertecs[k], -10);
				Vertecs[k] = RotationY(Vertecs[k], -90);
				break;

			case 3:
				Vertecs[k] = RotationX(Vertecs[k], 10);
				Vertecs[k] = RotationY(Vertecs[k], 0);
				break;

			case 4:
				Vertecs[k] = RotationZ(Vertecs[k], 10);
				Vertecs[k] = RotationY(Vertecs[k], 90);
				break;

			case 5:
				Vertecs[k] = RotationX(Vertecs[k], -10);
				Vertecs[k] = RotationY(Vertecs[k], 180);
				break;

			}
			Vertecs[k] = RotationX(Vertecs[k], 30);
		}
		float CoordinateZ[2] = { 0 };

		for (int i = 0; i < 4; ++i)
		{
			int rotationCentr = 0;

			Vec3 rotation = RotationY(Vec3(Vertecs[i].x + rotationCentr, Vertecs[i].y + rotationCentr, Vertecs[i].z), m_angleY);

			if (i % 2 == 0) {
				CoordinateZ[i/2] = rotation.z;
			}
			int distance = 5;
			float z = 1 / (distance - rotation.z);

			rotation = Vec3(rotation.x * z, rotation.y * z, 0);

			CubeFaces[j][i].x = static_cast<int>(rotation.x * size) + centerX;
			CubeFaces[j][i].y = static_cast<int>(rotation.y * size) + centerY;

		}

		zDistance[j] = (CoordinateZ[0] + CoordinateZ[1]) / 2;
	}

	
	CPen pen(PS_SOLID, 5, RGB(255, 0, 0)); 
	CBrush brush(RGB(0, 0, 0));    

	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	
	for (int i = 0; i < 5; i++) {

		for (int j = i + 1; j < 6; j++)
		{
			if (zDistance[i] > zDistance[j]) {

				std::swap(zDistance[i], zDistance[j]);
				std::swap(CubeFaces[i], CubeFaces[j]);
			}
		}
	}

	for (int i = 0; i < 6; i++)
	{
		pDC->Polygon(CubeFaces[i], 4);
	}

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}


void CMFCDrawBoxView::OnTimer(UINT_PTR nIDEvent) {

#ifndef Position

	if (m_bRight) 
		m_xPos += 2;
	else
		m_xPos -= 2;

	if (m_xPos >= 150)
		m_bRight = false;
	else if(m_xPos <= 0)
		m_bRight = true;

#endif // !Position


#ifndef Rotation

	m_angleY += 1.0f;
	if (m_angleY == 360.f) m_angleY = 0.0f;

#endif // !Rotation

	Invalidate();
	CView::OnTimer(nIDEvent);
}


// CMFCDrawBoxView printing

BOOL CMFCDrawBoxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCDrawBoxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCDrawBoxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMFCDrawBoxView diagnostics

#ifdef _DEBUG
void CMFCDrawBoxView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDrawBoxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDrawBoxDoc* CMFCDrawBoxView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDrawBoxDoc)));
	return (CMFCDrawBoxDoc*)m_pDocument;
}
#endif //_DEBUG



void CMFCDrawBoxView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// Устанавливаем таймер с интервалом 60 мс
	m_nTimer = SetTimer(1, 60, NULL);
	if (m_nTimer == 0)
	{
		AfxMessageBox(_T("Error, Timer not Instantiet!!!"));
	}
	// TODO: Add your specialized code here and/or call the base class
}



HBRUSH CMFCDrawBoxView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{

	return (HBRUSH)GetStockObject(m_backGroundColor);
	
}
