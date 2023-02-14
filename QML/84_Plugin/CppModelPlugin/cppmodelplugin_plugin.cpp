#include "cppmodelplugin_plugin.h"

#include "cppmodel.h"

#include <qqml.h>

void CppModelPluginPlugin::registerTypes(const char *uri)
{
    // @uri com.pandaman.cppmodel
    qmlRegisterType<CppModel>(uri, 1, 0, "CppModel");
}

