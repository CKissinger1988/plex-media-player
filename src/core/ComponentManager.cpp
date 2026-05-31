#include <QObject>
#include <QtQml>
#include <qqmlwebchannel.h>

#include "ComponentManager.h"

#include "ai/AIComponent.h"
#include "ai/MediaScraper.h"
#include "display/DisplayComponent.h"
#include "input/InputComponent.h"
#include "player/PlayerComponent.h"
#include "power/PowerComponent.h"
#include "remote/RemoteComponent.h"
#include "server/HTTPServer.h"
#include "settings/SettingsComponent.h"
#include "system/SystemComponent.h"
#include "system/UpdaterComponent.h"

#if KONVERGO_OPENELEC
#include "system/openelec/OESystemComponent.h"
#endif

#include "QsLog.h"

// Custom deleter that does nothing for static singletons
struct NoDeleter {
    void operator()(ComponentBase*) const {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
ComponentManager::ComponentManager() : QObject(nullptr) {}

///////////////////////////////////////////////////////////////////////////////////////////////////
void ComponentManager::registerComponent(std::shared_ptr<ComponentBase> comp)
{
  if (m_components.contains(comp->componentName()))
  {
    QLOG_ERROR() << "Component" << comp->componentName() << "already registered!";
    return;
  }

  if (comp->componentInitialize())
  {
    QLOG_INFO() << "Component:" << comp->componentName() << "inited";
    m_components[comp->componentName()] = comp;

    // define component as property for qml
    m_qmlProperyMap.insert(comp->componentName(), QVariant::fromValue(comp.get()));
  }
  else
  {
    QLOG_ERROR() << "Failed to init component:" << comp->componentName();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void ComponentManager::initialize()
{
  // then settings, since all other components
  // might have some settings
  //
  registerComponent(std::shared_ptr<ComponentBase>(&SettingsComponent::Get(), NoDeleter()));

  // start our web server
  m_server = std::make_unique<HttpServer>(this);
  m_server->start();

  registerComponent(std::shared_ptr<ComponentBase>(&InputComponent::Get(), NoDeleter()));
  registerComponent(std::shared_ptr<ComponentBase>(&SystemComponent::Get(), NoDeleter()));
  registerComponent(std::shared_ptr<ComponentBase>(&DisplayComponent::Get(), NoDeleter()));
  registerComponent(std::shared_ptr<ComponentBase>(&UpdaterComponent::Get(), NoDeleter()));
  registerComponent(std::shared_ptr<ComponentBase>(&RemoteComponent::Get(), NoDeleter()));
  registerComponent(std::shared_ptr<ComponentBase>(&PlayerComponent::Get(), NoDeleter()));
  registerComponent(std::shared_ptr<ComponentBase>(&PowerComponent::Get(), NoDeleter()));
  registerComponent(std::shared_ptr<ComponentBase>(&AIComponent::Get(), NoDeleter()));
  registerComponent(std::shared_ptr<ComponentBase>(&MediaScraper::Get(), NoDeleter()));

#if KONVERGO_OPENELEC
  registerComponent(std::shared_ptr<ComponentBase>(&OESystemComponent::Get(), NoDeleter()));
#endif

  for (auto component : m_components.values())
    component->componentPostInitialize();
}

/////////////////////////////////////////////////////////////////////////////////////////
void ComponentManager::setWebChannel(QWebChannel* webChannel)
{
  for (auto comp : m_components.values())
  {
    if (comp->componentExport())
    {
      QLOG_DEBUG() << "Adding component:" << comp->componentName() << "to webchannel";
      webChannel->registerObject(comp->componentName(), comp.get());
    }
  }
}
