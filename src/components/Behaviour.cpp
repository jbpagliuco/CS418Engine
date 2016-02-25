#include "components/Behaviour.h"

CS418::Behaviour::Behaviour(const std::string &type) : GameComponent(type) { Enabled = true; }

CS418::Behaviour::~Behaviour(){ }