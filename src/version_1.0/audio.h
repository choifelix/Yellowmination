#ifndef AUDIO_HH_
#define AUDIO_HH_

#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "path.h"
#include <array>


/****************************************************/
/* Classe qui gere le son               	        */
/****************************************************/
class Audio{
 	public:
 		Audio(std::string audio_file, int team, float volume);
  		~Audio(){}
 		void sound_ultimate();
 		void sound_death();
 		void shock_sound();
 		void dodge_sound();

 	private:
 		std::string _audio_file;
 		std::string _death_audio;

 		sf::SoundBuffer buffer;
 		sf::Sound sound;

 		sf::SoundBuffer buffer_shock;
 		sf::Sound sound_shock;

 		sf::SoundBuffer buffer_tp;
 		sf::Sound sound_tp;

 		//std::array<sf::SoundBuffer, 3> sound_buffers = { sf::SoundBuffer(),sf::SoundBuffer(),sf::SoundBuffer() } ;
 		//std::array<sf::Sound, 3> _sounds = {sf::Sound(),sf::Sound(),sf::Sound()};


 		float _volume;
};

#endif
