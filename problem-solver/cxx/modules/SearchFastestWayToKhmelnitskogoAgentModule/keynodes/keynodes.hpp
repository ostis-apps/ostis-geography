#pragma once

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

#include "keynodes.generated.hpp"

namespace SearchFastestWayToKhmelnitskogoAgentModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:
  SC_PROPERTY(Keynode("action_search_fastest_way_to_Khmelnitskogo"), ForceCreate)
  static ScAddr action_search_fastest_way_to_Khmelnitskogo;

  SC_PROPERTY(Keynode("nrel_main_idtf"), ForceCreate)
  static ScAddr nrel_main_idtf;

  SC_PROPERTY(Keynode("concept_parameter"), ForceCreate)
  static ScAddr concept_parameter;
};

}  // namespace SearchFastestWayToKhmelnitskogoAgentModule