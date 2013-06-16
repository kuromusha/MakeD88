// MakeD88.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "MakeD88.h"
#include "MakeD88Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMakeD88App

BEGIN_MESSAGE_MAP(CMakeD88App, CWinApp)
	//{{AFX_MSG_MAP(CMakeD88App)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMakeD88App クラスの構築

CMakeD88App::CMakeD88App()
{
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CMakeD88App オブジェクト

CMakeD88App theApp;

/////////////////////////////////////////////////////////////////////////////
// CMakeD88App クラスの初期化

BOOL CMakeD88App::InitInstance()
{
	// 標準的な初期化処理

	CMakeD88Dlg dlg;
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
