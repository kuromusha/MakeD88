// D88to2D.h : D88TO2D アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_D88TO2D_H__EE0291C1_5D4B_43E5_BC48_33427435356B__INCLUDED_)
#define AFX_D88TO2D_H__EE0291C1_5D4B_43E5_BC48_33427435356B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CD88to2DApp:
// このクラスの動作の定義に関しては D88to2D.cpp ファイルを参照してください。
//

class CD88to2DApp : public CWinApp
{
public:
	CD88to2DApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CD88to2DApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CD88to2DApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_D88TO2D_H__EE0291C1_5D4B_43E5_BC48_33427435356B__INCLUDED_)
