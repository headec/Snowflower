
// elmoManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "elmoManager.h"
#include "elmoManagerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CelmoManagerDlg dialog



CelmoManagerDlg::CelmoManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ELMOMANAGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CelmoManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_IMD, m_check_imd);
}

BEGIN_MESSAGE_MAP(CelmoManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CelmoManagerDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, &CelmoManagerDlg::OnBnClickedButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CelmoManagerDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_MOVE, &CelmoManagerDlg::OnBnClickedButtonMove)
	ON_BN_CLICKED(IDC_BUTTON_HALT, &CelmoManagerDlg::OnBnClickedButtonHalt)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CelmoManagerDlg::OnBnClickedButtonRun)
	//	ON_WM_DRAWITEM()
	ON_WM_TIMER(timer_id, OnTimer)
ON_BN_CLICKED(IDC_BUTTON_IDLE, &CelmoManagerDlg::OnBnClickedButtonIdle)
ON_BN_CLICKED(IDC_BUTTON_EMG, &CelmoManagerDlg::OnBnClickedButtonEmg)
ON_BN_CLICKED(IDC_BUTTON_HALT, &CelmoManagerDlg::OnBnClickedButtonHalt)
ON_BN_CLICKED(IDC_CHECK_IMD, &CelmoManagerDlg::OnBnClickedCheckImd)
ON_BN_CLICKED(IDC_BUTTON_BENDING, &CelmoManagerDlg::OnBnClickedButtonBending)
ON_BN_CLICKED(IDC_BUTTON_ALL, &CelmoManagerDlg::OnBnClickedButtonAll)
ON_BN_CLICKED(IDC_BUTTON_TRANS, &CelmoManagerDlg::OnBnClickedButtonTrans)
END_MESSAGE_MAP()


// CelmoManagerDlg message handlers

BOOL CelmoManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	pAddr = &Addr;
	client_ = ads::elmo(pAddr);
	
	//enableButton(TRUE, IDC_BUTTON_CONNECT);
	//enableButton(FALSE, {
	//	IDC_BUTTON_DISCONNECT,
	//	IDC_BUTTON_IDLE,
	//	IDC_BUTTON_RUN,
	//	IDC_BUTTON_RESET,
	//	IDC_BUTTON_MOVE,
	//	IDC_BUTTON_HALT,
	//	IDC_BUTTON_EMG });

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CelmoManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CelmoManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CelmoManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CelmoManagerDlg::OnBnClickedButtonConnect()
{
	nPort = AdsPortOpen();
	int nErr = AdsGetLocalAddress(pAddr);
	pAddr->port = 350;
	if (nErr) AfxMessageBox(_T("Error: AdsGetLocalAddress()"));
	else {
		constexpr int cycle_ms = 100;
		timer_id = 1;
		unsigned long stop = 0;
		protocol::setting_t pp_info = { 1, 500, 400, 400 };
		char state;

		try {
			client_.initialize();
			client_.send(ads::offset::setting, pp_info);
			client_.send(ads::offset::event, event::btn::connect);
			SetTimer(timer_id, cycle_ms, nullptr);
		}
		catch (ads::error_t e) {
			if (e == ads::error_t::request_fail)		AfxMessageBox(_T("Cannot request to server"));
			else if (e == ads::error_t::response_fail)	AfxMessageBox(_T("No response from server"));
			else								     	AfxMessageBox(_T("Unknown error"));
		}
	}
}

void CelmoManagerDlg::OnBnClickedButtonDisconnect()
{
	client_.send(ads::offset::event, event::btn::disconnect);

	int nErr = AdsPortClose();
	if (nErr) AfxMessageBox(_T("Error: AdsPortClose()"));
	
	KillTimer(timer_id);
	
	SetDlgItemText(IDC_EDIT_STATE, _T(""));
	
	//enableButton(TRUE, IDC_BUTTON_CONNECT);
	//enableButton(FALSE, {
	//	IDC_BUTTON_DISCONNECT, 
	//	IDC_BUTTON_IDLE,
	//	IDC_BUTTON_RUN, 
	//	IDC_BUTTON_RESET,
	//	IDC_BUTTON_MOVE,
	//	IDC_BUTTON_HALT,
	//	IDC_BUTTON_EMG });
}


