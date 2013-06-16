// D88to2DDlg.h : ヘッダー ファイル
//

#if !defined(AFX_D88TO2DDLG_H__F869A75B_1E02_4B73_B42B_58101C261D51__INCLUDED_)
#define AFX_D88TO2DDLG_H__F869A75B_1E02_4B73_B42B_58101C261D51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CD88to2DDlg ダイアログ

class CD88to2DDlg : public CDialog
{
// 構築
public:
	CD88to2DDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CD88to2DDlg)
	enum { IDD = IDD_D88TO2D_DIALOG };
	CEdit	m_edit2;
	CEdit	m_edit1;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CD88to2DDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CD88to2DDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_D88TO2DDLG_H__F869A75B_1E02_4B73_B42B_58101C261D51__INCLUDED_)
