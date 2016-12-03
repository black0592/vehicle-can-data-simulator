
// CanSimulatorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CanSimulator.h"
#include "CanSimulatorDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCanSimulatorDlg �Ի���

CApplication app;
CWorkbook book;
CWorkbooks books;
CWorksheet sheet;
CWorksheets sheets;
CRange range;
CFont font;
CRange cols;
LPDISPATCH lpDisp;

CCanSimulatorDlg::CCanSimulatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CANSIMULATOR_DIALOG, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCanSimulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_SelectProtocols);
	DDX_Control(pDX, IDC_EDIT1, m_TransferInterval);
	DDX_Control(pDX, IDC_EDIT2, m_InputDeviceId);
	DDX_Control(pDX, IDC_LIST1, m_AddedList);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_SystemTime);
}

BEGIN_MESSAGE_MAP(CCanSimulatorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCanSimulatorDlg::OnBnClickedAddDeviceId)
	ON_BN_CLICKED(IDC_BUTTON2, &CCanSimulatorDlg::OnBnClickedRemoveDeviceId)
	ON_BN_CLICKED(IDC_BUTTON4, &CCanSimulatorDlg::OnBnClickedExportDeviceIdTemplet)
	ON_BN_CLICKED(IDC_BUTTON3, &CCanSimulatorDlg::OnBnClickedImportDeviceId)
END_MESSAGE_MAP()


// CCanSimulatorDlg ��Ϣ�������

BOOL CCanSimulatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_DENORMAL);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// ��ѡ��Э�顱��Ͽ����������
	m_SelectProtocols.AddString(_T("v0"));
	m_SelectProtocols.AddString(_T("v1"));

	// ���á����������༭���Ĭ��ֵ
	m_TransferInterval.SetWindowTextW(_T("1"));

	// ��ʼ���������豸�š��༭��
	m_InputDeviceId.SetWindowTextW(_T(""));

	// ��ʼ����ϵͳʱ�䡱�ؼ�
	CTime tm;
	tm = CTime::GetCurrentTime();
	m_SystemTime.SetTime(&tm);
	m_SystemTime.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCanSimulatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCanSimulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCanSimulatorDlg::OnBnClickedAddDeviceId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString deviceid;
	m_InputDeviceId.GetWindowTextW(deviceid);

	if (deviceid == "")
		return;

	m_AddedList.AddString(deviceid);

	// ���ñ༭��
	m_InputDeviceId.SetWindowTextW(_T(""));
}


void CCanSimulatorDlg::OnBnClickedRemoveDeviceId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index = m_AddedList.GetCurSel();
	if (index < 0) {
		MessageBox(_T("��ѡ��Ҫ�Ƴ����豸�ţ�"));
		return;
	}

	m_AddedList.DeleteString(index);
	if (index > 0) {
		m_AddedList.SetCurSel(index - 1);
	}
}


void CCanSimulatorDlg::OnBnClickedExportDeviceIdTemplet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ����Excel
	CFileDialog dlg(FALSE, _T("(*.xls)"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("(*.xls)|*.xls||"), NULL);
	if (dlg.DoModal() == IDOK)
	{
		CString strFileName = dlg.GetPathName();
		COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
		if (!app.CreateDispatch(_T("Excel.Application")))
		{
			this->MessageBox(_T("����Excel����ʧ�ܣ�"));
			return;
		}

		books = app.get_Workbooks();
		book = books.Add(covOptional);
		sheets = book.get_Worksheets(); // �õ�Worksheets
		sheet = sheets.get_Item(COleVariant((short)1));
		range = sheet.get_Range(COleVariant(_T("A1")), COleVariant(_T("A1")));
		range.put_Value2(COleVariant(_T("�����豸��")));
		cols = range.get_EntireColumn();
		cols.put_NumberFormat(COleVariant(L"@")); // ����������Ϊ�ı���ʽ
		cols.AutoFit();
		range = sheet.get_Range(COleVariant(_T("B1")), COleVariant(_T("B1")));
		range.put_Value2(COleVariant(_T("���ε����豸������")));

		book.SaveCopyAs(COleVariant(strFileName));
		book.put_Saved(true);

		// �ͷŶ���
		book.ReleaseDispatch();
		books.ReleaseDispatch();
		app.Quit();
		app.ReleaseDispatch();
	}

}


