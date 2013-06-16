// 2DtoD88.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "2DtoD88.h"
#include "2DtoD88Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy2DtoD88App

BEGIN_MESSAGE_MAP(CMy2DtoD88App, CWinApp)
	//{{AFX_MSG_MAP(CMy2DtoD88App)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy2DtoD88App クラスの構築

CMy2DtoD88App::CMy2DtoD88App()
{
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CMy2DtoD88App オブジェクト

CMy2DtoD88App theApp;

/////////////////////////////////////////////////////////////////////////////
// CMy2DtoD88App クラスの初期化

BOOL CMy2DtoD88App::InitInstance()
{
	// 標準的な初期化処理

#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
#endif

	CMy2DtoD88Dlg dlg;
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
