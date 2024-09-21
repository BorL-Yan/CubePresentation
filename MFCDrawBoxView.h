
// MFCDrawBoxView.h : interface of the CMFCDrawBoxView class
//
#pragma once
#define Pi 3.14

class CMFCDrawBoxView : public CView//, Cube
{
protected:
	CString m_ClassName;
	BYTE m_Dragging;
	HCURSOR m_HCross;
	CPoint m_PointOld;
	CPoint m_PointOrigin;

	int m_xPos;
	BYTE m_bRight;
	float m_angle;

	UINT_PTR m_nTimer;
	COLORREF m_backGroundColor;

	Cube cube;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//afx_msg void Update();
	//afx_msg void OnDraw(CDC* pDC);


protected: // create from serialization only
	CMFCDrawBoxView() noexcept;
	DECLARE_DYNCREATE(CMFCDrawBoxView)

// Attributes
public:
	CMFCDrawBoxDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCDrawBoxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();

	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

struct Vector2 {
	float x, y;
	Vector2(int x = 0, int y = 0) :x(x), y(y) {};
};

struct Vector3 {

	float x, y, z;

	Vector3(float X = 0, float Y = 0, float Z = 0) :x(X), y(Y), z(Z) {};

	Vector3 operator+(const Vector3& v) const {
		return { x + v.x, y + v.y, z + v.z };
	}

	Vector3 operator-(const Vector3& v) const {
		return { x - v.x, y - v.y, z - v.z };
	}

	Vector3 operator*(float scalar) const {
		return { x * scalar, y * scalar, z * scalar };
	}

};

struct Matrix4x4 {
	float m[4][4];

	Matrix4x4() {
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] = (i == j) ? 1.0f : 0.0f;
	}

	Vector3 multiply(const Vector3& v) const {
		return {
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
		};
	}

	static Matrix4x4 rotation(float angle, const Vector3& axis) {
		Matrix4x4 rot;
		float cosTheta = cos(angle);
		float sinTheta = sin(angle);
		float oneMinusCos = 1.0f - cosTheta;

		rot.m[0][0] = cosTheta + axis.x * axis.x * oneMinusCos;
		rot.m[0][1] = axis.x * axis.y * oneMinusCos - axis.z * sinTheta;
		rot.m[0][2] = axis.x * axis.z * oneMinusCos + axis.y * sinTheta;

		rot.m[1][0] = axis.y * axis.x * oneMinusCos + axis.z * sinTheta;
		rot.m[1][1] = cosTheta + axis.y * axis.y * oneMinusCos;
		rot.m[1][2] = axis.y * axis.z * oneMinusCos - axis.x * sinTheta;

		rot.m[2][0] = axis.z * axis.x * oneMinusCos - axis.y * sinTheta;
		rot.m[2][1] = axis.z * axis.y * oneMinusCos + axis.x * sinTheta;
		rot.m[2][2] = cosTheta + axis.z * axis.z * oneMinusCos;

		return rot;
	}
};

struct Plane {
	Vector3 vertecs[4];

	Plane() {}

	Plane(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4) {
		vertecs[0] = v1;
		vertecs[1] = v2;
		vertecs[2] = v3;
		vertecs[3] = v4;
	}

	void rotate(float angle, const Vector3& axis) {
		Matrix4x4 rotMatrix = Matrix4x4::rotation(angle, axis);
		for (int i = 0; i < 4; ++i) {
			vertecs[i] = rotMatrix.multiply(vertecs[i]);
		}
	}

};


struct Cube  {
	Plane faces[4];

	Vector3 Center;
	Vector3 AxisX;
	Vector3 AxisY;
	Vector3 AxisZ;

	float zBufer[6];

	int CubeSize;
	//float distance = 0;

	//Cube();

	//void operator()(Vector3 center = (0, 0, 0), Vector3 localRotation = (0, 0, 0), int size = 0);

	//Cube();

	//~Cube();

	//
	//	void GlobalRotation(Vector3 angle) {
	//		for (int i = 0; i < 6; i++) {
	//			float CordinateZ[2];
	//			for (int j = 0; j < 4; j++)
	//			{
	//				Rotation(faces[i].vertecs[j], angle);
	//				if (i % 2 == 0) {
	//					CordinateZ[i / 2] = faces[i].vertecs[j].z;
	//				}
	//			}
	//			zBufer[i] = (CordinateZ[0] + CordinateZ[1]) / 2;
	//		}
	//	}
	//	
	//void DebugeCube(Vector2* point, int index);

	//void Sort();
	////

#ifndef Rotation


	/*void Rotation(Vector3& rotation, Vector3 angle) {
		RotationX(rotation, angle.x);
		RotationY(rotation, angle.y);
		RotationZ(rotation, angle.z);
	}
	static void RotationX(Vector3& rotating, float angle) {
		rotating = Vector3(rotating.x,
			rotating.y * (float)cos(angle * Pi / 180.0f) - rotating.z * (float)sin(angle * Pi / 180.0f),
			rotating.z * (float)cos(angle * Pi / 180.0f) + rotating.y * (float)sin(angle * Pi / 180.0f));

	}

	static void RotationY(Vector3& rotating, float angle) {
		rotating = Vector3(rotating.x * (float)cos(angle * Pi / 180.0f) + rotating.z * (float)sin(angle * Pi / 180.0f),
			rotating.y,
			rotating.z * (float)cos(angle * Pi / 180.0f) - rotating.x * (float)sin(angle * Pi / 180.0f));
	}

	static void RotationZ(Vector3& rotating, float angle) {
		rotating = Vector3(rotating.x * (float)cos(angle * Pi / 180.0f) - rotating.y * (float)sin(angle * Pi / 180.0f),
			rotating.y * (float)cos(angle * Pi / 180.0f) + rotating.x * (float)sin(angle * Pi / 180.0f),
			rotating.z);
	}*/

#endif // !Rotation

};


#ifndef _DEBUG  // debug version in MFCDrawBoxView.cpp
inline CMFCDrawBoxDoc* CMFCDrawBoxView::GetDocument() const
   { return reinterpret_cast<CMFCDrawBoxDoc*>(m_pDocument); }
#endif

