#include "C:\Users\famou\OneDrive\Desktop\distortion\Recoil\Imgui\imgui.h"
#include "C:\Users\famou\OneDrive\Desktop\distortion\Recoil\Imgui\imgui_impl_dx9.h"
#include "C:\Users\famou\OneDrive\Desktop\distortion\Recoil\Imgui\imgui_impl_win32.h"
#include "Settings.h"
#include "Utils.h"
#include "Recoil.h"
#include <d3d9.h>
#include "skCrypter.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <thread>
#include <Windows.h>
#include <string>
#include <sstream>
#include <D3dx9math.h>
#include "xorstr.hpp"
#include <WinUser.h>
#include <fstream>
#include <shlobj_core.h>
#include <iomanip>
#include <cstring>
#include "lazy_importer.hpp"
#include "ra.h"
#include <chrono>
#include <thread>
#include "Auth/auth.hpp"



using namespace KeyAuth;
using namespace std;

// Data
static LPDIRECT3D9              g_pD3D = NULL;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

settings g_settings;

std::string name = skCrypt("rust").decrypt(); // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = skCrypt("qQlrEridG4").decrypt(); // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = skCrypt("e7aed29ec2a34945242e444d7fd7e2f989b0483ed5ab7e02268b89dbf43e9e98").decrypt(); // app secret, the blurred text on licenses tab and other tabs
std::string version = skCrypt("1.0").decrypt(); // leave alone unless you've changed version on website
std::string url = skCrypt("https://keyauth.win/api/1.2/").decrypt(); // change if you're self-hosting


api KeyAuthApp(name, ownerid, secret, version, url);


static inline void SetupImGuiStyle()
{
    constexpr auto ColorFromBytes = [](uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
    {
        return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0);
    };
    int asdb12895 = ra::nral();
    auto& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    const ImVec4 bgColor = ColorFromBytes(41, 43, 47);
    const ImVec4 titleColor = ColorFromBytes(32, 34, 37);
    const ImVec4 lightBgColor = ColorFromBytes(82, 82, 85);
    const ImVec4 veryLightBgColor = ColorFromBytes(90, 90, 95);

    const ImVec4 panelColor = ColorFromBytes(32, 34, 37);
    const ImVec4 panelHoverColor = ColorFromBytes(29, 151, 236);
    const ImVec4 panelActiveColor = ColorFromBytes(0, 119, 200);

    const ImVec4 textColor = ColorFromBytes(255, 255, 255);
    const ImVec4 textDisabledColor = ColorFromBytes(151, 151, 151);
    const ImVec4 borderColor = ColorFromBytes(78, 78, 78);


    colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
    colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    // orange title colors[ImGuiCol_TitleBgActive] = ImVec4(0.988f, 0.671f, 0.012f, 1.000f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);
    colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.988f, 0.670f, 0.011f, 1.00f);


    style.WindowRounding = 0.0f;
    style.ChildRounding = 0.0f;
    style.FrameRounding = 6.0f;
    style.GrabRounding = 6.0f;
    style.PopupRounding = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.TabRounding = 6.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.FramePadding = ImVec2(4.0f, 3.0f);
    style.ItemSpacing = ImVec2(4.0f, 4.0f);
    style.WindowPadding = ImVec2(8.0f, 4.0f);
    style.ScrollbarSize = 9.0f;


}


