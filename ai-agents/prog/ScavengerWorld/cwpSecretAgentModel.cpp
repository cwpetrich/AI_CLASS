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

		std::vector<double> SecretAgentModel::getCurrLocation() {
			std::vector<double> curr_location;
			curr_location.push_back(curr_x);
			curr_location.push_back(curr_y);
			curr_location.push_back(curr_z);
			return curr_location;
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