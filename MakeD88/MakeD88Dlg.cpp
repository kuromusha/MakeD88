// MakeD88Dlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MakeD88.h"
#include "MakeD88Dlg.h"
#include "direct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMakeD88Dlg ダイアログ

CMakeD88Dlg::CMakeD88Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMakeD88Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMakeD88Dlg)
	//}}AFX_DATA_INIT
}

void CMakeD88Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMakeD88Dlg)
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMakeD88Dlg, CDialog)
	//{{AFX_MSG_MAP(CMakeD88Dlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMakeD88Dlg メッセージ ハンドラ

BOOL CMakeD88Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	m_edit3.SetWindowText("X1DISK");
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// 入力ファイル名の指定 May 13, 2000
void CMakeD88Dlg::OnButton1() 
{
	CFileDialog dlg(TRUE);
	char path[_MAX_DIR];
	if(_getcwd(path, _MAX_DIR) == NULL)
		*path=0;
	dlg.m_ofn.lpstrInitialDir=path;
	if(dlg.DoModal() == IDOK)
		m_edit1.SetWindowText(dlg.GetPathName());
}

// 出力ファイル名の指定 May 13, 2000
void CMakeD88Dlg::OnButton2() 
{
	CFileDialog dlg(FALSE);
	char path[_MAX_DIR];
	if(_getcwd(path, _MAX_DIR) == NULL)
		*path=0;
	dlg.m_ofn.lpstrInitialDir=path;
	if(dlg.DoModal() == IDOK)
		m_edit2.SetWindowText(dlg.GetPathName());
}