void CCanSimulatorDlg::OnBnClickedImportDeviceId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HRESULT hr;
	hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		AfxMessageBox(_T("Failed to call CoInitialize()."));
	}

	CFileDialog  filedlg(TRUE, L"*.xls", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"xls�ļ� (*.xls)|*.xls");
	filedlg.m_ofn.lpstrTitle = L"���ļ�";
	CString strFilePath;
	if (IDOK == filedlg.DoModal())
	{
		strFilePath = filedlg.GetPathName();
	}
	else
	{
		return;
	}

	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		this->MessageBox(_T("����Excel����ʧ�ܣ�"));
		return;
	}

	books = app.get_Workbooks();
	lpDisp = books.Open(strFilePath, covOptional
		, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional
		, covOptional, covOptional, covOptional
		, covOptional, covOptional, covOptional
		, covOptional);
	book.AttachDispatch(lpDisp);
	sheets = book.get_Worksheets();
	sheet = sheets.get_Item(COleVariant((short)1));

	// ��ȡExcel��������ɵ�Ԫ���ֵ������m_AddedList����ʾ
	COleVariant vResult;
	// ��ȡ�Ѿ�ʹ���������Ϣ�������Ѿ�ʹ�õ���������������ʼ�С���ʼ��
	range.AttachDispatch(sheet.get_UsedRange());
	range.AttachDispatch(range.get_Rows());
	// ����Ѿ�ʹ�õ�����
	long iRowNum = range.get_Count();
	range.AttachDispatch(range.get_Columns());
	// ����Ѿ�ʹ�õ�����
	long iColNum = range.get_Count();
	// �����ʹ���������ʼ�У���1��ʼ
	long iStartRow = range.get_Row();
	// �����ʹ���������ʼ�У���1��ʼ
	long iStartCol = range.get_Column();
	// ��ñ��ε����豸������
	range.AttachDispatch(sheet.get_Cells());
	range.AttachDispatch(range.get_Item(COleVariant((long)2), COleVariant((long)2)).pdispVal);
	vResult = range.get_Value2();
	vResult.ChangeType(VT_I4);
	int total = vResult.intVal;

	for (int i = 2; i <= total + 1; i++)
	{
		// ��ȡ��Ԫ���ֵ
		range.AttachDispatch(sheet.get_Cells());
		range.AttachDispatch(range.get_Item(COleVariant((long)i), COleVariant((long)1)).pdispVal);
		vResult = range.get_Value2();
		CString str, stry, strm, strd;
		SYSTEMTIME st;
		if (vResult.vt == VT_BSTR) // �ַ���
		{
			str = vResult.bstrVal;
			m_AddedList.AddString(str);
		}
		else if (vResult.vt == VT_R8) // 8-byte real
		{
			str.Format(L"%f", vResult.dblVal);
			m_AddedList.AddString(str);
		}
		else if (vResult.vt == VT_DATE) // ʱ��
		{
			VariantTimeToSystemTime(vResult.date, &st);
			stry.Format(L"%d", st.wYear);
			strm.Format(L"%d", st.wMonth);
			strd.Format(L"%d", st.wDay);
			str = stry + L"-" + strm + L"-" + strd;
			m_AddedList.AddString(str);
		}
		else if (vResult.vt == VT_EMPTY) // ��Ԫ��Ϊ��
		{
			str = L"";
			m_AddedList.AddString(str);
		}
		else if (vResult.vt == VT_I4) // 4-byte integer
		{
			str.Format(_T("%ld"), (int)vResult.lVal);
			m_AddedList.AddString(str);
		}
	}

	// �ͷŶ���
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.Quit();
	app.ReleaseDispatch();
}
