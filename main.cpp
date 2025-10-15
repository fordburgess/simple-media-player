#include <iostream>
#include "SDL2/SDL.h"

static SDL_AudioDeviceID audioDevice = 0;

int main(int argc, char* argv[]) {

  // 1. initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    std::cout << "Could not initialize SDL\n";
    return -1;
  }

  SDL_AudioSpec wavspec;
  Uint8* wavbuf = NULL;
  Uint32 wavlen = 0;

  // 2. load file
  if (SDL_LoadWAV("sample.wav", &wavspec, &wavbuf, &wavlen) == NULL) {
    std::cerr << "Error: couldn't load wav file - " << SDL_GetError() << "\n";
    SDL_Quit();
    return 0;
  }

  SDL_AudioSpec desired;
  SDL_zero(desired);

#if 0
  desired.freq = 48000;
  desired.format = AUDIO_F32;
  desired.channels = 2;
  desired.samples = 4096;
  desired.callback = NULL;
#endif

  // 3. open audio device (something to play file e.g. speaker)
  audioDevice = SDL_OpenAudioDevice(NULL, 0, &wavspec, NULL, 0);

  // 4. send audio file info to device
  SDL_QueueAudio(audioDevice, wavbuf, wavlen);
  SDL_FreeWAV(wavbuf);

  // 5. set paused to false i.e. play file
  SDL_PauseAudioDevice(audioDevice, 0);

  SDL_Delay(10000);

  // 6. close and quit everything
  SDL_CloseAudioDevice(audioDevice);
  SDL_Quit();
  return 0;
}
