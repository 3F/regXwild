#ifndef PROPERTY_GRID_WRAPPER_SAMPLE__H
#define PROPERTY_GRID_WRAPPER_SAMPLE__H

#include "../CGrid/CGrid.h"
using namespace net::r_eg::ui;

class Sample: public CDialogImpl<Sample>, ICGridEventKeys
{
public:
    enum{ IDD = IDD_MAINFRM };

    CGrid grid;

    BEGIN_MSG_MAP(Sample)
        MESSAGE_HANDLER(WM_INITDIALOG, onInitDialog)
        COMMAND_ID_HANDLER(IDCANCEL, onCancel)
        NOTIFY_CODE_HANDLER(PIN_CLICK, onGridItemClick);
        NOTIFY_CODE_HANDLER(PIN_SELCHANGED, onGridItemSelected);
        NOTIFY_CODE_HANDLER(PIN_ITEMCHANGED, onGridItemChanged);
        REFLECT_NOTIFICATIONS()
    END_MSG_MAP()

    LRESULT onKeyHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
    {
        ATLTRACE(_T("onKeyHandler :: [%d, %d] :: uMsg = %d, WPARAM = %d, LPARAM = %d \n"), 
                grid.GetSelectedIndex(), grid.GetSelectedColumn(), wParam, lParam);

        switch(uMsg){
            case WM_KEYDOWN:{
                bHandled = FALSE;
                return 0;
            }
            case WM_KEYUP:{
                bHandled = FALSE;
                return 0;
            }
            case WM_CHAR:{
                bHandled = FALSE;
                return 0;
            }
        }
        bHandled = FALSE;
        return 0;
    }

    void insertEmpty()
    {
        TCGridItemCustom btnInvert;
        btnInvert.caption     = _T("~");
        btnInvert.flags       = DT_SINGLELINE | DT_VCENTER | DT_CENTER;
        btnInvert.offset.top  = 4;

        int idx = grid.InsertItem(grid.GetSelectedIndex() + 1, CGridItem::ButtonPush(false, btnInvert));
        
        std::vector<LPCTSTR> types;
        types.push_back(_T("File & Path"));
        types.push_back(_T("Connection"));
        types.push_back(_T("User"));
        types.push_back(_T("Local path - status"));
        types.push_back(_T("Size"));

        TCGridItemCustom listTypes;
        listTypes.offset.right = 70;

        grid.SetSubItem(idx, 1, CGridItem::ListBox(types, listTypes, 2));
        grid.SetSubItem(idx, 2, CGridItem::EditBox(_T(""), this));
        grid.SetSubItem(idx, 3, CGridItem::Button(_T("+")));
        grid.SetSubItem(idx, 4, CGridItem::Button(_T("-")));
    }

    LRESULT onInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
    {
        CenterWindow();

        RECT rc = {0, 0, 360, 190};
        grid.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VSCROLL | LVS_REPORT | LVS_NOCOLUMNHEADER, WS_EX_CLIENTEDGE);
        grid.SetExtendedGridStyle(PGS_EX_SINGLECLICKEDIT /*| PGS_EX_NOGRID*/ | PGS_EX_NOSHEETNAVIGATION);

        grid.InsertColumn(0, _T("Invert"),  LVCFMT_LEFT, 14, 0);
        grid.InsertColumn(1, _T("Type"),    LVCFMT_LEFT, 70, 0);
        grid.InsertColumn(2, _T("Filter"),  LVCFMT_LEFT, 114, 0);
        grid.InsertColumn(3, _T("Add"),     LVCFMT_LEFT, 14, 0);
        grid.InsertColumn(4, _T("Del"),     LVCFMT_LEFT, 14, 0);

        insertEmpty();
        return TRUE;
    }

    LRESULT onGridItemClick(int idCtrl, LPNMHDR pnmh, BOOL& /*bHandled*/)
    {
        switch(grid.GetSelectedColumn()){
            case 3:{
                insertEmpty();
                return 0;
            }
            case 4:{
                if(grid.GetItemCount() < 2){
                    return 0;
                }
                grid.DeleteItem(grid.GetSelectedIndex());
                return 1;
            }
        }
        return 0;
    }

    void propInfo(LPCTSTR fn, int idCtrl, LPNMHDR pnmh)
    {
        LPNMPROPERTYITEM pnpi = (LPNMPROPERTYITEM)pnmh;
        if(pnpi->prop == NULL){
            return;
        }

        TCHAR valueItem[100] = {0};      
        pnpi->prop->GetDisplayValue(valueItem, sizeof(valueItem) / sizeof(TCHAR));
        
        CComVariant valueProp;
        pnpi->prop->GetValue(&valueProp);
        valueProp.ChangeType(VT_BSTR);
        
        ATLTRACE(_T("%s [%d, %d] :: item: '%s', prop: '%s', name: '%s' :: idCtrl = %d \n"),
                    fn, grid.GetSelectedIndex(), grid.GetSelectedColumn(), valueItem, valueProp.bstrVal, pnpi->prop->GetName(), idCtrl);
    }

    LRESULT onGridItemSelected(int idCtrl, LPNMHDR pnmh, BOOL& /*bHandled*/)
    {
        propInfo(_T("onGridItemSelected"), idCtrl, pnmh);
        return 0;
    }

    LRESULT onGridItemChanged(int idCtrl, LPNMHDR pnmh, BOOL& /*bHandled*/)
    {
        propInfo(_T("onGridItemChanged"), idCtrl, pnmh);
        return 0;
    }

    LRESULT onCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
    {
        EndDialog(wID);
        return 0;
    }
};

#endif // PROPERTY_GRID_WRAPPER_SAMPLE__H
