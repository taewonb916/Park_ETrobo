#ifndef ETRC22_GAME_PLAY_H_
#define ETRC22_GAME_PLAY_H_

#include "info_type.h"

class BingoAgent {
 public:
  BingoAgent(bool kLcourse);
  ~BingoAgent();
  void SolveBingo();
};

#endif  // ETRC22_GAME_PLAY_H_