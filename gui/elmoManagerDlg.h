
// elmoManagerDlg.h : header file
//

#pragma once

// ADS headers for TwinCAT 3
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsDef.h"
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsAPI.h"
#include "elmo.h"
#include "protocol.h"
#include "afxwin.h"

// CelmoManagerDlg dialog
class CelmoManagerDlg : public CDialogEx
{
// Construction
public:
	CelmoManagerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ELMOMANAGER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	template<class TO = uint16_t, class FROM>
	TO data(FROM which) { return static_cast<TO>(which); }
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	long writeADS(unsigned long offset, unsigned long size, void* data) { return AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, offset, size, data); } // 0x4020
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonMove();
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnBnClickedButtonIdle();
	afx_msg void OnBnClickedButtonEmg();
	afx_msg void OnBnClickedButtonHalt();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckImd();
	
	void enableButton(const bool status, UINT btn) {
		CButton* pConnBtn = (CButton*)GetDlgItem(btn);
		pConnBtn->EnableWindow(status);
	}

	void enableButton(const bool status, std::initializer_list<UINT> btns) {
		for (const UINT& btn : btns) enableButton(status, btn);
	}

	// fixed range: [-20000, 0]
	LONG getRandomRange() const {
		return (rand() % 20001) - 20000;
	}

	bool immediate() const {
		return m_check_imd.GetCheck() == BST_CHECKED;
	}

	// variables
	CButton m_check_imd;

private:
	UINT_PTR timer_id;
	ads::elmo client_;
	int _error;
	long nPort;
	AmsAddr Addr;
	PAmsAddr pAddr;	
public:
	afx_msg void OnBnClickedButtonBending();
	afx_msg void OnBnClickedButtonAll();
	afx_msg void OnBnClickedButtonTrans();
};
