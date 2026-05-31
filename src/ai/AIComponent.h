#ifndef __AICOMPONENT_H__
#define __AICOMPONENT_H__

#include "core/ComponentManager.h"
#include "utils/Utils.h"
#include <QObject>

class AIComponent : public ComponentBase
{
  Q_OBJECT
  DEFINE_SINGLETON(AIComponent);

public:
  bool componentInitialize() override;
  const char* componentName() override { return "AI"; }
  bool componentExport() override { return true; }

public slots:
  QString processQuery(const QString& query);
  QString generateSubtitles(const QString& audioPath);
  QString getRecommendations(const QString& viewingHistory);

private:
  AIComponent();
  ~AIComponent() override;
};

#endif
