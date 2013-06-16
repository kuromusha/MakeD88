// 2DtoD88Dlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "2DtoD88.h"
#include "2DtoD88Dlg.h"
#include "direct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ

/////////////////////////////////////////////////////////////////////////////
// CMy2DtoD88Dlg ダイアログ

CMy2DtoD88Dlg::CMy2DtoD88Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy2DtoD88Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy2DtoD88Dlg)
		// メモ: この位置に ClassWizard によってメンバの初期化が追加されます。
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy2DtoD88Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy2DtoD88Dlg)
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy2DtoD88Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy2DtoD88Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy2DtoD88Dlg メッセージ ハンドラ

BOOL CMy2DtoD88Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	// タイトルのデフォルト値 Apr 16, 2000
	m_edit3.SetWindowText("X1DISK");

	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CMy2DtoD88Dlg::OnPaint() 
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

HCURSOR CMy2DtoD88Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// 変換メイン Apr 16, 2000
void CMy2DtoD88Dlg::OnOK() 
{
	struct {
		char title[16];			// タイトル（余白は0x00で埋める）
		char dmy[10];			// 0x00*10
		short attr;				// ライトプロテクトなら0x10
		long next_disk;			// 次のディスク位置
		long next_track[84];	// 次のトラック位置
	} diskhd;

	struct sechd_type {
		char C;			// シリンダ番号
		char H;			// ヘッド番号
		char R;			// セクタ番号
		char N;			// セクタサイズ
		short secn;		// セクタ数
		char dmy[8];	// 0x00*10
		short size;		// セクタサイズ(bytes)
	} sechd[84];

	int sec_begin[84];

	CString in_file, out_file, title;
	m_edit1.GetWindowText(in_file);
	m_edit2.GetWindowText(out_file);
	m_edit3.GetWindowText(title);
	if(in_file == "" || out_file == ""){
		AfxMessageBox("ファイル名を指定してください。");
		return;
	}
	int len=title.GetLength();
	if(len == 0){
		AfxMessageBox("タイトルを何か指定してください。");
		return;
	}
	if(len > 16){
		AfxMessageBox("タイトルは16文字までです。");
		return;
	}
	FILE *fp;
	unsigned char* buf=0;
	long size;
	if((fp=fopen(in_file, "rb")) != NULL){
		fseek(fp, 0, SEEK_END);
		size=ftell(fp);
		fseek(fp, 0, SEEK_SET);
		if(size != 0 && (buf=new unsigned char[size]) != 0){
			size_t ret=fread(buf, 1, size, fp);
			if((long)ret != size){
				delete [] buf;
				buf=0;
			}
		}
		fclose(fp);
	}
	if(buf == 0){
		AfxMessageBox("入力ファイルが読めませんでした。");
		return;
	}
	if((fp=fopen(out_file, "wb")) != NULL){
		memset(&diskhd, 0, sizeof(diskhd));
		memcpy(&diskhd, (LPCTSTR)title, len);
		// トラック位置の計算
		int start=0x100, ptr=0, track=0, last_disk=0x2b0;
		// 通常の2Dフォーマットも変換できるようにする Jul 23, 2000
		if(size == 256*16*80){
			track=80;
			for(int i=0; i<80; i++){
				memset(&sechd[i], 0, sizeof(sechd_type));
				sechd[i].C=i>>1;
				sechd[i].H=i & 1;
				sechd[i].N=1;
				sechd[i].secn=16;
				sechd[i].size=256;
				sec_begin[i]=256*16*i;
				diskhd.next_track[i]=last_disk;
				last_disk+=(256+sizeof(sechd_type))*16;
			}
		} else
		while(strncmp((char*)buf+ptr, "X12D", 4) != 0 && buf[ptr] != 0xff){
			memset(&sechd[track], 0, sizeof(sechd_type));
			sechd[track].C=track>>1;
			sechd[track].H=track & 1;
			sechd[track].N=buf[ptr]>>4;
			// セクタサイズ(bytes)の設定 May 14, 2000
			sechd[track].size=128<<sechd[track].N;
			int sec_size=128<<sechd[track].N;
			sec_begin[track]=((buf[ptr]&0xf)<<16)|(buf[ptr+1]<<8)|buf[ptr+2];
			ptr+=3;
			int sec_end;
			if(strncmp((char*)buf+ptr, "X12D", 4) != 0 && buf[ptr] != 0xff)
				sec_end=((buf[ptr]&0xf)<<16)|(buf[ptr+1]<<8)|buf[ptr+2];
			else
				sec_end=size;
			sechd[track].secn=(sec_end-sec_begin[track])/sec_size;
			if(sec_end-sec_begin[track] != sec_size*sechd[track].secn){
				CString out;
				out.Format("セクタサイズが一定でないトラック(%d)が存在します。\n出力は不完全になります。", track);
				AfxMessageBox(out);
				break;
			}
			int track_size=sec_end-sec_begin[track]+(sechd[track].secn<<4);
			diskhd.next_track[track++]=last_disk;
			last_disk+=track_size;
		}
		diskhd.next_disk=last_disk;
		fwrite(&diskhd, sizeof(diskhd), 1, fp);
		for(int i=0; i<0x140; i++)
			fputc(0, fp);
		for(i=0; i<track; i++)
			for(int j=0; j<sechd[i].secn; j++){
				sechd[i].R=j+1;
				fwrite(&sechd[i], sizeof(sechd_type), 1, fp);
				int sec_size=128<<sechd[i].N;
				fwrite(&buf[sec_begin[i]+sec_size*j], 1, sec_size, fp);
			}
		fclose(fp);
		AfxMessageBox("D88フォーマットのファイルを出力しました。");
	}
	delete [] buf;
}

// 入力ファイル名の指定 Apr 16, 2000
void CMy2DtoD88Dlg::OnButton1() 
{
	CFileDialog dlg(TRUE);
	char path[_MAX_DIR];
	if(_getcwd(path, _MAX_DIR) == NULL)
		*path=0;
	dlg.m_ofn.lpstrInitialDir=path;
	if(dlg.DoModal() == IDOK)
		m_edit1.SetWindowText(dlg.GetPathName());
}

// 出力ファイル名の指定 Apr 16, 2000
void CMy2DtoD88Dlg::OnButton2() 
{
	CFileDialog dlg(FALSE);
	char path[_MAX_DIR];
	if(_getcwd(path, _MAX_DIR) == NULL)
		*path=0;
	dlg.m_ofn.lpstrInitialDir=path;
	if(dlg.DoModal() == IDOK)
		m_edit2.SetWindowText(dlg.GetPathName());
}
