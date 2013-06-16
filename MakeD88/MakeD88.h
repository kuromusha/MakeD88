// MakeD88.h : MAKED88 アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_MAKED88_H__97BF328C_D0EF_477A_9725_A3392FC08728__INCLUDED_)
#define AFX_MAKED88_H__97BF328C_D0EF_477A_9725_A3392FC08728__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CMakeD88App:
// このクラスの動作の定義に関しては MakeD88.cpp ファイルを参照してください。
//

class CMakeD88App : public CWinApp
{
public:
	CMakeD88App();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMakeD88App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CMakeD88App)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MAKED88_H__97BF328C_D0EF_477A_9725_A3392FC08728__INCLUDED_)
