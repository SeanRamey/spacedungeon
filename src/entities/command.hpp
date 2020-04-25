#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "stdpch.hpp"
#include "entity.hpp"
#include <cassert>

class Command {

	public:
		Command() = default;
		virtual ~Command() {};
		virtual void execute() = 0;

	private:

};

#endif
