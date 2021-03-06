
// shootStockDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "shootStock.h"
#include "shootStockDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <iostream>
#include <iterator>
#include <locale>
#include <string>
#include <sstream>

#define  COMMISSION	0.00015
#define  COMMISSION1	0.0015
#define  COMMISSION2	0.003
// {조회 키,		리얼 키,	행, 열, 타입,			색 변경, 정렬, 앞 문자, 뒷 문자}
const stGRID lstFID[] = 
{
	
	{L"종목코드",	L"9001",	-1,	0,		DT_NONE,					FALSE,	DT_CENTER,	L"",	L""},
	{L"신용구분",	L"917",		-1,	1,		DT_NONE,					FALSE,	DT_CENTER,	L"",	L""},
	{L"종목명",		L"302",		-1,	2,		DT_NONE,					FALSE,	DT_CENTER,	L"",	L""},
	{L"현재가",		L"10",		-1,	3,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
	{L"보유수량",	L"930",		-1,	4,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
	{L"평가금액",	L"-1",		-1,	5,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
	{L"평가손익",	L"-1",		-1,	6,		DT_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
	{L"수익률",		L"-1",		-1,	7,		DT_NONE,					FALSE,	DT_RIGHT,		L"",	L"%"},
	{L"매입금액",	L"932",		-1,	8,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
	{L"현재가",		L"10",		-1,	9,		DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(계산용으로 숨김)
	{L"보유수량",	L"930",		-1,	10,	DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(계산용으로 숨김)
	{L"매입금액",	L"932",		-1,	11,	DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(계산용으로 숨김)
	{L"평가금액",	L"-1",		-1,	12,	DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(계산용으로 숨김)
};


// {조회 키,		리얼 키,	행, 열, 타입,			색 변경, 정렬, 앞 문자, 뒷 문자}
const stGRID lstOPT10001[] = 
{
	{L"종목코드",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"종목명",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	/////////////////////////////////////
	// 현재가 그리드
	{L"현재가",			L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"대비기호",	L"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,L"",L""}, 
	{L"전일대비",	L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"등락율",		L"12",	0,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"거래량",		L"13",	0,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"거래대비",	L"30",	0,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	/////////////////////////////////////
	// 주식기본정보 그리드 1행
	{L"250최고",		L"-1",	0,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"250최고가대비율",L"-1",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"250최고가일",	L"-1",	0,	3,	DT_DATE,		FALSE,	DT_CENTER,L"",L""}, 
	{L"액면가",		L"-1",	0,	5,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L" 원"}, 
	{L"시가총액",	L"-1",	0,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L" 억"}, 
	{L"EPS",			L"-1",	0,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	/////////////////////////////////////
	// 주식기본정보 그리드 2행
	{L"250최저",		L"-1",	1,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"250최저가대비율",L"-1",	1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"250최저가일",	L"-1",	1,	3,	DT_DATE,		FALSE,	DT_CENTER,L"",L""}, 
	{L"자본금",		L"-1",	1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L" 억"}, 
	{L"대용가",		L"-1",	1,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"PER",			L"-1",	1,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	/////////////////////////////////////
	// 주식기본정보 그리드 3행
	{L"외인소진률",	L"-1",	2,	1,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L"%"}, 
	{L"상장주식",	L"-1",	2,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L" 천"}, 
	{L"신용비율",	L"-1",	2,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L"%"}, 
	{L"결산월",		L"-1",	2,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L"월"}, 
	/////////////////////////////////////
	// 주식기본정보 그리드 4행
	{L"연중최고",	L"-1",	3,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"BPS",			L"-1",	3,	9,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L""}, 
	/////////////////////////////////////
	// 주식기본정보 그리드 5행
	{L"연중최저",	L"-1",	4,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"PBR",			L"-1",	4,	9,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L""}, 
};


// {조회 키,		리얼 키,	행, 열, 타입,			색 변경, 정렬, 앞 문자, 뒷 문자}
const stGRID lstOPT10012[] = 
{
	{L"주문수량",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"주문가격",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	/////////////////////////////////////
	// 현재가 그리드
	{L"미체결수량",			L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"주문구분",	L"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,L"",L""}, 
	{L"주문상태",	L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"등락율",		L"12",	0,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"거래량",		L"13",	0,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"거래대비",	L"30",	0,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	/////////////////////////////////////
	// 주식기본정보 그리드 1행

};

// {조회 키,		리얼 키,	행, 열, 타입,			색 변경, 정렬, 앞 문자, 뒷 문자}
const stGRID lstOPW00013[] = 
{
	{L"금일재사용가능금액",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"현금금액",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	/////////////////////////////////////
	// 현재가 그리드
	{L"현금증거금",			L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"사용가능현금",	L"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,L"",L""}, 
	{L"미수금",	L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	/////////////////////////////////////
	// 주식기본정보 그리드 1행

};

// {조회 키,		리얼 키,	행, 열, 타입,			색 변경, 정렬, 앞 문자, 뒷 문자}
const stGRID lstOPW00018[] = 
{
	{L"종목번호",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"종목명",				L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"평가손익",			L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"수익률",				L"25",	0,	1,	DT_ZERO_NUMBER,		TRUE,	DT_CENTER,L"",L""}, 
	{L"매입가",				L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"보유수량",			L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"현재가",				L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	/////////////////////////////////////
	// 주식기본정보 그리드 1행

};

class MoneyOutputter
{
public:
  MoneyOutputter(const char* const locale_name = "US") : 
      loc(locale_name), 
      output(std::use_facet<std::money_put<char> >(loc)),
      iterator(os)
  {

    os.imbue(loc);
    os.setf(std::ios_base::showbase);
  }

  std::string as_string(double value)
  {
    os.str("");  // clear string
    output.put(iterator, false, os, ' ', value * 100.0);
    return os.str();
  }

private:
  std::locale loc;
  const std::money_put<char>& output;
  std::ostringstream os;
  std::ostreambuf_iterator<char, std::char_traits<char> > iterator;
};

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

//*******************************************************************/
// BEGIN_EVENTSINK_MAP
//*******************************************************************/
BEGIN_EVENTSINK_MAP(CshootStockDlg, CDialogEx)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 1, OnReceiveTrDataKhopenapictrl,	VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 2, OnReceiveRealDataKhopenapictrl,	VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 3, OnReceiveMsgKhopenapictrl,		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR )
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 4, OnReceiveChejanData,				VTS_BSTR VTS_I4 VTS_BSTR)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 5, OnEventConnect,					VTS_I4)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 7, OnReceiveRealCondition,			VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 8, OnReceiveTrCondition,			VTS_BSTR VTS_BSTR VTS_BSTR VTS_I2 VTS_I2)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 9, OnReceiveConditionVer,			VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()
// CshootStockDlg 대화 상자




CshootStockDlg::CshootStockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CshootStockDlg::IDD, pParent)
	, m_staticCode(_T("종목코드"))
	, m_staticName(_T("종목명"))
	, m_staticPrice(_T("현재가"))
	, m_boardJongmokCode(_T(""))
	, m_sellPercentage(2)
	, m_FuckPercentage(0)
	, isRunning(false)
	//, m_boughtPrice(0)
	//, m_checkedCount(0)
	//, m_checkedCode(_T(""))
	//, m_boughtCount(0)
	, isManual(false)
	, isStockMarketOpen(false)
	, m_staticHigh(_T(""))
	, m_staticLow(_T(""))
	, m_staticSales(_T(""))
	, m_staticProfit(_T(""))
{
	m_nRet = 0;
	m_nScrN0 = 0;
	m_nCount				= 0;
	m_bNextFlag			= FALSE;
	m_AccNo = L"";
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CshootStockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KHOPENAPICTRL, theApp.m_khOpenApi);
	DDX_Control(pDX, IDC_LIST1, m_logList);
	DDX_Control(pDX, IDC_TAB1, m_TabControl);
	DDX_Control(pDX, IDC_DEAL_LIST, m_dealList);
	DDX_Text(pDX, IDC_STATIC_CODE, m_staticCode);
	DDX_Text(pDX, IDC_STATIC_NAME, m_staticName);
	DDX_Text(pDX, IDC_STATIC_PRICE, m_staticPrice);
	DDX_Control(pDX, IDC_CONCLUDE_LIST, m_ConcludeList);
	DDX_Text(pDX, IDC_STATIC_HIGH, m_staticHigh);
	DDX_Text(pDX, IDC_STATIC_LOW, m_staticLow);
	DDX_Text(pDX, IDC_STATIC_SHELL, m_staticSales);
	DDX_Text(pDX, IDC_STATIC_INCOME, m_staticProfit);
}

BEGIN_MESSAGE_MAP(CshootStockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_UPDATESTATUSBAR, &CshootStockDlg::OnUpdatestatusbar)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CshootStockDlg::OnSelchangeTab)

	ON_COMMAND(ID_LIST_SEARCH, &CshootStockDlg::OnListSearch)
	
	ON_NOTIFY(NM_DBLCLK, IDC_DEAL_LIST, &CshootStockDlg::OnNMDblclkDealList)
END_MESSAGE_MAP()


IMPLEMENT_SERIAL(CSubject, CObject, VERSIONABLE_SCHEMA | 2)
void CSubject::Serialize(CArchive& ar){

}
void CSubject::AssertValid() const{

}
// CshootStockDlg 메시지 처리기

BOOL CshootStockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	InitStatusBar();
	InitlogList();
	InitTabControl();
	InitDealList();
	InitConcludeList();

	CFont fnt;
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 18;
	lf.lfWeight = FW_BOLD;
	::lstrcpy(lf.lfFaceName, (LPCWSTR)"Tahoma");
	fnt.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC_CODE)->SetFont(&fnt);
	GetDlgItem(IDC_STATIC_NAME)->SetFont(&fnt);
	GetDlgItem(IDC_STATIC_PRICE)->SetFont(&fnt);
	fnt.Detach();

	::ZeroMemory(&lf, sizeof(lf));
	lf.lfHeight = 15;
	lf.lfWeight = FW_BOLD;
	::lstrcpy(lf.lfFaceName, (LPCWSTR)"Tahoma");
	fnt.CreateFontIndirect(&lf);
	GetDlgItem(IDC_STATIC_HIGH)->SetFont(&fnt);
	GetDlgItem(IDC_STATIC_LOW)->SetFont(&fnt);
	GetDlgItem(IDC_STATIC_SHELL)->SetFont(&fnt);
	GetDlgItem(IDC_STATIC_INCOME)->SetFont(&fnt);
	fnt.Detach();



	theApp.m_khOpenApi.CommConnect();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CshootStockDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CshootStockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CshootStockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CshootStockDlg::MainOnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg){
	CString strRQName = sRQName;
	if (strRQName == _T("실시간미체결요청"))		// 주식기본정보 설정
	{
		m_ConcludeList.DeleteAllItems();
		CString strData;
		int nFieldCnt = 25;//sizeof(lstFID) / sizeof(*lstFID);		// 전체크기 / 원소크기 = 원소개수

		strRQName = _T("실시간미체결");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);	//데이터 건수
		m_nCount = nCnt;	//데이터 건수에 그리드 헤더 추가
		CString strIndex= L"";
		for (i = 0; i < nCnt; i++)
		{

			strIndex.Format(L"%d", i);

			int dwitem = 0;
			int dwCount = m_ConcludeList.GetItemCount();




			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"주문번호");strData.Trim();
			CString tmpOrderNo = strData;

			dwitem = m_ConcludeList.InsertItem(dwCount,strData,0);
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"종목코드");strData.Trim();
			CString tmpCode = strData;
			m_ConcludeList.SetItemText(i,1,strData );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"종목명");strData.Trim();
			m_ConcludeList.SetItemText(i,2,strData );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"주문구분");strData.Trim();
			m_ConcludeList.SetItemText(i,3,strData );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"주문가격");strData.Trim();
			m_ConcludeList.SetItemText(i,4,_wtoi(strData) );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"미체결수량");strData.Trim();
			m_ConcludeList.SetItemText(i,5,_wtoi(strData) );

			// 잔고 리스트에 넣어 일관매도 할때 빨리 함
			m_mapOrderNo.SetAt(tmpCode,tmpOrderNo);

			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"매매구분");strData.Trim();
			m_ConcludeList.SetItemText(i,6,strData );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"현재가");strData.Trim();
			m_ConcludeList.SetItemText(i,7,_wtoi(strData) );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"시간");strData.Trim();
			strData.Format(L"%s:%s:%s",strData.Mid(0,2),strData.Mid(2,2),strData.Mid(4,2));
			m_ConcludeList.SetItemText(i,8,strData );
		}

	}
	
	
	if (strRQName == _T("주식기본정보요청"))			// 계좌수익률//if (!lstrcmp(sRealType, L"주식체결"))	// 주식체결
	{

		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10001) / sizeof(*lstOPT10001);		// 전체크기 / 원소크기 = 원소개수

		strRQName = _T("주식기본정보");




		arrData.RemoveAll();
		for (int nIdx = 0; nIdx < nFieldCnt; nIdx++)
		{
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, lstOPT10001[nIdx].strKey);	strData.Trim();
			if(nIdx== 0){
				if(strData == m_boardJongmokCode){
					//strData = theApp.m_khOpenApi.GetCommRealData(strData, 10);	strData.Trim(); //현재가
					
					m_staticCode = strData;
					
					m_staticName =   theApp.m_khOpenApi.GetMasterCodeName(strData);
					strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"현재가");	strData.Trim();
					m_staticPrice = strData;
					strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"250최고");	strData.Trim();
					m_staticHigh = strData;
					m_staticHigh = L"50주최고: "+m_staticHigh.Mid(1,m_staticHigh.GetLength() -1);
					strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"250최저");	strData.Trim();
					m_staticLow = strData;
					m_staticLow = L"50주최저: "+m_staticLow.Mid(1,m_staticLow.GetLength() -1);
					strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"매출액");	strData.Trim();
					m_staticSales = L"매출액: "+strData;
					strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"영업이익");	strData.Trim();
					m_staticProfit = L"영업이익: "+strData;
			
					//TraceOutputW(strData);
					UpdateData(FALSE);
				}
			}
			arrData.Add(strData);
		}
	}

	if (strRQName == _T("계좌평가잔고내역요청"))			// 계좌수익률//if (!lstrcmp(sRealType, L"주식체결"))	// 주식체결
	{
		//m_checkedSubject.RemoveAll();
		CString strData;
		int nFieldCnt = 22;//sizeof(lstFID) / sizeof(*lstFID);		// 전체크기 / 원소크기 = 원소개수

		strRQName = _T("계좌평가잔고내역");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);	//데이터 건수
		m_nCount = nCnt;	//데이터 건수에 그리드 헤더 추가
		CString strIndex= L"";
		m_mapJongCode.RemoveAll();
		for (i = 0; i < nCnt; i++)
		{
			
			strIndex.Format(L"%d", i);

			int dwitem = 0;
	
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"종목번호");strData.Trim();
			m_mapJongCode.SetAt(strData.Mid(1,6), strIndex);

			CString tmpJomgmok = strData.Mid(1,6);
			//m_grdKwanSim.SetRowHeight(i, 20);		// 행의 높이 설정
			//m_grdKwanSim.SetItemText(i, 0, strCode);
			int dwCount = m_dealList.GetItemCount();

			dwitem = m_dealList.InsertItem(dwCount,strData.Mid(1,6),0);
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"종목명");strData.Trim();
			m_dealList.SetItemText(i,1,strData );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"평가손익");strData.Trim();
			m_dealList.SetItemText(i,2,_wtoi(strData) );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"수익률(%)");strData.Trim();
			m_dealList.SetItemText(i,3,_wtof(strData) );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"매입가");strData.Trim();
			m_dealList.SetItemText(i,4,_wtoi(strData) );

			int nBuyPrice = _wtoi(strData);

			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"보유수량");strData.Trim();
			m_dealList.SetItemText(i,5,_wtoi(strData) );

			// 잔고 리스트에 넣어 일관매도 할때 빨리 함
			m_OrderList.SetAt(tmpJomgmok,strData);

			CSubject * subject = new CSubject(nBuyPrice);
			subject->set_count(_wtoi(strData));
			subject->set_status(false);
			
		/*	subject->set_price(nBuyPrice);*/

			/************************************************************************/
			/*                                                                            */
			/************************************************************************/
			isRunning = true; //프로그램이 시작되면  현재 거래중인 종목이 있으면 바로 손절 감시 작동 
			m_checkedSubject.SetAt(tmpJomgmok,subject);

			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"현재가");strData.Trim();
			m_dealList.SetItemText(i,6,_wtoi(strData) );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"수수료합");strData.Trim();
			m_dealList.SetItemText(i,7,_wtoi(strData) );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"세금");strData.Trim();
			m_dealList.SetItemText(i,8,_wtoi(strData) );
		}

		CString strRQName = _T("관심종목"), strCodeList, strCode;
		long  nCodeCount(0);

		for (int nRow = 0; nRow < m_nCount; nRow++)
		{
			nCodeCount++;
			strCode = m_dealList.GetItemText(nRow, 0);
			strCode.Trim();
			strCode + ";";
			strCodeList += strCode ;
			//종목코드 = 전문 조회할 종목코드
			theApp.m_khOpenApi.SetInputValue(L"종목코드"	,  strCode);
			theApp.m_khOpenApi.CommRqData( L"주식기본정보요청",  L"OPT10001", 0, m_strScrNo); 
			//
			
		}

		long lRet = theApp.m_khOpenApi.CommKwRqData(strCodeList, 0, nCodeCount, 0, strRQName, m_strScrNo);
		if (!lRet)
		{
			return;
		}
	}
	////end
}



