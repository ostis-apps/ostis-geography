/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-agents-common/utils/CommonUtils.hpp>
#include <sc-agents-common/keynodes/coreKeynodes.hpp>
#include "classifyLakeVAgent.hpp"
#include "sc-core/sc_helper.h"
#include <sc-memory/sc_link.hpp>
#include <sc-memory/sc_wait.hpp>
#include <sc-memory/sc_stream.hpp>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
using namespace utils;

namespace classifyLakeModule
{

	 SC_AGENT_IMPLEMENTATION(classifyLakeVAgent)
		{
		    if (!edgeAddr.IsValid())
	    return SC_RESULT_ERROR;

	  ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
	  ScAddr param = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
	  if (!param.IsValid())
	    return SC_RESULT_ERROR_INVALID_PARAMS;

	  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);
	  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, param);

	  ScIterator5Ptr iterator5 = IteratorUtils::getIterator5(ms_context.get(), param, Keynodes::nrel_volume, true);
	  if(iterator5->Next())
	  {
	  	ScAddr url = iterator5->Get(2);//получаем адрес узла с площадью
        ScLink lnk(*ms_context, url);
        float const val = lnk.Get<float>();
        if (val >= 100)
        {
        	ScAddr edge1 = ms_context->CreateEdge(ScType::EdgeDCommonConst, param, Keynodes::voluminous);
        	ScAddr edge2 = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::nrel_volume_classification, edge1);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge1);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge2);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::voluminous);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::nrel_volume_classification);
        }
        else
        {
        	ScAddr edge1 = ms_context->CreateEdge(ScType::EdgeDCommonConst, param, Keynodes::not_voluminous);
        	ScAddr edge2 = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::nrel_volume_classification, edge1);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge1);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, edge2);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::not_voluminous);
        	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::nrel_volume_classification);
        }
	  }
	  system("echo 5");
	  AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
	  return SC_RESULT_OK;
        }
}
