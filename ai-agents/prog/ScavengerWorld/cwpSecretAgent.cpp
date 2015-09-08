#include "cwpSecretAgent.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>

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
      std::stringstream ss1;

      int agent_base;
      double agent_x, agent_y, agent_z, agent_hp, agent_charge, agent_goal_x, agent_goal_y, agent_goal_z;

      ss1.str(percept->GetAtom("BASE").GetValue()); ss1.clear();
      ss1 >> agent_base;
      model->updateBaseNum(agent_base);

      ss1.str(percept->GetAtom("X_LOC").GetValue()); ss1.clear();
      ss1 >> agent_x;
      ss1.str(percept->GetAtom("Y_LOC").GetValue()); ss1.clear();
      ss1 >> agent_y;
      ss1.str(percept->GetAtom("Z_LOC").GetValue()); ss1.clear();
      ss1 >> agent_z;
      model->updateCurrLocation(agent_x, agent_y, agent_z);

      ss1.str(percept->GetAtom("CHARGE").GetValue()); ss1.clear();
      ss1 >> agent_charge;
      model->updateCharge(agent_charge);

      ss1.str(percept->GetAtom("HP").GetValue()); ss1.clear();
      ss1 >> agent_hp;
      model->updateHitPoints(agent_hp);

      std::string agent_goal_loc = percept->GetAtom("GOAL_LOC").GetValue();
      ss1.str(agent_goal_loc); ss1.clear();
      ss1 >> agent_goal_x; ss1.ignore();
      ss1 >> agent_goal_y; ss1.ignore();
      ss1 >> agent_goal_z; ss1.ignore();
      model->updateGoalLocation(agent_goal_x, agent_goal_y, agent_goal_z);

      for (uint i = 0; i < percept->NumAtom(); i++){
        if (percept->GetAtom(i).GetName().substr(0, 5) == "CELL_"){
		      std::stringstream ss2;
        	double cell_x, cell_y, cell_z;
      		std::string cell_north, cell_south, cell_east, cell_west;

        	std::string value = percept->GetAtom(i).GetValue();
	        ss2.str(value); ss2.clear();
	        ss2 >> cell_x; ss2.ignore();
	        ss2 >> cell_y; ss2.ignore();
	        ss2 >> cell_z; ss2.ignore();
	        std::getline(ss2, cell_north, ',');
	        std::getline(ss2, cell_south, ',');
	        std::getline(ss2, cell_east, ',');
	        std::getline(ss2, cell_west, ',');

	        model->updateCell(percept->GetAtom(i).GetName().substr(5), cell_x, cell_y, cell_z, cell_north, cell_south, cell_east, cell_west);
        }
      }
      // for (uint i = 0; i < percept->NumAtom(); i++){
      // 	if (percept->GetAtom(i).GetName().substr(0,5) == "CELL_"){
      // 		std::stringstream ss2;
      //   	double cell_x, cell_y, cell_z;
      // 		std::string cell_north, cell_south, cell_east, cell_west;

      //   	std::string value = percept->GetAtom(i).GetValue();
	     //    ss2.str(value); ss2.clear();
	     //    ss2 >> cell_x; ss2.ignore();
	     //    ss2 >> cell_y; ss2.ignore();
	     //    ss2 >> cell_z; ss2.ignore();
	     //    std::getline(ss2, cell_north, ',');
	     //    std::getline(ss2, cell_south, ',');
	     //    std::getline(ss2, cell_east, ',');
	     //    std::getline(ss2, cell_west, ',');
      // 		cwp::Scavenger::CellData* cell = model->getCell(cell_x, cell_y);
      // 		std::ofstream myfile;
		    //   myfile.open("debugging.txt", std::ofstream::out | std::ofstream::app);
		    //   myfile << percept->GetAtom(i).GetName() << "\n";
		    //   myfile << "north: " << cell->getCellNorth() << "\n";
		    //   myfile << "east: " << cell->getCellEast() << "\n";
		    //   myfile << "west: " << cell->getCellWest() << "\n";
		    //   myfile << "south: " << cell->getCellEast() << "\n\n";
		    //   myfile.close();
      // 	}
      // }
      double current_x, current_y;
      current_x = model->getCurrX();
      current_y = model->getCurrY();
      std::ofstream myfile;
      myfile.open("debugging.txt", std::ofstream::out | std::ofstream::app);
      myfile << "InputX: " << current_x << "\n";
      myfile << "InputY: " << current_y << "\n\n";
      cwp::Scavenger::CellData* current_cell = model->getCell(current_x, current_y);
      myfile.close();

      if (current_cell->getCellNorth() == "plain" || current_cell->getCellNorth() == "mud"){
        action->SetCode(ai::Scavenger::Action::GO_NORTH);
      }else if (current_cell->getCellEast() == "plain" || current_cell->getCellEast() == "mud"){
        action->SetCode(ai::Scavenger::Action::GO_EAST);
      }else if (current_cell->getCellWest() == "plain" || current_cell->getCellWest() == "mud"){
        action->SetCode(ai::Scavenger::Action::GO_WEST);
      }else if (current_cell->getCellSouth() == "plain" || current_cell->getCellSouth() == "mud"){
        action->SetCode(ai::Scavenger::Action::GO_SOUTH);
      }else{
        action->SetCode(ai::Scavenger::Action::QUIT);
      }
        // }
      // }

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
