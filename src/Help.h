#pragma once

#include "Command.h"
#include "Option.h"

namespace Clipp
{
    Option createHelpOption();

    Command createHelpCommand();
}