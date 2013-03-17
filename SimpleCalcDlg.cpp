// SimpleCalcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SimpleCalc.h"
#include "SimpleCalcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

enum Operation {
    OpPlus = 1, OpMinus, OpMultiply, OpDivide, 
};

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSimpleCalcDlg dialog




CSimpleCalcDlg::CSimpleCalcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimpleCalcDlg::IDD, pParent)
    , m_opcount(0)
    , m_expr(_T(""))

    , m_fullexpr(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimpleCalcDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT2, m_editCtrl);
    DDX_Text(pDX, IDC_EDIT2, m_expr);
    DDX_Text(pDX, IDC_EDIT3, m_fullexpr);
}

BEGIN_MESSAGE_MAP(CSimpleCalcDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDOK, &CSimpleCalcDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CSimpleCalcDlg::OnBnClickedCancel)
    ON_BN_CLICKED(ID_ZERO, &CSimpleCalcDlg::OnBnClickedZero)
    ON_BN_CLICKED(ID_ONE, &CSimpleCalcDlg::OnBnClickedOne)
    ON_BN_CLICKED(ID_TWO, &CSimpleCalcDlg::OnBnClickedTwo)
    ON_BN_CLICKED(ID_THREE, &CSimpleCalcDlg::OnBnClickedThree)
    ON_BN_CLICKED(ID_FOUR, &CSimpleCalcDlg::OnBnClickedFour)
    ON_BN_CLICKED(ID_FIVE, &CSimpleCalcDlg::OnBnClickedFive)
    ON_BN_CLICKED(ID_SIX, &CSimpleCalcDlg::OnBnClickedSix)
    ON_BN_CLICKED(ID_SEVEN, &CSimpleCalcDlg::OnBnClickedSeven)
    ON_BN_CLICKED(ID_EIGHT, &CSimpleCalcDlg::OnBnClickedEight)
    ON_BN_CLICKED(ID_NINE, &CSimpleCalcDlg::OnBnClickedNine)
    ON_BN_CLICKED(ID_DOT, &CSimpleCalcDlg::OnBnClickedDot)
    ON_EN_SETFOCUS(IDC_EDIT2, &CSimpleCalcDlg::OnEnSetfocusEdit2)
    ON_EN_CHANGE(IDC_EDIT2, &CSimpleCalcDlg::OnEnChangeEdit2)
    ON_EN_KILLFOCUS(IDC_EDIT2, &CSimpleCalcDlg::OnEnKillfocusEdit2)
    ON_BN_CLICKED(ID_PLUS, &CSimpleCalcDlg::OnBnClickedPlus)
    ON_BN_CLICKED(ID_MINUS, &CSimpleCalcDlg::OnBnClickedMinus)
    ON_BN_CLICKED(ID_MUL, &CSimpleCalcDlg::OnBnClickedMul)
    ON_BN_CLICKED(ID_DIV, &CSimpleCalcDlg::OnBnClickedDiv)
    ON_BN_CLICKED(ID_C, &CSimpleCalcDlg::OnBnClickedC)
    ON_BN_CLICKED(ID_PLUS_MINUS, &CSimpleCalcDlg::OnBnClickedPlusMinus)
    ON_BN_CLICKED(IDSWF, &CSimpleCalcDlg::OnBnClickedSwf)
END_MESSAGE_MAP()


// CSimpleCalcDlg message handlers

BOOL CSimpleCalcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

    m_editCtrl.EnableWindow();
    m_flush = false;
    m_fullflush = false;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSimpleCalcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSimpleCalcDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSimpleCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CSimpleCalcDlg::Compute(int arg)
{
    UpdateData(TRUE);
    if(m_expr.GetLength() == 0)
        return -1;
    m_num2 = atof(m_expr);
    if(m_num2 == 0)
        m_fullexpr += "0";
    else
        m_fullexpr += m_expr;
    UpdateData(FALSE);
    UpdateData(TRUE);

    if(m_opcode == OpPlus)
    {
        m_result = m_num1 + m_num2;
    }
    else if(m_opcode == OpMinus)
    {
        m_result = m_num1 - m_num2;
    }
    else if(m_opcode == OpMultiply)
    {
        m_result = m_num1 * m_num2;
    }
    else if(m_opcode == OpDivide)
    {
        m_result = m_num1 / m_num2;
    }

    m_num1 = m_result;
    m_num2 = 0;
    m_opcount = 1;

    char buf[128];
    sprintf(buf, "%lf", m_result);
    m_expr = buf;
    m_flush = true;

    if(m_fullflush == true)
    {  
        m_fullexpr += "=";
        m_fullexpr += m_expr;
        m_num1 = m_num2 = m_result = 0;
        m_opcode = m_opcount = 0;
    }
    UpdateData(FALSE);
    return 0;
}

void CSimpleCalcDlg::OnBnClickedOk()
{
    if(m_opcount == 0)
        return;
    m_fullflush = true;
    Compute(1);
}

void CSimpleCalcDlg::OnBnClickedCancel()
{
    OnCancel();
}

void CSimpleCalcDlg::AddString(const CString &str)
{
    UpdateData(TRUE);
    
    if(m_fullflush == true)
    {
        m_expr = "";
        m_fullexpr = "";
        m_fullflush = false;
        m_flush = false;
    }
    else if(m_flush == true)
    {
        m_expr = "";
        m_flush = false;
    }

    m_expr += str;
    UpdateData(FALSE);
}

void CSimpleCalcDlg::OnBnClickedZero()
{
    AddString("0");
}

void CSimpleCalcDlg::OnBnClickedOne()
{
    AddString("1");
}

