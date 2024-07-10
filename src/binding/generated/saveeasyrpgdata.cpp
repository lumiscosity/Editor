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
#include "saveeasyrpgdata.h"
#include "common/dbstring.h"

namespace Binding::Generated {
	SaveEasyRpgData::SaveEasyRpgData(ProjectData& project, lcf::rpg::SaveEasyRpgData& data, QObject* parent) : Binding::BindingBase(project, parent), m_data(data) {
		{
			m_windows = new ArrayAdapter(this);
			auto& arr = m_windows->data();
			for (auto& var: m_data.windows)
				arr.push_back(new Binding::SaveEasyRpgWindow(m_project, var, this));
		}
	}
	int SaveEasyRpgData::version() {
		return m_data.version;
	}
	void SaveEasyRpgData::set_version(const int& new_version) {
		if (m_data.version == new_version)
			return;
		m_data.version = new_version;
		emit version_changed();
	}

	int SaveEasyRpgData::codepage() {
		return m_data.codepage;
	}
	void SaveEasyRpgData::set_codepage(const int& new_codepage) {
		if (m_data.codepage == new_codepage)
			return;
		m_data.codepage = new_codepage;
		emit codepage_changed();
	}

	ArrayAdapter* SaveEasyRpgData::windows() {
		return m_windows;
	}

} // namespace Binding::Generated
