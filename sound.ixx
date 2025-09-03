module;

#include <SFML/Audio.hpp>

export module sound;

export class Sound{
    public:
        Sound() : music("assets/music/theme.ogg"),
                  click_buffer("assets/music/Toom_Click.wav"),
                  click_sound(click_buffer),
                  buffer("assets/music/Victory.wav"),
                  sound(buffer),
                  tie_buffer("assets/music/tie.wav"),
                  tie_sound(tie_buffer){

            music.setLooping(true);
            music.setVolume(50);
            music.play();
        }

        void play_click_sound(){
            click_sound.play();
        }

        void play_victory_sound(){
            //sf::SoundBuffer buffer("assets/music/Victory.wav");
            //sound(buffer);
            sound.play();
        }

        void play_tie_sound(){
            // sf::SoundBuffer tie_buffer("assets/music/tie.wav");
            // sf::Sound tie_sound(buffer);
            tie_sound.play();
        }
    
    private:
        sf::SoundBuffer click_buffer;
        sf::Sound click_sound;

        sf::SoundBuffer buffer;
        sf::Sound sound;

        sf::SoundBuffer tie_buffer;
        sf::Sound tie_sound;

        sf::Music music;
};