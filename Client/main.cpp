#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "CEngine.h"
#include <vector>
using std::vector;
#define MAX_LOADSTRING 100
//apptitle
const wchar_t* g_pTitle = L"MyGame";

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND      g_hWnd; //메인 윈도우 핸들

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT __stdcall    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR __stdcall   About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(//현재는 가상 메모리를 쓰니깐 고유 주소가 필요 없음
                    _In_ HINSTANCE hInstance,
                     //hPrevInstance는 16비트 윈도우 시절 윈도우가 여러 개 있을때 다른 윈도우의
                     //주소를 알아야 할 필요가 있었음
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(6475);


    // 윈도우, DC, Brush, Pen, AccelTable 등등
    // Handle 로 다루는 오브젝트들은 kernel Object ( OS 가 관리하는 오브젝트 )
    // 윈도우 설정 세팅 
    MyRegisterClass(hInstance);



    // 윈도우 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //엔진 초기화 1600,900
    CEngine::GetInst()->init(g_hWnd, 1600, 900);
   
    //단축키 테이블 정보 가져오기
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg = {};

    // 기본 메시지 루프입니다:
    // 메세지 큐에서 메세지를 꺼내옴.
    // GetMessege : 메세지 큐에서 메세지를 꺼내옴
    // 리턴값 Bool False인 경우 프로그램이 종료된다.
    // 꺼내온 message(&msg) 가 WM_QUIT이면 getmessage는 false를 반환한다.
    // GetMessage는 메세지가 없을 경우 계속 대기
    // 1초에 수만번 계산을 하기 때문에 메세지 큐는 비어있을때가 많다. 즉, getmessage는 놀고 있는 경우가 많다.
    // while(GetMessage(&msg, nullptr, 0, 0)) -> while(true)로 바꿈
    while (true)
    {
        //PeekMessage : 메세지큐의 다음 메세지 확인
        // 메세지큐에 메세지가 있던 없던 함수를 무조건 반환함. 즉, 메세지큐가 비어있는 시간도 활용이 가능
        //PM_REMOVE 옵션과 조합할 경우, 메세지가 있으면 메세지 큐에서 메세지를 꺼내온다.(GetMessage와 동일)
        //리턴값 Bool이 true일 경우 메세지를 꺼내왔다.false일 경우 메세지가 없다. ->메세지의 유무를 확인
        if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            //게임 종료
            if (WM_QUIT == msg.message)
                break;
           
            //단축키 조합 확인
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {

                TranslateMessage(&msg);//메세지 분석
                DispatchMessage(&msg);//메세지 처리
            }
        }
        else
        {
            //Game Run
            CEngine::GetInst()->progress();
        }
        
    }
   

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    //구조체 초기화 = {} 붙혀야함
    WNDCLASSEXW wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.lpszClassName  = L"MySetting";
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));//MAKEINTRESOURCE(IDI_CLIENT)IDI_SHANTAE
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_CLIENT); //nullptr로 하면 메뉴바를 없앤다.
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));//MAKEINTRESOURCE(IDI_SMALL)

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd= CreateWindowW(L"MySetting", g_pTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd,true);
   UpdateWindow(g_hWnd);

   return TRUE;
}
//함수 정의만 해놓고 구현부분은 CEditorLevel에 있다.
INT_PTR CALLBACK TileCount(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK PlatformEdit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK PlatformPosChange(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK WallEdit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK WallPosChange(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK CeilingEdit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK CeilingPosChange(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


//메인 윈도우의 메세지 처리기 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static POINT ptMouse;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT: {
                //경고같은 팝업창을 띄우는것은 Modal방식
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            }
                
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
                
            case CHANGE_TILECOUNT:
            {   //타일 변경을 눌렀을 경우, 팝업창이 뜸
                DialogBox(hInst, MAKEINTRESOURCE(IDD_TILECOUNT), hWnd, TileCount);
            }

            break;
            case PLATFORM_SIZE:
            {   //platform크기 변경 누를 경우, platform변경됨
                DialogBox(hInst, MAKEINTRESOURCE(IDD_Platform), hWnd, PlatformEdit);
            }

            break;
            case PLATFORM_POS:
            {   //platform크기 변경 누를 경우, platform변경됨
                DialogBox(hInst, MAKEINTRESOURCE(IDD_PlatPos), hWnd, PlatformPosChange);
            }

            break;
            case Wall_Size:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_Wall), hWnd, WallEdit);
            }
            break;
            case WALL_POS:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_WallPos), hWnd, WallPosChange);
            }
            break;
            case CEILING_SIZE:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_WallPos), hWnd, CeilingEdit);
            }
            break;
            case CEILING_POS:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_WallPos), hWnd, CeilingPosChange);
            }
            break;
              
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    //WM_PAINT = 이 윈도우가 다시 그려져야 하는 상황이 왔을때
    //윈도우에 Rendering이 다시 발생해야 할 때
    // -> 해당 윈도우에 무효화 영역이 생겼을때 ex)화면 최소화 후 다시 키기
    case WM_PAINT:
        {

            PAINTSTRUCT ps;
            //Handle Device Context
            //Rendering에 필요한 데이터 = DC
            HDC hdc = BeginPaint(hWnd, &ps);
            //화면에 물체를 그린다.
           
           
          

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

// 정보 대화 상자의 메시지 처리기입니다.
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
