========================================================================
       MICROSOFT FOUNDATION CLASS BIBLIOTHEK : HexTools
========================================================================

Wichig sind nur :

CBitWnd
CHexText

Vorgehen :

BitWnd.h,
BitWnd.cpp
HexText.h
HexText.cpp

einbinden

#include "Hexext.h"
#include "BitWnd.h"

in das Dlg.cpp file einbinden


In DoDataExchange:

DDX_Text in DDX_HexText �nden
bzw.
F�r ein IDC_MY_STATIC eine DDX_BitWnd einf�gen

That's it

Ich gehe davon aus, da� ich eine R�ckmeldung erhalte,
falls der Code bei Dir zum Einsatz kommt, und Du fair genug bist
mich in Aboutbox Dokumentation o.�. zu erw�hnen

Michael Schikora