/*
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

#include <QString>
#include <lcf/rpg/eventcommand.h>
#include <qcoreapplication.h>

namespace Stringizer {
#ifdef PLEASE_HELP_LINGUIST
	/*
	 * NOTE: We need to help linguist, macro name is totally made up.
	 * See comment at top of source file for reasoning.
	 */
	Q_DECLARE_TR_FUNCTIONS(Stringizer)
#else
	// This is normally copied from qcoreapplication.h by the macro...
	static inline QString tr(const char *sourceText, const char *disambiguation = nullptr, int n = -1)
	{
		return QCoreApplication::translate("stringizer", sourceText, disambiguation, n);
	}
#endif
	QString stringize(const lcf::rpg::EventCommand& com);
}
