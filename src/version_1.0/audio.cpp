#include "audio.h"

Audio::Audio(std::string audio_file, int team, float volume){
	_audio_file  = audio_file;
    _volume = volume ;



	switch (team){
		case 0: _death_audio = AUDIO_PATH_YELL1;
			break;

		case 1: _death_audio = AUDIO_PATH_YELL2;
			break;

		case 2: _death_audio = AUDIO_PATH_YELL3;
			break;

		case 3: _death_audio = AUDIO_PATH_YELL4;
			break;

		case 4: _death_audio = AUDIO_PATH_YELL5;
			break;

		case 5: _death_audio = AUDIO_PATH_YELL6;
			break;
	}


}

void Audio::sound_ultimate(){
	
    if (!buffer.loadFromFile(_audio_file))
        return;
    // Display sound informations -> facultatif
    // std::cout << _audio_file << std::endl;
    // std::cout << " " << buffer.getDuration().asSeconds() << " seconds"       << std::endl;
    // std::cout << " " << buffer.getSampleRate()           << " samples / sec" << std::endl;
    // std::cout << " " << buffer.getChannelCount()         << " channels"      << std::endl;

    // Create a sound instance and play it
    sound = sf::Sound(buffer);
    //sound.setVolume(_volume);
    sound.play();
}

void Audio::sound_death(){
	//sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(_death_audio))
        return;
    // Display sound informations -> facultatif
    //std::cout << _death_audio << std::endl;
    /*std::cout << " " << buffer.getDuration().asSeconds() << " seconds"       << std::endl;
    std::cout << " " << buffer.getSampleRate()           << " samples / sec" << std::endl;
    std::cout << " " << buffer.getChannelCount()         << " channels"      << std::endl;*/

    // Create a sound instance and play it
    sound = sf::Sound(buffer);
    
    sound.play();
}


void Audio::shock_sound(){
    if ( buffer_shock.getDuration().asSeconds() < 0.1)
        if (!buffer_shock.loadFromFile(AUDIO_PATH_SHOCK))
            return;
    // Display sound informations -> facultatif
    //std::cout << AUDIO_PATH_SHOCK << std::endl;
    //std::cout << " " << buffer.getDuration().asSeconds() << " seconds"       << std::endl;
    //std::cout << " " << buffer.getSampleRate()           << " samples / sec" << std::endl;
    //std::cout << " " << buffer.getChannelCount()         << " channels"      << std::endl;

    // Create a sound instance and play it
    sound_shock = sf::Sound(buffer_shock);
    sound_shock.setVolume(10);
    sound_shock.play();
}

void Audio::dodge_sound(){
    //if ( buffer_tp.getDuration().asSeconds() < 0.1)
    if (!buffer_tp.loadFromFile(AUDIO_PATH_TP))
        return;
    // Display sound informations -> facultatif
    //std::cout << AUDIO_PATH_TP << std::endl;
    //std::cout << " " << buffer.getDuration().asSeconds() << " seconds"       << std::endl;
    //std::cout << " " << buffer.getSampleRate()           << " samples / sec" << std::endl;
    //std::cout << " " << buffer.getChannelCount()         << " channels"      << std::endl;

    // Create a sound instance and play it
    sound_tp = sf::Sound(buffer_tp);
    sound_tp.setVolume(10);
    sound_tp.play();
}












