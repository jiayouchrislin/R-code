/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.commontk.org/LICENSE

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

// QT includes
#include <QApplication>
#include <QTimer>

// CTK includes
#include "ctkExampleWorkflowStepUsingSignalsAndSlots.h"
#include "ctkWorkflowStep.h"
#include "ctkWorkflow.h"

// STD includes
#include <cstdlib>
#include <iostream>

//-----------------------------------------------------------------------------
int numberOfTimesEntryExitTest(ctkExampleWorkflowStepUsingSignalsAndSlots* step1=0, int step1Entry=0, int step1Exit=0, ctkExampleWorkflowStepUsingSignalsAndSlots* step2=0, int step2Entry=0, int step2Exit=0, ctkExampleWorkflowStepUsingSignalsAndSlots* step3=0, int step3Entry=0, int step3Exit=0, ctkExampleWorkflowStepUsingSignalsAndSlots* step4=0, int step4Entry=0, int step4Exit=0)
{
  if (step1)
    {
    if (step1->numberOfTimesRanOnEntry() != step1Entry || step1->numberOfTimesRanOnExit() != step1Exit)
      {
      return 0;
      }
    }

  if (step2)
    {
    if (step2->numberOfTimesRanOnEntry() != step2Entry || step2->numberOfTimesRanOnExit() != step2Exit)
      {
      return 0;
      }
    }

  if (step3)
    {
    if (step3->numberOfTimesRanOnEntry() != step3Entry || step3->numberOfTimesRanOnExit() != step3Exit)
      {
      return 0;
      }
    }

  if (step4)
    {
    if (step4->numberOfTimesRanOnEntry() != step4Entry || step4->numberOfTimesRanOnExit() != step4Exit)
      {
      return 0;
      }    
    }

  return 1;
}

//-----------------------------------------------------------------------------
int currentStepAndNumberOfTimesEntryExitTest(ctkWorkflow* workflow, ctkWorkflowStep* expectedStep, ctkExampleWorkflowStepUsingSignalsAndSlots* step1, int step1Entry, int step1Exit, ctkExampleWorkflowStepUsingSignalsAndSlots* step2, int step2Entry, int step2Exit, ctkExampleWorkflowStepUsingSignalsAndSlots* step3=0, int step3Entry=0, int step3Exit=0, ctkExampleWorkflowStepUsingSignalsAndSlots* step4=0, int step4Entry=0, int step4Exit=0)
{
  if (expectedStep)
    {
    if (workflow->currentStep() != expectedStep)
      {
      return 0;
      }
    }
  return numberOfTimesEntryExitTest(step1, step1Entry, step1Exit, step2, step2Entry, step2Exit, step3, step3Entry, step3Exit, step4, step4Entry, step4Exit);
}

//-----------------------------------------------------------------------------
int transitionTest(ctkWorkflow* workflow, int defaultTime, QApplication& app, ctkWorkflowStep* expectedStep, ctkExampleWorkflowStepUsingSignalsAndSlots* step1, int step1Entry, int step1Exit, ctkExampleWorkflowStepUsingSignalsAndSlots* step2, int step2Entry, int step2Exit, ctkExampleWorkflowStepUsingSignalsAndSlots* step3=0, int step3Entry=0, int step3Exit=0, ctkExampleWorkflowStepUsingSignalsAndSlots* step4=0, int step4Entry=0, int step4Exit=0)
{
  QTimer::singleShot(defaultTime, &app, SLOT(quit()));
  app.exec();
  return currentStepAndNumberOfTimesEntryExitTest(workflow, expectedStep, step1, step1Entry, step1Exit, step2, step2Entry, step2Exit, step3, step3Entry, step3Exit, step4, step4Entry, step4Exit);
}

//-----------------------------------------------------------------------------
int testStartWorkflow(ctkWorkflow* workflow, int defaultTime, QApplication& app, bool shouldRun, ctkWorkflowStep* expectedStep=0, ctkExampleWorkflowStepUsingSignalsAndSlots* step1=0, int step1Entry=0, int step1Exit=0, ctkExampleWorkflowStepUsingSignalsAndSlots* step2=0, int step2Entry=0, int step2Exit=0, ctkExampleWorkflowStepUsingSignalsAndSlots* step3=0, int step3Entry=0, int step3Exit=0, ctkExampleWorkflowStepUsingSignalsAndSlots* step4=0, int step4Entry=0, int step4Exit=0)
{
  workflow->start();
  QTimer::singleShot(defaultTime, &app, SLOT(quit()));
  app.exec();
  if (workflow->isRunning() != shouldRun)
    {
    return 0;
    }
  return currentStepAndNumberOfTimesEntryExitTest(workflow, expectedStep, step1, step1Entry, step1Exit, step2, step2Entry, step2Exit, step3, step3Entry, step3Exit, step4, step4Entry, step4Exit);
}

