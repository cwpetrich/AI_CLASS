#ifndef _SCAVENGERENVIRONMENT_H_
#define _SCAVENGERENVIRONMENT_H_

namespace ai
{
  namespace Scavenger
  {
    class Environment: public ai::Agent::Environment
    {
      friend class EnvironmentDisplay;
      friend class EnvironmentDisplay3D;    // 3D Display
    public:
      Environment();
      Environment(const ai::Agent::RandomNumber &rand_in, std::vector<ai::Agent::Socket *> *displays_in,
                  const std::string &world_filename_in);
      /*
       * Deletes all Cells in the cells collection.
       */
      ~Environment();

      virtual bool ApplyAction(ai::Agent::Agent *agent, ai::Agent::Action *action);
      virtual void CalculatePerformance(ai::Agent::Agent *agent);
      virtual ai::Agent::Percept *GetPercept(ai::Agent::Agent *agent);
      virtual void Step();
      virtual void Run(const int n_steps);
      virtual void AddAgent(Agent *agent, Location *location);
      virtual ai::Agent::Location *DefaultLocation() const;

      bool SetFullyObservable(const bool value_in);
      bool SetObjectLearning(const bool value_in);
      bool SetMaxCharge(const double value_in);
      bool SetRechargePerTurn(const double value_in);
      bool SetMaxHitPoints(const double value_in);
      bool SetMaxBinVolume(const double value_in);
      bool SetMaxArmMass(const double value_in);
      bool SetLiftDamage(const double value_in);
      bool SetFallDamagePerMeter(const double value_in);
      bool SetRechargeDamage(const double value_in);
      bool SetRechargeCharge(const double value_in);
      bool SetVChargePerMeter(const double value_in);
      bool SetHChargePerMeter(const double value_in);
      bool SetLookCharge(const double value_in);
      bool SetPickupCharge(const double value_in);
      bool SetDropCharge(const double value_in);
      bool SetDepositCharge(const double value_in);
      bool SetExamineCharge(const double value_in);
      bool SetSkipObjectCount(const unsigned int value_in);
      bool SetMaxObjectCount(const unsigned int value_in);
      
      bool   GetFullyObservable() const;
      bool   GetObjectLearning() const;
      double GetMaxCharge() const;
      double GetRechargePerTurn() const;
      double GetMaxHitPoints() const;
      double GetMaxBinVolume() const;
      double GetMaxArmMass() const;
      double GetLiftDamage() const;
      double GetFallDamagePerMeter() const;
      double GetRechargeDamage() const;
      double GetRechargeCharge() const;
      double GetVChargePerMeter() const;
      double GetHChargePerMeter() const;
      double GetLookCharge() const;
      double GetPickupCharge() const;
      double GetDropCharge() const;
      double GetDepositCharge() const;
      double GetExamineCharge() const;
      unsigned int GetSkipObjectCount() const;
      unsigned int GetMaxObjectCount() const;

      bool   MakeEnoughBases(int num_agents);
      
      void check_cells(const std::string &msg);
    protected:
      void TextDisplay(std::ostream &os) const;
      
      bool ReadFile();

      bool MoveAgent(Agent *sw_agent, int action_code);
      bool LookAgent(Agent *sw_agent, Location::Direction direction);
      bool RechargeAgent(Agent *sw_agent);
      bool PickupObject(Agent *sw_agent, const std::string &objec_id_in);
      bool DropObject(Agent *sw_agent, const std::string &objec_id_in);
      bool DepositObject(Agent *sw_agent, const std::string &objec_id_in);
      bool ExamineObject(Agent *sw_agent, const std::string &objec_id_in);
      bool QuitAgent(Agent *sw_agent);

      std::string world_filename;

      std::vector<Base *>                    bases;
      std::map<Location, Cell*>              cells;
      std::map<unsigned int, Cell*>          cells_by_id;
      std::map<std::string, CellInterface *> cell_interfaces;
      unsigned int                           goal_cell_id; // only used in fully observable

      int time_step; // The current time step, starting at 0
      

      bool   fully_observable;
      bool   object_learning;
      double max_charge;
      double recharge_per_turn;
      double max_hit_points;
      double max_bin_volume;
      double max_arm_mass;
      double lift_damage;
      double fall_damage_per_meter;
      double recharge_damage; // trying to recharge at opponent's base
      double recharge_charge; // trying to recharge when not at own base
      double v_charge_per_meter;
      double h_charge_per_meter;
      double look_charge;
      double pickup_charge;
      double drop_charge;
      double deposit_charge;
      double examine_charge;
      unsigned int skip_object_count;
      unsigned int max_object_count;
      
    private:
      friend class boost::serialization::access;
      template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
      {
        ar & boost::serialization::base_object<ai::Agent::Environment>(*this);
        ar & world_filename;
        ar & bases;
        ar & cells;
        ar & cells_by_id;
        ar & cell_interfaces;
        ar & goal_cell_id;
        ar & time_step;
        ar & fully_observable;
        ar & object_learning;
        ar & max_charge;
        ar & recharge_per_turn;
        ar & max_hit_points;
        ar & max_bin_volume;
        ar & max_arm_mass;
        ar & lift_damage;
        ar & fall_damage_per_meter;
        ar & recharge_damage;
        ar & recharge_charge;
        ar & v_charge_per_meter;
        ar & h_charge_per_meter;
        ar & look_charge;
        ar & pickup_charge;
        ar & drop_charge;
        ar & deposit_charge;
        ar & examine_charge;
        ar & skip_object_count;
        ar & max_object_count;
      }
    };
    
  }
}

#endif /* _SCAVENGERENVIRONMENT_H_ */
/* Local Variables: */
/* mode:c++         */
/* End:             */
