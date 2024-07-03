#pragma once
#include "OdaCommon.h"
#include "ExSystemServices.h"
#include "ExHostAppServices.h"

class MyServices : public ExSystemServices, public ExHostAppServices
{
protected:
    ODRX_USING_HEAP_OPERATORS(ExSystemServices);
    virtual void warning(const char*, const OdString& msg) ODRX_OVERRIDE
    {
        odPrintConsoleString(L"Exception: ");
        odPrintConsoleString(msg.c_str());
        odPrintConsoleString(L"\n");
    }
};

