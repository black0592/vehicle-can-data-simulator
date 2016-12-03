
// CanSimulatorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CCanSimulatorDlg �Ի���
class CCanSimulatorDlg : public CDialogEx
{
// ����
public:
	CCanSimulatorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CANSIMULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_SelectProtocols;
	CEdit m_TransferInterval;
	CEdit m_InputDeviceId;
	afx_msg void OnBnClickedAddDeviceId();
	afx_msg void OnBnClickedRemoveDeviceId();
	afx_msg void OnBnClickedExportDeviceIdTemplet();
	CListBox m_AddedList;
	afx_msg void OnBnClickedImportDeviceId();
	CDateTimeCtrl m_SystemTime;
};
