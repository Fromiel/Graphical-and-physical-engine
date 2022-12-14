#include "Systems/KeyInput.h"
#include <algorithm>

std::vector<KeyInput*> KeyInput::_instances;

KeyInput::KeyInput(std::vector<int> keysToMonitor) : _isEnabled(true) {
    for (int key : keysToMonitor) {
        _keys[key] = false;
        _keysPressed[key] = false;
    }
    // Add this instance to the list of instances
    KeyInput::_instances.push_back(this);
}

KeyInput::~KeyInput() {
    // Remove this instance from the list of instances
    _instances.erase(std::remove(_instances.begin(), _instances.end(), this), _instances.end());
}

bool KeyInput::getIsKeyDown(int key) {
    bool result = false;
    if (_isEnabled) {
        std::map<int, bool>::iterator it = _keys.find(key);
        if (it != _keys.end()) {
            result = _keys[key];
        }
    }
    return result;
}

bool KeyInput::getIsKeyPressed(int key)
{
    bool result = false;
    if (_isEnabled) {
        std::map<int, bool>::iterator it = _keysPressed.find(key);
        if (it != _keysPressed.end()) {
            result = _keysPressed[key];
        }
    }
    _keysPressed[key] = false;
    return result;
}

void KeyInput::setIsKeyDown(int key, bool isDown) {
    std::map<int, bool>::iterator it = _keys.find(key);
    std::map<int, bool>::iterator it2 = _keysPressed.find(key);
    if (it == _keys.end()) return;
    
    _keys[key] = isDown;  
}


void KeyInput::setIsKeyPressed(int key, bool isPressed)
{
    std::map<int, bool>::iterator it = _keysPressed.find(key);
    if (it == _keysPressed.end()) return;

    _keysPressed[key] = isPressed;
}


void KeyInput::setupKeyInputs(GLFWwindow* window) {
    glfwSetKeyCallback(window, KeyInput::callback);
}

void KeyInput::callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Send key event to all KeyInput instances
    for (KeyInput* keyInput : _instances) {
        keyInput->setIsKeyDown(key, action != GLFW_RELEASE);
        keyInput->setIsKeyPressed(key, action == GLFW_PRESS);
    }
}