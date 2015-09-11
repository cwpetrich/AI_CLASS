#include "cwpSecretAgentState.h"

namespace cwp {
	namespace Scavenger {

		State::State(){}

		State::State(double x, double y){
			this->x = x;
			this->y = y;
		}

		State::State(double x, double y, double c){
			this->x = x;
			this->y = y;
			this->charge = c;
		}

		void State::updateXandY(double x, double y){
			this->x = x;
			this->y = y;
		}

		void State::updateX(double x){
			this->x = x;
		}

		void State::updateY(double y){
			this->y = y;
		}

		void State::updateCharge(double c){
			this->charge = c;
		}

		double State::getX(){
			return x;
		}

		double State::getY(){
			return y;
		}

		double State::getCharge(){
			return charge;
		}

		bool State::IsEqual(const ai::Search::State * const state_in) const{
			const State * const state = dynamic_cast<const State * const>(state_in);
			return (*this) == (*state);
		}

		bool State::IsLessThan(const ai::Search::State * const state_in) const{
			const State * const state = dynamic_cast<const State * const>(state_in);
			return (*this) < (*state);
		}

		bool operator==(const State &rhs){
			if (fabs(this->getX() - rhs.getX()) < 0.00001 && fabs(this->getY() - rhs.getY()) < 0.00001){
				return true;
			}else{
				return false;
			}
		}

		bool operator<(const State &rhs){
			if (this->getCharge() < rhs.getCharge()) {
				return true;
			}else{
				return false;
			}
		}
	}
}