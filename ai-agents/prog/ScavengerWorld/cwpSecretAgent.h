#ifndef _SECRETAGENT_H_
#define _SECRETAGENT_H_

#include <ai_scavenger.h>

namespace cwp
{
  namespace Scavanger
  {
    class SecretAgent : public ai::Agent::AgentProgram
    {
    public:
      SecretAgent(ai::Agent::Options *opts);
      ~SecretAgent();
      virtual ai::Agent::Action * Program(const ai::Agent::Percept * percept);
    protected:
    private:
    };
  }
}

#endif /* _SECRETAGENT_H_ */
