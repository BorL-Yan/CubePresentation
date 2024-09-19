
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
: m_xPos(50), m_bRight(true), m_angle(0.0f)
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
public:
	float x, y, z;
	Vec3();
	Vec3(float X, float Y, float Z) :x(X), y(Y), z(Z) {};
};


class Cube : Vec3 {
public:
	Vec3 cube[6][4];

	float Centre;
	Vec3 AxisX;
	Vec3 AxisY;
	Vec3 AxisZ;

	float zBufer[6];


	Cube();


	void GlobalRotation(Vec3 angle) {
		for (int i = 0; i < 6; i++) {
			float CordinateZ[2];
			for (int j = 0; j < 4; j++)
			{
				Rotation(cube[i][j], angle);
				if (i % 2 == 0) {
					CordinateZ[i / 2] = cube[i][j].z;
				}
			}
			zBufer[i] = (CordinateZ[0] + CordinateZ[1]) / 2;
		}
	}

	void Rotation(Vec3& rotation, Vec3 angle) {
		RotationX(rotation, angle.x);
		RotationY(rotation, angle.y);
		RotationZ(rotation, angle.z);
	}
	void RotationX(Vec3& rotating, float angle) {
		rotating = Vec3(rotating.x,
			rotating.y * (float)cos(angle * Pi / 180.0f) - rotating.z * (float)sin(angle * Pi / 180.0f),
			rotating.z * (float)cos(angle * Pi / 180.0f) + rotating.y * (float)sin(angle * Pi / 180.0f));

	}

	void RotationY(Vec3& rotating, float angle) {
		rotating = Vec3(rotating.x * (float)cos(angle * Pi / 180.0f) + rotating.z * (float)sin(angle * Pi / 180.0f),
			rotating.y,
			rotating.z * (float)cos(angle * Pi / 180.0f) - rotating.x * (float)sin(angle * Pi / 180.0f));
	}

	void RotationZ(Vec3& rotating, float angle) {
		rotating = Vec3(rotating.x * (float)cos(angle * Pi / 180.0f) - rotating.y * (float)sin(angle * Pi / 180.0f),
			rotating.y * (float)cos(angle * Pi / 180.0f) + rotating.x * (float)sin(angle * Pi / 180.0f),
			rotating.z);
	}

	void GetFace(CPoint &face) {

	}
};

Cube::Cube() {
	for (int j = 0; j < 6; j++)
	{
		Vec3 Vertecs[4]{
			{-1,-1,1},
			{ 1,-1,1},
			{ 1, 1,1},
			{-1, 1,1}
		};
		for (int k = 0; k < 4; k++) {
			// index :: 0 - Up, 1 - Down, 2 - Left, 3 - Front, 4 - Right, 5 - Back
			switch (j)
			{
			case 0:
				Rotation(Vertecs[k], Vec3(90,0,0));
				break;

			case 1:
				Rotation(Vertecs[k], Vec3( - 90, 0, 0));
				break;

			case 2:
				Rotation(Vertecs[k], Vec3(0, -90, 0));
				break;

			case 3:
				Rotation(Vertecs[k], Vec3(0, 0, 0));
				break;
			case 4:
				Rotation(Vertecs[k], Vec3(0, 90, 0));
				break;

			case 5:
				Rotation(Vertecs[k], Vec3(0, 180, 0));
				break;
			}
			Cube::cube[j][k] = Vertecs[j];
		}
	}
}

	/*
	void CreatCube() {
		for (int j = 0; j < 6; j++)
		{
			Vec3 Vertecs[4]{
				{-1,-1,1},
				{ 1,-1,1},
				{ 1, 1,1},
				{-1, 1,1}
			};

			for (int k = 0; k < 4; k++) {
				// index :: 0 - Up, 1 - Down, 2 - Left, 3 - Front, 4 - Right, 5 - Back
				switch (j)
				{
				case 0:
					Rotation(Vertecs[k], 90, 0, 0);
					break;

				case 1:
					Rotation(Vertecs[k], -90, 0, 0);
					break;

				case 2:
					Rotation(Vertecs[k], 0, -90, 0);
					break;

				case 3:
					Rotation(Vertecs[k], 0, 0, 0);
					break;
				case 4:
					Rotation(Vertecs[k], 0, 90, 0);
					break;

				case 5:
					Rotation(Vertecs[k], 0, 180, 0);
					break;
				}
				//Rotation(Vertecs[k], 0, 90, 0);
			}
		}
	}
	*/

	/*
	void RotationX(Vec3 &rotating ,float angle){
		rotating = Vec3(rotating.x,
			rotating.y * (float)cos(angle * Pi / 180.0f) - rotating.z * (float)sin(angle * Pi / 180.0f),
			rotating.z * (float)cos(angle * Pi / 180.0f) + rotating.y * (float)sin(angle * Pi / 180.0f));

	}

	void RotationY(Vec3 &rotating, float angle) {
		rotating = Vec3(rotating.x * (float)cos(angle * Pi / 180.0f) + rotating.z * (float)sin(angle * Pi / 180.0f),
					rotating.y,
					rotating.z * (float)cos(angle * Pi / 180.0f) - rotating.x * (float)sin(angle * Pi / 180.0f));
	}

	void RotationZ(Vec3 &rotating, float angle) {
		rotating = Vec3(rotating.x * (float)cos(angle * Pi / 180.0f) - rotating.y * (float)sin(angle * Pi / 180.0f),
					rotating.y * (float)cos(angle * Pi / 180.0f) + rotating.x * (float)sin(angle * Pi / 180.0f),
					rotating.z);
	}

	static void Rotation(Vec3 &rotation,float x, float y, float z) {
		RotationX(rotation, x);
		RotationY(rotation, y);
		RotationZ(rotation, z);
	}
	*/

	/*
	Vec3 CentreDistance(Vec3 vertecs, float distanseCentre, byte face) {
		switch (face)
		{
			case 0:
				vertecs.y -= distanseCentre;
				break;
			case 1:
				vertecs.y += distanseCentre;
				break;
			case 2:
				vertecs.x -= distanseCentre;
				break;
			case 3:
				vertecs.z += distanseCentre;
				break;
			case 4:
				vertecs.x += distanseCentre;
				break;
			case 5:
				vertecs.z -= distanseCentre;
				break;
		}
		return vertecs;
	}
	*/


