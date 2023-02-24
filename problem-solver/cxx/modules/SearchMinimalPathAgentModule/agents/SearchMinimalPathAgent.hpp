#pragma once

#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "SearchMinimalPathAgent.generated.hpp"

namespace SearchMinimalPathAgentModule
{

class SearchMinimalPathAgent : public ScAgent
{
  SC_CLASS(Agent, Event(Keynodes::action_search_minimal_path, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()

  static void findMinimalPath(
      ScAddr currentNode,
      ScAddr target,
      int currentLength,
      int& resultLength,
      std::vector<ScAddr>& currentPath,
      std::vector<ScAddr>& result);

  static std::list<ScAddr> getAllIncidentNodes(const ScAddr& node);

  static std::list<ScAddr> getIdentifierMeta(const ScAddr& addr);

  static ScAddr getKmNode(const ScAddr& edge);

  static int getKmCount(ScAddr edge);

  static ScAddr getEdgeBetween(const ScAddr& from, const ScAddr& to, ScType type, bool findReverse);
};

}  // namespace StreetSearchAgentModule