void CSimpleCalcDlg::OnBnClickedTwo()
{
    AddString("2");
}

void CSimpleCalcDlg::OnBnClickedThree()
{
    AddString("3");
}

void CSimpleCalcDlg::OnBnClickedFour()
{
    AddString("4");
}

void CSimpleCalcDlg::OnBnClickedFive()
{
    AddString("5");
}

void CSimpleCalcDlg::OnBnClickedSix()
{
    AddString("6");
}

void CSimpleCalcDlg::OnBnClickedSeven()
{
    AddString("7");
}

void CSimpleCalcDlg::OnBnClickedEight()
{
    AddString("8");
}

void CSimpleCalcDlg::OnBnClickedNine()
{
    AddString("9");
}

void CSimpleCalcDlg::OnBnClickedDot()
{
    UpdateData(TRUE);
    if(m_expr.Find('.') == TRUE)
        return;
    AddString(".");
}

void CSimpleCalcDlg::OnEnSetfocusEdit2()
{
}

void CSimpleCalcDlg::OnEnChangeEdit2()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
}

void CSimpleCalcDlg::OnEnKillfocusEdit2()
{
    // TODO: Add your control notification handler code here
}

void CSimpleCalcDlg::OnBnClickedPlus()
{
    UpdateData(TRUE);
    if(m_fullflush == true)
    {
        m_expr = "";
        m_fullexpr = "";
        UpdateData(FALSE);
        return;
    }

    if(m_flush == true)
    {
        m_flush = false;
        m_opcount = 1;
        m_expr = "";
        m_opcode = OpPlus; // plus
    }
    else if( m_opcount == 0)
    {
        m_num1 = atof(m_expr);
        m_opcount = 1;
        m_fullexpr += m_expr;
        m_fullexpr += "+";
        m_expr = "";
        m_opcode = OpPlus; // plus
    }
    else 
    {   
        if(Compute() < 0)
            m_fullexpr = m_fullexpr.Left(m_fullexpr.GetLength() - 1);
        m_fullexpr += "+";
        m_opcode = OpPlus; // plus
    }
    
    UpdateData(FALSE);
}

void CSimpleCalcDlg::OnBnClickedMinus()
{
    UpdateData(TRUE);
    if(m_fullflush == true)
    {
        m_expr = "";
        m_fullexpr = "";
        UpdateData(FALSE);
        return;
    }
    if(m_flush == true)
    {
        m_flush = false;
        m_opcount = 1;
        m_expr = "";
        m_opcode = OpMinus; // minus
    }
    else if( m_opcount == 0)
    {
        m_num1 = atof(m_expr);
        m_opcount = 1;
        m_fullexpr += m_expr;
        m_fullexpr += "-";
        m_expr = "";
        m_opcode = OpMinus; // minus
    }
    else 
    {   
        if(Compute() < 0)
            m_fullexpr = m_fullexpr.Left(m_fullexpr.GetLength() - 1);
        m_fullexpr += "-";
        m_opcode = OpMinus; // minus

    }
    
    UpdateData(FALSE);
}

void CSimpleCalcDlg::OnBnClickedMul()
{
    UpdateData(TRUE);
    if(m_fullflush == true)
    {
        m_expr = "";
        m_fullexpr = "";
        UpdateData(FALSE);
        return;
    }
    if(m_flush == true)
    {
        m_flush = false;
        m_opcount = 1;
        m_expr = "";
        m_opcode = OpMultiply; // MUL
    }
    else if( m_opcount == 0)
    {
        m_num1 = atof(m_expr);
        m_opcount = 1;
        m_fullexpr += m_expr;
        m_fullexpr += "*";
        m_expr = "";
        m_opcode = OpMultiply; // MUL
    }
    else 
    {
        if(Compute() < 0)
            m_fullexpr = m_fullexpr.Left(m_fullexpr.GetLength() - 1);
        m_fullexpr += "*";
        m_opcode = OpMultiply; // MUL
    }
    
    UpdateData(FALSE);
}

void CSimpleCalcDlg::OnBnClickedDiv()
{
    UpdateData(TRUE);
    if(m_fullflush == true)
    {
        m_expr = "";
        m_fullexpr = "";
        UpdateData(FALSE);
        return;
    }
    if(m_flush == true)
    {
        m_flush = false;
        m_opcount = 1;
        m_expr = "";
        m_opcode = OpDivide; // DIV
    }
    else if( m_opcount == 0)
    {
        m_num1 = atof(m_expr);
        m_opcount = 1;
        m_fullexpr += m_expr;
        m_fullexpr += "/";
        m_expr = "";
        m_opcode = OpDivide; // DIV
    }
    else 
    {
        if(Compute() < 0)
            m_fullexpr = m_fullexpr.Left(m_fullexpr.GetLength() - 1);
        m_fullexpr += "/";
        m_opcode = OpDivide; // DIV
    }
    
    UpdateData(FALSE);
}

void CSimpleCalcDlg::OnBnClickedC()
{
    m_num1 = m_num2 = m_result = 0;
    m_expr = "";
    m_opcode = m_opcount = 0;
    UpdateData(FALSE);
}

void CSimpleCalcDlg::OnBnClickedPlusMinus()
{
    UpdateData(TRUE);
    m_expr.Format("%lf", -atof(m_expr));
    UpdateData(FALSE);
}

void CSimpleCalcDlg::OnBnClickedSwf()
{
    ShellExecute(NULL, _T("open"), _T("http://www.softwareandfinance.com"),
                NULL, NULL, SW_SHOWNORMAL);    
}
