// D88to2DDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "D88to2D.h"
#include "D88to2DDlg.h"
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CD88to2DDlg ダイアログ

CD88to2DDlg::CD88to2DDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CD88to2DDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CD88to2DDlg)
		// メモ: この位置に ClassWizard によってメンバの初期化が追加されます。
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CD88to2DDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CD88to2DDlg)
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CD88to2DDlg, CDialog)
	//{{AFX_MSG_MAP(CD88to2DDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CD88to2DDlg メッセージ ハンドラ

BOOL CD88to2DDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CD88to2DDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CD88to2DDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CD88to2DDlg::OnOK() 
{
	CString in_file, out_file;
	m_edit1.GetWindowText(in_file);
	m_edit2.GetWindowText(out_file);
	if(in_file == "" || out_file == ""){
		AfxMessageBox("ファイル名を指定してください。");
		return;
	}
	FILE *fp;
	if((fp=fopen(in_file, "rb")) != NULL){
		struct {
			char title[16];			// タイトル（余白は0x00で埋める）
			char dmy[10];			// 0x00*10
			char protect;			// ライトプロテクトなら0x10
			char fd_type;			// 2Dなら0x00, 2HDなら0x20
			long next_disk;			// 次のディスク位置
			long next_track[164];	// 次のトラック位置
		} diskhd;

		struct sechd_type {
			char C;			// シリンダ番号
			char H;			// ヘッド番号
			char R;			// セクタ番号
			char N;			// セクタサイズ
			short secn;		// セクタ数
			char dmy1[2];	// 0x00*2
			unsigned char stat;	// 正常なら0x00, CRCエラーなら0xa0
			char dmy2[3];	// 0x00*3
			unsigned char ID_stat;	// IDリード時のリターン値
			unsigned char SEC_stat;	// セクタリード時のリターン値
			short size;		// セクタサイズ(bytes)
		} sechd;

		char disk[256*16*80];
		int ok=0;
		fseek(fp, 0, SEEK_END);
		long size=ftell(fp);
		if(size >= sizeof(diskhd)){
			fseek(fp, 0, SEEK_SET);
			fread(&diskhd, sizeof(diskhd), 1, fp);
			if(diskhd.next_disk == size && size == sizeof(diskhd)+(256+sizeof(sechd))*16*80){
				for(int i=0; i<80; i++){
					if(diskhd.next_track[i] != (int)(sizeof(diskhd)+(256+sizeof(sechd))*16*i))
						break;
					for(int j=1; j<=16; j++){
						fread(&sechd, sizeof(sechd), 1, fp);
						if(sechd.C != i/2
						|| sechd.H != (i & 1)
						|| sechd.R != j
						|| sechd.N != 1
						|| sechd.secn != 16
						|| sechd.stat != 0
						|| sechd.ID_stat != 0
						|| sechd.SEC_stat != 0
						|| sechd.size != 256){
							j=-1;
							break;
						}
						fread(disk+i*256*16+(j-1)*256, sizeof(char), 256, fp);
					}
					if(j < 0)
						break;
				}
				if(i == 80)
					ok=1;
			}
		}
		fclose(fp);
		if(ok != 0){
			if((fp=fopen(out_file, "wb")) != NULL){
				fwrite(disk, sizeof(char), 256*16*80, fp);
				fclose(fp);
				AfxMessageBox("2Dフォーマットのファイルを出力しました。");
			} else
				AfxMessageBox("出力ファイルがオープンできませんでした。");
		} else
			AfxMessageBox("入力ファイルは2Dフォーマットに変換できません。");
	} else
		AfxMessageBox("入力ファイルがオープンできませんでした。");
}

void CD88to2DDlg::OnButton1() 
{
	CFileDialog dlg(TRUE);
	char path[_MAX_DIR];
	if(_getcwd(path, _MAX_DIR) == NULL)
		*path=0;
	dlg.m_ofn.lpstrInitialDir=path;
	if(dlg.DoModal() == IDOK)
		m_edit1.SetWindowText(dlg.GetPathName());
}

void CD88to2DDlg::OnButton2() 
{
	CFileDialog dlg(FALSE);
	char path[_MAX_DIR];
	if(_getcwd(path, _MAX_DIR) == NULL)
		*path=0;
	dlg.m_ofn.lpstrInitialDir=path;
	if(dlg.DoModal() == IDOK)
		m_edit2.SetWindowText(dlg.GetPathName());
}
