#include "Component.hpp"

namespace eng {

size_t Component::nextId = 1;

GameObject* Component::GetOwner() { return m_owner; }

} // namespace eng
