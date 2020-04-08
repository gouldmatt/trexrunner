/*
 * audio.h
 *	Created by: Elaine Crisostomo
 *	Sourced from: Zynqbook, Chapter 4 - Adventures with Ip
 *	Book: http://www.zynqbook.com/
 *	Source repository: https://github.com/alexvonduar/Zynq-Book-Tutorial-Source
 *
 *	Audio class to create sound effects for the game
 *
 */

#ifndef __AUDIO_H_
#define __AUDIO_H_

#include "xparameters.h"

#include "../audio_helpers/AudioInitializer.h"


class Audio{
	public:
		Audio(); //default constructor
		void RecordAudio(); //Records audio from Line In to memory
		void PlayAudio();	//Plays audio from samples in memory

		u32 startLeft; //starting left sample
		u32 startRight; //starting right sample
		u32 max; //last audio sample recorded

	private:
		u32 in_left; //left data sample
		u32 in_right; //right data sample


};



#endif
