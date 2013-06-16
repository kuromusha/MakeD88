// 2DtoD88Dlg.h : ヘッダー ファイル
//

#if !defined(AFX_2DTOD88DLG_H__78CBAF6B_A91B_48E8_9F61_FD341346DF74__INCLUDED_)
#define AFX_2DTOD88DLG_H__78CBAF6B_A91B_48E8_9F61_FD341346DF74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy2DtoD88Dlg ダイアログ

class CMy2DtoD88Dlg : public CDialog
{
// 構築
public:
	CMy2DtoD88Dlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CMy2DtoD88Dlg)
	enum { IDD = IDD_MY2DTOD88_DIALOG };
	CEdit	m_edit3;
	CEdit	m_edit2;
	CEdit	m_edit1;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CMy2DtoD88Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CMy2DtoD88Dlg)
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

#endif // !defined(AFX_2DTOD88DLG_H__78CBAF6B_A91B_48E8_9F61_FD341346DF74__INCLUDED_)
