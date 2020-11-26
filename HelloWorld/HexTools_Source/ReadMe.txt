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

DDX_Text in DDX_HexText änden
bzw.
Für ein IDC_MY_STATIC eine DDX_BitWnd einfügen

That's it

Ich gehe davon aus, daß ich eine Rückmeldung erhalte,
falls der Code bei Dir zum Einsatz kommt, und Du fair genug bist
mich in Aboutbox Dokumentation o.ä. zu erwähnen

Michael Schikora