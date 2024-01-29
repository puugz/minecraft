//
// Created by Matej on 29/12/2023.
//

#pragma once

#define KWARK_KEY_DEFINITIONS \
    DEFINE_KEY(Space, 32) \
    DEFINE_KEY(Apostrophe, 39) \
    DEFINE_KEY(Comma, 44) \
    DEFINE_KEY(Minus, 45) \
    DEFINE_KEY(Period, 46) \
    DEFINE_KEY(Slash, 47) \
    DEFINE_KEY(Zero, 48) \
    DEFINE_KEY(One, 49) \
    DEFINE_KEY(Two, 50) \
    DEFINE_KEY(Three, 51) \
    DEFINE_KEY(Four, 52) \
    DEFINE_KEY(Five, 53) \
    DEFINE_KEY(Six, 54) \
    DEFINE_KEY(Seven, 55) \
    DEFINE_KEY(Eight, 56) \
    DEFINE_KEY(Nine, 57) \
    DEFINE_KEY(Semicolon, 59) \
    DEFINE_KEY(Equal, 61) \
    \
    DEFINE_KEY(A, 65) \
    DEFINE_KEY(B, 66) \
    DEFINE_KEY(C, 67) \
    DEFINE_KEY(D, 68) \
    DEFINE_KEY(E, 69) \
    DEFINE_KEY(F, 70) \
    DEFINE_KEY(G, 71) \
    DEFINE_KEY(H, 72) \
    DEFINE_KEY(I, 73) \
    DEFINE_KEY(J, 74) \
    DEFINE_KEY(K, 75) \
    DEFINE_KEY(L, 76) \
    DEFINE_KEY(M, 77) \
    DEFINE_KEY(N, 78) \
    DEFINE_KEY(O, 79) \
    DEFINE_KEY(P, 80) \
    DEFINE_KEY(Q, 81) \
    DEFINE_KEY(R, 82) \
    DEFINE_KEY(S, 83) \
    DEFINE_KEY(T, 84) \
    DEFINE_KEY(U, 85) \
    DEFINE_KEY(V, 86) \
    DEFINE_KEY(W, 87) \
    DEFINE_KEY(X, 88) \
    DEFINE_KEY(Y, 89) \
    DEFINE_KEY(Z, 90) \
    \
    DEFINE_KEY(LeftBracket, 91) \
    DEFINE_KEY(Backslash, 92) \
    DEFINE_KEY(RightBracket, 93) \
    DEFINE_KEY(GraveAccent, 96) \
    DEFINE_KEY(World1, 161) \
    DEFINE_KEY(World2, 162) \
    DEFINE_KEY(Escape, 256) \
    DEFINE_KEY(Enter, 257) \
    DEFINE_KEY(Tab, 258) \
    DEFINE_KEY(Backspace, 259) \
    DEFINE_KEY(Insert, 260) \
    DEFINE_KEY(Delete, 261) \
    DEFINE_KEY(ArrowRight, 262) \
    DEFINE_KEY(ArrowLeft, 263) \
    DEFINE_KEY(ArrowDown, 264) \
    DEFINE_KEY(ArrowUp, 265) \
    \
    DEFINE_KEY(PageUp, 266) \
    DEFINE_KEY(PageDown, 267) \
    DEFINE_KEY(Home, 268) \
    DEFINE_KEY(End, 269) \
    DEFINE_KEY(CapsLock, 280) \
    DEFINE_KEY(ScrollLock, 281) \
    DEFINE_KEY(NumLock, 282) \
    DEFINE_KEY(PrintScreen, 283) \
    DEFINE_KEY(Pause, 284) \
    \
    DEFINE_KEY(F1, 290) \
    DEFINE_KEY(F2, 291) \
    DEFINE_KEY(F3, 292) \
    DEFINE_KEY(F4, 293) \
    DEFINE_KEY(F5, 294) \
    DEFINE_KEY(F6, 295) \
    DEFINE_KEY(F7, 296) \
    DEFINE_KEY(F8, 297) \
    DEFINE_KEY(F9, 298) \
    DEFINE_KEY(F10, 299) \
    DEFINE_KEY(F11, 300) \
    DEFINE_KEY(F12, 301) \
    DEFINE_KEY(F13, 302) \
    DEFINE_KEY(F14, 303) \
    DEFINE_KEY(F15, 304) \
    DEFINE_KEY(F16, 305) \
    DEFINE_KEY(F17, 306) \
    DEFINE_KEY(F18, 307) \
    DEFINE_KEY(F19, 308) \
    DEFINE_KEY(F20, 309) \
    DEFINE_KEY(F21, 310) \
    DEFINE_KEY(F22, 311) \
    DEFINE_KEY(F23, 312) \
    DEFINE_KEY(F24, 313) \
    DEFINE_KEY(F25, 314) \
    \
    DEFINE_KEY(Keypad0, 320) \
    DEFINE_KEY(Keypad1, 321) \
    DEFINE_KEY(Keypad2, 322) \
    DEFINE_KEY(Keypad3, 323) \
    DEFINE_KEY(Keypad4, 324) \
    DEFINE_KEY(Keypad5, 325) \
    DEFINE_KEY(Keypad6, 326) \
    DEFINE_KEY(Keypad7, 327) \
    DEFINE_KEY(Keypad8, 328) \
    DEFINE_KEY(Keypad9, 329) \
    DEFINE_KEY(KeypadDecimal, 330) \
    DEFINE_KEY(KeypadDivide, 331) \
    DEFINE_KEY(KeypadMultiply, 332) \
    DEFINE_KEY(KeypadSubstract, 333) \
    DEFINE_KEY(KeypadAdd, 334) \
    DEFINE_KEY(KeypadEnter, 335) \
    DEFINE_KEY(KeypadEqual, 336) \
    \
    DEFINE_KEY(LeftShift, 340) \
    DEFINE_KEY(LeftControl, 341) \
    DEFINE_KEY(LeftAlt, 342) \
    DEFINE_KEY(LeftSuper, 343) \
    DEFINE_KEY(RightShift, 344) \
    DEFINE_KEY(RightControl, 345) \
    DEFINE_KEY(RightAlt, 346) \
    DEFINE_KEY(RightSuper, 347) \
    DEFINE_KEY(Menu, 348)

