
// MFCDrawBoxView.h : interface of the CMFCDrawBoxView class
//
#pragma once
#include "Cube.h"

class CMFCDrawBoxView : public CView, public Cube
{
protected:
	CString m_ClassName;
	BYTE m_Dragging;
	CPoint m_PointOld;
	CPoint m_PointOrigin;

	int m_xPos;
	BYTE m_bRight;
	float m_angle;

	UINT_PTR m_nTimer;

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

};

#ifndef _DEBUG  // debug version in MFCDrawBoxView.cpp
inline CMFCDrawBoxDoc* CMFCDrawBoxView::GetDocument() const
   { return reinterpret_cast<CMFCDrawBoxDoc*>(m_pDocument); }
#endif