void CMakeD88Dlg::OnOK() 
{
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
	FILE *fp, *fp2=NULL;
	if((fp=fopen(in_file, "r")) != NULL){
		unsigned char buf[80];
		int mode=0, d88=0, track=0, side=0, sector=1, output=0;
		// 2D D88作成用 May 15, 2000
		int d88mode=0, d88count, data_size=0, sec_num=0, get=0, get_size=0, d88_size[164];
		unsigned char *d88_track[164], id[320], *tmp_track=0;
		sechd_type d88sechd[32];
		for(int i=0; i<164; i++){
			d88_track[i]=0;
			d88_size[i]=0;
		}
		CString text;
		while(fgets((char*)buf, 80, fp) != NULL){
			if(mode == 0){
				if(strncmp((char*)buf, "===X1:", 4) == 0){
					if((fp2=fopen(out_file, "wb")) == NULL){
						AfxMessageBox("出力ファイルがオープンできませんでした。");
						break;
					}
					mode++;
					if(strncmp((char*)buf+6, "2HD", 3) == 0)
						d88++;
					else
					if(strncmp((char*)buf+6, "D88", 3) == 0)
						d88--;
					if(d88 != 0){
						memset(&diskhd, 0, sizeof(diskhd));
						memset(&sechd, 0, sizeof(sechd_type));
						memcpy(&diskhd, (LPCTSTR)title, len);
						if(d88 > 0){
							diskhd.fd_type=0x20;
							diskhd.next_disk=sizeof(diskhd)+26*77*2*(256+16);
							for(int i=0; i<154; i++)
								diskhd.next_track[i]=sizeof(diskhd)+26*(256+16)*i;
							sechd.N=1;
							sechd.secn=26;
							sechd.size=256;
						}
					}
				}
			} else
			if(mode == 1){
				mode++;
				if(d88 != 0){
					if(strncmp((char*)buf, "WRITE PROTECT:ON", 16) == 0)
						diskhd.protect=0x10;
					if(d88 > 0)
						fwrite(&diskhd, sizeof(diskhd), 1, fp2);
				}
			} else {
				if(strncmp((char*)buf, "===END", 6) == 0)
					break;
				if(d88 == 0){
					if(strlen((char*)buf) != 65){
						AfxMessageBox("入力データが異常です。");
						break;
					}
					text+=CString((char*)buf, 64);
					unsigned char out[8];
					while(text.GetLength() >= 10){
						if(Conv10to8((unsigned char*)((LPCTSTR)text), out) == FALSE){
							AfxMessageBox("チェックサムエラーです。");
							break;
						}
						fwrite(out, 1, 8, fp2);
						text=text.Mid(10);
						output+=8;
					}
					if(text.GetLength() >= 10)
						break;
				} else
				if(d88 > 0){
					if(strlen((char*)buf) != 65){
						AfxMessageBox("入力データが異常です。");
						break;
					}
					text+=CString((char*)buf, 64);
					unsigned char out[8];
					while(text.GetLength() >= 10){
						if(output == 0){
							sechd.C=track;
							sechd.H=side;
							sechd.R=sector;
							fwrite(&sechd, sizeof(sechd_type), 1, fp2);
							sector++;
							if(sector > 26){
								sector=1;
								side++;
								if(side >= 2){
									side=0;
									track++;
								}
							}
						}
						if(Conv10to8((unsigned char*)((LPCTSTR)text), out) == FALSE){
							AfxMessageBox("チェックサムエラーです。");
							break;
						}
						fwrite(out, 1, 8, fp2);
						text=text.Mid(10);
						output+=8;
						if(output >= 256)
							output-=256;
					}
					if(text.GetLength() >= 10)
						break;
				} else {
					int i;
					unsigned char out[8];
					switch(d88mode){
					case 0:
						if(strncmp((char*)buf, "==TRACK,SIDE:", 13) == 0){
							track=atoi((char*)buf+13);
							char* ptr=strchr((char*)buf+13, ',');
							if(ptr == NULL){
								track=-1;
								break;
							}
							side=atoi(ptr+1);
							d88mode++;
							d88count=0;
							for(i=0; i<32; i++)
								memset(&d88sechd[i], 0, sizeof(sechd_type));
						}
						break;
					case 1:
						if(strlen((char*)buf) != 51){
							track=-1;
							break;
						}
						for(i=0; i<5; i++){
							if(Conv10to8((unsigned char*)buf+i*10, out) == FALSE){
								AfxMessageBox("チェックサムエラーです。");
								break;
							}
							memcpy(id+d88count, out, 8);
							d88count+=8;
						}
						if(d88count >= 320){
							d88mode++;
							int offset=0, offset2=7*32, start=0x4000, end=0x4000;
							for(sec_num=0; sec_num<32; sec_num++){
								if(id[offset] == 0xff)
									break;
								d88sechd[sec_num].C=id[offset++];
								d88sechd[sec_num].H=id[offset++];
								d88sechd[sec_num].R=id[offset++];
								d88sechd[sec_num].N=id[offset];
								offset+=3;
								d88sechd[sec_num].ID_stat=id[offset++];
								end=id[offset2]+(id[offset2+1]<<8);
								offset2+=2;
								d88sechd[sec_num].size=end-start;
								start=end;
								d88sechd[sec_num].SEC_stat=id[offset2++];
								if((d88sechd[sec_num].ID_stat & 8) != 0
								|| (d88sechd[sec_num].SEC_stat & 8) != 0)
									d88sechd[sec_num].stat=0xa0;
							}
							for(int i=0; i<sec_num; i++)
								d88sechd[i].secn=sec_num;
							get_size=data_size=end-0x4000;
							if((get_size & 0xff) != 0){
								get_size>>=8;
								get_size++;
								get_size<<=8;
							}
							get=output=0;
							text="";
							if(data_size != 0){
								tmp_track=new unsigned char[data_size];
								if(tmp_track == 0){
									track=-2;
									break;
								}
							} else {
								// セクタのみ Jul 9, 2000
								d88mode=0;
								d88_size[track*2+side]=sec_num*16;
								d88_track[track*2+side]=new unsigned char[d88_size[track*2+side]];
								if(d88_track[track*2+side] == 0){
									track=-2;
									break;
								}
								int ptr=0;
								for(int i=0; i<sec_num; i++){
									memcpy(d88_track[track*2+side]+ptr, &d88sechd[i], 16);
									ptr+=16;
								}
							}
						}
						break;
					default:
						if(strlen((char*)buf) != 65){
							track=-1;
							break;
						}
						text+=CString((char*)buf, 64);
						while(text.GetLength() >= 10){
							get+=8;
							if(output < data_size){
								if(Conv10to8((unsigned char*)((LPCTSTR)text), out) == FALSE){
									track=-3;
									break;
								}
								if(data_size-output >= 8){
									memcpy(tmp_track+output, out, 8);
									output+=8;
								} else {
									memcpy(tmp_track+output, out, data_size-output);
									output=data_size;
								}
								if(output >= data_size){
									d88_size[track*2+side]=data_size+sec_num*16;
									d88_track[track*2+side]=new unsigned char[d88_size[track*2+side]];
									if(d88_track[track*2+side] == 0){
										track=-2;
										break;
									}
									int ptr=0, ptr2=0;
									for(int i=0; i<sec_num; i++){
										memcpy(d88_track[track*2+side]+ptr, &d88sechd[i], 16);
										ptr+=16;
										memcpy(d88_track[track*2+side]+ptr, tmp_track+ptr2, d88sechd[i].size);
										ptr+=d88sechd[i].size;
										ptr2+=d88sechd[i].size;
									}
									delete [] tmp_track;
									tmp_track=0;
								}
							}
							text=text.Mid(10);
						}
						if(track < 0)
							break;
						if(get >= get_size)
							d88mode=0;
					}
					if(track == -1){
						AfxMessageBox("入力データが異常です。");
						break;
					}
					if(track == -2){
						AfxMessageBox("メモリ不足です。");
						break;
					}
					if(track == -3){
						AfxMessageBox("チェックサムエラーです。");
						break;
					}
				}
			}
		}
		if(d88 == 0){
			if(output == 256*16*80)
				AfxMessageBox("2Dフォーマットのファイルを出力しました。");
			else
				AfxMessageBox("2Dフォーマットの不完全なファイルを出力しました。");
		} else
		if(d88 > 0){
			if(track == 77 && side == 0 && sector == 1)
				AfxMessageBox("2HDのD88フォーマットのファイルを出力しました。");
			else
				AfxMessageBox("2HDのD88フォーマットの不完全なファイルを出力しました。");
		} else {
			int ptr=sizeof(diskhd);
			for(int i=0; i<164; i++)
				if(d88_track[i] != 0){
					diskhd.next_track[i]=ptr;
					ptr+=d88_size[i];
				}
			diskhd.next_disk=ptr;
			fwrite(&diskhd, sizeof(diskhd), 1, fp2);
			for(i=0; i<164; i++)
				if(d88_track[i] != 0)
					fwrite(d88_track[i], 1, d88_size[i], fp2);
			if(track >= 0)
				AfxMessageBox("2DのD88フォーマットのファイルを出力しました。");
			else
				AfxMessageBox("2DのD88フォーマットの不完全なファイルを出力しました。");
		}
		for(i=0; i<164; i++)
			if(d88_track[i] != 0)
				delete [] d88_track[i];
		fclose(fp);
		if(fp2 != NULL)
			fclose(fp2);
		if(tmp_track != 0)
			delete [] tmp_track;
	} else {
		AfxMessageBox("入力ファイルがオープンできませんでした。");
		return;
	}
}

// テキストのデコード May 13, 2000
BOOL CMakeD88Dlg::Conv10to8(unsigned char in[10], unsigned char out[8])
{
	unsigned char tmp[10];
	for(int i=0; i<10; i++){
		tmp[i]=in[i]-32;
		if(tmp[i] >= 0x80)
			tmp[i]-=50;
	}
	int sum=0;
	for(i=0; i<8; i++){
		unsigned char c=tmp[i];
		if(i != 0){
			if((tmp[8] & (0x80 >> i)) != 0)
				c|=0x80;
		} else {
			if((tmp[9] & 1) != 0)
				c|=0x80;
		}
		out[i]=c;
		sum+=c;
	}
	return (sum & 0x3f) == (tmp[9] >> 1);
}
