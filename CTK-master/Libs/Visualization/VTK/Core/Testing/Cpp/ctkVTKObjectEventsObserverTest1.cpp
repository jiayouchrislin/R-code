
// Qt includes
#include <QApplication>
#include <QDebug>
#include <QList>
#include <QTimer>

// CTKVTK includes
#include "ctkVTKObjectEventsObserver.h"

// STD includes
#include <cstdlib>
#include <iostream>

// VTK includes
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkObject.h>
#include <vtkSmartPointer.h>
#include <vtkTimerLog.h>

int ctkVTKObjectEventsObserverTest1( int argc, char * argv [] )
{
  QApplication app(argc, argv);
  
  int objects = 1000;
  int events = 100;
  
  vtkObject* obj = vtkObject::New();
  QObject*   topObject = new QObject(0);
  
  ctkVTKObjectEventsObserver* observer = new ctkVTKObjectEventsObserver(topObject);
  for (int i = 0; i < objects; ++i)
    {
    QTimer*    slotObject = new QTimer(topObject);
    observer->addConnection(obj, vtkCommand::ModifiedEvent,
      slotObject, SLOT(stop()));
    }

  vtkSmartPointer<vtkTimerLog> timerLog = 
    vtkSmartPointer<vtkTimerLog>::New();
  
  timerLog->StartTimer();
  for (int i = 0; i < events; ++i)
    {
    obj->Modified();
    }
  timerLog->StopTimer();
  
  double t1 = timerLog->GetElapsedTime();
  qDebug() << events << "events listened by" << objects << "objects (ctkVTKConnection): " << t1 << "seconds";

  obj->Delete();

  delete topObject;
  
  return EXIT_SUCCESS;
}