void BackGround(CDC* pDC, int Height, int Width) { //{
	CPen pen(PS_SOLID, 0, RGB(4, 13, 18));
	CBrush brush(RGB(34, 40, 49));

	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	CRect background(0, 0, Height, Width);

	pDC->Rectangle(&background);

	pDC->SelectObject(pOldPen);
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
	BackGround(pDC, clientRect.Width(), clientRect.Height());
	CPoint CubeFaces[6][4];
	Cube cube;
	float zBufer[6] = {0};

	int size = 100; //m_xPos;
	/*
	for (int j = 0; j < 6; j++)
	{
		Vec3 Vertecs[4]{
			{-1,-1,1},
			{ 1,-1,1},
			{ 1, 1,1},
			{-1, 1,1}
		};

		for (int k = 0; k < 4; k++) {
			// index :: 0 - Up, 1 - Down, 2 - Left, 3 - Front, 4 - Right, 5 - Back
			switch (j)
			{
			case 0:
				cube.Rotation(Vertecs[k], 90, 0, 0);
				break;

			case 1:
				cube.Rotation(Vertecs[k], -90, 0, 0);
				break;

			case 2:
				cube.Rotation(Vertecs[k], 0, -90, 0);
				break;

			case 3:
				cube.Rotation(Vertecs[k], 0, 0, 0);
				break;
			case 4:
				cube.Rotation(Vertecs[k], 0, 90, 0);
				break;

			case 5:
				cube.Rotation(Vertecs[k], 0, 180, 0);
				break;
			}
			//Rotation(Vertecs[k], 0, 90, 0);
		}

		float CoordinateZ[2] = { 0 };
		for (int i = 0; i < 4; ++i)
		{
			//Global
			Rotation(Vertecs[i], 0, m_angleY, 0);

			//Local
			Rotation(Vertecs[i], -20, 0, 0);

			//Vec3 vertecs =  CentreDistance(Vertecs[i], 1, j);

			if (i % 2 == 0) {
				CoordinateZ[i/2] = Vertecs[i].z;
			}
			int distance = 5;
			float z = 1 / (distance - Vertecs[i].z);

			Vec3(Vertecs[i].x * z, Vertecs[i].y * z, Vertecs[i].z);

			CubeFaces[j][i].x = static_cast<int>(Vertecs[i].x * size) + centerX;
			CubeFaces[j][i].y = static_cast<int>(Vertecs[i].y * size) + centerY;

		}
		
		zBufer[j] = (CoordinateZ[0] + CoordinateZ[1]) / 2;
	}*/

	cube.GlobalRotation(Vec3(m_angle,0,0));
	
	cube.GetFace(CubeFaces);


	
	CPen pen(PS_SOLID, 2, RGB(238, 238, 238));
	CBrush brush(RGB(118, 171, 174));

	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	
	for (int i = 0; i < 5; i++) {

		for (int j = i + 1; j < 6; j++)
		{
			if (zBufer[i] > zBufer[j]) {

				std::swap(zBufer[i], zBufer[j]);
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

	m_angle += 3.0f ;
	if (m_angle == 360.f) m_angle = 0.0f;

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
