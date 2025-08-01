#pragma once

#include <msctf.h>
#include "initguid.h"

class CTextEditor;

typedef struct
{
    ITfRange *pRange;
    ITfMouseSink *pMouseSink;
} MOUSESINK;

class CTextStore : public ITextStoreACP, public ITfContextOwnerCompositionSink, public ITfMouseTrackerACP
{
  public:
    CTextStore(CTextEditor *pEditor)
    {
        _prgMouseSinks = NULL;
        _nMouseSinks = 0;
        _pEditor = pEditor;
        _pCurrentCompositionView = NULL;
        _cRef = 1;
    }
    ~CTextStore()
    {
    }

    //
    // IUnknown methods
    //
    STDMETHODIMP QueryInterface(REFIID riid, void **ppvObj);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    //
    // ITextStoreACP
    //
    STDMETHODIMP AdviseSink(REFIID riid, IUnknown *punk, DWORD dwMask);
    STDMETHODIMP UnadviseSink(IUnknown *punk);
    STDMETHODIMP RequestLock(DWORD dwLockFlags, HRESULT *phrSession);
    STDMETHODIMP GetStatus(TS_STATUS *pdcs);
    STDMETHODIMP QueryInsert(LONG acpInsertStart, LONG acpInsertEnd, ULONG cch, LONG *pacpResultStart,
                             LONG *pacpResultEnd);
    STDMETHODIMP GetSelection(ULONG ulIndex, ULONG ulCount, TS_SELECTION_ACP *pSelection, ULONG *pcFetched);
    STDMETHODIMP SetSelection(ULONG ulCount, const TS_SELECTION_ACP *pSelection);
    STDMETHODIMP GetText(LONG acpStart, LONG acpEnd, __out_ecount(cchPlainReq) WCHAR *pchPlain, ULONG cchPlainReq,
                         ULONG *pcchPlainOut, TS_RUNINFO *prgRunInfo, ULONG ulRunInfoReq, ULONG *pulRunInfoOut,
                         LONG *pacpNext);
    STDMETHODIMP SetText(DWORD dwFlags, LONG acpStart, LONG acpEnd, __in_ecount(cch) const WCHAR *pchText, ULONG cch,
                         TS_TEXTCHANGE *pChange);
    STDMETHODIMP GetFormattedText(LONG acpStart, LONG acpEnd, IDataObject **ppDataObject);
    STDMETHODIMP GetEmbedded(LONG acpPos, REFGUID rguidService, REFIID riid, IUnknown **ppunk);
    STDMETHODIMP InsertEmbedded(DWORD dwFlags, LONG acpStart, LONG acpEnd, IDataObject *pDataObject,
                                TS_TEXTCHANGE *pChange);
    STDMETHODIMP RequestSupportedAttrs(DWORD dwFlags, ULONG cFilterAttrs, const TS_ATTRID *paFilterAttrs);
    STDMETHODIMP RequestAttrsAtPosition(LONG acpPos, ULONG cFilterAttrs, const TS_ATTRID *paFilterAttrs, DWORD dwFlags);
    STDMETHODIMP RequestAttrsTransitioningAtPosition(LONG acpPos, ULONG cFilterAttrs, const TS_ATTRID *paFilterAttrs,
                                                     DWORD dwFlags);
    STDMETHODIMP FindNextAttrTransition(LONG acpStart, LONG acpHalt, ULONG cFilterAttrs, const TS_ATTRID *paFilterAttrs,
                                        DWORD dwFlags, LONG *pacpNext, BOOL *pfFound, LONG *plFoundOffset);
    STDMETHODIMP RetrieveRequestedAttrs(ULONG ulCount, TS_ATTRVAL *paAttrVals, ULONG *pcFetched);
    STDMETHODIMP GetEndACP(LONG *pacp);
    STDMETHODIMP GetActiveView(TsViewCookie *pvcView);
    STDMETHODIMP GetACPFromPoint(TsViewCookie vcView, const POINT *pt, DWORD dwFlags, LONG *pacp);
    STDMETHODIMP GetTextExt(TsViewCookie vcView, LONG acpStart, LONG acpEnd, RECT *prc, BOOL *pfClipped);
    STDMETHODIMP GetScreenExt(TsViewCookie vcView, RECT *prc);
    STDMETHODIMP GetWnd(TsViewCookie vcView, HWND *phwnd);
    STDMETHODIMP QueryInsertEmbedded(const GUID *pguidService, const FORMATETC *pFormatEtc, BOOL *pfInsertable);
    STDMETHODIMP InsertTextAtSelection(DWORD dwFlags, __in_ecount(cch) const WCHAR *pchText, ULONG cch, LONG *pacpStart,
                                       LONG *pacpEnd, TS_TEXTCHANGE *pChange);
    STDMETHODIMP InsertEmbeddedAtSelection(DWORD dwFlags, IDataObject *pDataObject, LONG *pacpStart, LONG *pacpEnd,
                                           TS_TEXTCHANGE *pChange);

    //
    // ITfContextOwnerCompositionSink
    //
    STDMETHODIMP OnStartComposition(ITfCompositionView *pComposition, BOOL *pfOk);

    STDMETHODIMP OnUpdateComposition(ITfCompositionView *pComposition, ITfRange *pRangeNew);

    STDMETHODIMP OnEndComposition(ITfCompositionView *pComposition);

    //
    // ITfMouseTrackerACP
    //
    STDMETHODIMP AdviseMouseSink(ITfRangeACP *range, ITfMouseSink *pSink, DWORD *pdwCookie);
    STDMETHODIMP UnadviseMouseSink(DWORD dwCookie);

    void OnSelectionChange()
    {
        if (_pSink)
            _pSink->OnSelectionChange();
    }

    void OnTextChange(LONG acpStart, LONG acpOldEnd, LONG acpNewEnd)
    {
        if (_pSink)
        {
            TS_TEXTCHANGE textChange;
            textChange.acpStart = acpStart;
            textChange.acpOldEnd = acpOldEnd;
            textChange.acpNewEnd = acpNewEnd;
            _pSink->OnTextChange(0, &textChange);
        }
    }

    void OnLayoutChange()
    {
        if (_pSink)
        {
            _pSink->OnLayoutChange(TS_LC_CHANGE, 0x01);
        }
    }

    ITfCompositionView *GetCurrentCompositionView()
    {
        return _pCurrentCompositionView;
    }

    void OnMouseEvent(UINT uEdge, UINT uQuadrant, DWORD dwBtnState, BOOL *pbEaten)
    {
        *pbEaten = FALSE;
        for (UINT i = 1; i < _nMouseSinks; i++)
        {
            if (_prgMouseSinks->pMouseSink)
            {
                _prgMouseSinks->pMouseSink->OnMouseEvent(uEdge, uQuadrant, dwBtnState, pbEaten);
                if (*pbEaten)
                    break;
            }
        }
    }

  private:
    void PrepareAttributes(ULONG cFilterAttrs, const TS_ATTRID *paFilterAttrs);

    CTextEditor *_pEditor;

    TS_ATTRVAL _attrval[8];
    int _nAttrVals;

    ITextStoreACPSink *_pSink;

    ITfCompositionView *_pCurrentCompositionView;

    MOUSESINK *_prgMouseSinks;
    UINT _nMouseSinks;

    long _cRef;
};
