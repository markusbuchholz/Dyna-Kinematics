#ifndef GAME_H
#define GAME_H

#include <QThread>

#include "rigid_body_simulator.h"
#include "world.h"
#include "resource_manager.h"
#include "renderer_2D.h"
#include "window.h"
#include "state.h"
#include "finite_state_machine.h"

class Game : public QThread
{
   Q_OBJECT

public:

   Game(QObject* parent, const std::shared_ptr<Window>& glfwWindow);
   ~Game();

   Game(const Game&) = delete;
   Game& operator=(const Game&) = delete;

   Game(Game&&) = delete;
   Game& operator=(Game&&) = delete;

   bool  initialize();
   void  executeGameLoop();

public slots:

   void changeScene(int index);

   void startSimulation();
   void pauseSimulation();
   void resetSimulation();

   void changeGravity(int state);

   void changeTimeStep(double timeStep);
   void changeCoefficientOfRestitution(double coefficientOfRestitution);

   void enableWireframeMode(bool enable);
   void enableRememberFrames(bool enable);
   void changeRememberFramesFrequency(int frequency);
   void enableAntiAliasing(bool enable);
   void changeAntiAliasingMode(int index);
   void enableRecordGIF(bool enable);

signals:

   void simulationError(int errorCode);

   void simulatorViewerClosed();

private:

   void  run() override;

   bool                                    mInitialized;
   bool                                    mSimulate;
   bool                                    mTerminate;
   float                                   mTimeStep;
   std::vector<glm::vec2>                  mSceneDimensions;

   bool                                    mRecordGIF;

   std::shared_ptr<Window>                 mWindow;

   std::shared_ptr<FiniteStateMachine>     mFSM;

   std::shared_ptr<Renderer2D>             mRenderer2D;

   ResourceManager<Shader>                 mShaderManager;

   std::shared_ptr<World>                  mWorld;
};

#endif
