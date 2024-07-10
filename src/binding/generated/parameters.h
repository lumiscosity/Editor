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

#pragma once

// Headers
#include <lcf/rpg/parameters.h>
#include "binding/binding_base.h"
#include "binding/array_adapter.h"

class ProjectData;

/**
 * Binding::Generated::Parameters class.
 * Exposes lcf::rpg::Parameters to QML.
 */
namespace Binding::Generated {
class Parameters : public Binding::BindingBase {
	Q_OBJECT
	Q_PROPERTY(QList<int> maxhp READ maxhp WRITE set_maxhp NOTIFY maxhp_changed)
	Q_PROPERTY(QList<int> maxsp READ maxsp WRITE set_maxsp NOTIFY maxsp_changed)
	Q_PROPERTY(QList<int> attack READ attack WRITE set_attack NOTIFY attack_changed)
	Q_PROPERTY(QList<int> defense READ defense WRITE set_defense NOTIFY defense_changed)
	Q_PROPERTY(QList<int> spirit READ spirit WRITE set_spirit NOTIFY spirit_changed)
	Q_PROPERTY(QList<int> agility READ agility WRITE set_agility NOTIFY agility_changed)

public:
	Parameters(ProjectData& project, lcf::rpg::Parameters& data, QObject* parent = nullptr);

	lcf::rpg::Parameters& data();
	QList<int> maxhp();
	void set_maxhp(const QList<int>& new_maxhp);
	QList<int> maxsp();
	void set_maxsp(const QList<int>& new_maxsp);
	QList<int> attack();
	void set_attack(const QList<int>& new_attack);
	QList<int> defense();
	void set_defense(const QList<int>& new_defense);
	QList<int> spirit();
	void set_spirit(const QList<int>& new_spirit);
	QList<int> agility();
	void set_agility(const QList<int>& new_agility);

signals:
	void maxhp_changed();
	void maxsp_changed();
	void attack_changed();
	void defense_changed();
	void spirit_changed();
	void agility_changed();

protected:
	lcf::rpg::Parameters& m_data;
};
} // namespace Binding::Generated