//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : 조회 응답 처리
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		switch (_wtoi(strScrType))
		{
		case 0:		// 메인창
			{
				((CshootStockDlg *)pWnd)->MainOnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);
			}
			break;
		case 1:
			{
				
				((CBuyList *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			}
			break;
		case 2:
			{

				((CCurPrice *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			}
			break;
		case 3:
			{

				((CTopPrice *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			}
			break;
		case 4:
			{

				((CDailyReport *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			}
			break;
		case 5:
			{

				((CChartView *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			}
			break;
		case 6:
			{

				((CIncome *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			}
			break;
		}
	}
}

//*******************************************************************/
//! Function Name : OnReceiveMsgKhopenapictrl
//! Function      : 조회 에러 처리
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CString strRQ = sRQName;
	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		CString strData;
		strData.Format(_T("[%s] [%s] 오류"), sRQName, sTrCode);

		CString strErrMsg = sMsg;
		if(strErrMsg.Find(_T("비밀번호")) != -1 && strErrMsg.Find(_T("오류")) != -1){
			::MessageBox(m_hWnd,_T("비밀번호 오류! 5번 오류시 큰일남,제대로 입력하자!"),_T("비밀번호 오류!"),MB_ICONERROR);

			theApp.m_khOpenApi.KOA_Functions(_T("ShowAccountWindow"), _T(""));

			theApp.m_khOpenApi.SetInputValue(L"계좌번호", m_AccNo);

			long lRet = theApp.m_khOpenApi.CommRqData(L"계좌평가잔고내역요청", L"OPW00018", 0, m_strScrNo);
			if (!theApp.IsError(lRet))
			{
			}
			//return;
		}

		if(!theApp.g_is_password_success && strErrMsg.Find(_T("조회")) != -1 && strErrMsg.Find(_T("완료")) != -1){
			theApp.g_is_password_success = true;

			m_buyList.GetDataSearch();
			//수익률계산 조회 //8100875411
			//계좌번호 = 전문 조회할 보유계좌번호
			theApp.m_khOpenApi.SetInputValue(L"계좌번호", m_AccNo);

			//체결구분 = 0:체결+미체결조회, 1:미체결조회, 2:체결조회
				//SetInputValue("체결구분"	,  "1");
			theApp.m_khOpenApi.SetInputValue(L"체결구분", L"1");
			//매매구분 = 0:전체, 1:매도, 2:매수
				//SetInputValue("매매구분"	,  "");
			theApp.m_khOpenApi.SetInputValue(L"매매구분", L"0");

			LONG lRet = theApp.m_khOpenApi.CommRqData(L"실시간미체결요청", L"OPT10075", 0, m_strScrNo);
			if (!theApp.IsError(lRet))
			{
			}
		}

		CString strRQName = strRQ.Mid(4);
		switch (_wtoi(strScrType))
		{
		case 0:		// 현재가
			{
				//((CCurrentPriceDlg *)pWnd)->OnReceiveMsgKhopenapictrl(sScrNo, strRQName, sTrCode, sMsg);
				//pWnd->MessageBox(sMsg, strData, MB_ICONERROR | MB_OK);
				//+		sMsg	0x08dabe0c "[850188] 비밀번호 2회 오류, 5회 오류시 비밀번호 재등록(문의1544-9000)"	const wchar_t *
				TraceOutputW(sMsg);
			}
			break;


		}
	}
}
//*******************************************************************/
//! Function Name : OnReceiveRealDataKhopenapictrl
//! Function      : 실시간 처리
//! Param         : LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::MainOnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{

	//증거금세부내역조회요청
	CString strRealType = sRealType;
	if (strRealType == _T("주문체결"))			// 관심종목정보 설정
	{
		

	}
	if (!lstrcmp(sRealType, L"주식시세"))		// 주식시세
	{
		TraceOutputW(sRealType);
	}
	else if (!lstrcmp(sRealType, L"주식체결"))	// 주식체결
	{



		CString strIndex, strData;


		if(sJongmokCode == m_boardJongmokCode){
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, 10);	strData.Trim(); //현재가
			m_staticPrice = strData;
			m_staticCode = sJongmokCode;
			m_staticName =   theApp.m_khOpenApi.GetMasterCodeName(sJongmokCode);
			//TraceOutputW(strData);
			UpdateData(FALSE);
		}



		if(isRunning){ //손절 판단 
			CshootStockDlg* pMain =  (CshootStockDlg*)AfxGetApp()->GetMainWnd();
			CSubject *subject = new CSubject();
			if(pMain->m_checkedSubject.Lookup(sJongmokCode,(CObject*&)subject) && !subject->get_status()){
				
				strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, 10);	strData.Trim(); //현재가
				int nPrice = _wtoi(strData);
				if(nPrice < 0)
					nPrice = nPrice * -1;
				int nTmpBoughtPrice  = subject->get_price();
				if(nPrice < nTmpBoughtPrice){
					int nTemp = nTmpBoughtPrice - nPrice;
					double nPercentage = (double)nTemp / (double)nTmpBoughtPrice * 100;
					if(nPercentage > 1.5){ // 3%이상이면 손절
						
						CString strOrderNo;
						if (m_mapOrderNo.Lookup(sJongmokCode, strOrderNo))
						{
							CString strRQName = _T("주식주문"); //일단 매도 취소
							LONG lRet = theApp.m_khOpenApi.SendOrder(strRQName,m_strScrNo,m_AccNo, 4, sJongmokCode,subject->get_count(), 0, L"00",strOrderNo);
							subject->set_status(true);
							m_checkedSubject.SetAt(sJongmokCode,subject);
							//pMain->m_checkedCode = L"";
						}

					}
				}
			}
			
		}

		if (!m_mapJongCode.Lookup(sJongmokCode, strIndex))
		{
			return;
		}

		CString strCode;

		//실시간 데이터를 항목에 맞게 가져온다.
		strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, 10);	strData.Trim();
		COLORREF tempC = RGB(0,0,255);

		if (strData.GetAt(0) == '+' )	// 부호에 따라 색상변경
		{
			tempC =  RGB(255,0,0);
		}
		else if (strData.GetAt(0) == '-')	// 부호에 따라 색상변경
		{
			tempC =  RGB(0,0,255);
		}
		else
		{
			tempC =  RGB(0,0,0);
		}

		m_dealList.SetItemText(_ttoi(strIndex), 6,  theApp.ConvDataFormat(lstFID[5].nDataType, strData, lstFID[5].strBeforeData, lstFID[5].strAfterData));
		m_dealList.SetItemTextColor(_ttoi(strIndex), 6,tempC);

		CString strBuyPrice = m_dealList.GetItemText(_ttoi(strIndex),4);
		CString strBuyCount = m_dealList.GetItemText(_ttoi(strIndex),5);
		CString strfee = m_dealList.GetItemText(_ttoi(strIndex),7);
		CString strTax = m_dealList.GetItemText(_ttoi(strIndex),8);
		int nCount =  _wtoi(strBuyCount);
		int nNowPrice = _wtoi(strData);
		if( nNowPrice < 0) //if minus then convert to plus
			nNowPrice = nNowPrice * -1;
		int nTotalBought = _wtoi(strBuyPrice) *nCount;
		int nowTotalPrice = nNowPrice * nCount;

		int nProfit = nowTotalPrice - nTotalBought - _wtoi(strfee) - _wtoi(strTax);

		double nPercentageProfit = (double)nProfit / (double)nTotalBought* 100;
		CString strTemp;
		strTemp.Format(_T("%d"), nProfit);
		m_dealList.SetItemText(_ttoi(strIndex), 2,  theApp.ConvDataFormat(lstFID[6].nDataType, strTemp, lstFID[6].strBeforeData, lstFID[6].strAfterData));
		if (strTemp.GetAt(0) == '+' )	// 부호에 따라 색상변경
		{
			tempC =  RGB(255,0,0);
		}
		else if (strTemp.GetAt(0) == '-')	// 부호에 따라 색상변경
		{
			tempC =  RGB(0,0,255);
		}
		else
		{
			tempC =  RGB(0,0,0);
		}
		m_dealList.SetItemTextColor(_ttoi(strIndex), 2,tempC);
		strTemp.Format(_T("%0.2lf"), nPercentageProfit);
		m_dealList.SetItemText(_ttoi(strIndex),3,  theApp.ConvDataFormat(lstFID[7].nDataType, strTemp, lstFID[7].strBeforeData, lstFID[7].strAfterData));
		if (strTemp.GetAt(0) == '+' )	// 부호에 따라 색상변경
		{
			tempC =  RGB(255,0,0);
		}
		else if (strTemp.GetAt(0) == '-')	// 부호에 따라 색상변경
		{
			tempC =  RGB(0,0,255);
		}
		else
		{
			tempC =  RGB(0,0,0);
		}
		m_dealList.SetItemTextColor(_ttoi(strIndex), 3,tempC);

	}


	if (strRealType == _T("장시작시간"))			// 관심종목정보 설정
	{
		//TraceOutputW(L"장시작시간 메세지가 왔습니다");
		CString fmt;
		CString strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, 215);	strData.Trim(); //장운영구분 (0 장시작전,2 장종료전 3 장시작 4 ,8 장종료 9 장마감
		CString strRemainedTime = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, 214);	strData.Trim(); //예상잔여시간
		CString tradeTime = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, 20);	strData.Trim(); //체결시간 (HHMMSS);
		
		CString szHour = strRemainedTime.Mid(0,2);
		CString szMinute = strRemainedTime.Mid(2,2);
		CString szSecond = strRemainedTime.Mid(4,2);

		CString szHour1 = tradeTime.Mid(0,2);
		CString szMinute1 = tradeTime.Mid(2,2);
		CString szSecond1 = tradeTime.Mid(4,2);
		
		int nType = _wtoi(strData);
		switch(nType){
		case 0:
			fmt.Format(L"현재시간 %s:%s:%s 장시작전 %s 분 남았습니다 ",szHour1,szMinute1,szSecond1,szMinute);
			TraceOutputW(fmt);
			break;
		case 2:
			fmt.Format(L"현재시간 %s:%s:%s 장종료전 %s 분 남았습니다 ",szHour1,szMinute1,szSecond1,szMinute);
			TraceOutputW(fmt);
			break;
		case 3: //장시작이 되였습니다
			fmt.Format(L"현재시간 %s:%s:%s 장시작이 되였습니다 ",szHour1,szMinute1,szSecond1,szMinute);
			TraceOutputW(fmt);
			isStockMarketOpen = true;
			break;
		case 4:
			fmt.Format(L"현재시간 %s:%s:%s 장종료 되였습니다 ",szHour1,szMinute1,szSecond1,szMinute);
			TraceOutputW(fmt);
			break;
		case 8:
			fmt.Format(L"현재시간 %s:%s:%s 장시작이 되였습니다 %s:%s:%s 분 남았습니다 ",szHour1,szMinute1,szSecond1,szHour,szMinute,szSecond);
			TraceOutputW(fmt);
			break;
		case 9:
			fmt.Format(L"현재시간 %s:%s:%s 장마감이 되였습니다 %s:%s:%s 분 남았습니다 ",szHour1,szMinute1,szSecond1,szHour,szMinute,szSecond);
			TraceOutputW(fmt);
			break;
		default:
			TraceOutputW(L"default 장시작시간 오류  ");
			
			break;
		}
	}
}
//*******************************************************************/
//! Function Name : OnReceiveRealDataKhopenapictrl
//! Function      : 실시간 처리
//! Param         : LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CWnd *pWnd;
	CString strKey, strScrType;
	POSITION pos = m_mapScreenNum.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreenNum.GetNextAssoc(pos, strKey, strScrType);
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			switch (_wtoi(strScrType))
			{
			case 0:		// main window
				{
					//TraceOutputW(sRealType);
					this->MainOnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
					//this->onrecvrea
					
				}
				break;
			case 1:		// 관심종목
				{
					
					 ((CBuyList *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
				}
				break;
			case 2:		// 현재가
				{

					((CCurPrice *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
				}
				break;
			case 3:		// 등락률
				{

					((CTopPrice *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
				}
				break;
			case 4:		// 등락률
				{

					((CDailyReport *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
				}
				break;
			case 5:		// 등락률
				{

					((CChartView *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
				}
				break;
			case 6:		// 등락률
				{

					((CIncome *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
				}
				break;
			}
		}
	}

	// 장운영 정보 처리
	if (!lstrcmp(sRealType, L"장시작시간"))
	{
		int i;
		CString strData[3], strMsg;
		// 0: 장운영구분, 1:시간, 2:장시작 예상잔여시간
		for (i = 0; i < 3; i++)
		{
			strData[i] = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, i);	strData[i].Trim();
		}
		strMsg.Format(L"장운영구분 : %s\r\n시간 : %s\r\n예상잔여시간 : %s", strData[0], strData[1], strData[2]);

		if (_wtoi(strData[2]) == 10)
		{
			ReplyMessage(S_OK);		// SendMessage 풀림
			MessageBox(strMsg, L"장운영 정보", MB_ICONINFORMATION | MB_OK);
		}
	}
}
//*******************************************************************/
//! Function Name : OnReceiveChejanData
//! Function      : 체결잔고 실시간 처리
//! Param         : LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::MainOnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList){
	CString strGuBun(sGubun), strAccNo, strAcc;


	//OnReceiveChejanData(
	//	BSTR sGubun, // 체결구분 접수와 체결시 '0'값, 국내주식 잔고전달은 '1'값, 파생잔고 전달은 '4'
	//	LONG nItemCnt,
	//	BSTR sFIdList
	//	)

	//	주문요청후 주문접수, 체결통보, 잔고통보를 수신할 때 마다 호출되며 GetChejanData()함수를 이용해서 상세한 정보를 얻을수 있습니다.
	if(strGuBun == L"0"){//체결통보
		strAccNo	= theApp.m_khOpenApi.GetChejanData(9201);	// 체결된 종목의 계좌번호
		CString orderNo =  theApp.m_khOpenApi.GetChejanData(9201); //9203 주문번호
		CString orderStatus =  theApp.m_khOpenApi.GetChejanData(913); //913 주문상태

		TraceOutputW(orderStatus);
		if(orderStatus == L"접수"){
			
			CString strData = theApp.m_khOpenApi.GetChejanData( 907);	strData.Trim(); //매도수구분 1 매도 2 매수 이건 번호로
		
			strData = theApp.m_khOpenApi.GetChejanData( 905);	strData.Trim(); //매도수구분  매도  매수 이건 문자로
			TraceOutputW(strData + L"접수 되였씁니다");
			//if(strData = _T("-매도")){
			//	

			//	

			//	theApp.m_khOpenApi.SetInputValue(L"계좌번호", m_AccNo);

			//	//체결구분 = 0:체결+미체결조회, 1:미체결조회, 2:체결조회
			//	//SetInputValue("체결구분"	,  "1");
			//	theApp.m_khOpenApi.SetInputValue(L"체결구분", L"1");
			//	//매매구분 = 0:전체, 1:매도, 2:매수
			//	//SetInputValue("매매구분"	,  "");
			//	theApp.m_khOpenApi.SetInputValue(L"매매구분", L"0");

			//	LONG lRet = theApp.m_khOpenApi.CommRqData(L"실시간미체결요청", L"OPT10075", 0, m_strScrNo);
			//	if (!theApp.IsError(lRet))
			//	{
			//	}

			//}



			//주문접수일수도 있다 주문취소일수도 있고
		}else if(orderStatus == L"확인"){
			//TraceOutputW(L"주문취소가 확인 되였씁니다");
			CString strData = theApp.m_khOpenApi.GetChejanData( 907);	strData.Trim(); //매도수구분 1 매도 2 매수
			//strData = theApp.m_khOpenApi.GetChejanData( 913);	strData.Trim(); //매도수구분 1 매도 2 매수

			int nStatus = _wtoi(strData); // 2 미체결 매도취소가 되면 새로 시장가 팔기 손절을 위해 
			strData = theApp.m_khOpenApi.GetChejanData( 905);	strData.Trim(); //매도수구분 1 매도 2 매수
			TraceOutputW(strData + L"취소가 확인 되였씁니다");

			CString sJongmokCode =  theApp.m_khOpenApi.GetChejanData(9001); //913 주문코드
			sJongmokCode =  sJongmokCode.Mid(1,6);
			CSubject *subject = new CSubject;
			if(m_checkedSubject.Lookup(sJongmokCode,(CObject*&)subject) && !isManual){ //지정가로 걸어논 매도가 취소되면 시장가로 팔기
				CString strRQName = _T("주식주문"); //시장가로 팔기  손절
				LONG lRet = theApp.m_khOpenApi.SendOrder(strRQName,m_strScrNo,m_AccNo, 2, sJongmokCode,subject->get_count(), 0, L"03",L"");
				//m_checkedSubject.RemoveKey(sJongmokCode);

			}
			/// 매도가 취소 됬으니 미체결 다시 받아오기  그러니 까 현재 리스트에서 지워져야지
			theApp.m_khOpenApi.SetInputValue(L"계좌번호", m_AccNo);

			//체결구분 = 0:체결+미체결조회, 1:미체결조회, 2:체결조회
			//SetInputValue("체결구분"	,  "1");
			theApp.m_khOpenApi.SetInputValue(L"체결구분", L"1");
			//매매구분 = 0:전체, 1:매도, 2:매수
			//SetInputValue("매매구분"	,  "");
			theApp.m_khOpenApi.SetInputValue(L"매매구분", L"0");

			LONG lRet = theApp.m_khOpenApi.CommRqData(L"실시간미체결요청", L"OPT10075", 0, m_strScrNo);
			if (!theApp.IsError(lRet))
			{
			}
			isManual = false;

		}else if(orderStatus == L"체결"){
			//TraceOutputW(L"체결되였습니다");
			CString sJongmokCode =  theApp.m_khOpenApi.GetChejanData(9001); //913 주문코드
			sJongmokCode =  sJongmokCode.Mid(1,6);
			CString strIndex, strData,strCount,strPrice;
			CString stMarketName =   theApp.m_khOpenApi.GetMasterCodeName(sJongmokCode);
			strData = theApp.m_khOpenApi.GetChejanData( 907);	strData.Trim(); //매도수구분 1 매도 2 매수
			strCount = theApp.m_khOpenApi.GetChejanData( 911);	strData.Trim(); //체결량
			strPrice = theApp.m_khOpenApi.GetChejanData( 910);	strData.Trim(); //체결가
			CString strOrderNo = theApp.m_khOpenApi.GetChejanData( 9203);	strData.Trim(); //체결가
			m_mapOrderNo.SetAt(sJongmokCode,strOrderNo);
			CString fmt;
			if(strData == L"2")
				fmt.Format(L"매수주문이 체결되였습니다 %s 수량 = %s , 체결가 %s",stMarketName,strCount,strPrice);
			else
				fmt.Format(L"매도주문이 체결되였습니다 %s 수량 = %s , 체결가 %s",stMarketName,strCount,strPrice);


			TraceOutputW(fmt);

			int nPrice = _wtoi(strPrice);
			CSubject * subject = new CSubject(nPrice);
			if(strData == L"2"){
				isRunning = true;
				if(m_checkedSubject.Lookup(sJongmokCode,(CObject*&)subject)){
					int nTempCount = _wtoi(strCount);
					//int orgCount = subject->get_count();
					subject->set_count(nTempCount);
					

					if(subject->is_checked_all()){ //매수주문이 전부 체결이 된후에 매도주문을 건다 아니면 자꾸이상하게 부분만 지정매도가 됨
						//m_checkedCode = sJongmokCode; //체결된 종목
						//m_checkedData.SetAt(sJongmokCode,)
						subject->set_price(nPrice);
						//1000 아래는 1 씩 계산하니깐 pass 그 이상은 10 단위로 ,더 이상은 50단위로 ,더 이상은 100단위로
						nPrice = nPrice + nPrice * m_sellPercentage /100;
						if(nPrice < 10000 && nPrice > 1000){
							nPrice = nPrice - nPrice % 10 + 10;
						}else if(nPrice < 100000 && nPrice > 10000){
							nPrice = nPrice - nPrice % 50 + 50;
						}else if(nPrice < 1000000 && nPrice > 100000){
							nPrice = nPrice - nPrice % 100 + 100;
						}
						//int sellPrice = nPrice + nPrice * m_sellPercentage /100;
						fmt.Format(L"설정된 매도 퍼센트 %0.2f%% 즉 매도가격 = %d",m_sellPercentage,nPrice);
						TraceOutputW(fmt);
						CString strRQName = _T("주식주문");
						LONG lRet = theApp.m_khOpenApi.SendOrder(strRQName,m_strScrNo,m_AccNo, 2, sJongmokCode,subject->get_count(), nPrice, L"00", L"");
						TraceOutputW(L"지정가 주문완료 감시기기 작동 시작.");
						subject->set_status(false);
						m_checkedSubject.SetAt(sJongmokCode,subject);


						theApp.m_khOpenApi.SetInputValue(L"계좌번호", m_AccNo);
						lRet = theApp.m_khOpenApi.CommRqData(L"계좌평가잔고내역요청", L"OPW00018", 0, m_strScrNo);
						if (!theApp.IsError(lRet))
						{
						}
						//Sleep(1000);
						// 매도가 취소 됬으니 미체결 다시 받아오기  그러니 까 현재 리스트에서 지워져야지
						theApp.m_khOpenApi.SetInputValue(L"계좌번호", m_AccNo);

						//체결구분 = 0:체결+미체결조회, 1:미체결조회, 2:체결조회
						//SetInputValue("체결구분"	,  "1");
						theApp.m_khOpenApi.SetInputValue(L"체결구분", L"1");
						//매매구분 = 0:전체, 1:매도, 2:매수
						//SetInputValue("매매구분"	,  "");
						theApp.m_khOpenApi.SetInputValue(L"매매구분", L"0");

						lRet = theApp.m_khOpenApi.CommRqData(L"실시간미체결요청", L"OPT10075", 0, m_strScrNo);
						if (!theApp.IsError(lRet))
						{
						}

					}else
					{
						m_checkedSubject.SetAt(sJongmokCode,subject);
					}

				}else{
					subject->set_count(_wtoi(strCount));
					m_checkedSubject.SetAt(sJongmokCode,subject);
				}


				



			}else{
				isRunning = false;
				

				if(m_checkedSubject.Lookup(sJongmokCode,(CObject*&)subject)){
					int nTempCount = _wtoi(strCount);
					if(subject->get_count() == nTempCount){
						TraceOutputW(L"주식 다팔려서 감시기기 작동 멈춤.");

						m_checkedSubject.RemoveKey(sJongmokCode);
						m_dealList.DeleteAllItems();
						theApp.m_khOpenApi.SetInputValue(L"계좌번호", m_AccNo);
						long lRet = theApp.m_khOpenApi.CommRqData(L"계좌평가잔고내역요청", L"OPW00018", 0, m_strScrNo);
						if (!theApp.IsError(lRet))
						{
						}


						theApp.m_khOpenApi.SetInputValue(L"계좌번호", m_AccNo);

						//체결구분 = 0:체결+미체결조회, 1:미체결조회, 2:체결조회
						//SetInputValue("체결구분"	,  "1");
						theApp.m_khOpenApi.SetInputValue(L"체결구분", L"1");
						//매매구분 = 0:전체, 1:매도, 2:매수
						//SetInputValue("매매구분"	,  "");
						theApp.m_khOpenApi.SetInputValue(L"매매구분", L"0");

						lRet = theApp.m_khOpenApi.CommRqData(L"실시간미체결요청", L"OPT10075", 0, m_strScrNo);
						if (!theApp.IsError(lRet))
						{
						}

					}
					
				}



			}


			/// 매도가 취소 됬으니 미체결 다시 받아오기  그러니 까 현재 리스트에서 지워져야지
			//theApp.m_khOpenApi.SetInputValue(L"계좌번호", m_AccNo);

			////체결구분 = 0:체결+미체결조회, 1:미체결조회, 2:체결조회
			////SetInputValue("체결구분"	,  "1");
			//theApp.m_khOpenApi.SetInputValue(L"체결구분", L"1");
			////매매구분 = 0:전체, 1:매도, 2:매수
			////SetInputValue("매매구분"	,  "");
			//theApp.m_khOpenApi.SetInputValue(L"매매구분", L"0");

			//lRet = theApp.m_khOpenApi.CommRqData(L"실시간미체결요청", L"OPT10075", 0, m_strScrNo);
			//if (!theApp.IsError(lRet))
			//{
			//}
		}
	}else if(strGuBun == L"1"){// 잔고통보
		//TraceOutputW(L"잔고통보");
		//CString orderStatus =  theApp.m_khOpenApi.GetChejanData(913); //913 주문상태
		//TraceOutputW(orderStatus);
		//CString nRemainedConcludeCount =  theApp.m_khOpenApi.GetChejanData(902); //미체결 남은
		//TraceOutputW(nRemainedConcludeCount);

		//nRemainedConcludeCount =  theApp.m_khOpenApi.GetChejanData(9001); //미체결 남은
		//TraceOutputW(nRemainedConcludeCount);

	}
	
	// 현재 계좌번호
	//TraceOutputW(strAccNo);

	//
	//TraceOutputW(orderNo);

	//
	//TraceOutputW(orderStatus);
	////현재 수익률 조회한 계좌번호에 있는 체결된 종목만 받을 수 있게 처리.
	//if (strAccNo == strAcc)
	//{
	//	if (strGuBun == "4")
	//	{
	//		TraceOutputW(L"보유종목 재조회");
	//		//OnBtnSearch(); //보유종목을 재조회한다.
	//	}
	//}
}
//*******************************************************************/
//! Function Name : OnReceiveChejanData
//! Function      : 체결잔고 실시간 처리
//! Param         : LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CWnd *pWnd;
	CString strKey, strScrType;
	POSITION pos = m_mapScreenNum.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreenNum.GetNextAssoc(pos, strKey, strScrType);
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			switch (_wtoi(strScrType))
			{
			case 0:		// 현재가
				{
					this->MainOnReceiveChejanData(sGubun, nItemCnt, sFidList);
				}
				break;

			}
		}
	}
}

//*******************************************************************/
//! Function Name : OnReceiveRealCondition
//! Function      : 조건검색 실시간 종목 삽입/삭제
//! Param         : LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex
//! Return        : void
//! Create        : , 2015/04/20
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveRealCondition(LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CWnd *pWnd;
	CString strKey, strScrType;
	POSITION pos = m_mapScreenNum.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreenNum.GetNextAssoc(pos, strKey, strScrType);
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			switch (_wtoi(strScrType))
			{
			case 3:		// 조건검색
				{
					//((CRealAddDlg *)pWnd)->OnReceiveRealCondition(strCode, strType, strConditionName, strConditionIndex);
				}
				break;
			}
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveTrCondition
//! Function			: 조건검색 종목조회 응답
//! Param				: LPCTSTR sScrNo					- 화면번호
//!						: LPCTSTR strCodeList			- 종목리스트
//!						: LPCTSTR strConditionName	- 조건명
//!						: int nIndex								- 조건명인덱스
//!						: int nNext								- 연속조회여부(2: 연속조회, 0:연속조회없음)
//! Return        : void
//! Create        : , 2015/04/20
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveTrCondition(LPCTSTR sScrNo, LPCTSTR strCodeList, LPCTSTR strConditionName, int nIndex, int nNext)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		switch (_wtoi(strScrType))
		{
		case 3:	//조건검색
			{
				//((CRealAddDlg *)pWnd)->OnReceiveTrCondition(sScrNo, strCodeList, strConditionName, nIndex, nNext);
			}
			break;
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveConditionVer
//! Function			: 사용자 조건식 응답
//! Param				: BOOL bRet							- 성공(TRUE), 실패(FALSE)
//!						: LPCTSTR sMsg					- 메세지(reserved)
//! Return        : void
//! Create        : , 2015/04/20
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveConditionVer(long lRet, LPCTSTR sMsg)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	if(lRet != 1)
	{// 사용자 조건검색식 서버요청중 에러가 발생한 경우...
		CString		strErr; strErr.Format(_T("%s [%d]"), sMsg, lRet);
		AfxMessageBox(strErr);
		return;
	}

	int nScrNo = GetNextScreenNum(3);
	CString strScrNo;
	strScrNo.Format(L"%04d", nScrNo);

	CString strScrType, strKey = strScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		switch (_wtoi(strScrType))
		{
		case 3:	//조건검색
			{
				//((CRealAddDlg *)pWnd)->OnReceiveConditionVer(lRet, sMsg);
			}
			break;
		}
	}
}

//*******************************************************************/
//! Function Name : OnEventConnect
//! Function      : 접속 통보 처리
//! Param         : LONG nItemCnt
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnEventConnect(LONG nItemCnt)
{
	if (nItemCnt == 0)
	{
		// 접속 정상처리
		OutputDebugString(L"connect successs");

		
		SendMessage(WM_UPDATESTATUSBAR,0,(LPARAM)L"연결성공.");

		m_AccNo = theApp.m_khOpenApi.GetLoginInfo(L"ACCLIST");
		m_AccNo.Replace(L";",L"");

		m_AccNo = theApp.m_khOpenApi.GetLoginInfo(L"ACCLIST");
		m_AccNo.Replace(L";",L"");
		//CString   strSafeKeyStatus = theApp.m_khOpenApi.GetLoginInfo(L"KEY_BSECGB" );


		//LONG nLoginState = theApp.m_khOpenApi.GetConnectState();
		//if(nLoginState){
		//HWND pWnd = ::FindWindow(NULL,L"계좌비밀번호 입력 (버전: 3.72)");
		//CWnd *pWnd = FindWindowEx(this->m_hWnd,NULL,NULL,L"계좌비밀번호 입력 (버전: 3.72)");
		//FindWindowEx(this)	::SetWindowPos (pWnd,NULL,0,0,0,0,SWP_SHOWWINDOW);
		CString strServerType =  theApp.m_khOpenApi.KOA_Functions(_T("GetServerGubun"), _T(""));
		if(strServerType == L"1"){//모의투자
			AfxMessageBox(L"현재 접속한 서버는 모의투자서버입니다,비밀번호 아무거나 입력하셔도 됩니다 !",MB_ICONINFORMATION);
			theApp.m_khOpenApi.KOA_Functions(_T("ShowAccountWindow"), _T(""));
		}else{
			MessageBox(L"경고!주의!위험!",L"현재 접속한 서버는 리얼서버입니다,\n비밀번호 오류시 계좌가 정지 됩니다\n유의해주시길바랍니다 !",MB_ICONWARNING);
			theApp.m_khOpenApi.KOA_Functions(_T("ShowAccountWindow"), _T(""));
		}
		



		CString t = COleDateTime::GetCurrentTime().Format(_T("%H"));
		if(_wtoi(t) >= 9){
			isStockMarketOpen = true;
		}

		// 	여기서 strAcctList는 ';'로 분리한 보유계좌 목록임
		// 		예) "3040525910;567890;3040526010"

		if (!GetNextScreenNum(0))
		{
			return;
		}


		this->m_strScrNo.Format(_T("%04d"), m_nScrN0);


		m_mapScreen.SetAt(m_strScrNo, this);

	


		theApp.m_khOpenApi.SetInputValue(L"계좌번호"	, m_AccNo);

		//비밀번호 = 사용안함(공백)
			theApp.m_khOpenApi.SetInputValue(L"비밀번호"	, L"2419");

		//비밀번호입력매체구분 = 00
			theApp.m_khOpenApi.SetInputValue(L"비밀번호입력매체구분"	,  L"00");

		/*조회구분 = 1:합산, 2:개별*/
			theApp.m_khOpenApi.SetInputValue(L"조회구분"	,  L"1");

		long lRet = theApp.m_khOpenApi.CommRqData(L"계좌평가잔고내역요청", L"OPW00018", 0, m_strScrNo);
		if (!theApp.IsError(lRet))
		{
			
		}

		
		//m_buyList.GetDataSearch();
		//수익률계산 조회 //8100875411


		//계좌번호 = 전문 조회할 보유계좌번호
		//theApp.m_khOpenApi.SetInputValue(L"계좌번호", m_AccNo);

		////체결구분 = 0:체결+미체결조회, 1:미체결조회, 2:체결조회
		//	//SetInputValue("체결구분"	,  "1");
		//theApp.m_khOpenApi.SetInputValue(L"체결구분", L"1");
		////매매구분 = 0:전체, 1:매도, 2:매수
		//	//SetInputValue("매매구분"	,  "");
		//theApp.m_khOpenApi.SetInputValue(L"매매구분", L"0");

		//lRet = theApp.m_khOpenApi.CommRqData(L"실시간미체결요청", L"OPT10075", 0, m_strScrNo);
		//if (!theApp.IsError(lRet))
		//{
		//}



		//theApp.m_khOpenApi.SetInputValue(L"계좌번호", m_AccNo);
		// lRet = theApp.m_khOpenApi.CommRqData(L"계좌수익률", L"OPT10085", 0, m_strScrNo);
		//if (!theApp.IsError(lRet))
		//{
		//}
		//theApp.m_khOpenApi.SetInputValue(L"계좌번호", m_AccNo);
		//lRet = theApp.m_khOpenApi.CommRqData(L"주문체결요청", L"OPT10012", 0, m_strScrNo);
		//if (!theApp.IsError(lRet))
		//{
		//}
	}
	else
	{
		// 접속 비정상 처리
		EndDialog(IDCANCEL);
	}
}

//*******************************************************************/
//! Function Name : GetNextScreenNum
//! Function      : 다음 화면 번호 취득
//! Param         : int nScreenType
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
BOOL CshootStockDlg::GetNextScreenNum(int nScreenType)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static int nRepeat = 0;
	m_nScrN0++;
	if (m_nScrN0 > 9999)
	{
		nRepeat++;
		m_nScrN0 = 1;
	}

	if (nRepeat > 1)
	{
		nRepeat = 0;
		AfxMessageBox(L"더 이상 화면을 열수 없습니다.다른 화면을 닫고 실행 해 주세요~!");
		return FALSE;
	}

	CString strKey, strTemp;
	strKey.Format(L"%04d", m_nScrN0);
	if (m_mapScreenNum.Lookup(strKey, strTemp))
	{
		return GetNextScreenNum(nScreenType);
	}

	nRepeat = 0;
	strTemp.Format(L"%d", nScreenType);
	m_mapScreenNum.SetAt(strKey, strTemp);
	return TRUE;
}



afx_msg LRESULT CshootStockDlg::OnUpdatestatusbar(WPARAM wParam, LPARAM lParam)
{
	return m_StatusBar.SetPaneText(wParam,(LPCTSTR)lParam);
}


void CshootStockDlg::InitStatusBar(void)
{
	UINT m_IsCreated =  m_StatusBar.Create(this);


	UINT  Indicates[5]; 
	for (int i = 1; i<5;i++)
	{
		Indicates[i] = 50+i;
	}

	m_StatusBar.SetIndicators(Indicates,5);
	CRect rect;
	GetClientRect(&rect);
	UINT PaneWidth = rect.Width();

	m_StatusBar.SetPaneInfo(0,0,SBPS_NORMAL,PaneWidth * 10 / 100);
	m_StatusBar.SetPaneInfo(1,0,SBPS_NORMAL,PaneWidth * 21 / 100);
	m_StatusBar.SetPaneInfo(2,0,SBPS_NORMAL,PaneWidth * 21 / 100);
	m_StatusBar.SetPaneInfo(3,0,SBPS_NORMAL,PaneWidth * 21 / 100);
	m_StatusBar.SetPaneInfo(4,0,SBPS_NORMAL,PaneWidth * 27 / 100);

	m_StatusBar.SetPaneText(0,L" 연걸중..");
	m_StatusBar.SetPaneText(1,L"예수금: N/A");
	m_StatusBar.SetPaneText(2,L"d+1출금가능 N/A");
	m_StatusBar.SetPaneText(3,L"d+2출금가능 N/A");
	m_StatusBar.SetPaneText(4,L"현재시간");
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
}


void CshootStockDlg::OnBtnGetAccData(void)
{

	m_AccNo = theApp.m_khOpenApi.GetLoginInfo(L"ACCLIST");
	m_AccNo.Replace(L";",L"");
	//CString   strSafeKeyStatus = theApp.m_khOpenApi.GetLoginInfo(L"KEY_BSECGB" );


	//LONG nLoginState = theApp.m_khOpenApi.GetConnectState();
	//if(nLoginState){
		//HWND pWnd = ::FindWindow(NULL,L"계좌비밀번호 입력 (버전: 3.72)");
		//CWnd *pWnd = FindWindowEx(this->m_hWnd,NULL,NULL,L"계좌비밀번호 입력 (버전: 3.72)");
		//FindWindowEx(this)	::SetWindowPos (pWnd,NULL,0,0,0,0,SWP_SHOWWINDOW);
		CString strServerType =  theApp.m_khOpenApi.KOA_Functions(_T("GetServerGubun"), _T(""));
		if(strServerType == L"1"){//모의투자
			AfxMessageBox(L"현재 접속한 서버는 모의투자서버입니다,비밀번호 아무거나 입력하셔도 됩니다 !",MB_ICONINFORMATION);
			theApp.m_khOpenApi.KOA_Functions(_T("ShowAccountWindow"), _T(""));
		}else{
			MessageBox(L"경고!주의!위험!",L"현재 접속한 서버는 리얼서버입니다,\n비밀번호 오류시 계좌가 정지 됩니다\n유의해주시길바랍니다 !",MB_ICONWARNING);
			theApp.m_khOpenApi.KOA_Functions(_T("ShowAccountWindow"), _T(""));
		}
	//}


	
	CString t = COleDateTime::GetCurrentTime().Format(_T("%H"));
	if(_wtoi(t) >= 9){
		isStockMarketOpen = true;
	}

// 	여기서 strAcctList는 ';'로 분리한 보유계좌 목록임
// 		예) "3040525910;567890;3040526010"

	if (!GetNextScreenNum(0))
	{
		return;
	}


	this->m_strScrNo.Format(_T("%04d"), m_nScrN0);


	m_mapScreen.SetAt(m_strScrNo, this);

	//CString strRQName = _T("증거금세부내역조회요청");
	//CString strTRCode = TR_OPW00013;
	////theApp.theApp.m_khOpenApi.SetInputValue("종목코드", "113810");
	////계좌번호 = 전문 조회할 보유계좌번호  //51653280
	//theApp.m_khOpenApi.SetInputValue(_T("계좌번호")	, m_AccNo);
	////theApp.theApp.m_khOpenApi.SetInputValue("계좌번호"	,  "5165328010");
	////비밀번호 = 사용안함(공백)
	//theApp.m_khOpenApi.SetInputValue(_T("비밀번호")	,  _T(""));

	//long lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
	//CString		strErr;
	//if (!theApp.IsError(lRet))
	//{
	//	strErr.Format(_T("주식기본정보요청 에러 [%s][%d]"), strTRCode, lRet);
	//	OutputDebugString(strErr);
	//};

	//CString strRQName = _T("예수금상세현황요청");
	//CString strTRCode = TR_OPW00001;
	////theApp.theApp.m_khOpenApi.SetInputValue("종목코드", "113810");
	////계좌번호 = 전문 조회할 보유계좌번호  //51653280
	//theApp.m_khOpenApi.SetInputValue(_T("계좌번호")	, m_AccNo);
	////theApp.theApp.m_khOpenApi.SetInputValue("계좌번호"	,  "5165328010");
	////비밀번호 = 사용안함(공백)
	//theApp.m_khOpenApi.SetInputValue(_T("비밀번호")	,  _T("2419"));

	////비밀번호입력매체구분 = 00
	//theApp.m_khOpenApi.SetInputValue(_T("비밀번호입력매체구분")	,  _T("2419"));

	////조회구분 = 1:추정조회, 2:일반조회
	//theApp.m_khOpenApi.SetInputValue(_T("조회구분")	,  _T("2"));
	//long lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
	//CString		strErr;
	//if (!theApp.IsError(lRet))
	//{
	//	strErr.Format(_T("주식기본정보요청 에러 [%s][%d]"), strTRCode, lRet);
	//	OutputDebugString(strErr);
	//};
}


void CshootStockDlg::InitlogList(void)
{
	CRect rect;
	m_logList.GetClientRect(&rect);//삿혤죗깊柬暠왠숭돨욱똑

	int nWidth = rect.Width();

	m_logList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
	m_logList.InsertColumn(0, _T("No"), LVCFMT_LEFT);
	m_logList.InsertColumn(1, _T("Time"), LVCFMT_LEFT);
	m_logList.InsertColumn(2, _T("Information"), LVCFMT_LEFT);

	//�阮첩泰筠커瓷�

	m_logList.GetClientRect(&rect);//삿혤죗깊柬暠왠숭돨욱똑

	nWidth = rect.Width();
	m_logList.SetColumnWidth(0, nWidth * 7 / 100);//츰냔欖25%
	m_logList.SetColumnWidth(1, nWidth * 15 / 100);//쵱쯤欖13%
	m_logList.SetColumnWidth(2, nWidth * 78 / 100);//뒈囹欖25%


	m_logList.SetBkColor(RGB(0,0,0)); 
	m_logList.SetTextColor(RGB(0,255,102)); 
	m_logList.SetTextBkColor(RGB(0,0,0)); 
}
void CshootStockDlg::TraceOutputA(const char* fmt,...)
{
	string str = fmt;
	str += "\r\n";
	USES_CONVERSION;
	//m_RichEdit.SetSel(-1, -1);
	//m_RichEdit.ReplaceSel( (LPCTSTR)A2W(str.c_str()) );
	//m_RichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM,0); 
	//InitRichEdit();
	// 

	//흔벎댕黨係커댕黨1000橙맴딜
	//if(t_loglistControl.GetItemCount() > 1000 )
	//t_loglistControl.DeleteAllItems();

	CString time; //삿혤溝固珂쇌
	CTime tm; 

	tm = CTime::GetCurrentTime(); 

	time=tm.Format("%X"); 

	//OutputDebugString(time);
	//警속
	CString l_index;

	int dwCount = m_logList.GetItemCount();

	l_index.Format(_T("%d"),dwCount+1);

	int dwitem = m_logList.InsertItem(dwCount,l_index,0);
	m_logList.SetItem(dwitem,1,1,time,0,0,0,0);
	m_logList.SetItem(dwitem,2,1,A2W(str.c_str()),0,0,0,0);
	m_logList.EnsureVisible(dwitem,TRUE);
}

void CshootStockDlg::TraceOutputW(const TCHAR* fmt,...)
{
	CString time; //삿혤溝固珂쇌
	CTime tm; 

	tm = CTime::GetCurrentTime(); 

	time=tm.Format("%X"); 

	//OutputDebugString(time);
	//警속
	CString l_index;

	int dwCount = m_logList.GetItemCount();

	l_index.Format(_T("%d"),dwCount+1);

	int dwitem = m_logList.InsertItem(dwCount,l_index,0);
	m_logList.SetItem(dwitem,1,1,time,0,0,0,0);
	m_logList.SetItem(dwitem,2,1,fmt,0,0,0,0);
	m_logList.EnsureVisible(dwitem,TRUE);
}

void CshootStockDlg::InitTabControl(void)
{
	TCITEM   tm;   
	CImageList pImageList;


	pImageList.Create(16, 16, ILC_COLOR16|ILC_MASK,0,2);
	pImageList.SetBkColor(::GetSysColor(COLOR_BTNFACE));
	pImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	pImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON6));
	pImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	pImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON7));
	//this->m_hWnd = 0;

	m_TabControl.SetImageList(&pImageList);
	m_TabControl.InsertItem(0, _T("관심종목"));
	m_TabControl.InsertItem(1, _T("현재가"));
	m_TabControl.InsertItem(2, _T("전일등락률"));
	m_TabControl.InsertItem(3, _T("일자별시세"));
	m_TabControl.InsertItem(4, _T("일자별수익현황"));
	m_TabControl.InsertItem(5, _T("자동매매"));
	pImageList.Detach();

	tm.mask = TCIF_IMAGE;   //   속�麴蓚堊沽�鹿죄   
	for(int i=0; i<2; i++)   
	{   
		m_TabControl.GetItem(i,&tm);   
		tm.iImage=i;   
		m_TabControl.SetItem(i,&tm);   
	}

	m_TabControl.GetItem(5,&tm);   
	tm.iImage=3;   
	m_TabControl.SetItem(5,&tm);  

	if (!GetNextScreenNum(1))
	{
		return;
	}

	m_buyList.m_strScrNo.Format(L"%04d", m_nScrN0);
	m_buyList.Create(IDD_BUY_LIST, &m_TabControl);
	
	m_mapScreen.SetAt(m_buyList.m_strScrNo, &m_buyList);


	if (!GetNextScreenNum(2))
	{
		return;
	}

	m_curPrice.m_strScrNo.Format(L"%04d", m_nScrN0);
	m_curPrice.Create(IDD_CUR_PRICE,&m_TabControl);
	
	m_mapScreen.SetAt(m_curPrice.m_strScrNo, &m_curPrice);

	if (!GetNextScreenNum(3))
	{
		return;
	}


	m_topPrice.m_strScrNo.Format(L"%04d", m_nScrN0);
	m_topPrice.Create(IDD_TOP_PRICE,&m_TabControl);

	m_mapScreen.SetAt(m_topPrice.m_strScrNo, &m_topPrice);
	//m_BenXOut.Create(IDD_DIALOG_OUT,&m_TabControl);


	if (!GetNextScreenNum(4))
	{
		return;
	}


	m_DailyReport.m_strScrNo.Format(L"%04d", m_nScrN0);
	m_DailyReport.Create(IDD_DIALOG_DAILY,&m_TabControl);

	m_mapScreen.SetAt(m_DailyReport.m_strScrNo, &m_DailyReport);


	if (!GetNextScreenNum(6))
	{
		return;
	}


	m_incomeDlg.m_strScrNo.Format(L"%04d", m_nScrN0);
	m_incomeDlg.Create(IDD_DIALOG_INCOME,&m_TabControl);

	m_mapScreen.SetAt(m_incomeDlg.m_strScrNo, &m_incomeDlg);



	if (!GetNextScreenNum(7))
	{
		return;
	}


	m_AutoSystem.m_strScrNo.Format(L"%04d", m_nScrN0);
	m_AutoSystem.Create(IDD_AUTO_SYSTEM,&m_TabControl);

	m_mapScreen.SetAt(m_AutoSystem.m_strScrNo, &m_AutoSystem);

	CRect r;
	m_TabControl.GetClientRect (&r);

	m_buyList.SetWindowPos (NULL,3,22,r.right -8 ,r.bottom-28,SWP_SHOWWINDOW);
	m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW);
	m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW);
	m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
	m_incomeDlg.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
	m_AutoSystem.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
}


