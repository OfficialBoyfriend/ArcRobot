
// ArcRobotDlg.cpp : ʵ���ļ�
//

#include <iostream>
#include "stdafx.h"
#include "ArcRobot.h"
#include "ArcRobotDlg.h"
#include "afxdialogex.h"
#include "PosSeqDialog.h"
#include "ScanDialog.h"
#include "Resource.h"
#include "CalibrationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();


// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


// ʵ��
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


// CArcRobotDlg �Ի���



CArcRobotDlg::CArcRobotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ARCROBOT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	CalibrationDlg::CalibratedFlag = false;
	res0.resize(scanCount);
	for (int i = 0; i != scanCount; i++)
	{
		res0[i].resize(1000);
		for (int j = 0; j != 1000; j++)
			res0[i][j].resize(10);
	}


	SensorData0.resize(segCount);
	for (int i = 0; i != segCount; i++)
	{
		SensorData0[i].resize(1000);
		for (int j = 0; j != 1000; j++)
			SensorData0[i][j].resize(4);
	}
	
	numOfRes0[0] = 0;
	numOfRes0[1] = 0;
	numOfRes0[2] = 0;
}

void CArcRobotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CArcRobotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CArcRobotDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CArcRobotDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CArcRobotDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CArcRobotDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CArcRobotDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON9, &CArcRobotDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON7, &CArcRobotDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &CArcRobotDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &CArcRobotDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CArcRobotDlg ��Ϣ�������

BOOL CArcRobotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_SHOWNORMAL);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CArcRobotDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CArcRobotDlg::OnPaint()
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
HCURSOR CArcRobotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CArcRobotDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CArcRobotDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ABBSocket abbsoc;
	abbsoc.SocketListen();
	addtext(IDC_EDIT2, L"start Listen!");
	abbsoc.SocketAccept();
	addtext(IDC_EDIT2, L"aceepted a controller !");

	/*vector<vector<char *>> targetPos = {
		{ "[757.05,-839.97,1148.20]","[0.0300251,0.513015,-0.81292,0.274]","[-1,-1,-2,0]","[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]" },
		{ "[757.05,-1010.73,1148.20]","[0.0300251,0.513015,-0.81292,0.274]","[-1,-1,-2,0]","[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]" },
		{ "[363.58, -1074.88, 945.65]","[0.0300252, 0.513015, -0.812919, 0.274]", "[-1, 0, -2, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
		{ "[363.58, -704.45, 934.48]", "[0.0300252, 0.513015, -0.812919, 0.274]", "[-1, -1, -2, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" },
		{ "[943.61, 0.00, 1152.50]", "[0.5, -1.19121E-08, 0.866025, -6.87746E-09]", "[0, 0, -1, 0]", "[9E+09, 9E+09, 9E+09, 9E+09, 9E+09, 9E+09]" }
	};
	abbsoc.SocketSendPos(targetPos);
	addtext(IDC_EDIT2, L"send over !");*/
	
}

int CArcRobotDlg::addtext(int nID, CString str, bool addition)
{
	CString strOrigin;
	if (addition)
	{
		GetDlgItem(nID)->GetWindowText(strOrigin);
		strOrigin += str;
		strOrigin += "\r\n";
	}
	else
		strOrigin += str;
	GetDlgItem(nID)->SetWindowText(strOrigin);
	CEdit*p = (CEdit*)GetDlgItem(nID); //����һ��ָ��༭��ľ����ָ��
	p->LineScroll(p->GetLineCount()); //�������õ�
	return 0;
}

void CArcRobotDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString str;
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	str += "test display";
	str += "\r\n";
	GetDlgItem(IDC_EDIT2)->SetWindowText(str);
	CEdit*p = (CEdit*)GetDlgItem(IDC_EDIT2); //����һ��ָ��༭��ľ����ָ��
	p->LineScroll(p->GetLineCount()); //�������õ�
}



