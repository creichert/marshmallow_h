/*
 * Copyright 2011 Marshmallow Engine. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice, this list of
 *      conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice, this list
 *      of conditions and the following disclaimer in the documentation and/or other materials
 *      provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY MARSHMALLOW ENGINE ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MARSHMALLOW ENGINE OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those of the
 * authors and should not be interpreted as representing official policies, either expressed
 * or implied, of Marshmallow Engine.
 */

#include "core/identifier.h"
#include "game/enginebase.h"
#include "game/scenebase.h"
#include "game/scenemanager.h"
#include "game/tilemapscenelayer.h"
#include "graphics/factory.h"
#include "graphics/tileset.h"

MARSHMALLOW_NAMESPACE_USE;
using namespace Core;

class DemoScene : public Game::SceneBase
{
	bool m_init;

public:

	DemoScene(void)
	: SceneBase("DemoScene"),
	  m_init(false)
	  {}
	
	virtual ~DemoScene(void) {};

	VIRTUAL void activate(void)
	{
		SceneBase::activate();

		if (!m_init) {
			m_init = true;

			Graphics::SharedTextureData l_texture = Graphics::Factory::CreateTextureData();
			assert(l_texture->load("assets/sewer_tileset.png") && "Failed to load tilemap asset!");

			Graphics::SharedTilesetBase l_tileset = new Graphics::Tileset;
			l_tileset->setTextureData(l_texture);
			l_tileset->setTileSize(Math::Size2i(24, 24));

			Game::SharedTilemapSceneLayer l_tslayer = new Game::TilemapSceneLayer("tilemap", *this);
			l_tslayer->setSize(Math::Size2i(20, 15));
			l_tslayer->setTileSize(Math::Size2i(24, 24));
			l_tslayer->attachTileset(0, l_tileset.staticCast<Graphics::ITileset>());

			/* generate random tilemap */
			UINT16 *l_data = new UINT16[l_tslayer->size().area()];
			for (int i = 0; i < l_tslayer->size().area(); ++i)
				l_data[i] = rand() % 72; // 8 * 9 sample tileset

			l_tslayer->setData(l_data);

			pushLayer(l_tslayer.staticCast<Game::ISceneLayer>());
		}
	}

	VIRTUAL const Core::Type & type(void) const
	{
		static const Core::Type s_type("DemoScene");
		return(s_type);
	}
};

class Demo : public Game::EngineBase
{
	int m_stop_timer;
	Event::SharedEventListener m_debugListener;

public:

	Demo(void)
	: EngineBase(),
	  m_stop_timer(0)
	{
	}

	VIRTUAL bool initialize(void)
	{
		EngineBase::initialize();

		Game::SharedScene l_scene(new DemoScene);
		sceneManager()->pushScene(l_scene);

		return(true);
	}

	VIRTUAL void second(void)
	{
		EngineBase::second();

		if (++m_stop_timer == 10)
			stop();
	}
};

int
MMain(int argc, char *argv[])
{
	CHDIR(DEMO_CWD);
	return(Demo().run());
}
