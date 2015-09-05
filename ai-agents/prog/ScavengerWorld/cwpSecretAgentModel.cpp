#include "cwpSecretAgentModel.h"

namespace cwp {

	namespace Scavenger {

		SecretAgentModel::SecretAgentModel(){}

		SecretAgentModel::~SecretAgentModel(){}

		void SecretAgentModel::updateCurrLocation(double x, double y, double z){
			curr_x = x;
			curr_y = y;
			curr_z = z;
		}

		double SecretAgentModel::getCurrX(){
			return curr_x;
		}

		double SecretAgentModel::getCurrY(){
			return curr_y;
		}

		double SecretAgentModel::getCurrZ(){
			return curr_z;
		}

		void SecretAgentModel::updateGoalLocation(double x, double y, double z){
			goal_x = x;
			goal_y = y;
			goal_z = z;
		}

		double SecretAgentModel::getGoalX(){
			return goal_x;
		}

		double SecretAgentModel::getGoalY(){
			return goal_y;
		}

		double SecretAgentModel::getGoalZ(){
			return goal_z;
		}

		void SecretAgentModel::addCell(CellData *cell){
			// CellKey* key = new CellKey(cell->loc_x, cell->loc_y);
			known_cells.push_back(cell);
		}

		std::vector<CellData*> SecretAgentModel::getCells(){
			return known_cells;
		}

		void SecretAgentModel::updateCharge(double c){
			this->charge = c;
		}
		double SecretAgentModel::getCharge(){
			return charge;
		}
		void SecretAgentModel::updateHitPoints(double hp){
			this->hit_points = hp;
		}
		double SecretAgentModel::getHitPoints(){
			return hit_points;
		}
		void SecretAgentModel::updateBaseNum(int b){
			this->base_num = b;
		}
		int SecretAgentModel::getBaseNum(){
			return base_num;
		}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		CellData::CellData(){}

		void CellData::updateId(std::string new_id){
			this->id = new_id;
		}
		std::string CellData::getId(){
			return id;
		}
		void CellData::updateCellLocation(double x, double y, double z){
			this->loc_x = x;
			this->loc_y = y;
			this->loc_z = z;
		}
		void CellData::updateLocX(double x){
			this->loc_x = x;
		}
		void CellData::updateLocY(double y){
			this->loc_y = y;
		}
		void CellData::updateLocZ(double z){
			this->loc_z = z;
		}
		double CellData::getLocX(){
			return loc_x;
		}
		double CellData::getLocY(){
			return loc_y;
		}
		double CellData::getLocZ(){
			return loc_z;
		}
		void CellData::updateCellInterfaces(std::string n, std::string s, std::string e, std::string w){
			this->north = n;
			this->south = s;
			this->east = e;
			this->west = w;
		}
		void CellData::updateCellNorth(std::string n){
			this->north = n;
		}
		void CellData::updateCellSouth(std::string s){
			this->south = s;
		}
		void CellData::updateCellEast(std::string e){
			this->east = e;
		}
		void CellData::updateCellWest(std::string w){
			this->west = w;
		}
		std::string CellData::getCellNorth(){
			return north;
		}
		std::string CellData::getCellSouth(){
			return south;
		}
		std::string CellData::getCellEast(){
			return east;
		}
		std::string CellData::getCellWest(){
			return west;
		}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		// CellKey::CellKey(double x, double y){
		// 	this->x = x;
		// 	this->y = y;
		// }

		// double CellKey::getX(){
		// 	return this->x;
		// }

		// double CellKey::getY(){
		// 	return this->y;
		// }

		// std::ostream & operator<(CellKey &lkey, CellKey &rkey){
		// 	if ((lkey->getX() < rkey->getX() && fabs(lkey->getY() - rkey->getY()) < 0.00001) || (lkey->getX() < rkey->getX() && lkey->getY() < rkey->getY())){
		// 		return true;
		// 	}else{
		// 		return false;
		// 	}
		// }

		// std::ostream & operator==(CellKey &lkey, CellKey &rkey){
		// 	if (fabs(lkey->getX() - rkey->getX()) < 0.00001 && fabs(lkey->getY() - rkey->getY()) < 0.00001){
		// 		return true;
		// 	}else{
		// 		return false;
		// 	}
		// }

	}
}