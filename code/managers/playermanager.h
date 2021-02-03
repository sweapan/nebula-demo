#pragma once
//------------------------------------------------------------------------------
/**
	@class	Demo::PlayerManager

	(C) 2020 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------
#include "core/refcounted.h"
#include "core/singleton.h"
#include "game/manager.h"
#include "util/stringatom.h"
#include "renderutil/freecamerautil.h"
#include "game/entity.h"
#include "camera.h"

namespace Demo
{

class PlayerManager
{
	__DeclareSingleton(PlayerManager);
public:
	/// Create the singleton
	static Game::ManagerAPI Create();

	/// Destroy the singleton
	static void Destroy();

	/// Get playerEntity
	inline Game::Entity GetPlayerEntity() { return playerEntity; };

	/// Get Camera object
	inline Demo::Camera* GetCamera() { return &camera; };
private:
	/// constructor
	PlayerManager();
	/// destructor
	~PlayerManager();

	/// called when attached to game server.
	static void OnActivate();
    /// called once before every rendered frame
    static void OnBeginFrame();
	/// called once every frame
	static void OnFrame();

	Game::Entity playerEntity;

	RenderUtil::FreeCameraUtil freeCamUtil;
	Demo::Camera camera;
};

} // namespace Demo
