#pragma once

#include <Windows.h>
#include <msctf.h>

typedef struct
{
    UINT nStart;
    UINT nEnd;
    TF_DISPLAYATTRIBUTE da;
} COMPOSITIONRENDERINFO;

//----------------------------------------------------------------
//
//
//
//----------------------------------------------------------------

struct CHARINFO
{
    RECT rc;
    int GetWidth()
    {
        return rc.right - rc.left;
    }
};

//----------------------------------------------------------------
//
//
//
//----------------------------------------------------------------

typedef struct
{
    UINT nPos;
    UINT nCnt;
    CHARINFO *prgCharInfo;
} LINEINFO;

//----------------------------------------------------------------
//
//
//
//----------------------------------------------------------------

class CTextLayout
{
  public:
    CTextLayout()
    {
        _prgLines = NULL;
        _nLineCnt = 0;
        _fCaret = FALSE;
        _fInterimCaret = FALSE;
    }

    ~CTextLayout()
    {
        Clear();
    }

    BOOL Layout(HDC hdc, const WCHAR *psz, UINT nCnt);
    BOOL Render(HDC hdc, const WCHAR *psz, UINT nCnt, UINT nSelStart, UINT nSelEnd,
                const COMPOSITIONRENDERINFO *pCompositionRenderInfo, UINT nCompositionRenderInfo);
    BOOL RectFromCharPos(UINT nPos, RECT *prc);
    UINT CharPosFromPoint(POINT pt);
    UINT ExactCharPosFromPoint(POINT pt);
    UINT FineFirstEndCharPosInLine(UINT uCurPos, BOOL bFirst);
    void BlinkCaret(HDC hdc);
    void SetInterimCaret(BOOL fSet, UINT uPos);
    BOOL IsInterimCaret()
    {
        return _fInterimCaret;
    }

    int GetLineHeight()
    {
        return _nLineHeight;
    }

  private:
    HPEN CreateUnderlinePen(const TF_DISPLAYATTRIBUTE *pda, int nWidth);
    void Clear();

    int _nLineHeight;

    LINEINFO *_prgLines;
    UINT _nLineCnt;

    BOOL _fCaret;
    BOOL _fInterimCaret;
    RECT _rcCaret;
};
