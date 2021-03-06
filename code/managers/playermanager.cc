//------------------------------------------------------------------------------
//  playermanager.cc
//  (C) 2020 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "application/stdneb.h"
#include "playermanager.h"
#include "input/inputserver.h"
#include "graphics/cameracontext.h"
#include "visibility/visibilitycontext.h"
#include "imgui.h"
#include "dynui/im3d/im3dcontext.h"
#include "graphicsfeature/graphicsfeatureunit.h"
#include "basegamefeature/managers/entitymanager.h"
#include "input/mouse.h"
#include "renderutil/mouserayutil.h"
#include "game/api.h"
#include "properties/input.h"

namespace Demo
{

__ImplementSingleton(PlayerManager)

//------------------------------------------------------------------------------
/**
*/
Game::ManagerAPI
PlayerManager::Create()
{
    n_assert(!PlayerManager::HasInstance());
    Singleton = n_new(PlayerManager);

    Game::ManagerAPI api;
    api.OnActivate = &PlayerManager::OnActivate;
    api.OnBeginFrame = &PlayerManager::OnBeginFrame;
    api.OnFrame = &PlayerManager::OnFrame;
    return api;
}

//------------------------------------------------------------------------------
/**
*/
void
PlayerManager::Destroy()
{
    n_assert(PlayerManager::HasInstance());
    n_delete(Singleton);
}

//------------------------------------------------------------------------------
/**
*/
void
PlayerManager::OnActivate()
{
    auto view = GraphicsFeature::GraphicsFeatureUnit::Instance()->GetDefaultView();
    auto stage = GraphicsFeature::GraphicsFeatureUnit::Instance()->GetDefaultStage();

    auto const windowId = Base::DisplayDeviceBase::Instance()->GetMainWindow();
    auto const displayMode = CoreGraphics::WindowGetDisplayMode(windowId);
    SizeT width = displayMode.GetWidth();
    SizeT height = displayMode.GetHeight();

    Game::EntityCreateInfo playerCreateInfo;
    playerCreateInfo.templateId = Game::GetTemplateId("Player/player"_atm);
    playerCreateInfo.immediate = true;
    Singleton->playerEntity = Game::CreateEntity(playerCreateInfo);

    GraphicsFeature::Camera camera = Game::GetProperty<GraphicsFeature::Camera>(Singleton->playerEntity, Game::GetPropertyId("Camera"_atm));
    camera.aspectRatio = (float)width / (float)height;
    camera.viewHandle = GraphicsFeature::GraphicsFeatureUnit::Instance()->GetDefaultViewHandle();
    Game::SetProperty<GraphicsFeature::Camera>(Singleton->playerEntity, Game::GetPropertyId("Camera"_atm), camera);

    //This is a different "camera", this should probably be called "player" or some such
    Singleton->camera.Setup({0, 5, -3}, {0,1,0});

    GraphicsFeature::GraphicsFeatureUnit::Instance()->AddRenderUICallback([]()
    {
        //static Math::line ray;
        //if (Input::InputServer::Instance()->GetDefaultMouse()->ButtonPressed(Input::MouseButton::Code::RightButton))
        //{
        //    const Math::mat4 proj = Singleton->camera.GetProjectionMatrix();
        //    ray = RenderUtil::MouseRayUtil::ComputeWorldMouseRay(
        //        Input::InputServer::Instance()->GetDefaultMouse()->GetScreenPosition(),
        //        1000.0f,
        //        Math::inverse(Singleton->camera.view),
        //        Math::inverse(proj),
        //        0.1f
        //    );
        //}
        //Im3d::Im3dContext::DrawLine(ray, 2.0f, { 1.0f, 0.3f, 0.0f, 1.0f });
    });
}

//------------------------------------------------------------------------------
/**
*/
void
PlayerManager::OnBeginFrame()
{
    auto& io = ImGui::GetIO();
    PlayerInput input = Game::GetProperty<PlayerInput>(Singleton->playerEntity, Game::GetPropertyId("PlayerInput"));
    
    Singleton->camera.Update(input);

    Game::SetProperty<Math::mat4>(Singleton->playerEntity, Game::GetPropertyId("WorldTransform"_atm), Math::inverse(Singleton->camera.GetTransform()));
}

//------------------------------------------------------------------------------
/**
*/
void
PlayerManager::OnFrame()
{
    
}

//------------------------------------------------------------------------------
/**
*/
PlayerManager::PlayerManager()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
PlayerManager::~PlayerManager()
{
    // empty
}

} // namespace Game


