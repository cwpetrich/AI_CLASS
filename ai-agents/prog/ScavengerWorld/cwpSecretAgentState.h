#pragma once

#include <ai_search.h>

namespace cwp {
	namespace Scavenger {

		class State : public ai::Search::State
		{
		public:
			State();
			State(double x, double y);
			State(double x, double y, double c);
			bool operator==(const State &rhs);
			bool operator<(const State &rhs);
			void updateXandY(double x, double y);
			void updateX(double x);
			void updateY(double y);
			void updateCharge(double c);
			bool IsEqual(const ai::Search::State * const state_in) const;
			bool IsLessThan(const ai::Search::State * const state_in) const;
			double getX();
			double getY();
			double getCharge();
		private:
			double x, y, charge;
		};

	}
}