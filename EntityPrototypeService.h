/*
 * Asteroids Clone
 * 
 * Copyright (c) 2021 Roman Divotkey. All rights reserved.
 */

#pragma once

// Local includes


// AST-Utilities includes
#include <AstuServices.h>
#include <AstuECS.h>

class EntityPrototypeService : public astu::BaseService
{
public:

	  // Constructor.
	  EntityPrototypeService(bool debug = true);

private:
	  // Whether debug mode is activated.
	  bool debug;

	  // Inherited via BaseService
	  virtual void OnStartup() override;
	  virtual void OnShutdown() override;

	  using Vertices = std::vector<astu::Vector2f>;

	  std::shared_ptr<astu::Entity> CreateBoundary(float w, float h, bool kill);
	  std::shared_ptr<astu::Entity> createBall();
	  std::shared_ptr<astu::Entity> createBlock();
	  std::shared_ptr<astu::Entity> createPaddle();
};