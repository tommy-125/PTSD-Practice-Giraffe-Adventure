#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

void App::Update() {

    // TODO: Add your own logics to finish the tasks in README.md

    auto pos = m_Giraffe->GetPosition();

    if (Util::Input::IsKeyPressed(Util::Keycode::UP))    pos.y += 5.0f;
    if (Util::Input::IsKeyPressed(Util::Keycode::DOWN))  pos.y -= 5.0f;
    if (Util::Input::IsKeyPressed(Util::Keycode::LEFT))  pos.x -= 5.0f;
    if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) pos.x += 5.0f;

    m_Giraffe->SetPosition(pos);

    if (m_Chest->GetVisibility() && m_Giraffe->IfCollides(m_Chest)) {
        m_Chest->SetVisible(false);
    }

    for (auto& door : m_Doors) {
        if (door->GetVisibility() && m_Giraffe->IfCollides(door)) {
            door->SetImage(GA_RESOURCE_DIR"/Image/Character/door_open.png");
        }
    }

    if (m_Phase == Phase::COUNTDOWN) {
        m_Ball->SetVisible(true);
        m_Ball->SetLooping(false);
        m_Ball->Play();
    }

    /*
     *  Do not touch the code below as they serve the purpose for validating the tasks,
     *  rendering the frame, and exiting the game.
    */

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (m_EnterDown) {
        if (!Util::Input::IsKeyPressed(Util::Keycode::RETURN)) {
            ValidTask();
        }
    }
    m_EnterDown = Util::Input::IsKeyPressed(Util::Keycode::RETURN);

    m_Root.Update();
}
