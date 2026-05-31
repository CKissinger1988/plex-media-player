//
// Created by Tobias Hieta on 26/08/15.
//

#include "HelperSocket.h"
#include "Names.h"
#include "QsLog.h"
#include "UniqueApplication.h"
#include "Version.h"
#include "utils/Utils.h"
#include <QCoreApplication>
#include <UniqueApplication.h>

#ifdef ENABLE_CRASHDUMP
#include "CrashUploader.h"
#endif

using namespace QsLogging;

int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName(Names::MainName());
  QCoreApplication::setApplicationVersion(Version::GetVersionString());
  QCoreApplication::setOrganizationDomain("plex.tv");

  UniqueApplication uapp(nullptr, "samHelperUniqueApplication");
  if (!uapp.ensureUnique())
  {
    fprintf(stderr, "Other helper already running, refusing to start.\n");
    return EXIT_FAILURE;
  }

  // Note where the logfile is going to be
  qDebug("Logging to %s", qPrintable(Paths::logDir(Names::HelperName() + ".log")));

  // init logging.
  DestinationPtr dest = DestinationFactory::MakeFileDestination(
  Paths::logDir("samhelper.log"), EnableLogRotation, MaxSizeBytes(1024 * 1024), MaxOldLogCount(2));

  // make sure we get a fresh log
  dest->rotate();

  Logger::instance().addDestination(dest);
  Logger::instance().setLoggingLevel(DebugLevel);

  QLOG_DEBUG() << "Helper (" << Version::GetVersionString() << ") up and running";

  auto helperObject = new QObject;

  try
  {
#ifdef ENABLE_CRASHDUMP
    new CrashUploader(helperObject);
#endif
    new HelperSocket(helperObject);
  }
  catch (FatalException& e)
  {
    qWarning() << "Failed to setup the helper:" << e.message();
  }

  app.exec();

  delete helperObject;

  Logger::destroyInstance();
  return EXIT_SUCCESS;
}