//-----------------------------------------------------------------------------
int testStopWorkflow(ctkWorkflow* workflow, int defaultTime, QApplication& app, ctkExampleWorkflowStepUsingSignalsAndSlots* step1, int step1Entry, int step1Exit, ctkExampleWorkflowStepUsingSignalsAndSlots* step2, int step2Entry, int step2Exit, ctkExampleWorkflowStepUsingSignalsAndSlots* step3=0, int step3Entry=0, int step3Exit=0, ctkExampleWorkflowStepUsingSignalsAndSlots* step4=0, int step4Entry=0, int step4Exit=0)
{
  workflow->stop();
  QTimer::singleShot(defaultTime, &app, SLOT(quit()));
  app.exec();
  if (workflow->isRunning())
    {
    return 0;
    }
  return numberOfTimesEntryExitTest(step1, step1Entry, step1Exit, step2, step2Entry, step2Exit, step3, step3Entry, step3Exit, step4, step4Entry, step4Exit);
}

//-----------------------------------------------------------------------------
int ctkWorkflowTest2(int argc, char * argv [] )
{
  QApplication app(argc, argv);
  int defaultTime = 100;

  // create the steps and the workflow
  ctkWorkflow *workflow = new ctkWorkflow();
  ctkWorkflowStep *step1 = new ctkWorkflowStep(workflow, "Step 1");
  step1->setName("Step 1");
  step1->setDescription("Description for step 1");
  ctkWorkflowStep *step2 = new ctkWorkflowStep(workflow, "Step 2");
  step2->setName("Step 2");
  step2->setDescription("Description for step 2");
  ctkWorkflowStep *step3 = new ctkWorkflowStep(workflow, "Step 3");
  step3->setName("Step 3");
  step3->setDescription("Description for step 3");
  ctkWorkflowStep *step4 = new ctkWorkflowStep(workflow, "Step 4");
  step4->setName("Step 4");
  step4->setDescription("Description for step 4");

  // create the qObjects that implement the required functions, and
  // communicate with the workflow using signals and slots
  ctkExampleWorkflowStepUsingSignalsAndSlots* qObject1 = new ctkExampleWorkflowStepUsingSignalsAndSlots;
  ctkExampleWorkflowStepUsingSignalsAndSlots* qObject2 = new ctkExampleWorkflowStepUsingSignalsAndSlots;
  ctkExampleWorkflowStepUsingSignalsAndSlots* qObject3 = new ctkExampleWorkflowStepUsingSignalsAndSlots;
  ctkExampleWorkflowStepUsingSignalsAndSlots* qObject4 = new ctkExampleWorkflowStepUsingSignalsAndSlots;

  // use the qObjects for validation
  QObject::connect(step1->ctkWorkflowStepQObject(), SIGNAL(invokeValidateCommand(const QString&)), qObject1, SLOT(validate(const QString&)));
  QObject::connect(qObject1, SIGNAL(validationComplete(bool, const QString&)), workflow, SLOT(evaluateValidationResults(bool, const QString&)));
  QObject::connect(step2->ctkWorkflowStepQObject(), SIGNAL(invokeValidateCommand(const QString&)), qObject2, SLOT(validate(const QString&)));
  QObject::connect(qObject2, SIGNAL(validationComplete(bool, const QString&)), workflow, SLOT(evaluateValidationResults(bool, const QString&)));
  // step 3's validation will always fail
  QObject::connect(step3->ctkWorkflowStepQObject(), SIGNAL(invokeValidateCommand(const QString&)), qObject3, SLOT(validateFails()));
  QObject::connect(qObject3, SIGNAL(validationComplete(bool, const QString&)), workflow, SLOT(evaluateValidationResults(bool, const QString&)));

  QObject::connect(step4->ctkWorkflowStepQObject(), SIGNAL(invokeValidateCommand(const QString&)), qObject4, SLOT(validate(const QString&)));
  QObject::connect(qObject4, SIGNAL(validationComplete(bool, const QString&)), workflow, SLOT(evaluateValidationResults(bool, const QString&)));

  // use the qObjects for entry processing
  QObject::connect(step1->ctkWorkflowStepQObject(), SIGNAL(invokeOnEntryCommand(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)), qObject1, SLOT(onEntry(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)));
  QObject::connect(qObject1, SIGNAL(onEntryComplete()), workflow, SLOT(processingAfterOnEntry()));
  QObject::connect(step2->ctkWorkflowStepQObject(), SIGNAL(invokeOnEntryCommand(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)), qObject2, SLOT(onEntry(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)));
  QObject::connect(qObject2, SIGNAL(onEntryComplete()), workflow, SLOT(processingAfterOnEntry()));
  QObject::connect(step3->ctkWorkflowStepQObject(), SIGNAL(invokeOnEntryCommand(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)), qObject3, SLOT(onEntry(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)));
  QObject::connect(qObject3, SIGNAL(onEntryComplete()), workflow, SLOT(processingAfterOnEntry()));
  QObject::connect(step4->ctkWorkflowStepQObject(), SIGNAL(invokeOnEntryCommand(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)), qObject4, SLOT(onEntry(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)));
  QObject::connect(qObject4, SIGNAL(onEntryComplete()), workflow, SLOT(processingAfterOnEntry()));

  // use the qObjects for exit processing
  QObject::connect(step1->ctkWorkflowStepQObject(), SIGNAL(invokeOnExitCommand(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)), qObject1, SLOT(onExit(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)));
  QObject::connect(qObject1, SIGNAL(onExitComplete()), workflow, SLOT(processingAfterOnExit()));
  QObject::connect(step2->ctkWorkflowStepQObject(), SIGNAL(invokeOnExitCommand(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)), qObject2, SLOT(onExit(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)));
  QObject::connect(qObject2, SIGNAL(onExitComplete()), workflow, SLOT(processingAfterOnExit()));
  QObject::connect(step3->ctkWorkflowStepQObject(), SIGNAL(invokeOnExitCommand(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)), qObject3, SLOT(onExit(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)));
  QObject::connect(qObject3, SIGNAL(onExitComplete()), workflow, SLOT(processingAfterOnExit()));
  QObject::connect(step4->ctkWorkflowStepQObject(), SIGNAL(invokeOnExitCommand(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)), qObject4, SLOT(onExit(const ctkWorkflowStep*, const ctkWorkflowInterstepTransition::InterstepTransitionType)));
  QObject::connect(qObject4, SIGNAL(onExitComplete()), workflow, SLOT(processingAfterOnExit()));

  step1->setHasValidateCommand(1);
  step2->setHasValidateCommand(1);
  step3->setHasValidateCommand(1);
  step4->setHasValidateCommand(1);

  step1->setHasOnEntryCommand(1);
  step2->setHasOnEntryCommand(1);
  step3->setHasOnEntryCommand(1);
  step4->setHasOnEntryCommand(1);

  step1->setHasOnExitCommand(1);
  step2->setHasOnExitCommand(1);
  step3->setHasOnExitCommand(1);
  step4->setHasOnExitCommand(1);
  
  // set the initial step (which sets the initial state)
  workflow->setInitialStep(step1);
  
  // add the first and second steps
  if (!workflow->addTransition(step1, step2))
    {
    std::cerr << "could not add 1st and 2nd step" << std::endl;
    return EXIT_FAILURE;
    }

  // add the third step
  if (!workflow->addTransition(step2, step3))
    {
    std::cerr << "could not add 3rd step" << std::endl;
    return EXIT_FAILURE;
    }

  // add the fourth step
  if (!workflow->addTransition(step3, step4))
    {
    std::cerr << "could not add 4rd step" << std::endl;
    return EXIT_FAILURE;
    }

  // start the workflow
  if (!testStartWorkflow(workflow, defaultTime, app, 1, step1, qObject1, true, 0, qObject2, 0, 0, qObject3, 0, 0, qObject4, 0, 0))
    {
    std::cerr << "error starting workflow";
    return EXIT_FAILURE;
    }

  // trigger transition to the next step
  workflow->goForward();
  if (!transitionTest(workflow, defaultTime, app, step2, qObject1, 1, 1, qObject2, 1, 0, qObject3, 0, 0, qObject4, 0, 0))
    {
    std::cerr << "error transitioning to step 2";
    return EXIT_FAILURE;
    }

  // trigger transition to the next step
  workflow->goForward();
  if (!transitionTest(workflow, defaultTime, app, step3, qObject1, 1, 1, qObject2, 1, 1, qObject3, 1, 0, qObject4, 0, 0))
    {
    std::cerr << "error transitioning to step 3";
    return EXIT_FAILURE;
    }

  // trigger transition to the next state (this should fail!)
  workflow->goForward();
  if (!transitionTest(workflow, defaultTime, app, step3, qObject1, 1, 1, qObject2, 1, 1, qObject3, 1, 0, qObject4, 0, 0))
    {
    std::cerr << "error after transition failure at step 3";
    return EXIT_FAILURE;
    }

  // make sure the workflow stops properly
  if (!testStopWorkflow(workflow, defaultTime, app, qObject1, 1, 1, qObject2, 1, 1, qObject3, 1, 1, qObject4, 0, 0))
    {
    std::cerr << "error after stopping workflow";
    return EXIT_FAILURE;
    }

  // handles deletions of the workflow, steps, states and transitions
  delete workflow;

  return EXIT_SUCCESS;
}
