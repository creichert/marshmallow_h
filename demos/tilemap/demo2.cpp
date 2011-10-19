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

#include <core/identifier.h>
#include <core/logger.h>

#include <graphics/factory.h>
#include <graphics/tileset.h>
#include <graphics/transform.h>
#include <graphics/viewport.h>

#include <game/enginebase.h>
#include <game/entity.h>
#include <game/entityscenelayer.h>
#include <game/scenebase.h>
#include <game/scenemanager.h>
#include <game/textcomponent.h>

#define TIMEOUT 16
#define MESSAGE "Marshmallow!\n123456790~!@#$%%^\nSecond %d"

MARSHMALLOW_NAMESPACE_USE;

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
			l_texture->load("assets/terminus.png");
			assert(l_texture->isLoaded() && "Failed to load tilemap asset!");

			Graphics::SharedTilesetBase l_tileset = new Graphics::Tileset;
			l_tileset->setTileSize(Math::Size2i(16, 32));
			l_tileset->setTextureData(l_texture);

			Game::SharedEntitySceneLayer l_elayer = new Game::EntitySceneLayer("entity", *this);
			Game::SharedEntity l_entity = new Game::Entity("text", *l_elayer);
			Game::SharedTextComponent l_tcomp = new Game::TextComponent("txt", *l_entity);
			l_elayer->addEntity(l_entity);
			l_tcomp->text() = "Hello World!";
			l_tcomp->tileset() = l_tileset.staticCast<Graphics::ITileset>();
			l_entity->pushComponent(l_tcomp.staticCast<Game::IComponent>());
			pushLayer(l_elayer.staticCast<Game::ISceneLayer>());
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

public:

	Demo(void)
	: EngineBase(60, 60),
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

		if (++m_stop_timer == TIMEOUT)
			stop();

		Game::SharedEntitySceneLayer l_eslayer =
		    sceneManager()->activeScene()->getLayer("entity").staticCast<Game::EntitySceneLayer>();

		Game::SharedEntity l_entity = l_eslayer->getEntity("text");

		Game::SharedTextComponent l_tcomp =
		    l_entity->getComponent("txt").staticCast<Game::TextComponent>();

		char l_message[60];
		sprintf(l_message, MESSAGE, m_stop_timer);
		l_tcomp->text() = l_message;
	}
};

int
MMain(int argc, char *argv[])
{
	MMUNUSED(argc);
	MMUNUSED(argv);
	if (-1 == CHDIR(DEMO_CWD))
		MMFATAL("Failed to change working directory: ""%s"". ABORT!", DEMO_CWD);
	return(Demo().run());
}

