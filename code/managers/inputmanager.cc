//------------------------------------------------------------------------------
//  inputmanager.cc
//  (C) 2020 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "application/stdneb.h"
#include "inputmanager.h"
#include "input/inputserver.h"
#include "input/mouse.h"
#include "input/keyboard.h"
#include "basegamefeature/managers/entitymanager.h"
#include "properties/input.h"
#include "imgui.h"

namespace Demo
{

__ImplementSingleton(InputManager)

//------------------------------------------------------------------------------
/**
*/
Game::ManagerAPI
InputManager::Create()
{
    n_assert(!InputManager::HasInstance());
    Singleton = n_new(InputManager);

    Game::FilterCreateInfo filterInfo;
    filterInfo.inclusive[0] = Game::GetPropertyId("PlayerInput");
    filterInfo.access[0] = Game::AccessMode::WRITE;

    filterInfo.numInclusive = 1;

    Game::Filter filter = Game::CreateFilter(filterInfo);


    Game::ProcessorCreateInfo processorInfo;
    processorInfo.async = false;
    processorInfo.filter = filter;
    processorInfo.name = "InputManager"_atm;
    processorInfo.OnBeginFrame = [](Game::Dataset data)
    {
        auto& io = ImGui::GetIO();
        //Game::TimeSource const* const time = Game::TimeManager::GetTimeSource(TIMESOURCE_GAMEPLAY);
        for (int v = 0; v < data.numViews; v++) 
        {
            Game::Dataset::CategoryTableView const& view = data.views[v];
            PlayerInput* const input = (PlayerInput*)view.buffers[0];

            for (IndexT i = 0; i < view.numInstances; ++i) 
            {
                input->forward = io.KeysDown[Input::Key::Up];
                input->backward = io.KeysDown[Input::Key::Down];
                input->left = io.KeysDown[Input::Key::Left];
                input->right = io.KeysDown[Input::Key::Right];

                input->clockwiseY = io.KeysDown[Input::Key::D];
                input->countercwY = io.KeysDown[Input::Key::A];
                input->clockwiseX = io.KeysDown[Input::Key::S];
                input->countercwX = io.KeysDown[Input::Key::W];

                input->up = io.KeysDown[Input::Key::RightShift];
                input->down = io.KeysDown[Input::Key::RightControl];

                input->reset = io.KeysDown[Input::Key::R];
            }
        }
    };
    Game::ProcessorHandle pHandle = Game::CreateProcessor(processorInfo);
    Game::ManagerAPI api;
    api.OnActivate = &InputManager::OnActivate;
    api.OnBeginFrame = &InputManager::OnBeginFrame;
    return api;
}

//------------------------------------------------------------------------------
/**
*/
void
InputManager::Destroy()
{
    n_assert(InputManager::HasInstance());
    n_delete(Singleton);
}

//------------------------------------------------------------------------------
/**
*/
void
InputManager::OnActivate()
{
}

//------------------------------------------------------------------------------
/**
*/
void
ProcessPlayerInput()
{
    Ptr<Input::Keyboard> const& keyboard = Input::InputServer::Instance()->GetDefaultKeyboard();
    Ptr<Input::Mouse> const& mouse = Input::InputServer::Instance()->GetDefaultMouse();

    //Game::FilterSet filter(
    //    {
    //        Game::GetPropertyId("PlayerInput"_atm)
    //    },
    //    {
    //        // no excludes
    //    }
    //    );

    //Game::Dataset data = Game::Query(filter);

    //for (auto tbl : data.tables)
    //{
    //    Demo::PlayerInput* pInputs = (Demo::PlayerInput*)tbl.buffers[0];

    //    for (int i = 0; i < tbl.numInstances; i++)
    //    {
    //        auto& playerInput = pInputs[i];
    //        if (playerInput.hasFocus)
    //        {
    //            playerInput.forward = (char)keyboard->KeyPressed(Input::Key::Code::W) - (char)keyboard->KeyPressed(Input::Key::Code::S);
    //            playerInput.strafe = (char)keyboard->KeyPressed(Input::Key::Code::Right) - (char)keyboard->KeyPressed(Input::Key::Code::Left);
    //        }
    //    }
    //}
}

//------------------------------------------------------------------------------
/**
*/
void
InputManager::OnBeginFrame()
{
    ProcessPlayerInput();
}

//------------------------------------------------------------------------------
/**
*/
InputManager::InputManager()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
InputManager::~InputManager()
{
    // empty
}


} // namespace Game