void CArcRobotDlg::OnBnClickedButton3()
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������

	char* pos;
	CString cpos;
	pos = abbsoc.GetCurPos();
	cout << pos << endl;
	cpos.Format(_T("%s"), CStringW(pos));                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
	cout << cpos << endl;	
	addtext(IDC_EDIT2,cpos);
	vector<double> posVec=mathc.str2vec(pos);
	//cout << posVec[0] << " " << posVec[1] << " " << posVec[2] << " " << posVec[3] << " " << posVec[4] << " " << posVec[5] << " "  << posVec[6] <<endl;	
	for (int i = 0; i != 7; i++)
	{
		cpos.Format(_T("%.5lf"), posVec[i]);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
		//cout << cpos << endl;
		addtext(IDC_EDIT3+i,cpos,false);
	}



}


void CArcRobotDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	abbsoc.SetToZero();
}




void CArcRobotDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PosSeqDialog PSDiolog;
	PSDiolog.DoModal();
}




void CArcRobotDlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ScanDialog ScanD;
	ScanD.DoModal();
}


void CArcRobotDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CalibrationDlg* pDlg = new CalibrationDlg(this);
	// ������ģʽ�Ի���
	pDlg->Create(IDD_DIALOG3);
	// �ƶ����ڵ������ڵ�����
	pDlg->CenterWindow();
	// ��ʾ���´���
	pDlg->ShowWindow(SW_NORMAL);
	pDlg->UpdateWindow();
}


void CArcRobotDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
//1. ���ӻ����ˣ����Ӵ���������
	addtext(IDC_EDIT2, L"STEP1!");
	abbsoc.SocketListen();
	addtext(IDC_EDIT2, L"start Listen!");
	abbsoc.SocketAccept();
	addtext(IDC_EDIT2, L"aceepted a controller !");
	sensorsocket0.SocketListen();
	sensorsocket0.SocketAccept();
	//�ص�ԭ��
	abbsoc.SetToZero();

	for (int times = 0; times < scanCount; times++)
	{
		//���������ʾ����
		CString str;
		str.Format(_T("-------��%d��---------"), times + 1);

		//2.�������˶���ɨ�����
		addtext(IDC_EDIT2, str+L"STEP2!");
		FILE* FileOut;
		char startPosTxt[][30]={ "MoveToStartPos0.txt","MoveToStartPos1.txt","MoveToStartPos2.txt"};
		if (fopen_s(&FileOut, startPosTxt[times], "r") != 0)
			MessageBox(L"û�д��ļ�", L"��ʾ");
		char content[500];
		vector<vector<char *>> targetPos(100, vector<char *>(6, nullptr));
		int targetNum = 0;
		while (!feof(FileOut))                                   //ѭ����ȡÿһ�У�ֱ���ļ�β  
		{
			fgets(content, 1024, FileOut);                     //��fp��ָ����ļ�һ�����ݶ���strLine������ 
															   //std::cout << content << std::endl;


															   //char* data1,data2,data3;
			char data1[100] = { 0 }, data2[100] = { 0 }, data3[100] = { 0 }, data4[100] = { 0 };
			char* dataChar = content;
			int i = 0;
			for (i = 0; *dataChar != ']'; i++, dataChar++)
				data1[i] = *dataChar;
			data1[i] = *dataChar;
			dataChar += 2;

			for (i = 0; *dataChar != ']'; i++, dataChar++)
				data2[i] = *dataChar;
			data2[i] = *dataChar;
			dataChar += 2;

			for (i = 0; *dataChar != ']'; i++, dataChar++)
				data3[i] = *dataChar;
			data3[i] = *dataChar;
			dataChar += 2;

			for (i = 0; *dataChar != ']'; i++, dataChar++)
				data4[i] = *dataChar;
			data4[i] = *dataChar;
			targetPos[targetNum][0] = data1;
			targetPos[targetNum][1] = data2;
			targetPos[targetNum][2] = data3;
			targetPos[targetNum][3] = data4;
			targetPos[targetNum][4] = "MoveL";
			targetPos[targetNum][5] = "v50";
			targetNum++;
		}

		abbsoc.SocketSendPos(targetPos, targetNum);
		addtext(IDC_EDIT2, str+L"Have Moved To Scan Start Position!");


		//3.��ʼɨ�裬֪ͨ�����˿������봫�������̿�ʼ��ʱ������ȡ������ɨ�����λ������
		char scanPosText[][30] = { "ScanPosVec0.txt","ScanPosVec0.txt","ScanPosVec0.txt" };

		addtext(IDC_EDIT2, str+L"STEP3!");
		FILE* FileOut0;
		if (fopen_s(&FileOut0, scanPosText[times], "r") != 0)
			MessageBox(L"û�д��ļ�", L"��ʾ");

		targetNum = 0;
		char content0[500];
		vector<vector<char *>> targetPos0(100, vector<char *>(4, nullptr));
		while (!feof(FileOut0))                                   //ѭ����ȡÿһ�У�ֱ���ļ�β  
		{
			fgets(content0, 1024, FileOut0);                     //��fp��ָ����ļ�һ�����ݶ���strLine������ 
															   //std::cout << content << std::endl;


															   //char* data1,data2,data3;
			char data1[100] = { 0 }, data2[100] = { 0 }, data3[100] = { 0 }, data4[100] = { 0 };
			char* dataChar = content0;
			int i = 0;
			for (i = 0; *dataChar != ']'; i++, dataChar++)
				data1[i] = *dataChar;
			data1[i] = *dataChar;
			dataChar += 2;

			for (i = 0; *dataChar != ']'; i++, dataChar++)
				data2[i] = *dataChar;
			data2[i] = *dataChar;
			dataChar += 2;

			for (i = 0; *dataChar != ']'; i++, dataChar++)
				data3[i] = *dataChar;
			data3[i] = *dataChar;
			dataChar += 2;

			for (i = 0; *dataChar != ']'; i++, dataChar++)
				data4[i] = *dataChar;
			data4[i] = *dataChar;
			//std::cout << "data1:" << data1 << std::endl;
			//std::cout << "data2:" << data2 << std::endl;
			//std::cout << "data3:" << data3 << std::endl;
			//std::cout << std::endl;

			targetPos0[targetNum][0] = data1;
			targetPos0[targetNum][1] = data2;
			targetPos0[targetNum][2] = data3;
			targetPos0[targetNum][3] = data4;
			targetNum++;
		}
		fclose(FileOut0);
		sensorsocket0.SocketStart("start");//�����������̷��Ϳ�ʼ����
		recv(sensorsocket0.sClient, sensorsocket0.read_buf, sizeof(sensorsocket0.read_buf), 0);//�ȴ�����������
		abbsoc.SocketScan(targetPos0, &ScanStartTime0, targetNum);//λ�÷������������ʼ��ʱ
		addtext(IDC_EDIT2, str+L"Start Scanning!");

		//��ʼ��ȡ������λ������
		char* pos;
		int rval;
		pos = abbsoc.SocketPosRecv(&rval);
		while (rval != -1)
		{
			sscanf_s(pos, "%lf[%lf,%lf,%lf][%lf,%lf,%lf]", &res0[times][numOfRes0[times]][0], &res0[times][numOfRes0[times]][1], &res0[times][numOfRes0[times]][2], &res0[times][numOfRes0[times]][3], &res0[times][numOfRes0[times]][4], &res0[times][numOfRes0[times]][5], &res0[times][numOfRes0[times]][6]);
			//cout << "controller time:" << res[numOfRes][0] << endl;
			//calwl.calWeldLinePos(res[numOfRes], RealPos[numOfRes]);
			numOfRes0[times]++;
			pos = abbsoc.SocketPosRecv(&rval);
		}

	}

