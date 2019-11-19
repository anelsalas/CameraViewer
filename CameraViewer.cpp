// CameraViewer.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "CameraViewer.h"


#include <iostream>
#include <strsafe.h>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc.hpp>



#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void					popup(std::string message, HWND parent = NULL);

HWND g_hWnd;


int ShowVideo(int);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CAMERAVIEWER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CAMERAVIEWER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CAMERAVIEWER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CAMERAVIEWER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   g_hWnd = hWnd;

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// statics here simply means that once the variables have been initialized, 
	// they remains in memory until the end of the program.
	static HWND viewCamBtn;

	static HWND comPort;
	switch (message)
    {
		case WM_CREATE:
			{
				// buttons
				viewCamBtn = CreateWindow(L"BUTTON", L"PlayVid1", BS_TEXT | WS_CHILD | WS_VISIBLE,
					0, 0, 100, 20, hWnd, (HMENU)2, (HINSTANCE)GetWindowLongPtr(hWnd, -6)/*hInst*/, NULL);

				if (!viewCamBtn)
				{
					return FALSE;
				}

				comPort = CreateWindow(L"BUTTON", L"PlayVid2", WS_CHILD | WS_VISIBLE | BS_TEXT,
					0,20, 100, 20, hWnd, (HMENU)3, (HINSTANCE)GetWindowLongPtr(hWnd, -6), NULL);


			}
		case WM_COMMAND:
			{
				int wmId = LOWORD(wParam);
				// Parse the menu selections:
				switch (wmId)
				{
				case IDM_ABOUT:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				case 2:
					ShowVideo(0);
					//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				case 3:
					ShowVideo(1);
					//DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;


				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
			}
			break;
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				// TODO: Add any drawing code that uses hdc here...
				EndPaint(hWnd, &ps);
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



// please use this only on extreme cases or for debuging
// cuz popups are anoying
void popup(std::string message, HWND parent )
{
	//LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)message.c_str()) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("Message: %s"),
		message.c_str());
	MessageBox(parent, (LPCTSTR)lpDisplayBuf, TEXT("output"), MB_OK);
}

int ShowVideo(int cameraIndex = 1)
{
	int key(0);
	cv::Mat img;
	cv::Mat newImg;
	bool defaultVals(true);

	//cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
	//cv::namedWindow("Filtered", cv::WINDOW_AUTOSIZE);
	cv::VideoCapture cap(cameraIndex + cv::CAP_DSHOW);

	//HWND hWnd2 = (HWND)cvGetWindowHandle("Original");
	//HWND hWnd3 = (HWND)cvGetWindowHandle("Filtered");

	//
	////hParent = ::GetParent(hWnd2);
	//::SetParent(hWnd2, g_hWnd);
	//::SetParent(hWnd3, g_hWnd);

	//::ShowWindow(g_hWnd, SW_HIDE);
	double cannythreashold1(30), cannythreashold2(60);
	bool l2gradient(false);

	// contrast = alpha and brightness = beta from g(i,j) = alpha * f(i,j) + beta
	double alpha(1.0); // 1.0 - 3 contrast
	int beta(0); // 1 - 100 brightness
	while (true)
	{
		cap >> img;
		img.convertTo(newImg, -1, alpha, beta);

		cv::Mat edges1,edges,houghsp;

		cv::cvtColor(newImg, edges, cv::COLOR_BGR2GRAY);
		cv::Canny(edges, edges1, cannythreashold1, cannythreashold2,3, l2gradient);

		//cv::Vec4i lines;
		//cv::HoughLinesP(edges1, houghsp, 1, CV_PI / 180, 80);// , 30, 10);


		//::ShowWindow(g_hWnd, SW_HIDE);
		//cvShowImage("IDC_STATIC_OUTPUT", img);

		imshow("Filtered", edges1);
		imshow("Original", newImg);

		//imshow("shit", img);
		//key = 0xFF &  cv::waitKey(1);
		char key = cv::waitKey(1);
		switch (key)
		{
		case 'q':
			goto out;
		case 'Q':
			goto out;

		// canny parameters:
		case '1':
			cannythreashold1 += 5;
			break;
		case '!':
			cannythreashold1 -= 5;
			break;
		case '2':
			cannythreashold2 += 5;
			break;
		case '@':
			cannythreashold2 -= 5;
			break;
		case '3':
			l2gradient != l2gradient;
			break;
		case '4':
			l2gradient = false;
			cannythreashold1 = 30;
			cannythreashold2 = 60;
			alpha = 1;
			beta = 0;
			break;

		// brightness and contrast parameters
		//	 Enter the alpha value[1.0 - 3.0]: 2.2
		//   Enter the beta value[0 - 100] : 50
		case 'b': 
			if (beta == 100) break;
			beta += 1;
			break;
		case 'B': 
			if (beta == 0) break;
			beta -= 1;
			break;
		case 'c': 
			if (alpha == 3) break;
			alpha += 0.1;
			break;
		case 'C': 
			if (alpha == 1) break;
			alpha -= 0.1;
			break;
		}

	}
	out:
	/* deallocate resources */
	cv::destroyWindow	("Filtered");
	cv::destroyWindow	("Original");

	return 0;
}


