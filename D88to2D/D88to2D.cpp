// D88to2D.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "D88to2D.h"
#include "D88to2DDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD88to2DApp

BEGIN_MESSAGE_MAP(CD88to2DApp, CWinApp)
	//{{AFX_MSG_MAP(CD88to2DApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD88to2DApp クラスの構築

CD88to2DApp::CD88to2DApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CD88to2DApp オブジェクト

CD88to2DApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CD88to2DApp クラスの初期化

BOOL CD88to2DApp::InitInstance()
{
	// 標準的な初期化処理

	CD88to2DDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}