void CshootStockDlg::OnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CRect r;
	m_TabControl.GetClientRect (&r);

	switch(m_TabControl.GetCurSel())
	{
	case 0:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28 ,SWP_SHOWWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_incomeDlg.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_AutoSystem.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		break;
	case 1:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom -28,SWP_HIDEWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_SHOWWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_incomeDlg.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_AutoSystem.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		break;
	case 2:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom -28,SWP_HIDEWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_SHOWWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_incomeDlg.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 

		m_topPrice.SendSearch();
		//m_TabControl.SetCurSel(0);
		break;
	case 3:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom -28,SWP_HIDEWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_SHOWWINDOW ); 
		m_incomeDlg.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_AutoSystem.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SendSearch();
		//m_TabControl.SetCurSel(0);
		break;
	case 4:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom -28,SWP_HIDEWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_incomeDlg.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_SHOWWINDOW ); 
		m_AutoSystem.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		//m_TabControl.SetCurSel(0);
		m_incomeDlg.GetDailyIncome();
		break;

	case 5:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom -28,SWP_HIDEWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_incomeDlg.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		//m_TabControl.SetCurSel(0);
		m_AutoSystem.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_SHOWWINDOW ); 
		break;
	}
	*pResult = 0;
}

void CshootStockDlg::InitConcludeList(void)
{
	m_ConcludeList.SetExtendedStyle(LVS_EX_FULLROWSELECT  | LVS_EX_DOUBLEBUFFER);
	m_ConcludeList.ModifyStyle(0,LVS_SINGLESEL); 
	m_ConcludeList.SetGridLines();
	m_ConcludeList.InsertColumn(0,L"주문",0,70);
	m_ConcludeList.InsertColumn(1,L"종목코드",0,70);
	m_ConcludeList.InsertColumn(2,L"종목명",0,80);
	m_ConcludeList.InsertColumn(3,L"주문구분",0,70);
	//m_ListBox.InsertColumn(3,L"",0,100);

	m_ConcludeList.InsertColumn(4,L"주문가격",0,60);
	m_ConcludeList.InsertColumn(5,L"미체결수량",0,70);
	m_ConcludeList.InsertColumn(6,L"매매구분",0,70);
	m_ConcludeList.InsertColumn(7,L"현재가",0,70);
	m_ConcludeList.InsertColumn(8,L"주문시간",0,70);

}

