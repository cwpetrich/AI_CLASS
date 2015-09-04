#pragma once

#include <vector>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>

namespace cwp {

	namespace Scavenger {

		class CellData {
		public:
			std::string id;
			double loc_x, loc_y, loc_z;
			std::string north, south, east, west;
		};

		class SecretAgentModel {
		public:
			SecretAgentModel();
			~SecretAgentModel();
			void addCell(CellData* cell);
			std::vector<CellData*> getCells();
			void updateCurrLocation(double x, double y, double z);
			std::vector<double> getCurrLocation();
			void updateCharge(double c);
			double getCharge();
			void updateHitPoints(double hp);
			double getHitPoints();
			void updateBaseNum(int b);
			int getBaseNum();
			// void updateGoalLocation(double x, y);
			// double* SecretAgentModel::getGoalLocation() const;

		protected:
		private:
			std::vector<CellData*> known_cells;
			double curr_x;
			double curr_y;
			double curr_z;
			double charge;
			double hit_points;
			int base_num;
			// double goal_x;
			// double goal_y;
			// double goal_z;
		};

		// class CellKey {
		// public:
		// 	CellKey(double x, double y);
		// 	double getX();
		// 	double getY();

		// private:
		// 	double x;
		// 	double y;

		// };
		// std::ostream & operator==(CellKey &lkey, CellKey &rkey);
		// std::ostream & operator<(CellKey &lkey, CellKey &rkey);

	}
}