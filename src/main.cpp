#include <iostream>
#include <QDebug>

//Plugin
#include <QPluginLoader>
#include "plugin/PluginInterface.hpp"
#include "plugin/GUIPluginInterface.hpp"
#include "plugin/PluginProcessor.hpp"

int main(int argc, char* argv[])
{
    std::cout << "hello Plugin Host~" << std::endl;
    qDebug() << "hello qDebug";

    QPluginLoader* pLoader = new QPluginLoader("/Users/bin/project/obc/OBC-PluginHost/build/lib/libObPlugin-examples-Mock.so");
    QObject *plugin = pLoader->instance();
    std::shared_ptr<OBC::Plugin::ObPluginSettingsWidget> currentSettingsWidget;


    if(plugin == nullptr) {
        const auto errorMessage = pLoader->errorString();
        qDebug() << "error Message from PluginLoader " << errorMessage;
    } else {


        qDebug() << plugin->objectName();
        auto pluginInterface = qobject_cast<OBC::Plugin::ObInterface*>(plugin);

        if(pluginInterface == nullptr) {
            qDebug() << "can not cover plugin into plugin interface!";
        }
    
        pluginInterface->InitializePlugin("settings", QJsonObject{});
        qDebug() << pluginInterface->GetKernel()->GetKernelProtocols();

        qDebug() << pLoader->metaData();
    
    }

    return 0;
}
