#include <fmod.hpp>
#include <fmod_studio.hpp>
#include "fmod_errors.h"
#include <chrono>
#include <emscripten.h>
#include <iostream>
#include <sstream>

FMOD::Studio::System* studioSystem { nullptr };

void gameloopFunction()
{
    if (!studioSystem)
        return;

    studioSystem->update();
}

namespace {

void checkResult(FMOD_RESULT result)
{
    if (result == FMOD_OK) {
        return;
    }

    std::ostringstream oss;
    oss << "FMod Failed: (" << result << ") - " << FMOD_ErrorString(result);
    throw std::logic_error { oss.str() };
}
} // namespace

int main()
{

    checkResult(FMOD::Studio::System::create(&studioSystem));

    checkResult(studioSystem->initialize(10, // the max number of sounds playing
        FMOD_STUDIO_INIT_SYNCHRONOUS_UPDATE, // Synchronous update is required to run fmod via
                                             // emscripten, as there is no pthread support
        FMOD_INIT_NORMAL, // can be initialized normally
        nullptr));

    std::cout << "Emscripten FMod example" << std::endl;

    FMOD::Studio::Bank* bank;

    checkResult(
        studioSystem->loadBankFile("assets/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &bank));
    FMOD::Studio::Bank* stringsBank;
    checkResult(studioSystem->loadBankFile(
        "assets/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank));

    int eventCount { 0 };
    checkResult(bank->getEventCount(&eventCount));
    std::cout << "loaded N=" << eventCount << " events from bank" << std::endl;

    FMOD::Studio::EventDescription* description;
    checkResult(studioSystem->getEvent("event:/original_clemens", &description));
    FMOD::Studio::EventInstance* instance;
    checkResult(description->createInstance(&instance));
    checkResult(instance->start());

    std::cout << "start emscripten main loop" << std::endl;
    emscripten_set_main_loop(gameloopFunction, 0, 1);
    std::cout << "ended emscripten main loop" << std::endl;
    
    studioSystem->release();
    return 0;
}