//4.����������õ�����λ�ã����ͺ�������ڴ�����λ�����ݵ������ƽ���
	addtext(IDC_EDIT2, L"STEP4!");
	addtext(IDC_EDIT2, L"Waitting for Sensor Data Comming!");
	char recvbuf[100];
	int SubFrequency = 0;
	int th = 0;
	numOfSensorData0[0] = 0;numOfSensorData0[1] = 0;numOfSensorData0[2] = 0;

	//Recvbuf������ 18/8/13

	while (sensorsocket0.RecvLine(recvbuf, 100, '\n') != 0)
	{
		cout << recvbuf;
		//ZeroMemory(recvbuf, 100);//����ڴ�recvbuf
		if (charEqual(recvbuf,"next\r\n"))
		{
			SubFrequency = 0;
			th++;
			continue;
		}
		if (SubFrequency % 10 == 0)
		{
			//cout << SubFrequency << endl;
			//sscanf_s �ϸ��ո�ʽ������
			sscanf_s(recvbuf, "(%lf)x:%lf, y:%lf, z:%lf", &SensorData0[th][numOfSensorData0[th]][0], &SensorData0[th][numOfSensorData0[th]][1], &SensorData0[th][numOfSensorData0[th]][2], &SensorData0[th][numOfSensorData0[th]][3]);
			numOfSensorData0[th]++;
		}
		//ת���յ��Ĵ��������ݣ�������vector��

	}
	sensorsocket0.closeSocket();
	addtext(IDC_EDIT2, L"SensorData Received!");
	//for (int ii = 0; ii <= SubFrequency/10; ii++)
	//cout << "transformed:" << "x:" << SensorData[ii][0] << "y:" << SensorData[ii][1] << "z:" << SensorData[ii][2] << endl;


