#include "Input.h"

void Input::UpdateKeys(){
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::UpdateMousePosition(){
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    m_MousePosition = Vector2D(mouseX, mouseY);
}

void Input::UpdateMouseClicks(){
    m_MouseStates = SDL_GetMouseState(nullptr, nullptr);
}

bool Input::GetKeyDown(SDL_Scancode key){
    return (m_KeyStates[key]);
}

bool Input::GetMouseClick(int SDL_CLICK){
    return (m_MouseStates & SDL_CLICK);
}

bool Input::GetKeyPressed(SDL_Scancode key){
    if (m_KeyStates[key] && m_LastKeyPressed != key) {
        m_LastKeyPressed = key;
        return true;
    }
    else if (!m_KeyStates[key] && m_LastKeyPressed == key) {
        m_LastKeyPressed = SDL_SCANCODE_UNKNOWN;
    }
    return false;
}

Vector2D& Input::GetMousePosition(){
    return m_MousePosition;
}