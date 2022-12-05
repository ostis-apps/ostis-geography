#include <sc-memory/cpp/sc_stream.hpp>
 #include <sc-kpm/sc-agents-common/utils/IteratorUtils.hpp>
 #include <sc-kpm/sc-agents-common/utils/GenerationUtils.hpp>
 #include <sc-kpm/sc-agents-common/utils/AgentUtils.hpp>

 #include <iostream>
 #include "VeterinarySearchAgent.hpp"
 #include "keynodes/keynodes.hpp"

 using namespace std;
 using namespace utils;

 namespace VeterinaryModule
 {

 ScAddr getVeterinaryNode(ScLog *logger, std::unique_ptr<ScMemoryContext> &ms_context, ScAddr set){
 	  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);
     ScAddr first = ms_context->HelperFindBySystemIdtf("nrel_Vitebsk_veterinary");  
     logger->Message(ScLog::Type::Info, "Veterinary Vitebsk " + ms_context->HelperGetSystemIdtf(set));  


     ScIterator5Ptr iter = ms_context->Iterator5(set, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, first);
     while(iter->Next()){
     	SC_LOG_ERROR("Found Vitebsk veterinary")
         logger->Message(ScLog::Type::Info, "Veterinary: " + ms_context->HelperGetSystemIdtf(iter->Get(2)));  
         ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, iter->Get(2));                  
         return answer;
     }
     logger->Message(ScLog::Type::Info, "veterinary not found");  


     return answer;
 }

 SC_AGENT_IMPLEMENTATION(VeterinarySearchAgent)
 {
 	SC_LOG_ERROR("VeterinarySearchAgent started")
   ScLog *logger = ScLog::GetInstance();


   if (!edgeAddr.IsValid())
 		return SC_RESULT_ERROR;


   ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);

   ScAddr node  = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
     if (!node.IsValid())
     {
     	SC_LOG_ERROR("Arg not found")
     	return SC_RESULT_ERROR_INVALID_PARAMS; 
     }

   ScAddr answer = getVeterinaryNode(logger,ms_context,node);



   utils::AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);


   return SC_RESULT_OK;
 }
 }