//5.ͨ�����������ݺͻ�����λ�����ݼ���õ������������������ϵλ�ã��Լ�������̬
	//�����������֮ǰδ�궨��������������һ�α궨�Ľ��
	//bool  CalibrationDlg::CalibratedFlag = false;//�Ƿ�궨�ı�־
	double quaternion[][4] = { { 0.01074,0.36312,0.80240,-0.47348 },{ 0.01074,0.36312,0.80240,-0.47348 },{ 0.01074,0.36312,0.80240,-0.47348 },{ 0.01074,0.36312,0.80240,-0.47348} };
	addtext(IDC_EDIT2, L"STEP5!");
	if (CalibrationDlg::CalibratedFlag == false)
	{
		FILE* FileOut;
		if (fopen_s(&FileOut, "CalibrationResult.txt", "r") != 0)
			MessageBox(L"û�д��ļ�", L"��ʾ");
		char TStr[200];
		for (int Trow = 0; Trow != 4; Trow++)
		{
			fgets(TStr, 200, FileOut);
			sscanf_s(TStr, "%lf %lf %lf %lf", &CalibrationDlg::T(Trow, 0), &CalibrationDlg::T(Trow, 1), &CalibrationDlg::T(Trow, 2), &CalibrationDlg::T(Trow, 3));
		}
		fclose(FileOut);
	}
	cout << endl;
	cout << "��ת����" << endl;
	cout << CalibrationDlg::T << endl;

	for (int times = 0; times != segCount; times++)
	{
		cout << "��" << times << "��ɨ��" << endl;
		cout << "������λ�����ݣ�" << endl;
		for (int i = 0; i < numOfRes0[match[times]]; i++)
			cout << "time: " << res0[match[times]][i][0] << "s  " << res0[match[times]][i][1] << " " << res0[match[times]][i][2] << " " << res0[match[times]][i][3] << " " << res0[match[times]][i][4] << " " << res0[match[times]][i][5] << " " << res0[match[times]][i][6] << " " << res0[match[times]][i][7] << endl;
		cout << "���������ݣ�" << endl;
		for (int i = 0; i < numOfSensorData0[times]; i++)
			cout << "time: " << SensorData0[times][i][1] << "s  " << SensorData0[times][i][2] << " " << SensorData0[times][i][3] << endl;
	}


	//�ҵ������Ӧʱ�̻�����λ�ˣ�����������ϵõ�
	vector<vector<vector<double>>> fitPos;
	fitPos.resize(segCount);
	int numOfFitPos[segCount] = { 0 };
	for (int times = 0; times != segCount; times++)
	{
		fitPos[times].resize(numOfSensorData0[times], vector<double>(8, 0.0));
		int j = 1;
		double timeStart = res0[match[times]][0][0];
		for (int i = 0; i != numOfSensorData0[times]; i++)
		{
			//numOfSensorData0 - i - 1
			//�����ǰ������ʱ��С�ڻ����˵�һ��ʱ������������ȥ����С������ֱ��break
			if (SensorData0[times][i][1]<res0[match[times]][0][0])
				break;
			//�����ǰ������ʱ����ڻ��������һ��ʱ�������continue
			if (SensorData0[times][i][1] >= res0[match[times]][numOfRes0[times] - 1][0])
				continue;

			fitPos[times][numOfFitPos[times]][0] = SensorData0[times][i][1];//���͹����Ĵ�����λ��ֵ��ʱ���������
			while (fitPos[times][numOfFitPos[times]][0] > timeStart && j < numOfRes0[times])
			{
				timeStart = res0[match[times]][j++][0];
			}

			//���ڽǶ�������ֵ���ܻ����    2018/8/12


			vector<double> TemRes(6, 0.0);
			for (int ind = 0; ind != 6; ind++)
				TemRes[ind] = (fitPos[times][numOfFitPos[times]][0] - res0[match[times]][j - 2][0]) / (res0[match[times]][j - 1][0] - res0[match[times]][j - 2][0])*(res0[match[times]][j - 1][ind + 1] - res0[match[times]][j - 2][ind + 1]) + res0[match[times]][j - 2][ind + 1];

			//����任�õ�����λ��ֵ
			Matrix4d EndP;
			//1.��xyzabcת����T������ʽ
			double alfa = TemRes[3] / 180 * 3.1415926;
			double beta = TemRes[4] / 180 * 3.1415926;
			double gama = TemRes[5] / 180 * 3.1415926;
			vector<double> temR{ cos(alfa)*cos(beta), cos(alfa)*sin(beta)*sin(gama) - sin(alfa)*cos(gama), cos(alfa)*sin(beta)*cos(gama) + sin(alfa)*sin(gama),
				sin(alfa)*cos(beta), sin(alfa)*sin(beta)*sin(gama) + cos(alfa)*cos(gama), sin(alfa)*sin(beta)*cos(gama) - cos(alfa)*sin(gama),
				-sin(beta), cos(beta)*sin(gama), cos(beta)*cos(gama) };
			for (int Trow = 0; Trow != 3; Trow++)
				for (int Tcol = 0; Tcol != 3; Tcol++)
					EndP(Trow, Tcol) = temR[Trow * 3 + Tcol];
			EndP(0, 3) = TemRes[0]; EndP(1, 3) = TemRes[1]; EndP(2, 3) = TemRes[2];
			EndP(3, 0) = 0; EndP(3, 1) = 0; EndP(3, 2) = 0; EndP(3, 2) = 1;

			//2.���þ�����˵õ�λ�ú���̬
			Matrix4d TemRot(EndP*CalibrationDlg::T);
			Vector4d SensorDelta;
			SensorDelta << 0, SensorData0[times][i][2], SensorData0[times][i][3], 1;
			Vector4d TemPos(EndP*CalibrationDlg::T*SensorDelta);
			//3.T����ת����xyzabc��ʽ����ֵ��fitPos
			fitPos[times][numOfFitPos[times]][1] = TemPos(0);
			fitPos[times][numOfFitPos[times]][2] = TemPos(1);
			fitPos[times][numOfFitPos[times]][3] = TemPos(2);

			Matrix3d t_R;
			t_R(0, 0) = EndP(0, 0); t_R(0, 1) = EndP(0, 1); t_R(0, 2) = EndP(0, 2);
			t_R(1, 0) = EndP(1, 0); t_R(1, 1) = EndP(1, 1); t_R(1, 2) = EndP(1, 2);
			t_R(2, 0) = EndP(2, 0); t_R(2, 1) = EndP(2, 1); t_R(2, 2) = EndP(2, 2);
			Quaterniond Q3(t_R);
			//fitPos[numOfFitPos][4] = Q3.coeffs()(0);
			//fitPos[numOfFitPos][5] = Q3.coeffs()(1);
			//fitPos[numOfFitPos][6] = Q3.coeffs()(2);
			//fitPos[numOfFitPos][7] = Q3.coeffs()(3);
			//Ŀǰû�м��㺸����̬���Ȳ��ù̶���̬ quat=[0.01074,-0.36312,0.80240,-0.47348]
			fitPos[times][numOfFitPos[times]][4] = quaternion[times][0];
			fitPos[times][numOfFitPos[times]][5] = quaternion[times][1];
			fitPos[times][numOfFitPos[times]][6] = quaternion[times][2];
			fitPos[times][numOfFitPos[times]][7] = quaternion[times][3];
			//cout << "t_R: " << t_R << endl;
			//cout << "Quaternion3: " << endl << Q3.coeffs() << endl;

			//������һ�������
			numOfFitPos[times]++;

		}
		addtext(IDC_EDIT2, L"Finished caculating real position!");
		cout << "------------��" << times << "�κ�������" << endl;
		for (int i = 0; i < numOfFitPos[times]; i++)
			//cout << "time: " << fitPos[i][0] << "s  " << fitPos[i][1] << " " << fitPos[i][2] << " " << fitPos[i][3] << " " << fitPos[i][4] << " " << fitPos[i][5] << " " << fitPos[i][6] << " " << fitPos[i][6]<< endl;
			cout << "[" << fitPos[times][i][1] << ", " << fitPos[times][i][2] << " " << fitPos[times][i][3] << "]" << " [" << fitPos[times][i][4] << " " << fitPos[times][i][5] << " " << fitPos[times][i][6] << " " << fitPos[times][i][7] << "]" << "[0, 0, 0, 0] [9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]" << endl;
	}




	//6.����λ��ʹ�������˶�
	char startPos[][6][50] = {
		{ "[343.32,-632.11,828.00]","[0.01074,0.36312,0.80240,-0.47348]","[-1,-1,0,0]","[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]","MoveL","v50" } ,
		{ "[343.32,-632.11,828.00]","[0.01074,0.36312,0.80240,-0.47348]","[-1,-1,0,0]","[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]","MoveL","v50" } ,
		{ "[343.32,-632.11,828.00]","[0.01074,0.36312,0.80240,-0.47348]","[-1,-1,0,0]","[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]","MoveL","v50" } 
	};

	for (int times = 0; times != segCount; times++)
	{
		CString str2;
		str2.Format(_T("-------��%d��---------"), times + 1);
		addtext(IDC_EDIT2, str2+L"STEP6!");
		vector<vector<char *>> targetPos1(numOfFitPos[times]/5 + 2, vector<char *>(6, nullptr));
		for (int i = 0; i != numOfFitPos[times] / 5 + 2; i++)
		{
			for(int j=0;j!=6;j++)
			{	
				char *fitStr=new char[200];
				targetPos1[i][j] = fitStr;
			}
	
		}
		//[731.5, 650.5, 533.4][0.00640, -0.13130, 0.98885, 0.06989]
		sprintf_s(targetPos1[0][0],200,  startPos[times][0]);
		sprintf_s(targetPos1[0][0],200,  startPos[times][0]);
		sprintf_s(targetPos1[0][1], 200, startPos[times][1]);
		sprintf_s(targetPos1[0][2], 200, startPos[times][2]);
		sprintf_s(targetPos1[0][3], 200, startPos[times][3]);
		sprintf_s(targetPos1[0][4], 200, startPos[times][4]);
		sprintf_s(targetPos1[0][5], 200, startPos[times][5]);
		//-0.5422    0.5927 - 0.5956
		//0.8333    0.2886 - 0.4715
		//- 0.1076 - 0.7520 - 0.6503
		// -10 * [-0.5956, -0.4715, -0.6503]
		//ans =
		//5.9560    4.7150    6.5030
		for (int i = 1; i < numOfFitPos[times] /5 + 1; i++)
		{
			sprintf_s(targetPos1[i][0], 200, "[%lf, %lf, %lf]", fitPos[times][i * 5-1][1]+ 6, fitPos[times][i * 5 - 1][2]-1, fitPos[times][i * 5 - 1][3]+ 6.503);
			sprintf_s(targetPos1[i][1], 200, "[%lf, %lf, %lf, %lf]",fitPos[times][i*5 - 1][4],fitPos[times][i*5 - 1][5],fitPos[times][i*5 - 1][6],fitPos[times][i*5 - 1][7]);
			sprintf_s(targetPos1[i][2], 200, "[-1, -1, 0, 0]");
			sprintf_s(targetPos1[i][3], 200, "[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]");
			sprintf_s(targetPos1[i][4], 200, "ArcL");
			sprintf_s(targetPos1[i][5], 200, "v50");
		}
		sprintf_s(targetPos1[numOfFitPos[times] / 5 + 1][0], 200, "[%lf, %lf, %lf]", fitPos[times][numOfFitPos[times] - 1][1] + 6, fitPos[times][numOfFitPos[times] - 1][2]-1, fitPos[times][numOfFitPos[times] - 1][3] + 6.503);
		sprintf_s(targetPos1[numOfFitPos[times] / 5 + 1][1], 200, "[%lf, %lf, %lf, %lf]", fitPos[times][numOfFitPos[times] - 1][4], fitPos[times][numOfFitPos[times] - 1][5], fitPos[times][numOfFitPos[times] - 1][6], fitPos[times][numOfFitPos[times] - 1][7]);
		sprintf_s(targetPos1[numOfFitPos[times] / 5 + 1][2], 200, "[-1, -1, 0, 0]");
		sprintf_s(targetPos1[numOfFitPos[times] / 5 + 1][3], 200, "[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]");
		sprintf_s(targetPos1[numOfFitPos[times] / 5 + 1][4], 200, "ArcLEnd");
		sprintf_s(targetPos1[numOfFitPos[times] / 5 + 1][5], 200, "v50");

		sprintf_s(targetPos1[1][4], 200, "MoveJ");
		sprintf_s(targetPos1[2][4], 200, "ArcLStart");

		addtext(IDC_EDIT2, str2 + L"LET US MOVE!");
		abbsoc.SocketSendPos(targetPos1, numOfFitPos[times] /5 + 2,false);
	}
	
	
}

bool CArcRobotDlg::charEqual(char* recLine, char* split)
{
	int i = 0;
	bool res = true;
	while (recLine[i++] != 0)
	{
		if (recLine[i] != split[i])
		{
			res = false;
			break;
		}
	}
	return res;
}

vector<vector<vector<double>>> CArcRobotDlg::res0;//������λ�ô�ʱ���
int CArcRobotDlg::numOfRes0[3];//������λ�ü���

vector<vector<vector<double>>> CArcRobotDlg::SensorData0;//����������λ��0


int CArcRobotDlg::numOfSensorData0[3];//�������������

//vector<vector<double>> CArcRobotDlg::RealPos;
ABBSocket CArcRobotDlg::abbsoc;
DWORD CArcRobotDlg::ScanStartTime0;
DWORD CArcRobotDlg::GetWeldLineTime0;
int CArcRobotDlg::SensorPosCount0;
bool  CalibrationDlg::CalibratedFlag = false;//�Ƿ�궨�ı�־