// 	{L"종목번호",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
// 	{L"종목명",				L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
// 	{L"평가손익",			L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
// 	{L"수익률",				L"25",	0,	1,	DT_ZERO_NUMBER,		TRUE,	DT_CENTER,L"",L""}, 
// 	{L"매입가",				L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
// 	{L"보유수량",			L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
// 	{L"현재가",				L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
void CshootStockDlg::InitDealList(void)
{
	m_dealList.SetExtendedStyle(LVS_EX_FULLROWSELECT  | LVS_EX_DOUBLEBUFFER);
	m_dealList.ModifyStyle(0,LVS_SINGLESEL); 
	m_dealList.SetGridLines();
	m_dealList.InsertColumn(0,L"종목코드",0,70);
	m_dealList.InsertColumn(1,L"종목명",0,80);
	m_dealList.InsertColumn(2,L"평가손익",0,70);
	//m_ListBox.InsertColumn(3,L"",0,100);

	m_dealList.InsertColumn(3,L"수익률",0,60);
	m_dealList.InsertColumn(4,L"매입가",0,80);
	m_dealList.InsertColumn(5,L"보유수량",0,70);
	m_dealList.InsertColumn(6,L"현재가",0,70);
	m_dealList.InsertColumn(7,L"수수료합",0,70);
	m_dealList.InsertColumn(8,L"세금",0,60);
}
//*******************************************************************/
//! Function Name	: SetRate
//! Function			: 종목별 수익률 계산
//! Param				: 
//! Return				: void
//! Create				: , 2015/05/12
//! Comment			: 
//******************************************************************/
void CshootStockDlg::SetRate(int nRow, CString strCode)
{
	//주식 종목에 대한 수익률 계산이라 주식외 종목의 수익률은 다를수 있음을 알려드립니다.

	//현재가
	CString strData, strTmp;
	strData = m_dealList.GetItemText(nRow, 3);
	strData.Replace(L",",L"");
	strTmp = strData.Left(1);
	if (strTmp == "-" || strTmp == "+")
	{
		strData = strData.Mid(1);
	}
	double nPrice = _ttof(strData);

	//수량
	double nQty = _ttof(m_dealList.GetItemText(nRow, 4));

	//매입금액
	strTmp =  m_dealList.GetItemText(nRow, 8);
	strTmp.Replace(L",",L"");
	double nPurchase = _ttof(strTmp);

	int nCount(0);
	nCount = m_dealList.GetItemCount();

	//매수가계산 수수료 = 매입금액 * 매체수수료(0.015%) (10원미만 절사)
	m_BuyComm = nPurchase * COMMISSION;
	m_BuyComm = floor(m_BuyComm / 10) * 10;	//(10원미만 절사)

	//매도가계산 수수료 = 현재가 * 수량 * 매체수수료(0.015%) (10원미만 절사)
	m_SellComm = nPrice * nQty * COMMISSION;
	m_SellComm = floor(m_SellComm / 10) * 10;	//(10원미만 절사)

	//제세금
	long lMarketType = theApp.m_khOpenApi.GetMarketType(strCode);
	if (lMarketType == 0) //거래소
	{
		//제세금(거래소) = 현재가 * 수량 * 0.15%(원미만 절사) * 2
		m_Tax = nPrice * nQty * COMMISSION1;
		m_Tax = floor(m_Tax) * 2;
	} 
	else if (lMarketType == 10)//코스닥
	{
		//제세금(코스닥) = 현재가 * 수량 * 0.3%(원미만 절사)
		m_Tax = floor(nPrice * nQty * COMMISSION2);
	}

	CString strTemp;

	//종목별 평가금액 = (현재가 * 수량) - 매수가계산 수수료 - 매도가계산 수수료 - 제세금 가계산
	m_Eval = (nPrice * nQty) - m_BuyComm - m_SellComm - m_Tax;
	strTemp.Format(_T("%0.lf"), m_Eval);
	
	m_dealList.SetItemText(nRow, 5,  theApp.ConvDataFormat(lstFID[5].nDataType, strTemp, lstFID[5].strBeforeData, lstFID[5].strAfterData));
	//m_dealList.SetItemText(nRow, 12,  theApp.ConvDataFormat(lstFID[12].nDataType, strTemp, lstFID[12].strBeforeData, lstFID[12].strAfterData));

	COLORREF tempC = RGB(0,0,255);
	//종목별 평가손익 = 평가금액 - 매입금액
	m_Profit = m_Eval - nPurchase;
	strTemp.Format(_T("%0.lf"), m_Profit);

	if (strTemp.GetAt(0) == '+' )	// 부호에 따라 색상변경
	{
		tempC =  RGB(255,0,0);
	}
	else if (strTemp.GetAt(0) == '-')	// 부호에 따라 색상변경
	{
		tempC =  RGB(0,0,255);
	}
	else
	{
		tempC =  RGB(0,0,0);
	}

	m_dealList.SetItemText(nRow, 6,  theApp.ConvDataFormat(lstFID[6].nDataType, strTemp, lstFID[6].strBeforeData, lstFID[6].strAfterData));
	m_dealList.SetItemTextColor(nRow, 6,tempC);
	//종목별 수익률 = 평가손익 / 매입금액 * 100
	if (nPurchase == 0)
	{
		m_Rate = 0;
	}
	else
	{
		m_Rate = m_Profit / nPurchase * 100;
	}
	strTemp.Format(_T("%0.2lf"), m_Rate);

	
	if (strTemp.GetAt(0) == '+' )	// 부호에 따라 색상변경
	{
		tempC =  RGB(255,0,0);
	}
	else if (strTemp.GetAt(0) == '-')	// 부호에 따라 색상변경
	{
		tempC =  RGB(0,0,255);
	}
	else
	{
		tempC =  RGB(0,0,0);
	}
	m_dealList.SetItemText(nRow, 7,  theApp.ConvDataFormat(lstFID[7].nDataType, strTemp, lstFID[7].strBeforeData, lstFID[7].strAfterData));
	m_dealList.SetItemTextColor(nRow, 7,tempC);


}

