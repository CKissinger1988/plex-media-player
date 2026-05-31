#ifndef OSXUTILS_H
#define OSXUTILS_H

#include <ApplicationServices/ApplicationServices.h>
#include <QString>

namespace OSXUtils
{
  QString ComputerName();
  OSStatus SendAppleEventToSystemProcess(AEEventID eventToSendID);

  void SetCursorVisible(bool visible);
}; // namespace OSXUtils

#endif /* OSXUTILS_H */
