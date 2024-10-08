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

#include "chipset_widget.h"
#include "common/dbstring.h"
#include "ui_chipset_widget.h"

ChipSetWidget::ChipSetWidget(ProjectData& project, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChipSetWidget),
	m_project(project)
{
	ui->setupUi(this);
}

ChipSetWidget::~ChipSetWidget() {
	delete ui;
}

void ChipSetWidget::setData(lcf::rpg::Chipset* chipset) {
    lower_scene.set_chipset(ToQString(chipset->chipset_name));
    lower_scene.draw_overview(RpgPainter::ALL_LOWER);
    ui->lowerGraphicsView->setScene(&lower_scene);
    upper_scene.force_chipset(lower_scene.share_chipset());
    upper_scene.draw_overview(RpgPainter::ALL_UPPER);
    ui->upperGraphicsView->setScene(&upper_scene);
}
