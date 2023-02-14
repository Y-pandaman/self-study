#ifndef CPPMODELPLUGIN_PLUGIN_H
#define CPPMODELPLUGIN_PLUGIN_H

#include <QQmlExtensionPlugin>

class CppModelPluginPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // CPPMODELPLUGIN_PLUGIN_H
