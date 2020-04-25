#ifndef ENTITY_COMMAND
#define ENTITY_COMMAND

#include "command.hpp"
#include "stdpch.hpp"

template<typename EntityType>
class EntityCommand : public Command {
	public:
		EntityCommand(EntityType* entity, std::function<void(EntityType*)> action) : entity(entity) { this->action = action; };
		void execute() override { action(entity); };

	private:
		EntityType* entity;
		std::function<void(EntityType*)> action;
};

#endif