void CelmoManagerDlg::OnBnClickedButtonReset()
{
	client_.send(ads::offset::event, event::btn::reset);

	//enableButton(TRUE, IDC_BUTTON_RUN);
	//enableButton(FALSE, { IDC_BUTTON_IDLE, IDC_BUTTON_EMG });
}


void CelmoManagerDlg::OnBnClickedButtonMove()
{
	unsigned long target_pos_val = GetDlgItemInt(IDC_EDIT_TARGET_POS);
	bool immediate = m_check_imd.GetCheck() == BST_CHECKED;
	protocol::move_t move_to_pos = { immediate, target_pos_val };

	client_.send(ads::offset::move, move_to_pos);
	client_.send(ads::offset::event, event::btn::move);
}


void CelmoManagerDlg::OnBnClickedButtonRun()
{
	char state; 
	client_.send(ads::offset::event, event::btn::run);
	if(client_.receive(ads::offset::state, state) == 0 && state == data<char>(protocol::state_t::ready))
	{
		//enableButton(TRUE, { IDC_BUTTON_IDLE, IDC_BUTTON_MOVE, IDC_BUTTON_HALT, IDC_BUTTON_EMG });
		//enableButton(FALSE, IDC_BUTTON_RUN);
	}
}


void CelmoManagerDlg::OnBnClickedButtonIdle()
{
	client_.send(ads::offset::event, event::btn::idle);
	
	//enableButton(TRUE, { IDC_BUTTON_RUN, IDC_BUTTON_RESET });
	//enableButton(FALSE, { IDC_BUTTON_IDLE, IDC_BUTTON_RESET, IDC_BUTTON_MOVE, IDC_BUTTON_HALT, IDC_BUTTON_EMG });
}


void CelmoManagerDlg::OnBnClickedButtonEmg()
{
	client_.send(ads::offset::event, event::btn::emeregency);
	
	//enableButton(TRUE, IDC_BUTTON_RESET);
	//enableButton(FALSE, { IDC_BUTTON_IDLE, IDC_BUTTON_RUN, IDC_BUTTON_MOVE, IDC_BUTTON_HALT });
}


void CelmoManagerDlg::OnBnClickedButtonHalt()
{
	client_.send(ads::offset::event, event::btn::halt);
}

void CelmoManagerDlg::OnTimer(UINT_PTR nIDEvent)
{
	const CString parseState[] = {
		_T(""), _T("INIT"), _T("IDLE"), _T("READY"),
		_T("ACTIVE"), _T("EMERGENCY"), _T("RECOVERY"), _T("ERROR")
	};

	if (nIDEvent == timer_id) {
		char state;
		if(client_.receive(ads::offset::state, state) == 0){
			SetDlgItemText(IDC_EDIT_STATE, parseState[state]);
		}
	}
}

void CelmoManagerDlg::OnBnClickedCheckImd()
{
	if (m_check_imd.GetCheck() == BST_CHECKED) {
		// do nothing for now ...
	}
}


void CelmoManagerDlg::OnBnClickedButtonBending()
{
	protocol::move_t move_to_pos = { immediate(), getRandomRange() };
	
	client_.send(ads::offset::move, move_to_pos);
	client_.send(ads::offset::event, event::btn::bending);
}


void CelmoManagerDlg::OnBnClickedButtonAll()
{
	protocol::move_t move_to_pos = { immediate(), getRandomRange() };
	
	client_.send(ads::offset::move, move_to_pos);
	client_.send(ads::offset::event, event::btn::all_motors);
}


void CelmoManagerDlg::OnBnClickedButtonTrans()
{
	protocol::move_t move_to_pos = { immediate(), getRandomRange() };
	
	client_.send(ads::offset::move, move_to_pos);
	client_.send(ads::offset::event, event::btn::translation);
}
