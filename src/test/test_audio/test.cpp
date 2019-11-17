
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>


////////////////////////////////////////////////////////////
/// Play a sound
///
////////////////////////////////////////////////////////////
void playSound()
{
    // Load a sound buffer from a wav file
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../../../interface/sound/WAV/deja_vu.wav"))
        return;

    // Display sound informations
    std::cout << "deja_vu.wav:" << std::endl;
    std::cout << " " << buffer.getDuration().asSeconds() << " seconds"       << std::endl;
    std::cout << " " << buffer.getSampleRate()           << " samples / sec" << std::endl;
    std::cout << " " << buffer.getChannelCount()         << " channels"      << std::endl;

    // Create a sound instance and play it
    sf::Sound sound(buffer);
    sound.play();

    // Loop while the sound is playing
    while (sound.getStatus() == sf::Sound::Playing)
    {
        // Leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));

        // Display the playing position
        std::cout << "\rPlaying... " << sound.getPlayingOffset().asSeconds() << " sec        ";
        std::cout << std::flush;
    }
    std::cout << std::endl << std::endl;
}


////////////////////////////////////////////////////////////
/// Play a music
///
////////////////////////////////////////////////////////////
void playMusic(const std::string& filename)
{
    // Load an ogg music file
    sf::Music music;
    if (!music.openFromFile("resources/" + filename))
        return;

    // Display music informations
    std::cout << filename << ":" << std::endl;
    std::cout << " " << music.getDuration().asSeconds() << " seconds"       << std::endl;
    std::cout << " " << music.getSampleRate()           << " samples / sec" << std::endl;
    std::cout << " " << music.getChannelCount()         << " channels"      << std::endl;

    // Play it
    music.play();

    // Loop while the music is playing
    while (music.getStatus() == sf::Music::Playing)
    {
        // Leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));

        // Display the playing position
        std::cout << "\rPlaying... " << music.getPlayingOffset().asSeconds() << " sec        ";
        std::cout << std::flush;
    }
    std::cout << std::endl << std::endl;
}


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    /*sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../../../interface/sound/WAV/one_punch.wav"))
        return 0;

     // Display sound informations
    std::cout << "deja_vu.wav:" << std::endl;
    std::cout << " " << buffer.getDuration().asSeconds() << " seconds"       << std::endl;
    std::cout << " " << buffer.getSampleRate()           << " samples / sec" << std::endl;
    std::cout << " " << buffer.getChannelCount()         << " channels"      << std::endl;

    // Create a sound instance and play it
    sf::Sound sound(buffer);
    sound.play();


    sf::SoundBuffer buffer2;
    
    if (!buffer2.loadFromFile("../../../interface/sound/WAV/deja_vu.wav"))
        return 0;

     // Display sound informations
    std::cout << "deja_vu.wav:" << std::endl;
    std::cout << " " << buffer.getDuration().asSeconds() << " seconds"       << std::endl;
    std::cout << " " << buffer.getSampleRate()           << " samples / sec" << std::endl;
    std::cout << " " << buffer.getChannelCount()         << " channels"      << std::endl;
    
    // Create a sound instance and play it
    sf::Sound sound2(buffer2);
    sf::sleep(sf::milliseconds(3000));
    sound2.play();
    // Play a sound
    //playSound();

    // Play music from an ogg file
    //playMusic("orchestral.ogg");

    // Play music from a flac file
    //playMusic("ding.flac");

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');

    return EXIT_SUCCESS;*/
    playSound();
    return 0;
}
