#include <Windows.h>
#include <stdlib.h>
#include <string>
#include <vector>

// Define resource IDs
#define IDD_EDIT_TASK 101
#define IDC_TITLE_EDIT 102
#define IDC_DESCRIPTION_EDIT 103
#define IDC_DEADLINE_EDIT 104
#define IDC_PRIORITY_EDIT 105

// Define structure for Task
struct Task {
    std::wstring title;
    std::wstring description;
    std::wstring deadline;
    std::wstring priority;
    bool completed;
};

// Global variables
std::vector<Task> tasks; // Vector to store tasks

// Function prototypes
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK EditTaskDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
void PopulateTasks(HWND hWnd);
void AddTask(HWND hWnd);
void EditTask(HWND hWnd, int index);
void DeleteTask(int index);
void MarkTaskAsCompleted(int index);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    // Register the window class
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEXW);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"MyWindowClass";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassExW(&wcex)) {
        MessageBoxW(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Create the window
    HWND hWnd = CreateWindowExW(0, L"MyWindowClass", L"To-Do List App", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 400, NULL, NULL, hInstance, NULL);

    if (hWnd == NULL) {
        MessageBoxW(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Show the window
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop
    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
        PopulateTasks(hWnd);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1: // Add Task button
            AddTask(hWnd);
            break;
        case 2: // Edit Task button
            EditTask(hWnd, HIWORD(wParam));
            break;
        case 3: // Delete Task button
            DeleteTask(HIWORD(wParam));
            break;
        case 4: // Mark Task as Completed button
            MarkTaskAsCompleted(HIWORD(wParam));
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}

void PopulateTasks(HWND hWnd) {
    // Dummy tasks for demonstration
    tasks.push_back({ L"Task 1", L"Description 1", L"2024-05-01", L"High", false });
    tasks.push_back({ L"Task 2", L"Description 2", L"2024-05-02", L"Medium", true });
    tasks.push_back({ L"Task 3", L"Description 3", L"2024-05-03", L"Low", false });

    // Display tasks in the UI
    int yOffset = 20;
    for (size_t i = 0; i < tasks.size(); i++) {
        // Create labels for task details
        CreateWindowW(L"STATIC", tasks[i].title.c_str(), WS_VISIBLE | WS_CHILD, 20, yOffset, 200, 20, hWnd, NULL, NULL, NULL);
        yOffset += 20;
    }

    // Add buttons for each task
    yOffset = 20;
    for (size_t i = 0; i < tasks.size(); i++) {
        // Add Task button
        CreateWindowW(L"BUTTON", L"Edit", WS_VISIBLE | WS_CHILD, 220, yOffset, 60, 20, hWnd, (HMENU)(i + 2), NULL, NULL);
        // Edit Task button
        CreateWindowW(L"BUTTON", L"Delete", WS_VISIBLE | WS_CHILD, 290, yOffset, 60, 20, hWnd, (HMENU)(i + 3), NULL, NULL);
        yOffset += 20;
    }

    // Add button for adding a new task
    CreateWindowW(L"BUTTON", L"Add Task", WS_VISIBLE | WS_CHILD, 20, yOffset, 100, 30, hWnd, (HMENU)1, NULL, NULL);
}

void AddTask(HWND hWnd) {
    // Logic for adding a new task
    MessageBoxW(NULL, L"Functionality for adding a new task will be implemented here.", L"Add Task", MB_OK);
}

void EditTask(HWND hWnd, int index) {
    // Launch the edit task dialog
    DialogBoxParamW(NULL, MAKEINTRESOURCEW(IDD_EDIT_TASK), hWnd, EditTaskDlgProc, (LPARAM)index);
}

void DeleteTask(int index) {
    // Logic for deleting an existing task
    MessageBoxW(NULL, L"Functionality for deleting an existing task will be implemented here.", L"Delete Task", MB_OK);
}

void MarkTaskAsCompleted(int index) {
    // Logic for marking a task as completed
    MessageBoxW(NULL, L"Functionality for marking a task as completed will be implemented here.", L"Mark Task as Completed", MB_OK);
}

INT_PTR CALLBACK EditTaskDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_INITDIALOG:
        // Initialize dialog controls
        SetDlgItemTextW(hwndDlg, IDC_TITLE_EDIT, tasks[lParam].title.c_str());
        SetDlgItemTextW(hwndDlg, IDC_DESCRIPTION_EDIT, tasks[lParam].description.c_str());
        SetDlgItemTextW(hwndDlg, IDC_DEADLINE_EDIT, tasks[lParam].deadline.c_str());
        SetDlgItemTextW(hwndDlg, IDC_PRIORITY_EDIT, tasks[lParam].priority.c_str());
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDOK:
            // Save changes and close dialog
            WCHAR title[256], description[256], deadline[256], priority[256];
            GetDlgItemTextW(hwndDlg, IDC_TITLE_EDIT, title, 256);
            GetDlgItemTextW(hwndDlg, IDC_DESCRIPTION_EDIT, description, 256);
            GetDlgItemTextW(hwndDlg, IDC_DEADLINE_EDIT, deadline, 256);
            GetDlgItemTextW(hwndDlg, IDC_PRIORITY_EDIT, priority, 256);
            tasks[lParam].title = title;
            tasks[lParam].description = description;
            tasks[lParam].deadline = deadline;
            tasks[lParam].priority = priority;
            EndDialog(hwndDlg, IDOK);
            return (INT_PTR)TRUE;
        case IDCANCEL:
            // Cancel editing and close dialog
            EndDialog(hwndDlg, IDCANCEL);
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

