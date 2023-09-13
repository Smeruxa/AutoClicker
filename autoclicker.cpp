#include "framework.h"

#define BACKGROUND_COLOR RGB(255, 255, 255)

#define LBUTTON_LINK 255
#define RBUTTON_LINK 256

#define EXCHILD_LINK 301
#define EXCHILD_SETTINGS_LINK 302

#define STATE_LINK 101
#define SETTINGS_LINK 102

#define FSLIDER 501
#define SSLIDER 502

#define FSLIDER_TEXT_LINK 401
#define SSLIDER_TEXT_LINK 402

HWND s_fSlider;
HWND t_fSliderText;

HWND s_sSlider;
HWND t_sSliderText;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    const wchar_t* CLASS_NAME = _T("auclicker");

    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, CLASS_NAME, NULL };
    HICON hIcon = (HICON)LoadImage(NULL, L"autoclicker.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
    RegisterClassEx(&wc);

    HWND hWnd = CreateWindowEx(
        0,
        CLASS_NAME,                     
        L"AutoClicker",                  
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,        
        CW_USEDEFAULT, CW_USEDEFAULT,   
        270, 295,
        NULL,                            
        NULL,                          
        hInstance,                        
        NULL                           
    );

    if (hWnd == NULL)
    {
        return 0;
    }

    if (hIcon != NULL) {
        wc.hIcon = hIcon;
        SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HBRUSH hBrushColor = CreateSolidBrush(BACKGROUND_COLOR);

    switch (uMsg) {
    case WM_CREATE:
        {
            config = new Config();
            config->load();

            AutoClicker = new clicker(hwnd, config);

            // first child

            CreateWindow(TEXT("button"), TEXT("Включить / выключить"),
                WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX | BS_FLAT,
                40, 0, 170, 20,
                hwnd, (HMENU)STATE_LINK, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

            CreateWindowEx(
                0,                 
                L"STATIC",       
                L"Состояния",
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_VCENTER, 
                5, 20,    
                243, 70,      
                hwnd,       
                (HMENU)EXCHILD_LINK,           
                ((LPCREATESTRUCT)lParam)->hInstance,     
                NULL       
            );

            CreateWindow(TEXT("button"), TEXT("Вкл / выкл левую кнопку мыши"),
                WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX | BS_FLAT,
                7, 43, 235, 20,
                hwnd, (HMENU)LBUTTON_LINK, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

            CreateWindow(TEXT("button"), TEXT("Вкл / выкл правую кнопку мыши"),
                WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX | BS_FLAT,
                7, 69, 240, 20,
                hwnd, (HMENU)RBUTTON_LINK, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

            // first child

            // second child

            CreateWindow(TEXT("button"), TEXT("Собственная настройка"),
                WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX | BS_FLAT,
                35, 100, 177, 20,
                hwnd, (HMENU)SETTINGS_LINK, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

            CreateWindowEx(
                0,              
                L"STATIC",         
                L" Настройка задержки",
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_VCENTER, 
                5, 120,       
                243, 130,     
                hwnd,       
                (HMENU)EXCHILD_SETTINGS_LINK,          
                ((LPCREATESTRUCT)lParam)->hInstance,       
                NULL  
            );

            // create sliders

            {

                // Text over slider

                CreateWindowEx(0, L"STATIC", L"Задержка левой кнопки мыши", WS_CHILD | WS_VISIBLE,
                    8, 140, 210, 20, hwnd, (HMENU)FSLIDER_TEXT_LINK, NULL, NULL);

                // Text over slider

                // First slider

                s_fSlider = CreateWindowEx(WS_EX_STATICEDGE, TRACKBAR_CLASS, NULL, WS_CHILD | WS_VISIBLE | TBS_HORZ | TBS_AUTOTICKS | BS_FLAT,
                    8, 160, 170, 30, hwnd, (HMENU)FSLIDER, NULL, NULL);

                SendMessage(s_fSlider, TBM_SETRANGE, TRUE, MAKELPARAM(10, 100));
                SendMessage(s_fSlider, TBM_SETPOS, TRUE, config->get_left_wait());

                t_fSliderText = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE,
                    180, 164, 50, 20, hwnd, (HMENU)FSLIDER_TEXT_LINK, NULL, NULL);


                wchar_t temp_buffer[20];
                swprintf_s(temp_buffer, L"%d мс", config->get_left_wait());
                SetWindowText(t_fSliderText, temp_buffer);

                // First slider
            }

            {

                // Text over slider

                CreateWindowEx(0, L"STATIC", L"Задержка правой кнопки мыши", WS_CHILD | WS_VISIBLE,
                    8, 194, 220, 20, hwnd, (HMENU)FSLIDER_TEXT_LINK, NULL, NULL);

                // Text over slider

                // Second slider

                s_sSlider = CreateWindowEx(WS_EX_STATICEDGE, TRACKBAR_CLASS, NULL, WS_CHILD | WS_VISIBLE | TBS_HORZ | TBS_AUTOTICKS | BS_FLAT,
                    8, 215, 170, 30, hwnd, (HMENU)FSLIDER, NULL, NULL);

                SendMessage(s_sSlider, TBM_SETRANGE, TRUE, MAKELPARAM(10, 100));
                SendMessage(s_sSlider, TBM_SETPOS, TRUE, config->get_right_wait());

                t_sSliderText = CreateWindowEx(0, L"STATIC", NULL, WS_CHILD | WS_VISIBLE,
                    180, 219, 50, 20, hwnd, (HMENU)FSLIDER_TEXT_LINK, NULL, NULL);


                wchar_t second_temp_buffer[20];
                swprintf_s(second_temp_buffer, L"%d мс", config->get_right_wait());
                SetWindowText(t_sSliderText, second_temp_buffer);

                // Second slider
            }

            // create sliders

            // second child

            CheckDlgButton(hwnd, STATE_LINK, config->calculate_value_checkbox("state"));
            CheckDlgButton(hwnd, LBUTTON_LINK, config->calculate_value_checkbox("lbutton"));
            CheckDlgButton(hwnd, RBUTTON_LINK, config->calculate_value_checkbox("rbutton"));
            CheckDlgButton(hwnd, SETTINGS_LINK, config->calculate_value_checkbox("own_wait"));

            break;
        }

    case WM_COMMAND:
        {

            // State 
            
            AutoClicker->change_state(IsDlgButtonChecked(hwnd, STATE_LINK));

            // State

            // Buttons CLICKS

            AutoClicker->set_keys_available(IsDlgButtonChecked(hwnd, LBUTTON_LINK), IsDlgButtonChecked(hwnd, RBUTTON_LINK));

            // Buttons CLICKS

            // Own wait

            AutoClicker->change_own(IsDlgButtonChecked(hwnd, SETTINGS_LINK));

            // Own wait

            break;
        }
    case WM_HSCROLL:
        {
            // First slider
            {
                if ((HWND)lParam == s_fSlider)
                {
                    int current_value = SendMessage(s_fSlider, TBM_GETPOS, 0, 0);

                    config->set_left_wait(current_value);
                    AutoClicker->set_left_wait(current_value);

                    wchar_t text[20];
                    swprintf_s(text, L"%d мс", current_value);
                    SetWindowText(t_fSliderText, text);
                }
            }
            // First slider

            // Second slider
            {
                if ((HWND)lParam == s_sSlider)
                {
                    int current_value = SendMessage(s_sSlider, TBM_GETPOS, 0, 0);

                    config->set_right_wait(current_value);
                    AutoClicker->set_right_wait(current_value);

                    wchar_t text[20];
                    swprintf_s(text, L"%d мс", current_value);
                    SetWindowText(t_sSliderText, text);
                }
            }
            // Second slider
            break;
        }
    case WM_CTLCOLORSTATIC: 
        { 
            SetBkColor((HDC)wParam, BACKGROUND_COLOR); 
            return (LRESULT)hBrushColor; 
        }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            FillRect(hdc, &ps.rcPaint, hBrushColor);

            EndPaint(hwnd, &ps);
            break;
        }
    case WM_CLOSE:
        {
            PostQuitMessage(0);
            DeleteObject(hBrushColor);
            break;
        }
    case WM_DESTROY:
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
