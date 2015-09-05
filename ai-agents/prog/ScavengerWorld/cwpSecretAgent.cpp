#include "cwpSecretAgent.h"
#include <cmath>
#include <cstdio>
#include <cstring>

namespace cwp
{
  namespace Scavanger
  {
    /* For more on options look at the files:
     * ai-lib/include/Agent/Options.h
     * ai-lib/src/Agent/Options.cpp
     * al-lib/src/Agent/AgentDriver.cpp
     */
    /*
     * Run with:
     * ./RunProg ./SA_Test -a s -U 1
     */
    SecretAgent::SecretAgent(ai::Agent::Options *opts)
    {
      SetName("SecretAgent");
      std::cout << "The value of the -U option is: " << opts->GetArgInt("user1") << std::endl;
      this->model = new cwp::Scavenger::SecretAgentModel;
    }

    SecretAgent::~SecretAgent()
    {
      delete(model);
    }

    ai::Agent::Action * SecretAgent::Program(const ai::Agent::Percept * percept)
    {
      ai::Scavenger::Action *action = new ai::Scavenger::Action;
      std::stringstream ss;

      double cell_x, cell_y, cell_z;
      std::string cell_north, cell_south, cell_east, cell_west;

      int agent_base;
      double agent_x, agent_y, agent_z, agent_hp, agent_charge, agent_goal_x, agent_goal_y, agent_goal_z;

      ss.str(percept->GetAtom("BASE").GetValue()); ss.clear();
      ss >> agent_base;
      model->updateBaseNum(agent_base);
      ss.str(percept->GetAtom("X_LOC").GetValue()); ss.clear();
      ss >> agent_x;
      ss.str(percept->GetAtom("Y_LOC").GetValue()); ss.clear();
      ss >> agent_y;
      ss.str(percept->GetAtom("Z_LOC").GetValue()); ss.clear();
      ss >> agent_z;
      model->updateCurrLocation(agent_x, agent_y, agent_z);

      ss.str(percept->GetAtom("CHARGE").GetValue()); ss.clear();
      ss >> agent_charge;
      model->updateCharge(agent_charge);
      ss.str(percept->GetAtom("HP").GetValue()); ss.clear();
      ss >> agent_hp;
      model->updateHitPoints(agent_hp);

      std::string agent_goal_loc = percept->GetAtom("GOAL_LOC").GetValue();
      ss.str(agent_goal_loc); ss.clear();
      ss >> agent_goal_x; ss.ignore();
      ss >> agent_goal_y; ss.ignore();
      ss >> agent_goal_z; ss.ignore();


      for (uint i = 0; i < percept->NumAtom(); i++){
        if (percept->GetAtom(i).GetName().substr(0, 5) == "CELL_"){
		      cwp::Scavenger::CellData* cell = new cwp::Scavenger::CellData;
		      cell->updateId(percept->GetAtom(i).GetName().substr(5));

        	std::string value = percept->GetAtom(i).GetValue();
	        ss.str(value); ss.clear();

	        ss >> cell_x; ss.ignore();
	        ss >> cell_y; ss.ignore();
	        ss >> cell_z; ss.ignore();
	        cell->updateCellLocation(cell_x, cell_y, cell_z);

	        std::getline(ss, cell_north, ',');
	        std::getline(ss, cell_south, ',');
	        std::getline(ss, cell_east, ',');
	        std::getline(ss, cell_west, ',');
	        cell->updateCellInterfaces(cell_north, cell_south, cell_east, cell_west);

	        model->addCell(cell);

        }
      }

      std::vector<cwp::Scavenger::CellData*> cells = model->getCells();

      for (uint i = 0; i < cells.size(); i++){

        if (fabs(model->getCurrX() - cells[i]->getLocX()) < 0.00001 && fabs(model->getCurrY() - cells[i]->getLocY()) < 0.00001 && fabs(model->getCurrZ() - cells[i]->getLocZ()) < 0.00001){
          if (cells[i]->getCellNorth() == "plain" || cells[i]->getCellNorth() == "mud"){
            action->SetCode(ai::Scavenger::Action::GO_NORTH);
          }else if (cells[i]->getCellEast() == "plain" || cells[i]->getCellEast() == "mud"){
            action->SetCode(ai::Scavenger::Action::GO_EAST);
          }else if (cells[i]->getCellWest() == "plain" || cells[i]->getCellWest() == "mud"){
            action->SetCode(ai::Scavenger::Action::GO_WEST);
          }else if (cells[i]->getCellSouth() == "plain" || cells[i]->getCellSouth() == "mud"){
            action->SetCode(ai::Scavenger::Action::GO_SOUTH);
          }else{
            action->SetCode(ai::Scavenger::Action::QUIT);
          }
        }        
      }

      return action;
//       unsigned int i;

//       for(i = 0; i < percept->NumAtom(); i++)
//         {
//           ai::Agent::PerceptAtom a = percept->GetAtom(i);
//           if(std::strncmp(a.GetName().c_str(), "CELL_", 5) == 0)
//             {
//               int id;
//               double x,y,z;

//               std::sscanf(a.GetName().c_str(), "CELL_%d", &id);
//               const char *v = a.GetValue().c_str();
//               char *values = new char[std::strlen(v) + 1];
//               std::strcpy(values, v);
//               char *s = std::strtok(values, ",");
//               std::sscanf(s, "%lf", &x);
//               s = std::strtok(NULL, ",");
//               std::sscanf(s, "%lf", &y);
//               s = std::strtok(NULL, ",");
//               std::sscanf(s, "%lf", &z);
//               char *north = std::strtok(NULL, ",");
//               char *south = std::strtok(NULL, ",");
//               char *east  = std::strtok(NULL, ",");
//               char *west  = std::strtok(NULL, ",");
//               std::cout << id << " "
//                         << x << "," << y << "," << z << "  "
//                         << north << " "
//                         << south << " "
//                         << east << " "
//                         << west << " "
//                         << std::endl;
//               delete [] values;
//             }
//           else
//             {
//               std::cout << a.GetName() << ": " << a.GetValue() << std::endl;
//             }
//         }

// #if 0

//       double x, y, z;

//       x = atof(percept->GetAtom("X_LOC").GetValue().c_str());
//       y = atof(percept->GetAtom("Y_LOC").GetValue().c_str());
//       z = atof(percept->GetAtom("Z_LOC").GetValue().c_str());

//       std::cout << x << ", " << y << ", " << z << std::endl;
// #endif

//       {
//         int r = rand() % 2;
//         int d = rand() % 4;
//         if(r == 0)
//           {
//             switch(d)
//               {
//               case 0:
//                 action->SetCode(ai::Scavenger::Action::GO_NORTH);
//                 break;
//               case 1:
//                 action->SetCode(ai::Scavenger::Action::GO_SOUTH);
//                 break;
//               case 2:
//                 action->SetCode(ai::Scavenger::Action::GO_EAST);
//                 break;
//               case 3:
//                 action->SetCode(ai::Scavenger::Action::GO_WEST);
//                 break;
//               }
//           }
//         else
//           {
//             action->SetCode(ai::Scavenger::Action::LOOK);
//             switch(d)
//               {
//               case 0:
//                 action->SetDirection(ai::Scavenger::Location::NORTH);
//                 break;
//               case 1:
//                 action->SetDirection(ai::Scavenger::Location::SOUTH);
//                 break;
//               case 2:
//                 action->SetDirection(ai::Scavenger::Location::EAST);
//                 break;
//               case 3:
//                 action->SetDirection(ai::Scavenger::Location::WEST);
//                 break;
//               }
//           }
//       }

//       return action;
    }
  }
}
