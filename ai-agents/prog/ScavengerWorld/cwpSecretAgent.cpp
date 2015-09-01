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
    }

    SecretAgent::~SecretAgent()
    {
    }

    ai::Agent::Action * SecretAgent::Program(const ai::Agent::Percept * percept)
    {
      ai::Scavenger::Action *action = new ai::Scavenger::Action;
      std::stringstream ss;
      
      double agent_x, agent_y, agent_z;
      ss.str(ai::Agent::GetAtom("X_LOC").GetValue()); ss.clear();
      ss >> agent_x;
      ss.str(ai::Agent::GetAtom("Y_LOC").GetValue()); ss.clear();
      ss >> agent_y;
      ss.str(ai::Agent::GetAtom("Z_LOC").GetValue()); ss.clear();
      ss >> agent_z;

      for (int i = 0; i < ai::Agent::NumAtom(); i++){
        double cell_x, cell_y, cell_z;
        std::string value = percept->GetValue(i);
        ss.str(value); ss.clear();
        ss >> cell_x; ss.ignore();
        ss >> cell_y; ss.ignore();
        ss >> cell_z; ss.ignore();

        std::string cell_north, cell_south, cell_east, cell_west;
        std::getline(ss, cell_north, ",");
        std::getline(ss, cell_south, ",");
        std::getline(ss, cell_east, ",");
        std::getline(ss, cell_west, ",");

        if (fabs(agent_x - cell_x) < 0.00001 && fabs(agent_y - cell_y) < 0.00001 && fabs(agent_z - cell_z) < 0.00001){
          if (cell_north == "plain" || cell_north == "mud"){
            action->SetCode(ai::Scavenger::Action::GO_NORTH);
          }else if (cell_east == "plain" || cell_east == "mud"){
            action->SetCode(ai::Scavenger::Action::GO_EAST);
          }else if (cell_west == "plain" || cell_west == "mud"){
            action->SetCode(ai::Scavenger::Action::GO_WEST);
          }else if (cell_south == "plain" || cell_south == "mud"){
            action->SetCode(ai::Scavenger::Action::GO_SOUTH);
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