//*******************************************************************/
//! Function Name	: SetRate
//! Function			: 종목별 수익률 계산
//! Param				: 
//! Return				: void
//! Create				: , 2015/05/12
//! Comment			: 
//******************************************************************/
void CshootStockDlg::SetTotalRate()
{
// 	int nCnt = m_grdRate.GetRowCount();	//그리드 Row 갯수 구하기
// 	double dTotalEval(0), dTotalPurchase(0), dTotalProfit, dTotalRate(0);
// 	CString strTotalEval, strTotalPurchase, strTotalProfit, strTotalRate;
// 
// 	for (int i = 1; i < nCnt; i++)
// 	{
// 		dTotalEval += _ttof(m_grdRate.GetItemText(i, 12));			// 총 평가금액
// 		dTotalPurchase += _ttof(m_grdRate.GetItemText(i, 11));	// 총 매입금액
// 	}
// 
// 	strTotalEval.Format(_T("%0.lf"), dTotalEval);
// 	strTotalEval = theApp.ConvDataFormat(DT_ZERO_NUMBER, strTotalEval);
// 	m_EdtTotalEval.SetWindowText(strTotalEval);
// 
// 	strTotalPurchase.Format(_T("%0.lf"), dTotalPurchase);
// 	strTotalPurchase = theApp.ConvDataFormat(DT_ZERO_NUMBER, strTotalPurchase);
// 	m_EdtTotalPurchase.SetWindowText(strTotalPurchase);
// 
// 
// 	// 총 평가손익
// 	dTotalProfit = dTotalEval - dTotalPurchase;
// 	strTotalProfit.Format(_T("%0.lf"), dTotalProfit);
// 	strTotalProfit = theApp.ConvDataFormat(DT_ZERO_NUMBER, strTotalProfit);
// 	m_EdtTotalProfit.SetWindowText(strTotalProfit);
// 
// 	// 총 수익률
// 	dTotalRate = dTotalProfit / dTotalPurchase * 100;
// 	strTotalRate.Format(_T("%0.2lf"), dTotalRate);
// 	strTotalRate = theApp.ConvDataFormat(DT_NONE, strTotalRate, "", "%");
// 	m_EdtTotalRate.SetWindowText(strTotalRate);
}



