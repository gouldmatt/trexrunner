/*
 * game.h
 *
 *  Created on: Mar 26, 2020
 *      Author: Elaine Crisostomo
 *		Audio
 */

#ifndef SRC_GAME_GAME_H_
#define SRC_GAME_GAME_H_

#include "../audio_helpers/AudioInitializer.h"
#include "../audio_helpers/Shared.h"
#include "audio.h"
#include <vector>

using namespace std;

class Game{

	public:

		Game();
		void gameplay(std::vector<Audio> &sound);

};





#endif /* SRC_GAME_GAME_H_ */