#define KWARK_MOUSE_BUTTON_DEFINITIONS \
    DEFINE_BTN(Left, 0) \
    DEFINE_BTN(Right, 1) \
    DEFINE_BTN(Middle, 2) \
    DEFINE_BTN(Mouse4, 3) \
    DEFINE_BTN(Mouse5, 4) \
    DEFINE_BTN(Mouse6, 5) \
    DEFINE_BTN(Mouse7, 6) \
    DEFINE_BTN(Mouse8, 7) \

#include "GLFW/glfw3.h"

namespace minecraft
{
    enum class Key
    {
#define DEFINE_KEY(name, value) name = value,
        KWARK_KEY_DEFINITIONS
#undef DEFINE_KEY
    };

    enum class MouseButton
    {
#define DEFINE_BTN(name, value) name = value,
        KWARK_MOUSE_BUTTON_DEFINITIONS
#undef DEFINE_BTN
    };

    namespace Input
    {
        struct ButtonState
        {
            bool pressed;
            bool down;
            bool released;
        };

        struct State
        {
            ButtonState keys[GLFW_KEY_LAST + 1];
            ButtonState mouse[GLFW_MOUSE_BUTTON_LAST + 1];
        };

        bool ctrl();
        bool shift();
        bool alt();
        bool super();

        bool pressed(Key key);
        bool down(Key key);
        bool released(Key key);

        bool pressed(MouseButton btn);
        bool down(MouseButton btn);
        bool released(MouseButton btn);
    }
}
