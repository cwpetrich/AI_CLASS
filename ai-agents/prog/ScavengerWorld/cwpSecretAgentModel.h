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
			CellData();
			void updateId(std::string new_id);
			std::string getId();
			void updateCellLocation(double x, double y, double z);
			void updateLocX(double x);
			void updateLocY(double y);
			void updateLocZ(double z);
			double getLocX();
			double getLocY();
			double getLocZ();
			void updateCellInterfaces(std::string n, std::string s, std::string e, std::string w);
			void updateCellNorth(std::string n);
			void updateCellSouth(std::string s);
			void updateCellEast(std::string e);
			void updateCellWest(std::string w);
			std::string getCellNorth();
			std::string getCellSouth();
			std::string getCellEast();
			std::string getCellWest();
		private:
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
			double getCurrX();
			double getCurrY();
			double getCurrZ();
			void updateCharge(double c);
			double getCharge();
			void updateHitPoints(double hp);
			double getHitPoints();
			void updateBaseNum(int b);
			int getBaseNum();
			void updateGoalLocation(double x, double y, double z);
			double getGoalX();
			double getGoalY();
			double getGoalZ();

		protected:
		private:
			std::vector<CellData*> known_cells;
			int base_num;
			double curr_x, curr_y, curr_z, charge, hit_points, goal_x, goal_y, goal_z;
		};

		class CellKey {
		public:
			CellKey(double x, double y);

		private:
			double x, y;
		};

		std::ostream & operator==(CellKey &lkey, CellKey &rkey);
		std::ostream & operator<(CellKey &lkey, CellKey &rkey);

	}
}