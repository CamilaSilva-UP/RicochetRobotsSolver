#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "State.h"

class Controller {
public:
  void moveRedLeft(State state);
  void moveRedRight(State state);
  void moveRedDown(State state);
  void moveRedUp(State state);

  void moveGreenLeft(State state);
  void moveGreenRight(State state);
  void moveGreenDown(State state);
  void moveGreenUp(State state);

  void moveBlueLeft(State state);
  void moveBlueRight(State state);
  void moveBlueDown(State state);
  void moveBlueUp(State state);

  void moveYellowLeft(State state);
  void moveYellowRight(State state);
  void moveYellowDown(State state);
  void moveYellowUp(State state);
};

#endif
