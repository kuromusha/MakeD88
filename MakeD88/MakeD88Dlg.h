// MakeD88Dlg.h : ヘッダー ファイル
//

#if !defined(AFX_MAKED88DLG_H__DFE4BB8B_31EA_4B13_AE6A_4B46EEDDF41D__INCLUDED_)
#define AFX_MAKED88DLG_H__DFE4BB8B_31EA_4B13_AE6A_4B46EEDDF41D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMakeD88Dlg ダイアログ

class CMakeD88Dlg : public CDialog
{
// 構築
public:
	CMakeD88Dlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CMakeD88Dlg)
	enum { IDD = IDD_MAKED88_DIALOG };
	CEdit	m_edit3;
	CEdit	m_edit2;
	CEdit	m_edit1;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMakeD88Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// テキストのデコード May 13, 2000
	BOOL Conv10to8(unsigned char[10], unsigned char[8]);

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CMakeD88Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MAKED88DLG_H__DFE4BB8B_31EA_4B13_AE6A_4B46EEDDF41D__INCLUDED_)
