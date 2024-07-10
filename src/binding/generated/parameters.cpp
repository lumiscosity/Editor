/* !!!! GENERATED FILE - DO NOT EDIT !!!!
 * --------------------------------------
 *
 * This file is part of EasyRPG Editor.
 *
 * EasyRPG Editor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Editor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Editor. If not, see <http://www.gnu.org/licenses/>.
 */

// Headers
#include "parameters.h"
#include "common/dbstring.h"

namespace Binding::Generated {
	Parameters::Parameters(ProjectData& project, lcf::rpg::Parameters& data, QObject* parent) : Binding::BindingBase(project, parent), m_data(data) {
	}
	QList<int> Parameters::maxhp() {
		return QList<int>(m_data.maxhp.begin(), m_data.maxhp.end());
	}
	void Parameters::set_maxhp(const QList<int>& new_maxhp) {
		if (QList<int>(m_data.maxhp.begin(), m_data.maxhp.end()) == new_maxhp)
			return;
		m_data.maxhp = decltype(m_data.maxhp)(new_maxhp.begin(), new_maxhp.end());
		emit maxhp_changed();
	}

	QList<int> Parameters::maxsp() {
		return QList<int>(m_data.maxsp.begin(), m_data.maxsp.end());
	}
	void Parameters::set_maxsp(const QList<int>& new_maxsp) {
		if (QList<int>(m_data.maxsp.begin(), m_data.maxsp.end()) == new_maxsp)
			return;
		m_data.maxsp = decltype(m_data.maxsp)(new_maxsp.begin(), new_maxsp.end());
		emit maxsp_changed();
	}

	QList<int> Parameters::attack() {
		return QList<int>(m_data.attack.begin(), m_data.attack.end());
	}
	void Parameters::set_attack(const QList<int>& new_attack) {
		if (QList<int>(m_data.attack.begin(), m_data.attack.end()) == new_attack)
			return;
		m_data.attack = decltype(m_data.attack)(new_attack.begin(), new_attack.end());
		emit attack_changed();
	}

	QList<int> Parameters::defense() {
		return QList<int>(m_data.defense.begin(), m_data.defense.end());
	}
	void Parameters::set_defense(const QList<int>& new_defense) {
		if (QList<int>(m_data.defense.begin(), m_data.defense.end()) == new_defense)
			return;
		m_data.defense = decltype(m_data.defense)(new_defense.begin(), new_defense.end());
		emit defense_changed();
	}

	QList<int> Parameters::spirit() {
		return QList<int>(m_data.spirit.begin(), m_data.spirit.end());
	}
	void Parameters::set_spirit(const QList<int>& new_spirit) {
		if (QList<int>(m_data.spirit.begin(), m_data.spirit.end()) == new_spirit)
			return;
		m_data.spirit = decltype(m_data.spirit)(new_spirit.begin(), new_spirit.end());
		emit spirit_changed();
	}

	QList<int> Parameters::agility() {
		return QList<int>(m_data.agility.begin(), m_data.agility.end());
	}
	void Parameters::set_agility(const QList<int>& new_agility) {
		if (QList<int>(m_data.agility.begin(), m_data.agility.end()) == new_agility)
			return;
		m_data.agility = decltype(m_data.agility)(new_agility.begin(), new_agility.end());
		emit agility_changed();
	}

} // namespace Binding::Generated