void CshootStockDlg::OnListSearch()
{
	// TODO: Add your command handler code here
	if (!GetNextScreenNum(1))
	{
		return;
	}

	CJongDlg *pJongDlg = new CJongDlg(this);
	pJongDlg->m_strScrNo.Format(L"%04d", m_nScrN0);
	pJongDlg->Create(IDD_JONG_LIST);

	m_mapScreen.SetAt(pJongDlg->m_strScrNo, pJongDlg);
}


BOOL CshootStockDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_ESCAPE)   
		return TRUE;
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_RETURN)   
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}






void CshootStockDlg::OnNMDblclkDealList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	CString strRQName = _T("주식주문");
	CString strJongCode = L"";
	CString nowPrice = L"";
	CString strOrderNo = L"";
	for(int i=0; i<m_dealList.GetItemCount(); i++)
	{
		if( m_dealList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			strJongCode = m_dealList.GetItemText(i,0);

			//	CString strKey, strScrType;
			//POSITION pos = m_mapOrderNo.GetStartPosition();
			//while (pos != NULL)
			//{
			//	strOrderNo= L"";
			//	m_mapOrderNo.GetNextAssoc(pos, strKey, strScrType);
			//	m_mapOrderNo.Lookup(strKey, strOrderNo);
			//}
			CSubject *subject = new CSubject();
			if(m_checkedSubject.Lookup(strJongCode,(CObject*&)subject) ){
				if (m_mapOrderNo.Lookup(strJongCode, strOrderNo))
				{
					CString strRQName = _T("주식주문"); //일단 매도 취소
					LONG lRet = theApp.m_khOpenApi.SendOrder(strRQName,m_strScrNo,m_AccNo, 4, strJongCode,subject->get_count(), 0, L"00",strOrderNo);
					subject->set_status(true);
				}else{
					//걸어놓은 미체결이 없으니 바로 매도 함
					_Trace(L"걸어놓은 주식이 없어 바로 매도함///개발미완성/모니터링 정지 고민");
				}
				//m_checkedSubject.SetAt(strJongCode,subject);
			}


			//if(m_mapOrderNo.Lookup(strJongCode,strOrderNo)){
			//	theApp.m_khOpenApi.SendOrder(strRQName,m_strScrNo, m_AccNo, 4, strJongCode, 0, 0, L"00",strOrderNo);
			//	subject->set_status(true);
			//	m_checkedSubject.SetAt(sJongmokCode,subject);
			//	isManual = true;
			//}

		}
	}

	*pResult = 0;
}
