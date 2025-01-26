#include "InputPoller.h"

Bed::Event<Bed::InputData> Bed::InputPoller::InputEvent;
std::unordered_map<int, Bed::KeyState> Bed::InputPoller::m_LastKeyStates;