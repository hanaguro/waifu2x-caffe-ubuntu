#include "CControl.h"
#include "CDialog.h"


CDialog::CDialog() : mInitFunc(nullptr), mInitData(nullptr)
{
	mEventMap[WM_INITDIALOG] = stEvent([this](HWND hWnd, WPARAM wParam, LPARAM lParam, LPVOID){ SetControl(hWnd); if(mInitFunc) mInitFunc(hWnd, wParam, lParam, mInitData); }, nullptr);
	mEventMap[WM_CLOSE] = stEvent([this](HWND hWnd, WPARAM, LPARAM, LPVOID){ EndDialog(hWnd, 0); }, nullptr);
	mEventMap[WM_COMMAND] = stEvent([this](HWND hWnd, WPARAM wParam, LPARAM lParam, LPVOID){ CommandCallBack(hWnd, wParam, lParam); }, nullptr);
}

void CDialog::SetEventCallBack(const EventFunc &func, const LPVOID lpData, const UINT uMsg)
{
	if(uMsg == WM_INITDIALOG) // 特別に処理を挟まなくてはいけない関係上
	{
		mInitFunc = func;
		mInitData = lpData;
	}
	else
		mEventMap[uMsg] = stEvent(func, lpData);
}

void CDialog::SetCommandCallBack(const EventFunc &func, const LPVOID lpData, const UINT ResourceID)
{
	mCommandMap[ResourceID] = stCommand(func, lpData);
}

void CDialog::AddControl(CControl *pfunc)
{
	vControl.push_back(pfunc);
}

void CDialog::SetControl(HWND hWnd)
{
	for(std::vector<CControl*>::size_type i = 0; i < vControl.size(); i++)
		vControl[i]->RegisterFunc(hWnd);
}

INT_PTR CDialog::DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const auto it = mEventMap.find(uMsg);
	if(it != mEventMap.end())
	{
		it->second.pfunc(hWnd, wParam, lParam, it->second.lpData);
		return TRUE;
	}

	return FALSE;
}

void CDialog::CommandCallBack(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	const int ResourceID = LOWORD(wParam);

	auto it = mCommandMap.find(ResourceID);
	if(it != mCommandMap.end())
		it->second.pfunc(hWnd, wParam, lParam, it->second.lpData);
}
