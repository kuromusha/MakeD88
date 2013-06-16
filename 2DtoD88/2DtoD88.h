// 2DtoD88.h : 2DTOD88 アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_2DTOD88_H__CA28D4B2_CF46_4437_81D4_245700D899AC__INCLUDED_)
#define AFX_2DTOD88_H__CA28D4B2_CF46_4437_81D4_245700D899AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CMy2DtoD88App:
// このクラスの動作の定義に関しては 2DtoD88.cpp ファイルを参照してください。
//

class CMy2DtoD88App : public CWinApp
{
public:
	CMy2DtoD88App();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMy2DtoD88App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CMy2DtoD88App)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_2DTOD88_H__CA28D4B2_CF46_4437_81D4_245700D899AC__INCLUDED_)