void m_124013()
{



    bool insert_held;

    if (g_settings.menukey == 0x00) {
        insert_held = (LI_FN(GetKeyState)(VK_F8) & 0x8000) || (LI_FN(GetKeyState)(VK_INSERT) & 0x8000) || (LI_FN(GetKeyState)(VK_UP) & 0x8000) || (LI_FN(GetKeyState)(g_settings.menukey) & 0x8000);
    }
    else {
        insert_held = (LI_FN(GetKeyState)(g_settings.menukey) & 0x8000);
    }

    static bool pressed_insert = false;
    //static bool was_tabbed_out_while_active = false;
    static HWND TaskBar = ::FindWindow(skCrypt(L"Shell_TrayWnd"), NULL);
    HWND foreground_window = GetForegroundWindow();
    //bool tabbed_into_rust_while_menu_active = (globals::menu_active && foreground_window == globals::rust);
    bool tabbed_out_while_menu_inactive = (foreground_window != globals::rust && !globals::menu_active);
    bool insert_instance = (!pressed_insert && insert_held);
    bool context = (foreground_window == globals::overlay || foreground_window == globals::rust);
    bool tabbed_out_while_menu_active = (!context && globals::menu_active);

    if (tabbed_out_while_menu_active)
    {
        utils::SetWindowClickable(false, globals::overlay);
        globals::menu_active = false;
        //SetWindowVisible(true, tWnd);
        utils::SetWindowVisible(true, TaskBar);
    }
    else if (insert_instance) //insert pressed ONCE
    {
        if (context) //if the person is either tabbed into the overlay or tabbed into the game
        {
            globals::menu_active = !globals::menu_active;

            if (globals::menu_active) //Menu is now OPENING
            {
                utils::SetWindowClickable(true, globals::overlay);
                utils::SetWindowVisible(false, TaskBar);
                SetForegroundWindow(globals::overlay); // bring the window to the front
            }
            else if (!globals::menu_active) // Menu is now CLOSING
            {
                utils::SetWindowClickable(false, globals::overlay);
                SetForegroundWindow(globals::rust); //move the game back to the front
                utils::SetWindowVisible(true, globals::rust);
                utils::SetWindowVisible(true, TaskBar);
            }
        }
        pressed_insert = true;
    }

    if (!globals::menu_active) //if the window is not active we attatch it to the game
    {
        SetWindowPos(globals::rust, globals::overlay, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
    else
    {
        if (!context) {
            SetWindowPos(globals::overlay, globals::rust, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        }

    }

    if (!insert_held && pressed_insert)
        pressed_insert = false;

}


int m0p333333()
{
    
    // Create application window

    WNDCLASSEX wc;
    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hIcon = LoadIcon(0, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(0, IDI_APPLICATION);
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = L" ";
    wc.lpszMenuName = L" ";
    wc.style = CS_VREDRAW | CS_HREDRAW;

    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    g_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
    try
    {
        if (!RegisterClassEx(&wc))
        {
            throw std::exception(skCrypt("Failed to register class"));
        }
            

        RECT desktop;

        const HWND hDesktop = LI_FN(GetDesktopWindow)();

        GetWindowRect(hDesktop, &desktop);

        int horizontal = desktop.right;
        int vertical = desktop.bottom;

        int w = utils::random_float(58, 109);
        int h = utils::random_float(44, 127);

        globals::full_screen = screen_size{ horizontal + h, vertical + w };

        globals::small_screen = screen_size{ 80 + h, 100 + w };

        globals::overlay = CreateWindowEx(WS_EX_TOOLWINDOW | WS_EX_LAYERED, L" ", L" ", WS_POPUP, 1, 1, globals::small_screen.w, globals::small_screen.h, 0, 0, 0, 0);
        SetLayeredWindowAttributes(globals::overlay, 0, 1.0f, LWA_ALPHA);
        SetLayeredWindowAttributes(globals::overlay, 0, RGB(0, 0, 0), LWA_COLORKEY);
        SetForegroundWindow(globals::rust);
        ShowWindow(globals::overlay, SW_SHOW);

        if (!CreateDeviceD3D(globals::overlay))
        {
            CleanupDeviceD3D();
            ::UnregisterClass(wc.lpszClassName, wc.hInstance);
            return 1;
        }

        ::ShowWindow(globals::overlay, SW_SHOWDEFAULT);
        ::UpdateWindow(globals::overlay);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.IniFilename = NULL;
        io.Fonts->AddFontFromFileTTF(XorStr("C:\\Windows\\Fonts\\verdana.ttf").c_str(), 12);
        io.Fonts->Build();


        SetupImGuiStyle();
        ImGui_ImplWin32_Init(globals::overlay);
        ImGui_ImplDX9_Init(g_pd3dDevice);

    }
    catch (std::exception e) {
        utils::echo_error(e, 0x06);
    }

    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        if (!IsWindow(globals::rust))
            break;

        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }

        // Start the Dear ImGui frame

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // 1. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        
        static string w12301[] = { XorStr("-"), XorStr("AK"), XorStr("LR"), XorStr("M2"), XorStr("HMLMG"), XorStr("MP5"), XorStr("Tommy"), XorStr("Custom"), XorStr("Semi"), XorStr("Python"), XorStr("M92") };
        static string scp50293[] = { XorStr("-"), XorStr("Handmade"), XorStr("Holo"), XorStr("8X"), XorStr("16X") };
        static string brl1205401[] = { XorStr("-"), XorStr("Muzzle boost"), XorStr("Muzzle brake") };
        static string enbl_r4y_01294[] = { XorStr("Disabled"), XorStr("Enabled") };
        static string hipfire[] = { XorStr("Hipfire: Off"), XorStr("Hipfire: On") };


        static string c_wepn_204142 = XorStr("-");
        static string c_scp_2712834 = XorStr("-");
        static string c_brl_5912942 = XorStr("-");
        static std::vector <string> c_hfre906102  = { XorStr("Hipfire: Off") };
        static std::vector <string> enabledd = { XorStr("Enabled") };

        bool* p_open = NULL;


        static std::vector <string> hpf_crnt1025129 = { c_hfre906102 };
        static std::vector <string> crnt_1t3am069294 = { c_wepn_204142, c_scp_2712834, c_brl_5912942 };
       

        if (globals::menu_active)
        {
            try
            {
                
                ImGui::Begin(skCrypt(" distortion.pro"), p_open, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);   // Create our main window and append into it.

                ImGui::SetWindowSize(ImVec2{ 250, 285 });

                static int tabb = 0;
                static bool setpos = false;
                if (setpos == false)
                {
                    ImGui::SetWindowPos(ImVec2{ 10, 10 });
                    setpos = true;
                }

                {ImGui::SameLine();
                if (ImGui::Button(skCrypt("Main"), ImVec2(87, 20)))
                {
                    tabb = 0;
                }
                ImGui::SameLine();
                if (ImGui::Button(skCrypt("Keybinds"), ImVec2(87, 20)))
                {
                    tabb = 1;
                }
                ImGui::SameLine();
                }

                if (tabb == 0) {
                    ImGui::Dummy(ImVec2(0.0f, 20.0f));
                    ImGui::Separator();

                    ImGui::Checkbox(skCrypt("Enable"), &g_settings.enabled);

                    ImGui::Checkbox(skCrypt("Show settings"), &g_settings.disabled);

                    ImGui::Checkbox(skCrypt("Hipfire"), &g_settings.hipfire);
                    
                    ImGui::Checkbox(skCrypt("Autofire"), &g_settings.autofire);

                    ImGui::Checkbox(skCrypt("Humanization"), &g_settings.humanization);

                    ImGui::Checkbox(skCrypt("Recoil smoothness"), &g_settings.smoothing);

                    if (g_settings.smoothing) {
                        ImGui::SetNextItemWidth(190);
                        ImGui::SliderFloat(skCrypt(" "), &g_settings.smoothness, 50, 100, (skCrypt("%.1f")));
                        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                        {
                            ImGui::SetTooltip(skCrypt("Controls how smooth your recoil control will be (higher = smoother, lower = more shaky)"));
                        }
                    }
                    // ImGui::Text(skCrypt("Stand multiplier"));
                    // ImGui::SliderFloat(skCrypt("##multiplier"), &g_settings.stand, 0, 10, (skCrypt("%1f")));


                    ImGui::Separator();




                    if (ImGui::BeginCombo(skCrypt("Weapon"), (const char*)(crnt_1t3am069294)[0].c_str(), /*ImGuiComboFlags_NoArrowButton |*/ ImGuiComboFlags_PopupAlignLeft)) // The second parameter is the label previewed before opening the combo.
                    {
                        for (int n = 0; n < IM_ARRAYSIZE(w12301); n++)
                        {
                            bool is_selected = (crnt_1t3am069294[0] == w12301[n]); // You can store your selection however you want, outside or inside your objects
                            if (ImGui::Selectable((const char*)w12301[n].c_str(), is_selected))
                                crnt_1t3am069294[0] = (const char*)w12301[n].c_str();
                            if (is_selected)
                            {
                                ImGui::SetItemDefaultFocus(); // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                            }
                        }
                        ImGui::EndCombo();
                    }



                    //ImGui::SetNextItemWidth(220);
                    if (ImGui::BeginCombo(skCrypt("Scope"), (const char*)crnt_1t3am069294[1].c_str(), /*ImGuiComboFlags_NoArrowButton |*/ ImGuiComboFlags_PopupAlignLeft)) // The second parameter is the label previewed before opening the combo.
                    {
                        for (int n = 0; n < IM_ARRAYSIZE(scp50293); n++)
                        {
                            bool is_selected = (crnt_1t3am069294[1] == scp50293[n]); // You can store your selection however you want, outside or inside your objects
                            if (ImGui::Selectable((const char*)scp50293[n].c_str(), is_selected))
                                crnt_1t3am069294[1] = scp50293[n];
                            if (is_selected)
                            {
                                ImGui::SetItemDefaultFocus(); // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                            }
                        }
                        ImGui::EndCombo();
                    }



                    //ImGui::SetNextItemWidth(220);
                    if (ImGui::BeginCombo(skCrypt("Barrel"), (const char*)crnt_1t3am069294[2].c_str(), /*ImGuiComboFlags_NoArrowButton |*/ ImGuiComboFlags_PopupAlignLeft)) // The second parameter is the label previewed before opening the combo.
                    {
                        for (int n = 0; n < IM_ARRAYSIZE(brl1205401); n++)
                        {
                            bool is_selected = (crnt_1t3am069294[2] == brl1205401[n]); // You can store your selection however you want, outside or inside your objects
                            if (ImGui::Selectable((const char*)brl1205401[n].c_str(), is_selected))
                                crnt_1t3am069294[2] = brl1205401[n];
                            if (is_selected)
                            {
                                ImGui::SetItemDefaultFocus(); // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                            }
                        }
                        ImGui::EndCombo();
                    }
                    ImGui::Checkbox(skCrypt("Auto sync game settings"), &g_settings.sync);

                    if (!g_settings.sync) {

                        ImGui::SliderFloat(skCrypt("Sensitivity"), &g_settings.sensitivity, 0, 2, (skCrypt("%.2f")));
                        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                            ImGui::SetTooltip(skCrypt("Look for input.sensitivity in console"));

                        ImGui::SliderFloat(skCrypt("ADS Sensitivity"), &g_settings.ads_sens, 0, 2, (skCrypt("%.2f")));
                        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                            ImGui::SetTooltip(skCrypt("Look for input.ads_sensitivity in console"));
                       
                        ImGui::SliderFloat(skCrypt("FOV"), &g_settings.fov, 70, 90, (skCrypt("%.2f")));
                        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                            ImGui::SetTooltip(skCrypt("Look for graphics.fov in console"));
                        
                    }

                    if (ImGui::Button(skCrypt("Save cfg"), ImVec2(87, 20)))
                        utils::save_cfg();
                    ImGui::SameLine();
                    if (ImGui::Button(skCrypt("Load cfg"), ImVec2(87, 20)))
                        utils::load_cfg();
                }



                else if (tabb == 1) {

                    ImGui::Dummy(ImVec2(0.0f, 20.0f));
                    ImGui::Hotkey(skCrypt("Menu                      "), &g_settings.menukey, ImVec2{ 180, 20 });
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                    {
                        ImGui::SetTooltip(skCrypt("Keybind for opening and closing the menu"));
                    }
                    ImGui::Hotkey(skCrypt("Enabled/Disabled     "), &g_settings.enable_hotkey, ImVec2{ 180,20 });
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                    {
                        ImGui::SetTooltip(skCrypt("Keybind for enabling and disabling the script"));
                    }
                    ImGui::Hotkey(skCrypt("Reset selection        "), &g_settings.reset, ImVec2{ 180, 20 });
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
                    {
                        ImGui::SetTooltip(skCrypt("Resets your current weapon/scope/barrel selections"));
                    }
                    ImGui::Hotkey(skCrypt("Hipfire                    "), &g_settings.hipfire_bind, ImVec2{ 180, 20 });

                    ImGui::Separator();

                    static HWND TaskBar = ::FindWindow(skCrypt(L"Shell_TrayWnd"), NULL);
                    if (ImGui::Button(skCrypt("Unload"), ImVec2(87, 20))) {
                        utils::SetWindowVisible(true, TaskBar);
                        exit(0);
                    }

                    static int open = 0;

                    ImGui::SameLine();
                    if (ImGui::Button(skCrypt("Custom"), ImVec2(87, 20)))
                    {
                        open = 1;
                    }

                    if (open == 1) {


                        ImGui::Begin(skCrypt(" keybinds"), p_open, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
                        ImGui::SetWindowSize(ImVec2(250, 285));
                        ImGui::Hotkey(skCrypt("Weapon cycle        "), &g_settings.weapon_cycler, ImVec2{ 180, 20 });
                        ImGui::Hotkey(skCrypt("Scope cycle           "), &g_settings.scope_cycler, ImVec2{ 180, 20 });
                        ImGui::Hotkey(skCrypt("Barrel cycle           "), &g_settings.barrel_cycler, ImVec2{ 180, 20 });
                        ImGui::Hotkey(skCrypt("AK Holo                 "), &g_settings.ak_holo, ImVec2{ 180, 20 });
                        ImGui::Hotkey(skCrypt("MP5 Holo               "), &g_settings.mp5_holo, ImVec2{ 180, 20 });
                    }
                }

                ImGui::End();
                
            }
            catch (std::exception e) {
                utils::echo_error(e, 0x04);
            }
        }
        else
        {

            if (g_settings.disabled)
            {
                //ImGui::PushFont(globals::font2);
                ImGui::Begin(skCrypt("distortion.pro"), p_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);  // Create our main window and append into it.
                ImGui::SetWindowSize(ImVec2{ 150, 65 });
                ImGui::SetWindowPos(ImVec2{ 0, 0 });
                if (crnt_1t3am069294[0] != (std::string)XorStr("-")) {
                    ImGui::Text((const char*)crnt_1t3am069294[0].c_str());
                }
                if (crnt_1t3am069294[1] != (std::string)XorStr("-")) {
                    ImGui::Text((const char*)crnt_1t3am069294[1].c_str());
                }
                if (crnt_1t3am069294[2] != (std::string)XorStr("-")) {
                    ImGui::Text((const char*)crnt_1t3am069294[2].c_str());
                }

                ImGui::Text((const char*)enabledd[0].c_str());
                ImGui::Text((const char*)hpf_crnt1025129[0].c_str());
                ImGui::End();

            }
        }

        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
       

        m_124013();
        if (g_settings.weapon != WEAPON_NONE)
            r012401::doo2135();

        static bool pressed_1 = false;
        static HWND TaskBar = ::FindWindow(skCrypt(L"Shell_TrayWnd"), NULL);


        try
        {
            bool rust_correct = utils::correct(XorStr("Rust"));

            if (rust_correct)
            {


                if (utils::key_down(g_settings.enable_hotkey)) {
                    g_settings.enabled = !g_settings.enabled;
                    enabledd[0] = enbl_r4y_01294[g_settings.enabled];
                    Sleep(250);
                }


                if (utils::key_down(g_settings.hipfire_bind)) {

                    g_settings.hipfire = !g_settings.hipfire;
                    c_hfre906102[0] = hipfire[g_settings.hipfire];
                    Sleep(250);
                }
                if (utils::key_down(g_settings.reset)) {

                    crnt_1t3am069294[0] = w12301[0];
                    crnt_1t3am069294[1] = scp50293[0];
                    crnt_1t3am069294[2] = brl1205401[0];
                    Sleep(250);
                }

                if (utils::key_down(g_settings.ak_holo))
                {

                    crnt_1t3am069294[0] = w12301[1];
                    crnt_1t3am069294[1] = scp50293[2];
                    Sleep(150);
                }

                if (utils::key_down(g_settings.mp5_holo))
                {

                    crnt_1t3am069294[0] = w12301[5];
                    crnt_1t3am069294[1] = scp50293[2];
                    Sleep(150);
                }

                if (utils::key_down(g_settings.m2_sil))
                {

                    crnt_1t3am069294[0] = w12301[3];
                    crnt_1t3am069294[1] = scp50293[3];
                    Sleep(150);
                }

                if (utils::key_down(g_settings.weapon_cycler) && !pressed_1)
                {
                    int current_index = std::distance(w12301, std::find(w12301, w12301 + IM_ARRAYSIZE(w12301), crnt_1t3am069294[0]));
                    int next_index;

                    if (current_index + 1 >= IM_ARRAYSIZE(w12301))
                    {
                        next_index = 0;
                    }
                    else
                    {
                        next_index = std::distance(w12301, std::find(w12301, w12301 + IM_ARRAYSIZE(w12301), w12301[current_index + 1]));
                    }

                    crnt_1t3am069294[0] = w12301[next_index];
                    pressed_1 = true;



                }
                else if (!utils::key_down(g_settings.weapon_cycler) && pressed_1)
                {
                    pressed_1 = false;
                }
                g_settings.weapon = std::distance(w12301, std::find(w12301, w12301 + IM_ARRAYSIZE(w12301), crnt_1t3am069294[0]));

                static bool pressed_2 = false;

                if (utils::key_down(g_settings.scope_cycler) && !pressed_2)
                {
                    int current_index = std::distance(scp50293, std::find(scp50293, scp50293 + IM_ARRAYSIZE(scp50293), crnt_1t3am069294[1]));
                    int next_index;

                    if (current_index + 1 >= IM_ARRAYSIZE(scp50293))
                    {
                        next_index = 0;
                    }
                    else
                    {
                        next_index = std::distance(scp50293, std::find(scp50293, scp50293 + IM_ARRAYSIZE(scp50293), scp50293[current_index + 1]));
                    }

                    crnt_1t3am069294[1] = scp50293[next_index];
                    pressed_2 = true;
                }
                else if (!utils::key_down(g_settings.scope_cycler) && pressed_2)
                {
                    pressed_2 = false;
                }
                g_settings.scope = std::distance(scp50293, std::find(scp50293, scp50293 + IM_ARRAYSIZE(scp50293), crnt_1t3am069294[1]));

                static bool pressed_3 = false;

                if (utils::key_down(g_settings.barrel_cycler) && !pressed_3)
                {
                    int current_index = std::distance(brl1205401, std::find(brl1205401, brl1205401 + IM_ARRAYSIZE(brl1205401), crnt_1t3am069294[2]));
                    int next_index;

                    if (current_index + 1 >= IM_ARRAYSIZE(brl1205401))
                    {
                        next_index = 0;
                    }
                    else
                    {
                        next_index = std::distance(brl1205401, std::find(brl1205401, brl1205401 + IM_ARRAYSIZE(brl1205401), brl1205401[current_index + 1]));
                    }
                    crnt_1t3am069294[2] = brl1205401[next_index];
                    pressed_3 = true;
                }
                else if (!utils::key_down(g_settings.barrel_cycler) && pressed_3)
                {
                    pressed_3 = false;
                }
                g_settings.barrel = std::distance(brl1205401, std::find(brl1205401, brl1205401 + IM_ARRAYSIZE(brl1205401), crnt_1t3am069294[2]));

            }

        }

        catch (std::exception e) {
            utils::echo_error(e, 0x05);
        }   

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(globals::overlay);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

void atuo()
{

    string asjdfnkj12 = ra::nsal();
    asjdfnkj12 = asjdfnkj12 + ra::nsal();

}

int g_g_vls210452() {

    LONG   lResult;
    HKEY   hKey;
    LPBYTE folder = new BYTE[MAX_PATH];
    DWORD  dwSize = sizeof(folder);
    char   value[64];
    DWORD  value_length = 64;
    DWORD  dwType = REG_SZ;

    lResult = RegOpenKey(HKEY_LOCAL_MACHINE,
        TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\"
            "Uninstall\\Steam App 252490"),
        &hKey);

    RegQueryValueExA(hKey, std::string(skCrypt("InstallLocation")).c_str(), NULL, &dwType,
        (LPBYTE)&value, &value_length);

    RegCloseKey(hKey);

    std::ifstream file;
    std::string line;
    int fileLine = 0;

    try {

        std::string client(skCrypt("\\cfg\\client.cfg"));

        file.open(std::string(value) + client); // path to rust

        while (std::getline(file, line))
        {
            fileLine++;

            if (line.find(XorStr("graphics.fov")) != std::string::npos) { // makes sure we read the correct line of the .cfg file
                std::string fovString = line;
                size_t pos = fovString.find(" ");

                fovString = fovString.substr(pos + 2);
                std::stringstream fovConv(fovString);

                fovConv >> g_settings.fov;
            }
            else if (line.find(XorStr("input.sensitivity")) != std::string::npos) { // makes sure we read the correct line of the .cfg file

                std::string sensString = line;
                size_t pos = sensString.find(" ");

                sensString = sensString.substr(pos + 2);
                std::stringstream sensConv(sensString);

                sensConv >> g_settings.sensitivity;

            }
            else if (line.find(XorStr("input.ads_sensitivity")) != std::string::npos) {
                std::string ads_sensString = line;
                size_t pos = ads_sensString.find(" ");

                ads_sensString = ads_sensString.substr(pos + 2);
                std::stringstream ads_sensConv(ads_sensString);

                ads_sensConv >> g_settings.ads_sens;
            }
        }

    }
    catch (const std::exception e) {
        utils::echo_error(e, 0x01);
    }
    file.close();

    return 0;

}

bool findvar(std::string line, std::string var, size_t start, size_t end, std::string& string_out)
{
    if (line.find(var) != std::string::npos) {

        std::string string = line;

        string_out = string.substr(start, end);
        return true;
    }
    return false;
}

int g_kbds96438() {
    LONG   lResult;
    HKEY   hKey;
    LPBYTE folder = new BYTE[MAX_PATH];
    DWORD  dwSize = sizeof(folder);
    char   value[64];
    DWORD  value_length = 64;
    DWORD  dwType = REG_SZ;

    lResult = RegOpenKey(HKEY_LOCAL_MACHINE,
        TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\"
            "Uninstall\\Steam App 252490"),
        &hKey);

    RegQueryValueExA(hKey, std::string(skCrypt("InstallLocation")).c_str(), NULL, &dwType,
        (LPBYTE)&value, &value_length);

    RegCloseKey(hKey);

    std::ifstream file;
    std::string line;
    int fileLine = 0;

    std::string client(skCrypt("\\cfg\\keys.cfg"));

    file.open(std::string(value) + client); // path to rust


    try {

        while (std::getline(file, line))
        {
            fileLine++;

            std::string attack, scope, crouch;

            if (findvar(line, XorStr("+duck"), line.find(XorStr(" ")) + 1, line.substr(line.find(XorStr(" ")) + 1).find(XorStr(" ")), crouch))
                g_settings.crouch_key = utils::rust_key_to_virtual_key(crouch.c_str());

            else if (findvar(line, XorStr("+attack\""), line.find(XorStr(" ")) + 1, line.substr(line.find(XorStr(" ")) + 1).find(XorStr(" ")), attack))
                g_settings.attack_key = utils::rust_key_to_virtual_key(attack.c_str());

            else if (findvar(line, XorStr("+attack2\""), line.find(XorStr(" ")) + 1, line.substr(line.find(XorStr(" ")) + 1).find(XorStr(" ")), scope))
                g_settings.scope_key = utils::rust_key_to_virtual_key(scope.c_str());
        }

    }
    catch (std::exception e) {

    }
    file.close();
    return 0;

}


// Main code
void Stealth()
{
    HWND Stealth;
    LI_FN(AllocConsole)();
    Stealth = FindWindowA(skCrypt("ConsoleWindowClass"), NULL);
    LI_FN(ShowWindow)(Stealth, 0);

}

// Main code
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{


    LI_FN(AllocConsole)();

    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    LI_FN(SetConsoleTextAttribute)(hCon, 15);

    FILE* newstdin = nullptr;
    FILE* newstdout = nullptr;

    LI_FN(freopen_s)(&newstdin, skCrypt("CONIN$"), skCrypt("r"), stdin);
    LI_FN(freopen_s)(&newstdout, skCrypt("CONOUT$"), skCrypt("w"), stdout);

    HWND console = LI_FN(GetConsoleWindow)();
    RECT r;
    LI_FN(GetWindowRect)(console, &r); //stores the console's current dimensions

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;


    LI_FN(GetWindowRect)(console, &r); //stores the console's current dimensions
    LI_FN(MoveWindow)(console, 800, 450, 300, 200, TRUE);
    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    LI_FN(GetCurrentConsoleFontEx)(hOut, 0, &fontex);
    fontex.FontWeight = 700;
    fontex.dwFontSize.X = 14;
    fontex.dwFontSize.Y = 14;
    LI_FN(SetCurrentConsoleFontEx)(hOut, NULL, &fontex);
    LI_FN(GetConsoleScreenBufferInfo)(hOut, &scrBufferInfo);
    short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
    short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;
    LI_FN(ShowScrollBar)(GetConsoleWindow(), SB_VERT, 0);
    // current screen buffer size
    short scrBufferWidth = scrBufferInfo.dwSize.X;


    // to remove the scrollbar, make sure the window height matches the screen buffer height
    COORD newSize;
    newSize.X = scrBufferWidth;
    newSize.Y = winHeight;

    // set the new screen buffer dimensions
    int Status = LI_FN(SetConsoleScreenBufferSize)(hOut, newSize);
    HWND rust = FindWindow(NULL, skCrypt(L"Rust"));

    while (FindWindow(NULL, skCrypt(L"Rust"))) {
        std::cout << skCrypt("\n Please close Rust");
        LI_FN(Sleep)(20);
        LI_FN(system)(skCrypt("cls"));
        if (!rust) {
            LI_FN(system)(skCrypt("cls"));
            break;
        }
    }

    std::cout << skCrypt("\n Please Wait...");
    KeyAuthApp.init();
    if (!KeyAuthApp.data.success)
    {
        std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
        LI_FN(Sleep)(1500);
        LI_FN(exit)(0);
    }
    LI_FN(Sleep)(1000);

    LI_FN(system)(skCrypt("cls"));
    std::cout << skCrypt("\n") << skCrypt(" 1. Login") << skCrypt("\n") << skCrypt(" 2. Register") << skCrypt("\n") << skCrypt(" 3. Extend Subscription") << skCrypt("\n") << skCrypt("\n") << skCrypt(" Choose option: ");

    int option;
    std::string username;
    std::string password;
    std::string key;
    std::cin >> option;

    switch (option)
    {
    case 1:
        LI_FN(system)(skCrypt("cls"));
        std::cout << skCrypt("\n Username: ");
        std::cin >> username;
        std::cout << skCrypt(" Password: ");
        std::cin >> password;
        KeyAuthApp.login(username, password);
        break;
    case 2:
        LI_FN(system)(skCrypt("cls"));
        std::cout << skCrypt("\n Enter username: ");
        std::cin >> username;
        std::cout << skCrypt(" Enter password: ");
        std::cin >> password;
        std::cout << skCrypt(" Enter serial key: ");
        std::cin >> key;
        KeyAuthApp.regstr(username, password, key);
        break;
    case 3:
        LI_FN(system)(skCrypt("cls"));
        std::cout << skCrypt("\n Enter username: ");
        std::cin >> username;
        std::cout << skCrypt(" Enter serial key: ");
        std::cin >> key;
        KeyAuthApp.upgrade(username, key);
        break;
    default:
        LI_FN(system)(skCrypt("cls"));
        std::cout << skCrypt("\n Invalid Selection");
        LI_FN(Sleep)(3000);
        LI_FN(exit)(0);
    }

    if (!KeyAuthApp.data.success)
    {
        std::cout << KeyAuthApp.data.message;
        LI_FN(Sleep)(2500);
        LI_FN(exit)(0);
    }

    LI_FN(system)(skCrypt("cls"));
    std::cout << skCrypt("\n Press enter to begin") << skCrypt("\n\n") << skCrypt(" Menu keys: F8, Up Arrow, INSERT");

    // check if enter key pressed yet

    while (1) {
        if (LI_FN(GetAsyncKeyState)(VK_RETURN) & 0x8000) {
            LI_FN(system)(skCrypt("cls"));
            std::cout << skCrypt("\n Open Rust\n Loader closing...");
            LI_FN(Sleep)(2000);
            Stealth();
            ra::f1_r04256();
            LI_FN(SetThreadPriority)(GetCurrentThread(), 15);
            g_kbds96438();
            g_g_vls210452();
            m0p333333();


            if (!FindWindow(NULL, skCrypt(L"Rust"))) {
                LI_FN(exit)(0);
            }
        }
    }
}


bool CreateDeviceD3D(HWND hWnd)
{
  
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;
    
    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

